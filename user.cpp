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
