#include "net.hpp"


int32_t Net::recv_int32(int32_t *value, int32_t sock)
{
    std::cout << "Net::recv_int32 started" << '\n';
    *value = 1;
    char* recv_buffer = (char*)value;
    recv(sock, recv_buffer, sizeof(recv_buffer), 0);
    std::cout << "Net::recv_int32 finished, value = " << *value << '\n';
    return 0;
}

int32_t Net::receive(char *buf, int32_t sock)
{
    std::cout << "Net::receive started" << '\n';
    int32_t bufsize;
    bufsize = 0;
    Net::recv_int32(&bufsize, sock);
    std::cout << "Net::receive: bufsize is:" << bufsize << '\n';
    recv(sock, buf, bufsize, 0);
    std::cout << "Net::receive finished, buf = " << buf << '\n';
    return 0;
}    


int32_t Net::send_int32(int32_t *value, int32_t sock)
{
    std::cout << "Net::send_int32 started, value =" << *value << '\n';
    char* send_buffer = (char*)value;
    int32_t sent = send(sock, value, sizeof(*value), 0);      
    std::cout << "Net::send_int32 finished, sent " << sent << " bytes" << '\n';
    return sent;
}


int32_t Net::send_char(std::string *buf, int32_t sock)
{
    std::cout << "Net::send_char started" << '\n';
    int32_t bufsize;
    bufsize = buf->size();
    std::cout << "Net::send_char: bufsize is: " << bufsize << '\n';
    Net::send_int32(&bufsize, sock);
    uint32_t sent = send(sock, buf->c_str(), bufsize, 0);

    return sent;       
}    