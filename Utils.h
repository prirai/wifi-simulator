//
// Created by priyanshu on 11/28/24.
//

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <sstream>
#include <cmath>

extern bool isDebug;

class Utils {
public:
    /**
     * Prints an error message to the console
     * @param errorMsg the stringstream containing the error message
     */
    static void printError(std::stringstream errorMsg) {
        std::cout << "\033[1;31m" << errorMsg.str() << "\033[0m" << std::endl;
    }

    /**
     * Prints an info message to the console
     * @param infoMsg the stringstream containing the message
     */
    static void printInfo(std::stringstream infoMsg) {
        std::cout << "\033[1;34m" << infoMsg.str() << "\033[0m" << std::endl;
    }

    /**
     * Prints a warning message to the console
     * @param warningMsg the stringstream containing the message
     */
    /**
     * Prints a warning message to the console
     * @param warningMsg the stringstream containing the message
     */
    static void printWarning(std::stringstream warningMsg) {
        std::cout << "\033[1;33m" << warningMsg.str() << "\033[0m" << std::endl;
    }

    /**
     * Prints a debug message to the console if the global debug flag is set.
     * @param debugMsg the stringstream containing the message
     */
    static void printDebug(std::stringstream debugMsg) {
        if (isDebug)
            std::cout << "\033[0;37m" << debugMsg.str() << "\033[0m";
    }

    static void printWiFi(int standard_num) {
        std::cout << R"(
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
▓▓▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒▓▒▒▒▒▓▓▓▓▓▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▒▒▓▓▓▓▒▒
▓▓▓▒▒▒▓▓▒▒▒▒▓▓▒▒▒▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▒▒▒▓▓▓▓▓▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▒▒▒▓▓▓▒▒▒
▓▓▓▓▒▒▒▒▒▓▓▒▒▒▒▒▓▓▓▓▒▒▒▓▓▓▓▓▒▒▒▒▒▓▓▓▓▒▒▒▒▒▒▒▒▒▓▓▓▒▒▒
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒)" << standard_num << std::endl;
    }
};

/**
 * Calculates the total transmission time for all users in the network.
 * @param usersnum the number of users
 * @param packetsize the size of each packet
 * @param bandwidth the bandwidth of the network
 * @param modulationRate the modulation rate of the network
 * @param codingRate the coding rate of the network
 * @return the total transmission time for all users in the network
 */
long calcTotalTransmissionTime(int usersnum, int packetsize, int bandwidth, double modulationRate, double codingRate) {
    return static_cast<long>(
        std::ceil((usersnum * 8.0 * packetsize) / (bandwidth * modulationRate * codingRate)));
}
#endif // UTILS_H
