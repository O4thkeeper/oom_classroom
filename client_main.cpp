//
// Created by 冯昊 on 2022/10/20.
//

#include "src/network/client.h"

int main(int argc, char *argv[]) {
    Client client;
    client.start(8001);
    return 0;
}
