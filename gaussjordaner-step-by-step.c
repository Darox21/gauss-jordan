/* gaussjordaner-step-by-step.c
Gauss-Jordan Elimination
Version: 1.0.2
2023-11-08
Author: Darío Quiñones

Reads the dimensions of a matrix of fractions of size nxm,
then applies Gauss-Jordan elimination to the matrix.
Printing each step as it goes.

For compilation requires the function definitions for frac.h
so the compilation looks like:

> gcc -o gaussjordaner gaussjordaner-step-by-step.c frac.c

An example input can be something like:

3 6
2 1/2 1 6 4 5
0 2 2/3 3 -1 5
1 0 1 3 3 2

*/


#include <stdio.h>
#include <stdlib.h>
#include "frac.h"

// Matrix datatype
// Stores a matrix of fractions along
// with its dimensions as rows and columns.
typedef struct matrix
{
    int rows;
    int cols;
    frac **data;
} matrix;

// Reads a matrix from stdin
// Returns that matrix
matrix read_matrix();

// Prints a matrix to stdout
void print_matrix(matrix *m);

// Applies Gauss-Jordan elimination to a matrix
void gauss_jordan(matrix *m);

// Swaps two rows from a matrix
void swap_rows(matrix *m, int row1, int row2);

// Multiplies a row in a matrix for a given fraction
void multiply_row(matrix *m, int row, frac *f);

// Adds to row1 the result of multiplying row2 by a factor;
void add_rows(matrix *m, int row1, int row2, frac *factor);

int main()
{
    matrix m = read_matrix();
    printf("Matrix of size %dx%d\n", m.rows, m.cols);
    print_matrix(&m);
    gauss_jordan(&m);
    print_matrix(&m);
    return 0;
}

matrix read_matrix()
{
    matrix m;
    int i, j, num, den;
    scanf("%d", &m.rows);
    scanf("%d", &m.cols);
    m.data = (frac **)malloc(sizeof(frac *) * m.rows);
    for (i = 0; i < m.rows; i++)
    {
        m.data[i] = (frac *)malloc(sizeof(frac) * m.cols);
        for (j = 0; j < m.cols; j++)
        {
            m.data[i][j] = scan_frac();
        }
    }
    return m;
}

void print_matrix(matrix *m)
{
    int i, j;
    for (i = 0; i < m->rows; i++)
    {
        printf("[");
        for (j = 0; j < (m->cols)-1; j++)
        {
            print_frac(&m->data[i][j]);
            printf(",");
        }
        print_frac(&m->data[i][j]);
        printf("]\n");
    }
    printf("\n");
}

void gauss_jordan(matrix *m)
{
    int pivotRow, col, row, offset;
    frac *pivot, *current, mult_inverse, factor;

    pivotRow = 0;
    for (col = 0; col < m->cols; col++)
    {
        if (pivotRow == m->rows)
            break; // Not enough equations to continue

        pivot = &(m->data[pivotRow][col]);

        // Maybe Search for a valid pivot
        offset = 0;
        while (pivot->num == 0 && pivotRow + offset < (m->rows)-1)
        {
            offset++;
            pivot = &(m->data[pivotRow + offset][col]);
        }
        if (pivot->num == 0) // No pivot found this column
            continue;

        if (offset) // Swap the rows
        {
            printf("Swapped Rows\n");
            swap_rows(m, pivotRow, pivotRow + offset);
        }

        if (pivot->num != pivot->den) // If it is not 1/1
        {
            mult_inverse = create_frac(pivot->den, pivot->num);
            printf("R_%d * ", pivotRow+1);
            print_frac(&mult_inverse);
            printf("\n");
            multiply_row(m, pivotRow, &mult_inverse);
        }

        for (row = 0; row < m->rows; row++)
        {
            if (row == pivotRow) // Skip the pivot row
                continue;
            current = &(m->data[row][col]);
            if (current->num == 0) // Skip rows that have a 0
                continue;

            factor = create_frac(-(current->num), current->den);
            add_rows(m, row, pivotRow, &factor);
        }
        print_matrix(m);
        pivotRow += 1;
    }
    return;
}

void swap_rows(matrix *m, int row1, int row2)
{
    int i;
    frac temp;
    for (i = 0; i < m->cols; i++)
    {
        temp = m->data[row1][i];
        m->data[row1][i] = m->data[row2][i];
        m->data[row2][i] = temp;
    }
}

void multiply_row(matrix *m, int row, frac *f)
{
    int i;
    for (i = 0; i < m->cols; i++)
        m->data[row][i] = mult_frac(&m->data[row][i], f);
}

void add_rows(matrix *m, int row1, int row2, frac *factor)
{
    int i;
    frac f;
    printf("R_%d -> R_%d + (", row1 + 1, row1 + 1);
    print_frac(factor);
    printf(")*R_%d\n", row2 + 1);
    for (i = 0; i < m->cols; i++)
    {
        f = mult_frac(&(m->data[row2][i]), factor);
        m->data[row1][i] = add_frac(
            &m->data[row1][i],
            &f);
    }
}