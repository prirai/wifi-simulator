//
// Created by priyanshu on 11/28/24.
//

#include "Packet.h"

Packet::Packet(const int size) : packetSize(size), transmissionTime(0), latency(0) {
}



void Packet::calculateTransmissionTime(const int bandwidth, const double modulationRate, const double codingRate) {
    transmissionTime = static_cast<long>(std::ceil((8.0 * packetSize) / (bandwidth * modulationRate * codingRate)));
}

int Packet::getSize() const { return packetSize; }
long Packet::getTransmissionTime() const { return transmissionTime; }
void Packet::setLatency(const int latency) { this->latency = latency; }
int Packet::getLatency() const { return latency; }