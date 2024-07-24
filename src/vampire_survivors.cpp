#include <sstream>
#include <string.h>
#include "Configuration/Config.h"
#include "ObjectMgr.h"
#include "CreatureScript.h"
#include "GameObjectAI.h"
#include "GameObjectScript.h"
#include "PassiveAI.h"
#include "ScriptMgr.h"
#include "ScriptedGossip.h"
#include "ScriptedCreature.h"
#include "SpellAuraEffects.h"
#include "World.h"
#include "Player.h"
#include "Chat.h"

// What the fuck am I doing

bool VampireSurvivors_Enabled;
bool VampireSurvivors_AnnounceModule;

class VampireSurvivors_conf : public WorldScript
{
public:
    VampireSurvivors_conf() : WorldScript("VampireSurvivors_conf") { }

    void OnBeforeConfigLoad(bool /*reload*/) override
    {
        VampireSurvivors_Enabled        = sConfigMgr->GetOption("VampireSurvivors.Enabled", true);
        VampireSurvivors_AnnounceModule = sConfigMgr->GetOption("VampireSurvivors.Announce", true);
    }
};

// https://github.com/azerothcore/azerothcore-wotlk/blob/master/src/server/game/Scripting/ScriptMgr.h
class VampireSurvivors_Announce : public PlayerScript
{
public:
    VampireSurvivors_Announce() : PlayerScript("VampireSurvivors_Announce") {}

    // Announce Module
    void OnLogin(Player* player) override
    {
        if (VampireSurvivors_AnnounceModule)
        {
            ChatHandler(player->GetSession()).SendSysMessage("This server is running the |cFFFF0000Vampire Survivors|r module.");
        }
    }
};

class VampireSurvivors_Logic : public PlayerScript
{
public:
    VampireSurvivors_Logic() : PlayerScript("VampireSurvivors_Logic") {}

    // On Player Death, checks only for the CurrentPlayer.
    void OnPlayerJustDied(Player* player) override
    {
        if (player)
            player->GetSession()->SendNotification("You suck.");
    }

    void OnLevelChanged(Player* player, uint8 oldLevel) override
    {
        if (player)
            player->GetSession()->SendNotification("Level up!");
    }
};

enum PermaUpgrade
{
    QUEST_VAMPIRE_SURVIVORS = 91000,
    GOSSIP_HELLO            = 11201,
    ITEM_SURVIVORS_GOLD     = 45229,
    
    GOODBYE          = 20,

    TOP_15           = 21,
    REFUND_GOLD      = 22,
    MAPS             = 23,
};

enum Upgrades
{
    // Upgrades
    _MIGHT            = 0,
    _ARMOR            = 1,
    _HEALTH           = 2,
    _RECOVERY         = 3,
    _COOLDOWN         = 4,
    _AREA             = 5,
    _SPEED            = 6,
    _DURATION         = 7,
    _AMOUNT           = 8,
    _MOVESPEED        = 9,
    _MAGNET           = 10,
    _LUCK             = 11,
    _GROWTH           = 12,
    _GREED            = 13
};
// Cast spell with custompoints, depending on upgrade level

// [][MaxRank][BasePrice][BonusPerRank]
const int32 MaxRank[1][14][3] =
{
    {
        {5, 200,  5},   // Might
        {5, 600, -2},   // Armor
        {5, 300,  5},   // Health
        {5, 300,  2},   // Recovery
        {3, 1000, 3},   // Cooldown // 3.3
        {3, 600,  5},   // Area
        {3, 400,  10},  // Speed
        {3, 500,  10},  // Duration
        {2, 5000, 1},   // Amount
        {5, 400,  2},   // Movespeed
        {3, 300,  1},   // Magnet // +1 yard
        {3, 700,  10},  // Luck
        {5, 900,  3},   // Growth
        {5, 300,  10},  // Greed
    },
};

class npc_vs_upgrade : public CreatureScript
{
public:
    npc_vs_upgrade() : CreatureScript("npc_vs_upgrade") {}

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (creature->IsQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        QueryResult result = CharacterDatabase.Query("SELECT * FROM `vampiresurvivors` WHERE `CharacterGUID` = '{}'", player->GetGUID().GetCounter());
        if (result)
        {
            Field *fields = result->Fetch();
            //guid playerGUID = fields[0].Get<guid>();
            uint32 Highscore = fields[1].Get<uint32>();
            uint32 GoldSpent = fields[2].Get<uint32>();
            uint8 Maps = fields[3].Get<uint8>();
            uint8 Might = fields[4].Get<uint8>();
            uint8 Armor = fields[5].Get<uint8>();
            uint8 Health = fields[6].Get<uint8>();
            uint8 Recovery = fields[7].Get<uint8>();
            uint8 Cooldown = fields[8].Get<uint8>();
            uint8 Area = fields[9].Get<uint8>();
            uint8 Speed = fields[10].Get<uint8>();
            uint8 Duration = fields[11].Get<uint8>();
            uint8 Amount = fields[12].Get<uint8>();
            uint8 Movespeed = fields[13].Get<uint8>();
            uint8 Magnet = fields[14].Get<uint8>();
            uint8 Luck = fields[15].Get<uint8>();
            uint8 Growth = fields[16].Get<uint8>();
            uint8 Greed = fields[17].Get<uint8>();

            AddGossipItemFor(player, GOSSIP_ICON_DOT, "=== Menu ===", GOSSIP_SENDER_MAIN, 0);

            std::stringstream gossip;
            // Highscore & TOP_15
            gossip << "|TInterface\\Icons\\achievement_zone_arathihighlands_01:32|t Your Highscore: " << Highscore;
            AddGossipItemFor(player, GOSSIP_ICON_DOT, gossip.str(), GOSSIP_SENDER_MAIN, TOP_15);

            // Refund Gold
            gossip.str("");
            gossip << "|TInterface\\Icons\\inv_misc_coin_01:32|t Refund Gold: " << GoldSpent;
            AddGossipItemFor(player, GOSSIP_ICON_DOT, gossip.str(), GOSSIP_SENDER_MAIN, REFUND_GOLD, "Are you sure that you want to reset your upgrades?", 0, false);

            /*
            // Maps
            gossip.str("");
            gossip << "|TInterface\\Icons\\inv_misc_map02:32|t Unlocked Maps: " << Maps;
            AddGossipItemFor(player, GOSSIP_ICON_DOT, gossip.str(), GOSSIP_SENDER_MAIN, 0);
            AddGossipItemFor(player, GOSSIP_ICON_DOT, "=============================", GOSSIP_SENDER_MAIN, 0);
            */

            AddGossipItemFor(player, GOSSIP_ICON_DOT, "=== Upgrades ===", GOSSIP_SENDER_MAIN, 0);

            // 1 Might
            gossip.str("");
            gossip << "|TInterface\\Icons\\spell_nature_strength:32|t Might" << DisplayPrice(Might, _MIGHT) << "\n" << DisplayLevel(Might, 5) << "\nRaises inflicted Damage by 5% per rank (max +25%)";
            AddGossipItemFor(player, GOSSIP_ICON_DOT, gossip.str(), GOSSIP_SENDER_MAIN, _MIGHT);

            // 2 ARMOR
            gossip.str("");
            gossip << "|TInterface\\Icons\\inv_misc_armorkit_19:32|t Armor" << DisplayPrice(Armor, _ARMOR) << "\n" << DisplayLevel(Armor, 5) << "\nReduces incoming Damage by 2% per rank (max -10%)";
            AddGossipItemFor(player, GOSSIP_ICON_DOT, gossip.str(), GOSSIP_SENDER_MAIN, _ARMOR);

            // 3 Health
            gossip.str("");
            gossip << "|TInterface\\Icons\\inv_gizmo_runichealthinjector:32|t Health" << DisplayPrice(Health, _HEALTH) << "\n" << DisplayLevel(Health, 5) << "\nAugments Max Health by 5% per rank (max +25%)";
            AddGossipItemFor(player, GOSSIP_ICON_DOT, gossip.str(), GOSSIP_SENDER_MAIN, _HEALTH);

            // 4 Recovery
            gossip.str("");
            gossip << "|TInterface\\Icons\\spell_nature_rejuvenation:32|t Recovery" << DisplayPrice(Recovery, _RECOVERY) << "\n" << DisplayLevel(Recovery, 5) << "\nRecovers 2 HP per rank (max 10 HP) per second.";
            AddGossipItemFor(player, GOSSIP_ICON_DOT, gossip.str(), GOSSIP_SENDER_MAIN, _RECOVERY);

            // 5 Cooldown
            gossip.str("");
            gossip << "|TInterface\\Icons\\inv_misc_book_04:32|t Cooldown" << DisplayPrice(Cooldown, _COOLDOWN) << "\n" << DisplayLevel(Cooldown, 3) << "\nUses weapons 3.3% faster per rank (max 10%).";
            AddGossipItemFor(player, GOSSIP_ICON_DOT, gossip.str(), GOSSIP_SENDER_MAIN, _COOLDOWN);

            // 6 Area
            gossip.str("");
            gossip << "|TInterface\\Icons\\achievement_zone_outland_01:32|t Area" << DisplayPrice(Area, _AREA) << "\n" << DisplayLevel(Area, 3) << "\nAugments area of attacks by 5% per rank (max +15%).";
            AddGossipItemFor(player, GOSSIP_ICON_DOT, gossip.str(), GOSSIP_SENDER_MAIN, _AREA);

            // 7 Speed
            gossip.str("");
            gossip << "|TInterface\\Icons\\inv_ammo_arrow_04:32|t Speed" << DisplayPrice(Speed, _SPEED) << "\n" << DisplayLevel(Speed, 3) << "\nProjectiles move 10% faster per rank (max +30%).";
            AddGossipItemFor(player, GOSSIP_ICON_DOT, gossip.str(), GOSSIP_SENDER_MAIN, _SPEED);

            // 8 Duration
            gossip.str("");
            gossip << "|TInterface\\Icons\\inv_scarab_silver:32|t Duration" << DisplayPrice(Duration, _DURATION) << "\n" << DisplayLevel(Duration, 3) << "\nEffects from weapons last 10% longer per rank (max +30%).";
            AddGossipItemFor(player, GOSSIP_ICON_DOT, gossip.str(), GOSSIP_SENDER_MAIN, _DURATION);

            // 9 Amount
            gossip.str("");
            gossip << "|TInterface\\Icons\\inv_qiraj_ringmagisterial:32|t Amount" << DisplayPrice(Amount, _AMOUNT) << "\n" << DisplayLevel(Amount, 2) << "\nFires 1 more projectile (all weapons) (max 2).";
            AddGossipItemFor(player, GOSSIP_ICON_DOT, gossip.str(), GOSSIP_SENDER_MAIN, _AMOUNT);

            // 10 Movespeed
            gossip.str("");
            gossip << "|TInterface\\Icons\\spell_fire_burningspeed:32|t Movespeed" << DisplayPrice(Movespeed, _MOVESPEED) << "\n" << DisplayLevel(Movespeed, 5) << "\nCharacter moves 2% faster per rank (max 10%).";
            AddGossipItemFor(player, GOSSIP_ICON_DOT, gossip.str(), GOSSIP_SENDER_MAIN, _MOVESPEED);

            // 11 Magnet
            gossip.str("");
            gossip << "|TInterface\\Icons\\ability_vehicle_siegeengineram:32|t Magnet" << DisplayPrice(Magnet, _MAGNET) << "\n" << DisplayLevel(Magnet, 3) << "\nItems pickup range +20% per rank (max +60%).";
            AddGossipItemFor(player, GOSSIP_ICON_DOT, gossip.str(), GOSSIP_SENDER_MAIN, _MAGNET);

            // 12 Luck
            gossip.str("");
            gossip << "|TInterface\\Icons\\inv_misc_missilesmallcluster_green:32|t Luck" << DisplayPrice(Luck, _LUCK) << "\n" << DisplayLevel(Luck, 3) << "\nChance to get lucky goes up by 10% per rank (max +30%).";
            AddGossipItemFor(player, GOSSIP_ICON_DOT, gossip.str(), GOSSIP_SENDER_MAIN, _LUCK);
            
            // 13 Growth
            gossip.str("");
            gossip << "|TInterface\\Icons\\inv_crown_01:32|t Growth" << DisplayPrice(Growth, _GROWTH) << "\n" << DisplayLevel(Growth, 5) << "\nGains 3% more experience per rank (max +15%).";
            AddGossipItemFor(player, GOSSIP_ICON_DOT, gossip.str(), GOSSIP_SENDER_MAIN, _GROWTH);
            
            // 14 Greed
            gossip.str("");
            gossip << "|TInterface\\Icons\\inv_misc_bomb_04:32|t Greed" << DisplayPrice(Greed, _GREED) << "\n" << DisplayLevel(Greed, 5) << "\nGains 10% more coins per rank (max +50%).";
            AddGossipItemFor(player, GOSSIP_ICON_DOT, gossip.str(), GOSSIP_SENDER_MAIN, _GREED);

            gossip.str("");
        }

        SendGossipMenuFor(player, GOSSIP_HELLO, creature->GetGUID());
        return true;
    }

    // Current Skill Level / Max Skill Level
    std::string DisplayLevel(uint16 upgrade, uint16 max)
    {
        std::stringstream level;
        level.str("");
        for (uint8 i = 0; i < upgrade; i++)
        {
            level << "+";
        }
        if (upgrade != max)
        {
            for (uint8 i = upgrade; i < max; i++)
            {
                level << "-";
            }
        }
        level << " (" << upgrade << "/" << max << ")";
        return level.str();
    }

    // CurrentLevel, Skill
    std::string DisplayPrice(uint32 currentLevel, uint32 skill)
    {
        std::stringstream price;
        price.str("");
        uint32 maxLevel = MaxRank[0][skill][0];
        uint32 cost = MaxRank[0][skill][1];
        uint32 totalprice = currentLevel == 0 ? cost : cost * (currentLevel + 1);

        if (currentLevel < maxLevel)
        {
           price << "   |TInterface\\Icons\\inv_misc_coin_01:16|t " << totalprice;
           return price.str();
        }
        else
        {
            price.str("");
            return price.str();
        }
    }

    // Adds to the permanent upgrade
    void AddPermanentUpgrade(std::string name, uint32 skill, Player* player)
    {
        QueryResult result = CharacterDatabase.Query("SELECT `{}`, `GoldSpent` FROM `vampiresurvivors` WHERE `CharacterGUID` = '{}'", name, player->GetGUID().GetCounter());
        if (result)
        {
            Field *fields = result->Fetch();
            uint32 currentLevel = fields[0].Get<uint32>();
            uint32 currentgold = fields[1].Get<uint32>();

            uint32 maxLevel = MaxRank[0][skill][0];
            uint32 cost = MaxRank[0][skill][1];

            if (currentLevel == maxLevel)
                player->GetSession()->SendNotification("This skill is already at max level.");

            if (currentLevel < maxLevel)
            {
                uint32 price = currentLevel == 0 ? cost : cost * (currentLevel + 1);
                if (player->HasItemCount(ITEM_SURVIVORS_GOLD, price))
                {
                    player->DestroyItemCount(ITEM_SURVIVORS_GOLD, price, true);
                    CharacterDatabase.DirectExecute("UPDATE `vampiresurvivors` SET `{}` = '{}', `GoldSpent` = '{}' WHERE `CharacterGUID` = '{}';", name, currentLevel + 1, currentgold + price,  player->GetGUID().GetCounter());
                    player->GetSession()->SendNotification("Upgrade has been successfully purchased!");
                }
                else
                    player->GetSession()->SendNotification("Not enough survivor's gold.");
            }
        }
    }

    bool OnGossipSelect(Player* player, Creature*  creature, uint32 /*sender*/, uint32 action) override
    {
        ClearGossipMenuFor(player);

        switch (action)
        {
            case GOODBYE:
            {
                CloseGossipMenuFor(player);
                break;
            }
            // Reset skills and refund gold
            case REFUND_GOLD:
            {
                QueryResult result = CharacterDatabase.Query("SELECT `GoldSpent` FROM `vampiresurvivors` WHERE `CharacterGUID` = '{}'", player->GetGUID().GetCounter());
                if (result)
                {
                    Field *fields = result->Fetch();
                    uint32 gold = fields[0].Get<uint32>();
                    if (gold == 0)
                            player->GetSession()->SendNotification("Nothing to refund.");
                    else if (player->GetFreeInventorySpace())
                    {
                        player->GetSession()->SendNotification("Your gold has been refunded.");
                        player->AddItem(ITEM_SURVIVORS_GOLD, gold);
                        CharacterDatabase.DirectExecute("UPDATE `vampiresurvivors` SET `GoldSpent` = '0', `Might` = '0', `Armor` = '0', `Health` = '0', `Recovery` = '0', `Cooldown` = '0', `Area` = '0', `Speed` = '0', `Duration` = '0', `Amount` = '0', `Movespeed` = '0', `Magnet` = '0', `Luck` = '0', `Growth` = '0', `Greed` = '0' WHERE `CharacterGUID` = '{}'", player->GetGUID().GetCounter());
                    }
                    else
                        player->GetSession()->SendNotification("Not enough inventory space. Refunding gold has failed!");
                }
                CloseGossipMenuFor(player);
                break;
            }
            case TOP_15:
            {
                QueryResult result = CharacterDatabase.Query("SELECT `CharacterGUID`, `Highscore` FROM `vampiresurvivors` ORDER BY `Highscore` DESC LIMIT 15");
                if (!result)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_DOT, "Position - Name - Score", GOSSIP_SENDER_MAIN, GOODBYE);
                    AddGossipItemFor(player, GOSSIP_ICON_DOT, "Leaderboard is empty.", GOSSIP_SENDER_MAIN, GOODBYE);
                    SendGossipMenuFor(player, GOSSIP_HELLO, creature->GetGUID());
                }
                else
                {
                    AddGossipItemFor(player, GOSSIP_ICON_DOT, "Position - Name - Score", GOSSIP_SENDER_MAIN, GOODBYE);
                    uint32 top = 1;
                    do {
                        Field *fields = result->Fetch();
                        ObjectGuid pguid = ObjectGuid::Create<HighGuid::Player>((*result)[0].Get<uint32>());
                        std::string hiscore = fields[1].Get<std::string>();

                        std::string playername;
                        sCharacterCache->GetCharacterNameByGuid(pguid, playername);

                        std::stringstream buffer;
                        buffer << top << ". [" << playername << "]  - " << hiscore;

                        AddGossipItemFor(player, GOSSIP_ICON_DOT, buffer.str(), GOSSIP_SENDER_MAIN, GOODBYE);

                        top++;
                    } while(result->NextRow());
                }
                SendGossipMenuFor(player, GOSSIP_HELLO, creature->GetGUID());
                break;
            }
            case _MIGHT:
            {
                AddPermanentUpgrade("Might", _MIGHT, player);
                CloseGossipMenuFor(player);
                break;
            }
            case _ARMOR:
            {
                AddPermanentUpgrade("Armor", _ARMOR, player);
                CloseGossipMenuFor(player);
                break;
            }
            case _HEALTH:
            {
                AddPermanentUpgrade("Health", _HEALTH, player);
                CloseGossipMenuFor(player);
                break;
            }
            case _RECOVERY:
            {
                AddPermanentUpgrade("Recovery", _RECOVERY, player);
                CloseGossipMenuFor(player);
                break;
            }
            case _COOLDOWN:
            {
                AddPermanentUpgrade("Cooldown", _COOLDOWN, player);
                CloseGossipMenuFor(player);
                break;
            }
            case _AREA:
            {
                AddPermanentUpgrade("Area", _AREA, player);
                CloseGossipMenuFor(player);
                break;
            }
            case _SPEED:
            {
                AddPermanentUpgrade("Speed", _SPEED, player);
                CloseGossipMenuFor(player);
                break;
            }
            case _DURATION:
            {
                AddPermanentUpgrade("Duration", _DURATION, player);
                CloseGossipMenuFor(player);
                break;
            }
            case _AMOUNT:
            {
                AddPermanentUpgrade("Amount", _AMOUNT, player);
                CloseGossipMenuFor(player);
                break;
            }
            case _MOVESPEED:
            {
                AddPermanentUpgrade("Movespeed", _MOVESPEED, player);
                CloseGossipMenuFor(player);
                break;
            }
            case _MAGNET:
            {
                AddPermanentUpgrade("Magnet", _MAGNET, player);
                CloseGossipMenuFor(player);
                break;
            }
            case _LUCK:
            {
                AddPermanentUpgrade("Luck", _LUCK, player);
                CloseGossipMenuFor(player);
                break;
            }
            case _GROWTH:
            {
                AddPermanentUpgrade("Growth", _GROWTH, player);
                CloseGossipMenuFor(player);
                break;
            }
            case _GREED:
            {
                AddPermanentUpgrade("Greed", _GREED, player);
                CloseGossipMenuFor(player);
                break;
            }
        }
        return true;
    }

    bool OnQuestReward(Player* player, Creature* /*creature*/, const Quest* Quest, uint32 /*slot*/) override
    {
        if (Quest->GetQuestId() == QUEST_VAMPIRE_SURVIVORS)
        {
            // Register player upon quest completion
            QueryResult result = CharacterDatabase.Query("SELECT `CharacterGUID` FROM `vampiresurvivors` WHERE `CharacterGUID` = '{}'", player->GetGUID().GetCounter());
            if (!result)
            {
                CharacterDatabase.DirectExecute("REPLACE INTO `vampiresurvivors` (`CharacterGUID`) VALUES ('{}')", player->GetGUID().GetCounter());
            }
        }
        return false;
    }
};

enum Creatures
{   
    // Misc 210000+
    NPC_SPAWNER    = 210002,
    NPC_VS_MAGNET  = 210003,
    NPC_VS_C_LOGIC = 210004,

    // EXP Creatures 210100+
    NPC_EXP_BLUE   = 210100,

    // 1-5
    // Fighting Creatures 211000+
    NPC_VS_KOBOLD  = 211000,
    NPC_VS_IMP     = 211001,
};

enum Actions
{
    ACTION_SUMMON_TEST = 1,
};

enum GossipStartGame
{
    START_GAME = 100,
    CHANGE_HERO = 101,
};

class npc_vs_game_start : public CreatureScript
{
public:
    npc_vs_game_start() : CreatureScript("npc_vs_game_start") {}

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        AddGossipItemFor(player, GOSSIP_ICON_DOT, "=== Menu ===", GOSSIP_SENDER_MAIN, 0);
        AddGossipItemFor(player, GOSSIP_ICON_DOT, "Start Game", GOSSIP_SENDER_MAIN, START_GAME);
        AddGossipItemFor(player, GOSSIP_ICON_DOT, "Current Hero: Crush Flynn", GOSSIP_SENDER_MAIN, CHANGE_HERO);

        if (player->IsGameMaster())
        {
            AddGossipItemFor(player, GOSSIP_ICON_DOT, "=== GM Menu ===", GOSSIP_SENDER_MAIN, 0);
            AddGossipItemFor(player, GOSSIP_ICON_DOT, "Cast Recovery 2hps", GOSSIP_SENDER_MAIN, 1);
            AddGossipItemFor(player, GOSSIP_ICON_DOT, "Cast Armor 2%", GOSSIP_SENDER_MAIN, 2);
            AddGossipItemFor(player, GOSSIP_ICON_DOT, "=== Spawn Menu ===", GOSSIP_SENDER_MAIN, 0);
            AddGossipItemFor(player, GOSSIP_ICON_DOT, "Spawn 5 Kobolds & 5 imps", GOSSIP_SENDER_MAIN, 3);
            AddGossipItemFor(player, GOSSIP_ICON_DOT, "Summon Magnet NPC", GOSSIP_SENDER_MAIN, 4);
            AddGossipItemFor(player, GOSSIP_ICON_DOT, "Summon Central Logic NPC", GOSSIP_SENDER_MAIN, 5);
        }

        SendGossipMenuFor(player, GOSSIP_HELLO, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature*  creature, uint32 /*sender*/, uint32 action) override
    {
        ClearGossipMenuFor(player);

        switch (action)
        {
            case START_GAME:
            {
                player->RemoveAllAuras();

                if (Creature* magnet = player->SummonCreature(NPC_VS_MAGNET, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 960000))
                {
                    magnet->GetMotionMaster()->Clear(false);
                    magnet->GetMotionMaster()->MoveFollow(player, 0, 0, MOTION_SLOT_IDLE);
                }
                if (Creature* clogic = player->SummonCreature(NPC_VS_C_LOGIC, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 960000))
                {
                    clogic->GetMotionMaster()->Clear(false);
                    clogic->GetMotionMaster()->MoveFollow(player, 0, 0, MOTION_SLOT_IDLE);
                }
                CloseGossipMenuFor(player);
                break;
            }
            case 1:
            {
                player->CastCustomSpell(210004, SPELLVALUE_BASE_POINT0, 2, player, true);
                CloseGossipMenuFor(player);
                break;
            }
            case 2:
            {
                player->CastCustomSpell(210002, SPELLVALUE_BASE_POINT0, -20, player, true);
                CloseGossipMenuFor(player);
                break;
            }
            case 3:
            {
                if (Creature* spawner = creature->FindNearestCreature(NPC_SPAWNER, 50))
                    spawner->AI()->DoAction(ACTION_SUMMON_TEST);
                CloseGossipMenuFor(player);
                break;
            }
            case 4:
            {
                if (Creature* magnet = player->SummonCreature(NPC_VS_MAGNET, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 960000))
                {
                    magnet->GetMotionMaster()->Clear(false);
                    magnet->GetMotionMaster()->MoveFollow(player, 0, 0, MOTION_SLOT_IDLE);
                }
                CloseGossipMenuFor(player);
                break;
            }
            case 5:
            {
                if (Creature* clogic = player->SummonCreature(NPC_VS_C_LOGIC, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 960000))
                {
                    clogic->GetMotionMaster()->Clear(false);
                    clogic->GetMotionMaster()->MoveFollow(player, 0, 0, MOTION_SLOT_IDLE);
                }
                CloseGossipMenuFor(player);
                break;
            }
        }
        return true;
    }
};

class npc_vs_spawner : public CreatureScript
{
public:
    npc_vs_spawner() : CreatureScript("npc_vs_spawner") { }

    struct npc_vs_spawnerAI : public ScriptedAI
    {
        npc_vs_spawnerAI(Creature* creature) : ScriptedAI(creature), summons(me) {}

        void JustSummoned(Creature* cr) override
        {
            summons.Summon(cr);
        }

        void SummonedCreatureDespawn(Creature* /*summon*/) override {}

        void SummonedCreatureEvade(Creature* summon) override
        {
            summon->DespawnOrUnsummon();
        }

        void SummonedCreatureDies(Creature* summon, Unit* /*killer*/) override
        {
            if (summon)
            {
                summon->DespawnOrUnsummon();
                // Chance to drop EXP
                if (roll_chance_i(50))
                    me->SummonCreature(NPC_EXP_BLUE, summon->GetPositionX(), summon->GetPositionY(), summon->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 180000);
            }
        }

        void DoAction(int32 action) override
        {
            if (action == ACTION_SUMMON_TEST)
            {
                for (uint8 i = 0; i < 5; i++)
                {
                    me->SummonCreature(NPC_VS_KOBOLD, me->GetPositionX() + urand(1,4), me->GetPositionY() + urand(1,4), me->GetPositionZ() + 2, 0, TEMPSUMMON_TIMED_DESPAWN, 180000);
                    me->SummonCreature(NPC_VS_IMP, me->GetPositionX() + urand(1,4), me->GetPositionY() + urand(1,4), me->GetPositionZ() + 2, 0, TEMPSUMMON_TIMED_DESPAWN, 180000);
                }
            }
        }

    private:
        SummonList summons;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_vs_spawnerAI (creature);
    }
};

enum EXP_NPC
{
    SPELL_DAZE_IMMUNITY        = 57416,

    SPELL_BLUE_EXP             = 210015, // Stacks up to 1000
    SPELL_MAGNET_UPGRADE       = 210011, 
    EVENT_CHECK_FOR_NEARBY     = 1,
    EVENT_CHECK_MAGNET_COLLECT = 2,
};

class npc_vs_exp : public CreatureScript
{
public:
    npc_vs_exp() : CreatureScript("npc_vs_exp") { }

    struct npc_vs_expAI : public ScriptedAI
    {
        npc_vs_expAI(Creature* creature) : ScriptedAI(creature)
        {
            events.ScheduleEvent(EVENT_CHECK_FOR_NEARBY, 2s);
        }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);
            {
                {
                    switch (events.ExecuteEvent())
                    {
                        case EVENT_CHECK_FOR_NEARBY:
                        {
                            if (me->GetEntry() == NPC_EXP_BLUE)
                            {
                                ObjectGuid myguid = me->GetGUID();
                                std::list<Creature*> creatureList;
                                me->GetCreatureListWithEntryInGrid(creatureList, NPC_EXP_BLUE, 5);
                                for (Creature* cnear : creatureList)
                                {
                                    if (cnear && cnear->IsAlive() && cnear->GetGUID() != myguid)
                                    {
                                        // Eat first slime
                                        if (!cnear->HasAura(SPELL_BLUE_EXP) && !me->HasAura(SPELL_BLUE_EXP))
                                        {
                                            me->AddAura(SPELL_BLUE_EXP, me);
                                            cnear->DespawnOrUnsummon();
                                            break;
                                        }
                                        // cnear no aura
                                        if (!cnear->HasAura(SPELL_BLUE_EXP) && me->HasAura(SPELL_BLUE_EXP))
                                        {
                                            if (Aura* aur = me->GetAura(SPELL_BLUE_EXP))
                                            {
                                                me->SetAuraStack(SPELL_BLUE_EXP, me, aur->GetStackAmount() + 1);
                                                cnear->DespawnOrUnsummon();
                                                break;
                                            }
                                        }
                                        // me no aura
                                        if (cnear->HasAura(SPELL_BLUE_EXP) && !me->HasAura(SPELL_BLUE_EXP))
                                        {
                                            if (Aura* aur = cnear->GetAura(SPELL_BLUE_EXP))
                                            {
                                                cnear->SetAuraStack(SPELL_BLUE_EXP, cnear, aur->GetStackAmount() + 1);
                                                me->DespawnOrUnsummon();
                                                break;
                                            }
                                        }
                                        // Eat stacks off other slime. The highest stack creature should remain
                                        if (cnear->HasAura(SPELL_BLUE_EXP) && me->HasAura(SPELL_BLUE_EXP))
                                        {
                                            if (Aura* caura = cnear->GetAura(SPELL_BLUE_EXP))
                                            {
                                                if (Aura* aur = me->GetAura(SPELL_BLUE_EXP))
                                                {
                                                    // We have more stacks
                                                    if (aur->GetStackAmount() >= caura->GetStackAmount())
                                                    {
                                                        me->SetAuraStack(SPELL_BLUE_EXP, me, aur->GetStackAmount() + caura->GetStackAmount());
                                                        cnear->DespawnOrUnsummon();
                                                    }
                                                    // Target has more stacks
                                                    else if (caura->GetStackAmount() > aur->GetStackAmount())
                                                    {
                                                        cnear->SetAuraStack(SPELL_BLUE_EXP, cnear, caura->GetStackAmount() + aur->GetStackAmount());
                                                        me->DespawnOrUnsummon();
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            events.ScheduleEvent(EVENT_CHECK_FOR_NEARBY, 2s);
                            break;
                        }
                    }
                }
            }
        }

        private:
            EventMap events;
        };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_vs_expAI (creature);
    }
};

enum Magnet
{
    SETDATA_MAGNET_ADD_RANGE  = 1, // SetData: 1 | range
    SETDATA_MAGNET_GLOBAL_EXP = 2, // SetData: 1 | uint32 to float (e.g 15 * 100 -> 0.15)

};

float const BLUE_EXP = 20.0f;

class npc_vs_magnet : public CreatureScript
{
public:
    npc_vs_magnet() : CreatureScript("npc_vs_magnet") { }

    struct npc_vs_magnetAI : public ScriptedAI
    {
        npc_vs_magnetAI(Creature* creature) : ScriptedAI(creature)
        {
            // Calculate pullrange based on magnet upgrades, done only once, on summon of the magnet.
            if (WorldObject* owner = me->ToTempSummon()->GetSummoner())
            {
                if (Player* p = owner->ToPlayer())
                {
                    pullrange = 5;
                    global_exp_modifier = 0.0f;
                    ownerGUID = p->ToPlayer()->GetGUID();
                }
            }
            else
                me->DespawnOrUnsummon();

            events.ScheduleEvent(EVENT_CHECK_MAGNET_COLLECT, 250ms);
        }

        Player* GetPlayer() {return ObjectAccessor::GetPlayer(*me, ownerGUID);}

        // Magnet increase by a flat range, e.g +2 yards
        void SetData(uint32 type, uint32 id) override
        {
            if (type == SETDATA_MAGNET_ADD_RANGE)
                pullrange += id;

            if (type == SETDATA_MAGNET_GLOBAL_EXP)
                global_exp_modifier += (float)id / (float)100;
        }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);
            {
                {
                    switch (events.ExecuteEvent())
                    {
                        case EVENT_CHECK_MAGNET_COLLECT:
                        {
                            {
                                std::list<Creature*> ExpBlueList;
                                me->GetCreatureListWithEntryInGrid(ExpBlueList, NPC_EXP_BLUE, pullrange);
                                float EXP_BLUE_STACKS = 1; // Offset by 1, 2 slimes = 1 stack
                                for (Creature* creature : ExpBlueList)
                                {
                                    if (creature && creature->IsAlive())
                                    {
                                        if (creature->HasAura(SPELL_BLUE_EXP))
                                        {
                                            if (Aura* aur = creature->GetAura(SPELL_BLUE_EXP))
                                            {
                                                if (aur->GetStackAmount())
                                                {
                                                    // Xx EXP, depending on slime collected stacks
                                                    EXP_BLUE_STACKS += aur->GetStackAmount();
                                                    creature->DespawnOrUnsummon();
                                                }
                                            }
                                        }

                                        // 1x EXP if no stacks
                                        creature->DespawnOrUnsummon();
                                        if (Player* player = GetPlayer())
                                        {
                                            uint32 calcexp = BLUE_EXP + (BLUE_EXP * global_exp_modifier);
                                            player->GiveXP(((calcexp) * EXP_BLUE_STACKS), nullptr);
                                        }
                                    }
                                }
                            }
                            events.ScheduleEvent(EVENT_CHECK_MAGNET_COLLECT, 250ms);
                            break;
                        }
                    }
                }
            }
        }

        private:
            EventMap events;
            ObjectGuid ownerGUID;
            uint32 pullrange;
            float global_exp_modifier;
        };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_vs_magnetAI (creature);
    }
};

enum CentralLogic
{
    EVENT_CALCULATE_BASIC_UPGRADES = 1,

    // Spells (Hero spells)
    SPELL_BOULDER                  = 21071, // Crush Flynn

    // Heroes
    FLYNN                          = 10,


    EVENT_FIRE_MAIN_WEAPON         = 100,
};

class npc_vs_central_logic : public CreatureScript
{
public:
    npc_vs_central_logic() : CreatureScript("npc_vs_central_logic") { }

    struct npc_vs_central_logicAI : public ScriptedAI
    {
        npc_vs_central_logicAI(Creature* creature) : ScriptedAI(creature)
        {
            events.ScheduleEvent(EVENT_CALCULATE_BASIC_UPGRADES, 0s);
            events.ScheduleEvent(EVENT_FIRE_MAIN_WEAPON, 2500ms);
        }

        Player* GetPlayer() {return ObjectAccessor::GetPlayer(*me, ownerGUID);}

        // New weapons
        void SetData(uint32 weapon, uint32 strength) override
        {
            /*
            if (type == SETDATA_MAGNET_ADD_RANGE)
            {
                {
                    pullrange += id;
                }
            }
            */
        }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);
            {
                {
                    switch (events.ExecuteEvent())
                    {
                        // Ran only once
                        case EVENT_CALCULATE_BASIC_UPGRADES:
                        {
                            // Hero Settings
                            CURRENT_HERO = FLYNN;
                            switch (CURRENT_HERO)
                            {
                                case FLYNN: MainWeaponTimer = 2500;
                            }

                            global_weapon_amount = 1; // Some heroes might have addtional projectile.

                            // Calculate pullrange based on magnet upgrades, done only once, on summon of the magnet.
                            if (WorldObject* owner = me->ToTempSummon()->GetSummoner())
                            {
                                if (Player* p = owner->ToPlayer())
                                {
                                    ownerGUID = p->ToPlayer()->GetGUID();
                                }
                            }
                            else
                                me->DespawnOrUnsummon();

                            QueryResult result = CharacterDatabase.Query("SELECT * FROM `vampiresurvivors` WHERE `CharacterGUID` = '{}'", ownerGUID.GetCounter());
                            if (result)
                            {
                                Field *fields = result->Fetch();
                                /*
                                //guid playerGUID = fields[0].Get<guid>();
                                //uint32 Highscore = fields[1].Get<uint32>();
                                //uint32 GoldSpent = fields[2].Get<uint32>();
                                //uint8 Maps = fields[3].Get<uint8>();
                                uint8 Might = fields[4].Get<uint8>();
                                int8 Armor = fields[5].Get<int8>(); // Negative
                                uint8 Health = fields[6].Get<uint8>();
                                uint8 Recovery = fields[7].Get<uint8>();
                                uint8 Cooldown = fields[8].Get<uint8>();
                                uint8 Area = fields[9].Get<uint8>();
                                uint8 Speed = fields[10].Get<uint8>();
                                uint8 Duration = fields[11].Get<uint8>();
                                uint8 Amount = fields[12].Get<uint8>();
                                uint8 Movespeed = fields[13].Get<uint8>();
                                uint8 Magnet = fields[14].Get<uint8>();
                                uint8 Luck = fields[15].Get<uint8>();
                                uint8 Growth = fields[16].Get<uint8>();
                                uint8 Greed = fields[17].Get<uint8>();
                                */

                                uint8 LL = 4; // fetch offset
                                uint8 offset = 0; // 1-14 spells from the array
                                for (uint32 i = 210001; i < 210015; i++)
                                {
                                    int16 pupgrade = fields[LL].Get<int16>();
                                    int32 basepoints = pupgrade * MaxRank[0][offset][2]; // Get base value per point from the array.

                                    if (basepoints) // We check only if we have the upgrade to prevent clutter.
                                    {
                                        if (i == 210005) // Cooldown, 3.3% per point
                                        {
                                            MainWeaponTimer -= ((MainWeaponTimer / 100) * (pupgrade * 3.3));
                                            global_weapon_reduction = (pupgrade * 3.3f);
                                        }

                                        if (i == 210009) // Amount
                                            global_weapon_amount += basepoints;

                                        if (i == 210011) // Magnet, has to be SetData-ed
                                            if (Creature* magnet = me->FindNearestCreature(NPC_VS_MAGNET, 10))
                                                magnet->AI()->SetData(SETDATA_MAGNET_ADD_RANGE, basepoints);

                                        if (i == 210013) // Growth, 0.03% per point, max 0.15%
                                            if (Creature* magnet = me->FindNearestCreature(NPC_VS_MAGNET, 10))
                                                magnet->AI()->SetData(SETDATA_MAGNET_GLOBAL_EXP, basepoints);

                                        if (Player* player = GetPlayer())
                                            player->CastCustomSpell(i, SPELLVALUE_BASE_POINT0, basepoints, player, true);
                                    }
                                    LL++;
                                    offset++;
                                }
                            }
                            break;
                        }
                        case EVENT_FIRE_MAIN_WEAPON:
                        {
                            switch (CURRENT_HERO)
                            {
                                case FLYNN:
                                {
                                    for (uint8 i = 0; i < global_weapon_amount ; i++)
                                    {
                                        if (Player* player = GetPlayer())
                                            player->CastSpell(player, SPELL_BOULDER, true);
                                    }
                                }
                            }
                            events.RepeatEvent(MainWeaponTimer);
                            break;
                        }
                    }
                }
            }
        }

        private:
            EventMap events;
            ObjectGuid ownerGUID;
            uint32 MainWeaponTimer;
            uint32 CURRENT_HERO;
            float global_weapon_reduction;
            uint8 global_weapon_amount;
        };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_vs_central_logicAI (creature);
    }
};

void AddVampireSurvivorsScripts()
{
    new VampireSurvivors_conf();
    new VampireSurvivors_Announce();
    new VampireSurvivors_Logic();
    new npc_vs_upgrade();
    new npc_vs_game_start();
    new npc_vs_spawner();
    new npc_vs_exp();
    new npc_vs_magnet();
    new npc_vs_central_logic();
}
