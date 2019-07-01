#include "user.hpp"
#include "net.hpp"

class Client
{
    public:
        static uint32_t login_request(int32_t sock)
        {
            char message[] = "login";
            int32_t buf_size = sizeof(message);
            char* tosend = (char*)&buf_size;
            int32_t remaining = sizeof(buf_size);
            int32_t result = 0;
            int32_t sent = 0;
            while (remaining > 0) 
            {
                result = send(sock, tosend+sent, remaining, 0);
                if (result > 0) 
                {
                    remaining -= result;
                    sent += result;
                }
                else if (result < 0) 
                {
                    std::cout << "ERROR!" << '\n';
                    return -1;
                }
            }
        }
    private:
    
};