#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdarg.h>
#include <unistd.h>
#include <signal.h>

#define USERNAMELEN 256
#define ADMINNAMELEN 128

#define ACT_SIGRAT   0ul
#define ACT_LEAVE  1ul
#define ACT_ZANYAT   2ul
#define ACT_BCKDR  3ul

uint64_t user_rubli = 0ul;

char adminname[ADMINNAMELEN + 1] = {0};

char *valid_usernames[] = {"Seryoga", "Dasha", "Baton", "Nastya", "Maxim", "Dmitriy", "Yuliya", "Slava", "Nikita", "Saya", "Ivan"};

int is_username_valid(char *uname)
{
    for (uint64_t i = 0; i < sizeof(valid_usernames)/sizeof(char*); ++i)
        if (!strcmp(uname, valid_usernames[i]))
            return 1;

    return 0;
}

void errorlog(char *format, ...)
{
    va_list arg;
    va_start(arg, format);
    vfprintf(stdout, format, arg);
    va_end(arg);
}

void fgets_fix(char *buff, uint64_t n)
{
    fgets(buff, n, stdin);

    // just to make interaction easier
    char *x = strrchr(buff, '\n');
    if (x)
        *x = '\x00';
}

void generate_adminname()
{
    FILE *in = fopen("/dev/urandom", "r");
    for (int i = 0; i < ADMINNAMELEN; ++i)
        fread(adminname + i, 1, 1, in);
    fclose(in);
}

uint64_t get_action()
{
    char actbuff[100] = {0};
    printf("Enter your action: ");
    fgets_fix(actbuff, 100);

    if (!strcmp(actbuff, "sigrat"))
        return ACT_SIGRAT;
    else if (!strcmp(actbuff, "leave"))
        return ACT_LEAVE;
    else if (!strcmp(actbuff, "zanyat"))
        return ACT_ZANYAT;
    else if (!strcmp(actbuff, "bckdr"))
        return ACT_BCKDR;
    else
        return 0xfffffffffffffffful;
}

void sigrat()
{
    if (user_rubli == 0)
    {
        printf("Malovato deneg!\n");
        return;
    }

    printf("Sigraem? Kto segodnyashniy schastlivchik? ");

    char ugadaika[1024] = {0};
    fgets_fix(ugadaika, 1024);

    if (!is_username_valid(ugadaika))
    {
        errorlog("Invalid username: "), errorlog(ugadaika), errorlog(".\n");
        return;
    }

    FILE *in = fopen("/dev/urandom", "r");
    int WINNER = 0;
    fread(&WINNER, 1, 1, in);
    fclose(in);
    WINNER %= sizeof(valid_usernames)/sizeof(char*);
    if (!strcmp(ugadaika, valid_usernames[WINNER]))
        printf("Nichosi, derzhi denzhisha!\n"), user_rubli += 1;
    else
        printf("Ne povezlo, soryan\n"), user_rubli = 0;
}

void leave()
{
    printf("Ciao-kakao! Vot tvoya viruchka %lu\n", user_rubli);
    exit(0);
}

void zanyat()
{
    user_rubli += 100ul;
    printf("Vam dali 100 rubley\n");
}

void bckdr(char *username)
{
    if (!strcmp(adminname, username))
        system("cat flag.txt");
    exit(0);
}

int main()
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    signal(SIGALRM, exit);
    alarm(60);

    printf("Dobro pozhalovat v Grand Casino!\nKak tebya zovut: ");
    char username[USERNAMELEN] = {0};
    fgets_fix(username, USERNAMELEN);

    if (!is_username_valid(username))
    {
        printf("Falshivka!\n");
        exit(-1);
    }

    printf("Preved, %s!\n", username);

    generate_adminname();

    while(228)
    {
        uint64_t action = get_action();
        switch (action)
        {
            case ACT_SIGRAT:
                sigrat();
                break;
            case ACT_LEAVE:
                leave();
                break;
            case ACT_ZANYAT:
                zanyat();
                break;
            case ACT_BCKDR:
                bckdr(username);
                break;
            default:
                errorlog("Nepravilnoe deistvie!\n");
                break;
        }
    }
}
