#include <stdio.h>

const int max=100000000;
const int k=10;

int q[k]={0};
int n=0;

int main()
{
    int i;

    q[0] = 1;
    q[1] = 1;
    n = 1;
    
    for (; ! (q[n%k] <= max && (q[n%k] + q[(n-1)%k]) >= max); n++)
        q[(n+1)%k] = q[n%k] + q[(n-1)%k]; 

    for (i=0; i<k; ++i)
    {
        printf("%d\t%d\n", n, q[n%k]);
        n--;
    }

    return 0;
}
