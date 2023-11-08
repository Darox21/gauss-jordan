// Fraction datatype
//
// Stores a fraction as a numerator and a denominator.
// Always has the most simplified form of a fraction.
// The denominator is always positive.
// The zero fraction is represented as 0/1.
typedef struct frac
{
    int num;
    int den;
} frac;

// Creates a fraction from two integers.
// If the denominator is 0, it will be set to 1
// If the denominator is negative, the numerator
// will be negated instead.
// Simplifies the fraction if possible.
frac create_frac(int num, int den);

// Scans a fraction from stdin
// The input can be a whole number (num)
// or a fraction written as num/den
frac scan_frac();

// Prints a fraction to stdout
void print_frac(frac *f);

// Adds two fractions
// Returns a simplified fraction
frac add_frac(frac *f1, frac *f2);

// Multiplies two fractions
// Returns a simplified fraction
frac mult_frac(frac *f1, frac *f2);