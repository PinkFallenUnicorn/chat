#ifndef CHAT_HPP
#define CHAT_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include "data.hpp"


class Chat
{
    public:
        const uint32_t user1_id;
        const uint32_t user2_id;
        const uint64_t chat_id;

        struct message
        {
            const uint32_t sender_id;
            const uint32_t receiver_id; //Добавить текущее время
            const uint64_t chat_id;
            const std::string msg;
            uint32_t add_message();

            message(Chat chat, const uint32_t sender_id, const uint32_t receiver_id, const std::string msg) : 
            chat_id(chat.chat_id), sender_id (sender_id), receiver_id(receiver_id), msg(msg) 
            {
                add_message();
            }

            void showthismessage() 
            { std::cout << "sender id: " << sender_id << '\n' << "receiver id: " << receiver_id << '\n' << "message: " << msg << '\n'; }

        };

        Chat(const uint32_t user1_id, const uint32_t user2_id); 

    private:
        uint32_t add_chat();
        uint32_t add_chat_file();
        uint32_t size;
        std::vector<message> messages;

};

#endif //CHAT_HPP