//
// Created by priyanshu on 11/28/24.
//

#ifndef WIFI_ACCESS_POINTS_H
#define WIFI_ACCESS_POINTS_H

#include "AccessPoint.h"
#include "WiFiChannel.h"
#include "User.h"
#include <unordered_map>

class WiFi4AccessPoint : public AccessPoint {
private:
    WiFiChannel channel;

public:
    WiFi4AccessPoint(int id, long max_concurrent_users);

    bool transmitPacket(Packet* packet, User* user) override;
    long getBandwidth() override;
};

class WiFi5AccessPoint : public AccessPoint {
private:
    WiFiChannel channel;
    std::vector<User*> currentTransmittingUsers;
    std::vector<int> currentTransmittingUserIds;
    std::unordered_map<User*, long> userEndTimes;

public:
    WiFi5AccessPoint(int id, long max_concurrent_users);

    bool transmitPacket(Packet* packet, User* user) override;
    long getBandwidth() override;
};

class WiFi6AccessPoint : public AccessPoint {
private:
    WiFiChannel channel;
    std::vector<User*> currentTransmittingUsers;
    std::vector<int> currentTransmittingUserIds;
    std::unordered_map<User*, long> userEndTimes;

public:
    WiFi6AccessPoint(int id, long max_concurrent_users);

    bool transmitPacket(Packet* packet, User* user) override;
    long getBandwidth() override;
};

#endif // WIFI_ACCESS_POINTS_H
