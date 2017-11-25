#include <stdio.h>

//defines
#define M N+5
#define N 10

#define SUM(a, b) a+b
#define MUL(a, b) a*b

int main() {
	//main function
	int sum1 = SUM(N, M);
	int sum2 = MUL(SUM(1, 2), SUM(3, 4));
	printf("%d %d", sum1, sum2);
	return 0;
	// int sum1 = 10 +10 +5;
	// int sum2 = 1 +2*3 +4;
	// printf("%d %d", sum1, sum2);
	// return 0;
}


