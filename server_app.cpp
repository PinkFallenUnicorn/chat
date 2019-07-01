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
    const unsigned int MAX_BUF_LENGTH = 4096;
    std::vector<char> buffer(MAX_BUF_LENGTH); ;
    int bytes_read;

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
                char buf[5048];
                int32_t i = Net::receive(buf, sock);
                std::cout << "buf: " << buf  << '\n' << "bufsize: " << buf.size() <<;
                std::cout << "we are good" << '\n';

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