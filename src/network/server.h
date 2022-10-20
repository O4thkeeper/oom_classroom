//
// Created by 冯昊 on 2022/10/18.
//

#ifndef OOM_CLASSROOM_SERVER_H
#define OOM_CLASSROOM_SERVER_H


#include "../system/frontend.h"

//todo server
//与client 和 backend、frontend 交互
class Server {

public:

    int start(int port);

private:

    static void *creat_handle_thread(void *arg);

    static void handle_client(User user);

    static User login(string name, string password);

    static std::map<string, std::shared_ptr<std::vector<string>>> find_class(string &teacher);

    static Frontend frontend;

};

typedef struct sockets {
    int cli_sock;
    int serv_sock;
} sockets;


#endif //OOM_CLASSROOM_SERVER_H
