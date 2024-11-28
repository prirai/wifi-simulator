//
// Created by priyanshu on 11/28/24.
//

#ifndef USER_H
#define USER_H

#include <queue>
#include <random>
#include <chrono>
#include "Packet.h"
#include "AccessPoint.h"
#include "Globals.h"
#include "Utils.h"

class User {
private:
    int id;
    std::queue<Packet*> packetsToSend;
    int backoffTime;
    long latency;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution;

public:
    long remainingPackets;

    User(int id);
    int getId();
    void generatePackets(int num);
    void attemptTransmission(AccessPoint* ap, int currentTime);
    int getBackoffTime() const;
    int getLatency();
};

#endif // USER_H
