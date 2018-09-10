#include <stdio.h>
#include <time.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>
#include <unistd.h>

#define MAX_FILES_AMOUNT 4
#define MAX_DIGITS_AMOUNT 4
#define MAX_DIGIT 5
#define DEFAULT_DEEP 3

long func_file(char const* path, char const* op) {
    FILE* file = fopen(path, "r");
    if (file) {
        long res;
        int number;

        if (strcmp(op, "add") == 0) {
            res = 0;
            while (fscanf(file, "%d", &number) == 1) {
                res += number;
            }

            fclose(file);
            return res;
        } else if (strcmp(op, "mul") == 0) {
            res = 1;
            while (fscanf(file, "%d", &number) == 1) {
                res *= number;
            }
            
            fclose(file);
            return res;
        }
    }
}

long func(char const* path, char const* op) {
    DIR* dir = opendir(path);
    if (dir) {
        char local_path[PATH_MAX + 1];
        strcpy(local_path, path);
        strcat(local_path, "/");

        char dirent_path[PATH_MAX + 1];

        struct dirent* dirent;
        long res = (strcmp(op, "add") == 0) ? 0 : 1;
        if (res == 0) {    
            while (dirent = readdir(dir)) {
                if (strcmp(dirent->d_name, ".") != 0 && strcmp(dirent->d_name, "..") != 0) {   
                    strcpy(dirent_path, local_path);
                    strcat(dirent_path, dirent->d_name);

                    if (dirent->d_type == DT_REG) {
                        res += func_file(dirent_path, "add");
                    } else {
                        res += func(dirent_path, dirent->d_name);
                    }
                }
            }
        } else {
            while (dirent = readdir(dir)) {
                if (strcmp(dirent->d_name, ".") != 0 && strcmp(dirent->d_name, "..") != 0) {
                    strcpy(dirent_path, local_path);
                    strcat(dirent_path, dirent->d_name);
                    if (dirent->d_type == DT_REG) {
                        res *= func_file(dirent_path, "mul");
                    } else {
                        res *= func(dirent_path, dirent->d_name);
                    }
                }
            }
        }

        closedir(dir);
        return res;
    } else {
        return 0;
    } 
}


void test_file_create(char* dir_path) {
    int files_amount = rand() % MAX_FILES_AMOUNT;
    
    for (int i = 0; i != files_amount; ++i) {
        char file_path[100] = "";
        strcpy(file_path, dir_path);
        strcat(file_path, "/file");
        char file_number[3] = "";
        sprintf(file_number, "%d", i);
        strcat(file_path, file_number);

        FILE* file = fopen(file_path, "w");
        if (file) {
            int digits_amount = rand() % MAX_DIGITS_AMOUNT;
            for (int i = 0; i != digits_amount; ++i) {
                int digit = rand() % MAX_DIGIT + 1;
                fprintf(file, "%d ", digit);
            }
        }

        fclose(file);
    }
}

void test_create(char* dir_path, int deep, int* flag) {
    if (deep == 0) {
        test_file_create(dir_path);
    } else {
        char new_path[100];
        strcpy(new_path, dir_path);
        strcat(new_path, "/");

        int add_or_mul = rand() % 4;
        if (*flag) {
            if (add_or_mul % 2 == 1) {
                strcat(new_path, "add");
                mkdir(new_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); } else {
                strcat(new_path, "mul");
                mkdir(new_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
            }
        } else if (add_or_mul == 0) {
            strcat(new_path, "add");
            mkdir(new_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        } else if (add_or_mul == 1) { 
            strcat(new_path, "mul");
            mkdir(new_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        } else {
            char add_path[100];
            strcpy(add_path, new_path);
            strcat(add_path, "add");
            mkdir(add_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
            test_file_create(add_path);
            test_create(add_path, deep-1, flag);

            strcat(new_path, "mul");
            mkdir(new_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        }
        
        if (*flag) {
            test_file_create(new_path);
            *flag = 0;
        }
        
        test_create(new_path, deep-1, flag);
    }
}

int main(int argc, char** argv) {
    // srand(time(NULL));

    // int deep = argc == 2 ? (int)strtol(argv[1], (char **)NULL, 10) : DEFAULT_DEEP; 

    // rmdir("testing");
    // mkdir("testing", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    // int flag = 1; // first func call
    // test_create("testing", deep, &flag);

    // DIR* dir = opendir("testing");
    // struct dirent* dirent;
    // while (dirent = readdir(dir)) {
    //     if (strcmp(dirent->d_name, ".") != 0 && strcmp(dirent->d_name, "..") != 0) {
    //         char path[PATH_MAX + 1] = "testing";
    //         strcat(path, "/");  
    //         strcat(path, dirent->d_name);

    //         printf("%ld\n", func(path, dirent->d_name));
    //         // FILE* result = fopen("result.txt", "w"); 
    //         // fprintf(result, "%d\n", func(path, dirent->d_name));
    //         // fclose(result);
	   // }
    // }
    
    // closedir(dir);
    // system("tree ./testing");
    rmdir("testing");
    return 0;
}
