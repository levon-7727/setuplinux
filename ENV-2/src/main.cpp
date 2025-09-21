#include <iostream>
#include <vector>
#include "Complex.h"
#include "Sort.h"

int main() {
    std::vector<Complex> v = {
        Complex(3, 4),     
        Complex(1, 1),     
        Complex(-2, 2),    
        Complex(0, 5),     
        Complex(3, 4)      
    };

    std::cout << "Before sorting:\n";
    for (auto& c : v) {
        std::cout << "(" << c.getReal() << ", " << c.getImag() << ") abs=" << c.abs() << "\n";
    }

    sortComplexes(v);

    std::cout << "After sorting:\n";
    for (auto& c : v) {
        std::cout << "(" << c.getReal() << ", " << c.getImag() << ") abs=" << c.abs() << "\n";
    }

    return 0;
}

