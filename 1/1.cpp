// Maxwell Bohn
// AERSP 424 HW1 #1

#include <iostream>

using namespace std;

int main() 
{
    // declaring and initializing variables to store user inputs
    double max_weight = 2950, fwd_CG_lim = 82.1, aft_CG_lim = 84.7; // design limits
    double airplane_empty_weight = 0, baggage_weight = 0, weight_front_passengers = 0, weight_rear_passengers = 0, fuel_weight=0; // weights
    int num_front_seat_occupants = 0, num_rear_seat_occupants = 0; // number of passengers
    double front_seat_moment_arm = 0, rear_seat_moment_arm = 0, fuel_tank_moment_arm = 0, airplane_empty_weight_moment = 0, baggage_moment_arm = 0; // moment arms
    double usable_fuel_weights_per_gallon = 0, num_gallons_usable_fuel = 0; // fuel

    // Get inputs from the user
    cout << "Enter airplane empty weight (pounds): ";
    cin >> airplane_empty_weight;

    cout << "Enter airplane empty-weight moment (pounds-inches): ";
    cin >> airplane_empty_weight_moment;

    cout << "Enter the number of front seat occupants: ";
    cin >> num_front_seat_occupants;

    double *weight_front_individuals = new double[num_front_seat_occupants]; // declare array for number of front occupants

    for (int i = 0; i < num_front_seat_occupants; ++i) // getting weights for all front entered passengers
    {
        cout << "Enter weight (pounds) of passenger " << i + 1 << ": ";
        cin >> weight_front_individuals[i];
        weight_front_passengers += weight_front_individuals[i];
    }

    cout << "Enter front seat moment arm (inches): ";
    cin >> front_seat_moment_arm;

    cout << "Enter the number of rear seat occupants: ";
    cin >> num_rear_seat_occupants;

    double *weight_rear_individuals = new double[num_rear_seat_occupants]; // declare array for number of rear occupants

    for (int i = 0; i < num_rear_seat_occupants; ++i) // getting weights for all rear entered passengers
    {
        cout << "Enter weight (pounds) of passenger " << i + 1 << ": ";
        cin >> weight_rear_individuals[i];
        weight_rear_passengers += weight_rear_individuals[i];
    }

    cout << "Enter rear seat moment arm (inches): ";
    cin >> rear_seat_moment_arm;

    cout << "Enter the amount of usable fuel (gallons): ";
    cin >> num_gallons_usable_fuel;

    cout << "Enter usable fuel weights per gallon (pounds): ";
    cin >> usable_fuel_weights_per_gallon;

    fuel_weight = num_gallons_usable_fuel*usable_fuel_weights_per_gallon;

    cout << "Enter fuel tank moment arm (inches): ";
    cin >> fuel_tank_moment_arm;

    cout << "Enter baggage weight (pounds): ";
    cin >> baggage_weight;

    cout << "Enter baggage moment arm (inches): ";
    cin >> baggage_moment_arm;

    // Calculate total weight and moment
    double total_weight = airplane_empty_weight + baggage_weight + weight_front_passengers + weight_rear_passengers + fuel_weight;
    double total_moment = airplane_empty_weight_moment + (baggage_weight * baggage_moment_arm) + (weight_front_passengers * front_seat_moment_arm) + (weight_rear_passengers * rear_seat_moment_arm) + (num_gallons_usable_fuel * usable_fuel_weights_per_gallon * fuel_tank_moment_arm);

    // Check if gross weight and C.G. location are within design limits
    if (total_weight <= max_weight && (total_moment/total_weight) >= fwd_CG_lim && (total_moment/total_weight) <= aft_CG_lim) 
    {
        cout << "The gross weight and C.G. location are within design limits.\n";
    }
    else 
    {
        cout << "\nUH OH!!!!!!!! You are outside of limits. Recalculating...\n";
        double fuel_adjustment = 0.0;
        double precision=0.01;
        while (total_weight > max_weight || (total_moment/total_weight) < fwd_CG_lim || (total_moment/total_weight) > aft_CG_lim) 
        {
            if (total_weight > max_weight) {
            total_weight -= 0.01;
            fuel_weight -= precision;
            fuel_adjustment -= precision;
            } else if ((total_moment/total_weight) > aft_CG_lim) {
            total_weight += 0.01;
            fuel_weight += precision;
            fuel_adjustment += precision;
            } else if ((total_moment/total_weight) < fwd_CG_lim) {
            total_weight -= 0.01;
            fuel_weight -= precision;
            fuel_adjustment -= precision;
            }
        }

        cout << "New gross weight: " << total_weight << " pounds\n";
        cout << "New CG location: " << (total_moment/total_weight) << " inches\n";

        // Display fuel adjustment
        if (fuel_adjustment > 0) 
        {
        cout << "Added " << fuel_adjustment << " pounds of fuel to meet limits.\n";
        } 
        else if (fuel_adjustment < 0) 
        {
        cout << "Drained " << -fuel_adjustment << " pounds of fuel to meet limits.\n";
        } 
        else 
        {
        cout << "No fuel adjustment needed.\n";
        }
    }

    delete[] weight_front_individuals;
    delete[] weight_rear_individuals;
    return 0;
}