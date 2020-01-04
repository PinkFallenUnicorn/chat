#ifndef SERVER_HPP
#define SERVER_HPP

#include "user.hpp"
#include "chat.hpp"
#include "net.hpp"



class Server
{
    public:
        uint16_t detect(std::string *str);
        uint16_t login(std::string *str, int32_t sock);
        uint16_t dirrect(std::string *str, int32_t sock);
        uint16_t message(std::string *str, int32_t sock);
        uint16_t send_user_data(std::string login, int32_t sock);
        uint16_t send_user_chats(std::string login, int32_t sock);
        uint16_t sign_up(std::string *str, int32_t sock);
        uint16_t run();
        uint32_t Server_init();

        Tree <User> users{};
        std::vector <Chat> chats{};
        std::vector <User *> users_by_id{};
        uint32_t add_user(std::string nickname, std::string password);
        uint32_t add_chat(const uint32_t user1_id, const uint32_t user2_id);
        const int16_t find(std::string login, std::string password);
        Server()
        {
            User alfa_user{"nickname", "password"};
            User *pointeer = &alfa_user;
            users.add(alfa_user);
            users_by_id.push_back(pointeer);
        }
    private:
        int32_t sock;
        int32_t listener;
        sockaddr_in addr;
        uint32_t Server_users_init();
        uint32_t Server_chats_init();
        
};

#endif //SERVER_HPP