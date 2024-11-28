//
// Created by priyanshu on 11/28/24.
//

#include "WiFiAccessPoints.h"

WiFi4AccessPoint::WiFi4AccessPoint(int id, long max_concurrent_users) : AccessPoint(id, max_concurrent_users),
                                                                        channel(20) {
}

bool WiFi4AccessPoint::transmitPacket(Packet *packet, User *user) {
    debugstream << "[DEBUG] WiFi4AccessPoint: Attempting to transmit packet for User " << user->getId() << " at " <<
            currentTime << "." << std::endl;
    if (channel.sniffChannel(currentTime)) {
        debugstream << "[DEBUG] WiFi4AccessPoint: Channel is free. Proceeding with transmission." << std::endl;
        packet->calculateTransmissionTime(channel.bandwidth, log2(256), 5.0 / 6.0);
        channel.occupyChannel(packet->getTransmissionTime(), currentTime);
        channel.releaseChannel();
        Utils::printDebug(std::move(debugstream));
        user->remainingPackets--;
        debugstream << "[DEBUG] User " << user->getId() << " has " << user->remainingPackets << " remaining packets." <<
                std::endl;
        return true;
    }
    Utils::printDebug(std::move(debugstream));
    return false;
}

WiFi5AccessPoint::WiFi5AccessPoint(int id, long max_concurrent_users) : AccessPoint(id, max_concurrent_users),
                                                                        channel(20) {
}

bool WiFi5AccessPoint::transmitPacket(Packet *packet, User *user) {
    debugstream << "[DEBUG] WiFi5AccessPoint: Attempting to transmit packet for User " << user->getId() << " at "
            << currentTime << "." << std::endl;

    for (auto it = userEndTimes.begin(); it != userEndTimes.end();) {
        if (it->second <= currentTime) {
            debugstream << "User " << it->first->getId() << " has " << it->first->remainingPackets <<
                    " remaining packets and is done transmitting." << std::endl;

            auto userIt = std::ranges::find(currentTransmittingUsers, it->first);
            if (userIt != currentTransmittingUsers.end()) {
                currentTransmittingUsers.erase(userIt);
            }

            auto userIdIt = std::ranges::find(currentTransmittingUserIds, it->first->getId());
            if (userIdIt != currentTransmittingUserIds.end()) {
                currentTransmittingUserIds.erase(userIdIt);
                std::cout << "User with ID " << *userIdIt << " removed at time " << currentTime << std::endl;
            }

            it = userEndTimes.erase(it);
        } else {
            ++it;
        }
    }

    if (std::ranges::find(currentTransmittingUserIds, user->getId()) != currentTransmittingUserIds.end()) {
        debugstream << "[DEBUG] WiFi5AccessPoint: User " << user->getId() << " is already transmitting." << std::endl;
        Utils::printDebug(std::move(debugstream));
        return false;
    }
    if (currentTransmittingUsers.size() < maxConcurrentUsers) {
        debugstream << "[DEBUG] WiFi5AccessPoint: Channel has space. Proceeding with transmission." << std::endl;
        packet->calculateTransmissionTime(channel.bandwidth, log2(1024), 5.0 / 6.0);
        currentTransmittingUsers.push_back(user);
        currentTransmittingUserIds.push_back(user->getId());
        userEndTimes[user] = currentTime + packet->getTransmissionTime();

        for (auto i: userEndTimes) {
            std::cout << "User " << i.first->getId() << " | end time: " << i.second << std::endl;
        }
        std::cout << "-----" << std::endl;
        user->remainingPackets--;
        Utils::printDebug(std::move(debugstream));
    } else {
        debugstream << "[DEBUG] WiFi5AccessPoint: Channel busy. Cannot transmit at this time." << std::endl;
        Utils::printDebug(std::move(debugstream));
        return false;
    }

    return true;
}

//
// void WiFi5AccessPoint::releaseCompletedUsers(long currentTime) {
//     currentTransmittingUsers.erase(
//         std::remove_if(
//             currentTransmittingUsers.begin(),
//             currentTransmittingUsers.end(),
//             [&](User *user) {
//                 if (userEndTimes[user] <= currentTime) {
//                     userEndTimes.erase(user);
//                     return true;
//                 }
//                 return false;
//             }),
//         currentTransmittingUsers.end());
// }

WiFi6AccessPoint::WiFi6AccessPoint(int id, long max_concurrent_users) : AccessPoint(id, max_concurrent_users),
                                                                        channel(2) {
    infostream << "Created " << std::to_string(20 / channel.bandwidth) << " bands of " <<
            std::to_string(channel.bandwidth) << " MHz each." << std::endl;
    Utils::printInfo(std::move(infostream));
}

bool WiFi6AccessPoint::transmitPacket(Packet *packet, User *user) {
    debugstream << "[DEBUG] WiFi6AccessPoint: Attempting to transmit packet for User " << user->getId() << " at "
            << currentTime << "." << std::endl;

    for (auto it = userEndTimes.begin(); it != userEndTimes.end();) {
        if (it->second <= currentTime) {
            debugstream << "User " << it->first->getId() << " has " << it->first->remainingPackets <<
                    " remaining packets and is done transmitting." << std::endl;

            auto userIt = std::ranges::find(currentTransmittingUsers, it->first);
            if (userIt != currentTransmittingUsers.end()) {
                currentTransmittingUsers.erase(userIt);
            }

            auto userIdIt = std::ranges::find(currentTransmittingUserIds, it->first->getId());
            if (userIdIt != currentTransmittingUserIds.end()) {
                currentTransmittingUserIds.erase(userIdIt);
                std::cout << "User with ID " << *userIdIt << " removed at time " << currentTime << std::endl;
            }

            it = userEndTimes.erase(it);
        } else {
            ++it;
        }
    }

    if (std::ranges::find(currentTransmittingUserIds, user->getId()) != currentTransmittingUserIds.end()) {
        debugstream << "[DEBUG] WiFi5AccessPoint: User " << user->getId() << " is already transmitting." << std::endl;
        Utils::printDebug(std::move(debugstream));
        return false;
    }
    if (currentTransmittingUsers.size() < maxConcurrentUsers) {
        debugstream << "[DEBUG] WiFi6AccessPoint: Channel has space. Proceeding with transmission." << std::endl;
        packet->calculateTransmissionTime(channel.bandwidth, log2(2048), 5.0 / 6.0);
        currentTransmittingUsers.push_back(user);
        currentTransmittingUserIds.push_back(user->getId());
        userEndTimes[user] = currentTime + packet->getTransmissionTime();

        user->remainingPackets--;
        Utils::printDebug(std::move(debugstream));
    } else {
        debugstream << "[DEBUG] WiFi6AccessPoint: Channel busy. Cannot transmit at this time." << std::endl;
        Utils::printDebug(std::move(debugstream));
        return false;
    }

    return true;
}
