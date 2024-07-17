#include <iostream>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include <unistd.h>
#include <vector>
#include <memory>
#include <algorithm>
#include <fstream>
#include "Animal.h"
#include "Dog.h"
#include "Cat.h"
#include "User.h"
#include "Kennel.h"
#include "CoinFlip.h"

using namespace std;

time_t getCurrentTime() {
    return time(0);
}

time_t addDaysToTime(time_t startTime, int days) {
    return startTime + (days * 24 * 60 * 60); // Add days in seconds
}

string formatTime(time_t time) {
    struct tm * timeinfo = localtime(&time);
    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%d", timeinfo);
    return string(buffer);
}

void displayMenu() {
    cout << "\nKennel Booking System Menu:" << endl;
    cout << "1. Add Animal" << endl;
    cout << "2. Make Booking" << endl;
    cout << "3. List Animals" << endl;
    cout << "4. List Current Bookings" << endl;
    cout << "5. Complete Booking" << endl;
    cout << "6. Save Bookings to File" << endl;
    cout << "7. Load Bookings from File" << endl;
    cout << "8. Pay for Booking" << endl;
    cout << "9. View Cookies" << endl;
    cout << "10. Play Coin Flip Game" << endl;
    cout << "11. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    srand(time(0)); // Seed for random number generator
    Kennel kennel(10);
    User user; // Create a User instance
    int choice;
    bool running = true;

    while (running) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                string type, name, size, furColor;
                int age;
                while (true) {
                    cout << "Enter animal type (Dog/Cat): ";
                    cin >> type;
                    if (type == "Dog" || type == "Cat") {
                        break;
                    } else {
                        cout << "Invalid animal type! Please enter 'Dog' or 'Cat'." << endl;
                    }
                }
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter age: ";
                cin >> age;
                while (true) {
                    cout << "Enter size (small/medium/large): ";
                    cin >> size;
                    if (size == "small" || size == "medium" || size == "large") {
                        break;
                    } else {
                        cout << "Invalid size! Please enter 'small', 'medium', or 'large'." << endl;
                    }
                }
                cout << "Enter fur color: ";
                cin >> furColor;

                shared_ptr<Animal> animal;
                if (type == "Dog") {
                    animal = make_shared<Dog>(name, age, size, furColor);
                } else if (type == "Cat") {
                    animal = make_shared<Cat>(name, age, size, furColor);
                }

                if (kennel.checkInAnimal(animal)) {
                    cout << "Animal checked in successfully!" << endl;
                } else {
                    cout << "Kennel is full. Cannot check in animal." << endl;
                }
                break;
            }
            case 2: {
                string name;
                int days;
                cout << "Enter animal name: ";
                cin >> name;

                shared_ptr<Animal> animal = nullptr;
                for (auto& a : kennel.listAnimals()) {
                    if (a->getName() == name) {
                        animal = a;
                        break;
                    }
                }

                if (animal == nullptr) {
                    cout << "Animal not found!" << endl;
                    break;
                }

                cout << "Enter number of days: ";
                cin >> days;

                int cost = days * 1; // 1 cookie per day
                if (!user.spendCookies(cost)) {
                    cout << "Not enough cookies to make the booking." << endl;
                    break;
                }

                time_t startDate = getCurrentTime();
                time_t endDate = addDaysToTime(startDate, days);
                shared_ptr<Booking> booking = make_shared<Booking>(animal, startDate, endDate);
                kennel.addBooking(booking);
                cout << "Booking created successfully!" << endl;
                cout << animal->getName() << " will be in the kennel until " << formatTime(endDate) << "." << endl;
                cout << "Cost: " << cost << " cookies. Remaining cookies: " << user.getCookies() << endl;
                break;
            }
            case 3: {
                cout << "Animals in the kennel:" << endl;
                for (auto& animal : kennel.listAnimals()) {
                    cout << "Name: " << animal->getName()
                         << ", Type: " << animal->getSpecies()
                         << ", Age: " << animal->getAge()
                         << ", Size: " << animal->getSize()
                         << ", Fur Color: " << animal->getFurColor() << endl;
                }
                break;
            }
            case 4: {
                cout << "Current Bookings:" << endl;
                vector<shared_ptr<Booking>> currentBookings = kennel.listCurrentBookings();
                for (auto& booking : currentBookings) {
                    time_t startDate = booking->getStartDate();
                    time_t endDate = booking->getEndDate();
                    cout << "Animal: " << booking->getAnimal()->getName()
                         << ", Start Date: " << formatTime(startDate)
                         << ", End Date: " << formatTime(endDate)
                         << ", Is Paid: " << (booking->getIsPaid() ? "Yes" : "No") << endl;
                }
                break;
            }
            case 5: {
                string name;
                cout << "Enter animal name to complete booking: ";
                cin >> name;

                shared_ptr<Booking> booking = nullptr;
                for (auto& b : kennel.listCurrentBookings()) {
                    if (b->getAnimal()->getName() == name) {
                        booking = b;
                        break;
                    }
                }

                if (booking != nullptr) {
                    kennel.completeBooking(booking);
                    cout << "Booking completed successfully!" << endl;
                } else {
                    cout << "Booking not found!" << endl;
                }
                break;
            }
            case 6: {
                string filename;
                cout << "Enter filename to save bookings: ";
                cin >> filename;
                kennel.saveBookingsToFile(filename);
                cout << "Bookings saved to " << filename << endl;
                break;
            }
            case 7: {
                string filename;
                cout << "Enter filename to load bookings: ";
                cin >> filename;
                kennel.loadBookingsFromFile(filename);
                cout << "Bookings loaded from " << filename << endl;
                break;
            }
            case 8: {
                string name;
                cout << "Enter animal name to pay for booking: ";
                cin >> name;

                shared_ptr<Booking> booking = nullptr;
                for (auto& b : kennel.listCurrentBookings()) {
                    if (b->getAnimal()->getName() == name) {
                        booking = b;
                        break;
                    }
                }

                if (booking != nullptr) {
                    booking->setPaid(true);
                    cout << "Booking for " << booking->getAnimal()->getName() << " has been paid." << endl;
                } else {
                    cout << "Booking not found!" << endl;
                }
                break;
            }
            case 9: {
                cout << "You have " << user.getCookies() << " cookies." << endl;
                break;
            }
            case 10: { // New option for coin flip game
                playCoinFlipGame(user);
                break;
            }
            case 11: {
                running = false;
                cout << "Exiting the system. Goodbye!" << endl;
                break;
            }
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    }

    return 0;
}