#ifndef POKEHEARTGOLD_CONSTANTS_WIFI_PLAZA_H
#define POKEHEARTGOLD_CONSTANTS_WIFI_PLAZA_H

// Players in one lobby (the lobby slots)
#define WIFI_PLAZA_MAX_PLAYERS 20

// WiFiPlazaGroups: nine groups of three places (place = group * WIFI_PLAZA_GROUP_SEATS + seat)
#define WIFI_PLAZA_GROUP_COUNT 9
#define WIFI_PLAZA_GROUP_SEATS 3
#define WIFI_PLAZA_PLACE_COUNT (WIFI_PLAZA_GROUP_COUNT * WIFI_PLAZA_GROUP_SEATS)

// WiFiPlazaTalkSession.state: how far a talk between two players has got, and whose turn it is
enum WiFiPlazaTalkState {
    WIFI_PLAZA_TALK_STATE_NONE,
    WIFI_PLAZA_TALK_STATE_REQUESTED,
    WIFI_PLAZA_TALK_STATE_ASKER_TURN,
    WIFI_PLAZA_TALK_STATE_ANSWERER_TURN,
    WIFI_PLAZA_TALK_STATE_ENDED,
};

// WiFiPlazaTalkSession.role
enum WiFiPlazaTalkRole {
    WIFI_PLAZA_TALK_ROLE_NONE,
    WIFI_PLAZA_TALK_ROLE_ASKER,
    WIFI_PLAZA_TALK_ROLE_ANSWERER,
};

#endif // POKEHEARTGOLD_CONSTANTS_WIFI_PLAZA_H
