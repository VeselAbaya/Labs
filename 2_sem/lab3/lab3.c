#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h> 

int func_file(char const* path, char const* op) {
    FILE* file = fopen(path, "r");
    if (file) {
        int res;
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

int func(char const* path, char const* op) {
    DIR* dir = opendir(path);
    if (dir) {
        char local_path[PATH_MAX + 1];
        strcpy(local_path, path);
        strcat(local_path, "/");

        char dirent_path[PATH_MAX + 1];

        struct dirent* dirent;
        int res = (strcmp(op, "add") == 0) ? 0 : 1;
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

int main() {
    DIR* dir = opendir("tmp");
    struct dirent* dirent;
    while (dirent = readdir(dir)) {
        if (strcmp(dirent->d_name, ".") != 0 && strcmp(dirent->d_name, "..") != 0) {
            char path[PATH_MAX + 1] = "tmp";
            strcat(path, "/");  
            strcat(path, dirent->d_name);

            FILE* result = fopen("result.txt", "w"); 
            fprintf(result, "%d\n", func(path, dirent->d_name));
            fclose(file);
        }
    }
    
    closedir(dir);
    return 0;
}