#pragma once

#include "server.h"

void joinRoom() {
    server::makeConnection_c("127.0.0.1");
    return;
}

void createRoom() {
    server::makeConnection_s();
    return;
}