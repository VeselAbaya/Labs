#include "print_str.h"

void print_str(char* s) {
	for(int i = 0; s[i] != '\0'; ++i) {
		putchar(s[i]);
	}
}
