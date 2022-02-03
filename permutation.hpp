/* ----------------------------
 * Student Dev: Martin Kadzis
 * Date: October 30th, 2020
 * Class: COP4534, John Coffey
 * ----------------------------
 */

#ifndef PERMUTATION_HPP
#define PERMUTATION_HPP

#include <string>

class Permutation {

    private:
        static const int MAX = 20;

        int set[MAX];
        int nLength;

    public:
        Permutation(int length);
        void initSet(int length);
        
        void perm1();
        void swap(int i, int j);

        std::string printSet();
        int* getSet();

        long int factorial(long int);
};

#endif
