#include <iostream>
#include "main.h"

#include "Globals.h"
#include "Utils.h"
#include "AccessPoint.h"
#include "Simulator.h"

int main() {
    //if (argc == 1) {
//        std::cout << "No args passed. Running default simulations." << std::endl;
//    }

    int userCounts[] = {1, 10, 100};
    int accessPointTypes[] = {4, 5, 6};

    for (const int &apType: accessPointTypes) {
        Utils::printWiFi(apType);
        for (int n: userCounts) {
            std::cout << "Up next: WiFi" << apType << " with " << n << " users." << std::endl;
            std::cout << "Press Enter to continue..." << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();

            users_remaining = n;

            AccessPoint *ap = nullptr;
            ap_standard = apType;

            Simulator<User, AccessPoint> simulator(n);
            if (n > 10) isDebug = false;
            else isDebug = true;

            std::cout << "Running simulation for WiFi" << apType << " with " << n << " users." << std::endl;
            simulator.initializeSimulation();
            simulator.runSimulation(100000);
            simulator.computeMetrics();
            delete ap;

            std::cout << "Simulation completed for WiFi" << apType << " with " << n << " users." << std::endl;

            std::cout << std::endl;
        }
    }

    return 0;
}
