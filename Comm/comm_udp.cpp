#include "comm_udp.hpp"
#include <iostream>

CommUdp::CommUdp(/* args */)
{
    // Init Recv 
#ifdef _WIN64
    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &recv_wsaData) != 0)
    {
        std::cerr << "Failed to initialize Winsock\n";
        return;
    }
#endif
    // Create a socket for UDP communication
    recv_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
#ifdef _WIN64
    if (recv_socket == INVALID_SOCKET)
    {
        std::cerr << "Failed to create receiver socket\n";
        WSACleanup();
        return;
    }
#endif
    // Bind the socket to any available IP and the specified port
    recv_address.sin_family = AF_INET;
    recv_address.sin_port = htons(UDP_PORT_RECV);
    recv_address.sin_addr.s_addr = INADDR_ANY;
#ifdef _WIN64
    if (bind(recv_socket, (SOCKADDR*)&recv_address, sizeof(recv_address)) == SOCKET_ERROR)
    {
        std::cerr << "Failed to bind receiver socket\n";
        closesocket(recv_socket);
        WSACleanup();
        return;
    }
#elif __linux__
    bind(recv_socket, (struct sockaddr*)&recv_address, sizeof(recv_address));
#endif

    // Init Send 
#ifdef _WIN64
    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &send_wsaData) != 0)
    {
        std::cerr << "Failed to initialize Winsock\n";
        return;
    }
#endif
    // Create a socket for UDP communication
    send_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
#ifdef _WIN64
    if (send_socket == INVALID_SOCKET)
    {
        std::cerr << "Failed to create sender socket\n";
        WSACleanup();
        return;
    }
#endif
    // Set up receiver address
    send_address.sin_family = AF_INET;
    send_address.sin_port = htons(UDP_PORT_SEND);
#ifdef _WIN64
    InetPtonA(send_address.sin_family, ("127.0.0.1"), &send_address.sin_addr.S_un.S_addr);
#elif __linux__
    send_address.sin_addr.s_addr = inet_addr(UDP_SEND_IP);
#endif
}

CommUdp::~CommUdp()
{
#ifdef _WIN64
    // Clean up
    closesocket(recv_socket);
    WSACleanup();
#else
    close(recv_socket);
#endif
}

void CommUdp::recv_data(uint8_t *data, int data_size)
{
#ifdef __linux__
    struct sockaddr_in senderinfo;
    socklen_t addrlen = sizeof(senderinfo);
    recvfrom(recv_socket, data, data_size, 0, (struct sockaddr*)&senderinfo, &addrlen);
#elif _WIN64
    SOCKADDR_IN senderinfo;
    int addrlen = sizeof(senderinfo);
    int bytesRead = recvfrom(recv_socket, reinterpret_cast<char*>(data), data_size, 0, (SOCKADDR*)&senderinfo, &addrlen);
    std::cout << "Recv data size: " << bytesRead << std::endl;

    /*
    for (size_t i = 0; i < data_size; i++)
    {
        std::cout << data[i] << std::endl;
    }
    */

#endif // _WIN64

}

void CommUdp::send_data(const uint8_t *data, int data_size)
{
#ifdef __linux__
    sendto(send_socket, data, data_size, 0, (struct sockaddr *)&send_address, sizeof(send_address));
#elif _WIN64
    sendto(send_socket, reinterpret_cast<const char*>(data), data_size, 0, (SOCKADDR*)&send_address, sizeof(send_address));
    //std::string message = "Hello";
    //sendto(send_socket, message.c_str(), sizeof(message), 0, (SOCKADDR*)&send_address, sizeof(send_address));

#endif // _WIN64
}