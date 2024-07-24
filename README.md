﻿# ![logo](https://raw.githubusercontent.com/azerothcore/azerothcore.github.io/master/images/logo-github.png) AzerothCore

## Description

Adds [Vampire Survivors](https://store.steampowered.com/app/1794680/Vampire_Survivors/) to [AzerothCore](http://azerothcore.org/).

<p>
<img src="https://i.imgur.com/gick7EA.jpeg" alt="The Brawler's Guild" width=50%/>
</p>

<p float="left">
<img src="https://i.imgur.com/sBQhIcl.jpeg" alt="The Brawler's Guild" width=25%/>
<img src="https://i.imgur.com/FDR5Mnl.jpeg" alt="The Brawler's Guild" width=25%/>
</p>


> [!IMPORTANT]
> Requires at least AzerothCore commit [618f97b](https://github.com/azerothcore/azerothcore-wotlk/commit/618f97bee6aa74e6cf9ba7a82f4c91a25861e56e).
> This is meant to be played only as SINGLEPLAYER, do not run on production servers.

> [!IMPORTANT]
> How to uninstall:
> Drop acore_world & vampiresurvivors table (acore_characters)
> Remove the module folder and rebuild master
## How to use ingame

- .tele ringofvalor

## Description

The Brawler's Guild is an organization that arranges one on one battles between willing combatants, captured monsters, and other participants in gladiatorial combat. Being a neutral organization, only members of the Horde are allowed to enter, rising through the Brawler's Guild ranks with more wins. Prizes are awarded at higher ranks. The fights are all solo PvE matches in which the players must adapt and use different strategies depending on which opponent they are currently facing, making the Brawler's Guild one of the most challenging PvE activities a player can attempt on their own.

> [!NOTE]  
> Features:\
> Betting on win/lose for current fight\
> Multiple ranks to progress through.\
> VIP Area (South Seas) (Teleporter unlockable after reaching the highest rank (8))\
> Multiple Seasons (4 in total, 1 for each raid tier) *NYI*
### Season tuning information

- Season 1 - Tier 7 &nbsp; (213~)
- Season 2 - Tier 8 &nbsp; (232~)
- Season 3 - Tier 9 &nbsp; (245~)
- Season 4 - Tier 10 (264~)

(Item level is based on the highest obtainable gear from 10m)

## Installation

```
1) Simply place the module under the `modules` directory of your AzerothCore source. 
2) Import the SQL(s) manually to the right Database (auth, world or characters) or with the `db_assembler.sh`.
3) Re-run cmake and launch a clean build of AzerothCore.
```

## Edit module configuration (optional)

If you need to change the module configuration, go to your server configuration folder (where your `worldserver` or `worldserver.exe` is), copy `modarenatop.conf.dist` to `modarenatop.conf` and edit that new file.

## Edit shop configuration

In `npc_brawlers_guild.cpp` look for "Shop", there you can edit prices, items and required rank for every item.

## Credits
Avarishd: [GitHub](https://github.com/avarishd) [Discord](https://discordapp.com/users/125563894310633472)

AzerothCore: [GitHub Repository](https://github.com/azerothcore) [Website](http://azerothcore.org/) [Discord](https://discord.gg/PaqQRkd)
