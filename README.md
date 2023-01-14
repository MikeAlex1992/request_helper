## request_helper
#Simple program for handle requests for server from Yandex Practicum Backend C++ courses

## Available commands:

1) **MapList** [no arguments] --- /api/v1/maps

2) **MapConfig** [mapId] --- /api/v1/maps/mapId

3) **AddPlayer** [name mapId] --- /api/v1/game/join

4) **Tick** [time_delta] --- /api/v1/game/tick

5) **ShowState** [no arguments] --- /api/v1/game/state

    *{choose player from given list (PROGRAM CAN SHOW ONLY ADDED IN THAT SESSION PLAYERS)}*
    
6) **ShowPlayerList** [no arguments] --- /api/v1/game/players

    *{choose player from given list (PROGRAM CAN SHOW ONLY ADDED IN THAT SESSION PLAYERS)}*
    
7) **SendPlayerMovement** [no arguments] --- /api/v1/game/player/action

    *{type movement}*
    
8) **ShowRecords** [no arguments] ---/api/v1/game/records
