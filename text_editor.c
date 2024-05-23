#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text_editor.h"

// Видалити новий рядок
void removeNewline(char *str) {
    size_t length = strlen(str);
    if (length > 0 && str[length - 1] == '\n') {
        str[length - 1] = '\0';
    }
}

// Додавання тексту до останнього рядка
void appendText(Line **head, const char *text) {
    if (*head == NULL) {
        startNewLine(head);
    }
    Line *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    size_t newLength = strlen(current->text) + strlen(text) + 1;
    current->text = realloc(current->text, newLength);
    strcat(current->text, text);
}

// Додати новий рядок
void startNewLine(Line **head) {
    Line *newLine = malloc(sizeof(Line));
    newLine->text = malloc(1);
    newLine->text[0] = '\0';
    newLine->next = NULL;

    if (*head == NULL) {
        *head = newLine;
    } else {
        Line *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newLine;
    }
}

// Зберегти текст у файл
void saveToFile(Line *head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    Line *current = head;
    while (current != NULL) {
        fprintf(file, "%s\n", current->text);
        current = current->next;
    }
    fclose(file);
}

// Завантажити текст з файлу
void loadFromFile(Line **head, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    clearText(head);
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        removeNewline(buffer);
        startNewLine(head);
        appendText(head, buffer);
    }
    fclose(file);
}

// Друк поточного тексту
void printCurrentText(Line *head) {
    Line *current = head;
    while (current != NULL) {
        printf("%s\n", current->text);
        current = current->next;
    }
}

// Вставити текст на вказану позицію
void insertText(Line *head, int lineNumber, int charIndex, const char *text) {
    Line *current = head;
    for (int i = 0; i < lineNumber; ++i) {
        if (current == NULL) {
            fprintf(stderr, "Invalid line number\n");
            return;
        }
        current = current->next;
    }
    if (charIndex < 0 || charIndex > (int)strlen(current->text)) {
        fprintf(stderr, "Invalid character index\n");
        return;
    }
    size_t newLength = strlen(current->text) + strlen(text) + 1;
    char *newText = malloc(newLength);
    strncpy(newText, current->text, charIndex);
    newText[charIndex] = '\0';
    strcat(newText, text);
    strcat(newText, current->text + charIndex);
    free(current->text);
    current->text = newText;
}

// Пошук тексту
void searchText(Line *head, const char *query) {
    Line *current = head;
    int lineNumber = 0;
    while (current != NULL) {
        char *pos = strstr(current->text, query);
        while (pos != NULL) {
            printf("Found at line %d, character %ld\n", lineNumber, pos - current->text);
            pos = strstr(pos + 1, query);
        }
        current = current->next;
        lineNumber++;
    }
}

// Очистити текст
void clearText(Line **head) {
    Line *current = *head;
    while (current != NULL) {
        Line *next = current->next;
        free(current->text);
        free(current);
        current = next;
    }
    *head = NULL;
}

