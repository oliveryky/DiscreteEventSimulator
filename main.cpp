#include <iostream>
#include "Event.h"
#include "EventQueue.h"
#include "SuperMarket.h"
#include "Bank.h"

/**
 * git clone git@github.com
 *
 * git diff origin/master
 * git pull change upstream branch
 */
/**
 * service time vs arrival time
 * contour is the 90th percentile
 */
int main(int argc, char* argv[]) {
    if(argc != 4) {
        perror("Wrong number of arguments");
        exit(1);
    }
    double arrivalRate = atof(argv[1]);
    double maxServiceTime = atof(argv[2]);
    int seed = atoi(argv[3]);
    
    //    double arrivalRate = 0;
    //    double maxServiceTime = 0;
    //    int seed = 34534;
    
    SuperMarket market(arrivalRate, maxServiceTime, seed);
    Bank bank (arrivalRate, maxServiceTime, seed);
    
    market.simulate();
    bank.simulate();
    
    return 0;
}
