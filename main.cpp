// #include <iostream>
// #include <string>
// #include <math.h>
#include <bits/stdc++.h>
using namespace std;

#define endl "\n"
#define tab "\t"

struct Date
{

    int day, year;
    string month;
    Date(int d, string mon, int yr)
    {
        day = d;
        month = mon;
        year = yr;
    }
    Date()
    {
        day = 1;
        month = "January";
        year = 2024;
    }
};

struct Time
{
    int hour, minutes;
    Time(int hr, int min)
    {
        hour = hr;
        minutes = min;
    }
};

class Flight
{
public:
    string source, destination;
    Date *depart_date;
    Time *depart_time, *duration;
    float price, flight_number;
    int seats, filled_seats, empty_seats;
    Flight *next_flight, *prev_flight;

    Flight()
    {
        int DAY, YEAR, depart_hour, depart_min, dur_hour, dur_min;
        string MONTH;

        cout << "------------------Enter Flight Details------------------";
        cout << endl
             << "Enter Flight Number : ";
        cin >> flight_number;
        cout << endl
             << "Departure From : ";
        cin >> source;
        cout << endl
             << "Destination : ";
        cin >> destination;
        cout << endl
             << "Date Of Departure : ";
        cout << endl
             << tab << "Day : ";
        cin >> DAY;
        cout << endl
             << tab << "Month : ";
        cin >> MONTH;
        cout << endl
             << tab << "Year : ";
        cin >> YEAR;
        cout << endl
             << "Time Of Departure : ";
        cout << endl
             << tab << "Hours : ";
        cin >> depart_hour;
        cout << endl
             << tab << "Minutes : ";
        cin >> depart_min;
        cout << endl
             << "Duration of Flight : ";
        cout << endl
             << tab << "Hours : ";
        cin >> dur_hour;
        cout << endl
             << tab << "Minutes : ";
        cin >> dur_min;
        cout << endl
             << "Ticket Price : ";
        cin >> price;
        cout << endl
             << "Total Number Of Seats In Flight : ";
        cin >> seats;
        do
        {
            cout << endl
                 << "Occupied Seats : ";
            cin >> filled_seats;
            if (filled_seats > seats)
                cout << "Occupied Seats Cannot be GREATER than total Number Of Seats." << endl;
        } while (filled_seats > seats);

        empty_seats = seats - filled_seats;
        depart_date = new Date(DAY, MONTH, YEAR);
        depart_time = new Time(depart_hour, depart_min);
        duration = new Time(dur_hour, dur_min);

        cout << endl
             << "Flight Detail Registered Successfully ;)" << endl;

        next_flight = nullptr, prev_flight = nullptr;
    }
};

class FlightManagement
{
public:
    Flight *first, *last;

public:
    FlightManagement()
    {
        first = last = NULL;
    }
    void AddFlight()
    {
        Flight *new_flight = new Flight();
        if (first == NULL)
        {
            first = new_flight;
            last = first;
        }
        last->next_flight = new_flight;
        new_flight->prev_flight = last;
        last = last->next_flight;
    }

    Flight *ToPos(Flight *&current_flight, int flight_number)
    {
        while (current_flight->flight_number != flight_number)
        {
            current_flight = current_flight->next_flight;
            if (current_flight == NULL)
            {
                cout << "!!! Error !!!" << endl
                     << "No Flight With Flight Number " << flight_number << " Found." << endl;
                break;
            }
        }
        return current_flight;
    }

    void RemoveFlight(int flight_number)
    {
        Flight *current_flight = first;
        ToPos(current_flight, flight_number);

        if (current_flight == NULL)
            return;
        if (current_flight->next_flight != NULL)
        {
            current_flight->next_flight->prev_flight = current_flight->prev_flight;
        }
        current_flight->prev_flight->next_flight = current_flight->next_flight;
        free(current_flight);
    }

    void UpdateFlightDetails(int flight_number)
    {
        Flight *current_flight = first, *temp_flight;
        ToPos(current_flight, flight_number);
        cout << "Update Flight Details : " << endl;
        temp_flight = new Flight();
        temp_flight->next_flight = current_flight->next_flight;
        temp_flight->prev_flight = current_flight->prev_flight;
        if (current_flight->prev_flight != nullptr)
            current_flight->prev_flight->next_flight = temp_flight;
        if (current_flight->next_flight != nullptr)
            current_flight->next_flight->prev_flight = temp_flight;
        free(current_flight);
        cout << "Flight Details Updated Successfully ;)" << endl;
    }

    void DisplayMessage()
    {
        if (first == NULL)
        {
            cout << "No Flights To Display" << endl;
            return;
        }
        cout << endl
             << endl
             << "------------Flight Details Are------------" << endl
             << endl;
    }

    void DisplayDetails(Flight *current_flight)
    {

        DisplayMessage();

        if (current_flight == NULL)
            return;

        cout << endl
             << endl
             << "------------ ------------" << endl
             << endl;
        cout << "Flight Number : " << current_flight->flight_number << endl;
        cout << "Departure : " << current_flight->source << endl;
        cout << "Destination : " << current_flight->destination << endl;
        cout << "Departure Time : " << current_flight->depart_time->hour << " : " << current_flight->depart_time->minutes << endl;
        cout << "Departure Date : " << current_flight->depart_date->day << "th " << current_flight->depart_date->month << " " << current_flight->depart_date->year << endl;
        cout << "Duration of Flight : " << current_flight->duration << endl;
        cout << "Fare Price : " << current_flight->price << endl;
        cout << "Total Seats : " << current_flight->seats << endl;
        cout << "Seats Occupied : " << current_flight->filled_seats << endl;
        cout << "Empty Seats : " << current_flight->empty_seats;
        cout << endl
             << endl;
    }

    void DisplayAll()
    {

        DisplayMessage();

        if (first == NULL)
            return;

        Flight *current_flight = first;

        if (current_flight->next_flight == NULL)
        {
            DisplayDetails(current_flight);
            return;
        }

        while (current_flight != NULL)
        {
            DisplayDetails(current_flight);
            current_flight = current_flight->next_flight;
        }
    }

    void DisplayFlight(int flight_number)
    {

        // DisplayMessage();

        if (first == NULL)
            return;

        Flight *current_flight = first;
        ToPos(current_flight, flight_number);
        if (current_flight != NULL)
            DisplayDetails(current_flight);
    }

    Flight *ToFlight(int flight_number)
    {
        Flight *current_flight = first;
        ToPos(current_flight, flight_number);
        return current_flight;
    }
};

class Passenger
{
public:
    string first_name, last_name;
    int age, passenger_id, flight_number;
    char sex;
    Flight *flight_details;
    Passenger *next, *prev;

    Passenger()
    {
        cout << "------------------------ Enter Passenger's Information -----------------------";
        cout << endl
             << "First Name : ";
        cin >> first_name;
        cout << endl
             << "Last Name : ";
        cin >> last_name;
        cout << "Gender : ";
        cin >> sex;
        cout << endl
             << "Age : ";
        cin >> age;
        cout << endl
             << "Passenger ID : ";
        cin >> passenger_id;
        cout << endl
             << "Enter Flight Number : ";
        cin >> flight_number;
        cout << endl;
        flight_details = FlightManagement().ToFlight(flight_number);
        next = nullptr;
        prev = nullptr;
    }
};

class Reservation : FlightManagement
{
    Passenger *first, *last;

public:
    Reservation()
    {
        first = last = NULL;
    }

    bool Availability(int flight_number, bool redeem)
    {
        Flight *temp = FlightManagement().first;
        ToPos(temp, flight_number);
        if (temp->empty_seats >= 1)
        {
            if (redeem)
                UpdateSeats(temp);
            return true;
        }
        return false;
    }

    void UpdateSeats(Flight *Flight)
    {
        Flight->empty_seats--;
        Flight->filled_seats++;
    }

    void AddPassenger()
    {

        Passenger *new_passenger = new Passenger();
        bool allotted = false;

        do
        {
            if (Availability(new_passenger->flight_number, true))
            {
                allotted = true;
            }
            else
            {
                cout << "Seat Not Availabe in Flight " << new_passenger->flight_number << endl;
                cout << "Enter Flight Number : ";
                cin >> new_passenger->flight_number;
                cout << endl;
            }
        } while (!allotted);

        if (first == NULL)
        {
            first = last = new_passenger;
            return;
        }
        last->next = new_passenger;
        new_passenger->prev = last;
        last = last->next;
    }

    Passenger *ToPassenger(Passenger *&cur_passenger, int id)
    {

        while (cur_passenger->passenger_id != id)
        {
            cur_passenger = cur_passenger->next;
            if (cur_passenger == NULL)
            {
                cout << "No Passenger With PassengerID " << id << "Found." << endl;
                break;
            }
        }
        return cur_passenger;
    }

    void RemovePassenger(int id)
    {
        if (first == NULL)
        {
            cout << "NO Passengers" << endl;
            return;
        }

        Passenger *cur_passenger = first;
        char choice;

        ToPassenger(cur_passenger, id);
        if (cur_passenger == NULL)
        {
            cout << "Do You Want To re-enter Passenger ID [y/other] : ";
            cin >> choice;
            cout << endl;
            if (choice == 'y')
            {
                cout << "Enter Passenger ID : ";
                cin >> id;
                cur_passenger = first;
                ToPassenger(cur_passenger, id);
            }
        }
        if (cur_passenger->next != NULL)
            cur_passenger->next->prev = cur_passenger->prev;

        cur_passenger->prev->next = cur_passenger->next;
        free(cur_passenger);
    }

    void PassengerDetails(int id)
    {
        char choice;

        if (first == NULL)
        {
            cout << "No Passengers" << endl;
            return;
        }
        Passenger *cur_passenger = first;
        ToPassenger(cur_passenger, id);
        if (cur_passenger == NULL)
        {
            cout << "Do You Want To re-enter Passenger ID [y/other] : ";
            cin >> choice;
            cout << endl;
            if (choice == 'y')
            {
                cout << "Enter Passenger ID : ";
                cin >> id;
                cur_passenger = first;
                ToPassenger(cur_passenger, id);
            }
        }

        cout << "ID : " << cur_passenger->passenger_id << endl;
        cout << "Name : " << cur_passenger->first_name << " " << cur_passenger->last_name << endl;
        cout << "Age : " << cur_passenger->age << endl;
        cout << "Flight Details : ";
        DisplayFlight(cur_passenger->flight_number);
        cout << endl;
    }

    void ShowAll()
    {
        if (first == NULL)
        {
            cout << "No Passengers" << endl;
            return;
        }
        Passenger *cur_passenger = first;
        while (cur_passenger != NULL)
        {
            cout << "------ ------" << endl;
            cout << "ID : " << cur_passenger->passenger_id << endl;
            cout << "Name : " << cur_passenger->first_name << " " << cur_passenger->last_name << endl;
            cout << "Flight Number" << cur_passenger->flight_number << endl;
            cur_passenger = cur_passenger->next;
        }
    }
};

void Menu(FlightManagement &, Reservation &);
void FlightMenu(FlightManagement &, Reservation &);
void CustomerMenu(FlightManagement &, Reservation &);

string Invalid()
{

    cout << "Invalid Choice, Try Again";
    return endl;
}

void Menu(FlightManagement &flight, Reservation &customer)
{

    int choice;

    do
    {
        cout << "1. Flight Management" << endl;
        cout << "2. Customer Management" << endl;
        cout << "3. Go Back" << endl;

        cin >> choice;
        switch (choice)
        {
        case 1:
            FlightMenu(flight, customer);
            break;
        case 2:
            CustomerMenu(flight, customer);
            break;
        case 3:
            return;
        default:
            cout << Invalid();
        }

    } while (1);
}

void FlightMenu(FlightManagement &flight, Reservation &customer)
{

    int choice, flight_number, sub_choice;

    while (1)
    {

        cout << endl;
        cout << "1. Add Flight." << endl;
        cout << "2. Update Flight." << endl;
        cout << "3. Display Details Of Flight." << endl;
        cout << "4. Remove Flight" << endl;
        cout << "5. Customer Management." << endl;
        cout << "6. Go Back." << endl;

        cin >> choice;

        switch (choice)
        {

        case 1:
            flight.AddFlight();
            break;

        case 2:
            cout << "Enter Flight Number : ";
            cin >> flight_number;
            cout << endl;
            flight.UpdateFlightDetails(flight_number);
            break;

        case 3:
            while (1)
            {
                cout << "1. Show Details Of All Flight." << endl;
                cout << "2. Show Details Of A Particular Flight." << endl;
                cout << "3. Go Back" << endl;
                cin >> sub_choice;

                switch (sub_choice)
                {
                case 1:
                    flight.DisplayAll();
                    break;

                case 2:
                    cout << "Enter Flight Number : ";
                    cin >> flight_number;
                    cout << endl;
                    flight.DisplayFlight(flight_number);
                    break;

                case 3:
                    break;

                default:
                    cout << Invalid();
                }
                if (sub_choice <= 3 && sub_choice > 0)
                    break;
            }
            break;

        case 4:
            cout << "Enter Flight Number : ";
            cin >> flight_number;
            cout << endl;
            flight.RemoveFlight(flight_number);
            break;

        case 5:
            CustomerMenu(flight, customer);
            break;

        case 6:
            return;

        default:
            cout << Invalid();
        }
    }
}

void CustomerMenu(FlightManagement &flight, Reservation &customer)
{

    int choice, sub_choice, customer_id;

    while (1)
    {

        cout << "1. New Passenger." << endl;
        cout << "2. Display Passenger Details." << endl;
        cout << "3. Remove Passenger" << endl;
        cout << "4. Flight Management" << endl;
        cout << "5. Go Back" << endl;
        cin >> choice;

        switch (choice)
        {

        case 1:
            customer.AddPassenger();
            break;

        case 2:
            while (1)
            {
                cout << "1. Particular Passenger." << endl;
                cout << "2. All Passengers." << endl;
                cout << "3. Go Back" << endl;
                cin >> sub_choice;

                switch (sub_choice)
                {
                case 1:
                    cout << "Enter Passenger ID : ";
                    cin >> customer_id;
                    customer.PassengerDetails(customer_id);
                    break;

                case 2:
                    customer.ShowAll();
                    break;

                case 3:
                    break;

                default:
                    cout << Invalid();
                }

                if (sub_choice <= 3 && sub_choice >= 1)
                    break;
            }

            break;

        case 3:
            cout << "Enter Customer ID : ";
            cin >> customer_id;
            cout << endl;
            customer.RemovePassenger(customer_id);
            break;

        case 4:
            FlightMenu(flight, customer);
            break;

        case 5:
            return;

        default:
            cout << Invalid();
        }
    }
}

int main()
{

    FlightManagement flight;
    Reservation customer;
    int choice;

    cout << "------------------------ Welcome To Flight ManageMent System ------------------------" << endl;

    do
    {
        cout << "------ What Do You Want To Do ------" << endl;
        cout << "1. Main Menu" << endl;
        cout << "2. Exit" << endl;

        cin >> choice;

        if (choice == 1)
        {
            Menu(flight, customer);
        }

        else if (choice == 2)
        {
            break;
        }

        else
        {
            cout << Invalid();
        }

    } while (1);

    cout << endl
         << "----------------------- ThankYou For Using Our Flight Reservation System -------------" << endl;

    return 0;
}