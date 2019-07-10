#include "client.hpp"

uint16_t Client::login(int32_t sock, std::string login, std::string password)
{
    std::string request = "/log/" + login + password;
    
    Net::send_char(&request, sock);

    std::string success_flag;
    Net::receive(&success_flag, sock);

    if (success_flag == "success")
        return 0;

    else
    {
        std::cout << success_flag << '\n';
        return 1;
    }
}


uint16_t Client::message(int32_t sock, uint64_t chat_id, uint32_t sender_id, uint32_t receiver_id, std::string msg)
{
    std::string request = "/msg/" + std::to_string(chat_id) + '\n' + std::to_string(sender_id) + '\n' + std::to_string(receiver_id) + '\n' + msg;
    
    std::cout << request << '\n';

    Net::send_char(&request, sock);

    std::string success_flag;
    Net::receive(&success_flag, sock);

    if (success_flag == "success")
        return 0;

    else
    {
        std::cout << "Client::message: non success answer received" << '\n';
        exit(0);
    }

   return 0;
}

uint16_t Client::run()
{
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        { perror("socket"); exit(1); }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3328);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (connect(sock, (sockaddr *)&addr, sizeof(addr)) < 0)
        { perror("connect"); exit(2); }


    while (1)
    {
        int32_t i;
        std::cout << "Выберите действие:\n1. Авторизация\n2. Регистрация в системе" << '\n';
        std::cin >> i;
        if (i == 1)
        {
            system("clear");
            std::string login;
            std::string password;

            std::cout << "Авторизация.\n\nlogin: ";
            std::cin >> login;

            std::cout << "\npassword: ";
            std::cin >> password;

            int16_t log_status = Client::login(sock, login, password);
            if (log_status == 0)
            {
                //добавить сюда задание current_user_id
                login_status = true;
            }

            else
                continue;
            
            

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