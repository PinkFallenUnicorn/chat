#include "chat.hpp"
#include "data.hpp"
#include "user.hpp"
#include "server_data.hpp"
#include "client.hpp"

int main()
{
    //Data::first_data_init();
    std::string sstr = "123456789101112131415";
    std::string str = std::string(sstr, 0, 6);
    sstr = std::string(sstr, 6);
    std::cout << str << '\n';
    std::cout << sstr << '\n';
    
    return 0;
}