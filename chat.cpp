#include "chat.hpp"


uint32_t Chat::add_chat_file()
{
    const std::string filepath = "chats/" + std::to_string(chat_id);
    const std::string command = "touch " + filepath;
    const char *comm = command.c_str();

    system(comm);

    std::ofstream file;
    file.open(filepath);
    
    std::string errortext = "error open user file chat_id: " + std::to_string(chat_id);
    const char *errtext = errortext.c_str();
    if (!file.is_open()) {perror(errtext); exit(0);}

    else 
    { file  << user1_id << '\n' << user2_id << '\n';}
    file.close();
    
    return 0;
}


uint32_t Chat::add_chat()
{
    std::string filepath = "users/" + std::to_string(user1_id);

    std::ofstream file;
    file.open(filepath, std::ofstream::app);

    std::string errortext = "error open user file user_id: " + std::to_string(user1_id);
    const char *errtext = errortext.c_str();
    if (!file.is_open()) {perror(errtext); exit(0);}

    else
    {
        file << chat_id << '\n';
    }
    file.close();


    filepath = "users/" + std::to_string(user2_id);
    file.open(filepath, std::ofstream::app);

    errortext = "error open user file user_id: " + std::to_string(user2_id);
    errtext = errortext.c_str();
    if (!file.is_open()) {perror(errtext); exit(0);}

    else
    {
        file << chat_id << '\n';
    }
    file.close();
    return 0;
}


uint32_t Chat::message::add_message()
{
    const std::string filepath = "chats/" + std::to_string(chat_id);

    std::ofstream file;
    file.open(filepath, std::ofstream::app);
    
    std::string errortext = "error open user file chat_id: " + std::to_string(chat_id);
    const char *errtext = errortext.c_str();
    if (!file.is_open()) {perror(errtext); exit(0);}

    else 
    { file  << sender_id << " " << receiver_id << " " << msg << '\n';}
    file.close();
}

Chat::Chat(const uint32_t user1_id, const uint32_t user2_id) : 
user1_id(user1_id), user2_id(user2_id), chat_id(Data::next_chat_id)
{
    add_chat_file();
    Data::next_chat_id += 1;
    Data::rewrite_next_id();
    add_chat();
}