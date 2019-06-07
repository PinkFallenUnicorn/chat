#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include "data.hpp"



class User
{
    private:
        static uint32_t next_id;
        
    public:
        std::string nickname;
        std::string password;
        const uint32_t id;

        static uint32_t user_init();
        static uint32_t rewrite_next_id();

        User(std::string nickname, std::string password) : 
        id(next_id), nickname(nickname), password(password)
        { 
            next_id += 1; 
            rewrite_next_id();
        }

};


#endif //USER_HPP