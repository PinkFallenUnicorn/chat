#ifndef USER_HPP
#define USER_HPP


#include "chat.hpp"



class User
{ 
    public:
        std::string nickname;
        std::string password;
        const uint32_t id;
        std::vector<uint64_t> chats;

        static uint32_t add_chat(uint32_t user_id, uint64_t chat_id);

        User(std::string nickname, std::string password) : 
        id(Data::next_user_id), nickname(nickname), password(password)
        { 
            add_user_file();
            Data::next_user_id += 1; 
            Data::rewrite_next_id();
        }
        User(const uint32_t id, std::string nickname, std::string password) : 
        id(id), nickname(nickname), password(password)
        {}

        friend bool operator==(const User &left, const User &right);
        friend bool operator<(const User &left, const User &right);
        friend bool operator>(const User &left, const User &right);
        friend std::ostream& operator<<(std::ostream &out, const User &user);

    private:
        uint32_t add_user_file();   
};


#endif //USER_HPP