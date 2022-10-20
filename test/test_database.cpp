//
// Created by 冯昊 on 2022/10/18.
//

#include "gtest/gtest.h"
#include "../src/data/database.h"
#include <string>
#include <vector>
#include <map>

TEST(TestDatebase, test_query_user) {
    Database db;
    std::vector<std::string> res;
    std::string name = "cao";
    std::string pass = "333333";
    int property;
    std::string user_id;
    int num = db.query_user(name, pass, property, user_id);

    EXPECT_EQ(property, 1);
    EXPECT_STREQ(user_id.c_str(), "cao123");
}


TEST(TestDatebase, test_query_class) {
    Database db;
    std::map<std::string, std::shared_ptr<std::vector<std::string>>> result;
    int num = db.query_class("cao", result);

    EXPECT_EQ(num, 1);
    EXPECT_EQ(result.size(), 1);
    auto it = result.find("面向对象方法学");
    EXPECT_EQ(it->second->size(), 1);
}

TEST(TestDatebase, test_query_two) {
    Database db;

    std::vector<std::string> res;
    std::string name = "cao";
    std::string pass = "333333";
    int property;
    std::string user_id;
    int num = db.query_user(name, pass, property, user_id);

    EXPECT_EQ(property, 1);
    EXPECT_STREQ(user_id.c_str(), "cao123");


    std::map<std::string, std::shared_ptr<std::vector<std::string>>> result;
    num = db.query_class("cao", result);

    EXPECT_EQ(num, 1);
    EXPECT_EQ(result.size(), 1);
    auto it = result.find("面向对象方法学");
    EXPECT_EQ(it->second->size(), 1);
}
