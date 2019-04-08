//
// Created by Oliver Yu on 2019-04-01.
//

#ifndef ASSIGNMENT16_MARKET_H
#define ASSIGNMENT16_MARKET_H

#include "Environment.h"

class SuperMarket : public Environment {
public:
    SuperMarket(double arrivalRate, double maxServiceTime, int seed) : Environment(arrivalRate, maxServiceTime, seed, 12, 6, 6) {}
    
    int getShortestLine() {
        int ret = 0, min = registers[0].timeRemaining + lines[0].getCurrentWaitTime();
        
        for (int i = 1; i < registers.size(); ++i) {
            int temp = registers[i].timeRemaining + lines[i].getCurrentWaitTime();
            if (temp < min) {
                ret = i;
                min = temp;
            }
        }
        
        return ret;
    }
    
    void handleDepartureEvent(Event *curr) {
        totalServiceTime += curr->getTimeWaited();
        eventTimes.push_back(curr->getTimeWaited() / (double) 60);
        int currLine = curr->getLine();
        int currRegister = curr->getRegister();
        if (!lines[currLine].isEmpty()) {
            Event *nextEvent = lines[currLine].deque();
            nextEvent->updateEvent(DEPARTURE, time + nextEvent->getProcessingTime());
            
            registers[currRegister].isAvailable = false;
            registers[currRegister].timeRemaining = nextEvent->getProcessingTime();
            
            allEvents.enque(nextEvent);
        } else {
            registers[currRegister].isAvailable = true;
        }
        //                updateRegisterRemainingTime(timeD);
    }
    
    void handleArrivalEvent(Event *curr) {
        //                updateRegisterRemainingTime(timeD);
        int lineToEnque = getShortestLine();
        curr->updateLine(lineToEnque);
        curr->updateRegister(lineToEnque);
        if (registers[lineToEnque].isAvailable) {
            registers[lineToEnque].isAvailable = false;
            registers[lineToEnque].timeRemaining = curr->getProcessingTime();
            
            curr->updateEvent(DEPARTURE, time + curr->getProcessingTime());
            
            allEvents.enque(curr);
        } else {
            lines[lineToEnque].enque(curr);
        }
    }
    
    //departure: after departing the guy enqueues first then updates time difference
    //arrival: update time difference before adding to shortest register
    void simulate() {
        while (!allEvents.isEmpty() && time <= secondsToSimulate) {
            Event *curr = allEvents.deque();
            assert(time <= curr->getExecutionTime());
            
            time = curr->getExecutionTime();
            
            if (curr->getEventType() == DEPARTURE) {
                handleDepartureEvent(curr);
            } else if (curr->getEventType() == ARRIVAL) {
                handleArrivalEvent(curr);
            } else {
                perror("Nice job");
                exit(1);
            }
        }
        
        printStats("Supermarket service times in minutes: ");
        //        std::cout << "Total time: " << totalServiceTime << "\nAverage time: " << totalServiceTime / customersToEnque
        //                  << std::endl;
    }
};

#endif //ASSIGNMENT16_MARKET_H
