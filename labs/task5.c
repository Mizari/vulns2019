#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFF_SZ 40

void ret2win()
{
    system("/bin/cat flag.txt");
    exit(0);
}


int main()
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    char *welcome = "Hello to infoleak lab!\n";
    printf(welcome);

    char name[BUFF_SZ];
    read(0, name, BUFF_SZ);
    printf("Here's your leak, %s!\n", name);

    uint64_t what = 0;
    uint64_t *where = 0;
    printf("Enter arbitrary write stuff: ");
    scanf("%" SCNu64 " %" SCNu64, &what, &where);
    *where = what;
    printf("Good bye, %s!\n", name);
}
