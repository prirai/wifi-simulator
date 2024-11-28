//
// Created by priyanshu on 11/28/24.
//

#ifndef ACCESS_POINT_H
#define ACCESS_POINT_H

#include <vector>
#include "Packet.h"

class User;

class AccessPoint {
protected:
    int id;
    std::vector<User*> connectedUsers;
    long currentTime;
    long maxConcurrentUsers;

public:
    AccessPoint(int id, long max_concurrent_users);
    virtual ~AccessPoint() = default;

    void connectUser(User* user);
    [[nodiscard]] long getCurrentTime() const;
    void incrementTime();
    void addTime(long nano_sec);

    virtual bool transmitPacket(Packet* packet, User* user) = 0; // Pure virtual
    // virtual void releaseCompletedUsers(long currentTime) = 0;
    virtual long getBandwidth() = 0;
    [[nodiscard]] long getMaxConcurrentUsers() const {
        return maxConcurrentUsers;
    }
};

#endif // ACCESS_POINT_H
