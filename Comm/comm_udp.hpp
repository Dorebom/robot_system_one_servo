#pragma once

#include <stdio.h>
#include <sys/types.h>
#include <cstdint>

#ifdef __linux__ 
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    //#include <netdb.h>
#elif 	_WIN64
    #include <WinSock2.h>
    #include <ws2tcpip.h>
    //#include <Windows.h>
#endif

#include "param_comm_udp.hpp"

class CommUdp
{
private:
    /* data */
#ifdef __linux__ 
    int recv_socket;
    int send_socket;
    struct sockaddr_in recv_address;
    struct sockaddr_in send_address;
#elif 	_WIN64
    SOCKET send_socket;
    SOCKET recv_socket;
//    SOCKET send_sock;
    WSADATA recv_wsaData;
    WSADATA send_wsaData;
    SOCKADDR_IN send_address;
    SOCKADDR_IN recv_address;
#endif
public:
    CommUdp(/* args */);
    ~CommUdp();
    void send_data(const uint8_t *data, int data_size);
    void recv_data(uint8_t *data, int data_size);
};

