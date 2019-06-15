#include "chat.hpp"
#include "data.hpp"
#include "user.hpp"
#include "server_data.hpp"

int main()
{
    //Data::first_data_init();
    Server_data::server_data_init();
    std::cout << Server_data::users[2].nickname << '\n';
    std::cout << Server_data::chats[0].user2_id << '\n';

    return 0;
}