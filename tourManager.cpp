/* ----------------------------
 * Student Dev: Martin Kadzis
 * Date: October 30th, 2020
 * Class: COP4534, John Coffey
 * ----------------------------
 */

#include <string>
#include <vector>
#include <cmath>
#include <math.h>

#include <iostream>
#include <iomanip>
#include <fstream>

#include "tourManager.hpp"
#include "permutation.hpp"

void TourManager::loadMatrix(){

    std::ifstream file;
    file.open("distances.txt");

    for(int i = 0; i < this->MAX; i++){
        for(int j = 0; j < this->MAX; j++){

            if(i == j){
              this->distance[i][j] = 0.0;
            } else {
                file >> this->distance[i][j];
            }
        }
    }

    file.close();
}

TourManager::TourManager(int nCities, int nTours, int nGens, double nPercent){
    this->numberOfCities = nCities;
    this->numberOfTours = nTours;
    this->numberOfGenToRun = nGens;
    this->percentOfMutation = nPercent;

    this->optimalCost = 0.0;
    loadMatrix();
    srand((int)time(0));

    std::cout << "\n";
    std::cout << nCities << " CITIES | " << nTours << " TOURS | ";
    std::cout << nGens << " GENS | " << nPercent << " %MUTATE" << std::endl;
}

void TourManager::bruteForce(){

    Permutation p(this->numberOfCities);
    long int cities = (long int)this->numberOfCities;
    long int total = p.factorial(cities);
    double bestTourCost = 0.0;

    time_t start = time((time_t*)0);
    for(long int perm = 0; perm < total; ++perm){
        int* permSet = p.getSet();
        double tourCost = this->distance[0][permSet[0]];

        for (int i = 0; i < this->numberOfCities; ++i){
            int row = permSet[i];
            int col = permSet[i + 1];
            tourCost += this->distance[row][col];
        }

        if(bestTourCost == 0){
            bestTourCost = tourCost;
            p.perm1();
            continue;
        }
        
        if(tourCost < bestTourCost)
            bestTourCost = tourCost;
        
        if(perm == total - 1)
            break;

        p.perm1();
    }
    std::cout << std::endl;

    time_t end = time((time_t*)0);
    double elapsedTime = difftime(end, start);
    double elapsedMins = elapsedTime / 60.0;

    std::cout << "| Brute Force | Best Tour:" << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "  Optimal Cost: " << bestTourCost << std::endl;

    std::cout << "\n  Elapsed Time: ";
    std::cout << std::setprecision(2) << std::fixed;
    if(elapsedMins < 1.0){
        std::cout << elapsedTime << " seconds" << std::endl;
    } else {
        std::cout << elapsedMins << " minutes" << std::endl;
    }
 
    this->optimalCost = bestTourCost;
}

void TourManager::geneticAlg(){
    std::vector<int*> bestRouts;
    std::vector<double> bestCosts;

    struct timespec start, stop;
    clock_gettime(CLOCK_REALTIME, &start);
    
    for (int genCounter = 0; genCounter < numberOfGenToRun; ++genCounter){
        std::vector<int*> generation;
        
        //generate mutated permutations
        if(genCounter > 0){
            int numberOfMutations = this->numberOfTours * this->percentOfMutation;
            for (int i = 0; i < numberOfMutations; ++i){
                int random = (rand() % bestRouts.size());
                int* mutatedPermutation = mutate(bestRouts.at(random));
                generation.push_back(mutatedPermutation);
            }
        }
        
        //generate random permutations
        int numberOfRandoms = this->numberOfTours - generation.size();
        for(int i = 0; i < numberOfRandoms; ++i){
            int* randomPermutation = permRand();
            generation.push_back(randomPermutation);
        }
 
        //calculate this generations fittest 
        while(generation.size() != 0){
            int* permSet = generation.at(0);
            generation.erase(generation.begin());

            double tourCost = this->distance[0][permSet[0]];
            for(int i = 0; i < this->numberOfCities; ++i){
                int row = permSet[i];
                int col = permSet[i + 1];
                tourCost += this->distance[row][col];
            }

            if(bestCosts.size() < 2){
                bestCosts.push_back(tourCost);
                bestRouts.push_back(permSet);
                continue;
            }

            if(tourCost < bestCosts.at(0) && tourCost < bestCosts.at(1)){
                if(bestCosts.at(0) < bestCosts.at(1)){
                    bestCosts.at(1) = tourCost;
                    delete[] bestRouts.at(1);
                    bestRouts.at(1) = permSet;
                } else {
                    bestCosts.at(0) = tourCost;
                    delete[] bestRouts.at(0);
                    bestRouts.at(0) = permSet;
                }
                continue;
            }

            if(tourCost < bestCosts.at(0) && tourCost > bestCosts.at(1)){
                bestCosts.at(0) = tourCost;
                delete[] bestRouts.at(0);
                bestRouts.at(0) = permSet;
                continue;
            }

            if(tourCost > bestCosts.at(0) && tourCost < bestCosts.at(1)){
                bestCosts.at(1) = tourCost;
                delete[] bestRouts.at(1);
                bestRouts.at(1) = permSet;
                continue;
            }
            delete[] permSet;  
        }
 
        generation.clear();
    }
    
    clock_gettime(CLOCK_REALTIME, &stop);
    timespec elapsed = getElapsed(start, stop);
    double timeInSeconds = elapsed.tv_nsec / 1000000000.0;

    //print results
    std::cout << "\n| Genetic Alg | Best Tours:" << std::endl;
    std::cout << "---------------------------" << std::endl;
    std::cout << "  Elite Cost 1: " << bestCosts.at(0) << std::endl;
    std::cout << "  Elite Cost 2: " << bestCosts.at(1) << std::endl;

    std::cout << "\n  Elapsed Time: ";
    std::cout << std::setprecision(2) << std::fixed;
    std::cout << timeInSeconds << " seconds" << std::endl;

    std::cout << "\n---------------------------" << std::endl;
    
    double numerator = abs(this->optimalCost - bestCosts.at(0));
    double denominator = (this->optimalCost + bestCosts.at(0)); 
    double percent1 = (numerator/denominator) * 200 + 100;
    numerator = abs(this->optimalCost - bestCosts.at(1));
    denominator = (this->optimalCost + bestCosts.at(1));
    double percent2 = (numerator/denominator) * 200 + 100;
    
    std::cout << "Percent Optimal 1 = " << percent1 << std::endl;
    std::cout << "Percent Optimal 2 = " << percent2 << std::endl;
    
    //deallocate pointers
}

int* TourManager::permRand() {
    std::vector<int> numberBank(this->numberOfCities);
    for (int i = 0; i < this->numberOfCities; ++i)
        numberBank[i] = i + 1;

    int* randomPermutation = new int[this->MAX]();

    int index = 0;
    while(numberBank.size() != 0){
        int randi = (rand() % numberBank.size());
        int tempNum = numberBank.at(randi);
        numberBank.erase(numberBank.begin() + randi);
        
        randomPermutation[index] = tempNum;
        index++;
    }

    randomPermutation[this->numberOfCities] = 0;     
    return randomPermutation;
}

int* TourManager::mutate(int* elite){

    int index1 = (rand() % this->numberOfCities);
    int index2;
    do {
       index2 = (rand() % this->numberOfCities); 
    } while (index2 == index1);
   
    int* newMutate = new int[this->MAX]();
    for(int i = 0; i < this->numberOfCities; ++i)
        newMutate[i] = elite[i];
    newMutate[this->numberOfCities] = 0;

    int tempIndex1 = newMutate[index1];
    newMutate[index1] = newMutate[index2];
    newMutate[index2] = tempIndex1;
    return newMutate;
}

void TourManager::printElite(int* elite){
    for(int i = 0; i < this->numberOfCities; ++i)
        std::cout << elite[i] << " "; 
}

timespec TourManager::getElapsed(timespec start, timespec stop){
    timespec elapsed;
    int nano = 1000000000;

    if((stop.tv_nsec - start.tv_nsec) < 0){
        elapsed.tv_sec = stop.tv_sec - start.tv_sec - 1;
        elapsed.tv_nsec = nano + (stop.tv_nsec - start.tv_nsec);
    } else {
        elapsed.tv_sec = stop.tv_sec - start.tv_sec;
        elapsed.tv_nsec = stop.tv_nsec - start.tv_nsec;
    }
    return elapsed;
}
