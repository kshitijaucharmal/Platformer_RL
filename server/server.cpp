#include <iostream>
#include <enet/enet.h>
#include <string>

#define PORT 1234
void SendPacket(ENetPeer* peer, std::string data){
    ENetPacket* packet = enet_packet_create(data.data(), data.size(), ENET_PACKET_FLAG_RELIABLE);
    // Channel 0
    enet_peer_send(peer, 0, packet);
}

void ParseData(ENetHost* server, int id, char * data){
    std::cout << "Parse: " << data << "\n";

    int data_type;
    sscanf(data, "%d|", &data_type);

    switch (data_type)
    {
    case 1:
        /* code */
        break;
    case 2:
        // TODO: C code, convert to cpp
        char username[80];
        sscanf(data, "2|%[^\n]", &username);

        char send_data[1024] = {'\0'};
        sprintf(send_data, "2|%d|%s", id, username);

        std::cout << "Send: " << send_data << std::endl;
        break;
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
                // printf ("A packet of length %u containing %s was received from %x:%u on channel %u.\n",
                //     event.packet -> dataLength,
                //     event.packet -> data,
                //     event.peer -> address.host,
                //     event.peer -> address.port,
                //     event.channelID);

                printf("%s\n", event.packet->data);

                // ParseData(server, -1, (char*)event.packet->data);
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