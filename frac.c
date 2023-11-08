#include <stdio.h>
#include "frac.h"

// Simplifies a fraction.
//
// It has a linear complexity because it's not optimized
void simplify(frac *f)
{
    int i;
    if (f->num == 0)
    {
        f->den = 1;
    }
    else
    {
        if (f->num > f->den)
            i = f->den;
        else if (f->num < 0)
            i = -(f->num);
        else
            i = f->num;

        // This part could be FAR better than this
        for (; i > 1; i--)
        {
            if (f->num % i == 0 && f->den % i == 0)
            {
                f->num /= i;
                f->den /= i;
            }
        }
    }
}

frac create_frac(int num, int den)
{
    frac f;

    if (den == 0)
    {
        printf("Error: Denominator cannot be 0\n");
        den = 1;
    }
    else if (den < 0)
    {
        num = -num;
        den = -den;
    }
    f.num = num;
    f.den = den;
    simplify(&f);
    return f;
}

frac scan_frac()
{
    frac f;
    int num, den;
    char separator;
    scanf("%d%c", &num, &separator);
    // printf("%d,", separator);
    if (separator == ' ' || separator == '\n')
    {
        // If only one number was entered, it's a whole number (num)
        f.num = num;
        f.den = 1;
    }
    else if (separator == '/')
    {
        // If there is a '/', it's a proper fraction (num/den)
        f.num = num;
        if (scanf("%d", &den))
        {
            f.den = den;
            simplify(&f);
        }
        else
        {
            printf("Invalid input format.\n");
            den = 1;
        }
    }
    else
    {
        // Invalid input
        printf("Invalid input format.\n");
        f.num = 0;
        f.den = 1;
    }

    return f;
}

void print_frac(frac *f)
{
    if (f->den == 1)
        printf("%d", f->num);
    else
        printf("%d/%d", f->num, f->den);
}

frac add_frac(frac *f1, frac *f2)
{
    frac f;
    if (f1->den == f2->den)
    {
        f.num = f1->num + f2->num;
        f.den = f1->den;
    }
    else
    {
        f.num = (f1->num * f2->den) + (f2->num * f1->den);
        f.den = f1->den * f2->den;
    }
    simplify(&f);
    return f;
}

frac mult_frac(frac *f1, frac *f2)
{
    frac f;
    f.num = f1->num * f2->num;
    f.den = f1->den * f2->den;
    simplify(&f);
    return f;
}
