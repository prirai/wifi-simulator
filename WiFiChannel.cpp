//
// Created by priyanshu on 11/28/24.
//

#include "WiFiChannel.h"

WiFiChannel::WiFiChannel(int bandwidth) : isBusy(false), occupiedUntil(0), bandwidth(bandwidth) {
}

bool WiFiChannel::sniffChannel(long currentTime) const {
    if (currentTime < occupiedUntil) {
        return false;
    }
    return !isBusy;
}

void WiFiChannel::occupyChannel(long duration, long currentTime) {
    isBusy = true;

    debugstream << "[DEBUG] WiFiChannel: Occupying channel for " << duration << " microseconds." << std::endl;
    Utils::printDebug(std::move(debugstream));
    occupiedUntil = duration + currentTime;
}

void WiFiChannel::releaseChannel() {
    isBusy = false;
    debugstream << "[DEBUG] WiFiChannel: Channel released." << std::endl;
    Utils::printDebug(std::move(debugstream));
}

long WiFiChannel::getBandwidth() const {
    return bandwidth;
}
