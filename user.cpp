#include "user.hpp"

uint32_t User::add_user_file()
{
    const std::string filepath = "users/" + std::to_string(id);
    std::cout << id << '\n';
    const std::string command = "touch " + filepath;
    const char *comm = command.c_str();
    std::cout << command << '\n';

    system(comm);

    std::ofstream file;
    file.open(filepath);
    
    std::string errortext = "error open user file user_id: " + std::to_string(id);
    const char *errtext = errortext.c_str();
    if (!file.is_open()) {perror(errtext); exit(0);}

    else 
    { file << nickname << '\n' << password << '\n';}
    file.close();
    
    return 0;
}
