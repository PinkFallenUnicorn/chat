#include "server.hpp"


uint32_t Server::Server_users_init()
{
    if(Data::next_user_id == 0)
    {perror("Server_init: class Data not initialized"); exit(0);}
    for (uint32_t i = 1; i < Data::next_user_id; i++)
    {
        std::string filepath = "users/" + std::to_string(i);
        std::ifstream file;
        file.open(filepath);
        if(!file.is_open())
        {
            std::string errortext = "error open user file user_id: " + std::to_string(i);
            const char *errtext = errortext.c_str();
            perror(errtext); 
            exit(0);
        }
        std::string nickname;
        file >> nickname;
        std::string password;
        file >> password;
        User user{i, nickname, password};
        users.add(user);
        User *pointeer = &user;
        users_by_id.push_back(pointeer);
        file.close();
    }
    return 0;
}


uint32_t Server::Server_chats_init()
{
    if(Data::next_chat_id == 0)
    {perror("Server_init: class Data not initialized"); exit(0);}
    for (uint32_t i = 1; i < Data::next_chat_id; i++)
    {
        std::string filepath = "chats/" + std::to_string(i);
        std::ifstream file;
        file.open(filepath);
        if(!file.is_open())
        {
            std::string errortext = "error open user file chat_id: " + std::to_string(i);
            const char *errtext = errortext.c_str();
            perror(errtext); 
            exit(0);
        }
        std::string user1_id;
        file >> user1_id;
        std::string user2_id;
        file >> user2_id;
        chats.push_back(Chat(i, std::stoi(user1_id), std::stoi(user2_id)));
        file.close();
    }
    return 0;
}



/*Function which read from datafiles all data and initialize it 
as next_id variables/vector<User> users/vector<Chat> chats*/
uint32_t Server::Server_init()
{
    Data::data_init();
    Server_users_init();
    Server_chats_init();
    return 0;
}


uint32_t Server::add_user(std::string nickname, std::string password)
{
    User user{nickname, password};
    std::cout << "New user " << user << '\n';
    Server::users.add(user);
    User *pointeer = &user;
    if (users_by_id.size() == users_by_id.capacity())
        users_by_id.reserve(1000);
    users_by_id.push_back(pointeer);
    return 0;
}



uint32_t Server::add_chat(const uint32_t user1_id, const uint32_t user2_id)
{
    if (chats.size() == chats.capacity())
        chats.reserve(1000);
    Chat chat{user1_id, user2_id};
    chat.user1_name = users_by_id[user1_id]->nickname;
    chat.user2_name = users_by_id[user2_id]->nickname;
    users_by_id[user1_id]->chats.push_back(chat.chat_id);
    users_by_id[user2_id]->chats.push_back(chat.chat_id);
    chats.push_back(chat);
    return 0;
}

/*return 0 == success, return 1 == wrong login, return 2 == wrong pass */
const int16_t Server::find(std::string login, std::string password)
{
    std::cout << "Server::find started" << '\n';
    User tmpuser{0, login, password};
    int32_t i;
    Server::users.show();
    if (Server::users.search(tmpuser))
    {
        std::cout << "Server::find 12312314819283" << '\n';
        User *secondtmpuser;
        users.get(tmpuser, secondtmpuser);
        std::cout << "Server::find 923917397" << '\n';
        std::cout << secondtmpuser->password << '\n';
        if (secondtmpuser->password == password)
            i = 0;
        else
            i = 2;
    }
    else
    {
        std::cout << "Server::data::else" << '\n';
        i = 1;
    }
    std::cout << "Server::find finished" << i << '\n';
    return i;
}
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
    int16_t i = Server::find(log, pass);
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
    std::cout << "Server::sign_up started" << '\n';
    std::string log;
    std::string pass;
    Data::split(str, &log, &pass);
    std::cout << "log: " << log  << '\n';
    std::cout << "pass: " << pass << '\n';
    int16_t i = Server::find(log, pass);

    if (i == 1)
    {
        User *user =  new User{log, pass};
        std::cout << "New user " << user << '\n';
        Server::users.add(*user);
        users.show();

        //User *pointeer = &user;
        Server::users_by_id.push_back(user);

        std::string buf = "success";
        Net::send_char(&buf, sock);
        std::cout << "Server::sign_up finished" << '\n';
        return 0;
    }

    else
    {
        std::string buf = "wrong login: that login alredy in use";
        Net::send_char(&buf, sock);
        std::cout << "Server::sign_up finished" << '\n';
        return 1;
    }
}


uint16_t Server::send_user_data(std::string login, int32_t sock)
{
    User tmpuser{0, login, "0"};
    User *user;
    Server::users.get(tmpuser, user);
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
    Server::users.get(tmpuser, user);
    std::string buf = std::to_string(user->chats.size()) + '\n';
    for (size_t i = 0; i < user->chats.size(); i++)
    {
        buf += std::to_string(Server::chats[user->chats[i]].chat_id);
        buf += '\n';
        buf += std::to_string(Server::chats[user->chats[i]].user1_id);
        buf += '\n';
        buf += Server::chats[user->chats[i]].user1_name;
        buf += '\n';
        buf += std::to_string(Server::chats[user->chats[i]].user2_id);
        buf += '\n';
        buf += Server::chats[user->chats[i]].user2_name;
        buf += '\n';
        buf += std::to_string(Server::chats[user->chats[i]].msg_count());
        buf += '\n';

        for (size_t j = 0; j < Server::chats[user->chats[i]].msg_count(); j++)
        {
            buf += std::to_string(Server::chats[user->chats[i]].messages[j].sender_id);
            buf += '\n';
            buf += std::to_string(Server::chats[user->chats[i]].messages[j].receiver_id);
            buf += '\n';
            buf += std::to_string(Server::chats[user->chats[i]].messages[j].msg.size());
            buf += '\n';
            buf += Server::chats[user->chats[i]].messages[j].msg;
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

    Server::chats[chat_id].new_message(sender_id, receiver_id, msg);

    std::string buf = "success";
    Net::send_char(&buf, sock);
    return 0;
}


uint16_t Server::dirrect(std::string *str, int32_t sock)
{
    std::cout << "Server::dirrect started" << '\n';
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
    std::cout << "Server::dirrect finished" << '\n';
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
    std::cout  << users.root->data.nickname << '\n';

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
