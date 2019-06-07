#include "data.hpp"


std::string Data::filepath = "";


int32_t Data::data_init()
{
    system ("rm -rf data");
    system("mkdir data");
    system("touch data/next_id");

    filepath = "data/next_id";

    std::ofstream file;
    file.open(filepath);

    if (!file.is_open()) {perror("open data/next_id"); exit(0);}
    else 
    {
        file << "1\n";
    }

    file.close();

    return 0;
}