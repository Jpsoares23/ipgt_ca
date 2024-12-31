#include "arithmetic.h"

long long conversionToDecimal(const char *num, int base)
{
    int length = 0;
    long long result = 0;

    while (num[length] != '\0')
    { // length of the result
        length++;
    }

    for (int i = 0; i < length; i++)
    {
        int number = 0;

        // convert the character into a number (consider base 10 for now)
        if (num[i] >= '0' && num[i] <= '9')
        {
            number = num[i] - '0'; // Convert '0' to 0, '1' to 1, ..., '9' to 9
        }
        // handling of letters
        else if (num[i] >= 'A' && num[i] <= 'F')
        {
            number = num[i] - 'A' + 10;
        }
        else if (num[i] >= 'a' && num[i] <= 'f')
        {
            number = num[i] - 'a' + 10;
        }

        // update the result with the weighted value (exponential power of base)
        result += (number * exponencial(base, length - i - 1));
    }

    return result;
}

char *conversionFromDecimal(long long num, int base)
{
    if (base == 10)
    {
        //
    }

    static char result[33]; // ensure enough space for 32 bits
    char digits[] = "0123456789ABCDEF";
    int idx = 0;

    // perform the conversion
    do
    {
        result[idx++] = digits[num % base];
        num /= base;
    } while (num > 0);

    result[idx] = '\0';

    // Reverse the result to get the correct order
    for (int i = 0; i < idx / 2; i++)
    {
        char temp = result[i];
        result[i] = result[idx - 1 - i];
        result[idx - 1 - i] = temp;
    }

    return result;
}