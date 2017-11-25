#define LOWER -150
#define UPPER 150
#define STEP 20

#include <stdio.h>

int main() {
	float fahr, celsius;

	printf("%s\n", "Celsius---Fahr");

	celsius = LOWER;
	while (celsius <= UPPER) {
		fahr = (9.0 / 5.0) * celsius + 32.0;
		printf("%7.2f%8.2f\n", celsius, fahr);
		celsius += STEP;
	}
}