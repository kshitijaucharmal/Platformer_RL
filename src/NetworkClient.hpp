//
// Created by kshitij on 10/9/25.
//
#pragma once

#include <string>

#include "Player.hpp"
#include "enet/enet.h"

class NetworkClient {
public:
    NetworkClient();

    void SendPacket(std::string data);

    // Representation of address of server
    ENetAddress address;
    // Receiving data for example
    ENetEvent event;
    // Connected to
    ENetPeer* peer;

    ENetHost* client;

    ENetPeer* ConnectToServerUI(Player* player);

    int ConnectToServer(std::string host, int port);

    int Disconnect();
};
