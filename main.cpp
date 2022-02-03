/* ----------------------------
 * Student Dev: Martin Kadzis
 * Date: October 30th, 2020
 * Class: COP4534, John Coffey
 * ----------------------------
 */

#include <iostream>

#include "tourManager.hpp"

int main (){
    
    int nCities, nTours, nGens, nPercent;

    std::cout << "\nEnter the number of cities to run: ";
    std::cin >> nCities;
    
    std::cout << "\nEnter the number of tours in a given generation: ";
    std::cin >> nTours;

    std::cout << "\nEnter the number of generations to run: ";
    std::cin >> nGens;

    std::cout << "\nEnter the percentage of mutation in a generation: ";
    std::cin >> nPercent;

    std::cout << "\n";

    //Call class object to get these values
    TourManager tm(nCities, nTours, nGens, nPercent);

    tm.bruteForce();
    tm.geneticAlg();

    std::cout << "\n";

    return 0;
}
