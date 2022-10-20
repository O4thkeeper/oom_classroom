//
// Created by 冯昊 on 2022/10/19.
//

#ifndef OOM_CLASSROOM_DATA_TRANSFER_H
#define OOM_CLASSROOM_DATA_TRANSFER_H


#include <string>

void recv_data(int cli_sock, std::string &header, std::string &data);

void send_data(int cli_sock, const std::string &header, bool ok, const std::string &msg);

std::vector<std::string> split_string(const std::string& s);

#endif //OOM_CLASSROOM_DATA_TRANSFER_H
