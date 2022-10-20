//
// Created by 冯昊 on 2022/10/18.
//

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <csignal>
#include <vector>
#include "client.h"
#include "data_transfer.h"
#include "data_template.h"

using std::string;

int Client::start(int port) {
    std::cout << "This is client" << std::endl;
    // socket
    int client = socket(AF_INET, SOCK_STREAM, 0);
    if (client == -1) {
        std::cout << "Error: socket" << std::endl;
        return 0;
    }
    // connect
    struct sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(client, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        std::cout << "Error: connect" << std::endl;
        return 0;
    }
    std::cout << "...connect" << std::endl;
    while (true) {
        string header;
        string data;
        int data_recv;
        recv_data(client, header, data);

        handle_message(client, header, data);
    }
    close(client);
    return 0;
}

void Client::handle_message(int client, const std::string &header, const std::string &data) {
    std::vector<string> strings_list = split_string(header);
    std::vector<string> parameters = split_string(data);
    auto head = strings_list[0];
    if (head == "WAIT_LOGIN") {
        system("clear");
        std::cout << parameters[0] << std::endl;
        login(client);
    } else if (head == "LOGIN") {
        if (strings_list[1] == "OK") {
            system("clear");
            std::cout << parameters[0] << std::endl;
            command_list = string(parameters[1]);
            wait_command(client);
        } else {
            std::cout << parameters[0] << std::endl << "try type 'login' again:" << std::endl;
            login(client);
        }
    } else if (head == "FIND_CLASS") {

        if (strings_list[1] == "OK") {
            system("clear");
            std::cout << parameters[0] << std::endl;
            wait_command(client);
        } else {
            system("clear");
            std::cout << parameters[0] << std::endl;
            wait_command(client);
        }

    }else if (head=="WRONG_COMMAND"){
        std::cout <<"invalid command! type again:"<< std::endl;
        wait_command(client);
    }

}

void Client::login(int client) {
    string command;
    std::cin >> command;
    while (command != "login") {
        std::cout << "type again" << std::endl << std::endl;
        std::cin >> command;
    }
    string username, password;
    std::cout<<"username:";
    std::cin >> username;
    std::cout<<"password:";
    std::cin>> password;
    send_data(client, "LOGIN", true, username + SPLITTER + password);
}

void Client::wait_command(int client) {
    std::cout << command_list << std::endl;
    string command;
    std::cin >> command;
    send_data(client, command, true, "");
}
