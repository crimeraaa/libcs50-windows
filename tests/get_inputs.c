/* Standard libaries */
#include <stdbool.h>
#include <stdio.h>

/* Third-party libaries, e.g. CS50. */
#include <cs50.h>

int absolute_value(int number);
int *integer_division(int dividend, int divisor, int *quotient, int *remainder);

int main(void)
{
    string name = get_string("Hello, what's your name? ");
    string food = get_string("Hi %s! What's your favorite food? ", name);
    printf("%s loves %s!\n", name, food);

    int dividend = get_int("Enter a dividend: ");
    int divisor = get_int("Enter a divisor: ");
    int quotient;
    int remainder;
    if (!integer_division(dividend, divisor, &quotient, &remainder)) 
    {
        return 1;
    }
    printf("%i / %i = %i R %i\n", dividend, divisor, quotient, remainder);

    return 0;
}

int *integer_division(int dividend, int divisor, int *quotient, int *remainder)
{
    if (divisor == 0) 
    {
        printf("Division by 0 is not allowed!\n");
        return NULL;
    }

    bool positive_result = (dividend >= 0) && (divisor > 0);
    dividend = absolute_value(dividend);
    divisor = absolute_value(divisor);

    /* Local variable so we don't constantly dereference the pointer. */
    int quo = 0;
    while (dividend >= divisor) 
    {
        dividend -= divisor;
        quo++;
    }
    *quotient = quo;
    *remainder = dividend;
    if (!positive_result)
    {
        *quotient *= -1;
    }
    return quotient;
}

int absolute_value(int number)
{
    if (number < 0) 
    {
        return number * -1;
    }
    return number;
}