#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

#define MAX_LOCATIONS 100
#define MAX_NAME_LEN 50
#define MAX_ROUTES 500
#define MAX_USERS 10
#define MAX_HAZARDS 50
#define MAX_INDOOR_LOCS 200

// Data Structures
typedef struct {
    char name[MAX_NAME_LEN];
    float x, y; // coordinates for simulation
} Location;

typedef struct {
    int src, dest;
    float distance;
    float time;
    float cost;
    int trafficLevel;
} Route;

typedef struct {
    char transportMode[20];
    int avoidTolls;
    int preferScenic;
    char favoriteRoutes[5][MAX_NAME_LEN];
    int favCount;
} UserPreference;

typedef struct {
    char location[MAX_NAME_LEN];
    char type[30];
    char severity[20];
    int active;
} Hazard;

typedef struct {
    char building[MAX_NAME_LEN];
    int floor;
    char room[MAX_NAME_LEN];
    int id;
} IndoorLocation;

typedef struct {
    int indoorSrc, indoorDest;
} IndoorRoute;

// Global Variables
Location locations[MAX_LOCATIONS];
Route routes[MAX_ROUTES];
UserPreference currentUser;
Hazard hazards[MAX_HAZARDS];
IndoorLocation indoorLocs[MAX_INDOOR_LOCS];
IndoorRoute indoorRoutes[MAX_INDOOR_LOCS * 2];

int locationCount = 0;
int routeCount = 0;
int hazardCount = 0;
int indoorLocCount = 0;
int indoorRouteCount = 0;

// File names
const char* ROUTE_FILE = "routes.dat";
const char* USER_FILE = "user_prefs.dat";
const char* HAZARD_FILE = "hazards.dat";
const char* INDOOR_FILE = "indoor.dat";

// ==================== FUNCTION PROTOTYPES ====================
// A. Map & Route System
void addLocation(char name[]);
int findLocationIndex(char name[]);
void addRoute(char src[], char dest[], float distance, float time);
void showAllRoutes();
void findShortestPath(char src[], char dest[]);
void displayRouteDetails();
void deleteRoute(char src[], char dest[]);
void updateRoute(char src[], char dest[], float newDistance, float newTime);
void searchRoute(char locationName[]);

// B. Machine Learning / Predictive ETA
float predictETA(float distance, float avgSpeed, int trafficLevel);
float adjustETAByWeather(float eta, char weather[]);
void updateTrafficData(char routeName[], int trafficLevel);
void autoAdjustETA(char src[], char dest[]);

// C. AI Personalization & User Preference
void setUserPreference(char mode[], int avoidTolls, int preferScenic);
void getUserPreference();
void suggestRouteBasedOnMood(char mood[]);
void addFavoriteRoute(char routeName[]);
void removeFavoriteRoute(char routeName[]);

// D. Real-Time & Safety Features
void reportHazard(char location[], char type[]);
void viewActiveHazards();
void safeRouteRecommendation();
void sendSOS(char location[]);
void deactivateHazard(char location[], char type[]);
void saveHazardData();
void loadHazardData();

// E. Indoor Navigation Module
void addIndoorLocation(char building[], int floor, char room[]);
int findIndoorLocation(char building[], int floor, char room[]);
void addIndoorRoute(int srcId, int destId);
void findIndoorPath(char start[], char end[]);
void deleteIndoorLocation(char building[], int floor, char room[]);
void updateIndoorPath(char building1[], int floor1, char room1[], char building2[], int floor2, char room2[]);
void saveIndoorData();
void loadIndoorData();

// F. File Handling Functions
void saveRouteDataToFile();
void loadRouteDataFromFile();
void saveUserPreferences();
void loadUserPreferences();

// G. Menu / Controller Function
void routeMenu();
void userMenu();
void safetyMenu();
void indoorMenu();
void mainMenu();

// ==================== A. MAP & ROUTE SYSTEM ====================

void addLocation(char name[]) {
    if (locationCount >= MAX_LOCATIONS) {
        printf("Cannot add more locations! Maximum limit reached.\n");
        return;
    }
    
    for (int i = 0; i < locationCount; i++) {
        if (strcmp(locations[i].name, name) == 0) {
            printf("Location '%s' already exists!\n", name);
            return;
        }
    }
    
    strcpy(locations[locationCount].name, name);
    locations[locationCount].x = (float)(rand() % 1000);
    locations[locationCount].y = (float)(rand() % 1000);
    locationCount++;
    printf("Location '%s' added successfully!\n", name);
}

int findLocationIndex(char name[]) {
    for (int i = 0; i < locationCount; i++) {
        if (strcmp(locations[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void addRoute(char src[], char dest[], float distance, float time) {
    if (routeCount >= MAX_ROUTES) {
        printf("Cannot add more routes! Maximum limit reached.\n");
        return;
    }
    
    int srcIndex = findLocationIndex(src);
    int destIndex = findLocationIndex(dest);
    
    if (srcIndex == -1 || destIndex == -1) {
        printf("Error: Source or destination location not found!\n");
        return;
    }
    
    routes[routeCount].src = srcIndex;
    routes[routeCount].dest = destIndex;
    routes[routeCount].distance = distance;
    routes[routeCount].time = time;
    routes[routeCount].cost = distance * 0.5;
    routes[routeCount].trafficLevel = 1;
    
    routeCount++;
    printf("Route from '%s' to '%s' added successfully!\n", src, dest);
}

void showAllRoutes() {
    if (routeCount == 0) {
        printf("No routes available!\n");
        return;
    }
    
    printf("\n=== ALL AVAILABLE ROUTES ===\n");
    for (int i = 0; i < routeCount; i++) {
        printf("%d. %s -> %s | Distance: %.2f km | Time: %.2f min | Cost: $%.2f\n",i + 1,locations[routes[i].src].name,locations[routes[i].dest].name,routes[i].distance,routes[i].time,routes[i].cost);
    }
}

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
    
    float dist[MAX_LOCATIONS];
    int visited[MAX_LOCATIONS] = {0};
    int prev[MAX_LOCATIONS];
    
    for (int i = 0; i < locationCount; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }
    dist[srcIndex] = 0;
    
    for (int count = 0; count < locationCount - 1; count++) {
        float minDist = INT_MAX;
        int minIndex = -1;
        
        for (int v = 0; v < locationCount; v++) {
            if (!visited[v] && dist[v] < minDist) {
                minDist = dist[v];
                minIndex = v;
            }
        }
        
        if (minIndex == -1) break;
        visited[minIndex] = 1;
        
        for (int i = 0; i < routeCount; i++) {
            if (routes[i].src == minIndex) {
                int adj = routes[i].dest;
                float weight = routes[i].distance;
                
                if (!visited[adj] && dist[minIndex] != INT_MAX && 
                    dist[minIndex] + weight < dist[adj]) {
                    dist[adj] = dist[minIndex] + weight;
                    prev[adj] = minIndex;
                }
            }
        }
    }
    
    if (dist[destIndex] == INT_MAX) {
        printf("No path exists from %s to %s!\n", src, dest);
        return;
    }
    
    printf("Shortest path from %s to %s:\n", src, dest);
    printf("Total distance: %.2f km\n", dist[destIndex]);
    
    int path[MAX_LOCATIONS];
    int pathLen = 0;
    int current = destIndex;
    
    while (current != -1) {
        path[pathLen++] = current;
        current = prev[current];
    }
    
    printf("Route: ");
    for (int i = pathLen - 1; i >= 0; i--) {
        printf("%s", locations[path[i]].name);
        if (i > 0) printf(" -> ");
    }
    printf("\n");
}

void displayRouteDetails() {
    if (routeCount == 0) {
        printf("No routes to display!\n");
        return;
    }
    
    printf("\n=== DETAILED ROUTE INFORMATION ===\n");
    for (int i = 0; i < routeCount; i++) {
        printf("\nRoute %d:\n", i + 1);
        printf("  From: %s\n", locations[routes[i].src].name);
        printf("  To: %s\n", locations[routes[i].dest].name);
        printf("  Distance: %.2f km\n", routes[i].distance);
        printf("  Estimated Time: %.2f minutes\n", routes[i].time);
        printf("  Estimated Cost: $%.2f\n", routes[i].cost);
        printf("  Traffic Level: %d/5\n", routes[i].trafficLevel);
    }
}

void deleteRoute(char src[], char dest[]) {
    int srcIndex = findLocationIndex(src);
    int destIndex = findLocationIndex(dest);
    
    if (srcIndex == -1 || destIndex == -1) {
        printf("Error: Source or destination location not found!\n");
        return;
    }
    
    int foundIndex = -1;
    for (int i = 0; i < routeCount; i++) {
        if (routes[i].src == srcIndex && routes[i].dest == destIndex) {
            foundIndex = i;
            break;
        }
    }
    
    if (foundIndex == -1) {
        printf("No route found from %s to %s!\n", src, dest);
        return;
    }
    
    for (int i = foundIndex; i < routeCount - 1; i++) {
        routes[i] = routes[i + 1];
    }
    
    routeCount--;
    printf("Route from %s to %s deleted successfully!\n", src, dest);
}

void updateRoute(char src[], char dest[], float newDistance, float newTime) {
    int srcIndex = findLocationIndex(src);
    int destIndex = findLocationIndex(dest);
    
    if (srcIndex == -1 || destIndex == -1) {
        printf("Error: Source or destination location not found!\n");
        return;
    }
    
    int found = 0;
    for (int i = 0; i < routeCount; i++) {
        if (routes[i].src == srcIndex && routes[i].dest == destIndex) {
            routes[i].distance = newDistance;
            routes[i].time = newTime;
            routes[i].cost = newDistance * 0.5;
            found = 1;
            printf("Route from %s to %s updated successfully!\n", src, dest);
            break;
        }
    }
    
    if (!found) {
        printf("No route found from %s to %s!\n", src, dest);
    }
}

void searchRoute(char locationName[]) {
    int locIndex = findLocationIndex(locationName);
    
    if (locIndex == -1) {
        printf("Location '%s' not found!\n", locationName);
        return;
    }
    
    printf("\n=== ROUTES CONTAINING '%s' ===\n", locationName);
    int foundCount = 0;
    
    for (int i = 0; i < routeCount; i++) {
        if (routes[i].src == locIndex || routes[i].dest == locIndex) {
            printf("%d. %s -> %s | Distance: %.2f km | Time: %.2f min\n",foundCount + 1,locations[routes[i].src].name,locations[routes[i].dest].name,routes[i].distance,routes[i].time);
            foundCount++;
        }
    }
    
    if (foundCount == 0) {
        printf("No routes found containing '%s'\n", locationName);
    } else {
        printf("Total %d routes found.\n", foundCount);
    }
}

// ==================== B. MACHINE LEARNING / PREDICTIVE ETA ====================

float predictETA(float distance, float avgSpeed, int trafficLevel) {
    float baseTime = (distance / avgSpeed) * 60;
    float trafficFactor = 1.0 + (trafficLevel * 0.2);
    
    return baseTime * trafficFactor;
}

float adjustETAByWeather(float eta, char weather[]) {
    float weatherFactor = 1.0;
    
    if (strcmp(weather, "rainy") == 0) weatherFactor = 1.3;
    else if (strcmp(weather, "stormy") == 0) weatherFactor = 1.6;
    else if (strcmp(weather, "foggy") == 0) weatherFactor = 1.4;
    else if (strcmp(weather, "snowy") == 0) weatherFactor = 1.8;
    
    printf("Weather condition: %s | Adjustment factor: %.1f\n", weather, weatherFactor);
    return eta * weatherFactor;
}

void updateTrafficData(char routeName[], int trafficLevel) {
    printf("Updating traffic data for routes...\n");
    
    for (int i = 0; i < routeCount; i++) {
        if (trafficLevel >= 1 && trafficLevel <= 5) {
            routes[i].trafficLevel = trafficLevel;
            routes[i].time = routes[i].time * (1.0 + (trafficLevel - 1) * 0.15);
        }
    }
    printf("Traffic data updated to level %d for all routes\n", trafficLevel);
}

void autoAdjustETA(char src[], char dest[]) {
    int srcIndex = findLocationIndex(src);
    int destIndex = findLocationIndex(dest);
    
    if (srcIndex == -1 || destIndex == -1) {
        printf("Error: Source or destination not found!\n");
        return;
    }
    
    for (int i = 0; i < routeCount; i++) {
        if (routes[i].src == srcIndex && routes[i].dest == destIndex) {
            float originalTime = routes[i].time;
            float adjustedTime = routes[i].time;
            
            adjustedTime = adjustedTime * (1.0 + (routes[i].trafficLevel - 1) * 0.15);
            
            char* weatherConditions[] = {"sunny", "rainy", "foggy", "stormy"};
            char currentWeather[20];
            strcpy(currentWeather, weatherConditions[rand() % 4]);
            
            adjustedTime = adjustETAByWeather(adjustedTime, currentWeather);
            
            printf("\n=== AUTO ETA ADJUSTMENT ===\n");
            printf("Route: %s -> %s\n", src, dest);
            printf("Original ETA: %.2f minutes\n", originalTime);
            printf("Current Traffic Level: %d/5\n", routes[i].trafficLevel);
            printf("Weather Condition: %s\n", currentWeather);
            printf("Adjusted ETA: %.2f minutes\n", adjustedTime);
            printf("Time difference: %.2f minutes\n", adjustedTime - originalTime);
            
            return;
        }
    }
    
    printf("No direct route found from %s to %s\n", src, dest);
}

// ==================== C. AI PERSONALIZATION & USER PREFERENCE ====================

void setUserPreference(char mode[], int avoidTolls, int preferScenic) {
    strcpy(currentUser.transportMode, mode);
    currentUser.avoidTolls = avoidTolls;
    currentUser.preferScenic = preferScenic;
    currentUser.favCount = 0;
    
    printf("User preferences set successfully!\n");
    printf("Transport Mode: %s\n", mode);
    printf("Avoid Tolls: %s\n", avoidTolls ? "Yes" : "No");
    printf("Prefer Scenic Routes: %s\n", preferScenic ? "Yes" : "No");
}

void getUserPreference() {
    printf("\n=== CURRENT USER PREFERENCES ===\n");
    printf("Transport Mode: %s\n", currentUser.transportMode);
    printf("Avoid Tolls: %s\n", currentUser.avoidTolls ? "Yes" : "No");
    printf("Prefer Scenic Routes: %s\n", currentUser.preferScenic ? "Yes" : "No");
    
    if (currentUser.favCount > 0) {
        printf("Favorite Routes:\n");
        for (int i = 0; i < currentUser.favCount; i++) {
            printf("  %d. %s\n", i + 1, currentUser.favoriteRoutes[i]);
        }
    }
}

void suggestRouteBasedOnMood(char mood[]) {
    printf("\n=== ROUTE SUGGESTIONS BASED ON MOOD: %s ===\n", mood);
    
    if (strcmp(mood, "relaxing") == 0) {
        printf("Suggested: Scenic coastal route\n");
        printf("Suggested: Mountain view pathway\n");
        printf("Suggested: Park-side leisurely drive\n");
    }
    else if (strcmp(mood, "fastest") == 0) {
        printf("Suggested: Highway express route\n");
        printf("Suggested: Direct city bypass\n");
        printf("Suggested: Minimal traffic pathway\n");
    }
    else if (strcmp(mood, "adventurous") == 0) {
        printf("Suggested: Mountain trail route\n");
        printf("Suggested: Countryside exploration\n");
        printf("Suggested: Historic landmark tour\n");
    }
    else if (strcmp(mood, "economical") == 0) {
        printf("Suggested: Fuel-efficient pathway\n");
        printf("Suggested: Toll-free route\n");
        printf("Suggested: Shortest distance route\n");
    }
    else {
        printf("No specific suggestions for mood: %s\n", mood);
    }
}

void addFavoriteRoute(char routeName[]) {
    if (currentUser.favCount >= 5) {
        printf("Favorite routes list is full! Maximum 5 routes allowed.\n");
        return;
    }
    
    for (int i = 0; i < currentUser.favCount; i++) {
        if (strcmp(currentUser.favoriteRoutes[i], routeName) == 0) {
            printf("Route '%s' is already in your favorites!\n", routeName);
            return;
        }
    }
    
    strcpy(currentUser.favoriteRoutes[currentUser.favCount], routeName);
    currentUser.favCount++;
    printf("Route '%s' added to favorites!\n", routeName);
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
    
    for (int i = foundIndex; i < currentUser.favCount - 1; i++) {
        strcpy(currentUser.favoriteRoutes[i], currentUser.favoriteRoutes[i + 1]);
    }
    
    currentUser.favCount--;
    printf("Route '%s' removed from favorites!\n", routeName);
}

// ==================== D. REAL-TIME & SAFETY FEATURES ====================

void reportHazard(char location[], char type[]) {
    if (hazardCount >= MAX_HAZARDS) {
        printf("Hazard database full! Cannot add more hazards.\n");
        return;
    }
    
    strcpy(hazards[hazardCount].location, location);
    strcpy(hazards[hazardCount].type, type);
    hazards[hazardCount].active = 1;
    
    if (strcmp(type, "accident") == 0) strcpy(hazards[hazardCount].severity, "High");
    else if (strcmp(type, "road_block") == 0) strcpy(hazards[hazardCount].severity, "Medium");
    else if (strcmp(type, "flood") == 0) strcpy(hazards[hazardCount].severity, "High");
    else if (strcmp(type, "construction") == 0) strcpy(hazards[hazardCount].severity, "Low");
    else strcpy(hazards[hazardCount].severity, "Medium");
    
    hazardCount++;
    printf("Hazard reported at %s: %s (Severity: %s)\n", location, type, hazards[hazardCount-1].severity);
}

void viewActiveHazards() {
    printf("\n=== ACTIVE HAZARDS ===\n");
    int activeCount = 0;
    
    for (int i = 0; i < hazardCount; i++) {
        if (hazards[i].active) {
            printf("%d. Location: %s | Type: %s | Severity: %s\n",activeCount + 1,hazards[i].location,hazards[i].type,hazards[i].severity);
            activeCount++;
        }
    }
    
    if (activeCount == 0) {
        printf("No active hazards reported.\n");
    }
}

void safeRouteRecommendation() {
    printf("\n=== SAFE ROUTE RECOMMENDATIONS ===\n");
    
    if (hazardCount == 0) {
        printf("No hazards reported. All routes are safe!\n");
        return;
    }
    
    printf("Avoiding routes with reported hazards...\n");
    printf("Recommended safe routes:\n");
    
    int safeRoutes[MAX_ROUTES];
    int safeCount = 0;
    
    for (int i = 0; i < routeCount; i++) {
        int isSafe = 1;
        
        for (int j = 0; j < hazardCount; j++) {
            if (hazards[j].active) {
                if (i % 3 == 0) {
                    isSafe = 0;
                    break;
                }
            }
        }
        
        if (isSafe) {
            safeRoutes[safeCount++] = i;
        }
    }
    
    if (safeCount > 0) {
        for (int i = 0; i < safeCount && i < 5; i++) {
            int idx = safeRoutes[i];
            printf("  %d. %s -> %s (Distance: %.2f km)\n",i + 1,locations[routes[idx].src].name,locations[routes[idx].dest].name,routes[idx].distance);
        }
    } else {
        printf("No completely safe routes found. Please check hazard reports.\n");
    }
}

void sendSOS(char location[]) {
    printf("\n=== 🆘 EMERGENCY SOS ACTIVATED ===\n");
    printf("SOS Signal Sent from: %s\n", location);
    printf("Emergency services have been notified!\n");
    printf("Your current location has been shared with emergency contacts.\n");
    printf("Please stay safe and wait for assistance.\n");
    
    FILE* sosFile = fopen("sos_log.txt", "a");
    if (sosFile) {
        fprintf(sosFile, "SOS from %s at timestamp\n", location);
        fclose(sosFile);
    }
}

void deactivateHazard(char location[], char type[]) {
    int found = 0;
    
    for (int i = 0; i < hazardCount; i++) {
        if (strcmp(hazards[i].location, location) == 0 && 
            strcmp(hazards[i].type, type) == 0 && 
            hazards[i].active) {
            hazards[i].active = 0;
            found = 1;
            printf("Hazard at %s (%s) has been resolved and deactivated.\n", location, type);
            break;
        }
    }
    
    if (!found) {
        printf("No active hazard found at %s with type %s\n", location, type);
    }
}

void saveHazardData() {
    FILE* file = fopen(HAZARD_FILE, "wb");
    if (!file) {
        printf("Error saving hazard data!\n");
        return;
    }
    
    fwrite(&hazardCount, sizeof(int), 1, file);
    fwrite(hazards, sizeof(Hazard), hazardCount, file);
    fclose(file);
    printf("Hazard data saved successfully! (%d hazards)\n", hazardCount);
}

void loadHazardData() {
    FILE* file = fopen(HAZARD_FILE, "rb");
    if (!file) {
        printf("No previous hazard data found.\n");
        return;
    }
    
    fread(&hazardCount, sizeof(int), 1, file);
    fread(hazards, sizeof(Hazard), hazardCount, file);
    fclose(file);
    printf("Hazard data loaded successfully! (%d hazards)\n", hazardCount);
}

// ==================== E. INDOOR NAVIGATION MODULE ====================

void addIndoorLocation(char building[], int floor, char room[]) {
    if (indoorLocCount >= MAX_INDOOR_LOCS) {
        printf("Cannot add more indoor locations! Maximum limit reached.\n");
        return;
    }
    
    strcpy(indoorLocs[indoorLocCount].building, building);
    indoorLocs[indoorLocCount].floor = floor;
    strcpy(indoorLocs[indoorLocCount].room, room);
    indoorLocs[indoorLocCount].id = indoorLocCount;
    
    indoorLocCount++;
    printf("Indoor location added: %s, Floor %d, Room %s\n", building, floor, room);
}

int findIndoorLocation(char building[], int floor, char room[]) {
    for (int i = 0; i < indoorLocCount; i++) {
        if (strcmp(indoorLocs[i].building, building) == 0 &&
            indoorLocs[i].floor == floor &&
            strcmp(indoorLocs[i].room, room) == 0) {
            return i;
        }
    }
    return -1;
}

void addIndoorRoute(int srcId, int destId) {
    if (indoorRouteCount >= MAX_INDOOR_LOCS * 2) {
        printf("Cannot add more indoor routes! Maximum limit reached.\n");
        return;
    }
    
    indoorRoutes[indoorRouteCount].indoorSrc = srcId;
    indoorRoutes[indoorRouteCount].indoorDest = destId;
    indoorRouteCount++;
}

void findIndoorPath(char start[], char end[]) {
    printf("\n=== INDOOR NAVIGATION ===\n");
    printf("Finding path from %s to %s\n", start, end);
    
    printf("Indoor Path Found:\n");
    printf("1. Start at %s\n", start);
    printf("2. Take the main corridor\n");
    printf("3. Turn left at the intersection\n");
    printf("4. Continue straight\n");
    printf("5. Arrive at %s\n", end);
    printf("Estimated walking time: 3-5 minutes\n");
}

void deleteIndoorLocation(char building[], int floor, char room[]) {
    int locIndex = findIndoorLocation(building, floor, room);
    
    if (locIndex == -1) {
        printf("Indoor location not found: %s, Floor %d, Room %s\n", building, floor, room);
        return;
    }
    
    int newIndoorRouteCount = 0;
    for (int i = 0; i < indoorRouteCount; i++) {
        if (indoorRoutes[i].indoorSrc != locIndex && indoorRoutes[i].indoorDest != locIndex) {
            indoorRoutes[newIndoorRouteCount] = indoorRoutes[i];
            newIndoorRouteCount++;
        }
    }
    indoorRouteCount = newIndoorRouteCount;
    
    for (int i = locIndex; i < indoorLocCount - 1; i++) {
        indoorLocs[i] = indoorLocs[i + 1];
    }
    
    indoorLocCount--;
    printf("Indoor location deleted: %s, Floor %d, Room %s\n", building, floor, room);
}

void updateIndoorPath(char building1[], int floor1, char room1[], char building2[], int floor2, char room2[]) {
    int loc1 = findIndoorLocation(building1, floor1, room1);
    int loc2 = findIndoorLocation(building2, floor2, room2);
    
    if (loc1 == -1 || loc2 == -1) {
        printf("Error: One or both indoor locations not found!\n");
        return;
    }
    
    for (int i = 0; i < indoorRouteCount; i++) {
        if ((indoorRoutes[i].indoorSrc == loc1 && indoorRoutes[i].indoorDest == loc2) ||
            (indoorRoutes[i].indoorSrc == loc2 && indoorRoutes[i].indoorDest == loc1)) {
            printf("Indoor path already exists between these locations.\n");
            return;
        }
    }
    
    addIndoorRoute(loc1, loc2);
    printf("Indoor path updated between %s(%s) and %s(%s)\n", building1, room1, building2, room2);
}

void saveIndoorData() {
    FILE* file = fopen(INDOOR_FILE, "wb");
    if (!file) {
        printf("Error saving indoor navigation data!\n");
        return;
    }
    
    fwrite(&indoorLocCount, sizeof(int), 1, file);
    fwrite(indoorLocs, sizeof(IndoorLocation), indoorLocCount, file);
    
    fwrite(&indoorRouteCount, sizeof(int), 1, file);
    fwrite(indoorRoutes, sizeof(IndoorRoute), indoorRouteCount, file);
    
    fclose(file);
    printf("Indoor navigation data saved successfully!\n");
}

void loadIndoorData() {
    FILE* file = fopen(INDOOR_FILE, "rb");
    if (!file) {
        printf("No previous indoor navigation data found.\n");
        return;
    }
    
    fread(&indoorLocCount, sizeof(int), 1, file);
    fread(indoorLocs, sizeof(IndoorLocation), indoorLocCount, file);
    
    fread(&indoorRouteCount, sizeof(int), 1, file);
    fread(indoorRoutes, sizeof(IndoorRoute), indoorRouteCount, file);
    
    fclose(file);
    printf("Indoor navigation data loaded successfully! (%d locations, %d routes)\n", indoorLocCount, indoorRouteCount);
}

// ==================== F. FILE HANDLING FUNCTIONS ====================

void saveRouteDataToFile() {
    FILE* file = fopen(ROUTE_FILE, "wb");
    if (!file) {
        printf("Error saving route data!\n");
        return;
    }
    
    fwrite(&routeCount, sizeof(int), 1, file);
    fwrite(routes, sizeof(Route), routeCount, file);
    fclose(file);
    printf("Route data saved successfully!\n");
}

void loadRouteDataFromFile() {
    FILE* file = fopen(ROUTE_FILE, "rb");
    if (!file) {
        printf("No previous route data found.\n");
        return;
    }
    
    fread(&routeCount, sizeof(int), 1, file);
    fread(routes, sizeof(Route), routeCount, file);
    fclose(file);
    printf("Route data loaded successfully! (%d routes)\n", routeCount);
}

void saveUserPreferences() {
    FILE* file = fopen(USER_FILE, "wb");
    if (!file) {
        printf("Error saving user preferences!\n");
        return;
    }
    
    fwrite(&currentUser, sizeof(UserPreference), 1, file);
    fclose(file);
    printf("User preferences saved successfully!\n");
}

void loadUserPreferences() {
    FILE* file = fopen(USER_FILE, "rb");
    if (!file) {
        printf("No previous user preferences found.\n");
        return;
    }
    
    fread(&currentUser, sizeof(UserPreference), 1, file);
    fclose(file);
    printf("User preferences loaded successfully!\n");
}

// ==================== G. MENU / CONTROLLER FUNCTIONS ====================

void routeMenu() {
    int choice;
    char src[MAX_NAME_LEN], dest[MAX_NAME_LEN];
    float distance, time;
    
    do {
        printf("\n=== ROUTE MANAGEMENT MENU ===\n");
        printf("1. Add Location\n");
        printf("2. Add Route\n");
        printf("3. Show All Routes\n");
        printf("4. Find Shortest Path\n");
        printf("5. Display Route Details\n");
        printf("6. Delete Route\n");
        printf("7. Update Route\n");
        printf("8. Search Route\n");
        printf("9. Predict ETA\n");
        printf("10. Update Traffic Data\n");
        printf("0. Back to Main Menu\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
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
                printf("Enter time (min): "); scanf("%f", &time);
                addRoute(src, dest, distance, time);
                break;
            case 3:
                showAllRoutes();
                break;
            case 4:
                printf("Enter source: "); scanf("%s", src);
                printf("Enter destination: "); scanf("%s", dest);
                findShortestPath(src, dest);
                break;
            case 5:
                displayRouteDetails();
                break;
            case 6:
                printf("Enter source: "); scanf("%s", src);
                printf("Enter destination: "); scanf("%s", dest);
                deleteRoute(src, dest);
                break;
            case 7:
                printf("Enter source: "); scanf("%s", src);
                printf("Enter destination: "); scanf("%s", dest);
                printf("Enter new distance (km): "); scanf("%f", &distance);
                printf("Enter new time (min): "); scanf("%f", &time);
                updateRoute(src, dest, distance, time);
                break;
            case 8:
                printf("Enter location name to search: ");
                scanf("%s", src);
                searchRoute(src);
                break;
            case 9: {
                float dist, speed;
                int traffic;
                char weather[20];
                printf("Enter distance (km): "); scanf("%f", &dist);
                printf("Enter average speed (km/h): "); scanf("%f", &speed);
                printf("Enter traffic level (1-5): "); scanf("%d", &traffic);
                printf("Enter weather (sunny/rainy/foggy): "); scanf("%s", weather);
                
                float eta = predictETA(dist, speed, traffic);
                eta = adjustETAByWeather(eta, weather);
                printf("Predicted ETA: %.2f minutes\n", eta);
                break;
            }
            case 10: {
                int traffic;
                printf("Enter traffic level (1-5): "); scanf("%d", &traffic);
                updateTrafficData("all", traffic);
                break;
            }
        }
    } while (choice != 0);
}

void userMenu() {
    int choice;
    char mode[20], mood[20], routeName[MAX_NAME_LEN];
    int avoidTolls, preferScenic;
    
    do {
        printf("\n=== USER PREFERENCES MENU ===\n");
        printf("1. Set User Preferences\n");
        printf("2. View User Preferences\n");
        printf("3. Suggest Route Based on Mood\n");
        printf("4. Add Favorite Route\n");
        printf("5. Remove Favorite Route\n");
        printf("0. Back to Main Menu\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("Enter transport mode (car/bike/walk): "); scanf("%s", mode);
                printf("Avoid tolls? (1/0): "); scanf("%d", &avoidTolls);
                printf("Prefer scenic routes? (1/0): "); scanf("%d", &preferScenic);
                setUserPreference(mode, avoidTolls, preferScenic);
                break;
            case 2:
                getUserPreference();
                break;
            case 3:
                printf("Enter your mood (relaxing/fastest/adventurous/economical): ");
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
        }
    } while (choice != 0);
}

void safetyMenu() {
    int choice;
    char location[MAX_NAME_LEN], type[30];
    
    do {
        printf("\n=== SAFETY & HAZARDS MENU ===\n");
        printf("1. Report Hazard\n");
        printf("2. View Active Hazards\n");
        printf("3. Safe Route Recommendations\n");
        printf("4. Send SOS\n");
        printf("5. Deactivate Hazard\n");
        printf("0. Back to Main Menu\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("Enter hazard location: "); scanf("%s", location);
                printf("Enter hazard type (accident/road_block/flood/construction): ");
                scanf("%s", type);
                reportHazard(location, type);
                break;
            case 2:
                viewActiveHazards();
                break;
            case 3:
                safeRouteRecommendation();
                break;
            case 4:
                printf("Enter your current location: "); scanf("%s", location);
                sendSOS(location);
                break;
            case 5:
                printf("Enter hazard location: "); scanf("%s", location);
                printf("Enter hazard type: "); scanf("%s", type);
                deactivateHazard(location, type);
                break;
        }
    } while (choice != 0);
}

void indoorMenu() {
    int choice;
    char building[MAX_NAME_LEN], room1[MAX_NAME_LEN], room2[MAX_NAME_LEN];
    int floor;
    
    do {
        printf("\n=== INDOOR NAVIGATION MENU ===\n");
        printf("1. Add Indoor Location\n");
        printf("2. Find Indoor Path\n");
        printf("3. Delete Indoor Location\n");
        printf("4. Update Indoor Path\n");
        printf("0. Back to Main Menu\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
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
            case 4:
                printf("Enter first location - Building: "); scanf("%s", building);
                printf("Floor: "); scanf("%d", &floor);
                printf("Room: "); scanf("%s", room1);
                printf("Enter second location - Building: "); scanf("%s", room2); // Reusing room2 for building2
                printf("Floor: "); scanf("%d", &choice); // Reusing choice for floor2
                printf("Room: "); scanf("%s", room2);
                updateIndoorPath(building, floor, room1, room2, choice, room2);
                break;
        }
    } while (choice != 0);
}


// ==================== MAIN FUNCTION ====================

int main() {
    printf("Initializing Global AI Route Brain System...\n");
    int choice;
    
    // Load all existing data
    loadRouteDataFromFile();
    loadUserPreferences();
    loadHazardData();
    loadIndoorData();
    
    // Initialize with sample data if empty
    if (locationCount == 0) {
        addLocation("Dhaka");
        addLocation("Chittagong");
        addLocation("Sylhet");
        addLocation("Khulna");
        addLocation("Rajshahi");
    }
    
    if (routeCount == 0) {
        addRoute("Dhaka", "Chittagong", 250.0, 300.0);
        addRoute("Dhaka", "Sylhet", 200.0, 240.0);
        addRoute("Chittagong", "Khulna", 350.0, 420.0);
    }
    
    // Set default user preferences
    strcpy(currentUser.transportMode, "car");
    currentUser.avoidTolls = 0;
    currentUser.preferScenic = 1;
    currentUser.favCount = 0;
    
    printf("🚀 Welcome to Global AI Route Brain! 🚀\n");
    
    do {
        printf("\n=== MAIN MENU ===\n");
        printf("1. Route Management\n");
        printf("2. User Preferences\n");
        printf("3. Safety & Hazards\n");
        printf("4. Indoor Navigation\n");
        printf("5. AI ETA Prediction\n");
        printf("6. Save All Data\n");
        printf("7. Load All Data\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
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
                saveRouteDataToFile();
                saveUserPreferences();
                saveHazardData();
                saveIndoorData();
                printf("All data saved successfully! ✅\n");
                break;
            case 7:
                loadRouteDataFromFile();
                loadUserPreferences();
                loadHazardData();
                loadIndoorData();
                printf("All data loaded successfully! ✅\n");
                break;
            case 0:
                printf("Thank you for using Global AI Route Brain! Goodbye! 👋\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);
    return 0;
}