//
// Created by priyanshu on 11/28/24.
//

#include "Utils.h"

bool isDebug = true;

long calcTotalTransmissionTime(int usersnum, int packetsize, int bandwidth, double modulationRate, double codingRate) {
    return static_cast<long>(
        std::ceil((usersnum * 8.0 * packetsize) / (bandwidth * modulationRate * codingRate)));
}