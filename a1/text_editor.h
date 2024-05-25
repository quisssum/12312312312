#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

typedef struct Line {
    char *text;
    struct Line *next;
} Line;

void appendText(Line **head, const char *text);
void startNewLine(Line **head);
void saveToFile(Line *head, const char *filename);
void loadFromFile(Line **head, const char *filename);
void printCurrentText(Line *head);
void insertText(Line *head, int lineNumber, int charIndex, const char *text);
void searchText(Line *head, const char *query);
void clearText(Line **head);
void removeNewline(char *str);

#endif

