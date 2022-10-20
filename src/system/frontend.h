//
// Created by 冯昊 on 2022/10/18.
//

#ifndef OOM_CLASSROOM_FRONTEND_H
#define OOM_CLASSROOM_FRONTEND_H


//todo 支持学生、教师的前台操作
//登陆登出：查库、
//创建课堂：内存数据结构

#include "../data/database.h"
#include "../entity/user.h"

using std::string;

class Frontend {

public:

    explicit Frontend(const char *name = "oom", const char *ip = "10.211.55.3", const char *user = "root",
                      const char *password = "root", int port = 3306) : db(name, ip, user, password, port) {};

    User login(string name, string password);

    int find_class(const string &teacher, std::map<string, std::shared_ptr<std::vector<string>>> &result);


private:
    Database db;

};


#endif //OOM_CLASSROOM_FRONTEND_H
