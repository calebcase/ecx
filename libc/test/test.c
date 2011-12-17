#include <ecx_stdlib.h>
#include <stdio.h>

int main()
{
    double d = ecx_strtod("1.3345", NULL);
    printf("1.3345 + 2.0 = %f\n", d + 2.0);

    d = ecx_strtod("", NULL);
    printf("d = %f\n", d);

    return 0;
}
