#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 1024
const char *morse_table[36] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",                           // A-I
    ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",                         // J-R
    "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",                                // S-Z
    "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----." // 0-9
};

int char_to_index(char c)
{
    if (isalpha(c))
        return toupper(c) - 'A';
    if (isdigit(c))
        return c - '0' + 26;
    return -1;
}

char morse_to_char(const char *code)
{
    for (int i = 0; i < 36; i++)
    {
        if (strcmp(code, morse_table[i]) == 0)
        {
            if (i < 26)
                return 'A' + i;
            else
                return '0' + (i - 26);
        }
    }
    return '?';
}

void text_to_morse(const char *input)
{
    printf("Morse Code: ");
    for (int i = 0; input[i]; i++)
    {
        if (input[i] == ' ')
        {
            printf(" / ");
        }
        else
        {
            int idx = char_to_index(input[i]);
            if (idx != -1)
            {
                printf("%s ", morse_table[idx]);
            }
        }
    }
    printf("\n");
}

void morse_to_text(const char *input)
{
    printf("Text: ");
    char buffer[10];
    int buf_idx = 0;

    for (int i = 0;; i++)
    {
        char c = input[i];

        if (c == '.' || c == '-')
        {
            buffer[buf_idx++] = c;
        }
        else if (c == ' ' || c == '\0')
        {
            if (buf_idx > 0)
            {
                buffer[buf_idx] = '\0';
                printf("%c", morse_to_char(buffer));
                buf_idx = 0;
            }

            if (c == ' ' && input[i + 1] == '/' && input[i + 2] == ' ')
            {
                printf(" ");
                i += 2;
            }

            if (c == '\0')
                break;
        }
    }
    printf("\n");
}

int main()
{
    char input[MAX_INPUT];
    int choice;

    while (1)
    {
        printf("\n=== Morse Code Converter ===\n");
        printf("1. Text to Morse\n");
        printf("2. Morse to Text\n");
        printf("3. Exit\n");
        printf("Choose option: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 3)
        {
            printf("Goodbye!\n");
            break;
        }

        printf("Enter input: ");
        fgets(input, MAX_INPUT, stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 0)
        {
            printf("Empty input. Try again.\n");
            continue;
        }

        if (choice == 1)
        {
            text_to_morse(input);
        }
        else if (choice == 2)
        {
            morse_to_text(input);
        }
        else
        {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
