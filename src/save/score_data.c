#include <score_data.h>


bool load_score_data(save_ScoreData* out_score_data, const char* path) {
    
    FILE * in_file = fopen(path , "rb");
    
    assert(in_file);

    fread(out_score_data , sizeof(save_ScoreData) , 1 , in_file);

    return true;
}

bool save_score_data(const save_ScoreData * score_data, const char* path) {
    FILE * out_file = fopen(path , "wb");
    assert(out_file);

    fwrite(score_data , sizeof(save_ScoreData) , 1 , out_file);

    return true;
}

void save_create_data_file(const char* path){
    
    FILE* file = fopen(path , "wb");
    assert(file);

}

void save_ScoreData_CheckRecord(save_ScoreData * data) {

    if(data->score > data->record) {
        data->record = data->score;
    }

}

void save_ScoreData_IncreaseScore(save_ScoreData * data , const uint32_t amount) {
    data->score += amount;
}


