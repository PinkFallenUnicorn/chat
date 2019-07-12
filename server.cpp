#include "server.hpp"


/*function, which takes a string *, 
    string must look like "/tag/other data"
   "cut off" a /tag/ from that string, 
   and returns a value which depends on that tag*/
uint16_t Server::detect(std::string *str)
{
    std::string tag = std::string(*str, 0, 5);
    *str = std::string(*str, 5);
    if (tag == "/log/")
        return 1;
    else if (tag == "/sgn/")
        return 2;
    else if (tag == "/msg/")
        return 3;
    //write more when needed
    return 0;
}


uint16_t Server::login(std::string *str, int32_t sock)
{
    std::cout << "Server::login started" << '\n';
    std::string log;
    std::string pass;
    Data::split(str, &log, &pass);
    int16_t i = Server_data::find(log, pass);
    if (i == 0)
    {
        std::string buf = "success";
        Net::send_char(&buf, sock);
        send_user_data(log, sock);
        send_user_chats(log, sock);
    }

    if (i == 1)
    {
        std::string buf = "wrong login";
        Net::send_char(&buf, sock);
    }

    if (i == 2)
    {
        std::string buf = "wrong password";
        Net::send_char(&buf, sock);
    }
    std::cout << "Server::login finished" << i << '\n';
    
    return 0;
}


uint16_t Server::sign_up(std::string *str, int32_t sock)
{
    std::string log;
    std::string pass;
    Data::split(str, &log, &pass);
    int16_t i = Server_data::find(log, pass);

    if (i == 1)
    {
        User user{log, pass};
        Server_data::users.add(user);

        User *pointeer = &user;
        Server_data::users_by_id.push_back(pointeer);

        std::string buf = "success";
        Net::send_char(&buf, sock);
        return 0;
    }

    else
    {
        std::string buf = "wrong login: that login alredy in use";
        Net::send_char(&buf, sock);
        return 1;
    }
    

}


uint16_t Server::send_user_data(std::string login, int32_t sock)
{
    User tmpuser{0, login, "0"};
    User *user;
    Server_data::users.get(tmpuser, user);
    std::string buf = std::to_string(user->id) + '\n' + std::to_string(user->chats.size()) + '\n';
    for (size_t i = 0; i < user->chats.size(); i++)
    {
        buf += std::to_string(user->chats[i]);
        buf += '\n';
    }
    
    Net::send_char(&buf, sock);
    return 0;
}


uint16_t Server::send_user_chats(std::string login, int32_t sock)
{
    User tmpuser{0, login, "0"};
    User *user;
    Server_data::users.get(tmpuser, user);
    std::string buf = std::to_string(user->chats.size()) + '\n';
    for (size_t i = 0; i < user->chats.size(); i++)
    {
        buf += std::to_string(Server_data::chats[user->chats[i]].chat_id);
        buf += '\n';
        buf += std::to_string(Server_data::chats[user->chats[i]].user1_id);
        buf += '\n';
        buf += Server_data::chats[user->chats[i]].user1_name;
        buf += '\n';
        buf += std::to_string(Server_data::chats[user->chats[i]].user2_id);
        buf += '\n';
        buf += Server_data::chats[user->chats[i]].user2_name;
        buf += '\n';
        buf += std::to_string(Server_data::chats[user->chats[i]].msg_count());
        buf += '\n';

        for (size_t j = 0; j < Server_data::chats[user->chats[i]].msg_count(); j++)
        {
            buf += std::to_string(Server_data::chats[user->chats[i]].messages[j].sender_id);
            buf += '\n';
            buf += std::to_string(Server_data::chats[user->chats[i]].messages[j].receiver_id);
            buf += '\n';
            buf += std::to_string(Server_data::chats[user->chats[i]].messages[j].msg.size());
            buf += '\n';
            buf += Server_data::chats[user->chats[i]].messages[j].msg;
        }   
    }
    
    Net::send_char(&buf, sock);
    return 0;
}


uint16_t Server::message(std::string *str, int32_t sock)
{
    std::string tmp;

    Data::split(str, &tmp, str);
    uint64_t chat_id = stoi(tmp);
    
    Data::split(str, &tmp, str);
    uint32_t sender_id = stoi(tmp);

    Data::split(str, &tmp, str);
    uint32_t receiver_id = stoi(tmp);

    std::string msg = *str;

    Server_data::chats[chat_id].new_message(sender_id, receiver_id, msg);

    std::string buf = "success";
    Net::send_char(&buf, sock);
    return 0;
}


uint16_t Server::dirrect(std::string *str, int32_t sock)
{
    int16_t num = detect(str);

    if (num == 0)
    {
        std::cout << "Server::listen: message w/o tag" << '\n';
    }

    else if (num == 1)
    {
        login(str, sock);
        return 0;
    }

    else if (num == 2)
    {
        sign_up(str, sock);
        return 0;
    }

    else if (num == 3)
    {
        message(str, sock);
        return 0;
    }
    return 0;
}


uint16_t Server::run()
{
    listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener < 0)
        {perror("listener"); exit(0);}
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3328);
    addr.sin_addr.s_addr = (INADDR_ANY);

    if (bind(listener,(sockaddr *)&addr, sizeof(addr)) < 0)
        {perror("bind"); exit(0);}
    
    listen(listener, 1);

    while (1)
    {
        sock = accept(listener, nullptr, nullptr);
        if (sock < 0)
            {perror("accept"); exit(0);}
        
        uint32_t forkstatus = fork();
        if (forkstatus == -1)
            { perror("fork"); exit(0);}
        else if (forkstatus == 0)
        {
            close(listener);
            while (1)
            {
                std::string buf;
                int32_t i = Net::receive(&buf, sock);
                dirrect(&buf, sock);
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
