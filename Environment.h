//
// Created by Oliver Yu on 2019-03-31.
//

#ifndef ASSIGNMENT16_ENVIRONMENT_H
#define ASSIGNMENT16_ENVIRONMENT_H

#include "iomanip"
#include "iostream"
#include "string"
#include "EventQueue.h"

struct Register{
    bool isAvailable;
    int timeRemaining;
};

class Environment {
protected:
    int customersToEnque, maxServiceTime, secondsToSimulate, time, totalServiceTime;
    EventQueue allEvents;
    std::vector<Register> registers;
    std::vector<EventQueue> lines;
    std::vector<double> eventTimes;
public:
    Environment(double arrivalRate, double maxServiceTime, int seed, double hoursToSimulate, int regCount, int lineCount) {
        secondsToSimulate = hoursToSimulate * 3600;
        customersToEnque = arrivalRate * hoursToSimulate * 60;
        this -> maxServiceTime = maxServiceTime * 60;
        totalServiceTime = 0;

        srand(seed);

        for(int i = 0; i < regCount; ++i) {
            registers.push_back(Register {true, 0});
        }

        for(int i = 0; i < lineCount; ++i) {
            lines.push_back(EventQueue());
        }

        for(int i = 0; i < customersToEnque; ++i) {
            int arrivalTime = rand() % secondsToSimulate;
            int processingTime = this -> maxServiceTime == 0 ? 0 : (rand() % (int) this -> maxServiceTime) + 1;
            allEvents.enque(new Event(arrivalTime, processingTime, ARRIVAL));
        }

        time = 0;
    }

    void updateRegisterRemainingTime(int time) {
        for(Register reg: registers) {
            if(!reg.isAvailable) {
                reg.timeRemaining -= time;
//                assert(reg.timeRemaining >= 0);
            }
        }
    }

    void printStats(const std::string &msg) {
        std::sort(eventTimes.begin(), eventTimes.end());
        int percentCount = eventTimes.size() / 10;

        double tP = 0, nP = 0, fP = eventTimes.size() == 0 ? 0 : eventTimes[eventTimes.size()/2];

        for(int i = 0; i < percentCount; ++i) {
            tP += eventTimes[i];
            nP += eventTimes[eventTimes.size() - 1 - i];
        }

        if(eventTimes.size() > 0) {
            tP /= percentCount;
            nP /= percentCount;
        }

        std::cout << msg << std::setprecision(2) << std::fixed << "10th %tile: " << tP << ", 50th %tile: " << fP << ", 90th %tile: " << nP << std::endl;
    }

    virtual void simulate() {}
};
#endif //ASSIGNMENT16_ENVIRONMENT_H
