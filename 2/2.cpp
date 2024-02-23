// Maxwell Bohn
// AERSP 424 HW1 #2

#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() 
{
    // initialize map container
    map<string, map<string, int>> flights;

    // Add flight information
    flights["SCE"]["PHL"] = 160;
    flights["SCE"]["ORD"] = 640;
    flights["SCE"]["EWR"] = 220;

    // Accessing flight information
    cout << "Distance between State College and Philadelphia: " << flights["SCE"]["PHL"] << " miles\n";
    cout << "Distance between State College and Chicago: " << flights["SCE"]["ORD"] << " miles\n";
    cout << "Distance between State College and Newark: " << flights["SCE"]["EWR"] << " miles\n";

    return 0;
}