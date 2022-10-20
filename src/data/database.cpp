//
// Created by 冯昊 on 2022/10/18.
//

#include "database.h"

bool Database::query_user(std::string &name, std::string &password, int &property, std::string &user_id) {

    mysqlpp::Query query = conn.query();
    query << "select property,user_id from user where name=" << mysqlpp::quote_only << name << " and password="
          << mysqlpp::quote_only << password;
    auto s = query.str();
    mysqlpp::StoreQueryResult res = query.store();
    if (!res.empty()) {
        property = int(res[0]["property"]);
        user_id = std::string(res[0]["user_id"]);
        return true;
    }
    return false;
}

int
Database::query_class(const std::string &teacher,
                      std::map<std::string, std::shared_ptr<std::vector<std::string>>> &result) {
    mysqlpp::Query query = conn.query();
    query << "select id,name from class where teacher=" << mysqlpp::quote_only << teacher;
    mysqlpp::StoreQueryResult res = query.store();

    for (int i = 0; i < res.num_rows(); ++i) {
        std::string id = std::string(res[i]["id"]);
        std::string name = std::string(res[i]["name"]);
        mysqlpp::Query query_in = conn.query();
        query_in << "select name from user where id in (select user_id from class_user where class_id=" << id
                 << " and user_property=2)";
        mysqlpp::StoreQueryResult res_in = query_in.store();
        std::vector<std::string> temp;
        auto sptr = std::make_shared<std::vector<std::string>>(temp);
        for (const auto &item: res_in) {
            sptr->emplace_back(std::string(item["name"]));
        }
        result[name] = sptr;
    }

    return int(res.num_rows());
}
