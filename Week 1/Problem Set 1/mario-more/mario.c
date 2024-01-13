#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    const int gap_size = 2;
    //Get height of pyramid from user
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    //making pyramid
    for (int i = 0; i < n; i++)
    {
        //Print spaces
        for (int j = 0; j < n - i - 1; j++)
        {
            printf(" ");
        }

        //print left hashes
        for (int j = n - i; j <= n; j++)
        {
            printf("#");
        }

        //print gap
        for (int j = 0; j < gap_size; j++)
        {
            printf(" ");
        }

        //print right hashes
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}