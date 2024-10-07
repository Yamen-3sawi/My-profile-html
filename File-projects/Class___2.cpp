#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Seat {
private:
    string seatNumber;
    string passengerName;

public:
    Seat(const string& seatNum) : seatNumber(seatNum), passengerName("") {}

    const string& getSeatNumber() const {
        return seatNumber;
    }

    const string& getPassengerName() const {
        return passengerName;
    }

    void setPassengerName(const string& name) {
        passengerName = name;
    }

    bool isEmpty() const {
        return passengerName.empty();
    }

    string toString() const {
        return "Seat Number: " + seatNumber + ", Passenger Name: " + (passengerName.empty() ? "Empty" : passengerName);
    }

    bool isValid() const {

        return true;
    }
};

class Flight {
private:
    const int ROWS = 12;
    const int COLS = 4;
    Seat* seats[12][4];

public:
    Flight() {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                seats[i][j] = new Seat(to_string(i + 1) + char('A' + j));
            }
        }
    }

    ~Flight() {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                delete seats[i][j];
            }
        }
    }

    void start() {
        int choice;
        do {
            cout << "Menu:" << endl;
            cout << "1. Read passengers' file." << endl;
            cout << "2. Reserve a new empty seat." << endl;
            cout << "3. Delete a reserved seat." << endl;
            cout << "4. Delete all reserved seats." << endl;
            cout << "5. Update passengers' file." << endl;
            cout << "6. Quit." << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
            case 1:
                readPassengersFile("passengers.txt");
                break;
            case 2:
                reserveSeat();
                break;
            case 3:
                deleteReservedSeat();
                break;
            case 4:
                deleteAllReservedSeats();
                break;
            case 5:
                updatePassengersFile("passengers.txt");
                break;
            case 6:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 6);
    }

    void readPassengersFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            string seatNum, passengerName;
            while (file >> seatNum >> passengerName) {
                if (isValidSeatNumber(seatNum)) {
                    reserveSeat(seatNum, passengerName);
                }
            }
            file.close();
        }
        else {
            cout << "Unable to open file: " << filename << endl;
        }
    }

    void reserveSeat() {
        string seatNum, passengerName;
        cout << "Enter seat number to reserve: ";
        cin >> seatNum;
        cout << "Enter passenger name: ";
        cin >> passengerName;
        reserveSeat(seatNum, passengerName);
    }

    void reserveSeat(const string& seatNum, const string& passengerName) {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (seats[i][j]->getSeatNumber() == seatNum) {
                    if (seats[i][j]->isEmpty()) {
                        seats[i][j]->setPassengerName(passengerName);
                        cout << "Seat " << seatNum << " reserved for " << passengerName << endl;
                    }
                    else {
                        cout << "Seat " << seatNum << " is already reserved." << endl;
                    }
                    return;
                }
            }
        }
        cout << "Seat " << seatNum << " Empty." << endl;
    }

    void deleteReservedSeat() {
        string seatNum;
        cout << "Enter seat number to cancel reservation: ";
        cin >> seatNum;
        deleteReservedSeat(seatNum);
    }

    void deleteReservedSeat(const string& seatNum) {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (seats[i][j]->getSeatNumber() == seatNum) {
                    if (!seats[i][j]->isEmpty()) {
                        seats[i][j]->setPassengerName("");
                        cout << "Reservation for seat " << seatNum << " canceled." << endl;
                    }
                    else {
                        cout << "Seat " << seatNum << " is not reserved." << endl;
                    }
                    return;
                }
            }
        }
        cout << "Seat " << seatNum << " Empty." << endl;
    }

    void deleteAllReservedSeats() {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                seats[i][j]->setPassengerName("");
            }
        }
        cout << "All reservations canceled." << endl;
    }

    void updatePassengersFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (int i = 0; i < ROWS; ++i) {
                for (int j = 0; j < COLS; ++j) {
                    if (!seats[i][j]->isEmpty()) {
                        file << seats[i][j]->getSeatNumber() << " " << seats[i][j]->getPassengerName() << endl;
                    }
                }
            }
            file.close();
            cout << "Passengers' file updated." << endl;
        }
        else {
            cout << "Unable to open file: " << filename << endl;
        }
    }

    bool isValidSeatNumber(const string& seatNum) {


        return true;
    }
};

int main() {
    Flight flight;
    flight.start();
}


