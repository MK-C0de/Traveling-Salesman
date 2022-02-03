/* ----------------------------
 * Student Dev: Martin Kadzis
 * Date: October 30th, 2020
 * Class: COP4534, John Coffey
 * ----------------------------
 */

#ifndef TOURMANAGER_HPP
#define TOURMANAGER_HPP

#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

class TourManager {

    private:
        static const int MAX = 20;

        int numberOfCities;
        int numberOfTours;
        int numberOfGenToRun;
        double percentOfMutation;

        double optimalCost;

        double distance[MAX][MAX];
        void loadMatrix();

    public:
        TourManager(int, int, int, double);

        void bruteForce();
        void geneticAlg();

        int* permRand();
        int* mutate(int*);
        void printElite(int*);

        timespec getElapsed(timespec, timespec);
};

#endif
