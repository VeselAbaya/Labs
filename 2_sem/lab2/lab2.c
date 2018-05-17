#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INIT_SIZE 10
#define FACTOR 1.5
#define TAG_SIZE 10

typedef char* type;

typedef struct Stack {
    type* data;
    int size;
    int capacity;
} Stack; 

Stack stack_init() {
    Stack stack;
    stack.data = (type*)malloc(INIT_SIZE*sizeof(type));
    stack.size = 0;
    stack.capacity = INIT_SIZE;

    return stack;
}

int push(Stack* stack, type el) {
    if (stack->size == stack->capacity) { 
        if (stack->data = realloc(stack->data, stack->capacity * FACTOR)) { 
            stack->capacity *= FACTOR;
            stack->data[stack->size++] = el;
        } else {
            fprintf(stderr, "Out of memory");
            return 0;
        }
    } else { 
        stack->data[stack->size++] = el;
        return 1;
    }
}

type pop(Stack* stack) {
    return stack->data[stack->size-- - 1];
}

type top(Stack* stack) {
    return stack->data[stack->size - 1];
}

int isEmpty(Stack* stack) {
    return !stack->size;
}

void shrink_to_fit(Stack* stack) {
    stack->data = realloc(stack->data, stack->size);
}

void free_stack(Stack* stack) {
    free(stack->data);
}

int main() {
    Stack stack = stack_init();

    char ch;
    char* tag = (char*)malloc(TAG_SIZE);
    int tag_capacity = TAG_SIZE;
    int tag_size = 0;
    while ((ch = getchar()) != '\n') {
        if (ch == '<') {
            while ((ch = getchar()) != '>' && ch != ' ') {
                if (tag_size == tag_capacity - 1) {
                    tag = realloc(tag, tag_capacity*FACTOR);
                    tag_capacity *= FACTOR;
                }

                tag[tag_size++] = ch;
            }

            tag[tag_size++] = '\0';

            if (tag[0] == '/') {
                if (isEmpty(&stack)) { 
                    printf("wrong\n");
                    free_stack(stack);
                    return 0;
                } else if (strcmp(pop(&stack), &tag[1]) == 0) {} 
                else {
                    printf("wrong\n");
                    free_stack(stack);
                    return 0;
                }
            } else {
                if (strcmp(tag, "br") != 0 && strcmp(tag, "hr") != 0) {
                    char* tag_copy = (char*)malloc(tag_size);
                    for (int i = 0; i != tag_size; ++i) {
                        tag_copy[i] = tag[i];
                    }

                    push(&stack, tag_copy);
                }
            }
        }

        tag_size = 0;
    }

    printf("correct\n");
    free_stack(stack);
    return 0;
}