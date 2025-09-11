#include <iostream>
#include <enet/enet.h>
#include <string>
#include <sstream>

#define PORT 1234
void SendPacket(ENetPeer* peer, std::string data){
    ENetPacket* packet = enet_packet_create(data.data(), data.size(), ENET_PACKET_FLAG_RELIABLE);
    // Channel 0
    enet_peer_send(peer, 0, packet);
}

void ParseData(ENetHost* server, int id, const char* data) {
    std::stringstream ss(data);
    std::string token;

    // Get data_type (first field)
    if (!std::getline(ss, token, '|')) return;
    int data_type = std::stoi(token);

    std::string username;
    std::string extra;

    switch (data_type) {
        case 1: {
            // 1|username
            if (std::getline(ss, username)) {
                std::cout << username << " Registered." << std::endl;
            }
            break;
        }
        case 2: {
            // 2|username|ready
            if (std::getline(ss, username, '|') && std::getline(ss, extra)) {
                // extra is ready (string, can be "0", "1", or anything else)
                std::cout << username << " ready:" << extra << std::endl;
            }
            break;
        }
        case 3: {
            // 3|username|player_dat
            if (std::getline(ss, username, '|') && std::getline(ss, extra)) {
                std::string player_dat = extra;
                std::cout << username << player_dat << std::endl;
            }
            break;
        }
        case 4: {
            // 4|username
            if (std::getline(ss, username)) {
                std::cout << username << " Disconnected." << std::endl;
            }
            break;
        }
        default: break;
    }
}

int main(int argc, char ** argv){
    if(enet_initialize() != 0){
        fprintf(stderr, "Error initialising Enet\n");
        return EXIT_FAILURE;
    }
    // At Exit, de init
    atexit(enet_deinitialize);

    // Representation of address of host
    ENetAddress address;
    // Receiving data for example
    ENetEvent event;
    // Server object
    ENetHost* server;

    // Can connect from anywhere, MACRO for 0
    address.host = ENET_HOST_ANY;
    address.port = PORT;

    // Player limit, channels, bw limit (0 -> unlimited)
    server = enet_host_create(&address, 32, 1, 0, 0);

    if(server == nullptr){
        fprintf(stderr, "Error creating server\n");
        return EXIT_FAILURE;
    }

    // Game loop START

    while(true){
        while(enet_host_service(server, &event, 1000) > 0){
            switch (event.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
                printf("New Client Connected %x:%u\n",
                    event.peer->address.host,
                    event.peer->address.port
                 );
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                // printf("%s\n", event.packet->data);

                ParseData(server, -1, reinterpret_cast<char *>(event.packet->data));
                enet_packet_destroy(event.packet);

                // SendPacket(event.peer, "Received - ACK");
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                printf("%x:%u disconnected.\n",
                    event.peer->address.host,
                    event.peer->address.port
                 );

                // If sending data, set it to null
                event.peer->data = nullptr;
                break;
            
            default:
                break;
            }
        }
    }
    
    // Game loop END

    enet_host_destroy(server);

    return EXIT_SUCCESS;
}