//
// Created by Oliver Yu on 2019-03-31.
//

#ifndef ASSIGNMENT16_EVENTQUEUE_H
#define ASSIGNMENT16_EVENTQUEUE_H

#include <queue>
#include <vector>
#include "Event.h"

struct Comparator {
public:
    bool operator()(Event *lhs, Event *rhs) {
        return lhs->getExecutionTime() > rhs->getExecutionTime();
    }
};

class EventQueue {
private:
    int currentWaitTime;
    std::priority_queue<Event*, std::vector<Event*>, Comparator> eventQueue;
public:
    EventQueue() : currentWaitTime(0) {}
    
    void enque(Event *event) {
        currentWaitTime += event->getProcessingTime();
        eventQueue.push(event);
    }
    
    Event* deque() {
        if(eventQueue.empty()) {
            return nullptr;
        }
        
        Event *ret = eventQueue.top();
        eventQueue.pop();
        currentWaitTime -= ret->getProcessingTime();
        return ret;
    }
    
    int getCurrentWaitTime() {
        return currentWaitTime;
    }
    
    bool isEmpty() {
        return eventQueue.empty();
    }
};

#endif //ASSIGNMENT16_EVENTQUEUE_H
