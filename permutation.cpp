/* ----------------------------
 * Student Dev: Martin Kadzis
 * Date: October 30th, 2020
 * Class: COP4534, John Coffey
 * ----------------------------
 * 
 * The following code is a rewritten
 * Permutation Class that was given
 * by the professor, it is rewritten
 * in hopes to understand it better.
 */

#include <iostream>

#include "permutation.hpp"

Permutation::Permutation(int length){
    this->nLength = length;

    initSet(length);
}

void Permutation::initSet(int length){
    int i;
    for(i = 0; i < length; ++i)
        this->set[i] = i + 1;
    this->set[i] = 0;
}

void Permutation::perm1(){

    int m, k, p, q, i;

    m = this->nLength - 1;
    while(this->set[m] > this->set[m+1])
        m--;

    k = this->nLength - 1;
    while(this->set[m] > this->set[k])
        k--;

    swap(m, k);

    p = m + 1;
    q = this->nLength - 1;
    while(p < q){
        swap(p, q);
        p++;
        q--;
    }
}

void Permutation::swap(int i, int j){
    int tempI = this->set[i];
    this->set[i] = this->set[j];
    this->set[j] = tempI;
}

std::string Permutation::printSet(){

    std::string setString = "";
    for (int i = 0; i < this->nLength; ++i)
        setString += std::to_string(this->set[i]) + " ";
    
    return setString;
}

int* Permutation::getSet(){
    return this->set;
}

long int Permutation::factorial(long int n){
    if (n == 0) return 1;
    return factorial(n - 1) * n;
}
