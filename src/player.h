#pragma once

#include <stdint.h>
#include <string>
#include <cstring>
#include <vector>
#include <mutex>
#include "arcdps_datastructures.h"

struct Player
{
    std::string name;
    std::string account;
    uintptr_t id;            //instance id
    uint16_t downs;              //number of times the player has downed
    uint16_t deaths;              //number of times the player has completely died
    uint16_t pulls;         //number of boss pulls
    bool is_downed;     //is currently is down state
    uint16_t mechanics_failed;   //number of mechanics failed
    uint16_t mechanics_received;//number of boss mechanics received
    uint64_t last_stab_time;  //time stability is going to expire
    uint64_t last_hit_time;       //time player was last hit with a mechanic
    uint16_t last_mechanic;       //skill id of last failed mechanic
    bool in_squad;          //currently in squad

    struct mechanic_tracker
    {
        std::string name; //name of mechanic
        uint16_t id; //skill id;
        bool fail;
        uint16_t hits;
        uint32_t boss; //boss id
        uint16_t pulls;

        mechanic_tracker(std::string &new_name,uint16_t &new_id,bool &new_fail, uint32_t &new_boss);

        std::string to_string();
        void add_pull(uint32_t new_boss);
    };

    std::vector<mechanic_tracker> tracker;

    Player();
    Player(ag* &new_player);
    Player(char* new_name, char* new_account, uintptr_t new_id);

    void down();
    void dead();
    void rally();
    void fix_double_down(); //manual case to fix vapor form counting as 2 downs

    void mechanic_receive(std::string &name,uint16_t &id,bool &is_fail, uint32_t &boss);
    bool is_relevant();     //if player is relevant for displaying

    uint64_t get_last_stab_time();
    void set_stab_time(uint64_t new_stab_time);

    uint64_t get_last_hit_time();
    void set_last_hit_time(uint64_t new_hit_time);

    uint16_t get_last_mechanic();
    void set_last_mechanic(uint16_t new_mechanic);

    std::string to_string();
    uint16_t get_mechanics_total();//returns the number of total mechanics the player had
    void reset_stats();
    void add_pull(uint32_t new_boss);
};

extern std::mutex players_mtx;
extern std::mutex tracker_mtx;

extern std::vector<Player> players;

Player* get_player(ag* &new_player);
void add_player(char* name, char* account, uintptr_t id);
void remove_player(char* name, char* account, uintptr_t id);
void add_pull(uint32_t boss);
bool is_player(ag* &new_player);
void reset_all_player_stats();
uint16_t get_mechanics_total(std::vector<Player> &players);
