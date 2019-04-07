//
//  modExp.cpp
//  
//
//  Created by Joseph Harrison on 05/04/2019.
//

#include <iostream>

using namespace std;

int mod_exp(int base, int exp, int modulus)
{
    if (modulus == 1){
        return 0;
    }
    int result = 1;
    base = base % modulus;
    while (exp > 0)
    {
        if (exp % 2 == 1)
        {
            result = (result * base) % modulus;
        }
        exp = exp >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

int main(void)
{
    //get our base, exponent and modulus
    int base, exp, modulus, result;
    std::cout << "base: ";
    std::cin >> base;
    std::cout << "exp: ";
    std::cin >> exp;
    std::cout << "modulus: ";
    std::cin >> modulus;
    result = mod_exp(base, exp, modulus);
    std::cout << "result: " << result << "\n";
}
