//
// Created by priyanshu on 11/28/24.
//

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>
#include "User.h"
#include "AccessPoint.h"
#include "Globals.h"
#include "WiFiAccessPoints.h"
#include <fstream>

class Simulator {
private:
    int numusers;
    std::vector<User*> users;
    double totalThroughput;
    std::vector<int> latencies;

public:
    AccessPoint* accessPoint;
    Simulator(int n);
    ~Simulator() = default;
    void initializeSimulation();
    void runSimulation(int duration);
    void computeMetrics();
};

#endif // SIMULATOR_H
