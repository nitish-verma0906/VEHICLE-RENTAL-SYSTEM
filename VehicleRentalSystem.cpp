
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
using namespace std;
//module 1
class Vehicle {
private:
    int id;
    string name;
    double rent;
    string status;

public:
    Vehicle() {
        id = 0;
        rent = 0;
        status = "Available";
    }

    void getData() {
        cout << "Enter Vehicle ID: ";
        cin >> id;

        cout << "Enter Vehicle Name : ";
        cin >> name;

        cout << "Enter Rent Per Day: ";
        cin >> rent;

        status = "Available";
    }

    int getId() {
        return id;
    }

    string getName() {
        return name;
    }

    double getRent() {
        return rent;
    }

    string getStatus() {
        return status;
    }

    virtual string getType() {
        return "Vehicle";
    }

    virtual void showDetails() {
        cout << "Vehicle ID: " << id << endl;
        cout << "Vehicle Name: " << name << endl;
        cout << "Rent Per Day: Rs. " << rent << endl;
        cout << "Status: " << status << endl;
    }

    virtual void saveToFile() {
        ofstream file("vehicles.txt", ios::app);

        file << getType() << endl;
        file << id << endl;
        file << name << endl;
        file << rent << endl;
        file << status << endl;

        file.close();
    }

    virtual ~Vehicle() {}
};

class Car : public Vehicle {
public:
    string getType() override {
        return "Car";
    }

    void showDetails() override {
        cout << "\nVehicle Type: Car" << endl;
        Vehicle::showDetails();
    }
};

class Bike : public Vehicle {
public:
    string getType() override {
        return "Bike";
    }

    void showDetails() override {
        cout << "\nVehicle Type: Bike" << endl;
        Vehicle::showDetails();
    }
};


void addVehicle() {
    int type;

    while (true) {
        cout << "\n1. Car" << endl;
        cout << "2. Bike" << endl;
        cout << "Press 0 to stop adding vehicles" << endl;
        cout << "Choose Vehicle Type: ";
        cin >> type;

        if (type == 0) {
            cout << "Vehicle adding stopped" << endl;
            break;
        }

        Vehicle *v;

        if (type == 1) {
            v = new Car;
        }
        else if (type == 2) {
            v = new Bike;
        }
        else {
            cout << "Invalid Vehicle Type" << endl;
            continue;
        }

        v->getData();

  

  

        v->saveToFile();

   
        v->showDetails();

        delete v;
    }
}


void viewVehicles() {
    ifstream file("vehicles.txt");

    string type, name, status;
    int id;
    double rent;
    bool found = false;

   while (getline(file, type)) {
    file >> id;
    file.ignore(1000, '\n');

    getline(file, name);

    file >> rent;
    file.ignore(1000, '\n');

    getline(file, status);

    cout << "\n----------------------" << endl;
    cout << "Vehicle Type: " << type << endl;
    cout << "Vehicle ID: " << id << endl;
    cout << "Vehicle Name: " << name << endl;
    cout << "Rent Per Day: Rs. " << rent << endl;
    cout << "Status: " << status << endl;

    found = true;
}
file.close();

    if (!found) {
        cout << "No Vehicle Found!" << endl;
    }
}


void deleteVehicle() {
    int deleteId, id;
    string type, name, status;
    double rent;
    bool found = false;

    cout << "Enter Vehicle ID to Delete: ";
    cin >> deleteId;

    ifstream file("vehicles.txt");
    ofstream temp("temp.txt");

    while (getline(file, type)) {
    file >> id;
    file.ignore(1000, '\n');

    getline(file, name);

    file >> rent;
    file.ignore(1000, '\n');

    getline(file, status);

    if (id == deleteId) {
        if (status == "Booked") {
            cout << "Vehicle is booked. Cannot delete" << endl;

            temp << type << endl << id << endl
                 << name << endl << rent << endl
                 << status << endl;
        }
        else {
            found = true;
        }
    }
    else {
        temp << type << endl << id << endl
             << name << endl << rent << endl
             << status << endl;
    }
}

file.close();
temp.close();

    remove("vehicles.txt");
    rename("temp.txt", "vehicles.txt");

    
}

// MODULE 2
class Rental : public Vehicle {
public:
    void rentVehicle() {
        int searchId, id, days;
        int bookingId = 1001;
        string type, name, status;
        double rent, total;
        bool found = false;

        cout << "Enter Vehicle ID to Rent: ";
        cin >> searchId;

       
        ifstream file("vehicles.txt");

       while (getline(file, type)) {
    file >> id;
    file.ignore(1000, '\n');

    getline(file, name);

    file >> rent;
    file.ignore(1000, '\n');

    getline(file, status);

    if (id == searchId && status == "Available") {
        found = true;
        break;
    }
}

file.close();

        if (!found) {
            cout << "Vehicle not available!" << endl;
            return;
        }

        cout << "Enter Number of Days: ";
        cin >> days;

        
        total = rent * days;

    
        ifstream bookings("bookings.txt");
        string line;
        int oldBookingId;

while (getline(bookings, line)) {
    if (line.empty())
        continue;

    oldBookingId = stoi(line);

    if (oldBookingId >= bookingId)
        bookingId = oldBookingId + 1;

    for (int i = 0; i < 5; i++)
        getline(bookings, line);
}

bookings.close();

      
        ifstream input("vehicles.txt");
        ofstream temp("temp.txt");

       while (getline(input, type)) {
    input >> id;
    input.ignore(1000, '\n');

    getline(input, name);

    input >> rent;
    input.ignore(1000, '\n');

    getline(input, status);

    if (id == searchId)
        status = "Booked";

    temp << type << endl << id << endl
         << name << endl << rent << endl
         << status << endl;
}

input.close();
temp.close();

        remove("vehicles.txt");
        rename("temp.txt", "vehicles.txt");

       
        ofstream out("bookings.txt", ios::app);

        out << bookingId << endl;
        out << searchId << endl;
        out << name << endl;
        out << days << endl;
        out << rent << endl;
        out << total << endl;

        out.close();

        cout << "\nBooking Successful" << endl;
        cout << "Booking ID: " << bookingId << endl;
        cout << "Vehicle Name: " << name << endl;
        cout << "Number of Days: " << days << endl;
        cout << "Total Rent: Rs. " << total << endl;
        cout << "Status: Booked" << endl;
    }
};
//MODULE 3

class RentalHistory : public Rental {
public:

   
    void showRentalHistory() {
        ifstream file("bookings.txt");

        int bookingId, vehicleId, days;
        string name;
        double rent, total;
        bool found = false;

        if (!file) {
            cout << "No Rental History Found" << endl;
            return;
        }

        cout << "\n RENTAL HISTORY \n";

        while (file >> bookingId
                    >> vehicleId
                    >> name
                    >> days
                    >> rent
                    >> total) {

            found = true;

            cout << "\n\n";
            cout << "Booking ID: " << bookingId << endl;
            cout << "Vehicle ID: " << vehicleId << endl;
            cout << "Vehicle Name: " << name << endl;
            cout << "Days Rented: " << days << endl;
            cout << "Rent Per Day: Rs. " << rent << endl;
            cout << "Total Rent: Rs. " << total << endl;
        }

        if (!found) {
            cout << "No Rental History Found" << endl;
        }

        file.close();
    }

 
    void showBookingDetails() {
        int searchBookingId;
        int bookingId, vehicleId, days;
        string name;
        double rent, total;
        bool found = false;

        cout << "Enter Booking ID: ";
        cin >> searchBookingId;

        ifstream file("bookings.txt");

        if (!file) {
            cout << "Booking File Not Found" << endl;
            return;
        }

        while (file >> bookingId
                    >> vehicleId
                    >> name
                    >> days
                    >> rent
                    >> total) {

            if (bookingId == searchBookingId) {
                cout << "\nBOOKING DETAILS\n";
                cout << "Booking ID: " << bookingId << endl;
                cout << "Vehicle ID: " << vehicleId << endl;
                cout << "Vehicle Name: " << name << endl;
                cout << "Number of Days: " << days << endl;
                cout << "Rent Per Day: Rs. " << rent << endl;
                cout << "Total Rent: Rs. " << total << endl;

                found = true;
                break;
            }
        }


        file.close();
    }

    
    void showVehicleStatus(string requiredStatus) {
        ifstream file("vehicles.txt");

        string type, name, status;
        int id;
        double rent;
        bool found = false;

        if (!file) {
            cout << "Vehicle File Not Found!" << endl;
            return;
        }

        cout << "\n " << requiredStatus<< " VEHICLES \n";

        while (getline(file, type)) {
    file >> id;
    file.ignore(1000, '\n');

    getline(file, name);

    file >> rent;
    file.ignore(1000, '\n');

    getline(file, status);

    if (status == requiredStatus) {
        cout << "\nVehicle Type: " << type << endl;
        cout << "Vehicle ID: " << id << endl;
        cout << "Vehicle Name: " << name << endl;
        cout << "Rent Per Day: Rs. " << rent << endl;
        cout << "Status: " << status << endl;

        found = true;
    }
}


file.close();
    }
};



int main() {
    int choice;

    do {
        cout << "\n VEHICLE RENTAL SYSTEM " << endl;
        cout << "1. Add Vehicle" << endl;
        cout << "2. View Vehicles" << endl;
        cout << "3. Delete Vehicle" << endl;
        cout << "4. Rent Vehicle" << endl;
        cout << "5. Rental History" << endl;
        cout << "6. Booking Details" << endl;
        cout << "7. Available Vehicles" << endl;
        cout << "8. Booked Vehicles" << endl;
        cout << "9. Exit" << endl;
      
        cout << "Enter Choice: ";

        cin >> choice;

        switch (choice) {
            case 1:
                addVehicle();
                break;

            case 2:
                viewVehicles();
                break;

            case 3:
                deleteVehicle();
                break;

            case 4: {
                Rental r;
                r.rentVehicle();
                break;
            }

           case 5: {
    RentalHistory h;
    h.showRentalHistory();
    break;
}

case 6: {
    RentalHistory h;
    h.showBookingDetails();
    break;
}

case 7: {
    RentalHistory h;
    h.showVehicleStatus("Available");
    break;
}

case 8: {
    RentalHistory h;
    h.showVehicleStatus("Booked");
    break;
}

case 9:
    cout << "Thank You!" << endl;
    break;

            default:
                cout << "Invalid Choice!" << endl;
        }

    } while (choice != 9);

    return 0;
}
