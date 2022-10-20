//
// Created by 冯昊 on 2022/10/18.
//

#ifndef OOM_CLASSROOM_USER_H
#define OOM_CLASSROOM_USER_H


//todo 基类user
//子类

#include <string>

class User {

public:
    User(int cliSock, bool active);

    User(const std::string &name, int aProperty, const std::string &userId);

    explicit User(int aProperty);

    int cli_sock;
    bool active;

    std::string name;
    int property;
    std::string user_id;

};


#endif //OOM_CLASSROOM_USER_H
