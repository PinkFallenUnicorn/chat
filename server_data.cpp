#include "server_data.hpp"

User alfa_user{0 ,"nnnnnnnnnnnnnnnn", "nnnnnnnnnnnnnnn"};
Tree <User> Server_data::users {alfa_user};
User *pointeer = &alfa_user;
std::vector <User *> Server_data::users_by_id = {pointeer};
std::vector <Chat> Server_data::chats = {};


uint32_t Server_data::server_data_users_init()
{
    if(Data::next_user_id == 0)
    {perror("server_data_init: class Data not initialized"); exit(0);}
    for (uint32_t i = 1; i < Data::next_user_id; i++)
    {
        std::string filepath = "users/" + std::to_string(i);
        std::ifstream file;
        file.open(filepath);
        if(!file.is_open())
        {
            std::string errortext = "error open user file user_id: " + std::to_string(i);
            const char *errtext = errortext.c_str();
            perror(errtext); 
            exit(0);
        }
        std::string nickname;
        file >> nickname;
        std::string password;
        file >> password;
        User user{i, nickname, password};
        users.add(user);
        User *pointeer = &user;
        users_by_id.push_back(pointeer);
        file.close();
    }
    return 0;
}


uint32_t Server_data::server_data_chats_init()
{
    if(Data::next_chat_id == 0)
    {perror("server_data_init: class Data not initialized"); exit(0);}
    for (uint32_t i = 1; i < Data::next_chat_id; i++)
    {
        std::string filepath = "chats/" + std::to_string(i);
        std::ifstream file;
        file.open(filepath);
        if(!file.is_open())
        {
            std::string errortext = "error open user file chat_id: " + std::to_string(i);
            const char *errtext = errortext.c_str();
            perror(errtext); 
            exit(0);
        }
        std::string user1_id;
        file >> user1_id;
        std::string user2_id;
        file >> user2_id;
        chats.push_back(Chat(i, std::stoi(user1_id), std::stoi(user2_id)));
        file.close();
    }
    return 0;
}



/*Function which read from datafiles all data and initialize it 
as next_id variables/vector<User> users/vector<Chat> chats*/
uint32_t Server_data::server_data_init()
{
    Data::data_init();
    server_data_users_init();
    server_data_chats_init();
    return 0;
}


uint32_t Server_data::add_user(std::string nickname, std::string password)
{
    User user{nickname, password};
    Server_data::users.add(user);
    User *pointeer = &user;
    if (users_by_id.size() == users_by_id.capacity())
        users_by_id.reserve(1000);
    users_by_id.push_back(pointeer);
    return 0;
}



uint32_t Server_data::add_chat(const uint32_t user1_id, const uint32_t user2_id)
{
    if (chats.size() == chats.capacity())
        chats.reserve(1000);
    Chat chat{user1_id, user2_id};
    chats.push_back(chat);
    return 0;
}

/*return 0 == success, return 1 == wrong login, return 2 == wrong pass */
const int16_t Server_data::find(std::string login, std::string password)
{
    User tmpuser(0, login, password);
    if (Server_data::users.search(tmpuser))
    {
        User *secondtmpuser;
        users.get(tmpuser, secondtmpuser);
        if (secondtmpuser->password == password)
            return 0;
        else
            return 2;
    }
    else
        return 1;
}
