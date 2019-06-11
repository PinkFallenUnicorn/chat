#include "chat.hpp"
#include "data.hpp"
#include "user.hpp"

int main()
{
    Data::first_data_init();
    Data::data_init();
    User asada {"oasodjaosd", "assadsaddas"};
    User aasdsada {"oasosdjaosd", "assadsaddas"};
    User asafda {"oasodjao1sd", "assadsaddas"};
    User asddada {"oasodjasosd", "assadsaddas"};
    User asasdada {"oagsodjaosd", "assadsaddas"};
    Chat newchat {asada.id, aasdsada.id};
    Chat::message msg {newchat, newchat.user1_id, newchat.user2_id, "ojsadajsdojasodjaosjdosajdoajodojsvbasdhosjdaosdhbfjiabds"};
    return 0;
}