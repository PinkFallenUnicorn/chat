#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "chat.hpp"

struct message {};

int error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main()
{
    int32_t sock, listener;
    sockaddr_in addr;
    message msgbuf;
    void *buf = &msgbuf;
    int bytes_read;

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener < 0)
        error("listener");
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1488);
    addr.sin_addr.s_addr = (INADDR_ANY);

    if (bind(listener,(sockaddr *)&addr, sizeof(addr)) < 0)
        error("bind");
    
    listen(listener, 1);

    while (1)
    {
        sock = accept(listener, nullptr, nullptr);
        if (sock < 0)
            error("accept");
        
        uint32_t forkstatus = fork();
        if (forkstatus == -1)
            error("fork");
        else if (forkstatus == 0)
        {
            close(listener);
            while (1)
            {
                bytes_read = recv(sock, buf, 1024, 0);
                if (bytes_read <= 0 ) break;
            }
        }
    }



    return 0;
}