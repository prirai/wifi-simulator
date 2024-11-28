//
// Created by priyanshu on 11/28/24.
//

#include "Simulator.h"

Simulator::Simulator(int n) : numusers(n), accessPoint(nullptr), totalThroughput(0) {
}

void Simulator::initializeSimulation() {
    if (ap_standard == 4) {
        accessPoint = new WiFi4AccessPoint(0, 1);
    } else if (ap_standard == 5) {
        accessPoint = new WiFi5AccessPoint(0, 10);
    } else if (ap_standard == 6) {
        accessPoint = new WiFi6AccessPoint(0, 10);
    } else {
        throw std::invalid_argument("Invalid Access Point type specified");
    }

    for (int i = 0; i < numusers; ++i) {
        auto user = new User(i);
        users.push_back(user);
        accessPoint->connectUser(user);
        user->generatePackets(maxPackets);
    }
}

void Simulator::runSimulation(int duration) {
    debugstream << "[DEBUG] Simulator: Starting simulation for " << duration << " microseconds." << std::endl;
    Utils::printDebug(std::move(debugstream));
    long csi_trtime = calcTotalTransmissionTime(numusers, 200, accessPoint->getBandwidth(), log2(256), 5.0 / 6.0);

    for (int currtime = 0; currtime < duration && users_remaining > 0; ++currtime) {
        if (ap_standard == 5) {
            if (currtime % (15000 + csi_trtime) == 0) {
                std::cout << "Touched CSI time: " << csi_trtime << std::endl;
                currtime += csi_trtime;
                accessPoint->addTime(csi_trtime);
            }
        }
        for (User *user: users) {
            user->attemptTransmission(accessPoint, currtime);
        }
        accessPoint->incrementTime();
    }
}

void Simulator::computeMetrics() {
    debugstream << "[DEBUG] Simulator: Computing metrics." << std::endl;
    long totalLatency = 0;
    // int successfulTransmissions = 0;

    long max_latency = 0;
    long total_packets_transferred = 0;

    for (User *user: users) {
        long user_latency = user->getLatency();
        totalLatency += user_latency;
        total_packets_transferred += (maxPackets - user->remainingPackets);
        if (user_latency > max_latency)
            max_latency = user_latency;
    }

    std::cout << std::min(accessPoint->getMaxConcurrentUsers(), static_cast<long>(numusers)) << std::endl;

    long totalTime = accessPoint->getCurrentTime() +
                     calcTotalTransmissionTime(numusers/ std::min(accessPoint->getMaxConcurrentUsers(), static_cast<long>(numusers)), 1024, accessPoint->getBandwidth(), log2(256), 5.0 / 6.0);

    totalThroughput = (total_packets_transferred * 1024) / (totalTime / 1e6);

    std::stringstream infostream;
    double averageLatency = total_packets_transferred > 0 ? totalLatency * 1.0 / numusers : 0;

    Utils::printDebug(std::move(debugstream));

    std::ofstream logfile("log.txt", std::ios_base::app);

    if (!logfile.is_open()) {
        logfile.open("log.txt", std::ios_base::out);
        if (!logfile.is_open()) {
            std::cerr << "Failed to create log file." << std::endl;
            return;
        }
        std::cerr << "Failed to open log file." << std::endl;
    }
    infostream << "WiFi" << ap_standard << std::endl;
    infostream << "Concurrent Users: " << std::min(accessPoint->getMaxConcurrentUsers(), static_cast<long>(numusers)) << std::endl;
    infostream << "User count: " << numusers << std::endl;
    infostream << "Total packets transferred: " << total_packets_transferred << std::endl;
    infostream << "Throughput = " << totalThroughput << " bytes per sec" << std::endl;
    infostream << "Average Latency = " << averageLatency << " microseconds." << std::endl;
    infostream << "Max Latency = " << max_latency << " microseconds." << std::endl;

    std::stringstream infostreamCopy;
    infostreamCopy << infostream.rdbuf();
    logfile << infostreamCopy.rdbuf();
    Utils::printInfo(std::move(infostream));

    logfile.close();
}
