/*
 * assg4.c
 *
 *  Created on: Oct 29, 2018
 *      Author: SUNIL
 */

#include<time.h>//to read wallclock time
#include<stdio.h>
#include<stdlib.h>
#include"functions.h"
#include <omp.h>

#define numRows 5//Number of rows = Number of columns
#define numthreads 2//to control number of threads

int main()
{
	printf("\n--------------------\nStart of program run\n--------------------\n");
	int global_count=0;
	srand(time(NULL));//seeding rand() with time

	//Creating memory for matrix A
	double ** A = (double **)malloc(numRows*sizeof(double *));//allocating memory for matrix A
	if(A!=NULL)//checking for success of memory allocation for matrix A double pointer
	{
		if(!fillMatrix(A,1, numRows))//check if matrix A is filled with valid values
		{
			printf("matrix population unsuccessful\n");
			return -1;
		}
	}
	else//malloc error in allocating memory for double pointer
	{
		printf("malloc error\n");
		return -1;
	}

	//Creating memory for matrix B
	double ** B = (double **)malloc(numRows*sizeof(double *));//allocating memory for matrix B
	if(B!=NULL)//checking for success of memory allocation for matrix B double pointer
	{
		if(!fillMatrix(B,1, numRows))//check if matrix B is filled with valid values
		{
			printf("matrix population unsuccessful\n");
			return -1;
		}
	}
	else//malloc error in allocating memory for double pointer
	{
		printf("malloc error\n");
		return -1;
	}

	//Creating memory for matrix C
	double ** C = (double **)malloc(numRows*sizeof(double *));//allocating memory for matrix C
	if(C!=NULL)//checking for success of memory allocation for matrix C double pointer
	{
		if(!fillMatrix(C,0, numRows))//check if matrix C is filled with valid values
		{
			printf("matrix population unsuccessful\n");
		}
	}
	else//malloc error in allocating memory for double pointer
	{
		printf("malloc error\n");
		return -1;
	}

	//Code below is used to print Matrices A, B, and C [Before multiplication]

	//Print Matrix A
	printf("Matrix A:\n");
	if(!printMatrix(A, numRows))//printing matrix A and checking for successful function execution
	{
		printf("invalid print operation\n");
	}

	//Print Matrix B
	printf("Matrix B:\n");
	if(!printMatrix(B, numRows))//printing matrix A and checking for successful function execution
	{
		printf("invalid print operation\n");
	}

	//Print Matrix C [before multiplication]
	printf("Matrix C [Before multiplication]:\n");
	if(!printMatrix(C, numRows))//printing matrix A and checking for successful function execution
	{
		printf("invalid print operation\n");
	}

	//Perform sequential matri multiplication
	double seq_time = sequentialProduct(A,B,C, numRows);//assign variable with time taken for sequential multiplication
	if(seq_time<0)//perform sequential product of A and B, store in C and also check for success of operation
	{
		printf("unsuccessful matrix multiplication\n");
	}

	//print matrix C after sequential multiplication
	printf("Matrix C [After Sequential multiplication]:\n");
	if(!printMatrix(C, numRows))//printing matrix A and checking for successful function execution
	{
		printf("invalid print operation\n");
	}

	//Perform parallel[static mapping] computation of matrix product and store time for parallel computation
	double statMap_time = staticMapping_Product(A, B, C, numRows, numthreads);//store operation time in variable
	if(statMap_time<0)//perform static mapping product of A and B, store in C and also check for success of operation
	{
		printf("unsuccessful matrix multiplication\n");
	}

	//Print matrix C after parallel [static mapping] computation
	printf("Matrix C [After Static mapping multiplication]:\n");
	if(!printMatrix(C, numRows))//printing matrix A and checking for successful function execution
	{
		printf("invalid print operation\n");
	}

	//Perform parallel[dynamic mapping] computation of matrix product and store time for parallel computation
	double dynMap_time = dynamicMapping_Product(A, B, C, numRows, numthreads, global_count);//store operation time in variable
	if(dynMap_time<0)//perform static mapping product of A and B, store in C and also check for success of operation
	{
		printf("unsuccessful matrix multiplication\n");
	}

	//Print matrix C after parallel [dynamic mapping] computation
	printf("Matrix C [After Dynamic mapping multiplication]:\n");
	if(!printMatrix(C, numRows))//printing matrix A and checking for successful function execution
	{
		printf("invalid print operation\n");
	}

	if(!freeMatrix(C, numRows))//freeing pointers pointed to by double pointer C and checking for successful operation
	{
		printf("invalid operation\n");
		return -1;
	}
	free(C);//freeing memory allocated to double pointer C

	if(!freeMatrix(B, numRows))//freeing pointers pointed to by double pointer B and checking for successful operation
	{
		printf("invalid operation\n");
		return -1;
	}
	free(B);//freeing memory allocated to double pointer B

	if(!freeMatrix(A, numRows))//freeing pointers pointed to by double pointer C and checking for successful operation
	{
		printf("invalid operation\n");
		return -1;
	}
	free(A);//freeing memory allocated to double pointer A

	//Summarizing operation times
	printf("Sequential Product time is %lf\n", seq_time);
	printf("Static Mapping parallel product time is %lf\n", statMap_time);
	printf("Dynamic Mapping parallel product time is %lf\n", dynMap_time);

	double speedupK_dyn = speedupKdyn(seq_time, dynMap_time);//store value of  speedup(K) for dynamic mapping
	double speedupK_stat = speedupKstat(seq_time, statMap_time);//store value for speedup(K) for static mapping
	if(speedupK_dyn==-1 || speedupK_stat==-1)//check for successful computation of speedup(K) values
	{
		printf("invalid operation\n");
		return -1;
	}
	else
	{
		//print speedup(K) values
		printf("SpeedupK value relating to Static mapping is %lf\n",speedupK_stat);
		printf("SpeedupK value relating to Dynamic mapping is %lf\n",speedupK_dyn);
	}
	return 1;
}



