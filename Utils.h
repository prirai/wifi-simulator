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
    static void printError(std::stringstream errorMsg) {
        std::cout << "\033[1;31m" << errorMsg.str() << "\033[0m" << std::endl;
    }

    static void printInfo(std::stringstream infoMsg) {
        std::cout << "\033[1;34m" << infoMsg.str() << "\033[0m" << std::endl;
    }

    static void printWarning(std::stringstream warningMsg) {
        std::cout << "\033[1;33m" << warningMsg.str() << "\033[0m" << std::endl;
    }

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

long calcTotalTransmissionTime(int usersnum, int packetsize, int bandwidth, double modulationRate, double codingRate);
#endif // UTILS_H
