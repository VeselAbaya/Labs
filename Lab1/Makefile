all: main.o get_name.o print_str.o
	gcc get_name.o print_str.o main.o -o lab1
main.o: main.c 
	gcc -c main.c
get_name.o: get_name.c
	gcc -c get_name.c
print_str.o: print_str.c
	gcc -c print_str.c
clean:
	rm -f *.o lab1
