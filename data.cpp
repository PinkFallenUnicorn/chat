#include "data.hpp"


std::string Data::filepath = "";
uint64_t Data::next_chat_id = 0;
uint32_t Data::next_user_id = 0;



uint32_t Data::first_data_init()
{
    system("rm -rf data");
    system("mkdir data");
    system("rm -rf users");
    system("mkdir users");
    system("rm -rf chats");
    system("mkdir chats");
    system("touch data/next_id");

    std::ofstream file;
    file.open("data/next_id");

    if (!file.is_open()) {perror("open data/next_id"); exit(0); }
    
    else 
    { file << "1\n1\n";}
    file.close();

    return 0;
}


uint32_t Data::data_init()
{
    filepath = "data/next_id";

    std::ifstream file;
    file.open(filepath);

    if (!file.is_open()) {perror("open data/next_id"); exit(0);}
    else 
    { 
        file >> next_user_id;
        file >> next_chat_id;
    }
    file.close();

    return 0;
}



uint32_t Data::rewrite_next_id()
{
    std::ofstream file;
    file.open(Data::filepath);

    if (!file.is_open()) {perror("open next_id"); exit(0);}

    file << next_user_id << '\n' << next_chat_id << '\n';


    file.close();
    return 0;
}