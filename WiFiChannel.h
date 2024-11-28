//
// Created by priyanshu on 11/28/24.
//

#ifndef WIFICHANNEL_H
#define WIFICHANNEL_H

#include "Globals.h"
#include "Utils.h"

class WiFiChannel {
private:
    bool isBusy;
    long occupiedUntil;

public:
    int bandwidth;
    WiFiChannel(int bandwidth = 20);
    bool sniffChannel(long currentTime) const;
    void occupyChannel(long duration, long currentTime);
    void releaseChannel();
};

#endif //WIFICHANNEL_H
