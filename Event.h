//
// Created by Oliver Yu on 2019-03-30.
//

#ifndef ASSIGNMENT16_EVENT_H
#define ASSIGNMENT16_EVENT_H

enum EventType{DEPARTURE, ARRIVAL};

class Event {
private:
    int enqueTime, executionTime, lineNum, processingTime, registerNum;
    EventType eventType;
public:
    Event(int executionTime, int processingTime, EventType eventType) {
        this -> enqueTime = this -> executionTime = executionTime;
        this -> lineNum = this -> registerNum = 0;
        this->processingTime = processingTime;
        this -> eventType = eventType;
    }

    void updateExecutionTime(int time) {
        this -> executionTime = time;
    }

    void updateLine(int lineNum) {
        this -> lineNum = lineNum;
    }

    void updateRegister(int registerNum) {
        this -> registerNum = registerNum;
    }

    void udpateEvent(EventType eventType) {
        this -> eventType = eventType;
    }

    EventType getEventType() {
        return eventType;
    }

    int getExecutionTime() {
        return executionTime;
    }

    int getLine() {
        return lineNum;
    }

    int getProcessingTime() {
        return processingTime;
    }

    int getRegister() {
        return registerNum;
    }

    int getTimeWaited() {
        return executionTime - enqueTime;
    }
};
#endif //ASSIGNMENT16_EVENT_H
