#ifndef INCLUDE_SCORE_DATA_H
#define INCLUDE_SCORE_DATA_H

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>


#define DATA_PATH "data/player.bin"


typedef struct save_ScoreData_S {
    uint32_t score;
    uint32_t sessions;
    uint32_t record;
} save_ScoreData;


bool load_score_data(save_ScoreData* out_score_data, const char* path);
bool save_score_data(const save_ScoreData * score_data, const char* path);
void save_create_data_file(const char* path);

void save_ScoreData_CheckRecord(save_ScoreData * data);

void save_ScoreData_IncreaseScore(save_ScoreData * data , const uint32_t amount);


#endif