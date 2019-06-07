#include "chat.hpp"
#include "data.hpp"
#include "user.hpp"

int main()
{
    Data::data_init();
    User::user_init();
    User a{"asdasd", "idasjijaisj"};

    return 0;
}