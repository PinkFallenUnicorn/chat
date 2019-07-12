#ifndef CHAT_HPP
#define CHAT_HPP


#include "data.hpp"


class Chat
{
    public:
        const uint32_t user1_id;
        const uint32_t user2_id;
        const uint64_t chat_id;
        std::string user1_name;
        std::string user2_name;
    
        Chat(const uint32_t user1_id, const uint32_t user2_id); 
        Chat(const uint32_t chat_id, const uint32_t user1_id, const uint32_t user2_id); 
        uint32_t new_message(const uint32_t sender_id, const uint32_t receiver_id, const std::string msg);
        uint16_t other_user_id(uint32_t user_id);

    private:
        struct message
        {
            const uint32_t sender_id;
            const uint32_t receiver_id; //Добавить текущее время
            const std::string msg;
            
            message(const uint32_t sender_id, const uint32_t receiver_id, const std::string msg) : 
            sender_id (sender_id), receiver_id(receiver_id), msg(msg) 
            {}

            void showthismessage() 
            { std::cout << "sender id: " << sender_id << '\n' << "receiver id: " << receiver_id << '\n' << "message: " << msg << '\n'; }
        };

        uint32_t add_message_file();
        uint32_t add_chat_to_userfile();
        uint32_t add_chat_file();
        uint32_t size;
    public:
        std::vector<message> messages;
        size_t msg_count() { return messages.size();}
};

#endif //CHAT_HPP