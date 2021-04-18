#ifndef net_mgt_h
#define net_mgt_h

struct RawPacket{
    unsigned char status;

    unsigned int size;
    unsigned char data[];
};

#endif