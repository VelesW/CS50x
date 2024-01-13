#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Get name input from an user
    string name = get_string("What is your name? ");
    
    //print output on the screen
    printf("hello, %s\n", name);
}