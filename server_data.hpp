#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "user.hpp"
#include "chat.hpp"
#include "net.hpp"

class Server_data
{
    private:
        static uint32_t server_data_users_init();
        static uint32_t server_data_chats_init();

    public:
        static const bool find(std::string login, std::string password);

        static uint32_t server_data_init();
        static Tree <User> users;
        static std::vector <Chat> chats;
        static uint32_t add_user(std::string nickname, std::string password);
        static uint32_t add_chat(const uint32_t user1_id, const uint32_t user2_id);
};

#endif