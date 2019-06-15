#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "user.hpp"
#include "chat.hpp"

class Server_data
{
    private:
        static uint32_t server_data_users_init();
        static uint32_t server_data_chats_init();

    public:
        static uint32_t server_data_init();
        static std::vector<User> users;
        static std::vector<Chat> chats;
};

#endif