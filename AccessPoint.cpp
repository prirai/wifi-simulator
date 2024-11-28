//
// Created by priyanshu on 11/28/24.
//

#include "AccessPoint.h"

AccessPoint::AccessPoint(int id, long max_concurrent_users) : id(id), currentTime(0), maxConcurrentUsers(max_concurrent_users) {
}

void AccessPoint::connectUser(User *user) {
    connectedUsers.push_back(user);
}

long AccessPoint::getCurrentTime() const { return currentTime; }

void AccessPoint::incrementTime() { currentTime += 1; }

void AccessPoint::addTime(long nano_sec) {
    currentTime += nano_sec;
}