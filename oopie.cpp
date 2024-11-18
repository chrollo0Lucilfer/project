#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

class Booking
{
protected:
    string name;
    int seatNo;

public:
    Booking(string _name, int _seatNo) : name(_name), seatNo(_seatNo) {}

    virtual void printTicket() const
    {
        cout << "\n"
             << "=====================================" << endl;
        cout << "|          AAPLI BUS TICKET          |\n";
        cout << "=====================================" << endl;
        cout << "| Passenger Name: " << left << name << "|\n";
        cout << "| Seat Number:    " << left << seatNo << "|\n";
    }

    int getSeatNo() const { return seatNo; }
    void setName(const string &newName) { name = newName; }
    string getName() const { return name; }
    virtual string getType() const = 0;
    virtual string getAdditionalInfo() const { return ""; }
    virtual ~Booking() = default;
};

class StandardBooking : public Booking
{
public:
    StandardBooking(string _name, int _seatNo) : Booking(_name, _seatNo) {}

    void printTicket() const override
    {
        Booking::printTicket();
        cout << "| Ticket Type:    " << left << setw(20) << "Standard" << "|\n";
        cout << string(36, '=') << "\n";
    }

    string getType() const override { return "standard"; }
};

class VIPBooking : public Booking
{
private:
    string additionalPerks;

public:
    VIPBooking(string _name, int _seatNo, string perks)
        : Booking(_name, _seatNo), additionalPerks(perks) {}

    void printTicket() const override
    {
        Booking::printTicket();
        cout << "| Ticket Type:    " << left << setw(20) << "VIP" << "|\n";
        cout << "| Perks:          " << left << setw(20) << additionalPerks << "|\n";
        cout << string(36, '=') << "\n";
    }

    string getType() const override { return "vip"; }
    string getAdditionalInfo() const override { return additionalPerks; }
};

class BusBookingSystem
{
private:
    vector<Booking *> bookings;
    const string filename = "bookings.txt";

    void saveToFile()
    {
        ofstream outFile(filename, ios::trunc); // Overwrite file each time
        if (!outFile)
        {
            cerr << "Error saving to file.\n";
            return;
        }
        for (const auto &booking : bookings)
        {
            outFile << booking->getType() << " " << booking->getName() << " " << booking->getSeatNo();
            if (booking->getType() == "vip")
            {
                outFile << " " << booking->getAdditionalInfo();
            }
            outFile << endl;
        }
        outFile.close();
    }

    void loadFromFile()
    {
        ifstream inFile(filename);
        if (!inFile)
        {
            cerr << "Error loading from file.\n";
            return;
        }

        string type, name, perks;
        int seatNo;
        while (inFile >> type >> name >> seatNo)
        {
            if (type == "standard")
            {
                bookings.push_back(new StandardBooking(name, seatNo));
            }
            else if (type == "vip")
            {
                inFile.ignore(); // Ignore whitespace before perks
                getline(inFile, perks);
                bookings.push_back(new VIPBooking(name, seatNo, perks));
            }
        }
        inFile.close();
    }

    bool isSeatAvailable(int seatNo) const
    {
        for (const auto &booking : bookings)
        {
            if (booking->getSeatNo() == seatNo)
            {
                return false;
            }
        }
        return true;
    }

public:
    BusBookingSystem() { loadFromFile(); }

    ~BusBookingSystem()
    {
        for (auto booking : bookings)
        {
            delete booking;
        }
    }

    void bookSeat()
    {
        string name, bookingType;
        int seatNo;
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter seat number: ";
        cin >> seatNo;

        if (!isSeatAvailable(seatNo))
        {
            cout << "Seat number " << seatNo << " is already booked. Please choose a different seat.\n";
            return;
        }

        cout << "Enter booking type (standard/vip): ";
        cin >> bookingType;

        if (bookingType == "standard")
        {
            bookings.push_back(new StandardBooking(name, seatNo));
            cout << "Standard seat booked successfully.\n";
        }
        else if (bookingType == "vip")
        {
            string perks;
            cout << "Enter additional perks: ";
            cin.ignore();
            getline(cin, perks);
            bookings.push_back(new VIPBooking(name, seatNo, perks));
            cout << "VIP seat booked successfully.\n";
        }
        else
        {
            cout << "Invalid booking type.\n";
            return;
        }

        saveToFile();
    }

    void viewReservations() const
    {
        if (bookings.empty())
        {
            cout << "No reservations made yet.\n";
            return;
        }

        cout << "All reservations:\n";
        cout << "Seat No.\tType\n";
        for (const auto &booking : bookings)
        {
            cout << booking->getSeatNo() << "\t\t" << booking->getType() << endl;
        }
    }

    void editReservation()
    {
        int seatToEdit;
        cout << "Enter seat number to edit: ";
        cin >> seatToEdit;

        bool found = false;
        for (auto &booking : bookings)
        {
            if (booking->getSeatNo() == seatToEdit)
            {
                string newName;
                cout << "Enter new name: ";
                cin >> newName;
                booking->setName(newName);
                cout << "Reservation edited successfully.\n";
                found = true;
                saveToFile();
                break;
            }
        }

        if (!found)
        {
            cout << "Reservation not found.\n";
        }
    }

    void printTicket() const
    {
        int seatToPrint;
        cout << "Enter seat number to print ticket: ";
        cin >> seatToPrint;

        bool found = false;
        for (const auto &booking : bookings)
        {
            if (booking->getSeatNo() == seatToPrint)
            {
                booking->printTicket();
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "Reservation not found.\n";
        }
    }
};

int main()
{
    BusBookingSystem system;
    int choice;

    do
    {
        cout << "\nMini Bus Booking System\n";
        cout << "1. Book a seat\n";
        cout << "2. View reservations\n";
        cout << "3. Edit a reservation\n";
        cout << "4. Print a ticket\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            system.bookSeat();
            break;
        case 2:
            system.viewReservations();
            break;
        case 3:
            system.editReservation();
            break;
        case 4:
            system.printTicket();
            break;
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 5);

    return 0;
}
