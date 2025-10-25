#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30
#define CITY_NAME_LENGTH 50

char cities[MAX_CITIES][CITY_NAME_LENGTH];
int cityCount = 0;
int distances[MAX_CITIES][MAX_CITIES];

void manageCities();
void manageDistances();
void handleDeliveryRequest();
void viewReports();
void addCity();
void removeCity();
void renameCity();
void displayCities();

int main()
{
    printf("=============================================\n");
    printf("         LOGISTICS MANAGEMENT SYSTEM         \n");
    printf("=============================================\n");

    int choice;
    do
    {
        printf("\n========= MAIN MENU =========\n");
        printf("1. City Management\n");
        printf("2. Distance Management\n");
        printf("3. Delivery Request\n");
        printf("4. Performance Reports\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            manageCities();
            break;
        case 2:
            manageDistances();
            break;
        case 3:
            handleDeliveryRequest();
            break;
        case 4:
            viewReports();
            break;
        case 5:
            printf("Exiting System.Thank you!\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);
    return 0;
}

void manageCities()
{
    int choice;
    do
    {
        printf("\n======City Management======\n");
        printf("1. Add new city\n");
        printf("2. Remove city\n");
        printf("3. Rename city\n");
        printf("4. Display all cities\n");
        printf("5. Back to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addCity();
            break;
        case 2:
            removeCity();
            break;
        case 3:
            renameCity();
            break;
        case 4:
            displayCities();
            break;
        case 5:
            return;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);
}

void addCity()
{
    if (cityCount >= MAX_CITIES)
    {
        printf("Maximum city limit reached\n");
        return;
    }

    char newCity[CITY_NAME_LENGTH];
    printf("Enter city name: ");
    getchar();
    fgets(newCity, CITY_NAME_LENGTH, stdin);
    newCity[strcspn(newCity, "\n")] = 0;

    for (int i = 0; i < cityCount; i++)
    {
        if (strcmp(cities[i], newCity) == 0)
        {
            printf("This city already exists\n");
            return;
        }
    }

    strcpy(cities[cityCount], newCity);
    cityCount++;
    printf("%s city added successfully!\n", newCity);
}


