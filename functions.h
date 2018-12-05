/*
 * functions.h
 *
 *  Created on: Oct 29, 2018
 *      Author: SUNIL
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

/*
 * Function to fill matrix elements with double values between (inclusive) 0 and 1
 * @param X is a pointer to a pointer pointing to the first element of the square matrix to be filled
 * @param filltype, 0 indicates that the matrix is to be initialized with zeroes, and 1 for initializing with random values between 0 and 1
 * @param numRows, indicating the size of the square matrix
 * return 1 for successful operation, 0 otherwise
 */
int fillMatrix(double ** X, int filltype, int numRows);

/*
 * Function to print a matrix to the console
 * @param X, double pointer of type double to characterize the matrix to be printed
 * @param numRows, of type int indicating the size of the square matrix
 * return 1 indicating successful operation, 0 otherwise
 */
int printMatrix(double ** X, int numRows);

/*
 * Function to release memory allocated to elements of the matrix (each row)
 * @param X, double pointer of type double to characterize the matrix whose elements are to be freed
 * @param numRows, of type int indicating the size of the square matrix
 * return 1 for successful operation, 0 otherwise
 */
int freeMatrix(double **X, int numRows);

/*
 * Function to perform sequential matrix multiplication
 * @param A, double pointer characterizing the first matrix to be multiplied
 * @param B, double pointer characterizing the second matrix to be multiplied
 * @param C, double pointer to the result matrix
 * @param numRows, size of each of the square matrices
 * return a double value indicating the time for matrix multiplication if successful, -1 otherwise
 */
double sequentialProduct(double **A, double **B, double **C, int numRows);

/*
 * Function to perform parallel (static mapping) matrix multiplication
 * @param A, double pointer characterizing the first matrix to be multiplied
 * @param B, double pointer characterizing the second matrix to be multiplied
 * @param C, double pointer to the result matrix
 * @param numRows, size of each of the square matrices
 * @param numthreads, number of threads to be utilized for parallel operation
 * return a double value indicating the time for matrix multiplication if successful, -1 otherwise
 */
double staticMapping_Product(double **A, double **B, double **C, int numRows, int numthreads);

/*
 * Function to perform parallel (dynamic mapping) matrix multiplication
 * @param A, double pointer characterizing the first matrix to be multiplied
 * @param B, double pointer characterizing the second matrix to be multiplied
 * @param C, double pointer to the result matrix
 * @param numRows, size of each of the square matrices
 * @param numthreads, number of threads to be utilized for parallel operation
 * @param global count, value of the shared variable to keep track of next row to be allocated to the next awaiting thread
 * return a double value indicating the time for matrix multiplication if successful, -1 otherwise
 */
double dynamicMapping_Product(double **A, double **B, double **C, int numRows, int numthreads, int global_count);

/*
 * Function to calculate SpeedUp(K) for dynamic mapping
 * @param seqtime, time taken for sequential product
 * @param dyntime, time taken for obtaining product using dynamic mapping
 * return a double value indicating the SpeedUp(K) value if successful, -1 otherwise
 */
double speedupKdyn(double seqtime, double dyntime);

/*
 * Function to calculate SpeedUp(K) for static mapping
 * @param seqtime, time taken for sequential product
 * @param stattime, time taken for obtaining product using dynamic mapping
 * return a double value indicating the SpeedUp(K) value if successful, -1 otherwise
 */
double speedupKstat(double seqtime, double stattime);

#endif /* FUNCTIONS_H_ */
