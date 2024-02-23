// Maxwell Bohn
// AERSP 424 HW1 #6 and 7

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

    // container from question 2
    map<string, map<string, int>> flights;

public:
    // Constructor
    Plane(string from, string to) : origin(from), destination(to)
    {
        flights["SCE"]["PHL"] = 160;
        flights["SCE"]["ORD"] = 640;
        flights["SCE"]["EWR"] = 220;

        // Set the distance based on the flight between origin and destination
        distance = flights[from][to];

        cout << "Plane created with a tail number " << this << endl;
    }

    // Destructor
    ~Plane()
    {
        cout << "\nPlane Destroyed" << endl;
    }

    // operate function
    void operate(double dt)
    {
        if (vel < 0) // check for negative velocities and set to zero if true
        {
            vel = 0;
        }
        else if (dt < 0) // check for negative dt and set to zero if true
        {
            dt = 0;
        }
        else if (pos < distance) // case where plane has not yet reached destination (updating position)
        {
            pos += vel * (dt / 3600.0);
            at_SCE = false;
        }
        else if (destination == "SCE")
        {
            at_SCE = true;

            // Swap origin and destination
            string temp = origin;
            origin = destination;
            destination = temp;
        }
        else
        {
            // Swap origin and destination
            string temp = origin;
            origin = destination;
            destination = temp;

            pos = 0; // we have arrived, resetting position to zero
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
    // Constructor to print name and memory address
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

    // pointer named myPlane to an object of the Plane class
    Plane* myPlane;
};

int main() {
    // Instantiate Plane object
    Plane plane("SCE", "PHL");

    // Instantiate Pilot objects
    Pilot pilot1("Alpha");
    Pilot pilot2("Bravo");

    // Assign memory address of airplane
    pilot1.myPlane = &plane;
    pilot2.myPlane = &plane;

    // Set flight speed between 400-500 mph
    double airspeed = 450.0; // mph
    plane.setVelocity(airspeed);

    // Choose timestep between 10-100 seconds
    double dt = 15.0;

    // Choose maximum number of iterations between 1000-2000
    int max_iterations = 1500;

    // Assign pilots their "certificate numbers" (memory addresses)
    Pilot* PilotInCommand = &pilot1;
    Pilot* CoPilot = &pilot2;

    for (int i = 0; i <= max_iterations; i++) 
    {
        plane.operate(dt);

        if (plane.get_at_SCE()) // check to see if plane is in SCE
        {
            cout << "\nThe plane " << &plane << " is at SCE" << endl;

            // Switch control to the other pilot along with "certificate number" (memory address)
            Pilot* temp = PilotInCommand;
            PilotInCommand = CoPilot;
            CoPilot = temp;
            PilotInCommand->myPlane = &plane; // Update memory address
            CoPilot->myPlane = nullptr; // Release control for the other pilot

            cout << "Pilot " << PilotInCommand->getName() << " with certificate number " << PilotInCommand << " is now in control of a plane " << &plane << endl;
            cout << "Pilot " << CoPilot->getName() << " with certificate number " << CoPilot << " is not in control of the plane." << endl;
        }
    }

    return 0;
}