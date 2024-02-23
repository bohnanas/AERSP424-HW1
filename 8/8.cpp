// Maxwell Bohn
// AERSP 424 HW1 #8

#include <iostream>
#include <map>
#include <string>

using namespace std;

class Plane
{
private:
    double pos = 0, vel = 0, distance;
    bool at_SCE = false;
    string origin, destination;
    map<string, map<string, int> > flights;

public:
    // Constructor
    Plane(string from, string to) : origin(from), destination(to)
    {
        flights["SCE"]["PHL"] = 160;
        flights["SCE"]["ORD"] = 640;
        flights["SCE"]["EWR"] = 220;
        distance = flights[from][to];
        cout << "Plane created with a tail number " << this << endl;
    }

    // Destructor
    ~Plane()
    {
        cout << "\nPlane Destroyed" << endl;
    }

    void operate(double dt)
    {
        if (vel < 0)
            vel = 0;
        else if (dt < 0)
            dt = 0;
        else if (pos < distance)
        {
            pos += vel * (dt / 3600.0);
            at_SCE = false;
        }
        else if (destination == "SCE")
        {
            at_SCE = true;
            string temp = origin;
            origin = destination;
            destination = temp;
        }
        else
        {
            string temp = origin;
            origin = destination;
            destination = temp;
            pos = 0;
        }
    }

    // get/set functions
    double getPosition()
    {
        return pos;
    }
    string getOrigin()
    {
        return origin;
    }
    string getDestination()
    {
        return destination;
    }
    bool get_at_SCE()
    {
        return at_SCE;
    }
    double getVelocity()
    {
        return vel;
    }
    void setVelocity(double newVelocity)
    {
        vel = newVelocity;
    }
};

class Pilot
{
private:
    string name;

public:
    // Constructor
    Pilot(string pilotName) : name(pilotName)
    {
        cout << "Pilot " << name << " with certificate number " << this << " is at the gate, ready to board the plane." << endl;
    }

    // Destructor
    ~Pilot()
    {
        cout << "\nPilot " << name << " is out of the plane." << endl;
    }

    // get/set functions
    string getName()
    {
        return name;
    }

    // pointer to Plane object
    Plane* myPlane;
};

int main()
{
    // changed instantiation to dynamically allocated memory
    Plane* plane = new Plane("SCE", "PHL");
    Pilot* pilot1 = new Pilot("Alpha");
    Pilot* pilot2 = new Pilot("Bravo");

    // changed assignments to pointers
    pilot1->myPlane = plane;
    pilot2->myPlane = plane;

    double airspeed = 450.0; // mph
    plane->setVelocity(airspeed); // used arrow operator to access members through pointers
    double dt = 15.0;
    int max_iterations = 1500;

    // Assign pilots their "certificate numbers" (memory addresses)
    Pilot* PilotInCommand = pilot1;
    Pilot* CoPilot = pilot2;

    for (int i = 0; i <= max_iterations; i++)
    {
        plane->operate(dt); // used arrow operator to access members through pointers

        if (plane->get_at_SCE())
        {
            cout << "\nThe plane " << plane << " is at SCE" << endl;

            Pilot* temp = PilotInCommand;
            PilotInCommand = CoPilot;
            CoPilot = temp;

            PilotInCommand->myPlane = plane; // used arrow operator to access members through pointers
            CoPilot->myPlane = nullptr;

            cout << "Pilot " << PilotInCommand->getName() << " with certificate number " << PilotInCommand << " is now in control of a plane " << plane << endl;
            cout << "Pilot " << CoPilot->getName() << " with certificate number " << CoPilot << " is not in control of the plane." << endl;
        }
    }

    // deleting dynamically allocated memory
    delete plane;
    delete pilot1;
    delete pilot2;

    return 0;
}