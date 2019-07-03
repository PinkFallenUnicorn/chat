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


uint32_t Chat::add_chat_to_userfile()
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


uint32_t Chat::add_message_file()
{
    const std::string filepath = "chats/" + std::to_string(chat_id);
    std::cout << filepath << '\n';
    std::ofstream file;
    file.open(filepath, std::ofstream::app);
    
    std::string errortext = "error open user file chat_id: " + std::to_string(chat_id);
    const char *errtext = errortext.c_str();
    if (!file.is_open()) {perror(errtext); exit(0);}

    else 
    { file  << messages[messages.size() - 1].sender_id << " " << messages[messages.size() - 1].receiver_id << " " << messages[messages.size() - 1].msg << '\n';}
    file.close();

    return 0;
}


uint32_t Chat::new_message(const uint32_t sender_id, const uint32_t receiver_id, const std::string msg)
{
    messages.push_back(message(sender_id, receiver_id, msg));
    add_message_file();

    return 0;
}


Chat::Chat(const uint32_t user1_id, const uint32_t user2_id) : 
chat_id(Data::next_chat_id), user1_id(user1_id), user2_id(user2_id)
{
    add_chat_file();
    Data::next_chat_id += 1;
    Data::rewrite_next_id();
    add_chat_to_userfile();
}


Chat::Chat(const uint32_t chat_id,const uint32_t user1_id, const uint32_t user2_id) : 
chat_id(chat_id), user1_id(user1_id), user2_id(user2_id)
{}

