#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Описание структуры MusicalComposition
typedef struct MusicalComposition {
    char* name;
    char* author;
    int year;
    struct MusicalComposition* prev;
    struct MusicalComposition* next;
} MusicalComposition;

// LIST(MusicalCompositionList, MusicalComposition);

// Создание структуры MusicalComposition
MusicalComposition* createMusicalComposition(char* name, char* author, int year) {
    MusicalComposition* ret = (MusicalComposition*)malloc(sizeof(MusicalComposition));

    ret->name = name;
    ret->author = author;
    ret->year = year;
    ret->prev = NULL;
    ret->next = NULL;

    return ret;
}

// Функции для работы со списком MusicalComposition

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n) {
    MusicalComposition* head = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);

    MusicalComposition* prev = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    prev = head;

    MusicalComposition* cur = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    for (int i = 1; i != n; ++i) {
        cur = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        cur->prev = prev;
        cur->prev->next = cur;
        cur->next = NULL;
        prev = cur;
    }

    return head;
}

void push(MusicalComposition* head, MusicalComposition* element) {
    if (head == NULL) { head = element; return; } 

    MusicalComposition* cur = head;
    
    while (cur->next) { cur = cur->next; }
    element->prev = cur;
    cur->next = element;
    element->next = NULL;

}

void removeEl(MusicalComposition* head, char* name_for_remove) {
    if (head == NULL) { return; }

    MusicalComposition* cur = head;

    if (strcmp(head->name, name_for_remove) == 0) {
        head->next->prev = NULL;
        free(head);
        return;
    }

    while (cur->next) {
        if (strcmp(cur->name, name_for_remove) == 0) { 
            cur->prev->next = cur->next;
            cur->next->prev = cur->prev;
            free(cur);
            return;
        }

        cur = cur->next;
    }

    if (strcmp(cur->name, name_for_remove) == 0) {
        cur->prev->next = NULL;
        free(cur);
    }
}

int count(MusicalComposition* head) {
    if (head == NULL) { return 0; }
    
    MusicalComposition* cur = head;    
    int ret = 1;
    while (cur = cur->next) { ++ret; }

    return ret;
}

void print_names(MusicalComposition* head) {
    if (head == NULL) { return ; }

    MusicalComposition* cur = head;
    do {
        printf("%s\n", cur->name);
    } while (cur = cur->next);
}

int main(){
    int length;
    scanf("%d\n", &length);  

    char** names = (char**)malloc(sizeof(char*)*length);
    char** authors = (char**)malloc(sizeof(char*)*length);
    int* years = (int*)malloc(sizeof(int)*length);

    for (int i=0;i<length;i++) {
        char name[80];
        char author[80];

        fgets(name, 80, stdin);
        fgets(author, 80, stdin);
        fscanf(stdin, "%d\n", &years[i]);

        (*strstr(name,"\n"))=0;
        (*strstr(author,"\n"))=0;

        names[i] = (char*)malloc(sizeof(char*) * (strlen(name)+1));
        authors[i] = (char*)malloc(sizeof(char*) * (strlen(author)+1));

        strcpy(names[i], name);
        strcpy(authors[i], author);
    }

    MusicalComposition* head = createMusicalCompositionList(names, authors, years, length);
    char name_for_push[80];
    char author_for_push[80];
    int year_for_push;

    char name_for_remove[80];

    fgets(name_for_push, 80, stdin);
    fgets(author_for_push, 80, stdin);
    fscanf(stdin, "%d\n", &year_for_push);
    (*strstr(name_for_push,"\n"))=0;
    (*strstr(author_for_push,"\n"))=0;

    MusicalComposition* element_for_push = createMusicalComposition(name_for_push, author_for_push, year_for_push);

    fgets(name_for_remove, 80, stdin);
    (*strstr(name_for_remove,"\n"))=0;

    printf("%s %s %d\n", head->name, head->author, head->year);
    int k = count(head);

    printf("%d\n", k);
    push(head, element_for_push);

    k = count(head);
    printf("%d\n", k);

    removeEl(head, name_for_remove); 

    print_names(head);

    k = count(head);
    printf("%d\n", k);

    for (int i=0;i<length;i++) {
        free(names[i]);
        free(authors[i]);
    }

    free(names);
    free(authors);
    free(years);

    return 0;

}