#include "user.hpp"



uint32_t User::add_user_file()
{
    const std::string filepath = "users/" + std::to_string(id);
    const std::string command = "touch " + filepath;
    const char *comm = command.c_str();

    system(comm);

    std::ofstream file;
    file.open(filepath);
    
    if (!file.is_open()) 
    {
        std::string errortext = "error open user file user_id: " + std::to_string(id);
        const char *errtext = errortext.c_str();
        perror(errtext);
        exit(0);
    }

    else 
    { file << nickname << '\n' << password << '\n';}
    file.close();
    
    return 0;
}


std::ostream& operator<<(std::ostream &out, const User &user)
{
    out << user.id << '\n' << user.nickname << '\n' << user.password << '\n';

    return out;
}


bool operator==(const User &left, const User &right)
{
    std::cout << left.nickname << " " <<  left.nickname.size()  << '\n' << right.nickname << " " << right.nickname.size()  << '\n';
    return left.nickname == right.nickname;
}


bool operator<(const User &left, const User &right)
{
    return left.nickname < right.nickname;
}


bool operator>(const User &left, const User &right)
{
    return left.nickname > right.nickname;
}