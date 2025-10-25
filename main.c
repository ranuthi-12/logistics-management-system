#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void manageCities();
void manageDistances();
void handleDeliveryRequest();
void viewReports();

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

