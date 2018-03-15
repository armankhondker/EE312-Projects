#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "MatrixMultiply.h"


void generateIdentityMatrix(double a[], const uint32_t rows,
                            const uint32_t cols);

void generateIdentityMatrixPtr(double **a, const uint32_t rows,
                               const uint32_t cols);

void perturbMatrix(double a[], const uint32_t rows, const uint32_t cols,
                   uint32_t src_row[], double perturb_values[],
                   const uint32_t num_perturbations);

void perturbMatrixPtr(double **a, const uint32_t rows, const uint32_t cols,
                      uint32_t src_row[], double perturb_values[],
                      const uint32_t num_perturbations);

void generateRandomMatrix(double a[], const uint32_t rows,
                          const uint32_t cols);

void generateRandomMatrixPtr(double** a, const uint32_t rows,
                             const uint32_t cols);


int assertEqualMatrices(double a[], double b[], const uint32_t rows,
                        const uint32_t cols);

int assertEqualMatricesPtr(double** a, double** b, const uint32_t rows,
                           const uint32_t cols);

void copyMatrix(double dest[], double src[], const uint32_t rows,
                const uint32_t cols);

void copyMatrixPtr(double** dest, double** src, const uint32_t rows,
                   const uint32_t cols);

void printMatrix(double a[], const uint32_t rows, const uint32_t cols);

void printMatrixPtr(double** a, const uint32_t rows, const uint32_t cols);

void memoryRelease(double** ptr, int length);

void generateIdentityMatrix(double a[], const uint32_t rows,
                            const uint32_t cols) {
    uint32_t i, j; // two loop variables, uninteresting in all respects.
    i = 0;
    while (i < rows) {
        j = 0;
        while (j < cols) {
            if (i == j) {
                a[(i * cols) + j] = 1.0;
            } else {
                a[(i * cols) + j] = 0;
            }
            j += 1;
        }
        i += 1;
    }
}

void generateIdentityMatrixPtr(double **a, const uint32_t rows,
                               const uint32_t cols) {
    uint32_t i, j; // two loop variables, uninteresting in all respects.
    i = 0;
    while (i < rows) {
        j = 0;
        while (j < cols) {
            if (i == j) {
                a[i][j] = 1.0;
            } else {
                a[i][j] = 0;
            }
            j += 1;
        }
        i += 1;
    }
}

void perturbMatrix(double a[], const uint32_t rows, const uint32_t cols,
                   uint32_t src_row[], double perturb_values[],
                   const uint32_t num_perturbations) {
    uint32_t i, k;    // two loop variables, uninteresting in all respects.
    uint32_t dst_row; // index of the row being written into
    i = 0;
    while (i < num_perturbations) {
        assert(src_row[i] < rows);
        /* apply perturbation i to every row (except to itself) */
        dst_row = 0;
        while (dst_row < rows) {
            if (dst_row != src_row[i]) {
                /* take the src row, and scale it by the perturbation value
                 * and add the resulting row to the destination row */
                k = 0;
                while (k < cols) {
                    a[(dst_row * cols) + k] +=
                    perturb_values[i] * a[(src_row[i] * cols) + k];
                    k += 1;
                } // end for each element in a row
            }   // end if dst_row != src_row
            dst_row += 1;
        } // end for each dst_row in the matrix
        i += 1;
    } // end for each perturbation
}

void perturbMatrixPtr(double **a, const uint32_t rows, const uint32_t cols,
                      uint32_t src_row[], double perturb_values[],
                      const uint32_t num_perturbations) {
    uint32_t i, k;    // two loop variables, uninteresting in all respects.
    uint32_t dst_row; // index of the row being written into
    i = 0;
    while (i < num_perturbations) {
        assert(src_row[i] < rows);
        /* apply perturbation i to every row (except to itself) */
        dst_row = 0;
        while (dst_row < rows) {
            if (dst_row != src_row[i]) {
                /* take the src row, and scale it by the perturbation value
                 * and add the resulting row to the destination row */
                k = 0;
                while (k < cols) {
                    a[dst_row][k] += perturb_values[i] * a[src_row[i]][k];
                    k += 1;
                } // end for each element in a row
            }   // end if dst_row != src_row
            dst_row += 1;
        } // end for each dst_row in the matrix
        i += 1;
    } // end for each perturbation
}

/*
 * generate a matrix with random elements.
 * the matrix should be stored in array a in row-major order
 * the parameters 'rows' and 'cols' specify the size of the matrix
 */
void generateRandomMatrix(double a[], const uint32_t rows,
                          const uint32_t cols) {
    const int max_value = 100; // maximum scale factor to apply to a row
    const int perturbations = 7;
    uint32_t src_rows[7];
    double perturb_values[7];
    int k; // an unininteresting loop variable
    
    /* randomly perturb the matrix seven times, that should scramble things pretty
     * well */
    generateIdentityMatrix(a, rows, cols);
    
    k = 0;
    while (k < perturbations) {
        src_rows[k] = rand() % rows;
        perturb_values[k] = max_value - (rand() % (2 * max_value));
        k += 1;
    }
    
    perturbMatrix(a, rows, cols, src_rows, perturb_values, perturbations);
}

void generateRandomMatrixPtr(double **a, const uint32_t rows,
                             const uint32_t cols) {
    const int max_value = 100; // maximum scale factor to apply to a row
    const int perturbations = 7;
    uint32_t src_rows[7];
    double perturb_values[7];
    int k; // an unininteresting loop variable
    
    /* randomly perturb the matrix seven times, that should scramble things pretty
     * well */
    generateIdentityMatrixPtr(a, rows, cols);
    
    k = 0;
    while (k < perturbations) {
        src_rows[k] = rand() % rows;
        perturb_values[k] = max_value - (rand() % (2 * max_value));
        k += 1;
    }
    
    perturbMatrixPtr(a, rows, cols, src_rows, perturb_values, perturbations);
}

int assertEqualMatrices(double a[], double b[], const uint32_t rows,
                        const uint32_t cols) {
    uint32_t i, j; // two loop variables, uninteresting in all respects.
    
    i = 0;
    while (i < rows) {
        j = 0;
        while (j < cols) {
            double difference = fabs(a[(i * cols) + j] - b[(i * cols) + j]);
            if (difference > 1.0e-6) {
                fprintf(stderr, "Sorry, matrices do not match, first difference at row "
                        "%d and col %d\n",
                        i, j);
                return false;
            }
            j += 1;
        }
        i += 1;
    }
    return true;
}

int assertEqualMatricesPtr(double **a, double **b, const uint32_t rows,
                           const uint32_t cols) {
    uint32_t i, j; // two loop variables, uninteresting in all respects.
    
    i = 0;
    while (i < rows) {
        j = 0;
        while (j < cols) {
            double difference = fabs(a[i][j] - b[i][j]);
            if (difference > 1.0e-6) {
                fprintf(stderr, "Sorry, matrices do not match, first difference at row "
                        "%d and col %d\n",
                        i, j);
                return false;
            }
            j += 1;
        }
        i += 1;
    }
    return true;
}

void copyMatrix(double dest[], double src[], const uint32_t rows,
                const uint32_t cols) {
    uint32_t i = 0;
    while (i < rows) {
        uint32_t j = 0;
        while (j < cols) {
            dest[(i * cols) + j] = src[(i * cols) + j];
            j += 1;
        }
        i += 1;
    }
}

void copyMatrixPtr(double **dest, double **src, const uint32_t rows,
                   const uint32_t cols) {
    uint32_t i = 0;
    while (i < rows) {
        uint32_t j = 0;
        while (j < cols) {
            dest[i][j] = src[i][j];
            j += 1;
        }
        i += 1;
    }
}

void printMatrix(double a[], const uint32_t rows, const uint32_t cols) {
    uint32_t i = 0;
    while (i < rows) {
        uint32_t j = 0;
        while (j < cols) {
            printf("%g, ", a[(i * cols) + j]); // %g is just like %f, only better
            j += 1;
        }
        printf("\n");
        i += 1;
    }
}

void printMatrixPtr(double **a, const uint32_t rows, const uint32_t cols) {
    uint32_t i = 0;
    while (i < rows) {
        uint32_t j = 0;
        while (j < cols) {
            printf("%g, ", a[i][j]); // %g is just like %f, only better
            j += 1;
        }
        printf("\n");
        i += 1;
    }
}


void memoryRelease(double** ptr, int length) {
    for(int i =0; i < length ; i++) {
        free(*(ptr + i));
    }
    free(ptr);
}

/* ---------------------------------------- */

void testMultiplyMatrixA(void) {
    double a[100];
    double b[100];
    double c[100];
    
    generateRandomMatrix(a, 10, 10);
    generateIdentityMatrix(b, 10, 10);
    multiplyMatrices(a, 10, 10, b, 10, c);
    printf("Stage 1 test testMultiplyMatrixA:...");
    if (!assertEqualMatrices(a, c, 10, 10)) {
        return;
    }
    printf("passed! :-)\n");
}

void testMultiplyMatrixB(void) {
    double a[100];
    double b[100];
    double c[100];
    
    generateRandomMatrix(a, 10, 10);
    generateIdentityMatrix(b, 10, 10);
    multiplyMatrices(b, 10, 10, a, 10, c);
    printf("Stage 1 test testMultiplyMatrixB:...");
    if (!assertEqualMatrices(a, c, 10, 10)) {
        return;
    }
    printf("passed! :-)\n");
}

void testMultiplyMatrixC(void) {
    double a[100];
    double b[100];
    double c[100];
    
    /* these arrays are used only for test C */
    uint32_t perturb_rows[5] = {2, 4, 6, 1, 7};
    double perturb_vals[5] = {1.0, -1.0, 2.0, -2.5, 3.0};
    double expected[] = {
        1, -10, 0, 0, 18, 0, -12, 3, 0, 0, 0, -6.5, 0, 0, 10.5, 0, -7,  3, 0, 0,
        0, -10, 0, 0, 18, 0, -12, 3, 0, 0, 0, -10,  0, 1, 18,   0, -12, 3, 0, 0,
        0, -10, 1, 0, 20, 0, -12, 3, 0, 0, 0, -10,  0, 0, 18,   1, -12, 3, 0, 0,
        0, -10, 0, 0, 20, 0, -13, 3, 0, 0, 0, -2.5, 0, 0, 4.5,  0, -3,  1, 0, 0,
        0, -10, 0, 0, 18, 0, -12, 3, 1, 0, 0, -10,  0, 0, 18,   0, -12, 3, 0, 1};
    
    generateIdentityMatrix(a, 10, 10);
    generateIdentityMatrix(b, 10, 10);
    
    perturbMatrix(a, 10, 10, perturb_rows, perturb_vals, 5);
    copyMatrix(a, b, 10, 10);
    perturbMatrix(b, 10, 10, perturb_rows, perturb_vals, 5);
    
    multiplyMatrices(a, 10, 10, b, 10, c);
    
    printf("Stage 1 test testMultiplyMatrixC:...");
    
    if (!assertEqualMatrices(c, expected, 10, 10)) {
        return;
    }
    printf("passed! :-)\n");
}

//added test case, try with non-square matrices and decimal points
void testMultiplyMatrixD(void) {
    double a[20] = {
        0.00, 0.05, -0.04, 0.67,
        -0.26, 0.75, 0.38, 0.43,
        0.00 , -0.48, 0.07, 0.16,
        0.65, 0.28, 0.43, 0.24,
        0.20, 0.00, 0.00 , 1.00};
    double b[8] = {
        0.06, 0.00,
        0.00, 0.34,
        -0.49, 0.71,
        -0.44, 0.00};
    double expected[10] = {
        -0.275200, -0.011400,
        -0.391000, 0.524800,
        -0.104700, -0.113500,
        -0.277300, 0.400500,
        -0.428000, 0.000000};
    double c[10];
    
    multiplyMatrices(a, 5, 4, b, 2, c);
    printf("Stage 1 test testMultiplyMatrixD:...");
    if (!assertEqualMatrices(c, expected, 5, 2)) {
        return;
    }
    printf("passed! :-)\n");
}

void testStage1(void) {
    testMultiplyMatrixA();
    testMultiplyMatrixB();
    testMultiplyMatrixC();
    testMultiplyMatrixD();
    
}

/* ---------------------------------------- */

void testMultiplyMatrixPtrA(void) {
    double **a;
    double **b;
    double **c;
    
    a = (double **)malloc(sizeof(double *) * 10);
    for (int i = 0; i < 10; i++) {
        *(a + i) = (double *)malloc(sizeof(double) * 10);
    }
    b = (double **)malloc(sizeof(double *) * 10);
    for (int i = 0; i < 10; i++) {
        *(b + i) = (double *)malloc(sizeof(double) * 10);
    }
    generateRandomMatrixPtr(a, 10, 10);
    generateIdentityMatrixPtr(b, 10, 10);
    c = multiplyMatricesPtr(a, 10, 10, b, 10);
    printf("Stage 2 testMultiplyMatrixPtrA:...");
    if (!assertEqualMatricesPtr(a, c, 10, 10)) {
        return;
    }
    memoryRelease(a, 10);
    memoryRelease(b, 10);
    memoryRelease(c, 10);
    
    printf("passed! :-)\n");
}

void testMultiplyMatrixPtrB(void) {
    double **a;
    double **b;
    double **c;
    
    a = (double **)malloc(sizeof(double *) * 10);
    for (int i = 0; i < 10; i++) {
        *(a + i) = (double *)malloc(sizeof(double) * 10);
    }
    b = (double **)malloc(sizeof(double *) * 10);
    for (int i = 0; i < 10; i++) {
        *(b + i) = (double *)malloc(sizeof(double) * 10);
    }
    
    generateRandomMatrixPtr(a, 10, 10);
    generateIdentityMatrixPtr(b, 10, 10);
    c = multiplyMatricesPtr(b, 10, 10, a, 10);
    
    printf("Stage 2 testMultiplyMatrixPtrB:...");
    
    if (!assertEqualMatricesPtr(a, c, 10, 10)) {
        return;
    }
    
    memoryRelease(a, 10);
    memoryRelease(b, 10);
    memoryRelease(c, 10);
    
    printf("passed! :-)\n");
}

void testMultiplyMatrixPtrC(void) {
    double **a;
    double **b;
    double **c;
    double **expected_ptr;
    
    /* these arrays are used only for test C */
    uint32_t perturb_rows[5] = {2, 4, 6, 1, 7};
    double perturb_vals[5] = {1.0, -1.0, 2.0, -2.5, 3.0};
    double one[10] = {1, -10, 0, 0, 18, 0, -12, 3, 0, 0};
    double two[10] = {0, -6.5, 0, 0, 10.5, 0, -7, 3, 0, 0};
    double three[10] = {0, -10, 0, 0, 18, 0, -12, 3, 0, 0};
    double four[10] = {0, -10, 0, 1, 18, 0, -12, 3, 0, 0};
    double five[10] = {0, -10, 1, 0, 20, 0, -12, 3, 0, 0};
    double six[10] = {0, -10, 0, 0, 18, 1, -12, 3, 0, 0};
    double seven[10] = {0, -10, 0, 0, 20, 0, -13, 3, 0, 0};
    double eight[10] = {0, -2.5, 0, 0, 4.5, 0, -3, 1, 0, 0};
    double nine[10] = {0, -10, 0, 0, 18, 0, -12, 3, 1, 0};
    double ten[10] = {0, -10, 0, 0, 18, 0, -12, 3, 0, 1};
    
    double *expected[] = {one, two, three, four, five,
        six, seven, eight, nine, ten};
    
    expected_ptr = expected;
    
    a = (double **)malloc(sizeof(double *) * 10);
    for (int i = 0; i < 10; i++) {
        *(a + i) = (double *)malloc(sizeof(double) * 10);
    }
    b = (double **)malloc(sizeof(double *) * 10);
    for (int i = 0; i < 10; i++) {
        *(b + i) = (double *)malloc(sizeof(double) * 10);
    }
    
    generateIdentityMatrixPtr(a, 10, 10);
    perturbMatrixPtr(a, 10, 10, perturb_rows, perturb_vals, 5);
    
    generateIdentityMatrixPtr(b, 10, 10);
    copyMatrixPtr(a, b, 10, 10);
    perturbMatrixPtr(b, 10, 10, perturb_rows, perturb_vals, 5);
    c = multiplyMatricesPtr(a, 10, 10, b, 10);
    
    printf("Stage 2 testMultiplyMatrixPtrC:...");
    
    if (!assertEqualMatricesPtr(c, expected_ptr, 10, 10)) {
        return;
    }
    
    memoryRelease(a, 10);
    memoryRelease(b, 10);
    memoryRelease(c, 10);
    
    printf("passed! :-)\n");
}

void testStage2(void) {
    testMultiplyMatrixPtrA();
    testMultiplyMatrixPtrB();
    testMultiplyMatrixPtrC();
}

/* ---------------------------------------- */

void testTransposeA(void) {
    double **result;
    double **input_ptr;
    double **expected_ptr;
    
    double one_a[2] = {1, 2};
    double two_a[2] = {3, 4};
    double *input_a[] = {one_a, two_a};
    input_ptr = input_a;
    
    double one_trans_a[2] = {1, 3};
    double two_trans_a[2] = {2, 4};
    
    double *expected_a[] = {one_trans_a, two_trans_a};
    expected_ptr = expected_a;
    
    
    printf("Stage 3 testTransposeA:...");
    result = transposeMatrix(input_ptr, 2, 2);
    
    if (!assertEqualMatricesPtr(result, expected_ptr, 2, 2)) {
        return;
    }
    
    memoryRelease(result, 2);
    printf("passed! :-)\n");
}

void testTransposeB(void) {
    double **result;
    double **input_ptr;
    double **expected_ptr;
    
    double one_b[3] = {1, 2, 3};
    double two_b[3] = {4, 5, 6};
    double three_b[3] = {7, 8, 9};
    double *input_b[] = {one_b, two_b, three_b};
    input_ptr = input_b;
    
    double one_trans_b[3] = {1, 4, 7};
    double two_trans_b[3] = {2, 5, 8};
    double three_trans_b[3] = {3, 6, 9};
    
    double *expected_b[] = {one_trans_b, two_trans_b, three_trans_b};
    expected_ptr = expected_b;
    
    printf("Stage 3 testTransposeB:...");
    result = transposeMatrix(input_ptr, 3, 3);
    if (!assertEqualMatricesPtr(result, expected_ptr, 3, 3)) {
        return;
    }
    
    memoryRelease(result, 3);
    printf("passed! :-)\n");
}

void testTransposeC(void) {
    double **result;
    double **input_ptr;
    double **expected_ptr;
    
    double one_c[3] = {1, 2, 3};
    double two_c[3] = {4, 5, 6};
    double *input_c[] = {one_c, two_c};
    input_ptr = input_c;
    
    double one_trans_c[2] = {1, 4};
    double two_trans_c[2] = {2, 5};
    double three_trans_c[2] = {3, 6};
    
    double *expected_c[] = {one_trans_c, two_trans_c, three_trans_c};
    expected_ptr = expected_c;
    
    printf("Stage 3 testTransposeC:...");
    result = transposeMatrix(input_ptr, 2, 3);
    if (!assertEqualMatricesPtr(result, expected_ptr, 3, 2)) {
        return;
    }
    
    memoryRelease(result, 3);
    
    printf("passed! :-)\n");
}

void testStage3(void) {
    testTransposeA();
    testTransposeB();
    testTransposeC();
}

int main(int argc, char **argv) {
    int i;
    
    /** Run only a specific test */
    for (i = 1; i < argc; i++) {
        if (strcmp("testMultiplyMatrixA", argv[i]) == 0) {
            testMultiplyMatrixA();
        } else if (strcmp("testMultiplyMatrixB", argv[i]) == 0) {
            testMultiplyMatrixB();
        } else if (strcmp("testMultiplyMatrixC", argv[i]) == 0) {
            testMultiplyMatrixC();
        } else if (strcmp("testMultiplyMatrixD", argv[i]) == 0) {
            testMultiplyMatrixD();
        } else if (strcmp("testTransposeA", argv[i]) == 0) {
            testTransposeA();
        } else if (strcmp("testTransposeB", argv[i]) == 0) {
            testTransposeB();
        } else if (strcmp("testTransposeC", argv[i]) == 0) {
            testTransposeC();
        } else if (strcmp("testMultiplyMatrixPtrA", argv[i]) == 0) {
            testMultiplyMatrixPtrA();
        } else if (strcmp("testMultiplyMatrixPtrB", argv[i]) == 0) {
            testMultiplyMatrixPtrB();
        } else if (strcmp("testMultiplyMatrixPtrC", argv[i]) == 0) {
            testMultiplyMatrixPtrC();
        } else {
            printf("ERROR: Incorrect test name %s\n", argv[i]);
            exit(1);
        }
    }
    
    if (argc == 1) {
        testStage1();
        testStage2();
        testStage3();
    }
    
    return 0;
}
