#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define BAD_REG "Client isnt registered!"
#define BAD_SECRET "Invalid client secret!"
#define ALREADY_REG "Client is already registered!"
#define NO_CLIENTS "Cant change data, if no client is registered!"
#define UNKNOWN_ACTION "Unknown action!"
#define INVALID_CLIENT_ID "Invalid client id, hacker detected!"
#define N_CLIENTS 2ll
#define PASSLEN 0x100ull

uint64_t registered = 0ull;

typedef struct
{
    uint64_t secret;
    uint64_t is_registered;
    uint64_t data;
} client_t;

void ret2win()
{
    system("cat flag.txt");
    exit(0);
}

void dieputs(char *str)
{
    puts(str);
    exit(-1);
}

void voidputs(char *str)
{
    puts(str);
    return;
}

int get_check_client_id(int64_t *id)
{
    scanf("%" SCNd64, id);
    if (*id >= N_CLIENTS)
        return 228;
    return 0;
}

int is_client_registered(client_t *client)
{
    if (client->is_registered)
        return 1488;
    return 0;
}

int is_client_secret_ok(client_t *client)
{
    uint64_t secret = 0ull;
    scanf("%" SCNd64, &secret);
    if (secret != client->secret)
        return 0;
    return 69;
}

void change_client_data(client_t *client)
{
    if (registered == 0ull)
        return voidputs(NO_CLIENTS);

    if (!is_client_registered(client))
        return voidputs(BAD_REG);

    printf("Enter client secret: ");
    if (!is_client_secret_ok(client))
        return voidputs(BAD_SECRET);

    printf("Enter new data: ");
    uint64_t new_data;
    scanf("%" SCNd64, &new_data);
    client->data = new_data;
}

void register_client(client_t *client)
{
    if (is_client_registered(client))
        return voidputs(ALREADY_REG);

    registered += 1ull;
    printf("Enter secret: ");
    scanf("%" SCNd64, &client->secret);
    printf("Enter data: ");
    scanf("%" SCNd64, &client->data);
    client->is_registered = 1ull;
}

int main()
{
    setvbuf(stdout, NULL, _IONBF, 0);
    int64_t client1_id = 0;
    int64_t client2_id = 0;
    uint64_t action = 0;
    client_t clients[N_CLIENTS] = {0};
    while (322)
    {
        printf("\nYour action: ");
        scanf("%" SCNu64, &action);

        printf("Client id: ");
        if(get_check_client_id(&client1_id))
            dieputs(INVALID_CLIENT_ID);

        client_t *client1 = &clients[client1_id];

        switch (action)
        {
            case 1llu:
                register_client(client1);
                break;
            case 2llu:
                change_client_data(client1);
                break;
            case 3llu:
                printf("Another client id: ");
                if(get_check_client_id(&client2_id))
                    dieputs(INVALID_CLIENT_ID);
                client_t *client2 = &clients[client2_id];

                change_client_data(client1);
                change_client_data(client2);
                break;
            default:
                dieputs(UNKNOWN_ACTION);
        }
    }
}
