#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 100
#define MAX_NAME_LENGTH 50
#define MAX_NUMBER_LENGTH 15

struct Contact {
    char name[MAX_NAME_LENGTH];
    char num[MAX_NUMBER_LENGTH];
};

struct PhoneBook {
    struct Contact contacts[MAX_CONTACTS];
    int num_contacts;
};

void add_contact(struct PhoneBook *phone_book, const char *name, const char *num) {
    if (phone_book->num_contacts < MAX_CONTACTS) {
        strcpy(phone_book->contacts[phone_book->num_contacts].name, name);
        strcpy(phone_book->contacts[phone_book->num_contacts].num, num);
        phone_book->num_contacts++;
        printf("Added %s to the phone book with number %s.\n", name, num);
    } else {
        printf("Phone book is full. Cannot add more contacts.\n");
    }
}

void search_contact(struct PhoneBook *phone_book, const char *name) {
    int i;
    for (i = 0; i < phone_book->num_contacts; i++) {
        if (strcmp(phone_book->contacts[i].name, name) == 0) {
            printf("%s: %s\n", phone_book->contacts[i].name, phone_book->contacts[i].num);
            return;
        }
    }
    printf("%s not found in the phone book.\n", name);
}

void delete_contact(struct PhoneBook *phone_book, const char *name) {
    int i;
    for (i = 0; i < phone_book->num_contacts; i++) {
        if (strcmp(phone_book->contacts[i].name, name) == 0) {
            printf("%s has been deleted from the phone book.\n", phone_book->contacts[i].name);
            memmove(&phone_book->contacts[i], &phone_book->contacts[i + 1], (phone_book->num_contacts - i - 1) * sizeof(struct Contact));
            phone_book->num_contacts--;
            return;
        }
    }
    printf("%s not found in the phone book.\n", name);
}

void display_contacts(struct PhoneBook *phone_book) {
    int i;
    if (phone_book->num_contacts == 0) {
        printf("Phone book is empty.\n");
    } else {
        printf("Phone Book:\n");
        for (i = 0; i < phone_book->num_contacts; i++) {
            printf("%s: %s\n", phone_book->contacts[i].name, phone_book->contacts[i].num);
        }
    }
}

int main() {
    struct PhoneBook phone_book;
    phone_book.num_contacts = 0;

    while (1) {
        printf("\nPhone Book Menu:\n");
        printf("1. Add Contact\n");
        printf("2. Search Contact\n");
        printf("3. Delete Contact\n");
        printf("4. Display All Contacts\n");
        printf("5. Exit\n");

        int choice;
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);
        getchar(); // consume newline

        char name[MAX_NAME_LENGTH];
        char num[MAX_NUMBER_LENGTH];

        switch (choice) {
            case 1:
                printf("Enter contact name: ");
                fgets(name, MAX_NAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = '\0'; // remove trailing newline
                printf("Enter contact number: ");
                fgets(num, MAX_NUMBER_LENGTH, stdin);
                num[strcspn(num, "\n")] = '\0'; // remove trailing newline
                add_contact(&phone_book, name, num);
                break;
            case 2:
                printf("Enter contact name to search: ");
                fgets(name, MAX_NAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = '\0'; // remove trailing newline
                search_contact(&phone_book, name);
                break;
            case 3:
                printf("Enter contact name to delete: ");
                fgets(name, MAX_NAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = '\0'; // remove trailing newline
                delete_contact(&phone_book, name);
                break;
            case 4:
                display_contacts(&phone_book);
                break;
            case 5:
                printf("Exiting phone book application.\n");
                return 0;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
                break;
        }
    }

    return 0;
}
