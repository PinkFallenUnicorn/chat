#ifndef NET_HPP
#define NET_HPP

#include "data.hpp"

class Net
{
    public:
        static int32_t recv_int32(int32_t *value, int32_t sock);
        static int32_t receive(char *buf, int32_t sock);
        static int32_t send_int32(int32_t *value, int32_t sock);
        static int32_t send_char(std::string *buf, int32_t);
    private:
};

#endif //NET_HPP
