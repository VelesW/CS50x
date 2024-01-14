#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(const char *str);
int count_sentences(const char *str);
int count_words(const char *str);

int main(void)
{
    char text[10000];
    printf("Text: ");
    fgets(text, sizeof(text), stdin);

    double W = count_words(text);
    double L = count_letters(text) / W * 100;
    double S = count_sentences(text) / W * 100;

    double index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = round(index);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }

    // printf("letters %f\n", L);
    // printf("words %f\n", W);
    // printf("sentences %f\n", S);
}

int count_letters(const char *str)
{
    int count = 0;

    while (*str != '\0')
    {
        if (isalpha(*str))
            count++;
        str++;
    }
    return count;
}

int count_sentences(const char *str)
{
    int count = 0;

    while (*str != '\0')
    {
        if (*str == '.' || *str == '!' || *str == '?')
            count++;
        str++;
    }
    return count;
}

int count_words(const char *str)
{
    int count = 0;
    if (*str != '\0')
        count++;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ' ' && str[i + 1] != ' ')
        {
            count++;
            continue;
        }
    }
    return count;
}