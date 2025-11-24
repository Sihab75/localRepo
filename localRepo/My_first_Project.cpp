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
public:

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

