#include <iostream>

int main () {
    bool Rx = 0;
    bool BTU = 0;
    bool BCU = 0;
    while (true) {
        std::cout << "Rx: ";
        if (!(std::cin >> Rx)) break;
        std::cout << "BTU: ";
        if (!(std::cin >> BTU)) break;
        std::cout << "BCU: ";
        if (!(std::cin >> BCU)) break;
    }
}