#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30
#define CITY_NAME_LENGTH 50
#define INFINITY_VALUE 999999
#define FUEL_PRICE 310.0
#define MAX_DELIVERIES 50

char cities[MAX_CITIES][CITY_NAME_LENGTH];
int cityCount = 0;
int distances[MAX_CITIES][MAX_CITIES];

char vehicleNames[3][30] = {"Van", "Truck", "Lorry"};
int vehicleCapacity[3] = {1000, 5000, 10000};
float vehicleRate[3] = {30.0, 40.0, 80.0};
float vehicleSpeed[3] = {60.0, 50.0, 45.0};
float vehicleFuelEfficiency[3] = {12.0, 6.0, 4.0};

int minDistance = 0;
int path[MAX_CITIES];
int pathLen = 0;

int deliveryCount = 0;
int deliverySource[MAX_DELIVERIES];
int deliveryDestination[MAX_DELIVERIES];
int deliveryWeight[MAX_DELIVERIES];
int deliveryVehicle[MAX_DELIVERIES];
float deliveryDistance[MAX_DELIVERIES];
float deliveryCost[MAX_DELIVERIES];
float deliveryTime[MAX_DELIVERIES];
float deliveryRevenue[MAX_DELIVERIES];
float deliveryProfit[MAX_DELIVERIES];

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
void calculateDeliveryCost(int source, int destination, int weight, int vehicleType);
void saveDeliveryRecord(int source, int destination, int weight, int vehicleType, float distance, float delivCost, float time, float customerCharge, float profit);
void displayDeliveryEstimate(int source, int destination, int weight, int vehicleType, float distance, float deliveryCost,
                             float fuelUsed, float fuelCost, float totalCost, float profit, float customerCharge, float time);
void findShortestPath(int source, int destination);
void loadFromFiles();
void saveToFiles();

int main()
{
    printf("=============================================\n");
    printf("         LOGISTICS MANAGEMENT SYSTEM         \n");
    printf("=============================================\n");

    loadFromFiles();

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

    saveToFiles();
    printf("All data saved successfully.\n");
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
    calculateDeliveryCost(source, destination, weight, vehicleType);

}

void calculateDeliveryCost(int source, int destination, int weight, int vehicleType)
{
    findShortestPath(source, destination);

    if (minDistance == 0 || minDistance == INFINITY_VALUE)
    {
        printf("No route available between selected cities!\n");
        return;
    }

    float distance = (float)minDistance;
    float rate = vehicleRate[vehicleType];
    float speed = vehicleSpeed[vehicleType];
    float efficiency = vehicleFuelEfficiency[vehicleType];

    float deliveryCost = distance * rate * (1.0 + (weight / 10000.0));
    float fuelUsed = distance / efficiency;
    float fuelCost = fuelUsed * FUEL_PRICE;
    float totalCost = deliveryCost + fuelCost;
    float profit = deliveryCost * 0.25;
    float customerCharge = totalCost + profit;
    float time = distance / speed;

    displayDeliveryEstimate(source, destination, weight, vehicleType, distance, deliveryCost, fuelUsed, fuelCost, totalCost, profit, customerCharge, time);
    saveDeliveryRecord(source, destination, weight, vehicleType, distance, deliveryCost, time, customerCharge, profit);
}

void saveDeliveryRecord(int source, int destination, int weight, int vehicleType, float distance, float delivCost, float time, float customerCharge, float profit)
{
    if (deliveryCount >= MAX_DELIVERIES)
    {
        printf("Maximum delivery records reached!\n");
        deliveryCount = MAX_DELIVERIES - 1;
    }

    deliverySource[deliveryCount] = source;
    deliveryDestination[deliveryCount] = destination;
    deliveryWeight[deliveryCount] = weight;
    deliveryVehicle[deliveryCount] = vehicleType;
    deliveryDistance[deliveryCount] = distance;
    deliveryCost[deliveryCount] = delivCost;
    deliveryTime[deliveryCount] = time;
    deliveryRevenue[deliveryCount] = customerCharge;
    deliveryProfit[deliveryCount] = profit;
    deliveryCount++;
}

void displayDeliveryEstimate(int source, int destination, int weight, int vehicleType, float distance, float deliveryCost,
                             float fuelUsed, float fuelCost, float totalCost, float profit, float customerCharge, float time)
{
    printf("\n===================================================\n");
    printf("                 Delivery Cost Estimation              ");
    printf("\n----------------------------------------------------\n");
    printf(" From:              %s\n", cities[source]);
    printf(" To:                %s\n", cities[destination]);
    printf(" Minimum Distance:  %.0f km\n", distance);
    printf(" Vehicle:           %s\n", vehicleNames[vehicleType]);
    printf(" Weight:            %d kg\n", weight);
    printf("-------------------------------------------------------\n");
    printf(" Base Cost:         %.2f x %.0f x (1 + %d/10000.0)\n", distance, vehicleRate[vehicleType], weight);
    printf("                    = %.2f LKR\n", deliveryCost);
    printf(" Fuel Used:         %.2f L\n", fuelUsed);
    printf(" Fuel Cost:          %.2f LKR\n", fuelCost);
    printf(" Operational Cost:   %.2f LKR\n", totalCost);
    printf(" Profit:             %.2f LKR\n", profit);
    printf(" Customer Charge:    %.2f LKR\n", customerCharge);
    printf(" Estimated Time:     %.2f hours\n", time);
    printf("\n=====================================================\n");
}

void findShortestPath(int source, int destination)
{
    if (distances[source][destination] > 0)
    {
        minDistance = distances[source][destination];
        path[0] = source;
        path[1] = destination;
        pathLen = 2;
    }
    else
    {
        minDistance = INFINITY_VALUE;
        pathLen = 0;
    }

    for (int intermediate = 0; intermediate < cityCount; intermediate++)
    {
        if (intermediate == source || intermediate == destination)
        {
            continue;
        }

        if (distances[source][intermediate] > 0 && distances[intermediate][destination] > 0)
        {
            int totalDistance = distances[source][intermediate] + distances[intermediate][destination];
            if (totalDistance < minDistance)
            {
                minDistance = totalDistance;
                path[0] = source;
                path[1] = intermediate;
                path[2] = destination;
                pathLen = 3;
            }
        }
    }

    for (int i = 0; i < cityCount; i++)
    {
        if (i == source || i == destination)
        {
            continue;
        }
        for (int j = 0; j < cityCount; j++)
        {
            if (j == source || j == destination || j == i)
            {
                continue;
            }

            if (distances[source][i] > 0 && distances[i][j] > 0 && distances[j][destination] > 0)
            {
                int totalDistance = distances[source][i] + distances[i][j] + distances[j][destination];
                if (totalDistance < minDistance)
                {
                    minDistance = totalDistance;
                    path[0] = source;
                    path[1] = i;
                    path[2] = j;
                    path[3] = destination;
                    pathLen = 4;
                }
            }
        }
    }
}

void viewReports()
{
    if (deliveryCount == 0)
    {
        printf("No deliveries completed yet!\n");
        return;
    }

    printf("\n==================================================================\n");
    printf("                        Performance Reports                           ");
    printf("\n==================================================================\n");

    float totalDistance = 0;
    float totalTime = 0;
    float totalRevenue = 0;
    float totalProfit = 0;
    float maxDistance = 0;
    float minDistance = INFINITY_VALUE;
    int maxDistanceIndex = 0;
    int minDistanceIndex = 0;

    for (int i = 0; i < deliveryCount; i++)
    {
        totalDistance += deliveryDistance[i];
        totalTime += deliveryTime[i];
        totalRevenue += deliveryRevenue[i];
        totalProfit += deliveryProfit[i];

        if (deliveryDistance[i] > maxDistance)
        {
            maxDistance = deliveryDistance[i];
            maxDistanceIndex = i;
        }
        if (deliveryDistance[i] < minDistance)
        {
            minDistance = deliveryDistance[i];
            minDistanceIndex = i;
        }
    }

    float avgTime = totalTime / deliveryCount;

    printf("\nSUMMARY STATISTICS\n");
    printf("  ------------------------------------------------------------\n");
    printf("  Total Deliveries Completed:     %d\n", deliveryCount);
    printf("  Total Distance Covered:         %.2f km\n", totalDistance);
    printf("  Average Delivery Time:          %.2f hours\n", avgTime);
    printf("  Total Revenue:                  %.2f LKR\n", totalRevenue);
    printf("  Total Profit:                   %.2f LKR\n", totalProfit);
    printf("\nROUTE STATISTICS\n");
    printf("  -------------------------------------------------------------\n");
    printf("  Longest Route:                  %.2f km\n", maxDistance);
    printf("    (%s => %s)\n", cities[deliverySource[maxDistanceIndex]], cities[deliveryDestination[maxDistanceIndex]]);
    printf("  Shortest Route:                 %.2f km\n", minDistance);
    printf("    (%s => %s)\n", cities[deliverySource[minDistanceIndex]], cities[deliveryDestination[minDistanceIndex]]);
}

void loadFromFiles() {
    FILE *routesFile = fopen("routes.txt", "r");
    if (routesFile != NULL) {
        fscanf(routesFile, "%d", &cityCount);
        for (int i = 0; i < cityCount; i++) {
            fscanf(routesFile, " %[^\n]", cities[i]);
        }

        for (int i = 0; i < cityCount; i++) {
            for (int j = 0; j < cityCount; j++) {
                fscanf(routesFile, "%d", &distances[i][j]);
            }
        }
        fclose(routesFile);
        printf("Routes data loaded successfully!\n");
    }

    FILE *deliveriesFile = fopen("deliveries.txt", "r");
    if (deliveriesFile != NULL) {
        fscanf(deliveriesFile, "%d", &deliveryCount);
        for (int i = 0; i < deliveryCount; i++) {
            fscanf(deliveriesFile, "%d %d %d %d %f %f %f %f %f",
                   &deliverySource[i],
                   &deliveryDestination[i],
                   &deliveryWeight[i],
                   &deliveryVehicle[i],
                   &deliveryDistance[i],
                   &deliveryCost[i],
                   &deliveryTime[i],
                   &deliveryRevenue[i],
                   &deliveryProfit[i]);
        }

        fclose(deliveriesFile);
        printf("Delivery records loaded successfully!\n");
    }
}

void saveToFiles() {
    FILE *routesFile = fopen("routes.txt", "w");
    if (routesFile != NULL) {
        fprintf(routesFile, "%d\n", cityCount);
        for (int i = 0; i < cityCount; i++) {
            fprintf(routesFile, "%s\n", cities[i]);
        }

        for (int i = 0; i < cityCount; i++) {
            for (int j = 0; j < cityCount; j++) {
                fprintf(routesFile, "%d ", distances[i][j]);
            }
            fprintf(routesFile, "\n");
        }

        fclose(routesFile);
    }

    FILE *deliveriesFile = fopen("deliveries.txt", "w");
    if (deliveriesFile != NULL) {
        fprintf(deliveriesFile, "%d\n", deliveryCount);
        for (int i = 0; i < deliveryCount; i++) {
            fprintf(deliveriesFile, "%d %d %d %d %.2f %.2f %.2f %.2f %.2f\n",
                    deliverySource[i],
                    deliveryDestination[i],
                    deliveryWeight[i],
                    deliveryVehicle[i],
                    deliveryDistance[i],
                    deliveryCost[i],
                    deliveryTime[i],
                    deliveryRevenue[i],
                    deliveryProfit[i]);
        }

        fclose(deliveriesFile);
    }
}
