#include <stdio.h>
#include "text_editor.h"

void printMenu() {
    printf("Choose the command:\n");
    printf("1. Append text symbols to the end\n");
    printf("2. Start a new line\n");
    printf("3. Save to file\n");
    printf("4. Load from file\n");
    printf("5. Print current text\n");
    printf("6. Insert text by line and symbol index\n");
    printf("7. Search text\n");
    printf("8. Clear console\n");
    printf("0. Exit\n");
}

int main() {
    Line *head = NULL;
    int command;
    while (1) {
        printMenu();
        printf("> ");
        scanf("%d", &command);
        getchar(); // Видалити новий рядок після введення числа

        switch (command) {
            case 1:
            {
                char text[1024];
                printf("Enter text to append: ");
                fgets(text, sizeof(text), stdin);
                removeNewline(text);
                appendText(&head, text);
            }
                break;
            case 2:
                startNewLine(&head);
                printf("New line is started\n");
                break;
            case 3:
            {
                char filename[1024];
                printf("Enter the file name for saving: ");
                fgets(filename, sizeof(filename), stdin);
                removeNewline(filename);
                saveToFile(head, filename);
                printf("Text has been saved successfully\n");
            }
                break;
            case 4:
            {
                char filename[1024];
                printf("Enter the file name for loading: ");
                fgets(filename, sizeof(filename), stdin);
                removeNewline(filename);
                loadFromFile(&head, filename);
                printf("Text has been loaded successfully\n");
            }
                break;
            case 5:
                printCurrentText(head);
                break;
            case 6:
            {
                int lineNumber, charIndex;
                char text[1024];
                printf("Enter line number and character index: ");
                scanf("%d %d", &lineNumber, &charIndex);
                getchar(); // Видалити новий рядок після введення чисел
                printf("Enter text to insert: ");
                fgets(text, sizeof(text), stdin);
                removeNewline(text);
                insertText(head, lineNumber, charIndex, text);
            }
                break;
            case 7:
            {
                char query[1024];
                printf("Enter text to search: ");
                fgets(query, sizeof(query), stdin);
                removeNewline(query);
                searchText(head, query);
            }
                break;
            case 8:
                printf("\033[2J\033[1;1H"); // Очистити консоль
                break;
            case 0:
                clearText(&head);
                printf("Exiting the editor...\n");
                return 0;
            default:
                printf("Invalid command, please try again.\n");
                break;
        }
    }
}
