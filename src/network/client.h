//
// Created by 冯昊 on 2022/10/18.
//

#ifndef OOM_CLASSROOM_CLIENT_H
#define OOM_CLASSROOM_CLIENT_H


//todo client
//server 和 命令行交互

#include <string>

class Client {
public:

    int start(int port);

private:

    void handle_message(int client, const std::string& header, const std::string& data);

    void wait_command(int client);

    void login(int client);

    std::string command_list;

};


#endif //OOM_CLASSROOM_CLIENT_H
