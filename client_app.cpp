#include "client.hpp"


int main()
{
    system("clear");
    int32_t sock;
    sockaddr_in addr;
    bool login_status = false;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    { perror("socket"); exit(1); }
       
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3328);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if (connect(sock, (sockaddr *)&addr, sizeof(addr)) < 0)
    { perror("connect"); exit(2); }

    int32_t i;
    while (1)
    {
        std::cout << "Выберите действие:\n1. Авторизация\n2. Регистрация в системе" << '\n';
        std::cin >> i;
        if (i == 1)
        {
            while (1)
            {
                std::string message;
                std::cin >> message;
                std::cout << "client_app: message: " << message << "\nclientapp: message: size: " << message.size() << '\n';
                Net::send_char(&message, sock);
                break;
            }
            break;
        }
        else if (i == 2)
        {
            /*Регистрация*/
            continue;
        }
        else
        {
            system("clear");
            std::cout << "Проверьте введенные данные!" << '\n';
            continue;
        }
    }
    close(sock);
    if (login_status)
    {
        /* app starts */
    }
    else return 0;
    
    


    return 0;
}