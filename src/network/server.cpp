//
// Created by 冯昊 on 2022/10/18.
//

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <utility>
#include "server.h"
#include "data_transfer.h"
#include "data_template.h"

int Server::start(int port) {

    std::cout << "This is server" << std::endl;
    // socket
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd == -1) {
        std::cout << "Error: socket" << std::endl;
        return 0;
    }
    // bind
    struct sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(listen_fd, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
        std::cout << "Error: bind" << std::endl;
        return 0;
    }
    // listen
    if (listen(listen_fd, 5) == -1) {
        std::cout << "Error: listen" << std::endl;
        return 0;
    }
    // accept
    struct sockaddr_in clientAddr{};
    socklen_t clientAddrLen = sizeof(clientAddr);
    int new_socket;
    while (true) {
        if ((new_socket = accept(listen_fd, (struct sockaddr *) &clientAddr, &clientAddrLen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        std::cout << "Client: " << new_socket << " connected" << std::endl;
        pthread_t new_thread;
        auto *socks = (sockets *) (malloc(sizeof(sockets)));
        socks->cli_sock = new_socket;
        socks->serv_sock = listen_fd;

        pthread_create(&new_thread, nullptr, (creat_handle_thread), socks);
    }
    close(listen_fd);
    return 0;
}

void *Server::creat_handle_thread(void *arg) {

    auto *socks = (sockets *) arg;
    User user = User(socks->cli_sock, true);

    std::cout << "Thread spawned" << std::endl;

    handle_client(user);

    return nullptr;
}

void Server::handle_client(User user) {
    std::cout << "Handling client" << std::endl;
    int cli_sock = user.cli_sock;
    string message = HANDLE_CLI;
    send_data(cli_sock, "WAIT_LOGIN", true, message);
    while (true) {
        if (!(user.active)) {
            break;
        }

        string header;
        string data;
        int data_recv;
        recv_data(cli_sock, header, data);
        std::vector<string> strings_list = split_string(header);
        std::vector<string> parameters = split_string(data);
        if (strings_list[0] == "LOGIN") {
            string username = parameters[0];
            string passwd = parameters[1];
            User log_user = login(username, passwd);
            if (log_user.property < 0) {
                send_data(cli_sock, "LOGIN", false, "LOGIN_FAIL");
            } else {
                user.name = log_user.name;
                user.property = log_user.property;
                user.user_id = log_user.user_id;
                string new_message = "Welcome ";
                switch (user.property) {
                    case 0:
                        new_message += "root manager " + user.name + "\n";
                        break;
                    case 1:
                        new_message += "Teacher " + user.name + "\n" + SPLITTER;
                        new_message += TEACHER_MANUEL;
                        break;
                    case 2:
                        new_message += "Student " + user.name + "\n";
                        break;
                }

                send_data(cli_sock, "LOGIN", true, new_message);
            }
        } else if (strings_list[0] == "class") {

            if (user.property != 1)break;
            auto res = find_class(user.name);
            if (res.empty()) {
                send_data(cli_sock, "FIND_CLASS", false, "you dont have a class");
            } else {
                std::stringstream ss;
                ss << "your classes:" << std::endl;
                for (const auto &item: res) {
                    ss << "\t" << item.first << ":" << std::endl << "\t\t";
                    for (const auto &stu: *item.second) {
                        ss << stu << " ";
                    }
                    ss << std::endl;
                }
                send_data(cli_sock, "FIND_CLASS", true, ss.str());
            }

        } else {
            send_data(cli_sock, "WRONG_COMMAND", false, "");
        }
    }
}


User Server::login(string name, string password) {
    return frontend.login(std::move(name), std::move(password));
}

std::map<string, std::shared_ptr<std::vector<string>>> Server::find_class(string &teacher) {
    std::map<string, std::shared_ptr<std::vector<string>>> res;
    frontend.find_class(teacher, res);
    return res;
}

Frontend Server::frontend = Frontend();
