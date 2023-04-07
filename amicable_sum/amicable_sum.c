#include "p21.h"

int
amicable_sum(int uplim)
{
    int tot_sum = 0;
    for (int i = 2; i < uplim; i++)
    {
        int a_sum = sum_divisors(i);
        int b_sum = sum_divisors(a_sum);
        if ((i == b_sum) && (i != a_sum))
        {
            tot_sum += (i + a_sum);
        }
    }
    return tot_sum;
}


int
sum_divisors(int x)
{
    sum = 0;
    for (int i = 1; i < x; i++)
    {
        if (x % i == 0)
        {
            sum += i;
        }
    }
    return sum;
}

