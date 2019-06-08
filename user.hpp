#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include "data.hpp"



class User
{
    private:
        uint32_t add_user_file();    
    public:
        std::string nickname;
        std::string password;
        const uint32_t id;

        User(std::string nickname, std::string password) : 
        id(Data::next_user_id), nickname(nickname), password(password)
        { 
            add_user_file();
            Data::next_user_id += 1; 
            Data::rewrite_next_id();
        }
};


#endif //USER_HPP