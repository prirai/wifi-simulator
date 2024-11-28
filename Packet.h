//
// Created by priyanshu on 11/28/24.
//

#ifndef PACKET_H
#define PACKET_H

#include <iostream>
#include <cmath>

class Packet {
private:
    int packetSize;
    long starttime{0};
    long transmissionTime;
    double latency;

public:
    Packet(int size = 1024);
    void calculateTransmissionTime(int bandwidth, double modulationRate, double codingRate);
    int getSize() const;
    long getTransmissionTime() const;
    long getStartTime() { return starttime; }
    void setStartTime(long st_time) { starttime = st_time; }
    void setLatency(int latency);
    int getLatency() const;
};

#endif //PACKET_H
