/* The C program to simulate the random walk of the tourist
 * Author: Linglin Yu
 * Time: Oct. 31th, 2015
 */

#include<stdlib.h>
#include<stdio.h>

int main()
{
	long double probNblocks_Nsteps(int a, int b);
	int numberofSteps(int dist);

	int MAX = 23345678;		//sample MAX times
	int i;
	int N = 100;
	int nSteps, nBlocks;
	printf("input the number of steps the tourist will walk:\n");
	scanf("%d",&nSteps);
	printf("input the number of blocks the tourist away from the original point:\n");
	scanf("%d",&nBlocks);

// for Q1_question 1-4
	
	long double prob, total_prob=0.000;
	for(i=0; i<N; ++i)
	{
		prob = probNblocks_Nsteps(nBlocks, nSteps);
		printf("%.10lf\n",prob);
		total_prob += prob;
	}
	prob = total_prob/N;
	printf("the probability is: %.10lf\n",prob);

// for Q1_question 5-6
	N = 345234  
	int steps = 0, total_steps=0;
	long double averNsteps = 0.000;
	for(i=0; i<N; ++i)
	{
		steps = numberofSteps(nBlocks);
		printf("%d\n",steps);
		total_steps += steps;
	}
	averNsteps = (long double)total_steps/N;
	printf("the average number of steps is: %.10lf\n",averNsteps);

	return 0;
}

// function to count the steps required to reach the certain dist
int numberofSteps(int dist)
{
	int maxSteps = 2000000; //limit of steps
	int i, count = 0;
	int ns = 0, ew = 0;
	for(i=0; i<maxSteps; ++i)
	{
		double r = (double)rand()/RAND_MAX;
		if(r < 0.25)        //walk towards the north
			ns++;
		else if(r >=0.25 && r<0.50)
			ns--;			//walk towards the south
		else if(r >=0.50 && r<0.75)
			ew++;			//walk towards the east
		else
			ew--;			//walk towards the west
		if(abs(ns)+abs(ew) >= dist)
			return i+1;
	}
	return 0;
}

// function to get the probabilities:
// 1. at least nBlocks after nSteps;
// 2. ever at least nBlocks after nSteps;
// 3. ever east of East 1st Ave. but ends up west of West 1st Ave.
long double probNblocks_Nsteps(int nBlocks, int nSteps)
{
	int MAX = 2334567;
	int i, count = 0;
	for(i=0; i<MAX; ++i)
	{
		int	maxDist = 0;
		int maxEast = 0;
		int ns = 0, ew = 0;
		int j;
		for(j=0; j<nSteps; ++j)
		{
			double r = (double)rand()/RAND_MAX;
			if(r < 0.25)        //walk towards the north
				ns++;
			else if(r >=0.25 && r<0.50)
				ns--;			//walk towards the south
			else if(r >=0.50 && r<0.75)
				ew++;			//walk towards the east
			else
				ew--;			//walk towards the west
			maxDist = maxDist>(abs(ns)+abs(ew))? maxDist:(abs(ns)+abs(ew));
			maxEast = maxEast>ew? maxEast:ew;
		}
	//	if(abs(ns)+abs(ew) >= nBlocks) //at least nBlocks after nSteps
	//	if(maxDist >= nBlocks)  //ever at least nBlocks after nSteps
		if(maxEast>=1 && ew<=-1)//ever East 1st, AND end up west to West 1st
			count++;
	}
	printf("the total count is %d\n", count);
	long double prob = (long double)count/MAX;
	return prob;
}
