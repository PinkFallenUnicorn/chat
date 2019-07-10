#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "user.hpp"
#include "net.hpp"

class Client
{
    public:
        uint16_t login(int32_t sock, std::string login, std::string password);
        uint16_t message(int32_t sock, uint64_t chat_id, uint32_t sender_id, uint32_t receiver_id, std::string msg);
        uint16_t find(int32_t sock);
        uint16_t run();
    private:
        bool is_running = false;
        int32_t sock;
        sockaddr_in addr;
        bool login_status = false;
        std::string current_login;
        std::string current_user_id;
};

#endif