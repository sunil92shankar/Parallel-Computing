/*
 * functions.c
 *
 *  Created on: Oct 29, 2018
 *      Author: SUNIL
 */

#include<time.h>//to read wallclock time
#include<stdio.h>
#include<stdlib.h>
#include <omp.h>

//function to fill matrix components with values - random values between 0-1 if filltype is 1, else fill all elements as 0
int fillMatrix(double ** X, int filltype, int numRows)
{
	if(X==NULL || (filltype!=0 && filltype!=1) || numRows<0)//parameter check, X should be a valid double pointer, filltype should have predefined values (0,1) ad numRows cannot be negative
	{
		printf("invalid input\n");
		return 0;
	}
	//looping through all pointers to rows of the matrix in order to allocate memory for rows
	for(int i=0;i<numRows;i++)
	{
		//allocate memory for pointers to row elements of the matrix
		X[i]=(double *) malloc(numRows*sizeof(double));
		//check for success of memory allocation
		if(X[i]==NULL)
		{
			printf("malloc error\n");
			return 0;
		}
	}

	//if filltype is 1, then fill matrix elements with random values between 0 and 1
	if(filltype==1)
	{
		for(int i=0;i<numRows;i++)//loop through rows
			for(int j=0;j<numRows;j++)//loop through columns
			{
				X[i][j]=((double) rand())/RAND_MAX;//allocate random value between 0 and 1 to each element
			}
	}
	else//if filltype is 0, then initialize a matrix with zero
	{
		for(int i=0;i<numRows;i++)//loop through rows
			for(int j=0;j<numRows;j++)//loop through columns
			{
				X[i][j]=0;//initilize each element as 0
			}
	}
	return 1;
}

//function to print matrix X given its size is numRows
int printMatrix(double ** X, int numRows)
{
	if(X==NULL || numRows<0)//check for validity of function arguments
	{
		printf("invalid matrix\n");
		return 0;//unsuccessful operation
	}

	for(int i=0;i<numRows;i++)//loop through matrix rows
	{
		for(int j=0;j<numRows;j++)//loop through matrix columns
		{
			printf("%lf ",X[i][j]);//print matrix element
		}
		printf("\n");
	}
	printf("\n");

	return 1;//successful operation
}

//function to free memory allocated to pointers pointing to the elements in a matrix row
int freeMatrix(double **X, int numRows)
{
	if(X!=NULL && numRows>=0)//check validity of parameters
	{
		for(int i=0;i<numRows;i++)//loop through each row
		{
			if(X[i]!=NULL)//check for validity of pointer
				free(X[i]);//free pointer to each row element
			else
			{
				printf("invalid pointer\n");
				return 0;//unsuccessful operation if pointer is invalid
			}
		}
	}
	else
	{
		printf("invalid matrix\n");
		return 0;//unsuccessful operation if the double pointer is invalid
	}

	return 1;//successful operation
}

//Function to perform sequential matrix multiplication
double sequentialProduct(double **A, double **B, double **C, int numRows)
{
	if(A==NULL || B==NULL || C==NULL || numRows<0)//parameter check
	{
		printf("invalid matrix for multiplication\n");
		return -1;//unsuccessful operation
	}
	double start = omp_get_wtime();//get current time and store value
	for(int i=0;i<numRows;i++)//loop through rows
	{
		for(int j=0;j<numRows;j++)//loop through columns
		{
			//C[i][j]=0; this step is not required as the result maatrix is already initialized to 0
			for(int k=0;k<numRows;k++)//traverse through elements of matrices to be multiplied
			{
				C[i][j]=C[i][j]+A[i][k]*B[k][j];//storing product values in result matrix elements
			}
		}
	}
	double delta = omp_get_wtime() - start;//calculating sequential product operation time
	return delta;//return operation time
}

//function to perform parallel product of matrices using static mapping
double staticMapping_Product(double **A, double **B, double **C, int numRows, int numthreads)
{
	if(A==NULL || B==NULL || C==NULL || numRows<0 || numthreads<1)//parameter check
	{
		printf("invalid matrices (or) arguments\n");
		return -1;//unsuccessful operation
	}

	int nthreads=-1;//variable to obtain number of threads actually generated after parallelization
	omp_set_num_threads(numthreads);//set number of threads desired for parallelization
	double start = omp_get_wtime();//start time for operation
	#pragma omp parallel//start parallelization
	{
		double sum=0;//local sum variable to thread
		if(omp_get_thread_num()==0)//checking if this is the first thread
		{
			nthreads=omp_get_num_threads();//actual number of threads generated during parallelization
			printf("Number of threads for static mapping: %d\n", nthreads);//NOTE: this line was commented out during simulation
		}
		for (int i=omp_get_thread_num(); i<numRows; i+=nthreads)//looping through rows allocated for each thread
		{
			for(int j=0;j<numRows;j++)//looping through columns
			{
				for(int k=0;k<numRows;k++)//looping through elements of A and B to obtain product
				{
					sum+=A[i][k]*B[k][j];
				}
				C[i][j]=sum;//value of element i,j of result matrix
				sum=0;//re initialize sum to zero for i,j+1 element computation
			}
		}
	}
	double delta = omp_get_wtime() - start;//get time for product operation
	printf("\n");
	return delta;

}

//function to perform parallel product of matrices using dynamic mapping
double dynamicMapping_Product(double **A, double **B, double **C, int numRows, int numthreads, int global_count)
{
	if(A==NULL || B==NULL || C==NULL ||  numRows<0 || numthreads<1 ||  global_count!=0)//parameter check
	{
		printf("invalid matrices (or) variables\n");
		return -1;//unsuccessful operation
	}
	omp_set_num_threads(numthreads);//set number of threads desired for parallel processing
	double start = omp_get_wtime();//get current time
	#pragma omp parallel//start parallelization (generation of threads)
	{
		double sum=0;//declare and initialize variable that holds the value for each element of the result matrix
		//NOTE the following 4 lines were commented out for speedup studies
		if(omp_get_thread_num()==0)//check if this is the first thread
		{
			printf("Number of threads for dynamic mapping: %d\n", omp_get_num_threads());//check actual number of threads allocated for dynamic mapping parallel processing
		}
		for (int i=global_count; i<numRows; i=global_count)//looping through the global count variable that allocated rows to the threads [equivalent to the while loop used for illustration in the assignment]
		{
			#pragma omp critical//critical region to update global count variable
			{
				(global_count)++;//update global count in critical region
			}
			for(int j=0;j<numRows;j++)//loop through columns
			{
				for(int k=0;k<numRows;k++)//loop through elements of A and B to generate dot product
				{
					sum+=A[i][k]*B[k][j];//We do not use C[i][j] here to reduce repeated access to a non-local (to the thread) variable
				}
				C[i][j]=sum;//element i,j of result matrix C
				sum=0;//re initialize sum to zero for i,j+1 element computation
			}
		}
	}
	double delta = omp_get_wtime() - start;//calculate  time for dynamic mapping parallel product operation
	printf("\n");
	return delta;//return operation time

}

//function to compute speedup(k) for dynamic mapping
double speedupKdyn(double seqtime, double dyntime)
{
	if(seqtime<0 || dyntime<0)//parameter check
	{
		printf("invalid time value\n");
		return -1;//unsuccessful operation
	}

	return (seqtime/dyntime);//return speedup value
}

double speedupKstat(double seqtime, double stattime)
{
	if(seqtime<0 || stattime<0)//parameter check
	{
		printf("invalid time value\n");
		return -1;//unsuccessful operation
	}

	return (seqtime/stattime);//return speedup value
}

