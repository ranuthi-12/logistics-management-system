#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30
#define CITY_NAME_LENGTH 50

char cities[MAX_CITIES][CITY_NAME_LENGTH];
int cityCount = 0;
int distances[MAX_CITIES][MAX_CITIES];

char vehicleNames[3][30] = {"Van", "Truck", "Lorry"};
int vehicleCapacity[3] = {1000, 5000, 10000};
float vehicleRate[3] = {30.0, 40.0, 80.0};
float vehicleSpeed[3] = {60.0, 50.0, 45.0};
float vehicleFuelEfficiency[3] = {12.0, 6.0, 4.0};

void manageCities();
void manageDistances();
void handleDeliveryRequest();
void viewReports();
void addCity();
void removeCity();
void renameCity();
void displayCities();
void editDistance();
void displayDistanceTable();

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

void removeCity()
{
    if (cityCount == 0)
    {
        printf("No cities to remove.\n");
        return;
    }

    displayCities();

    int index;
    printf("Enter city number to remove (1-%d): ", cityCount);
    scanf("%d", &index);

    if (index < 1 || index > cityCount)
    {
        printf("Invalid city number!\n");
        return;
    }

    index--;

    printf("%s city removed successfully!\n", cities[index]);

    for (int i = index; i < cityCount - 1; i++)
    {
        strcpy(cities[i], cities[i + 1]);
    }

    for (int i = 0; i < cityCount - 1; i++)
    {
        for (int j = 0; j < cityCount; j++)
        {
            distances[i][j] = distances[i + 1][j];
        }
    }

    for (int i = 0; i < cityCount; i++)
    {
        for (int j = 0; j < cityCount - 1; j++)
        {
            distances[i][j] = distances[i][j + 1];
        }
    }

    cityCount--;
}

void renameCity()
{
    if (cityCount == 0)
    {
        printf("No cities to rename.\n");
        return;
    }

    displayCities();

    int index;
    printf("Enter city number to rename (1-%d): ", cityCount);
    scanf("%d", &index);
    getchar();

    if (index < 1 || index > cityCount)
    {
        printf("Invalid city number!\n");
        return;
    }

    index--;

    char newName[CITY_NAME_LENGTH];
    printf("Enter new name: ");
    fgets(newName, CITY_NAME_LENGTH, stdin);
    newName[strcspn(newName, "\n")] = 0;

    for (int i = 0; i < cityCount; i++)
    {
        if (i != index && strcmp(cities[i], newName) == 0)
        {
            printf("City name already exists\n");
        }
    }

    printf("%s City renamed to %s successfully!\n", cities[index], newName);
    strcpy(cities[index], newName);
}

void displayCities()
{
    printf("\n==================================\n");
    printf("               City List            \n");
    printf("====================================\n");

    if (cityCount == 0)
    {
        printf("No cities available.\n");
    }
    else
    {
        for (int i = 0; i < cityCount; i++)
        {
            printf("%d. %s\n", i + 1, cities[i]);
        }
    }
}

void manageDistances()
{
    int choice;
    do
    {
        printf("\n======Distance Management======\n");
        printf("1. Input/Edit distance\n");
        printf("2. Display Distance table\n");
        printf("3. Back to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            editDistance();
            break;
        case 2:
            displayDistanceTable();
            break;
        case 3:
            return;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);
}

void editDistance()
{
    if (cityCount < 2)
    {
        printf("Need at least 2 cities to set distances!\n");
        return;
    }

    displayCities();

    int city1, city2, distance;
    printf("Enter first city number: ");
    scanf("%d", &city1);
    printf("Enter second city number: ");
    scanf("%d", &city2);

    if (city1 < 1 || city1 > cityCount || city2 < 1 || city2 > cityCount)
    {
        printf("Invalid city numbers!\n");
        return;
    }

    if (city1 == city2)
    {
        printf("Cannot set distance from city to itself!\n");
        return;
    }

    city1--;
    city2--;

    printf("Enter distance (km): ");
    scanf("%d", &distance);

    if (distance < 0)
    {
        printf("Invalid distance!\n");
        return;
    }

    distances[city1][city2] = distance;
    distances[city2][city1] = distance;

    printf("Distance set successfully!\n");
}

void displayDistanceTable()
{
    if (cityCount == 0)
    {
        printf("No cities available!\n");
        return;
    }

    printf("\n=======================================\n");
    printf("          Distances between 2 cities     \n");
    printf("\n=======================================\n");

    printf("%15s", " ");
    for (int i = 0; i < cityCount; i++)
    {
        printf("%-15s", cities[i]);
    }
    printf("\n");
    printf("---------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < cityCount; i++)
    {
        printf("%-15s", cities[i]);
        for (int j = 0; j < cityCount; j++)
        {
            if (distances[i][j] == 0 && i != j)
            {
                printf("%-15s", "-");
            }
            else
            {
                printf("%-15d", distances[i][j]);
            }
        }
        printf("\n");
    }
}

void handleDeliveryRequest()
{
    if (cityCount < 2)
    {
        printf("Need at least 2 cities for delivery!\n");
        return;
    }

    displayCities();

    int source, destination, weight, vehicleType;

    printf("Enter source city number: ");
    scanf("%d", &source);
    printf("Enter destination city number: ");
    scanf("%d", &destination);

    if (source == destination)
    {
        printf("Source and destination cannot be the same!\n");
        return;
    }

    source--;
    destination--;

    printf("Enter weight(kg): ");
    scanf("%d", &weight);

    if (weight <= 0)
    {
        printf("Weight must be positive!\n");
        return;
    }

    printf("\n===== Available Vehicles =====\n");

    for (int i = 0; i < 3; i++)
    {
        printf(" %d. %-10s - Capacity: %5d kg, Rate: %.0f LKR/km\n", i + 1, vehicleNames[i], vehicleCapacity[i], vehicleRate[i]);
    }

    printf("Select vehicle type (1-3): ");
    scanf("%d", &vehicleType);

    if (vehicleType < 1 || vehicleType > 3)
    {
        printf("Invalid. Enter again");
        return;
    }

    vehicleType--;

    if (weight > vehicleCapacity[vehicleType])
    {
        printf("Weight exceeds vehicle capacity!\n");
        printf("Maximum capacity for %s: %d kg\n", vehicleNames[vehicleType], vehicleCapacity[vehicleType]);
        return;
    }

}

