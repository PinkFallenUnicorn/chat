#ifndef SERVER_HPP
#define SERVER_HPP

#include "server_data.hpp"

class Server
{
    public:
        uint16_t detect(std::string *str);
        uint16_t login(std::string *str, int32_t sock);
        uint16_t listen(std::string *str, int32_t sock);
        uint16_t message(std::string *str, int32_t sock);
        uint16_t sign_up(std::string *str, int32_t sock);
    private:
};

#endif //SERVER_HPP