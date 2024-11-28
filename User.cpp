//
// Created by priyanshu on 11/28/24.
//

#include "User.h"

User::User(int id) : id(id), backoffTime(0), generator(std::chrono::system_clock::now().time_since_epoch().count()) {
}

void User::generatePackets(int num) {
    remainingPackets = num;
    for (int i = 0; i < num; ++i) {
        packetsToSend.push(new Packet());
    }
}

void User::attemptTransmission(AccessPoint *ap, int currentTime) {
    if (!packetsToSend.empty()) {
        if (backoffTime > 0) {
            backoffTime--;
            return;
        }

        Packet *packet = packetsToSend.front();
        if (ap->transmitPacket(packet, this)) {
            debugstream << "Current time = " << currentTime << ", trtime = " << packet->getTransmissionTime() <<
                    std::endl;
            long trtime = packet->getTransmissionTime();
            packet->setLatency(currentTime + packet->getTransmissionTime() - packet->getStartTime());
            latency = packet->getLatency();
            debugstream << "[DEBUG] User " << id << ": Packet transmitted successfully. Latency = " << latency <<
                    " microseconds." << std::endl;
            packetsToSend.pop();
            packetsToSend.front()->setStartTime(currentTime + trtime);
            // users_remaining--;
        } else {
            distribution = std::uniform_int_distribution<int>(0, std::pow(2, std::min(10, backoffTime + 1)) - 1);
            packet->calculateTransmissionTime(20, log2(256), 5.0 / 6.0);
            long max_backoff_time = packet->getTransmissionTime() / 2;
            distribution = std::uniform_int_distribution<int>(0, max_backoff_time);
            backoffTime = distribution(generator);
            debugstream << "[DEBUG] User " << id << ": Collision detected. New backoff time = " << backoffTime << "." <<
                    std::endl;
        }
        Utils::printDebug(std::move(debugstream));
    }
}

int User::getId() { return id; }
int User::getBackoffTime() const { return backoffTime; }
int User::getLatency() { return latency; }
