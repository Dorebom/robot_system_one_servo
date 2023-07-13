#include <iostream>
#include <chrono>
#include <thread>
#include <array>
#include <cmath>

#include "../Comm/comm_udp.hpp"

CommUdp comm_udp_;

struct RecvData
{
    /* data */
    int id;
    int num;
    double num_d;
    RecvData()
    {
        id = 1;
        num = 0;
    }
};

struct SendData
{   
    int id;
    int num;
    double num_d;
    std::array<double, 3> xyz;
    SendData()
    {
        id = 11;
        num = 0;
        num_d = M_PI;
        xyz[0] = 1.0;
        xyz[1] = 2.0;
        xyz[2] = 3.0;
    }
};

void task_recv()
{
    std::cout << "Recv thread" << std::endl;

    RecvData recv_data;

    while (1)
    {
        comm_udp_.recv_data(reinterpret_cast<uint8_t*>(&recv_data), sizeof(RecvData));

        // Process
        std::cout << recv_data.id << std::endl;
        std::cout << recv_data.num << std::endl;
        std::cout << recv_data.num_d << std::endl;

        std::this_thread::sleep_for(std::chrono::microseconds(100000));	
    }
}

void task_send()
{
    std::cout << "Send thread" << std::endl;

    SendData send_data;

    while (1)
    {
        // Process
        send_data.num++;

        comm_udp_.send_data(reinterpret_cast<uint8_t*>(&send_data), sizeof(SendData));
        std::this_thread::sleep_for(std::chrono::microseconds(1000000));	
    }
}

int main()
{
    std::cout << "Hello" << std::endl;

    std::thread th_recv(task_recv);
    std::thread th_send(task_send);

    th_recv.join();
    th_send.join();

    return 0;
}