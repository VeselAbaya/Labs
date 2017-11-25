#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_str(char* s) {
	for(int i = 0; s[i] != '\0'; ++i) {
		putchar(s[i]);
	}
}

char* get_name() {
	char* name = (char*) malloc(100 * sizeof(char));
	int c = 0;
	int i = 0;
	for (;(c = getchar()) != '\n' && i != 99; ++i) {
		name[i] = c;
	} name[++i] = '\0';
	return name;
}

int main() {
	char* name = get_name();
	char* hello = "hello, ";
  strncat(hello, name, 107);
  print_str(hello);
	return 0;
}















// #include <stdio.h>

// int main() {
// 	int c;
// 	while ((c = getchar()) != EOF) {
// 		if (c != ' ') {putchar(с);}
// 		else {
// 			while (c == ' ') {c = getchar();}
// 			putchar(c);
// 		}
// 	}
// }

// упр. № 1.18
// #include <stdio.h>

// int main() {
// 	int c;
// 	while ((c = getchar()) != EOF) {
// 		if (c != '\t') { 
// 			putchar(c); 
// 		} else { 
// 			putchar(' '); 
// 			continue;
// 		}

// 		if (c == ' ' || c == '\t') {
// 			if ((c = getchar()) == ' ' || c == '\t') {
// 				while (c == ' ' || c == '\t') { c = getchar(); }
// 				putchar(c);
// 			} else { putchar(c); }
// 		} else if (c == '\n') {
// 			if ((c = getchar()) == '\n') {
// 				while (c == '\n') { c = getchar(); }
// 				putchar(c);
// 			} else { putchar(c); }
// 		}
// 	}
// 	return 0;
// }


// // detab
// #include <stdio.h>

// #define TAB 4

// int main() {
// 	int c = 0;
// 	while ((c = getchar()) != EOF) {
// 		if (c != '\t') {
// 			putchar(c);
// 		} else {
// 			for (int i = 0; i != TAB; ++i) {
// 				putchar(' ');
// 			}
// 		}
// 	}
// 	return 0;
// }

// // entab
// #include <stdio.h>

// #define TAB 4

// int main() {
// 	int space_counter = 0;
// 	int c = 0;
// 	while ((c = getchar()) != EOF) {
// 		if (c != ' ') { putchar(c); }
// 		else {
// 			++space_counter;
// 			for (int i = 1; i != TAB && (c = getchar()) == ' '; ++i) { ++space_counter; }
// 			if (space_counter == TAB) {
// 				putchar('\t');
// 				space_counter = 0;
// 			} else {
// 				for (int i = 0; i != space_counter; ++i) {
// 					putchar(' ');
// 				}
// 				putchar(c);
// 				space_counter = 0;
// 			}
// 		}
// 	}
// 	return 0;
// }


// //htoi
// #include <stdio.h>
// #include <assert.h>
// #include <math.h>
// #include <ctype.h>
// #include <string.h>

// enum ABCDEF {a = 10, b, c, d, e, f};

// unsigned int htoi(char const sixteen_base[]) {
// 	assert(sixteen_base[0] == '0' && sixteen_base[1] == 'x' || sixteen_base[1] == 'X');
// 	enum ABCDEF abcdef;
// 	int razr = 0;
// 	unsigned int result = 0;
// 	int size = strlen(sixteen_base);
// 	for (int i = size - 1; i != 1; --i) {
// 		if (isdigit(sixteen_base[i])) { 
// 			result += pow(16, razr) * (sixteen_base[i] - '0');
// 		} else {
// 			abcdef = tolower(sixteen_base[i]) - 87;
// 			printf("%d\n", abcdef);
// 			result += pow(16, razr) * abcdef; } 
// 		++razr;
// 	}
// 	return result;
// }

// int main() {
// 	char const input[] = "0x12f";
// 	printf("%d\n", htoi(input));
// 	return 0;
// }

// // squeeze
// #include <stdio.h>

// void squeeze(char s1[], char const s2[]) {
// 	int i = 0;
// 	int j = 0;
// 	int k = 0;
// 	for (; s1[i] != '\0'; ++i) {
// 		for (k = 0; s1[i] != s2[k] && s2[k] != '\0'; ++k) { ; }
// 		if (s2[k] == '\0') {
// 			s1[j++] = s1[i];
// 		}
// 	}
// 	s1[j] = '\0';
// }

// int main() {
// 	char s1[11] = "I love you.";
// 	char s2[3] = "oe";
// 	squeeze(s1, s2);
// 	printf("%s\n", s1);
// 	return 0;
// }

// // any
// #include <stdio.h>

// int strbrk(char const s1[], char const s2[]) {
// 	int j = 0;
// 	for (int i = 0; s1[i] != '\0'; ++i) {
// 		for (j = 0; s1[i] != s2[j] && s2[j] != '\0'; ++j) { ; }
// 		if (s2[j] != '\0') {
// 			return i;
// 		}
// 	}
// 	return -1;
// }

// int main() {
// 	char s1[10] = "I love you";
// 	char s2[3] = "u";
// 	printf("%d\n", strbrk(s1, s2));
// 	return 0;
// }

// // lower через тернарный оператор
// #include <stdio.h>
// void lower(char string[]) {
// 	for (int i = 0; string[i] != '\0'; ++i) {
// 		;// string[i] = (string[i] >= 97 && string[i] <=122) ? string[i] : 
// 	}
// }

// int main() {
// 	int A = 'A';
// 	int a = 'a';
// 	int z = 'z';
// 	printf("%d\n", A);
// 	printf("%d\n", a);
// 	printf("%d\n", z);
// 	return 0;
// }

// // escape
// #include <stdio.h>

// void escape(char s[], char t[]) {
// 	int j = 0;
// 	for (int i = 0; s[i] != '\0'; ++i) {
// 		switch (s[i]) {
// 			case '\n': 
// 				t[j++] = '\\';
// 				t[j++] = 'n';
// 				break;
// 			case '\t':
// 				t[j++] = '\\';
// 				t[j++] = 't'; 
// 				break;
// 			default: 
// 				t[j++] = s[i];
// 				break;
// 		}
// 	}
// }

// // expand
// #include <stdio.h>
// #include <assert.h>
// void expand(char s1[], char s2[]) {
// 	char begin;
// 	char end;
// 	int j = 0;
// 	for (int i = 0; s1[i] != '\0'; ++i) {
// 		if (s1[i + 1] == '-') {
// 			begin = s1[i];
// 			end = s1[i++ + 2];
// 			assert(begin <= end);
// 			for (; begin != end; ++begin) {
// 				s2[j++] = begin;
// 			} 
// 		} else { s2[j++] = s1[i]; }
// 	}
// }

// int main() {
// 	char s1[10] = "v-c";
// 	char s2[100];
// 	expand(s1, s2);
// 	printf("%s\n", s2);
// 	return 0;
// }

// // itob (Segmentation fault)
// #include <stdio.h>

// void itob(int n, char s[], int base) {
// 	int i = 0;
// 	do {
// 		s[i++] = n % base;
// 		n /= base;
// 	} while (n % base != 1 && n % base != 0);
// 	s[i] = n % base;
// 	s[++i] = '1';
// }

// int main() {
// 	int n = 75;
// 	char s[15];
// 	int base = 8;
// 	itob(n, s, base);
// 	printf("%s\n", s);
// 	return 0;
// }