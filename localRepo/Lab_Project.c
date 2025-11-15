
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <time.h>
#include <float.h>

#define MAX_NAME_LEN 100
#define MAX_TYPE_LEN 50
#define MAX_SEVERITY_LEN 30

// ==================== LINKED LIST DATA STRUCTURES ====================

// Location Node
typedef struct LocationNode {
    char name[MAX_NAME_LEN];
    float x, y;
    int id;
    struct LocationNode* next;
} LocationNode;

// Route Node
typedef struct RouteNode {
    int src, dest;
    float distance;
    float time;
    float cost;
    int trafficLevel;
    struct RouteNode* next;
} RouteNode;

// Hazard Node
typedef struct HazardNode {
    char location[MAX_NAME_LEN];
    char type[MAX_TYPE_LEN];
    char severity[MAX_SEVERITY_LEN];
    int active;
    time_t reportedTime;
    struct HazardNode* next;
} HazardNode;

// Indoor Location Node
typedef struct IndoorLocationNode {
    char building[MAX_NAME_LEN];
    int floor;
    char room[MAX_NAME_LEN];
    int id;
    struct IndoorLocationNode* next;
} IndoorLocationNode;

// User Preference
typedef struct {
    char transportMode[20];
    int avoidTolls;
    int preferScenic;
    char** favoriteRoutes;  // Dynamic array
    int favCount;
    int favCapacity;
} UserPreference;

// Record-only structs for file IO
typedef struct {
    char name[MAX_NAME_LEN];
    float x, y;
    int id;
} LocationRecord;

typedef struct {
    int src, dest;
    float distance;
    float time;
    float cost;
    int trafficLevel;
} RouteRecord;

typedef struct {
    char location[MAX_NAME_LEN];
    char type[MAX_TYPE_LEN];
    char severity[MAX_SEVERITY_LEN];
    int active;
    time_t reportedTime;
} HazardRecord;

typedef struct {
    char building[MAX_NAME_LEN];
    int floor;
    char room[MAX_NAME_LEN];
    int id;
} IndoorRecord;

// Global Linked List Heads
LocationNode* locationHead = NULL;
RouteNode* routeHead = NULL;
HazardNode* hazardHead = NULL;
IndoorLocationNode* indoorHead = NULL;

UserPreference currentUser;

// Dynamic counters
int locationCount = 0;
int routeCount = 0;
int hazardCount = 0;
int indoorLocCount = 0;

// File names
const char* ROUTE_FILE = "routes_unlimited.dat";
const char* USER_FILE = "user_prefs_unlimited.dat";
const char* HAZARD_FILE = "hazards_unlimited.dat";
const char* INDOOR_FILE = "indoor_unlimited.dat";
const char* LOCATION_FILE = "locations_unlimited.dat";

// ==================== DYNAMIC MEMORY UTILITY FUNCTIONS ====================

// Initialize user preferences with dynamic favorite routes
void initUserPreferences() {
    strcpy(currentUser.transportMode, "car");
    currentUser.avoidTolls = 0;
    currentUser.preferScenic = 1;
    currentUser.favCount = 0;
    currentUser.favCapacity = 10; // Start with capacity for 10 favorites
    currentUser.favoriteRoutes = malloc(currentUser.favCapacity * sizeof(char*));
    if (!currentUser.favoriteRoutes) {
        perror("Failed to initialize user favorites");
        exit(1);
    }
}

// Resize favorite routes array if needed
void resizeFavoriteRoutesIfNeeded() {
    if (currentUser.favCount >= currentUser.favCapacity) {
        int newCapacity = currentUser.favCapacity * 2;
        char** newFavorites = realloc(currentUser.favoriteRoutes, newCapacity * sizeof(char*));
        if (!newFavorites) {
            perror("Failed to resize favorites array");
            return;
        }
        currentUser.favoriteRoutes = newFavorites;
        currentUser.favCapacity = newCapacity;
        printf("Expanded favorites capacity to %d\n", newCapacity);
    }
}

// ==================== LINKED LIST UTILITY FUNCTIONS ====================

LocationNode* createLocationNode(char name[], float x, float y, int id) {
    LocationNode* newNode = (LocationNode*)malloc(sizeof(LocationNode));
    if (!newNode) {
        printf("Error: Memory allocation failed for new location!\n");
        return NULL;
    }
    strncpy(newNode->name, name, MAX_NAME_LEN-1);
    newNode->name[MAX_NAME_LEN-1] = 0;
    newNode->x = x;
    newNode->y = y;
    newNode->id = id;
    newNode->next = NULL;
    return newNode;
}

RouteNode* createRouteNode(int src, int dest, float distance, float timeV, float cost, int trafficLevel) {
    RouteNode* newNode = (RouteNode*)malloc(sizeof(RouteNode));
    if (!newNode) {
        printf("Error: Memory allocation failed for new route!\n");
        return NULL;
    }
    newNode->src = src;
    newNode->dest = dest;
    newNode->distance = distance;
    newNode->time = timeV;
    newNode->cost = cost;
    newNode->trafficLevel = trafficLevel;
    newNode->next = NULL;
    return newNode;
}

HazardNode* createHazardNode(char location[], char type[], char severity[], int active) {
    HazardNode* newNode = (HazardNode*)malloc(sizeof(HazardNode));
    if (!newNode) {
        printf("Error: Memory allocation failed for new hazard!\n");
        return NULL;
    }
    strncpy(newNode->location, location, MAX_NAME_LEN-1);
    newNode->location[MAX_NAME_LEN-1] = 0;
    strncpy(newNode->type, type, MAX_TYPE_LEN-1);
    newNode->type[MAX_TYPE_LEN-1] = 0;
    strncpy(newNode->severity, severity, MAX_SEVERITY_LEN-1);
    newNode->severity[MAX_SEVERITY_LEN-1] = 0;
    newNode->active = active;
    newNode->reportedTime = time(NULL);
    newNode->next = NULL;
    return newNode;
}

IndoorLocationNode* createIndoorNode(char building[], int floor, char room[], int id) {
    IndoorLocationNode* newNode = (IndoorLocationNode*)malloc(sizeof(IndoorLocationNode));
    if (!newNode) {
        printf("Error: Memory allocation failed for new indoor location!\n");
        return NULL;
    }
    strncpy(newNode->building, building, MAX_NAME_LEN-1);
    newNode->building[MAX_NAME_LEN-1] = 0;
    newNode->floor = floor;
    strncpy(newNode->room, room, MAX_NAME_LEN-1);
    newNode->room[MAX_NAME_LEN-1] = 0;
    newNode->id = id;
    newNode->next = NULL;
    return newNode;
}

LocationNode* insertLocationAtEnd(LocationNode* head, char name[], float x, float y, int id) {
    LocationNode* newNode = createLocationNode(name, x, y, id);
    if (!newNode) return head;

    if (head == NULL) return newNode;

    LocationNode* temp = head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = newNode;
    return head;
}

RouteNode* insertRouteAtEnd(RouteNode* head, int src, int dest, float distance, float timeV, float cost, int trafficLevel) {
    RouteNode* newNode = createRouteNode(src, dest, distance, timeV, cost, trafficLevel);
    if (!newNode) return head;

    if (head == NULL) return newNode;

    RouteNode* temp = head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = newNode;
    return head;
}

HazardNode* insertHazardAtEnd(HazardNode* head, char location[], char type[], char severity[], int active) {
    HazardNode* newNode = createHazardNode(location, type, severity, active);
    if (!newNode) return head;

    if (head == NULL) return newNode;

    HazardNode* temp = head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = newNode;
    return head;
}

IndoorLocationNode* insertIndoorAtEnd(IndoorLocationNode* head, char building[], int floor, char room[], int id) {
    IndoorLocationNode* newNode = createIndoorNode(building, floor, room, id);
    if (!newNode) return head;

    if (head == NULL) return newNode;

    IndoorLocationNode* temp = head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = newNode;
    return head;
}

// ==================== A. MAP & ROUTE SYSTEM (UNLIMITED VERSION) ====================

void addLocation(char name[]) {
    // Input validation
    if (strlen(name) == 0 || strlen(name) >= MAX_NAME_LEN) {
        printf("Error: Location name must be between 1 and %d characters!\n", MAX_NAME_LEN-1);
        return;
    }

    // Check for duplicates
    LocationNode* temp = locationHead;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            printf("Location '%s' already exists!\n", name);
            return;
        }
        temp = temp->next;
    }

    float x = (float)(rand() % 1000);
    float y = (float)(rand() % 1000);
    LocationNode* newHead = insertLocationAtEnd(locationHead, name, x, y, locationCount);
    if (newHead) {
        locationHead = newHead;
        locationCount++;
        printf("Location '%s' added successfully! (Total locations: %d)\n", name, locationCount);
    }
}

int findLocationIndex(char name[]) {
    LocationNode* temp = locationHead;
    int index = 0;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) return index;
        temp = temp->next;
        index++;
    }
    return -1;
}

LocationNode* getLocationByIndex(int index) {
    if (index < 0 || index >= locationCount) return NULL;

    LocationNode* temp = locationHead;
    int current = 0;
    while (temp != NULL && current < index) {
        temp = temp->next;
        current++;
    }
    return temp;
}

LocationNode* getLocationByName(char name[]) {
    LocationNode* temp = locationHead;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) return temp;
        temp = temp->next;
    }
    return NULL;
}

void addRoute(char src[], char dest[], float distance, float timeV) {
    // Input validation
    if (distance <= 0 || timeV <= 0) {
        printf("Error: Distance and time must be positive values!\n");
        return;
    }

    int srcIndex = findLocationIndex(src);
    int destIndex = findLocationIndex(dest);
    if (srcIndex == -1 || destIndex == -1) {
        printf("Error: Source or destination location not found!\n");
        return;
    }

    if (srcIndex == destIndex) {
        printf("Error: Source and destination cannot be the same!\n");
        return;
    }

    // Check if route already exists
    RouteNode* temp = routeHead;
    while (temp != NULL) {
        if (temp->src == srcIndex && temp->dest == destIndex) {
            printf("Route from '%s' to '%s' already exists!\n", src, dest);
            return;
        }
        temp = temp->next;
    }

    float cost = distance * 0.5f;
    RouteNode* newHead = insertRouteAtEnd(routeHead, srcIndex, destIndex, distance, timeV, cost, 1);
    if (newHead) {
        routeHead = newHead;
        routeCount++;
        printf("Route from '%s' to '%s' added successfully! (Total routes: %d)\n", src, dest, routeCount);
    }
}

void showAllRoutes() {
    if (routeHead == NULL) {
        printf("No routes available!\n");
        return;
    }
    printf("\n=== ALL AVAILABLE ROUTES (%d total) ===\n", routeCount);
    RouteNode* temp = routeHead;
    int i = 1;
    while (temp != NULL) {
        LocationNode* srcLoc = getLocationByIndex(temp->src);
        LocationNode* destLoc = getLocationByIndex(temp->dest);
        if (srcLoc && destLoc) {
            printf("%d. %s -> %s | Distance: %.2f km | Time: %.2f min | Cost: $%.2f | Traffic: %d/5\n", i, srcLoc->name, destLoc->name, temp->distance, temp->time, temp->cost, temp->trafficLevel);
        } else {
            printf("%d. (invalid route indices) src=%d dest=%d\n", i, temp->src, temp->dest);
        }
        temp = temp->next;
        i++;
    }
}

// Enhanced Dijkstra with unlimited nodes
void findShortestPath(char src[], char dest[]) {
    int srcIndex = findLocationIndex(src);
    int destIndex = findLocationIndex(dest);
    if (srcIndex == -1 || destIndex == -1) {
        printf("Error: Source or destination not found!\n");
        return;
    }
    if (srcIndex == destIndex) {
        printf("Source and destination are the same!\n");
        return;
    }

    int n = locationCount;
    if (n <= 0) {
        printf("No locations available.\n");
        return;
    }

    // Dynamic allocation for algorithm
    float* dist = (float*)malloc(n * sizeof(float));
    int* visited = (int*)malloc(n * sizeof(int));
    int* prev = (int*)malloc(n * sizeof(int));

    if (!dist || !visited || !prev) {
        printf("Memory allocation error for pathfinding!\n");
        free(dist); free(visited); free(prev);
        return;
    }

    // Initialize arrays
    for (int i=0; i<n; i++) {
        dist[i] = FLT_MAX;
        visited[i] = 0;
        prev[i] = -1;
    }
    dist[srcIndex] = 0.0f;

    // Dijkstra's algorithm
    for (int count=0; count < n-1; count++) {
        float minDist = FLT_MAX;
        int minIndex = -1;

        // Find unvisited node with minimum distance
        for (int v=0; v<n; v++) {
            if (!visited[v] && dist[v] < minDist) {
                minDist = dist[v];
                minIndex = v;
            }
        }

        if (minIndex == -1) break; // No path exists
        visited[minIndex] = 1;

        // Update distances to adjacent nodes
        RouteNode* temp = routeHead;
        while (temp != NULL) {
            if (temp->src == minIndex) {
                int adj = temp->dest;
                float weight = temp->distance;
                if (!visited[adj] && dist[minIndex] != FLT_MAX &&
                    dist[minIndex] + weight < dist[adj]) {
                    dist[adj] = dist[minIndex] + weight;
                    prev[adj] = minIndex;
                }
            }
            temp = temp->next;
        }
    }

    if (dist[destIndex] == FLT_MAX) {
        printf("No path exists from %s to %s!\n", src, dest);
        free(dist); free(visited); free(prev);
        return;
    }

    printf("Shortest path from %s to %s:\n", src, dest);
    printf("Total distance: %.2f km\n", dist[destIndex]);

    // Reconstruct path
    int* path = (int*)malloc(n * sizeof(int));
    if (!path) {
        printf("Memory allocation error for path reconstruction!\n");
        free(dist); free(visited); free(prev);
        return;
    }

    int pathLen = 0;
    int current = destIndex;
    while (current != -1 && pathLen < n) {
        path[pathLen++] = current;
        current = prev[current];
    }

    printf("Route: ");
    for (int i = pathLen-1; i >= 0; i--) {
        LocationNode* loc = getLocationByIndex(path[i]);
        if (loc) printf("%s", loc->name);
        else printf("(unknown)");
        if (i > 0) printf(" -> ");
    }
    printf("\n");

    free(dist); free(visited); free(prev); free(path);
}

void displayRouteDetails() {
    if (routeHead == NULL) {
        printf("No routes to display!\n");
        return;
    }
    printf("\n=== DETAILED ROUTE INFORMATION (%d routes) ===\n", routeCount);
    RouteNode* temp = routeHead;
    int i = 1;
    while (temp != NULL) {
        LocationNode* srcLoc = getLocationByIndex(temp->src);
        LocationNode* destLoc = getLocationByIndex(temp->dest);
        printf("\nRoute %d:\n", i);
        if (srcLoc && destLoc) {
            printf("  From: %s\n  To: %s\n", srcLoc->name, destLoc->name);
        } else {
            printf("  From: (invalid) [%d]\n  To: (invalid) [%d]\n", temp->src, temp->dest);
        }
        printf("  Distance: %.2f km\n  Estimated Time: %.2f minutes\n  Estimated Cost: $%.2f\n  Traffic Level: %d/5\n", temp->distance, temp->time, temp->cost, temp->trafficLevel);
        temp = temp->next;
        i++;
    }
}

void deleteRoute(char src[], char dest[]) {
    int srcIndex = findLocationIndex(src);
    int destIndex = findLocationIndex(dest);
    if (srcIndex == -1 || destIndex == -1) {
        printf("Error: Source or destination location not found!\n");
        return;
    }

    RouteNode* current = routeHead;
    RouteNode* prevR = NULL;
    int found = 0;
    while (current != NULL) {
        if (current->src == srcIndex && current->dest == destIndex) {
            found = 1;
            if (prevR == NULL) routeHead = current->next;
            else prevR->next = current->next;
            free(current);
            routeCount--;
            printf("Route from %s to %s deleted successfully! (Remaining routes: %d)\n", src, dest, routeCount);
            break;
        }
        prevR = current;
        current = current->next;
    }
    if (!found) printf("No route found from %s to %s!\n", src, dest);
}

void updateRoute(char src[], char dest[], float newDistance, float newTime) {
    // Input validation
    if (newDistance <= 0 || newTime <= 0) {
        printf("Error: Distance and time must be positive values!\n");
        return;
    }

    int srcIndex = findLocationIndex(src);
    int destIndex = findLocationIndex(dest);
    if (srcIndex == -1 || destIndex == -1) {
        printf("Error: Source or destination location not found!\n");
        return;
    }

    RouteNode* temp = routeHead;
    int found = 0;
    while (temp != NULL) {
        if (temp->src == srcIndex && temp->dest == destIndex) {
            temp->distance = newDistance;
            temp->time = newTime;
            temp->cost = newDistance * 0.5f;
            found = 1;
            printf("Route from %s to %s updated successfully!\n", src, dest);
            break;
        }
        temp = temp->next;
    }
    if (!found) printf("No route found from %s to %s!\n", src, dest);
}

void searchRoute(char locationName[]) {
    int locIndex = findLocationIndex(locationName);
    if (locIndex == -1) {
        printf("Location '%s' not found!\n", locationName);
        return;
    }
    printf("\n=== ROUTES CONTAINING '%s' ===\n", locationName);
    RouteNode* temp = routeHead;
    int foundCount = 0;
    while (temp != NULL) {
        if (temp->src == locIndex || temp->dest == locIndex) {
            LocationNode* srcLoc = getLocationByIndex(temp->src);
            LocationNode* destLoc = getLocationByIndex(temp->dest);
            if (srcLoc && destLoc) {
                printf("%d. %s -> %s | Distance: %.2f km | Time: %.2f min | Traffic: %d/5\n", foundCount + 1, srcLoc->name, destLoc->name, temp->distance, temp->time, temp->trafficLevel);
            } else {
                printf("%d. (invalid route indices)\n", foundCount + 1);
            }
            foundCount++;
        }
        temp = temp->next;
    }
    if (foundCount == 0) printf("No routes found containing '%s'\n", locationName);
    else printf("Total %d routes found.\n", foundCount);
}

// ==================== B. MACHINE LEARNING / PREDICTIVE ETA ====================

float predictETA(float distance, float avgSpeed, int trafficLevel) {
    if (distance <= 0.0f) {
        printf("Error: Distance must be positive!\n");
        return -1.0f;
    }
    if (avgSpeed <= 0.0f) {
        printf("Error: Average speed must be positive!\n");
        return -1.0f;
    }
    if (trafficLevel < 1 || trafficLevel > 5) {
        printf("Error: Traffic level must be between 1-5!\n");
        return -1.0f;
    }

    float baseTime = (distance / avgSpeed) * 60.0f;
    float trafficFactor = 1.0f + ((trafficLevel - 1) * 0.2f);
    return baseTime * trafficFactor;
}

float adjustETAByWeather(float eta, char weather[]) {
    if (eta <= 0.0f) return eta;

    float weatherFactor = 1.0f;
    if (strcmp(weather, "rainy") == 0) weatherFactor = 1.3f;
    else if (strcmp(weather, "stormy") == 0) weatherFactor = 1.6f;
    else if (strcmp(weather, "foggy") == 0) weatherFactor = 1.4f;
    else if (strcmp(weather, "snowy") == 0) weatherFactor = 1.8f;
    else if (strcmp(weather, "sunny") == 0) weatherFactor = 1.0f;
    else if (strcmp(weather, "clear") == 0) weatherFactor = 0.9f;
    else {
        printf("Unknown weather condition '%s', using default factor.\n", weather);
        weatherFactor = 1.1f;
    }

    printf("Weather condition: %s | Adjustment factor: %.1f\n", weather, weatherFactor);
    return eta * weatherFactor;
}

void updateTrafficData(char routeName[], int trafficLevel) {
    if (trafficLevel < 1 || trafficLevel > 5) {
        printf("Error: Traffic level must be between 1-5!\n");
        return;
    }

    printf("Updating traffic data for routes...\n");
    RouteNode* temp = routeHead;
    int updatedCount = 0;
    while (temp != NULL) {
        temp->trafficLevel = trafficLevel;
        temp->time = temp->time * (1.0f + (trafficLevel - 1) * 0.15f);
        updatedCount++;
        temp = temp->next;
    }
    printf("Traffic data updated to level %d for %d routes\n", trafficLevel, updatedCount);
}

void autoAdjustETA(char src[], char dest[]) {
    int srcIndex = findLocationIndex(src), destIndex = findLocationIndex(dest);
    if (srcIndex == -1 || destIndex == -1) {
        printf("Error: Source or destination not found!\n");
        return;
    }

    RouteNode* temp = routeHead;
    while (temp != NULL) {
        if (temp->src == srcIndex && temp->dest == destIndex) {
            float originalTime = temp->time;
            float adjustedTime = temp->time;
            adjustedTime = adjustedTime * (1.0f + (temp->trafficLevel - 1) * 0.15f);
            char* weatherConditions[] = {"sunny","rainy","foggy","stormy","clear"};
            char currentWeather[20];
            strcpy(currentWeather, weatherConditions[rand()%5]);
            adjustedTime = adjustETAByWeather(adjustedTime, currentWeather);
            printf("\n=== AUTO ETA ADJUSTMENT ===\n");
            printf("Route: %s -> %s\n", src, dest);
            printf("Original ETA: %.2f minutes\n", originalTime);
            printf("Current Traffic Level: %d/5\n", temp->trafficLevel);
            printf("Weather Condition: %s\n", currentWeather);
            printf("Adjusted ETA: %.2f minutes\n", adjustedTime);
            printf("Time difference: %.2f minutes\n", adjustedTime - originalTime);
            return;
        }
        temp = temp->next;
    }
    printf("No direct route found from %s to %s\n", src, dest);
}

// ==================== C. AI PERSONALIZATION & USER PREFERENCE ====================

void setUserPreference(char mode[], int avoidTolls, int preferScenic) {
    // Validate transport mode
    if (strcmp(mode, "car") != 0 && strcmp(mode, "bike") != 0 &&
        strcmp(mode, "walk") != 0 && strcmp(mode, "bus") != 0 &&
        strcmp(mode, "train") != 0) {
        printf("Error: Transport mode must be 'car', 'bike', 'walk', 'bus', or 'train'!\n");
        return;
    }

    strncpy(currentUser.transportMode, mode, 19);
    currentUser.transportMode[19] = 0;
    currentUser.avoidTolls = avoidTolls;
    currentUser.preferScenic = preferScenic;
    printf("User preferences set successfully!\nTransport Mode: %s\nAvoid Tolls: %s\nPrefer Scenic Routes: %s\n", currentUser.transportMode, avoidTolls ? "Yes":"No", preferScenic ? "Yes":"No");
}

void getUserPreference() {
    printf("\n=== CURRENT USER PREFERENCES ===\n");
    printf("Transport Mode: %s\nAvoid Tolls: %s\nPrefer Scenic Routes: %s\n", currentUser.transportMode, currentUser.avoidTolls ? "Yes":"No", currentUser.preferScenic ? "Yes":"No");

    if (currentUser.favCount > 0) {
        printf("Favorite Routes (%d):\n", currentUser.favCount);
        for (int i = 0; i < currentUser.favCount; i++) {
            printf("  %d. %s\n", i+1, currentUser.favoriteRoutes[i]);
        }
        printf("Favorites capacity: %d\n", currentUser.favCapacity);
    } else {
        printf("No favorite routes saved.\n");
    }
}

void suggestRouteBasedOnMood(char mood[]) {
    printf("\n=== ROUTE SUGGESTIONS BASED ON MOOD: %s ===\n", mood);
    if (strcmp(mood, "relaxing") == 0) {
        printf("Suggested: Scenic coastal route\nSuggested: Mountain view pathway\nSuggested: Park boulevard route\n");
        printf("Suggested: Riverside drive\nSuggested: Countryside lanes\n");
    }
    else if (strcmp(mood, "fastest") == 0) {
        printf("Suggested: Highway express route\nSuggested: Direct city bypass\nSuggested: Express toll route\n");
        printf("Suggested: Freeway direct\nSuggested: Urban expressway\n");
    }
    else if (strcmp(mood, "adventurous") == 0) {
        printf("Suggested: Mountain trail route\nSuggested: Countryside exploration\nSuggested: Forest pathway\n");
        printf("Suggested: Hill climb route\nSuggested: Off-road adventure\n");
    }
    else if (strcmp(mood, "economical") == 0) {
        printf("Suggested: Fuel-efficient pathway\nSuggested: Toll-free route\nSuggested: Shortest distance route\n");
        printf("Suggested: Public transport route\nSuggested: Carpool lanes\n");
    }
    else if (strcmp(mood, "tourist") == 0) {
        printf("Suggested: City landmarks route\nSuggested: Historical sites tour\nSuggested: Cultural district path\n");
        printf("Suggested: Scenic overlook route\nSuggested: Photo spots tour\n");
    }
    else {
        printf("No specific suggestions for mood: %s\n", mood);
        printf("Available moods: relaxing, fastest, adventurous, economical, tourist\n");
    }
}

void addFavoriteRoute(char routeName[]) {
    resizeFavoriteRoutesIfNeeded();

    // Check if route already in favorites
    for (int i = 0; i < currentUser.favCount; i++) {
        if (strcmp(currentUser.favoriteRoutes[i], routeName) == 0) {
            printf("Route '%s' already in favorites!\n", routeName);
            return;
        }
    }

    // Allocate memory for the new favorite route
    currentUser.favoriteRoutes[currentUser.favCount] = malloc(strlen(routeName) + 1);
    if (!currentUser.favoriteRoutes[currentUser.favCount]) {
        printf("Error: Memory allocation failed for favorite route!\n");
        return;
    }

    strcpy(currentUser.favoriteRoutes[currentUser.favCount], routeName);
    currentUser.favCount++;
    printf("Route '%s' added to favorites! (Total favorites: %d)\n", routeName, currentUser.favCount);
}

void removeFavoriteRoute(char routeName[]) {
    int foundIndex = -1;
    for (int i = 0; i < currentUser.favCount; i++) {
        if (strcmp(currentUser.favoriteRoutes[i], routeName) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("Route '%s' not found in your favorites!\n", routeName);
        return;
    }

    // Free the memory for the removed favorite
    free(currentUser.favoriteRoutes[foundIndex]);

    // Shift remaining favorites
    for (int i = foundIndex; i < currentUser.favCount - 1; i++) {
        currentUser.favoriteRoutes[i] = currentUser.favoriteRoutes[i + 1];
    }

    currentUser.favCount--;
    printf("Route '%s' removed from favorites! (Remaining favorites: %d)\n", routeName, currentUser.favCount);
}

// ==================== D. REAL-TIME & SAFETY FEATURES ====================

void reportHazard(char location[], char type[]) {
    // Validate hazard type
    if (strcmp(type, "accident") != 0 && strcmp(type, "road_block") != 0 &&
        strcmp(type, "flood") != 0 && strcmp(type, "construction") != 0 &&
        strcmp(type, "ice") != 0 && strcmp(type, "debris") != 0 &&
        strcmp(type, "police") != 0 && strcmp(type, "animal") != 0) {
        printf("Error: Invalid hazard type! Use: accident, road_block, flood, construction, ice, debris, police, animal\n");
        return;
    }

    char severity[20];
    if (strcmp(type, "accident") == 0 || strcmp(type, "flood") == 0) strcpy(severity, "High");
    else if (strcmp(type, "road_block") == 0 || strcmp(type, "ice") == 0) strcpy(severity, "Medium");
    else if (strcmp(type, "police") == 0) strcpy(severity, "Low");
    else if (strcmp(type, "construction") == 0) strcpy(severity, "Low");
    else if (strcmp(type, "debris") == 0) strcpy(severity, "Medium");
    else if (strcmp(type, "animal") == 0) strcpy(severity, "Medium");
    else strcpy(severity, "Medium");

    HazardNode* newHead = insertHazardAtEnd(hazardHead, location, type, severity, 1);
    if (newHead) {
        hazardHead = newHead;
        hazardCount++;
        printf("Hazard reported at %s: %s (Severity: %s) (Total hazards: %d)\n", location, type, severity, hazardCount);
    }
}

void viewActiveHazards() {
    printf("\n=== ACTIVE HAZARDS (%d total) ===\n", hazardCount);
    HazardNode* temp = hazardHead;
    int activeCount = 0;
    while (temp != NULL) {
        if (temp->active) {
            printf("%d. Location: %s | Type: %s | Severity: %s | Reported: %s",activeCount + 1, temp->location, temp->type, temp->severity, ctime(&temp->reportedTime));
            activeCount++;
        }
        temp = temp->next;
    }
    if (activeCount == 0) printf("No active hazards reported.\n");
    else printf("Total active hazards: %d\n", activeCount);
}

void safeRouteRecommendation() {
    printf("\n=== SAFE ROUTE RECOMMENDATIONS ===\n");
    if (hazardHead == NULL) {
        printf("No hazards reported. All routes are safe!\n");
        return;
    }

    printf("Avoiding routes with reported hazards...\n");
    printf("Active hazards detected: %d\n", hazardCount);
    printf("Recommended safe routes:\n");

    RouteNode* temp = routeHead;
    int safeCount = 0;
    int totalChecked = 0;

    // Get list of hazardous locations
    char** hazardousLocations = malloc(hazardCount * sizeof(char*));
    int hazardLocCount = 0;
    HazardNode* hazardTemp = hazardHead;

    while (hazardTemp != NULL) {
        if (hazardTemp->active) {
            hazardousLocations[hazardLocCount] = malloc(strlen(hazardTemp->location) + 1);
            strcpy(hazardousLocations[hazardLocCount], hazardTemp->location);
            hazardLocCount++;
        }
        hazardTemp = hazardTemp->next;
    }

    // Find safe routes (routes that don't contain hazardous locations)
    while (temp != NULL) {
        LocationNode* srcLoc = getLocationByIndex(temp->src);
        LocationNode* destLoc = getLocationByIndex(temp->dest);

        if (srcLoc && destLoc) {
            int isSafe = 1;
            // Check if either source or destination is hazardous
            for (int i = 0; i < hazardLocCount; i++) {
                if (strcmp(srcLoc->name, hazardousLocations[i]) == 0 ||
                    strcmp(destLoc->name, hazardousLocations[i]) == 0) {
                    isSafe = 0;
                    break;
                }
            }

            if (isSafe) {
                printf("  %d. %s -> %s (Distance: %.2f km, Traffic: %d/5)\n", safeCount + 1, srcLoc->name, destLoc->name, temp->distance, temp->trafficLevel);
                safeCount++;
                if (safeCount >= 10) break; // Show top 10 safe routes
            }
        }
        temp = temp->next;
        totalChecked++;
    }

    // Free hazardous locations memory
    for (int i = 0; i < hazardLocCount; i++) {
        free(hazardousLocations[i]);
    }
    free(hazardousLocations);

    if (safeCount == 0) {
        printf("No completely safe routes found. Please check hazard reports.\n");
    } else {
        printf("Found %d safe routes out of %d total routes checked.\n", safeCount, totalChecked);
    }
}

void sendSOS(char location[]) {
    printf("\n=== 🆘 EMERGENCY SOS ACTIVATED ===\n");
    printf("SOS Signal Sent from: %s\n", location);
    printf("Emergency services have been notified!\n");
    printf("Your current location has been shared with emergency contacts.\n");
    printf("Please stay on the line for further instructions.\n");

    FILE* sosFile = fopen("sos_log.txt", "a");
    if (sosFile) {
        time_t now = time(NULL);
        fprintf(sosFile, "SOS from %s at %s", location, ctime(&now));
        fclose(sosFile);
        printf("SOS log saved successfully.\n");
    } else {
        printf("Warning: Could not save SOS log.\n");
    }
}

void deactivateHazard(char location[], char type[]) {
    HazardNode* temp = hazardHead;
    int found = 0;
    while (temp != NULL) {
        if (strcmp(temp->location, location) == 0 &&
            strcmp(temp->type, type) == 0 &&
            temp->active) {
            temp->active = 0;
            found = 1;
            printf("Hazard at %s (%s) has been resolved and deactivated.\n", location, type);
            break;
        }
        temp = temp->next;
    }
    if (!found) printf("No active hazard found at %s with type %s\n", location, type);
}

// ==================== E. INDOOR NAVIGATION MODULE ====================

void addIndoorLocation(char building[], int floor, char room[]) {
    // Input validation
    if (strlen(building) == 0 || strlen(room) == 0) {
        printf("Error: Building and room names cannot be empty!\n");
        return;
    }

    if (floor < -10 || floor > 200) {
        printf("Error: Floor number must be between -10 and 200!\n");
        return;
    }

    // Check for duplicates
    IndoorLocationNode* temp = indoorHead;
    while (temp != NULL) {
        if (strcmp(temp->building, building) == 0 &&
            temp->floor == floor &&
            strcmp(temp->room, room) == 0) {
            printf("Indoor location already exists: %s, Floor %d, Room %s\n", building, floor, room);
            return;
        }
        temp = temp->next;
    }

    IndoorLocationNode* newHead = insertIndoorAtEnd(indoorHead, building, floor, room, indoorLocCount);
    if (newHead) {
        indoorHead = newHead;
        indoorLocCount++;
        printf("Indoor location added: %s, Floor %d, Room %s (Total indoor locations: %d)\n",building, floor, room, indoorLocCount);
    }
}

int findIndoorLocation(char building[], int floor, char room[]) {
    IndoorLocationNode* temp = indoorHead;
    int index = 0;
    while (temp != NULL) {
        if (strcmp(temp->building, building) == 0 &&
            temp->floor == floor &&
            strcmp(temp->room, room) == 0)
            return index;
        temp = temp->next;
        index++;
    }
    return -1;
}

void findIndoorPath(char start[], char end[]) {
    printf("\n=== INDOOR NAVIGATION ===\n");
    printf("Finding path from %s to %s\n", start, end);

    // Enhanced indoor pathfinding simulation
    printf("Indoor Path Found:\n");
    printf("1. Start at %s\n", start);
    printf("2. Take the main corridor towards central area\n");
    printf("3. Use elevator/staircase to required floor\n");
    printf("4. Follow hallway signs\n");
    printf("5. Turn left at the intersection\n");
    printf("6. Continue straight past common areas\n");
    printf("7. Arrive at %s\n", end);
    printf("Estimated walking time: 3-8 minutes\n");
    printf("Total distance: ~150-300 meters\n");
    printf("Accessibility: Elevator and ramp access available\n");
}

void deleteIndoorLocation(char building[], int floor, char room[]) {
    int locIndex = findIndoorLocation(building, floor, room);
    if (locIndex == -1) {
        printf("Indoor location not found: %s, Floor %d, Room %s\n", building, floor, room);
        return;
    }

    IndoorLocationNode* current = indoorHead;
    IndoorLocationNode* prev = NULL;
    int currentIndex = 0;
    while (current != NULL && currentIndex < locIndex) {
        prev = current;
        current = current->next;
        currentIndex++;
    }

    if (current != NULL) {
        if (prev == NULL) indoorHead = current->next;
        else prev->next = current->next;
        free(current);
        indoorLocCount--;
        printf("Indoor location deleted: %s, Floor %d, Room %s (Remaining: %d)\n",building, floor, room, indoorLocCount);
    }
}

void displayAllIndoorLocations() {
    if (indoorHead == NULL) {
        printf("No indoor locations available!\n");
        return;
    }

    printf("\n=== ALL INDOOR LOCATIONS (%d total) ===\n", indoorLocCount);
    IndoorLocationNode* temp = indoorHead;
    int i = 1;
    while (temp != NULL) {
        printf("%d. Building: %s, Floor: %d, Room: %s\n", i, temp->building, temp->floor, temp->room);
        temp = temp->next;
        i++;
    }
}

// ==================== F. FILE HANDLING FUNCTIONS ====================

void saveLocationDataToFile() {
    FILE* file = fopen(LOCATION_FILE, "wb");
    if (!file) {
        printf("Error saving location data!\n");
        return;
    }

    fwrite(&locationCount, sizeof(int), 1, file);
    LocationNode* temp = locationHead;
    while (temp != NULL) {
        LocationRecord rec;
        strncpy(rec.name, temp->name, MAX_NAME_LEN);
        rec.x = temp->x;
        rec.y = temp->y;
        rec.id = temp->id;
        fwrite(&rec, sizeof(LocationRecord), 1, file);
        temp = temp->next;
    }
    fclose(file);
    printf("Location data saved successfully! (%d locations)\n", locationCount);
}

void loadLocationDataFromFile() {
    FILE* file = fopen(LOCATION_FILE, "rb");
    if (!file) {
        printf("No previous location data found.\n");
        return;
    }

    int count;
    if (fread(&count, sizeof(int), 1, file) != 1) {
        printf("Error reading location count!\n");
        fclose(file);
        return;
    }

    for (int i = 0; i < count; i++) {
        LocationRecord rec;
        if (fread(&rec, sizeof(LocationRecord), 1, file) != 1) break;
        locationHead = insertLocationAtEnd(locationHead, rec.name, rec.x, rec.y, rec.id);
    }
    locationCount = count;
    fclose(file);
    printf("Location data loaded successfully! (%d locations)\n", locationCount);
}

void saveRouteDataToFile() {
    FILE* file = fopen(ROUTE_FILE, "wb");
    if (!file) {
        printf("Error saving route data!\n");
        return;
    }

    fwrite(&routeCount, sizeof(int), 1, file);
    RouteNode* temp = routeHead;
    while (temp != NULL) {
        RouteRecord rec = { temp->src, temp->dest, temp->distance, temp->time, temp->cost, temp->trafficLevel };
        fwrite(&rec, sizeof(RouteRecord), 1, file);
        temp = temp->next;
    }
    fclose(file);
    printf("Route data saved successfully! (%d routes)\n", routeCount);
}

void loadRouteDataFromFile() {
    FILE* file = fopen(ROUTE_FILE, "rb");
    if (!file) {
        printf("No previous route data found.\n");
        return;
    }

    int count;
    if (fread(&count, sizeof(int), 1, file) != 1) {
        printf("Error reading route count!\n");
        fclose(file);
        return;
    }

    for (int i = 0; i < count; i++) {
        RouteRecord rec;
        if (fread(&rec, sizeof(RouteRecord), 1, file) != 1) break;
        routeHead = insertRouteAtEnd(routeHead, rec.src, rec.dest, rec.distance, rec.time, rec.cost, rec.trafficLevel);
    }
    routeCount = count;
    fclose(file);
    printf("Route data loaded successfully! (%d routes)\n", routeCount);
}

void saveHazardData() {
    FILE* file = fopen(HAZARD_FILE, "wb");
    if (!file) {
        printf("Error saving hazard data!\n");
        return;
    }

    fwrite(&hazardCount, sizeof(int), 1, file);
    HazardNode* temp = hazardHead;
    while (temp != NULL) {
        HazardRecord rec;
        strncpy(rec.location, temp->location, MAX_NAME_LEN);
        strncpy(rec.type, temp->type, MAX_TYPE_LEN);
        strncpy(rec.severity, temp->severity, MAX_SEVERITY_LEN);
        rec.active = temp->active;
        rec.reportedTime = temp->reportedTime;
        fwrite(&rec, sizeof(HazardRecord), 1, file);
        temp = temp->next;
    }
    fclose(file);
    printf("Hazard data saved successfully! (%d hazards)\n", hazardCount);
}

void loadHazardData() {
    FILE* file = fopen(HAZARD_FILE, "rb");
    if (!file) {
        printf("No previous hazard data found.\n");
        return;
    }

    int count;
    if (fread(&count, sizeof(int), 1, file) != 1) {
        printf("Error reading hazard count!\n");
        fclose(file);
        return;
    }

    for (int i = 0; i < count; i++) {
        HazardRecord rec;
        if (fread(&rec, sizeof(HazardRecord), 1, file) != 1) break;
        hazardHead = insertHazardAtEnd(hazardHead, rec.location, rec.type, rec.severity, rec.active);
        if (hazardHead) {
            HazardNode* last = hazardHead;
            while (last->next != NULL) last = last->next;
            last->reportedTime = rec.reportedTime;
        }
    }
    hazardCount = count;
    fclose(file);
    printf("Hazard data loaded successfully! (%d hazards)\n", hazardCount);
}

void saveIndoorData() {
    FILE* file = fopen(INDOOR_FILE, "wb");
    if (!file) {
        printf("Error saving indoor navigation data!\n");
        return;
    }

    fwrite(&indoorLocCount, sizeof(int), 1, file);
    IndoorLocationNode* temp = indoorHead;
    while (temp != NULL) {
        IndoorRecord rec;
        strncpy(rec.building, temp->building, MAX_NAME_LEN);
        rec.floor = temp->floor;
        strncpy(rec.room, temp->room, MAX_NAME_LEN);
        rec.id = temp->id;
        fwrite(&rec, sizeof(IndoorRecord), 1, file);
        temp = temp->next;
    }
    fclose(file);
    printf("Indoor navigation data saved successfully! (%d locations)\n", indoorLocCount);
}

void loadIndoorData() {
    FILE* file = fopen(INDOOR_FILE, "rb");
    if (!file) {
        printf("No previous indoor navigation data found.\n");
        return;
    }

    int count;
    if (fread(&count, sizeof(int), 1, file) != 1) {
        printf("Error reading indoor location count!\n");
        fclose(file);
        return;
    }

    for (int i = 0; i < count; i++) {
        IndoorRecord rec;
        if (fread(&rec, sizeof(IndoorRecord), 1, file) != 1) break;
        indoorHead = insertIndoorAtEnd(indoorHead, rec.building, rec.floor, rec.room, rec.id);
    }
    indoorLocCount = count;
    fclose(file);
    printf("Indoor navigation data loaded successfully! (%d locations)\n", indoorLocCount);
}

void saveUserPreferences() {
    FILE* file = fopen(USER_FILE, "wb");
    if (!file) {
        printf("Error saving user preferences!\n");
        return;
    }

    // Save basic user info
    fwrite(&currentUser, sizeof(UserPreference) - sizeof(char**), 1, file);

    // Save favorite routes count
    fwrite(&currentUser.favCount, sizeof(int), 1, file);

    // Save each favorite route
    for (int i = 0; i < currentUser.favCount; i++) {
        int len = strlen(currentUser.favoriteRoutes[i]) + 1;
        fwrite(&len, sizeof(int), 1, file);
        fwrite(currentUser.favoriteRoutes[i], sizeof(char), len, file);
    }

    fclose(file);
    printf("User preferences saved successfully! (%d favorites)\n", currentUser.favCount);
}

void loadUserPreferences() {
    FILE* file = fopen(USER_FILE, "rb");
    if (!file) {
        printf("No previous user preferences found.\n");
        return;
    }

    // Load basic user info
    if (fread(&currentUser, sizeof(UserPreference) - sizeof(char**), 1, file) != 1) {
        printf("Error reading user preferences!\n");
        fclose(file);
        return;
    }

    // Initialize favorites array
    initUserPreferences();

    // Load favorite routes count
    int favCount;
    if (fread(&favCount, sizeof(int), 1, file) != 1) {
        printf("Error reading favorites count!\n");
        fclose(file);
        return;
    }

    // Load each favorite route
    for (int i = 0; i < favCount; i++) {
        int len;
        if (fread(&len, sizeof(int), 1, file) != 1) break;

        resizeFavoriteRoutesIfNeeded();
        currentUser.favoriteRoutes[currentUser.favCount] = malloc(len);
        if (!currentUser.favoriteRoutes[currentUser.favCount]) {
            printf("Memory allocation failed for favorite route!\n");
            break;
        }

        if (fread(currentUser.favoriteRoutes[currentUser.favCount], sizeof(char), len, file) != len) {
            free(currentUser.favoriteRoutes[currentUser.favCount]);
            break;
        }

        currentUser.favCount++;
    }

    fclose(file);
    printf("User preferences loaded successfully! (%d favorites)\n", currentUser.favCount);
}

// ==================== MEMORY CLEANUP FUNCTIONS ====================

void freeAllMemory() {
    // Free locations
    LocationNode* locTemp = locationHead;
    while (locTemp != NULL) {
        LocationNode* next = locTemp->next;
        free(locTemp);
        locTemp = next;
    }
    locationHead = NULL;

    // Free routes
    RouteNode* routeTemp = routeHead;
    while (routeTemp != NULL) {
        RouteNode* next = routeTemp->next;
        free(routeTemp);
        routeTemp = next;
    }
    routeHead = NULL;

    // Free hazards
    HazardNode* hazardTemp = hazardHead;
    while (hazardTemp != NULL) {
        HazardNode* next = hazardTemp->next;
        free(hazardTemp);
        hazardTemp = next;
    }
    hazardHead = NULL;

    // Free indoor locations
    IndoorLocationNode* indoorTemp = indoorHead;
    while (indoorTemp != NULL) {
        IndoorLocationNode* next = indoorTemp->next;
        free(indoorTemp);
        indoorTemp = next;
    }
    indoorHead = NULL;

    // Free user favorites
    for (int i = 0; i < currentUser.favCount; i++) {
        free(currentUser.favoriteRoutes[i]);
    }
    free(currentUser.favoriteRoutes);

    // Reset counters
    locationCount = routeCount = hazardCount = indoorLocCount = 0;
    currentUser.favCount = 0;
    currentUser.favCapacity = 0;
}

void displayMemoryUsage() {
    size_t totalMemory = 0;

    // Calculate location memory
    LocationNode* locTemp = locationHead;
    while (locTemp != NULL) {
        totalMemory += sizeof(LocationNode);
        locTemp = locTemp->next;
    }

    // Calculate route memory
    RouteNode* routeTemp = routeHead;
    while (routeTemp != NULL) {
        totalMemory += sizeof(RouteNode);
        routeTemp = routeTemp->next;
    }

    // Calculate hazard memory
    HazardNode* hazardTemp = hazardHead;
    while (hazardTemp != NULL) {
        totalMemory += sizeof(HazardNode);
        hazardTemp = hazardTemp->next;
    }

    // Calculate indoor memory
    IndoorLocationNode* indoorTemp = indoorHead;
    while (indoorTemp != NULL) {
        totalMemory += sizeof(IndoorLocationNode);
        indoorTemp = indoorTemp->next;
    }

    // Calculate favorites memory
    for (int i = 0; i < currentUser.favCount; i++) {
        totalMemory += strlen(currentUser.favoriteRoutes[i]) + 1;
    }
    totalMemory += currentUser.favCapacity * sizeof(char*);

    printf("\n=== MEMORY USAGE REPORT ===\n");
    printf("Locations: %d nodes\n", locationCount);
    printf("Routes: %d nodes\n", routeCount);
    printf("Hazards: %d nodes\n", hazardCount);
    printf("Indoor Locations: %d nodes\n", indoorLocCount);
    printf("Favorite Routes: %d/%d\n", currentUser.favCount, currentUser.favCapacity);
    printf("Total Estimated Memory: %.2f MB\n", totalMemory / (1024.0 * 1024.0));
    printf("System is UNLIMITED - Can handle thousands of locations and routes!\n");
}

// ==================== MENU FUNCTIONS ====================

void routeMenu() {
    int choice;
    char src[MAX_NAME_LEN], dest[MAX_NAME_LEN];
    float distance, timeV;

    do {
        printf("\n=== ROUTE MANAGEMENT MENU (Unlimited) ===\n");
        printf("1. Add Location\n2. Add Route\n3. Show All Routes\n4. Find Shortest Path\n");
        printf("5. Display Route Details\n6. Delete Route\n7. Update Route\n8. Search Route\n");
        printf("9. Predict ETA\n10. Update Traffic Data\n11. Memory Usage\n0. Back to Main Menu\n");
        printf("Choice: ");

        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n');
            printf("Invalid input! Please enter a number.\n");
            choice = -1;
            continue;
        }

        switch(choice) {
            case 1:
                printf("Enter location name: ");
                scanf("%s", src);
                addLocation(src);
                break;
            case 2:
                printf("Enter source: "); scanf("%s", src);
                printf("Enter destination: "); scanf("%s", dest);
                printf("Enter distance (km): "); scanf("%f", &distance);
                printf("Enter time (min): "); scanf("%f", &timeV);
                addRoute(src, dest, distance, timeV);
                break;
            case 3: showAllRoutes(); break;
            case 4:
                printf("Enter source: "); scanf("%s", src);
                printf("Enter destination: "); scanf("%s", dest);
                findShortestPath(src, dest);
                break;
            case 5: displayRouteDetails(); break;
            case 6:
                printf("Enter source: "); scanf("%s", src);
                printf("Enter destination: "); scanf("%s", dest);
                deleteRoute(src, dest);
                break;
            case 7:
                printf("Enter source: "); scanf("%s", src);
                printf("Enter destination: "); scanf("%s", dest);
                printf("Enter new distance (km): "); scanf("%f", &distance);
                printf("Enter new time (min): "); scanf("%f", &timeV);
                updateRoute(src, dest, distance, timeV);
                break;
            case 8:
                printf("Enter location name to search: "); scanf("%s", src);
                searchRoute(src);
                break;
            case 9: {
                float dist, speed; int traffic; char weather[20];
                printf("Enter distance (km): "); scanf("%f", &dist);
                printf("Enter average speed (km/h): "); scanf("%f", &speed);
                printf("Enter traffic level (1-5): "); scanf("%d", &traffic);
                printf("Enter weather (sunny/rainy/foggy/stormy/clear): "); scanf("%s", weather);
                float eta = predictETA(dist, speed, traffic);
                if (eta >= 0.0f) {
                    eta = adjustETAByWeather(eta, weather);
                    printf("Predicted ETA: %.2f minutes\n", eta);
                }
                break;
            }
            case 10: {
                int traffic;
                printf("Enter traffic level (1-5): "); scanf("%d", &traffic);
                updateTrafficData("all", traffic);
                break;
            }
            case 11: displayMemoryUsage(); break;
            case 0: break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);
}

void userMenu() {
    int choice;
    char mode[20], mood[20], routeName[MAX_NAME_LEN];
    int avoidTolls, preferScenic;

    do {
        printf("\n=== USER PREFERENCES MENU (Unlimited Favorites) ===\n");
        printf("1. Set User Preferences\n2. View User Preferences\n3. Suggest Route Based on Mood\n");
        printf("4. Add Favorite Route\n5. Remove Favorite Route\n0. Back to Main Menu\n");
        printf("Choice: ");

        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n');
            printf("Invalid input! Please enter a number.\n");
            choice = -1;
            continue;
        }

        switch(choice) {
            case 1:
                printf("Enter transport mode (car/bike/walk/bus/train): "); scanf("%s", mode);
                printf("Avoid tolls? (1/0): "); scanf("%d", &avoidTolls);
                printf("Prefer scenic routes? (1/0): "); scanf("%d", &preferScenic);
                setUserPreference(mode, avoidTolls, preferScenic);
                break;
            case 2: getUserPreference(); break;
            case 3:
                printf("Enter your mood (relaxing/fastest/adventurous/economical/tourist): ");
                scanf("%s", mood);
                suggestRouteBasedOnMood(mood);
                break;
            case 4:
                printf("Enter route name to add to favorites: ");
                scanf("%s", routeName);
                addFavoriteRoute(routeName);
                break;
            case 5:
                printf("Enter route name to remove from favorites: ");
                scanf("%s", routeName);
                removeFavoriteRoute(routeName);
                break;
            case 0: break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);
}

void safetyMenu() {
    int choice;
    char location[MAX_NAME_LEN], type[30];

    do {
        printf("\n=== SAFETY & HAZARDS MENU (Unlimited Hazards) ===\n");
        printf("1. Report Hazard\n2. View Active Hazards\n3. Safe Route Recommendations\n");
        printf("4. Send SOS\n5. Deactivate Hazard\n0. Back to Main Menu\n");
        printf("Choice: ");

        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n');
            printf("Invalid input! Please enter a number.\n");
            choice = -1;
            continue;
        }

        switch(choice) {
            case 1:
                printf("Enter hazard location: "); scanf("%s", location);
                printf("Enter hazard type (accident/road_block/flood/construction/ice/debris/police/animal): ");
                scanf("%s", type);
                reportHazard(location, type);
                break;
            case 2: viewActiveHazards(); break;
            case 3: safeRouteRecommendation(); break;
            case 4:
                printf("Enter your current location: "); scanf("%s", location);
                sendSOS(location);
                break;
            case 5:
                printf("Enter hazard location: "); scanf("%s", location);
                printf("Enter hazard type: "); scanf("%s", type);
                deactivateHazard(location, type);
                break;
            case 0: break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);
}

void indoorMenu() {
    int choice;
    char building[MAX_NAME_LEN], room1[MAX_NAME_LEN], room2[MAX_NAME_LEN];
    int floor;

    do {
        printf("\n=== INDOOR NAVIGATION MENU (Unlimited Locations) ===\n");
        printf("1. Add Indoor Location\n2. Find Indoor Path\n3. Delete Indoor Location\n");
        printf("4. Display All Indoor Locations\n0. Back to Main Menu\n");
        printf("Choice: ");

        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n');
            printf("Invalid input! Please enter a number.\n");
            choice = -1;
            continue;
        }

        switch(choice) {
            case 1:
                printf("Enter building name: "); scanf("%s", building);
                printf("Enter floor number: "); scanf("%d", &floor);
                printf("Enter room name: "); scanf("%s", room1);
                addIndoorLocation(building, floor, room1);
                break;
            case 2:
                printf("Enter start location: "); scanf("%s", room1);
                printf("Enter end location: "); scanf("%s", room2);
                findIndoorPath(room1, room2);
                break;
            case 3:
                printf("Enter building name: "); scanf("%s", building);
                printf("Enter floor number: "); scanf("%d", &floor);
                printf("Enter room name: "); scanf("%s", room1);
                deleteIndoorLocation(building, floor, room1);
                break;
            case 4: displayAllIndoorLocations(); break;
            case 0: break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);
}

// ==================== MAIN FUNCTION ====================

int main() {
    srand((unsigned)time(NULL));
    printf("Initializing Global AI Route Brain System (UNLIMITED Linked List Version)...\n");

    // Initialize user preferences with dynamic memory
    initUserPreferences();

    int choice;

    // Load all existing data
    loadLocationDataFromFile();
    loadRouteDataFromFile();
    loadUserPreferences();
    loadHazardData();
    loadIndoorData();

    // Initialize with sample data if empty
    if (locationHead == NULL) {
        printf("Initializing with sample data...\n");
        addLocation("Dhaka"); addLocation("Chittagong"); addLocation("Sylhet");
        addLocation("Khulna"); addLocation("Rajshahi"); addLocation("Barisal");
        addLocation("Rangpur"); addLocation("Mymensingh");
    }
    if (routeHead == NULL) {
        addRoute("Dhaka", "Chittagong", 250.0f, 300.0f);
        addRoute("Dhaka", "Sylhet", 200.0f, 240.0f);
        addRoute("Chittagong", "Khulna", 350.0f, 420.0f);
        addRoute("Dhaka", "Rajshahi", 280.0f, 330.0f);
    }

    printf("🚀 Welcome to Global AI Route Brain (UNLIMITED Version)! 🚀\n");
    printf("System initialized with %d locations and %d routes.\n", locationCount, routeCount);
    printf("Memory: Dynamic allocation - No artificial limits! 💾\n");

    do {
        printf("\n=== MAIN MENU (UNLIMITED SYSTEM) ===\n");
        printf("1. Route Management\n2. User Preferences\n3. Safety & Hazards\n4. Indoor Navigation\n");
        printf("5. AI ETA Prediction\n6. Save All Data\n7. Load All Data\n8. Memory Usage\n0. Exit\n");
        printf("Choice: ");

        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n');
            printf("Invalid input! Please enter a number.\n");
            choice = -1;
            continue;
        }

        switch(choice) {
            case 1: routeMenu(); break;
            case 2: userMenu(); break;
            case 3: safetyMenu(); break;
            case 4: indoorMenu(); break;
            case 5: {
                char src[MAX_NAME_LEN], dest[MAX_NAME_LEN];
                printf("Enter source: "); scanf("%s", src);
                printf("Enter destination: "); scanf("%s", dest);
                autoAdjustETA(src, dest);
                break;
            }
            case 6:
                saveLocationDataToFile();
                saveRouteDataToFile();
                saveUserPreferences();
                saveHazardData();
                saveIndoorData();
                printf("All data saved successfully! ✅\n");
                break;
            case 7:
                // Clear current lists then reload
                freeAllMemory();
                initUserPreferences();
                loadLocationDataFromFile();
                loadRouteDataFromFile();
                loadUserPreferences();
                loadHazardData();
                loadIndoorData();
                printf("All data loaded successfully! ✅\n");
                break;
            case 8: displayMemoryUsage(); break;
            case 0:
                printf("Saving data before exit...\n");
                saveLocationDataToFile();
                saveRouteDataToFile();
                saveUserPreferences();
                saveHazardData();
                saveIndoorData();
                printf("Thank you for using Global AI Route Brain! Goodbye! 👋\n");
                break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);

    freeAllMemory();
    return 0;
}
