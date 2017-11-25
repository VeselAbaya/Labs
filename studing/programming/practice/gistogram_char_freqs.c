#include <stdio.h>

int main() {
	int c;
	int amount = 0;
	int map[100];
	for (int i = 0; i != 100; ++i) {
		map[i] = 0;
	}

	while ((c = getchar()) != EOF) {
		if (c != '\n' && c != '\t' && c != ' ') { ++map[c - 32]; }
	}

	for (int i = 0; i != 100; ++i) {
		if (map[i] != 0) {
			printf("%3c ", i + 32);
			for (int j = 0; j != map[i]; ++j) { printf("-"); }
			printf("\n");
		}
	}
 	return 0;
}