#include "client.hpp"

uint16_t Client::recv_user_data(int32_t sock)
{
    std::string buf;
    Net::receive(&buf, sock);

    std::string tmp;

    Data::split(&buf, &tmp, &buf);
    current_user_id = stoi(tmp);

    Data::split(&buf, &tmp, &buf);
    uint32_t chats_size = stoi(tmp);

    for (size_t i = 0; i < chats_size; i++)
    {
        Data::split(&buf, &tmp, &buf);
        chat_ids.push_back(stoi(tmp));
    }
    return 0;    
}





uint16_t Client::recv_user_chats(int32_t sock)
{
    std::string buf;
    Net::receive(&buf, sock);

    std::string tmp;

    Data::split(&buf, &tmp, &buf);
    int64_t chats_number = stoi(tmp);

    for (size_t i = 0; i < chats_number; i++)
    {
        Data::split(&buf, &tmp, &buf);
        int64_t chat_id = stoi(tmp);

        Data::split(&buf, &tmp, &buf);
        int32_t user1_id = stoi(tmp);

        Data::split(&buf, &tmp, &buf);
        std::string user1_name = tmp;

        Data::split(&buf, &tmp, &buf);
        int32_t user2_id = stoi(tmp);

        Data::split(&buf, &tmp, &buf);
        std::string user2_name = tmp;

        chats.push_back(Chat(chat_id, user1_id, user2_id));
        chats[i].user1_name = user1_name;
        chats[i].user2_name = user2_name;

        Data::split(&buf, &tmp, &buf);
        size_t msg_count = stoi(tmp);

        for (size_t i = 0; i < msg_count; i++)
        {
            Data::split(&buf, &tmp, &buf);
            uint32_t sender_id = stoi(tmp);

            Data::split(&buf, &tmp, &buf);
            uint32_t receiver_id = stoi(tmp);

            Data::split(&buf, &tmp, &buf);
            uint32_t msg_size = stoi(tmp);

            std::string msg = std::string(tmp, 0, msg_size);

            chats[i].new_message(sender_id, receiver_id, msg);
        }
    }
    return 0;
}


uint16_t Client::cout_chats()
{
    for (size_t i = 0; i < chats.size(); i++)
    {
        if (chats[i].user1_id != current_user_id && chats[i].user2_id != current_user_id)
        {
            throw "No current user in this chat error";
        }
                    
        std::cout << i  << ". "<< '\n';

        if (chats[i].user1_id == current_user_id)
            std::cout << chats[i].user2_name << "  ";

        else std::cout << chats[i].user1_name << '\n';

        if (chats[i].messages[chats[i].messages.size() - 1].sender_id == chats[i].user1_id)
            std::cout << chats[i].user1_name << ": ";

        else std::cout << chats[i].user2_name << ": ";

        if (chats[i].messages[chats[i].messages.size() - 1].msg.size() > 50)
            std::cout << std::string(chats[i].messages[chats[i].messages.size() - 1].msg, 0, 50) << "...\n" << '\n';

        else std::cout << chats[i].messages[chats[i].messages.size() - 1].msg << "\n\n";
    }
    return 0;
}



uint16_t Client::login(int32_t sock, std::string login, std::string password)
{
    std::string request = "/log/" + login + '\n' + password;
    
    Net::send_char(&request, sock);

    std::string success_flag;
    Net::receive(&success_flag, sock);

    if (success_flag == "success")
    {
        recv_user_data(sock);
        recv_user_chats(sock);
        return 0;
    }
    else
    {
        std::cout << success_flag << '\n';
        return 1;
    }
}

uint16_t Client::sign_up(int32_t sock, std::string login, std::string password)
{
    std::string request = "/sgn/" + login + '\n' + password;
    
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
    while (1)
    {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0)
            { perror("socket"); exit(1); }

        addr.sin_family = AF_INET;
        addr.sin_port = htons(3328);
        addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

        if (connect(sock, (sockaddr *)&addr, sizeof(addr)) < 0)
            { perror("connect"); exit(2); }



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
            system("clear");
            std::string login;
            std::string password;

            std::cout << "Регистрация.\n\nlogin: ";
            std::cin >> login;

            std::cout << "\npassword: ";
            std::cin >> password;

            int16_t sgn_status = Client::sign_up(sock, login, password);
            if (sgn_status == 0)
            {
                system("clear");
                std::cout << "Регистрация прошла успешно. \nТеперь Вы можете войти в систему используя логин и пароль указанные при регистрации" << '\n';
            }
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
    if (login_status == true)
    {
        while(1)
        {
            system("clear");
            int32_t i;
            std::cout << "1. Просмотреть чаты\n2. Профиль\n3. Выход" << '\n';
            std::cin >> i;

            if (i == 1)
            {  
                cout_chats();
                std::cout << "Выберите чат для отправки сообщения. " << '\n';
                int32_t j;
                std::cin >> j;
                std::string msg;
                std::cout << "Введите сообщение: " << '\n';
                std::cin >> msg;
                message(sock, chats[j].chat_id, current_user_id, chats[j].other_user_id(current_user_id), msg);
            }

            else if(i == 2)
            {
                std::cout << "login: " << current_login << '\n';
                std::cout << "password: " << current_password << '\n';
                std::cout << "id: " << current_user_id << '\n';
            }

            else if(i == 3)
            {
                break;
            }

            else
            {
                std::cout << "Проверьте ввод." << '\n';
                continue;
            }
        }
    }
    else return 0;
    return 0;
}