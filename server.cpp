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
    std::string log;
    std::string pass;
    Data::split(str, &log, &pass);
    int16_t i = Server_data::find(log, pass);
    if (i == 0)
    {
        std::string buf = "success";
        Net::send_char(&buf, sock);
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
    }

    else
    {
        std::string buf = "wrong login: that login alredy in use";
        Net::send_char(&buf, sock);
    }
    
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


uint16_t Server::listen(std::string *str, int32_t sock)
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

    else if (num == 3)
    {
        message(str, sock);
        return 0;
    }
    return 0;
}
