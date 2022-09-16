#include <iostream>

// The "preprocessor", part of compiler build process, replaces this line with the contents of the
// `foo.h` file.  This is why she says to define the function signature above your main function.
#include "foo.h"

using namespace std;

void hello_world() {
    std::cout << "Hello, world." << endl;
}
