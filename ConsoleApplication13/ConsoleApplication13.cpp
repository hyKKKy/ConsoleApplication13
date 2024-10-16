#include <iostream>
#include "Array.h"

int main()
{
    Array<int> arr{ 1, 2, 3, 4, 5 };

    try {
        
        std::cout << arr[6] << std::endl;
    }
    catch (const std::out_of_range& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
}


