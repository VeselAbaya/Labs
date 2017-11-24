#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define GOLDSEC 1.62
#define END "Dragon flew away!"
#define FIRST_ALLOC_LEN 50

int is_end(char const* text, char const* end);

int buffer_realloc(char* text, int text_len);

int main() {
    int before_edit = 0; 
    int after_edit = 0;
    char* text = (char*)calloc(FIRST_ALLOC_LEN, sizeof(char));
    int text_len = FIRST_ALLOC_LEN;
    char* end = END;
    int end_size = strlen(end);

    int sentence_begin = 0; // Индекс начала текущего предложения
    int text_index = 0;
    char c = 0;
    while (c = getchar()) {
        if (text_index == sentence_begin && (c == '\t' || c == '\n' || c == ' ')) { continue; }

        if (c != '.' && c != ';' && c != '?' && c != '7') {
            if (text_index == text_len) { text_len = buffer_realloc(text, text_len); }

            text[text_index++] = c;

            // Проверка на конец ввода
            if (c == end[end_size - 1] && is_end(text, end)) {
                printf("%s\n", text);
                break;
            }
        } else if (c == '7') { // Удаление предложения с семеркой
            while ((c = getchar()) != '.' && c != ';' && c != '?');
            ++before_edit;

            text_index = sentence_begin; // Передвинули текущий индекс на начало предложения
        } else { // В случае конца предложения
            ++after_edit;
            ++before_edit;

            if (text_index == text_len - 2) { text_len = buffer_realloc(text, text_len); } // -2 чтобы в текст вместилось с, '\n' и первый символ след. предложения
            
            text[text_index++] = c;
            text[text_index++] = '\n';

            sentence_begin = text_index;
        }
    }

    printf("Количество предложений до %d и Количество предложений после %d\n", before_edit, after_edit);

    free(text);

    return 0;
}

int is_end(char const* text, char const* end) {
    int text_size = strlen(text);
    int end_size = strlen(end);

    int j = end_size - 1;
    int i = 0;
    for (i = text_size - 1; i != text_size - end_size - 1; --i, --j) {
        if (text[i] != end[j]) { return 0; }
    }

    // Проверка на отсутсвие постфиксов 
    if (text[i - 1] != '.' && text[i - 1] != ';' && text[i - 1] != '?') { return 0; }

    return 1;
}

int buffer_realloc(char* text, int text_len) {
    text_len = text_len * GOLDSEC;
    text = realloc(text, text_len);
    text[(int)(text_len - 1)] = '\0';
    return text_len;
}