#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


