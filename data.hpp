#ifndef DATA_HPP
#define DATA_HPP


#include <vector>
#include <iostream>
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "b_tree.hpp"


class Data
{
    private:

    public:
        static uint64_t next_chat_id;
        static uint32_t next_user_id;
        static uint32_t data_init();
        static uint32_t first_data_init();
        static uint32_t rewrite_next_id();

};



#endif //DATA_HPP