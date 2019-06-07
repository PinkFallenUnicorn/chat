#ifndef CHAT_HPP
#define CHAT_HPP

#include <iostream>
#include <fstream>
#include <vector>
struct message;

class Chat
{
    public:
        struct message
        {
            const uint32_t sender_id;
            const uint32_t receiver_id; //Добавить текущее время
            const std::string msg;

            message(const uint32_t sender_id, const uint32_t receiver_id, const std::string msg) : sender_id (sender_id), receiver_id(receiver_id), msg(msg) 
            {}

            void showthismessage() 
            { std::cout << "sender id: " << sender_id << '\n' << "receiver id: " << receiver_id << '\n' << "message: " << msg << '\n'; }

        };

    private:
        const uint32_t user1_id;
        const uint32_t user2_id;
        uint32_t size;
        std::vector<message> messages;

};

#endif //CHAT_HPP