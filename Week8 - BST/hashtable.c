#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

// Structure for each hash table entry
struct HashNode
{
    char key[50];
    int value;
    struct HashNode *next;
};

// Structure for Hash Table
struct HashTable
{
    struct HashNode *buckets[SIZE];
};

// Function to create a new hash node
struct HashNode *createNode(const char *key, int value)
{
    struct HashNode *newNode = (struct HashNode *)malloc(sizeof(struct HashNode));
    strcpy(newNode->key, key);
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Hash function (simple string hash)
unsigned int hash(const char *key)
{
    unsigned int hashValue = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        hashValue = (hashValue * 31 + key[i]) % SIZE;
    }
    return hashValue;
}

// Initialize hash table
void initHashTable(struct HashTable *table)
{
    for (int i = 0; i < SIZE; i++)
    {
        table->buckets[i] = NULL;
    }
}

// Insert a key-value pair into the hash table
void insert(struct HashTable *table, const char *key, int value)
{
    unsigned int index = hash(key);

    // Check if key already exists
    struct HashNode *current = table->buckets[index];
    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            current->value = value; // Update value if key exists
            return;
        }
        current = current->next;
    }

    // If key doesn't exist, create a new node
    struct HashNode *newNode = createNode(key, value);

    // Insert at the beginning of the linked list (chaining)
    newNode->next = table->buckets[index];
    table->buckets[index] = newNode;
}

// Search for a key in the hash table
int search(struct HashTable *table, const char *key)
{
    unsigned int index = hash(key);
    struct HashNode *current = table->buckets[index];

    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            return current->value; // Key found
        }
        current = current->next;
    }

    return -1; // Key not found
}

// Delete a key from the hash table
int delete(struct HashTable *table, const char *key)
{
    unsigned int index = hash(key);
    struct HashNode *current = table->buckets[index];
    struct HashNode *prev = NULL;

    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            // Found the key to delete
            if (prev == NULL)
            {
                // If it's the first node in the bucket
                table->buckets[index] = current->next;
            }
            else
            {
                // If it's not the first node
                prev->next = current->next;
            }
            int value = current->value;
            free(current);
            return value; // Return the value of deleted key
        }
        prev = current;
        current = current->next;
    }

    return -1; // Key not found
}

// Display the hash table
void display(struct HashTable *table)
{
    printf("\nHash Table Contents:\n");
    for (int i = 0; i < SIZE; i++)
    {
        printf("Bucket %d: ", i);
        struct HashNode *current = table->buckets[i];
        while (current != NULL)
        {
            printf("(%s:%d) -> ", current->key, current->value);
            current = current->next;
        }
        printf("NULL\n");
    }
}

// Free the hash table memory
void freeHashTable(struct HashTable *table)
{
    for (int i = 0; i < SIZE; i++)
    {
        struct HashNode *current = table->buckets[i];
        while (current != NULL)
        {
            struct HashNode *temp = current;
            current = current->next;
            free(temp);
        }
        table->buckets[i] = NULL;
    }
}

int main()
{
    struct HashTable table;
    initHashTable(&table);

    int choice, value;
    char key[50];

    do
    {
        printf("\n\n--- Hash Table Operations ---\n");
        printf("1. Insert a key-value pair\n");
        printf("2. Search for a key\n");
        printf("3. Delete a key\n");
        printf("4. Display the hash table\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter key: ");
            scanf("%s", key);
            printf("Enter value: ");
            scanf("%d", &value);
            insert(&table, key, value);
            printf("Key-value pair inserted successfully!\n");
            break;

        case 2:
            printf("Enter key to search: ");
            scanf("%s", key);
            value = search(&table, key);
            if (value != -1)
            {
                printf("Value for key '%s': %d\n", key, value);
            }
            else
            {
                printf("Key '%s' not found!\n", key);
            }
            break;

        case 3:
            printf("Enter key to delete: ");
            scanf("%s", key);
            value = delete (&table, key);
            if (value != -1)
            {
                printf("Key '%s' with value %d deleted successfully!\n", key, value);
            }
            else
            {
                printf("Key '%s' not found!\n", key);
            }
            break;

        case 4:
            display(&table);
            break;

        case 5:
            printf("Exiting program...\n");
            break;

        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    // Free the hash table memory before exiting
    freeHashTable(&table);

    return 0;
}