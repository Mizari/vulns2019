#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

void ret2win()
{
    system("/bin/cat flag.txt");
    exit(0);
}

void greet()
{
    char buf[1024] = {0};
    printf("Whats your name, by the way? ");
    scanf("%1024s", buf);
    printf("Greetings, %s!\n", buf);
}

uint64_t get_randnum()
{
    uint64_t res;
    FILE *f = fopen("/dev/urandom", "r");
    fread(&res, 1, 8, f);
    fclose(f);
    return res;
}

uint64_t get_guess()
{
    uint64_t res;
    scanf("%" SCNd64, &res);
    return res;
}

void main(void)
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    puts("Try to guess a number!");
    uint64_t yourguess = get_guess();

    greet();

    uint64_t randnum = get_randnum();

    if (yourguess == randnum)
        puts("Wow, congrats! No flag for you tho :S");
    else
        puts("Incorret, hehe");
}
