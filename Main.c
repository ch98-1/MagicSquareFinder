//Copyright (C) 2016  Corwin Hansen
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>




//randomly try to find a working magic square

#define MAXINT unsigned long long int//integer to use for calculation


MAXINT count;//trial counter


inline MAXINT power(unsigned long long base, unsigned long long exponent);//rase base by exponent
inline void powertable(MAXINT *lookup, MAXINT max, MAXINT power);//fill the powertable
inline void fillsq(MAXINT *magicsq, MAXINT max, MAXINT d);//fill magic square with random values below max
inline void convertsq(const MAXINT *magicsq, MAXINT *psq, const MAXINT *lookup, MAXINT d);//convert the magic square by raising it to power on lookup table
inline MAXINT checksq(const MAXINT *magicsq, MAXINT d);//returns the magic constant if it is a magic sqare, and 0 if not.
inline void printsq(const MAXINT *magicsq, MAXINT d);//print out the magic square
inline void setuprand(void);//set up random number generator
inline MAXINT randv(MAXINT max);//get random value between 0 and max
void printcount(void);//print how many tries it did


int main(int argc, char *argv[]){
	count = 0;
	atexit(printcount);
	MAXINT d, p, m;//dimention, power, and max size
	if(argc != 4) printf("%s <dimention> <power> <max>\nNormal magic square is 3 for dimention and 1 for power and 99 for max \nIt will print out the generated magic square when finished.", argv[0]);
	d = atoll(argv [1]);//read input values
	p = atoll(argv [2]);
	m = atoll(argv [3]);

	if (d*d <= m){//if not enough number to fill the magic square
		printf("Can't fill magic square\n");
		exit(EXIT_FAILUARE);
	}

	MAXINT *magicsq = malloc(sizeof(MAXINT)*d*d);//magic square itself
	MAXINT *psq = malloc(sizeof(MAXINT)*d*d);//magic square converted
	MAXINT *lookup = malloc(sizeof((MAXINT)*(m+1)));//lookup table for powers of numbers
	powertable(lookup, m, p);//fill lookup table

	do{//fill, convert, and check square until success
		fillsq(magicsq, m, d);
		convertsq(magicsq, psq, lookup, d);
		count++;
	} while (checksq(psq, d) == 0);
	printsq(magicsq, d);//print magic square
	printf("magic constant = %llu", checksq(psq, d));//print magic constant

	exit(EXIT_SUCCESS);
}


inline MAXINT power(MAXINT base, MAXINT exponent){//rase base by exponent
	while(exponent > 0){
		base *= base;
		exponent--;
	}
	return base;
}


inline void powertable(const MAXINT *lookup, MAXINT max, MAXINT power){//fill the powertable
	while(max >= 0){
		lookup[max] = power(max, power);
		max--;
	}
	return 0;
}


inline void fillsq(MAXINT *magicsq, MAXINT max, MAXINT d){//fill magic square with random values below max

}


inline void convertsq(const MAXINT *magicsq, MAXINT *psq, const MAXINT *lookup, MAXINT d){//convert the magic square by raising it to power on lookup table

}


inline MAXINT checksq(const MAXINT *magicsq, MAXINT d){//returns the magic constant if it is a magic sqare, and 0 if not.

}


inline void printsq(const MAXINT *magicsq, MAXINT d){//print out the magic square

}


inline void setuprand(void){//set up random number generator

}


inline MAXINT randv(MAXINT max){//get random value between 0 and max

}


void printcount(void){//print how many tries it did
	printf("Tries %llu times", count);
}



