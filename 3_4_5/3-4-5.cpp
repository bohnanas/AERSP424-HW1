// Maxwell Bohn
// AERSP 424 HW1 #3, 4, and 5

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
        cout << "Plane Destroyed" << endl;
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
        else if (destination == "SCE") // case where plane has reached SCE
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

int main()
{
    // Instantiate Plane object
    Plane plane("SCE", "PHL");

    // Set flight speed between 400-500 mph
    double airspeed = 450.0; // mph
    plane.setVelocity(airspeed);

    // Choose timestep between 10-100 seconds
    double dt = 15.0;

    // Choose maximum number of iterations between 1000-2000
    int max_iterations = 1500;

    // Iterative statement
    for (int i = 0; i <= max_iterations; i++)
    {
        if (i == 0) // check to make sure position = 0 at time = 0
        {
            cout << "Time: " << i << " seconds, Position: " << plane.getPosition() << " miles." << endl;
        }
        else
        {
        plane.operate(dt);
        cout << "Time: " << i*dt << " seconds, Position: " << plane.getPosition() << " miles." << endl;
        }
    }

    return 0;
}