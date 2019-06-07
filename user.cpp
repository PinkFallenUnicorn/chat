#include "user.hpp"


uint32_t User::next_id = 0;


uint32_t User::user_init()
{
    std::ifstream file;
    file.open(Data::filepath);

    if (!file.is_open()) {perror("open next_id"); exit(0);}


    file >> next_id;
           
    file.close();
    return 0;
}


uint32_t User::rewrite_next_id()
{
    std::ofstream file;
    file.open(Data::filepath);

    if (!file.is_open()) {perror("open next_id"); exit(0);}

    file << next_id;

    file.close();
    return 0;
}