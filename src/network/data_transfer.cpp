//
// Created by 冯昊 on 2022/10/19.
//

#include <sys/socket.h>
#include <vector>
#include <sstream>
#include "data_transfer.h"
#include "data_template.h"

using std::string;

void recv_data(int cli_sock, string &header, string &data) {
    int data_recv;
    char temp_header[BUF_SIZE + 1];
    data_recv = recv(cli_sock, temp_header, BUF_SIZE, 0);
    if (data_recv < 0) {
        perror("recv() failed");
    }
    temp_header[data_recv] = '\0';

    header = temp_header;
    std::vector<string> strings_list = split_string(header);

    char temp_buffer[BUF_SIZE + 1];
    data = "";

    string buffer;
    int data_to_recv = atoi(strings_list[2].c_str());
    while ((data_to_recv > 0) && ((data_recv = recv(cli_sock, temp_buffer, BUF_SIZE, 0)) > 0)) {
        if (data_recv < 0) {
            perror("recv() failed");
        }
        temp_buffer[data_recv] = '\0';
        buffer = temp_buffer;
        data += buffer;
        data_to_recv -= data_recv;
    }
}

void send_data(int cli_sock, const string &header, bool ok, const string &msg) {
    string code;
    if (ok) {
        code = "OK";
    } else {
        code = "NOK";
    }
    string len = std::to_string(msg.length());
    string resp = header + SPLITTER + code + SPLITTER + len;
    if (send(cli_sock, resp.c_str(), BUF_SIZE, 0) < 0) {
        perror("send() failed");
    }
    int data_sent;
    if ((data_sent = send((cli_sock), msg.c_str(), stoi(len), 0)) != stoi(len)) {
        perror("send() failed");
        exit(1); // Replace this with fail message
        // fail_msg();
    }
}

std::vector<string> split_string(const string& s) {
    std::stringstream ss(s);
    string parse;
    std::vector<string> v;
    while (getline(ss, parse, SPLITTER)) {
        v.push_back(parse);
    }
    return v;
}