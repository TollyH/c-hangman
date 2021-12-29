#include <stdio.h>
#include <stdlib.h>


int string_contains_char(char item, char array[]);
int has_won(char word[], char guessed_letters[]);
void flush_stdin();


int main()
{
    char word[20] = "";
    fputs("Enter a word up to 20 characters long to be guessed > ", stdout);
    scanf("%20s", word);
    flush_stdin();
    #ifdef WINNT
        /* Clear terminal for Windows */
        system("cls");
    #else
        /* Clear terminal for non-Windows (macOS, Linux, ...) */
        system("clear");
    #endif

    /* Sized for all 6 incorrect guesses,
       20 correct guesses,
       plus a null terminator */
    char guessed_letters[27] = {0};
    int total_guesses = 0;
    int incorrect_guesses = 0;

    /* Main game loop */
    while (!has_won(word, guessed_letters) && incorrect_guesses < 6)
    {
        puts("\n");

        /* Print out the word, substituting characters yet to be guessed
           with underscores */
        int word_index = 0;
        while (word[word_index] != '\0')
        {
            if (string_contains_char(word[word_index], guessed_letters))
            {
                printf("%c ", word[word_index]);
            }
            else
            {
                fputs("_ ", stdout);
            }
            word_index++;
        }
        puts("\n");

        /* Print out all of the correct and incorrect guesses */
        fputs("Guessed letters: ", stdout);
        int guessed_letter_index = 0;
        while (guessed_letters[guessed_letter_index] != '\0')
        {
            printf("%c ", guessed_letters[guessed_letter_index]);
            guessed_letter_index++;
        }
        puts("");

        printf("You have %d guesses remaining.\n", 6 - incorrect_guesses);
        fputs("Enter a letter > ", stdout);
        char guess = getchar();
        flush_stdin();
        puts("");

        if (string_contains_char(guess, guessed_letters))
        {
            puts("You have already guessed that letter!");
        }
        else
        {
            guessed_letters[total_guesses] = guess;
            total_guesses++;
            if (string_contains_char(guess, word))
            {
                puts("Correct!");
            }
            else
            {
                puts("Incorrect!");
                incorrect_guesses++;
            }
        }
    }

    puts(
        has_won(word, guessed_letters) ?
            "Congratulations! You win!" : "Sorry! You lose!");
    printf("The word was %s\n", word);

    return 0;
}


int string_contains_char(char item, char string[])
{
    int string_index = 0;
    while (string[string_index] != '\0')
    {
        if (string[string_index] == item)
        {
            return 1;
        }
        string_index++;
    }

    return 0;
}


int has_won(char word[], char guessed_letters[])
{
    int word_index = 0;
    while (word[word_index] != '\0')
    {
        if (!string_contains_char(word[word_index], guessed_letters))
        {
            return 0;
        }
        word_index++;
    }

    return 1;
}


void flush_stdin()
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}
