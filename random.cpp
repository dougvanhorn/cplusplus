#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>

#include "foo.h"

using namespace std;


int main() {
    hello_world();
    return 0;
}


/*
int random_example()
{
    unsigned seed = static_cast<unsigned>(time(nullptr));
    //srand(seed);
    srand(612712738);
    int random_value = rand();
    cout
        << "Seed: " << seed
        << endl << "Range: [0, " << RAND_MAX << "]"
        << endl << "Random Value: " << rand()
        << endl << "Random Value: " << rand()
        << endl << "Random Value: " << rand()
        << endl;

    cout << rand() << endl;

    return 0;
}
*/