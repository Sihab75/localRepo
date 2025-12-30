#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <climits>
#include <cfloat>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;

struct LocationNode {
    string name;
    float x, y;
    int id;
    LocationNode* next;

    LocationNode(string n, float xx, float yy, int i)
        : name(n), x(xx), y(yy), id(i), next(nullptr) {}
};

struct RouteNode {
    int src, dest;
    float distance;
    float time;
    float cost;
    int trafficLevel;
    RouteNode* next;

    RouteNode(int s, int d, float dis, float t, float c, int traffic)
        : src(s), dest(d), distance(dis), time(t), cost(c), trafficLevel(traffic), next(nullptr) {}
};

struct HazardNode {
    string location;
    string type;
    string severity;
    bool active;
    time_t reportedTime;
    HazardNode* next;

    HazardNode(string loc, string ty, string sev, bool act)
        : location(loc), type(ty), severity(sev), active(act), reportedTime(time(nullptr)), next(nullptr) {}
};

struct IndoorNode {
    string building;
    int floor;
    string room;
    int id;
    IndoorNode* next;

    IndoorNode(string bld, int flr, string rm, int i)
        : building(bld), floor(flr), room(rm), id(i), next(nullptr) {}
};

// ==================== LOCATION MANAGER ====================

class LocationManager {
private:
    LocationNode* head;
    int locationCount;

public:
    LocationManager() : head(nullptr), locationCount(0) {}

    void addLocation(const string& name) {
        if (name.empty() || name.length() > 99) {
            cout << "Error: Location name must be 1-99 characters!\n";
            return;
        }

        // Check for duplicates
        LocationNode* temp = head;
        while (temp != nullptr) {
            if (temp->name == name) {
                cout << "Location '" << name << "' already exists!\n";
                return;
            }
            temp = temp->next;
        }

        // Generate random coordinates
        float x = static_cast<float>(rand() % 1000);
        float y = static_cast<float>(rand() % 1000);

        LocationNode* newNode = new LocationNode(name, x, y, locationCount);

        if (head == nullptr) {
            head = newNode;
        } else {
            LocationNode* temp = head;
            while (temp->next != nullptr) temp = temp->next;
            temp->next = newNode;
        }

        locationCount++;
        cout << "Location '" << name << "' added! (Total: " << locationCount << ")\n";
    }

    int findLocationIndex(const string& name) const {
        LocationNode* temp = head;
        int index = 0;
        while (temp != nullptr) {
            if (temp->name == name) return index;
            temp = temp->next;
            index++;
        }
        return -1;
    }

    LocationNode* getLocationByIndex(int index) const {
        if (index < 0 || index >= locationCount) return nullptr;

        LocationNode* temp = head;
        int current = 0;
        while (temp != nullptr && current < index) {
            temp = temp->next;
            current++;
        }
        return temp;
    }

    LocationNode* getLocationByName(const string& name) const {
        LocationNode* temp = head;
        while (temp != nullptr) {
            if (temp->name == name) return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    void displayAllLocations() const {
        if (head == nullptr) {
            cout << "No locations available!\n";
            return;
        }

        cout << "\n=== ALL LOCATIONS (" << locationCount << ") ===\n";
        LocationNode* temp = head;
        int i = 0;
        while (temp != nullptr) {
            cout << i << ". " << temp->name << " (ID: " << temp->id << ", Coordinates: " << fixed << setprecision(2) << temp->x << ", " << temp->y << ")\n";
            temp = temp->next;
            i++;
        }
    }

    int getLocationCount() const { return locationCount; }

    void saveToFile(const string& filename) const {
        ofstream file(filename, ios::binary);
        if (!file) {
            cerr << "Error saving location data!\n";
            return;
        }

        file.write((char*)&locationCount, sizeof(int));
        LocationNode* temp = head;
        while (temp != nullptr) {
            int nameLen = temp->name.length() + 1;
            file.write((char*)&nameLen, sizeof(int));
            file.write(temp->name.c_str(), nameLen);
            file.write((char*)&temp->x, sizeof(float));
            file.write((char*)&temp->y, sizeof(float));
            file.write((char*)&temp->id, sizeof(int));
            temp = temp->next;
        }

        cout << "Location data saved to '" << filename << "' (" << locationCount << " locations)\n";
    }

    bool loadFromFile(const string& filename) {
        ifstream file(filename, ios::binary);
        if (!file) {
            cout << "No previous location data found.\n";
            return false;
        }

        clear();

        int count;
        file.read((char*)&count, sizeof(int));

        for (int i = 0; i < count; i++) {
            int nameLen;
            file.read((char*)&nameLen, sizeof(int));

            string name(nameLen, '\0');
            file.read(&name[0], nameLen);
            name.pop_back(); // Remove null terminator

            float x, y;
            int id;
            file.read((char*)&x, sizeof(float));
            file.read((char*)&y, sizeof(float));
            file.read((char*)&id, sizeof(int));

            LocationNode* newNode = new LocationNode(name, x, y, id);
            if (!head) head = newNode;
            else {
                LocationNode* temp = head;
                while (temp->next) temp = temp->next;
                temp->next = newNode;
            }
            locationCount++;
        }

        cout << "Location data loaded from '" << filename << "' (" << locationCount << " locations)\n";
        return true;
    }

private:
    void clear() {
        LocationNode* current = head;
        while (current != nullptr) {
            LocationNode* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        locationCount = 0;
    }
};

class RouteManager {
private:
    RouteNode* head;
    int routeCount;
    const LocationManager& locationManager;

public:
    RouteManager(const LocationManager& locMgr) : head(nullptr), routeCount(0), locationManager(locMgr) {}

    void addRoute(const string& src, const string& dest, float distance, float timeVal) {
        if (distance <= 0 || timeVal <= 0) {
            cout << "Error: Distance and time must be positive!\n";
            return;
        }

        int srcIdx = locationManager.findLocationIndex(src);
        int destIdx = locationManager.findLocationIndex(dest);

        if (srcIdx == -1 || destIdx == -1) {
            cout << "Error: Source or destination not found!\n";
            return;
        }

        if (srcIdx == destIdx) {
            cout << "Error: Source and destination cannot be the same!\n";
            return;
        }

        RouteNode* temp = head;
        while (temp != nullptr) {
            if (temp->src == srcIdx && temp->dest == destIdx) {
                cout << "Route already exists!\n";
                return;
            }
            temp = temp->next;
        }

        float cost = distance * 0.5f;
        RouteNode* newNode = new RouteNode(srcIdx, destIdx, distance, timeVal, cost, 1);

        if (head == nullptr) {
            head = newNode;
        } else {
            RouteNode* temp = head;
            while (temp->next != nullptr) temp = temp->next;
            temp->next = newNode;
        }

        routeCount++;
        cout << "Route added: " << src << " -> " << dest << " (Total routes: " << routeCount << ")\n";
    }

    void displayAllRoutes() const {
        if (head == nullptr) {
            cout << "No routes available!\n";
            return;
        }

        cout << "\n=== ALL ROUTES (" << routeCount << ") ===\n";
        RouteNode* temp = head;
        int i = 1;
        while (temp != nullptr) {
            LocationNode* srcLoc = locationManager.getLocationByIndex(temp->src);
            LocationNode* destLoc = locationManager.getLocationByIndex(temp->dest);

            if (srcLoc && destLoc) {
                cout << i << ". " << srcLoc->name << " -> " << destLoc->name << " | Dist: " << fixed << setprecision(2) << temp->distance << " km" << " | Time: " << temp->time << " min" << " | Cost: " << temp->cost << " taka | Traffic: " << temp->trafficLevel << "/5\n";
            }
            temp = temp->next;
            i++;
        }
    }

    void findShortestPath(const string& src, const string& dest) const {
        int srcIdx = locationManager.findLocationIndex(src);
        int destIdx = locationManager.findLocationIndex(dest);

        if (srcIdx == -1 || destIdx == -1) {
            cout << "Error: Locations not found!\n";
            return;
        }

        int n = locationManager.getLocationCount();
        if (n == 0) {
            cout << "No locations available.\n";
            return;
        }

        vector<float> dist(n, FLT_MAX);
        vector<bool> visited(n, false);
        vector<int> prev(n, -1);
        dist[srcIdx] = 0;

        for (int count = 0; count < n - 1; count++) {
            float minDist = FLT_MAX;
            int minIdx = -1;

            for (int v = 0; v < n; v++) {
                if (!visited[v] && dist[v] < minDist) {
                    minDist = dist[v];
                    minIdx = v;
                }
            }

            if (minIdx == -1) break;
            visited[minIdx] = true;

            RouteNode* temp = head;
            while (temp != nullptr) {
                if (temp->src == minIdx) {
                    int adj = temp->dest;
                    if (!visited[adj] && dist[minIdx] != FLT_MAX &&
                        dist[minIdx] + temp->distance < dist[adj]) {
                        dist[adj] = dist[minIdx] + temp->distance;
                        prev[adj] = minIdx;
                    }
                }
                temp = temp->next;
            }
        }

        if (dist[destIdx] == FLT_MAX) {
            cout << "No path exists from " << src << " to " << dest << "!\n";
            return;
        }

        cout << "\n=== SHORTEST PATH ===\n";
        cout << "From: " << src << "\nTo: " << dest << "\n";
        cout << "Total Distance: " << dist[destIdx] << " km\n";

        vector<int> path;
        for (int at = destIdx; at != -1; at = prev[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());

        cout << "Route: ";
        for (size_t i = 0; i < path.size(); i++) {
            LocationNode* loc = locationManager.getLocationByIndex(path[i]);
            cout << loc->name;
            if (i < path.size() - 1) cout << " -> ";
        }
        cout << "\n";
    }

    void updateRoute(const string& src, const string& dest, float newDist, float newTime) {
        int srcIdx = locationManager.findLocationIndex(src);
        int destIdx = locationManager.findLocationIndex(dest);

        if (srcIdx == -1 || destIdx == -1) {
            cout << "Error: Route not found!\n";
            return;
        }

        RouteNode* temp = head;
        bool found = false;
        while (temp != nullptr) {
            if (temp->src == srcIdx && temp->dest == destIdx) {
                temp->distance = newDist;
                temp->time = newTime;
                temp->cost = newDist * 0.5f;
                found = true;
                cout << "Route updated successfully!\n";
                break;
            }
            temp = temp->next;
        }

        if (!found) cout << "Route not found!\n";
    }

    void deleteRoute(const string& src, const string& dest) {
        int srcIdx = locationManager.findLocationIndex(src);
        int destIdx = locationManager.findLocationIndex(dest);

        if (srcIdx == -1 || destIdx == -1) {
            cout << "Error: Route not found!\n";
            return;
        }

        RouteNode* current = head;
        RouteNode* prev = nullptr;
        bool found = false;

        while (current != nullptr) {
            if (current->src == srcIdx && current->dest == destIdx) {
                found = true;
                if (prev == nullptr) {
                    head = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                routeCount--;
                cout << "Route deleted! (Remaining: " << routeCount << ")\n";
                break;
            }
            prev = current;
            current = current->next;
        }

        if (!found) cout << "Route not found!\n";
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename, ios::binary);
        if (!file) {
            cerr << "Error saving route data!\n";
            return;
        }

        file.write((char*)&routeCount, sizeof(int));

        RouteNode* temp = head;
        while (temp != nullptr) {
            file.write((char*)&temp->src, sizeof(int));
            file.write((char*)&temp->dest, sizeof(int));
            file.write((char*)&temp->distance, sizeof(float));
            file.write((char*)&temp->time, sizeof(float));
            file.write((char*)&temp->cost, sizeof(float));
            file.write((char*)&temp->trafficLevel, sizeof(int));
            temp = temp->next;
        }

        cout << "Route data saved to '" << filename << "' (" << routeCount << " routes)\n";
    }

    bool loadFromFile(const string& filename) {
        ifstream file(filename, ios::binary);
        if (!file) {
            cout << "No previous route data found.\n";
            return false;
        }

        clear();

        int count;
        file.read((char*)&count, sizeof(int));

        for (int i = 0; i < count; i++) {
            int src, dest, traffic;
            float dist, timeVal, cost;

            file.read((char*)&src, sizeof(int));
            file.read((char*)&dest, sizeof(int));
            file.read((char*)&dist, sizeof(float));
            file.read((char*)&timeVal, sizeof(float));
            file.read((char*)&cost, sizeof(float));
            file.read((char*)&traffic, sizeof(int));

            addRouteFromData(src, dest, dist, timeVal, cost, traffic);
        }

        cout << "Route data loaded from '" << filename << "' (" << routeCount << " routes)\n";
        return true;
    }

private:
    void addRouteFromData(int src, int dest, float distance, float timeVal, float cost, int traffic) {
        RouteNode* newNode = new RouteNode(src, dest, distance, timeVal, cost, traffic);

        if (head == nullptr) {
            head = newNode;
        } else {
            RouteNode* temp = head;
            while (temp->next != nullptr) temp = temp->next;
            temp->next = newNode;
        }
        routeCount++;
    }

    void clear() {
        RouteNode* current = head;
        while (current != nullptr) {
            RouteNode* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        routeCount = 0;
    }
};

class AIAssistant {
private:
    string transportMode;
    bool avoidTolls;
    bool preferScenic;
    vector<string> favoriteRoutes;

public:
    AIAssistant() : transportMode("car"), avoidTolls(false), preferScenic(true) {}

    void setPreferences(const string& mode, bool noTolls, bool scenic) {
        if (mode != "car" && mode != "bike" && mode != "walk" && mode != "bus" && mode != "train") {
            cout << "Error: Invalid transport mode!\n";
            return;
        }

        transportMode = mode;
        avoidTolls = noTolls;
        preferScenic = scenic;

        cout << "\nPreferences updated:\n";
        cout << "Mode: " << transportMode << "\n";
        cout << "Avoid Tolls: " << (avoidTolls ? "Yes" : "No") << "\n";
        cout << "Prefer Scenic: " << (preferScenic ? "Yes" : "No") << "\n";
    }

    void displayPreferences() const {
        cout << "\n=== CURRENT PREFERENCES ===\n";
        cout << "Transport Mode: " << transportMode << "\n";
        cout << "Avoid Tolls: " << (avoidTolls ? "Yes" : "No") << "\n";
        cout << "Prefer Scenic Routes: " << (preferScenic ? "Yes" : "No") << "\n";

        if (!favoriteRoutes.empty()) {
            cout << "\nFavorite Routes (" << favoriteRoutes.size() << "):\n";
            for (size_t i = 0; i < favoriteRoutes.size(); i++) {
                cout << "  " << i + 1 << ". " << favoriteRoutes[i] << "\n";
            }
        }
    }

    float predictETA(float distance, float avgSpeed, int traffic) const {
        if (distance <= 0 || avgSpeed <= 0) {
            cout << "Error: Invalid input for ETA prediction!\n";
            return -1;
        }

        float baseTime = (distance / avgSpeed) * 60.0f;
        float trafficFactor = 1.0f + (traffic - 1) * 0.2f;
        return baseTime * trafficFactor;
    }

    float adjustETAForWeather(float eta, const string& weather) const {
        float factor = 1.0f;

        if (weather == "sunny") factor = 1.0f;
        else if (weather == "rainy") factor = 1.3f;
        else if (weather == "stormy") factor = 1.6f;
        else if (weather == "foggy") factor = 1.4f;
        else if (weather == "snowy") factor = 1.8f;
        else if (weather == "clear") factor = 0.9f;
        else {
            cout << "Unknown weather, using default factor.\n";
            factor = 1.1f;
        }

        return eta * factor;
    }

    void addFavorite(const string& routeName) {
        if (find(favoriteRoutes.begin(), favoriteRoutes.end(), routeName) != favoriteRoutes.end()) {
            cout << "Route already in favorites!\n";
            return;
        }
        favoriteRoutes.push_back(routeName);
        cout << "Added to favorites!\n";
    }

    void suggestByMood(const string& mood) const {
        cout << "\n=== SUGGESTIONS FOR " << mood << " MOOD ===\n";

        if (mood == "relaxing") {
            cout << "• Scenic coastal route\n• Park boulevard\n• Riverside drive\n";
        } else if (mood == "fastest") {
            cout << "• Highway express\n• City bypass\n• Express toll route\n";
        } else if (mood == "adventurous") {
            cout << "• Mountain trail\n• Forest pathway\n• Countryside exploration\n";
        } else if (mood == "economical") {
            cout << "• Fuel-efficient path\n• Toll-free route\n• Public transport\n";
        } else {
            cout << "Try: relaxing, fastest, adventurous, economical\n";
        }
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file) {
            cerr << "Error saving preferences!\n";
            return;
        }

        file << transportMode << "\n";
        file << avoidTolls << " " << preferScenic << "\n";
        file << favoriteRoutes.size() << "\n";
        for (const auto& route : favoriteRoutes) {
            file << route << "\n";
        }

        cout << "Preferences saved!\n";
    }

    bool loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cout << "No saved preferences found.\n";
            return false;
        }

        file >> transportMode;
        file >> avoidTolls >> preferScenic;

        int favCount;
        file >> favCount;
        file.ignore(); // Skip newline

        favoriteRoutes.clear();
        for (int i = 0; i < favCount; i++) {
            string route;
            getline(file, route);
            favoriteRoutes.push_back(route);
        }

        cout << "Preferences loaded!\n";
        return true;
    }
};

class SafetySystem {
private:
    HazardNode* head;
    int hazardCount;

public:
    SafetySystem() : head(nullptr), hazardCount(0) {}

    void reportHazard(const string& location, const string& type) {
        vector<string> validTypes = {"accident", "road_block", "flood", "construction", "ice", "debris", "police", "animal"};

        if (find(validTypes.begin(), validTypes.end(), type) == validTypes.end()) {
            cout << "Error: Invalid hazard type!\n";
            cout << "Valid types: accident, road_block, flood, construction, ice, debris, police, animal\n";
            return;
        }

        string severity = "Medium";
        if (type == "accident" || type == "flood") severity = "High";
        else if (type == "police" || type == "construction") severity = "Low";

        HazardNode* newNode = new HazardNode(location, type, severity, true);

        if (head == nullptr) {
            head = newNode;
        } else {
            HazardNode* temp = head;
            while (temp->next != nullptr) temp = temp->next;
            temp->next = newNode;
        }

        hazardCount++;
        cout << "Hazard reported at " << location << " (" << type << ")\n";
    }

    void displayActiveHazards() const {
        if (head == nullptr) {
            cout << "No active hazards.\n";
            return;
        }

        cout << "\n=== ACTIVE HAZARDS ===\n";
        HazardNode* temp = head;
        int activeCount = 0;

        while (temp != nullptr) {
            if (temp->active) {
                activeCount++;
                cout << activeCount << ". " << temp->location << " - " << temp->type << " (" << temp->severity << ") - " << ctime(&temp->reportedTime);
            }
            temp = temp->next;
        }

        if (activeCount == 0) cout << "No active hazards.\n";
    }

    void sendSOS(const string& location) const {
        cout << "\n=== EMERGENCY SOS ===\n";
        cout << "Location: " << location << "\n";
        cout << "Emergency services notified!\n";

        ofstream logFile("sos_log.txt", ios::app);
        if (logFile) {
            time_t now = time(nullptr);
            logFile << "SOS from " << location << " at " << ctime(&now);
            logFile.close();
        }
    }

    void resolveHazard(const string& location, const string& type) {
        HazardNode* temp = head;
        bool found = false;

        while (temp != nullptr) {
            if (temp->location == location && temp->type == type && temp->active) {
                temp->active = false;
                found = true;
                cout << "Hazard resolved: " << location << " - " << type << "\n";
                break;
            }
            temp = temp->next;
        }

        if (!found) cout << "Hazard not found or already resolved.\n";
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename, ios::binary);
        if (!file) {
            cerr << "Error saving hazard data!\n";
            return;
        }

        file.write((char*)&hazardCount, sizeof(int));

        HazardNode* temp = head;
        while (temp != nullptr) {
            int locLen = temp->location.length() + 1;
            int typeLen = temp->type.length() + 1;
            int sevLen = temp->severity.length() + 1;

            file.write((char*)&locLen, sizeof(int));
            file.write(temp->location.c_str(), locLen);

            file.write((char*)&typeLen, sizeof(int));
            file.write(temp->type.c_str(), typeLen);

            file.write((char*)&sevLen, sizeof(int));
            file.write(temp->severity.c_str(), sevLen);

            file.write((char*)&temp->active, sizeof(bool));
            file.write((char*)&temp->reportedTime, sizeof(time_t));

            temp = temp->next;
        }

        cout << "Hazard data saved!\n";
    }

    bool loadFromFile(const string& filename) {
        ifstream file(filename, ios::binary);
        if (!file) {
            cout << "No previous hazard data found.\n";
            return false;
        }

        clear();

        int count;
        file.read((char*)&count, sizeof(int));

        for (int i = 0; i < count; i++) {
            int locLen, typeLen, sevLen;
            file.read((char*)&locLen, sizeof(int));
            string location(locLen, '\0');
            file.read(&location[0], locLen);
            location.pop_back();

            file.read((char*)&typeLen, sizeof(int));
            string type(typeLen, '\0');
            file.read(&type[0], typeLen);
            type.pop_back();

            file.read((char*)&sevLen, sizeof(int));
            string severity(sevLen, '\0');
            file.read(&severity[0], sevLen);
            severity.pop_back();

            bool active;
            time_t reportedTime;
            file.read((char*)&active, sizeof(bool));
            file.read((char*)&reportedTime, sizeof(time_t));

            HazardNode* newNode = new HazardNode(location, type, severity, active);
            newNode->reportedTime = reportedTime;

            if (!head) head = newNode;
            else {
                HazardNode* temp = head;
                while (temp->next) temp = temp->next;
                temp->next = newNode;
            }
            hazardCount++;
        }

        cout << "Hazard data loaded (" << hazardCount << " hazards)\n";
        return true;
    }

private:
    void clear() {
        HazardNode* current = head;
        while (current != nullptr) {
            HazardNode* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        hazardCount = 0;
    }
};

class IndoorNavigation {
private:
    IndoorNode* head;
    int indoorCount;

public:
    IndoorNavigation() : head(nullptr), indoorCount(0) {}

    void addLocation(const string& building, int floor, const string& room) {
        if (building.empty() || room.empty()) {
            cout << "Error: Building and room names required!\n";
            return;
        }

        if (floor < -10 || floor > 200) {
            cout << "Error: Invalid floor number!\n";
            return;
        }

        IndoorNode* temp = head;
        while (temp != nullptr) {
            if (temp->building == building && temp->floor == floor && temp->room == room) {
                cout << "Location already exists!\n";
                return;
            }
            temp = temp->next;
        }

        IndoorNode* newNode = new IndoorNode(building, floor, room, indoorCount);

        if (head == nullptr) {
            head = newNode;
        } else {
            IndoorNode* temp = head;
            while (temp->next != nullptr) temp = temp->next;
            temp->next = newNode;
        }

        indoorCount++;
        cout << "Indoor location added: " << building << ", Floor " << floor << ", Room " << room << "\n";
    }

    void findPath(const string& start, const string& end) const {
        cout << "\n=== INDOOR NAVIGATION ===\n";
        cout << "From: " << start << "\nTo: " << end << "\n";
        cout << "\nPath:\n";
        cout << "1. Start at " << start << "\n";
        cout << "2. Follow main corridor\n";
        cout << "3. Take elevator to required floor\n";
        cout << "4. Turn left at intersection\n";
        cout << "5. Continue to " << end << "\n";
        cout << "\nEstimated time: 5 minutes\n";
    }

    void displayAllLocations() const {
        if (head == nullptr) {
            cout << "No indoor locations.\n";
            return;
        }

        cout << "\n=== INDOOR LOCATIONS ===\n";
        IndoorNode* temp = head;
        int i = 1;
        while (temp != nullptr) {
            cout << i << ". " << temp->building << " - Floor " << temp->floor << " - Room " << temp->room << "\n";
            temp = temp->next;
            i++;
        }
    }

private:
    void clear() {
        IndoorNode* current = head;
        while (current != nullptr) {
            IndoorNode* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        indoorCount = 0;
    }
};

class mainMap {
private:
    LocationManager locationMgr;
    RouteManager routeMgr;
    AIAssistant aiAssistant;
    SafetySystem safetySys;
    IndoorNavigation indoorNav;

    void showMainMenu() {
        cout << "\n========================================\n";
        cout << "     Route Map System\n";
        cout << "========================================\n";
        cout << "1. Location Management\n";
        cout << "2. Route Management\n";
        cout << "3. AI & User Preferences\n";
        cout << "4. Safety & Hazards\n";
        cout << "5. Indoor Navigation\n";
        cout << "6. Save All Data\n";
        cout << "7. Load All Data\n";
        cout << "0. Exit\n";
        cout << "========================================\n";
        cout << "Choice: ";
    }

    void locationMenu() {
        int choice;
        do {
            cout << "\n=== LOCATION MANAGEMENT ===\n";
            cout << "1. Add Location\n";
            cout << "2. View All Locations\n";
            cout << "0. Back\n";
            cout << "Choice: ";
            cin >> choice;

            if (choice == 1) {
                string name;
                cout << "Enter location name: ";
                cin >> name;
                locationMgr.addLocation(name);
            } else if (choice == 2) {
                locationMgr.displayAllLocations();
            }
        } while (choice != 0);
    }

    void routeMenu() {
        int choice;
        string src, dest;
        float dist, timeVal;

        do {
            cout << "\n=== ROUTE MANAGEMENT ===\n";
            cout << "1. Add Route\n";
            cout << "2. View All Routes\n";
            cout << "3. Find Shortest Path\n";
            cout << "4. Update Route\n";
            cout << "5. Delete Route\n";
            cout << "0. Back\n";
            cout << "Choice: ";
            cin >> choice;

            switch(choice) {
                case 1:
                    cout << "Source: "; cin >> src;
                    cout << "Destination: "; cin >> dest;
                    cout << "Distance (km): "; cin >> dist;
                    cout << "Time (min): "; cin >> timeVal;
                    routeMgr.addRoute(src, dest, dist, timeVal);
                    break;
                case 2:
                    routeMgr.displayAllRoutes();
                    break;
                case 3:
                    cout << "Source: "; cin >> src;
                    cout << "Destination: "; cin >> dest;
                    routeMgr.findShortestPath(src, dest);
                    break;
                case 4:
                    cout << "Source: "; cin >> src;
                    cout << "Destination: "; cin >> dest;
                    cout << "New Distance: "; cin >> dist;
                    cout << "New Time: "; cin >> timeVal;
                    routeMgr.updateRoute(src, dest, dist, timeVal);
                    break;
                case 5:
                    cout << "Source: "; cin >> src;
                    cout << "Destination: "; cin >> dest;
                    routeMgr.deleteRoute(src, dest);
                    break;
            }
        } while (choice != 0);
    }

    void aiMenu() {
        int choice;
        string mode, mood, routeName;
        bool avoidTolls, preferScenic;

        do {
            cout << "\n=== AI ASSISTANT ===\n";
            cout << "1. Set Preferences\n";
            cout << "2. View Preferences\n";
            cout << "3. Add Favorite Route\n";
            cout << "4. Mood-based Suggestions\n";
            cout << "5. Predict ETA\n";
            cout << "0. Back\n";
            cout << "Choice: ";
            cin >> choice;

            switch(choice) {
                case 1:
                    cout << "Transport mode (car/bike/walk/bus/train): "; cin >> mode;
                    cout << "Avoid tolls? (0/1): "; cin >> avoidTolls;
                    cout << "Prefer scenic? (0/1): "; cin >> preferScenic;
                    aiAssistant.setPreferences(mode, avoidTolls, preferScenic);
                    break;
                case 2:
                    aiAssistant.displayPreferences();
                    break;
                case 3:
                    cout << "Route name to favorite: "; cin >> routeName;
                    aiAssistant.addFavorite(routeName);
                    break;
                case 4:
                    cout << "Your mood (relaxing/fastest/adventurous/economical): "; cin >> mood;
                    aiAssistant.suggestByMood(mood);
                    break;
                case 5: {
                    float dist, speed;
                    int traffic;
                    string weather;
                    cout << "Distance (km): "; cin >> dist;
                    cout << "Avg Speed (km/h): "; cin >> speed;
                    cout << "Traffic (1-5): "; cin >> traffic;
                    cout << "Weather: "; cin >> weather;
                    float eta = aiAssistant.predictETA(dist, speed, traffic);
                    if (eta > 0) {
                        eta = aiAssistant.adjustETAForWeather(eta, weather);
                        cout << "Predicted ETA: " << eta << " minutes\n";
                    }
                    break;
                }
            }
        } while (choice != 0);
    }

    void safetyMenu() {
        int choice;
        string location, type;

        do {
            cout << "\n=== SAFETY SYSTEM ===\n";
            cout << "1. Report Hazard\n";
            cout << "2. View Active Hazards\n";
            cout << "3. Send SOS\n";
            cout << "4. Resolve Hazard\n";
            cout << "0. Back\n";
            cout << "Choice: ";
            cin >> choice;

            switch(choice) {
                case 1:
                    cout << "Location: "; cin >> location;
                    cout << "Type: "; cin >> type;
                    safetySys.reportHazard(location, type);
                    break;
                case 2:
                    safetySys.displayActiveHazards();
                    break;
                case 3:
                    cout << "Your location: "; cin >> location;
                    safetySys.sendSOS(location);
                    break;
                case 4:
                    cout << "Location: "; cin >> location;
                    cout << "Type: "; cin >> type;
                    safetySys.resolveHazard(location, type);
                    break;
            }
        } while (choice != 0);
    }

    void indoorMenu() {
        int choice;
        string building, room1, room2;
        int floor;

        do {
            cout << "\n=== INDOOR NAVIGATION ===\n";
            cout << "1. Add Indoor Location\n";
            cout << "2. Find Indoor Path\n";
            cout << "3. View All Indoor Locations\n";
            cout << "0. Back\n";
            cout << "Choice: ";
            cin >> choice;

            switch(choice) {
                case 1:
                    cout << "Building: "; cin >> building;
                    cout << "Floor: "; cin >> floor;
                    cout << "Room: "; cin >> room1;
                    indoorNav.addLocation(building, floor, room1);
                    break;
                case 2:
                    cout << "Start: "; cin >> room1;
                    cout << "End: "; cin >> room2;
                    indoorNav.findPath(room1, room2);
                    break;
                case 3:
                    indoorNav.displayAllLocations();
                    break;
            }
        } while (choice != 0);
    }

    void createDefaultData() {
        cout << "\n⚠ No data found. Creating default data...\n";

        locationMgr.addLocation("Dhaka");
        locationMgr.addLocation("Chittagong");
        locationMgr.addLocation("Rajshahi");
        locationMgr.addLocation("Sylhet");
        locationMgr.addLocation("Khulna");

        // Add default routes
        routeMgr.addRoute("Dhaka", "Chittagong", 245.5, 5.0);
        routeMgr.addRoute("Dhaka", "Rajshahi", 256.0, 5.5);
        routeMgr.addRoute("Dhaka", "Sylhet", 238.0, 5.2);
        routeMgr.addRoute("Chittagong", "Sylhet", 390.0, 7.0);

        // Set default preferences
        aiAssistant.setPreferences("car", false, true);
        aiAssistant.addFavorite("Dhaka -> Chittagong");
        aiAssistant.addFavorite("Dhaka -> Sylhet");

        // Add some hazards
        safetySys.reportHazard("Dhaka-Chittagong Highway", "construction");
        safetySys.reportHazard("Sylhet City", "flood");

        cout << "Default data created.\n";
    }

public:
    mainMap() : routeMgr(locationMgr) {
        srand(time(nullptr));
    }

    void run() {
        cout << "\n Initializing Route Map System...\n";
        cout << "System Ready!\n";

        loadAllData();

        int choice;
        do {
            showMainMenu();
            cin >> choice;

            switch(choice) {
                case 1: locationMenu(); break;
                case 2: routeMenu(); break;
                case 3: aiMenu(); break;
                case 4: safetyMenu(); break;
                case 5: indoorMenu(); break;
                case 6: saveAllData(); break;
                case 7: loadAllData(); break;
                case 0:
                    cout << "\nThank you for using Route Map System!\n";
                    saveAllData();
                    break;
                default:
                    cout << "Invalid choice!\n";
            }
        } while (choice != 0);
    }

    void saveAllData() {
        locationMgr.saveToFile("locations.dat");
        routeMgr.saveToFile("routes.dat");
        aiAssistant.saveToFile("preferences.txt");
        safetySys.saveToFile("hazards.dat");
        cout << "All data saved!\n";
    }

    void loadAllData() {
        bool locLoaded = locationMgr.loadFromFile("locations.dat");
        bool routeLoaded = routeMgr.loadFromFile("routes.dat");
        bool prefLoaded = aiAssistant.loadFromFile("preferences.txt");
        bool safetyLoaded = safetySys.loadFromFile("hazards.dat");

        if (!locLoaded || !routeLoaded || !prefLoaded || !safetyLoaded) {
            createDefaultData();
            saveAllData();
        }
    }
};

int main() {
    mainMap app;
    app.run();
    return 0;
}