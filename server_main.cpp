#include "src/network/server.h"

int main(int argc, char *argv[]) {
    Server server;
    server.start(8001);
    return 0;
}
