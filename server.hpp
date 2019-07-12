#ifndef SERVER_HPP
#define SERVER_HPP

#include "server_data.hpp"

class Server
{
    public:
        uint16_t detect(std::string *str);
        uint16_t login(std::string *str, int32_t sock);
        uint16_t dirrect(std::string *str, int32_t sock);
        uint16_t message(std::string *str, int32_t sock);
        uint16_t send_user_data(std::string login, int32_t sock);
        uint16_t send_user_chats(std::string login, int32_t sock);
        uint16_t sign_up(std::string *str, int32_t sock);
        uint16_t run();
    private:
        int32_t sock;
        int32_t listener;
        sockaddr_in addr;
};

#endif //SERVER_HPP