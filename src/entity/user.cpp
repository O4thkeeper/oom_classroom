//
// Created by 冯昊 on 2022/10/18.
//

#include "user.h"

#include <utility>


User::User(int cliSock, bool active) : cli_sock(cliSock), active(active) {}

User::User(int aProperty) : property(aProperty) {}

User::User(const std::string &name, int aProperty, const std::string &userId) : name(name), property(aProperty),
                                                                                user_id(userId) {}
