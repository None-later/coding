#include <string>

using namespace std;


string intToRoman(int n) 
{
    int values[13] = { 1000, 
                    900, 500, 400, 100, 
                    90, 50, 40, 10, 
                    9, 5, 4, 1 };
    string symbols[13] = { "M", 
                    "CM", "D", "CD", "C",
                    "XC", "L", "XL", "X",
                    "IX", "V", "IV", "I" };
    string res("");                

    for (int i = 0; i < 13; ++i)
    {
        int x = n / values[i];
        while (x > 0)
        {
            res += symbols[i];
            n -= values[i];
            x--;
        }
        if (n == 0)
            break;
    }            
    return res;                 
}