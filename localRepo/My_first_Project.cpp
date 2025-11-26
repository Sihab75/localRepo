#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <climits>
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
    Location_Node head;
    void push_back (string n, float xx, float yy, int i) {
        Location_Node* newNode = new Location_Node (n, xx, yy, i);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        Location_Node* temp = head;
        while (temp->next == nullptr) {
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
        while (temp != head) {
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
};

class Route {
    int src, dest;
    float distance;
    float time;
    float cost;
    int trafficLevel;
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
        temp->next = head;
    }
public:
    void add_Route (string source, string destination, float dis, float timeV) {
        Location l;
        if (dis <= 0 || timeV <=0) {
            cout << "Error: Distance and time must be positive values!" << endl;
            return;
        }
        int srcIdx = l.find_Location_Index (source);
        int destIdx = l.find_Location_Index (destination);
        if (srcIdx == -1 || destIdx == -1) {
            cout << "Error: Source and destination location not found!" << endl;
            return;
        }
        if (srcIdx == destIdx) {
            cout << "Error: Source and destination cannot be the same!" << endl;
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
        push_back (srcIdx, destIdx, dis, timeV, cost, 1);
        Route_Count++;
        cout << "Route from '" << source << "' to '" << destination << "' added successfully! (Total routes: " << Route_Count << ")" << endl;
    }
    void show_All_Routes () {
        Location l;
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
    void find_Shortest_Path (sring source, string destination) {
        Location l;
        int srcIdx = l.find_Location_Index (source);
        int destIdx = l.find_Location_Index (destination);
        if (srcIdx == -1 || destination == -1) {
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

