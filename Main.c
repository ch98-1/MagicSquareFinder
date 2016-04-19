//Copyright (C) 2016  Corwin Hansen
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>




//randomly try to find a working magic square

#define MAXINT unsigned long long int//integer to use for calculation
//#define STARTZERO //start from 0 insted of 1


MAXINT count;//trial counter


static inline MAXINT power(unsigned long long base, unsigned long long exponent);//rase base by exponent
static inline void powertable(MAXINT *lookup, MAXINT max, MAXINT pow);//fill the powertable
static inline void fillsq(MAXINT *magicsq, MAXINT max, MAXINT ds);//fill magic square with random values below max
static inline void convertsq(const MAXINT *magicsq, MAXINT *psq, const MAXINT *lookup, MAXINT ds);//convert the magic square by raising it to power on lookup table
static inline MAXINT checksq(const MAXINT *magicsq, MAXINT d);//returns the magic constant if it is a magic sqare, and 0 if not.
static inline void printsq(const MAXINT *magicsq, MAXINT d);//print out the magic square
static inline void setuprand(void);//set up random number generator
static inline MAXINT randv(MAXINT max);//get random value between 1 (or 0) and max
void printcount(void);//print how many tries it did


int main(int argc, char *argv[]){
	count = 0;
	atexit(printcount);

	setuprand();//initialise random number generator

	MAXINT d, p, m, ds;//dimention, power, max size, and d squared
	if(argc != 4){
		printf("%s <dimention> <power> <max>\nNormal magic square is 3 for dimention, 1 for power, and 15 for max \nIt will print out the generated magic square when finished.\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	d = atoll(argv [1]);//read input values
	p = atoll(argv [2]);
	m = atoll(argv [3]);
	ds = d*d;

#ifdef STARTZERO //macro choice between including zero or not
	if (ds - 1 > m){//if not enough number to fill the magic square
		printf("Can't fill magic square\n");
		exit(EXIT_FAILURE);
	}
#else
	if (ds > m){//if not enough number to fill the magic square
		printf("Can't fill magic square\n");
		exit(EXIT_FAILURE);
	}
#endif

	MAXINT *magicsq = malloc(sizeof(MAXINT)*ds);//magic square itself
	MAXINT *psq = malloc(sizeof(MAXINT)*ds);//magic square converted
	MAXINT *lookup = malloc(sizeof(MAXINT)*(m+1));//lookup table for powers of numbers
	powertable(lookup, m, p);//fill lookup table

	do{//fill, convert, and check square until success
		fillsq(magicsq, m, ds);
		convertsq(magicsq, psq, lookup, ds);
		count++;
	} while (checksq(psq, d) == 0);
	printsq(magicsq, d);//print magic square
	printf("magic constant = %llu\n", checksq(psq, d));//print magic constant

	exit(EXIT_SUCCESS);
}


static inline MAXINT power(MAXINT base, MAXINT exponent){//rase base by exponent
	while(exponent > 1){
		base *= base;
		exponent--;
	}
	return base;
}


static inline void powertable(MAXINT *lookup, MAXINT max, MAXINT pow){//fill the powertable
	while(1){
		lookup[max] = power(max, pow);
		if(max == 0) break;
		max--;
	}
}


static inline void fillsq(MAXINT *magicsq, MAXINT max, MAXINT ds){//fill magic square with random values below max
	MAXINT dsc = 0;
	while(dsc < ds){
		while(1){
			MAXINT rn = randv(max);
			MAXINT i;
			int stat = 1;
			for(i = 0; i < dsc ;i++){//check for matching
				if (rn == magicsq[i]){
					stat = 0;
					break;
				}
			}
			if(stat == 1) {
				magicsq[dsc] = rn;
				break;//break loop if none is matching
			}
		}
		dsc++;
	}
}


static inline void convertsq(const MAXINT *magicsq, MAXINT *psq, const MAXINT *lookup, MAXINT ds){//convert the magic square by raising it to power on lookup table
	while (1){
		ds--;
		psq[ds] = lookup[magicsq[ds]];//raise values to it's powers
		if (ds == 0) break;
	}
}


static inline MAXINT checksq(const MAXINT *magicsq, MAXINT d){//returns the magic constant if it is a magic sqare, and 0 if not.
	MAXINT i, j;
	MAXINT mc = 0;//magic constant

	for (j = 0; j < d; j++){//find initial value
		mc += magicsq[j];
	}

	for (i = 1; i < d; i++){//rows
		MAXINT ms = 0;//magic constant sum
		for (j = 0; j < d; j++){
			ms += magicsq[d*i + j];
		}
		if(mc != ms) return 0;
	}

	for (j = 0; j < d; j++){//columns
		MAXINT ms = 0;
		for (i = 0; i < d; i++){
			ms += magicsq[d*i + j];
		}
		if(mc != ms) return 0;
	}

	MAXINT ms = 0;
	for (i = 0; i < d; i++){//diagonal 1
		ms += magicsq[d*i + i];
	}
	if(mc != ms) return 0;

	ms = 0;
	for (i = 0; i < d; i++){
		ms += magicsq[d*i + (d - i - 1)];
	}
	if(mc != ms) return 0;

	return mc;
}


static inline void printsq(const MAXINT *magicsq, MAXINT d){//print out the magic square
	MAXINT i, j;
	for (i = 0; i < d; i++){//rows
		for (j = 0; j < d; j++){
			printf("%llu ", magicsq[d*i + j]);
		}
		printf("\n");
	}
}


static inline void setuprand(void){//set up random number generator
	srand((unsigned) time(NULL));
}


static inline MAXINT randv(MAXINT max){//get random value between 1 and max
#ifdef STARTZERO //macro choice between including zero or not
	return ((MAXINT)rand())%(max+1);
#else
	return (((MAXINT)rand())%(max))+1;
#endif
}


void printcount(void){//print how many tries it did
	printf("Tried %llu times\n", count);
}



