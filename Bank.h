//
// Created by Oliver Yu on 2019-04-01.
//

#ifndef ASSIGNMENT16_BANK_H
#define ASSIGNMENT16_BANK_H

#include "Environment.h"

class Bank : public Environment {
public:
    Bank(double arrivalRate, double maxServiceTime, int seed) : Environment(arrivalRate, maxServiceTime, seed, 12, 6, 1) {}

    int getAvailableRegister() {
        for(int i = 0; i < registers.size(); ++i) {
            if(registers[i].isAvailable) {
                return i;
            }
        }

        return -1;
    }

    void simulate(){
        while(!allEvents.isEmpty() && time <= secondsToSimulate) {
            Event* curr = allEvents.deque();

            //makes sure time doesn't move backwards
            assert(time <= curr -> getExecutionTime());

            time = curr -> getExecutionTime();

            if(curr -> getEventType() == DEPARTURE) {
                totalServiceTime += curr -> getTimeWaited();
                eventTimes.push_back(curr->getTimeWaited() / (double) 60);
                int currRegister = curr -> getRegister();
                if(!lines[0].isEmpty()) {
                    registers[currRegister].isAvailable = false;

                    Event* nextEvent = lines[0].deque();
                    nextEvent -> updateRegister(currRegister);
                    nextEvent -> udpateEvent(DEPARTURE);
                    nextEvent -> updateExecutionTime(time + nextEvent -> getProcessingTime());
                    allEvents.enque(nextEvent);
                }else {
                    registers[currRegister].isAvailable = true;
                }
            }else if(curr -> getEventType() == ARRIVAL) {
                int availableRegister = getAvailableRegister();
                if(availableRegister > -1) {
                    registers[availableRegister].isAvailable = false;
                    curr -> updateRegister(availableRegister);
                    curr -> udpateEvent(DEPARTURE);
                    curr -> updateExecutionTime(time + curr -> getProcessingTime());
                    allEvents.enque(curr);
                }else {
                    lines[0].enque(curr);
                }
            }else {
                perror("Nice job");
                exit(1);
            }
        }

        printStats("Bank service times in minutes: ");
//        std::cout << "Total time: " << totalServiceTime << "\nAverage time: " << totalServiceTime / customersToEnque
//                  << std::endl;
    }
};
#endif //ASSIGNMENT16_BANK_H
