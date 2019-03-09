#include <stdio.h>
#include <math.h>
#include <time.h>
#include "primes.h"

int main(){
	long long unsigned start,stop;
	printf("Enter range to calculate primes: ");
	scanf("%llu %llu",&start,&stop);
	printf("Checking range [%llu,%llu] for primes\n",start,stop);
	determ(start,stop);
	if (start>62) milRab(start,stop); //milRab ignores some primes below 62
	return 0;
}


