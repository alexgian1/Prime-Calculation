#include <stdio.h>
#include <math.h>
#include <time.h>
#define MINNUM 3990000000  
#define MAXNUM 4010000000 
int main(){
	printf("Checking range [%lu,%lu] for primes\n",MINNUM,MAXNUM);
	double Tstart,Tstop;  /*Counting time elapsed*/
	int primeCount;
	
	/* Deterministic Test*/
	Tstart = ((float) clock())/CLOCKS_PER_SEC;
	primeCount=0;
	unsigned int current; /*Number currently being tested*/
	int curDivs;  /*Counts dividers of every number*/
	for (current=MINNUM+1; current<=MAXNUM; current+=2){  /*Skips even numbers*/
		curDivs=0;
		for (int d=3;d*d<=current;d+=2){  /*divider testing ends at the sq.root of current/even numbers skipped */
			if (current%d==0){
				curDivs++;
				break;
			}	
		}
		if (curDivs==0){
			primeCount++;
		}
	}
	Tstop = ((float) clock())/CLOCKS_PER_SEC;
	printf("Deterministic algorithm: Found %d primes in %.2f seconds\n",primeCount,Tstop-Tstart);
	
	/*Miller-Rabin Test*/
	Tstart = ((float) clock())/CLOCKS_PER_SEC;
	primeCount = 0; 
	int a,exit,k,r;  
	unsigned long exp,d;
	unsigned long long x,base;
	for (unsigned int n=MINNUM+1;n<=MAXNUM;n+=2){  /*The described algorithm begins here.
		Variable names used in this program are the same as in the described algorithm (n,r,d etc..)*/
		
		if (n%3==0 || n%5==0 || n%7==0){      //skips testing for multiples of 3,5,7
			continue;
		}
		
		d = n-1;   /*Writes (n-1) as (2^r * d)  */
		r=0;
		while (d%2==0){
			r++;
			d/=2;
		}
			
		
		exit=0; /*Boolean role. When exit is 1 the loop stops*/
		a = 2;  /*takes values {2,7,61}*/
		k = 1; /*counter for the loop.The loop is repeated maximum 3 times */
		
		while (k<=3 && exit==0){
			
			base=a;          /*calculates (a^d) mod n */
			exp = d;
			x = 1;
			base %= n;
			while (exp>0){
				if(exp%2 ==1){
					x = (x*base) % n;
				}
				exp = exp>>1;
				base = (base*base) % n;
			}
			
			if (x==1 || x==n-1){
				if (a == 61) exit=1;     /*61 is the last value a can take */
				else if (a == 7) a = 61;   /*changes the value of a to the next (2->7->61) and repeats the loop*/
				else if (a == 2) a = 7;
				continue;
			}
			for (int i = 1;i<=r-1;i++){
				x = ((x%n)*(x%n)) % n;  /*equal to (x*x) % n */
				if (x==n-1){
					if (a == 61) exit=1;
					else if (a == 7) a = 61;  /*same as previous value change of a */
					else if (a == 2) a = 7;
					continue;
					
				}
			}
			k++;	
		}
		if (exit==1){
			primeCount++;
		}	
	}
	Tstop = ((float) clock())/CLOCKS_PER_SEC;
	printf("Miller-Rabin algorithm: Found %d primes in %.2f seconds\n",primeCount,Tstop-Tstart);
}




















