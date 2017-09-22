#include "get_name.h"

char* get_name() {
	char* name = (char*) malloc(100 * sizeof(char));
	char c = 0;
	int i = 0;

	for (;(c = getchar()) != '\n' && i != 99; ++i) {
		name[i] = c;
	} name[i] = '\0';

	return name;
}
