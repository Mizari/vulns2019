#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define BAD_REG "Client isnt registered!"
#define BAD_SECRET "Invalid client secret!"
#define ALREADY_REG "Client is already registered!"
#define N_CLIENTS 2ll
#define PASSLEN 0x100ull

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
    uint64_t new_data = 0ull;
    if (!is_client_registered(client))
        return voidputs(BAD_REG);

    printf("Enter client secret: ");
    if (!is_client_secret_ok(client))
        return voidputs(BAD_SECRET);

    printf("Enter new data: ");
    scanf("%" SCNd64, &new_data);
    client->data = new_data;
}

void register_client(client_t *client)
{
    if (is_client_registered(client))
        return voidputs(ALREADY_REG);

    printf("Enter secret: ");
    scanf("%" SCNd64, &client->secret);
    printf("Enter data: ");
    scanf("%" SCNd64, &client->data);
    client->is_registered = 1ull;
}

void show_client_data(client_t *client)
{
    if (!is_client_registered(client))
        return voidputs(BAD_REG);

    printf("Enter client secret: ");
    if (!is_client_secret_ok(client))
        return voidputs(BAD_SECRET);

    printf("Client data is: %" PRIx64 "\n", client->data);
}

void deregister_client(client_t *client)
{
    if (!is_client_registered(client))
        return voidputs(BAD_REG);

    if (!is_client_secret_ok(client))
        return voidputs(BAD_SECRET);

    client->is_registered = 0ull;
    client->secret = 0ull;
    client->data = 0ull;
}

int main()
{
    setvbuf(stdout, NULL, _IONBF, 0);
    uint64_t action = 0;
    int64_t client_id = 0;
    client_t clients[N_CLIENTS] = {0};
    while (322)
    {
        printf("\nYour client id: ");
        if(get_check_client_id(&client_id))
        {
            puts("Invalid client id!");
            continue;
        }
        client_t *current_client = &clients[client_id];

        printf("Your action: ");
        scanf("%" SCNu64, &action);
        switch (action)
        {
            case 1llu:
                register_client(current_client);
                break;
            case 2llu:
                change_client_data(current_client);
                break;
            case 3llu:
                show_client_data(current_client);
                break;
            case 4llu:
                deregister_client(current_client);
                break;
            default:
                printf("default");
                break;
        }
    }
}
