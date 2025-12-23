#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <climits>
#include <cfloat>
#include <bits/stdc++.h>
using namespace std;

int Location_Count = 0;
int Route_Count = 0;
int Hazard_Count = 0;
int Indoor_Count = 0;

class Location_Node {
public:
    string name;
    float x, y;
    int id;
    Location_Node* next;
    Location_Node (string n, float xx, float yy, int i) {
        name = n;
        x = xx;
        y = yy;
        id = i;
        next = nullptr;
    }
};

class Route_Node {
public:
    int src, dest;
    float distance;
    float time;
    float cost;
    int traffic_Level;
    Route_Node* next;
    Route_Node (int s, int d, float dis, float t, float c, int traffic) {
        src = s;
        dest = d;
        distance = dis;
        time = t;
        cost = c;
        traffic_Level = traffic;
        next = nullptr;
    }
};

class Hazard_Node {
public:
    string location;
    string type;
    string severity;
    int active;
    time_t reported_time;
    Hazard_Node* next;
    Hazard_Node (string loc, string ty, string sev, int act) {
        location = loc;
        type = ty;
        severity = sev;
        active = act;
        reported_time = time (NULL);
        next = nullptr;
    }
};

class Indoor_Location_Node {
public:
    string building;
    int floor;
    string room;
    int id;
    Indoor_Location_Node* next;
    Indoor_Location_Node (string bui, int flo, string roo, int i) {
        building = bui;
        floor = flo;
        room = roo;
        id = i;
    }
};

class Location {
    string name;
    float x, y;
    int id;
    Location_Node* head = nullptr;
    void push_back (string n, float xx, float yy, int i) {
        Location_Node* newNode = new Location_Node (n, xx, yy, i);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        Location_Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
public:
    void addLocation (string n) {
        if (n.size () == 0) {
            cout << "Error: Location name must getter then 1 characters" << endl;
            return;
        }
        Location_Node* temp = head;
        while (temp != nullptr) {
            if (temp->name == n) {
                cout << "Location '" << n <<"' Already exists!" << endl;
                return;
            }
            temp = temp->next;
        }
        float xx = (float) (rand() % 1000);
        float yy = (float) (rand() % 1000);
        push_back(n, xx, yy, Location_Count);
        Location_Count++;
        cout << "Location '" << n << "' added successfully! (Total Location is : " << Location_Count << ")" << endl;
    }
    int find_Location_Index (string n) {
        Location_Node* temp = head;
        int idx = 0;
        while (temp != nullptr) {
            if (temp->name == n) {
                return idx;
            }
            temp = temp->next;
            idx++;
        }
        return -1;
    }
    Location_Node* get_Location_By_Index (int idx) {
        if (idx < 0 || idx >= Location_Count) {
            return nullptr;
        }
        Location_Node* temp = head;
        int i = 0;
        while (temp != nullptr && i < idx) {
            temp = temp->next;
            i++;
        }
        return temp;
    }
    Location_Node* get_Location_By_Name (string n) {
        Location_Node* temp = head;
        while (temp != nullptr) {
            if (temp->name == n) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }
    void display_All_Locations() {
        cout << "=== ALL LOCATIONS ===" << endl;
        Location_Node* temp = head;
        int i = 0;
        while (temp != nullptr) {
            cout << i << ". " << temp->name << " (ID: " << temp->id << ")" << endl;
            temp = temp->next;
            i++;
        }
    }
};

class Route {
    int src, dest;
    float distance;
    float time;
    float cost;
    int trafficLevel;
    Route_Node* head = nullptr;
    void push_back (int s, int de, float dis, float timeV, float cos, int traffic) {
        Route_Node* newNode = new Route_Node (s, de, dis, timeV, cos, traffic);
        if (!newNode) {
            return;
        }
        if (head == nullptr) {
            head = newNode;
            return;
        }
        Route_Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
public:
    void add_Route (Location& l, string source, string destination, float dis, float timeV) {
        if (dis <= 0 || timeV <=0) {
            cout << "Error: Distance and time must be positive values!" << endl;
            return;
        }
        int srcIdx = l.find_Location_Index (source);
        int destIdx = l.find_Location_Index (destination);
        if (srcIdx == -1 || destIdx == -1) {
            cout << "Error: Source and destination location not found!" << endl;
            l.display_All_Locations ();
            return;
        }
        if (srcIdx == destIdx) {
            cout << "Error: Source and destination cannot be the same!" << endl;
            l.display_All_Locations ();
            return;
        }
        Route_Node* temp = head;
        while (temp != nullptr) {
            if (temp->src == srcIdx && temp->dest == destIdx) {
                cout << "Route from '" << source << "' to '" << destination << "' already exists!" << endl;
                return;
            }
            temp = temp->next;
        }
        float cos = dis * 0.5;
        push_back (srcIdx, destIdx, dis, timeV, cos, 1);
        Route_Count++;
        cout << "Route from '" << source << "' to '" << destination << "' added successfully! (Total routes: " << Route_Count << ")" << endl;
    }
    void show_All_Routes (Location &l) {
        if (head == nullptr) {
            cout << "No routes available!" << endl;
            return;
        }
        cout << endl << "=== ALL AVAILABLE ROUTES (" << Route_Count << " total) ===" << endl;
        Route_Node* temp = head;
        int i = 1;
        while (temp != nullptr) {
            Location_Node* srcLoc = l.get_Location_By_Index (temp->src);
            Location_Node* destLoc = l.get_Location_By_Index (temp->dest);
            if (srcLoc && destLoc) {
                cout << i <<'.' << ' ' << temp->src << "->" << temp->dest << " | Distance: " << temp->distance << " km | Time : " << temp->time << " min | Cost: " << temp->cost << " taka | Traffic: " << temp->traffic_Level << endl;
            } else {
                cout << i << "(invalid route indices) source = " << temp->src << "destination = " << temp->dest << endl;
            }
            temp = temp->next;
            i++;
        }
    }
    void find_Shortest_Path (Location& l, string source, string destination) {
        int srcIdx = l.find_Location_Index (source);
        int destIdx = l.find_Location_Index (destination);
        if (srcIdx == -1 || destIdx == -1) {
            cout << "Error: Source of destination not found!" << endl;
            return;
        }
        if (srcIdx == destIdx) {
            cout << "Source and destination are same!" << endl;
            return;
        }
        int n = Location_Count;
        if (n <= 0) {
            cout << "No location available." << endl;
            return; 
        }
        vector<float> dist(n, FLT_MAX);
        vector<bool> visited(n, false);
        vector<int> prev(n, -1);
        dist[srcIdx] = 0.0f;
        for (int i = 0; i < n - 1; i++) {
            float minDist = FLT_MAX;
            int minIdx = -1;
            for (int j = 0; j < n; j++) {
                if (!visited[j] && dist[j] < minDist) {
                    minDist = dist[j];
                    minIdx = j;
                }
            }
            if (minIdx == -1) {
                break;
            }
            visited[minIdx] = true;
            Route_Node* temp = head;
            while (temp != nullptr) {
                if (temp->src == minIdx) {
                    int adj = temp->dest;
                    float weight = temp->distance;
                    if (!visited[adj] && dist[minIdx] + weight < dist [adj]) {
                        dist[adj] = dist[minIdx] + weight;
                        prev [adj] = minIdx;
                    }
                }
                temp = temp->next;
            }
        }
        if (dist[destIdx] == FLT_MAX) {
            cout << "No path exists from " << src << " to " << dest << endl;
            return;
        }
        cout << "Shortest path From " << source << " to " << destination << endl;
        cout << "Total distance: " << dist[destIdx] << " km" << endl;
        vector <int> path;
        for (int current = destIdx; current != -1; current = prev[current]) {
            path.push_back (current);
        }
        cout << "Rote: ";
        for (int i = path.size() - 1; i >=0; i--) {
            Location_Node* loc = l.get_Location_By_Index (path[i]);
            cout << loc->name;
            if (i > 0) {
                cout << " -> ";
            }
        }
        cout << endl;
    }
    void display_Route_Details (Location& l) {
        if (head == nullptr) {
            cout << "No routes to display!" << endl;
            return;
        }
        cout << endl << "=== DETAILED ROUTE INFORMATION (" << Route_Count << " routes) ===" << endl;
        int i = 1;
        Route_Node* temp = head;
        while (temp != nullptr) {
            Location_Node* srcLoc = l.get_Location_By_Index(temp->src);
            Location_Node* destLoc = l.get_Location_By_Index (temp->dest);
            cout << endl << "Route " << i <<":"<< endl;
            if (srcLoc && destLoc) {
                cout << "  From: " << srcLoc->name << endl << "  To " << destLoc->name << endl;
            } else {
                cout << "  From:  (invalid) " << temp->src << endl << "  To: (invalid) " <<  temp->dest << endl;
            }
            cout << "  Distance: " << temp->distance << " km" << endl << "Estimated Time: " << temp->time << " minutes" << endl << "Estimated Cost: " << temp->cost << "taka" << endl << "Traffic Level: " << temp->traffic_Level << endl;
            temp = temp->next;
            i++;
        }
    }
    void delete_Route (Location& l, string source, string destination) {
        int srcIdx = l.find_Location_Index (source);
        int destIdx = l.find_Location_Index (destination);
        if (srcIdx == -1 || destIdx == -1) {
            cout << "Error: Source or destination location not found!" << endl;
            return;
        }
        Route_Node* current = head;
        Route_Node* prev = nullptr;
        bool found = true;
        while (current != nullptr) {
            if (current->src == srcIdx && current->dest == destIdx) {
                found = false;
                if (prev == nullptr) {
                    head = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                Route_Count--;
                cout << "Route from " << source << " to " << destination << " Deleted successfully! (Remaining routes:" << Route_Count << ")" << endl;
                break;
            }
            prev = current;
            current = current->next;
        }
        if (found) {
            cout << "No route found from " << source << " to " << destination << '!' << endl;
        }
    }
    void update_Route (Location l, string source, string destination, float newDistance, float newTime) {
        if (newDistance <= 0 || newTime <= 0) {
            cout << "Error: Distance and time must be positive values!" << endl;
            return;
        }
        int srcIdx = l.find_Location_Index (source);
        int destIdx = l.find_Location_Index (destination);
        if (src == -1 || destIdx == -1) {
            cout << "Error: Source or destination location not found!" << endl;
            return;
        }
        Route_Node* temp = head;
        bool found = true;
        while (temp != nullptr) {
            if (temp->src == srcIdx && temp->dest == destIdx) {
                temp->distance = newDistance;
                temp->time = newTime;
                temp->cost = newDistance * 0.5f;
                found = false;
                break;
            }
            temp = temp->next;
        }
        if (found) {
            cout << "No route found from " << source << " to " << destination << '!' << endl;
        }
    }
    void search_Route (Location l, string location_Name) {
        int locIdx = l.find_Location_Index (location_Name);
        if (locIdx == -1) {
            cout << "Location " << location_Name << " not found!" << endl;
            return;
        }
        cout << endl << "=== ROUTES CONTAINING " << location_Name << " ===" << endl;
        Route_Node* temp = head;
        int found_Count = 0;
        while (temp != nullptr) {
            if (temp->src == locIdx || temp->dest == locIdx) {
                Location_Node* srcLoc = l.get_Location_By_Index (temp->src);
                Location_Node* destLoc = l.get_Location_By_Index (temp->dest);
                if (srcLoc && destLoc) {
                    cout << found_Count + 1 << ". " << srcLoc->name << " -> " << destLoc->name << " | Distance: " << temp->distance << " km | Time: " << temp->time << " min | Traffic: " << temp->traffic_Level << "/5" << endl;
                } else {
                    cout << found_Count + 1 << ". (invalid route indices)" << endl;
                }
                found_Count++;
            }
            temp = temp->next;
        }
        if (found_Count == 0) {
            cout << "No routes found containing " << location_Name << endl;
        } else {
            cout << "Total " << found_Count << " routes found." << endl;
        }
    }
    Route_Node* route_head () {
        return head;
    }
};


class AI {
    string transportMode;
    int avoidTolls;
    int preferScenic;
    vector <string> favoriteRoutes;
    int favCount;
    int favCapacity;
public:
    float predictETA (float distance, float avgSpeed, int trafficLevel) {
        if (distance <= 0.0f) {
            cout << "Error: Distance must be positive!" << endl;
            return -1.0f;
        }
        if (avgSpeed <= 0.0f) {
            cout << "Error: Average speed must be positive!" << endl;
            return -1.0f;
        }
        if (trafficLevel < 1 || trafficLevel > 5) {
            cout << "Error: Traffic level must be between 1-5!" << endl;
            return -1.0f;
        }
        float bestTime = (distance / avgSpeed) * 60.0f;
        float trafficFactor = 1.0f + ((trafficLevel - 1) * 0.2f);
        return bestTime * trafficFactor;
    }

    float adjustETAByWeather(float eta, const string& weather) {
        if (eta <= 0.0f) return eta;

        float weatherFactor = 1.0f;

        if (weather == "rainy") weatherFactor = 1.3f;
        else if (weather == "stormy") weatherFactor = 1.6f;
        else if (weather == "foggy") weatherFactor = 1.4f;
        else if (weather == "snowy") weatherFactor = 1.8f;
        else if (weather == "sunny") weatherFactor = 1.0f;
        else if (weather == "clear") weatherFactor = 0.9f;
        else {
            cout << "Unknown weather condition '" << weather << "', using default factor 1.1" << endl;
            weatherFactor = 1.1f;
        }

        cout << "Weather condition: " << weather << " | Adjustment factor: " << weatherFactor << endl;

        return eta * weatherFactor;
    }

    void update_Traffic_Data (Route r,/*string routeName,*/ int traffic) {
        if (traffic < 1 || traffic > 5) {
            cout << "Error: Traffic level must be 1-5!" << endl;
            return;
        }
        cout << "Updating traffic Data for routes..." << endl;
        Route_Node* temp = r.route_head ();
        int updatedCount = 0;
        while (temp != nullptr) {
            temp->traffic_Level = traffic;
            temp->time = temp->time * (1.0f + (traffic - 1) * 0.15f);
            updatedCount++;
            temp = temp->next;
        }
        cout << "Traffic data updated to level " << traffic << " for " << updatedCount << " routes" << endl;
    }

    void auto_Adjust_ETA(Location l, Route r, string source, string destination) {

        int srcIdx = l.find_Location_Index(source);
        int destIdx = l.find_Location_Index(destination);

        if (srcIdx == -1 || destIdx == -1) {
            cout << "Error: Source or destination not found!" << endl;
            return;
        }

        Route_Node* temp = r.route_head();
        bool found = false;

        while (temp != nullptr) {

            if (temp->src == srcIdx && temp->dest == destIdx) {

                found = true;

                float original_Time = temp->time;
                float adjusted_Time = temp->time;
                adjusted_Time = adjusted_Time * (1.0f + (temp->traffic_Level - 1) * 0.15f);
                vector<string> weatherList = {"sunny", "rainy", "foggy", "stormy", "clear"};
                string currentWeather = weatherList[rand() % weatherList.size()];
                adjusted_Time = adjustETAByWeather (adjusted_Time, currentWeather);
                cout << "\n===== AUTO ETA ADJUSTMENT =====" << endl;
                cout << "Route: " << source << " -> " << destination << endl;
                cout << "Original ETA: " << original_Time << " minutes" << endl;
                cout << "Traffic Level: " << temp->traffic_Level << "/5" << endl;
                cout << "Weather Condition: " << currentWeather << endl;
                cout << "Adjusted ETA: " << adjusted_Time << " minutes" << endl;
                cout << "Time difference: " << adjusted_Time - original_Time << " minutes" << endl;
                return;
            }
            temp = temp->next;
        }
        if (!found) {
            cout << "No direct route found from " << source << " to " << destination << endl;
        }
    }

    void setUserPreference (string mode, int avoidToll, int scenic) {
        if (mode != "char" && mode != "bike" && mode != "walk" && mode != "bus" && mode != "train") {
            cout << "Error: Transport mode must be 'car', 'bike', 'walk', 'bus','train' !" << endl;
            return;
        }
        transportMode = mode;
        avoidTolls = avoidToll;
        preferScenic = scenic;
        cout << "User preferences set successfully!" << endl << "Transport Mode: " << transportMode << endl << "Avoid Tolls:" << (avoidToll ? "Yes" : "No") << endl << "Prefer Scenic Routes: " << (scenic ? "Yes" : "No") << endl;
    }

    void getUserPreference () {
        cout << endl << "=== CURRENT USER PREFERENCES ===" << endl;
        cout << "Transport Mode: " << transportMode << endl << "Avoid Tolls: " << (avoidTolls ? "Yes": "No") << endl << "Prefer Scenic Routes: " << (preferScenic ? "Yes" : "No") << endl;
        if (favCount > 0) {
            cout << "Favorite Routes " << favCount << " : " << endl;
            for (int i = 0; i < favCount; i++) {
                cout << "  " <<  i + 1 << ". " << favoriteRoutes[i]; 
            }
            cout << "Favorites capacity: " << favCapacity << endl;
        } else {
            cout << "No favorite routes save." << endl;
        }
    }

    void suggestRouteBasedOnMood(string mood) {
        cout << "\n=== ROUTE SUGGESTIONS BASED ON MOOD: " << mood << " ===\n";

        if (mood == "relaxing") {
            cout << "Suggested: Scenic coastal route\n";
            cout << "Suggested: Mountain view pathway\n";
            cout << "Suggested: Park boulevard route\n";
            cout << "Suggested: Riverside drive\n";
            cout << "Suggested: Countryside lanes\n";
        }
        else if (mood == "fastest") {
            cout << "Suggested: Highway express route\n";
            cout << "Suggested: Direct city bypass\n";
            cout << "Suggested: Express toll route\n";
            cout << "Suggested: Freeway direct\n";
            cout << "Suggested: Urban expressway\n";
        }
        else if (mood == "adventurous") {
            cout << "Suggested: Mountain trail route\n";
            cout << "Suggested: Countryside exploration\n";
            cout << "Suggested: Forest pathway\n";
            cout << "Suggested: Hill climb route\n";
            cout << "Suggested: Off-road adventure\n";
        }
        else if (mood == "economical") {
            cout << "Suggested: Fuel-efficient pathway\n";
            cout << "Suggested: Toll-free route\n";
            cout << "Suggested: Shortest distance route\n";
            cout << "Suggested: Public transport route\n";
            cout << "Suggested: Carpool lanes\n";
        }
        else if (mood == "tourist") {
            cout << "Suggested: City landmarks route\n";
            cout << "Suggested: Historical sites tour\n";
            cout << "Suggested: Cultural district path\n";
            cout << "Suggested: Scenic overlook route\n";
            cout << "Suggested: Photo spots tour\n";
        }
        else {
            cout << "No specific suggestions for mood: " << mood << endl;
            cout << "Available moods: relaxing, fastest, adventurous, economical, tourist\n";
        }
    }

    void initUserPreferences () {
        transportMode = "car";
        avoidTolls = 0;
        preferScenic = -1;
        favCount = 0;
        favCapacity = 10;
        favoriteRoutes.clear ();
        favoriteRoutes.reserve (favCapacity);
    }
    void resizeFavoriteRoutesIfNeeded() {
        if (favoriteRoutes.size() >= (size_t) favCapacity) {
            favCapacity *= 2;
            favoriteRoutes.reserve(favCapacity);
            cout << "Expanded favorites capacity to " << favCapacity << endl;
        }
    }
    void addFavoriteRoute(string routeName) {
        resizeFavoriteRoutesIfNeeded ();
        for (string r: favoriteRoutes) {
            if (r == routeName) {
                cout << "Route '" << routeName << "' already in favorites!" << endl;
                return;
            }
        }
        favoriteRoutes.push_back(routeName);
        favCount++;
        cout << "Route '" << routeName << "' added to favorites! (Total favorites: " << favCount << ")" << endl;
    }
    void removeFavoriteRoute(string routeName) {
        int foundIndex = -1;
        for (size_t i = 0; i < favoriteRoutes.size(); i++) {
            if (favoriteRoutes[i] == routeName) {
                foundIndex = i;
                break;
            }
        }
        if (foundIndex == -1) {
            cout << "Route '" << routeName << "' not found in your favorites!" << endl;
            return;
        }
        favoriteRoutes.erase(favoriteRoutes.begin() + foundIndex);
        favCount--;
        cout << "Route '" << routeName << "' removed from favorites! (Remaining favorites: " << favCount << ")" << endl;
    }

};
class Hazard{
    string location;
    string type;
    string severity;
    int active;
    time_t reportedTime;
    Hazard_Node* head = nullptr;
public:
    void reportHazard(string loc, string typ) {
        if (typ != "accident" && typ != "road_block" && typ != "flood" && typ != "construction" && typ != "ice" && typ != "debris" && typ != "police" && typ != "animal") {
            cout << "Error: Invalid hazard type! Use: accident, road_block, flood, construction, ice, police, animal" << endl;
            return;
        }
        if (type == "accident" || type == "flood") severity = "High";
        else if (type == "road_block" || type == "ice") severity = "Medium";
        else if (type == "police" || type == "construction") severity = "Low";
        else if (type == "debris" || type == "animal") severity = "Medium";
        else severity = "Medium";
        Hazard_Node* newNode = new Hazard_Node(loc, typ, severity, 1);
        if (!head) {
            head = newNode;
        } else {
            Hazard_Node* temp = head;
            while (temp->next != nullptr) temp = temp->next;
            temp->next = newNode;
        }

        Hazard_Count++;
        cout << "Hazard reported at " << loc << ": " << typ << " (Severity: " << severity << ") (Total hazards: " << Hazard_Count << ")\n";
    }
    void viewActiveHazards() {
        if (!head) {
            cout << "\nNo hazards reported.\n";
            return;
        }

        cout << "\n=== ACTIVE HAZARDS ===\n";
        Hazard_Node* temp = head;
        int activeCount = 0;

        while (temp != nullptr) {
            if (temp->active) {
                activeCount++;
                cout << activeCount << ". Location: " << temp->location << " | Type: " << temp->type << " | Severity: " << temp->severity << " | Reported: " << ctime(&(temp->reported_time)); // readable time
            }
            temp = temp->next;
        }

        if (activeCount == 0) {
            cout << "No active hazards reported.\n";
        } else {
            cout << "Total active hazards: " << activeCount << endl;
        }
    }

};

class Indoor {
    string building;
    int floor;
    string room;
    int id;
public:

};

int main () {
    Location l;
    string name;
    getline (cin, name);
    l.addLocation (name);
    getline (cin, name);
    l.addLocation (name);
    l.display_All_Locations ();
    Route r;
    string source, destination;
    float distance, timeV;
    getline (cin, source);
    cout << "source is :" << source << endl;
    getline (cin, destination);
    cout << "destination is : " << destination << endl;
    cin >> distance;
    cin.ignore ();
    cin >> timeV;
    cin.ignore ();
    r.add_Route (l, source, destination, distance,timeV);
    r.show_All_Routes (l);
    r.find_Shortest_Path (l, source, destination);
    r.display_Route_Details (l);
    return 0;
}