#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long card_number = 10, card_number_tmp;
    int result = 3, checksum = 0, num, num_len = 0;
    string result_possibilities[4] = {"AMEX", "MASTERCARD", "VISA", "INVALID"};

    //Prompt for input
    do
    {
        card_number = get_long("Number: ");
    }
    while (card_number <= 1);

    //Calculate checksum
    card_number_tmp = card_number;
    for (int i = 1; card_number_tmp > 0; i++ ) //loop for digits multiplied by 2
    {
        if (i % 2 == 0)
        {
            num = 2 * (card_number_tmp % 10);
            if (num > 9)
                    checksum += num % 10 + (num / 10) % 10;
            else
                checksum += num;
        }
        card_number_tmp = card_number_tmp / 10;
    }
        card_number_tmp = card_number;

        for(int i = 1; card_number_tmp > 0; i++) //loop for another digits
        {
            if( i % 2 == 1)
            {
                num = card_number_tmp % 10;
                checksum += num;
            }
            card_number_tmp = card_number_tmp / 10;
        }

    if (checksum % 10 != 0) //validation checksum
    {
        printf("%s\n", result_possibilities[3]);
        return 0;
    }

    //Chceck for length and starting digits
    card_number_tmp = card_number;
    while(card_number_tmp > 0)
    {
        num_len++;
        card_number_tmp /= 10;
    }

    if (num_len != 16 && num_len != 15 && num_len != 13)
    {
        printf("%s\n", result_possibilities[3]);
        return 0;
    }

    //Check digits for VISA
    if (num_len == 13)
    {
        if ((card_number / 1000000000000) % 10 == 4)
            result = 2;
    }

    //Check digis for AMEX
    else if (num_len == 15)
    {
        num = (card_number / 10000000000000) % 100;
            if (num == 34 || num == 37)
                result = 0;
    }

    //Check digits for MASTERCARD or VISA
    else if (num_len == 16)
    {
        num = (card_number / 100000000000000) % 100;
        if (num == 51 || num == 52 || num == 53 || num == 54 || num == 55)
            result = 1;
        num = num / 10;
        if (num % 10 == 4)
            result = 2;
    }
    else
        result = 3;

    //Print result
    printf("%s\n", result_possibilities[result]);
}