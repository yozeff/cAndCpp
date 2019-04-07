//
//  millerRabinTest.cpp
//  
//
//  Created by Joseph Harrison on 07/04/2019.
//

#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

//fast algorithm for modular exponentiation
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

bool miller_rabin(int n, int k)
{
    //write n as 2^r * d + 1
    int r = 0;
    int d = n - 1;
    while (d % 2 == 0)
    {
        d /= 2;
        r++;
    }
    cout << n << " = " << "2^" << r << " * " << d << " + 1\n";
    int a, x;
    bool contflag;
    //witness loop
    for (int i = 0; i < k; i++)
    {
        //pick integer a
        a = rand() % (n - 2) + 2;
        x = mod_exp(a, d, n);
        if (x == 1 || x == n - 1)
        {
            continue;
        }
        else
        {
            contflag = false;
            for (int j = 0; j < r - 1; j++)
            {
                x = mod_exp(x, 2, n);
                if (x == n - 1)
                {
                    j = r - 1;
                    contflag = true;
                    break;
                }
            }
            if (contflag == false)
            {
                return false;
            }
        }
    }
    return true;
}

int main(void)
{
    int n, k;
    bool result;
    cout << "n: ";
    cin >> n;
    cout << "k: ";
    cin >> k;
    result = miller_rabin(n, k);
    if (result == true)
    {
        cout << "prime\n";
    }
    else
    {
        cout << "composite\n";
    }
}
