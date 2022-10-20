//
// Created by 冯昊 on 2022/10/18.
//

#include "frontend.h"


User Frontend::login(string name, string password) {
    int property;
    string user_id;
    if (db.query_user(name, password, property, user_id)) {
        return {name, property, user_id};
    }
    return User(-1);
}

int Frontend::find_class(const string &teacher, std::map<string, std::shared_ptr<std::vector<string>>> &result) {
    return db.query_class(teacher, result);
}
