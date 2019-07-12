#include "server.hpp"

struct message {};

int error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main()
{
    Server srv;
    srv.run();
}
