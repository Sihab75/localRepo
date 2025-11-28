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
};

class Hazard{
    string location;
    string type;
    string severity;
    int active;
    time_t reportedTime;
public:

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