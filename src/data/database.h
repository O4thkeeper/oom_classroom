//
// Created by 冯昊 on 2022/10/18.
//

#ifndef OOM_CLASSROOM_DATABASE_H
#define OOM_CLASSROOM_DATABASE_H

#include <mysql++.h>
#include <string>
#include <vector>
#include <map>

class Database {

public:

    explicit Database(const char *name = "oom", const char *ip = "127.0.0.1", const char *user = "root",
                      const char *password = "root", int port = 3306) :
            conn(false) {
        if (!conn.connect(name, ip, user, password, port)) {
            std::cout << "cannot connect database" << std::endl;
            exit(0);
        }
    }

    bool query_user(std::string &name, std::string &password, int &r_property, std::string &r_user_id);

    int
    query_class(const std::string &teacher, std::map<std::string, std::shared_ptr<std::vector<std::string>>> &result);


private:

    mysqlpp::Connection conn;

};


#endif //OOM_CLASSROOM_DATABASE_H
