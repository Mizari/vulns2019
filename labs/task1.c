#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>

const int shellcode_sz = 30;

int main()
{
    setvbuf(stdout, NULL, _IONBF, 0);
    char name[100] = {0};
    int (*shellcode)(void) = mmap(NULL, shellcode_sz, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (shellcode == MAP_FAILED)
    {
        puts("Failed to allocate");
        return -1;
    }
    printf("Allocated at %p\n", shellcode);

    printf("Enter shellcode: ");
    read(0, shellcode, shellcode_sz);

    printf("Enter your name: ");
    gets(name);
    return printf("Lets see, what you've got for me, %s!\n", name);
}
