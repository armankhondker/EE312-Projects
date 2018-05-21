// matrix-multiplication <Project2.cpp>
// EE 312 Project 2 submission by
// Arman Khondker
// aak2464
// Slip days used: 0
// Spring 2018
// Include the contents of this file at the top of every file that you submit, replacing the fields within <>.  Do not keep the <>.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "MatrixMultiply.h"

void multiplyMatrices(
        double a[],
        const uint32_t a_rows,
        const uint32_t a_cols,
        double b[],
        const uint32_t b_cols,
        double c[])
{

    const uint32_t b_rows = a_cols;             //columns in A must equal rows in B for multiplication to be valid

    int row =0;

    while( row < a_rows)
    {
        int column=0;

        while (column < b_cols)
        {
            double sum = 0;
            int k=0;           //k-loop

            while( k < b_rows)
            {
                sum = sum + ( a[(row * a_cols) + k] * b[(k * b_cols) + column] );          //sum will hold the value needed to be stored after looping
                k++;

            }

            c[row * b_cols + column] = sum;          //set the c matrix to appropriate value
            column++;
        }

        row++;
    }

}

double** multiplyMatricesPtr(
        double** a,
        const uint32_t a_rows,
        const uint32_t a_cols,
        double** b,
        const uint32_t b_cols)
{

    const uint32_t b_rows = a_cols;             //columns in A must equal rows in B for multiplication to be valid
    int z;
    double** matrix = (double**)malloc(a_rows* sizeof(double*));                     //dynamically allocate the matrix
    for(z=0; z < a_rows; z++){
        double* col = (double*)malloc(a_cols* sizeof(double));
        matrix[z] =col;
    }

    int row =0;

    while( row < a_rows)
    {
        int column=0;

        while (column < b_cols)
        {
            double sum = 0;
            int k=0;                    //k-loop

            while( k < b_rows)
            {
                sum = sum + (a[row][k] * b[k][column]);
                k++;

            }
            matrix[row][column]=sum;        //set the c matrix to appropriate value
            column++;
        }
        row++;
    }
  return matrix;

}

double** transposeMatrix(
         double** a,
         const uint32_t a_rows,
         const uint32_t a_cols)
{

    int z;
    double** transposeMatrix = (double**)malloc(a_cols* sizeof(double*));              //dynamically allocate the transpose
    for(z=0; z < a_cols; z++){
        double* col = (double*)malloc(a_rows* sizeof(double));
        transposeMatrix[z] =col;
    }

    int row =0;

    for(row=0; row< a_rows; row++)
    {
         int column=0;

         for(column=0; column< a_cols; column++)
        {
            transposeMatrix[column][row] = a[row][column];            //creates the transpose
        }

    }

    return transposeMatrix;
}
