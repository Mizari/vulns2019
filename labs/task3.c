#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_N_CLIENTS 0x10ull
#define MAX_DATA_LEN 0x10ull
#define MAX_PASS_LEN 0x10ull

void **clients = NULL;
FILE *f = NULL;

void ret2win()
{
    system("/bin/cat flag.txt");
    exit(0);
}

uint8_t read_byte()
{
    uint8_t res = 0;
    if (read(0, &res, 1) != 1)
        exit(2);
    return res;
}

uint8_t get_random()
{
    uint8_t res = 0;
    fread(&res, 1, 1, f);
    return res;
}


void change_data(void *client)
{
    if (*(uint8_t*)(client) != 1)
        exit(3);

    uint8_t passlen = *(uint8_t*)(client + 1);
    uint8_t datalen = read_byte();

    // new datalen
    *(uint8_t*)(client + 2 + passlen) = datalen;

    // new data
    for (uint8_t i = 0; i < datalen; ++i)
        *(uint8_t*)(client + 3 + passlen + i) = read_byte();
}

int main()
{
    f = fopen("/dev/urandom", "r");

    uint8_t passlen = 0ull;
    uint8_t datalen = 0ull;
    void *client = NULL;
    uint8_t n_clients = 0ull;

    n_clients = 2 + get_random() % MAX_N_CLIENTS;
    write(1, &n_clients, 1);

    clients = malloc(n_clients * sizeof(void *));
    for (uint64_t i = 0ull; i < n_clients; ++i)
    {
        // allocating client
        passlen = 20 + get_random() % MAX_PASS_LEN;
        datalen = 20 + get_random() % MAX_DATA_LEN;
        write(1, &passlen, 1);
        write(1, &datalen, 1);
        client = alloca(3 + passlen + datalen);
        clients[i] = client;

        // populating client
        *(uint8_t*)client = 0;
        *(uint8_t*)(client + 1) = passlen;
        for (uint8_t j = 0; j < passlen; ++j)
            *(uint8_t*)(client + 2 + j) = get_random();
        *(uint8_t*)(client + 2 + passlen) = datalen;
        for (uint8_t j = 0; j < passlen; ++j)
            *(uint8_t*)(client + 3 + passlen) = get_random();
    }

    *(uint8_t*)(clients[n_clients - 1]) = 1;

    while (1)
    {
        switch (read_byte())
        {
            // change data
            case 1:
                change_data(clients[read_byte()]);
                break;

            // exit
            case 2:
                goto endmain;

            default:
                exit(4);
        }
    }

endmain:
    fclose(f);
    return 0;
}
