#ifndef net_mgt_h
#define net_mgt_h

enum PACKET_STATUS {
    WAITING,
    SENDING,
    SENT
}

struct RawPacket {
    PACKET_STATUS status;

    unsigned int size;
    unsigned char data[];
};

#endif