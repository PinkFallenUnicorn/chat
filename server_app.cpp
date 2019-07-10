#include "server.hpp"

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

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener < 0)
        error("listener");
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3328);
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
                std::string buf;
                int32_t i = Net::receive(&buf, sock);
                std::cout << "server_app.cpp: buf: " << buf  << '\n' << "server_app.cpp: bufsize: " << buf.size() << '\n';
                std::cout << "server_app.cpp: we are good" << '\n';
                if (i >= 0)               
                    break;
                

            }
            close(sock);
            _exit(0);
        }
        else close(sock);
    }

    close(listener);
    
    return 0;
}
