SET @ID := 210000;
SET @GUID := 3100000;
SET @Quests := 91000;

-- Upgrades
DELETE FROM `creature_template` WHERE (`entry` = @ID);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@ID, 0, 0, 0, 0, 0, 'Upgrades', 'Permanent Upgrades', '', 0, 80, 80, 0, 35, 3, 1, 1, 1, 1, 1, 2, 3, 0, 1, 0, 0, 0, 0, 1, 0, 32768, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 400, 1, 1, 1, 0, 0, 1, 0, 0, 2, 'npc_vs_upgrade', 0);

DELETE FROM `creature_template_model` WHERE `CreatureID` = @ID;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`) VALUES
(@ID, 0, 28738, 1, 1, 0);

DELETE FROM `creature` WHERE (`id1` = @ID);
INSERT INTO `creature` (`guid`, `id1`, `id2`, `id3`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `wander_distance`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `ScriptName`, `VerifiedBuild`, `CreateObject`, `Comment`) VALUES
(@GUID, @ID, 0, 0, 1, 0, 0, 1, 1, 0, 16235, 16262, 16, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0, '', 0, 0, NULL);

-- Kullervo - Game Start NPC
DELETE FROM `creature_template` WHERE (`entry` = @ID+1);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@ID+1, 0, 0, 0, 0, 0, 'Kullervo', '', '', 0, 80, 80, 0, 35, 3, 1, 1, 1, 1, 1, 2, 1.25, 0, 1, 0, 0, 0, 0, 1, 0, 32768, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 400, 1, 1, 1, 0, 0, 1, 0, 0, 2, 'npc_vs_game_start', 0);

DELETE FROM `creature_template_model` WHERE `CreatureID` = @ID+1;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`) VALUES
(@ID+1, 0, 31028, 1, 1, 0);

DELETE FROM `creature` WHERE (`id1` = @ID+1);
INSERT INTO `creature` (`guid`, `id1`, `id2`, `id3`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `wander_distance`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `ScriptName`, `VerifiedBuild`, `CreateObject`, `Comment`) VALUES
(@GUID+1, @ID+1, 0, 0, 1, 0, 0, 1, 1, 0, 16235, 16259, 16, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0, '', 0, 0, NULL);

-- Spawner NPC
DELETE FROM `creature_template` WHERE (`entry` = @ID+2);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@ID+2, 0, 0, 0, 0, 0, 'Spawner NPC', '', '', 0, 1, 1, 0, 35, 0, 5, 5, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 130, 'npc_vs_spawner', 0);

DELETE FROM `creature_template_model` WHERE `CreatureID` = @ID+2;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`) VALUES
(@ID+2, 0, 169, 1, 1, 0);

-- Magnet
DELETE FROM `creature_template` WHERE (`entry` = @ID+3);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@ID+3, 0, 0, 0, 0, 0, 'Magnet', '', '', 0, 1, 1, 0, 35, 0, 5, 5, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 130, 'npc_vs_magnet', 0);

DELETE FROM `creature_template_model` WHERE `CreatureID` = @ID+3;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`) VALUES
(@ID+3, 0, 29071, 1, 1, 0);

-- Central Logic
DELETE FROM `creature_template` WHERE (`entry` = @ID+4);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@ID+4, 0, 0, 0, 0, 0, 'Central Logic', '', '', 0, 1, 1, 0, 35, 0, 5, 5, 1, 1, 1, 0.5, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 130, 'npc_vs_central_logic', 0);

DELETE FROM `creature_template_model` WHERE `CreatureID` = @ID+4;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`) VALUES
(@ID+4, 0, 169, 1, 1, 0);

-- Levelup Upgrades
-- Common
DELETE FROM `creature_template_model` WHERE `CreatureID` BETWEEN @ID+5 AND @ID+9;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`) VALUES
(@ID+5, 0, 28738, 1, 1, 0),
(@ID+6, 0, 28738, 1, 1, 0),
(@ID+7, 0, 28738, 1, 1, 0),
(@ID+8, 0, 28738, 1, 1, 0),
(@ID+9, 0, 28738, 1, 1, 0);

DELETE FROM `creature_template` WHERE `entry` BETWEEN @ID+5 AND @ID+9;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@ID+5, 0, 0, 0, 0, 0, 'Upgrade', 'Common', '',    0, 80, 80, 0, 35, 3, 1, 1, 1, 1, 1, 1.5, 3, 0, 1, 0, 0, 0, 0, 1, 768, 32768, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 400, 1, 1, 1, 0, 0, 1, 0, 0, 2, 'npc_vs_levelup_upgrade', 0),
(@ID+6, 0, 0, 0, 0, 0, 'Upgrade', 'Uncommon', '',  0, 80, 80, 0, 35, 3, 1, 1, 1, 1, 1, 1.5, 3, 0, 1, 0, 0, 0, 0, 1, 768, 32768, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 400, 1, 1, 1, 0, 0, 1, 0, 0, 2, 'npc_vs_levelup_upgrade', 0),
(@ID+7, 0, 0, 0, 0, 0, 'Upgrade', 'Rare', '',      0, 80, 80, 0, 35, 3, 1, 1, 1, 1, 1, 1.5, 3, 0, 1, 0, 0, 0, 0, 1, 768, 32768, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 400, 1, 1, 1, 0, 0, 1, 0, 0, 2, 'npc_vs_levelup_upgrade', 0),
(@ID+8, 0, 0, 0, 0, 0, 'Upgrade', 'Epic', '',      0, 80, 80, 0, 35, 3, 1, 1, 1, 1, 1, 1.5, 3, 0, 1, 0, 0, 0, 0, 1, 768, 32768, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 400, 1, 1, 1, 0, 0, 1, 0, 0, 2, 'npc_vs_levelup_upgrade', 0),
(@ID+9, 0, 0, 0, 0, 0, 'Upgrade', 'Legendary', '', 0, 80, 80, 0, 35, 3, 1, 1, 1, 1, 1, 1.5, 3, 0, 1, 0, 0, 0, 0, 1, 768, 32768, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 400, 1, 1, 1, 0, 0, 1, 0, 0, 2, 'npc_vs_levelup_upgrade', 0);
                                                                                    -- sclae

-- Quest: The Vampire Survivors
DELETE FROM `quest_template` WHERE (`ID` = @Quests);
INSERT INTO `quest_template` (`ID`, `QuestType`, `QuestLevel`, `MinLevel`, `QuestSortID`, `QuestInfoID`, `SuggestedGroupNum`, `RequiredFactionId1`, `RequiredFactionId2`, `RequiredFactionValue1`, `RequiredFactionValue2`, `RewardNextQuest`, `RewardXPDifficulty`, `RewardMoney`, `RewardMoneyDifficulty`, `RewardDisplaySpell`, `RewardSpell`, `RewardHonor`, `RewardKillHonor`, `StartItem`, `Flags`, `RequiredPlayerKills`, `RewardItem1`, `RewardAmount1`, `RewardItem2`, `RewardAmount2`, `RewardItem3`, `RewardAmount3`, `RewardItem4`, `RewardAmount4`, `ItemDrop1`, `ItemDropQuantity1`, `ItemDrop2`, `ItemDropQuantity2`, `ItemDrop3`, `ItemDropQuantity3`, `ItemDrop4`, `ItemDropQuantity4`, `RewardChoiceItemID1`, `RewardChoiceItemQuantity1`, `RewardChoiceItemID2`, `RewardChoiceItemQuantity2`, `RewardChoiceItemID3`, `RewardChoiceItemQuantity3`, `RewardChoiceItemID4`, `RewardChoiceItemQuantity4`, `RewardChoiceItemID5`, `RewardChoiceItemQuantity5`, `RewardChoiceItemID6`, `RewardChoiceItemQuantity6`, `POIContinent`, `POIx`, `POIy`, `POIPriority`, `RewardTitle`, `RewardTalents`, `RewardArenaPoints`, `RewardFactionID1`, `RewardFactionValue1`, `RewardFactionOverride1`, `RewardFactionID2`, `RewardFactionValue2`, `RewardFactionOverride2`, `RewardFactionID3`, `RewardFactionValue3`, `RewardFactionOverride3`, `RewardFactionID4`, `RewardFactionValue4`, `RewardFactionOverride4`, `RewardFactionID5`, `RewardFactionValue5`, `RewardFactionOverride5`, `TimeAllowed`, `AllowableRaces`, `LogTitle`, `LogDescription`, `QuestDescription`, `AreaDescription`, `QuestCompletionLog`, `RequiredNpcOrGo1`, `RequiredNpcOrGo2`, `RequiredNpcOrGo3`, `RequiredNpcOrGo4`, `RequiredNpcOrGoCount1`, `RequiredNpcOrGoCount2`, `RequiredNpcOrGoCount3`, `RequiredNpcOrGoCount4`, `RequiredItemId1`, `RequiredItemId2`, `RequiredItemId3`, `RequiredItemId4`, `RequiredItemId5`, `RequiredItemId6`, `RequiredItemCount1`, `RequiredItemCount2`, `RequiredItemCount3`, `RequiredItemCount4`, `RequiredItemCount5`, `RequiredItemCount6`, `Unknown0`, `ObjectiveText1`, `ObjectiveText2`, `ObjectiveText3`, `ObjectiveText4`, `VerifiedBuild`) VALUES
(@Quests, 0, 80, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'The Vampire Survivors', 'Humanity\'s last hope lies in the hands of a few scattered survivors of a devastating vampire attack that wiped out most of the world\'s population. With the vampires\' twisted powers and regenerative abilities, the survivors must band together to scavenge for supplies, upgrade their skills, and fight against the undead hordes to re-establish their operations and reclaim their world. As they navigate treacherous ruins and abandoned cities, they\'ll uncover dark secrets about the vampires\' origins and the true nature of their curse, and must make difficult choices to ensure their survival in a world gone mad.', 'Humanity\'s last hope lies in the hands of a few scattered survivors of a devastating vampire attack that wiped out most of the world\'s population. With the vampires\' twisted powers and regenerative abilities, the survivors must band together to scavenge for supplies, upgrade their skills, and fight against the undead hordes to re-establish their operations and reclaim their world. As they navigate treacherous ruins and abandoned cities, they\'ll uncover dark secrets about the vampires\' origins and the true nature of their curse, and must make difficult choices to ensure their survival in a world gone mad.', '', 'Humanity\'s last hope lies in the hands of a few scattered survivors of a devastating vampire attack that wiped out most of the world\'s population. With the vampires\' twisted powers and regenerative abilities, the survivors must band together to scavenge for supplies, upgrade their skills, and fight against the undead hordes to re-establish their operations and reclaim their world. As they navigate treacherous ruins and abandoned cities, they\'ll uncover dark secrets about the vampires\' origins and the true nature of their curse, and must make difficult choices to ensure their survival in a world gone mad.', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', '', '', 0);

DELETE FROM `quest_offer_reward` WHERE (`ID` = @Quests);
INSERT INTO `quest_offer_reward` (`ID`, `Emote1`, `Emote2`, `Emote3`, `Emote4`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `EmoteDelay4`, `RewardText`, `VerifiedBuild`) VALUES
(@Quests, 1, 0, 0, 0, 0, 0, 0, 0, 'We\'ve cleared out the last of the vampires, but what about rebuilding and securing our new territory.\nWe\'ve lost so much, but we can\'t give up. We need to regroup, gather our remaining forces, and start anew.\nI\'ve prepared a new base of operations for us to call home. It\'s not safe yet, but it\'s a start.\nWe\'ll work together to rebuild our society and ensure our survival.', 0);

DELETE FROM `creature_queststarter` WHERE (`quest` = @Quests);
INSERT INTO `creature_queststarter` (`id`, `quest`) VALUES
(@ID, @Quests);

DELETE FROM `creature_questender` WHERE (`quest` = @Quests);
INSERT INTO `creature_questender` (`id`, `quest`) VALUES
(@ID, @Quests);

-- Item (PH item)
DELETE FROM `item_template` WHERE (`entry` = 45229);
INSERT INTO `item_template` (`entry`, `class`, `subclass`, `SoundOverrideSubclass`, `name`, `displayid`, `Quality`, `Flags`, `FlagsExtra`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `StatsCount`, `stat_type1`, `stat_value1`, `stat_type2`, `stat_value2`, `stat_type3`, `stat_value3`, `stat_type4`, `stat_value4`, `stat_type5`, `stat_value5`, `stat_type6`, `stat_value6`, `stat_type7`, `stat_value7`, `stat_type8`, `stat_value8`, `stat_type9`, `stat_value9`, `stat_type10`, `stat_value10`, `ScalingStatDistribution`, `ScalingStatValue`, `dmg_min1`, `dmg_max1`, `dmg_type1`, `dmg_min2`, `dmg_max2`, `dmg_type2`, `armor`, `holy_res`, `fire_res`, `nature_res`, `frost_res`, `shadow_res`, `arcane_res`, `delay`, `ammo_type`, `RangedModRange`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellppmRate_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellppmRate_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellppmRate_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellppmRate_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellppmRate_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `description`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `RandomSuffix`, `block`, `itemset`, `MaxDurability`, `area`, `Map`, `BagFamily`, `TotemCategory`, `socketColor_1`, `socketContent_1`, `socketColor_2`, `socketContent_2`, `socketColor_3`, `socketContent_3`, `socketBonus`, `GemProperties`, `RequiredDisenchantSkill`, `ArmorDamageModifier`, `duration`, `ItemLimitCategory`, `HolidayId`, `ScriptName`, `DisenchantID`, `FoodType`, `minMoneyLoot`, `maxMoneyLoot`, `flagsCustom`, `VerifiedBuild`) VALUES
(45229, 12, 0, -1, 'Survivor\'s Gold', 50216, 4, 134217760, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9999, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1000, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 'Obtained by playing the Vampire Survivors module.\nUsed to purchase upgrades.', 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0);

