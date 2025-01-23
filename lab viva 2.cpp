#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function prototypes
void displayWelcomeMessage();
void displayCars(string cars[], double rates[], int size);
void saveUserData(const string &username, const string &email);
void collectFeedback();
void adminPanel();
void userPanel();
void displayUsers();
void displayFeedback();
void addCar(string cars[], double rates[], int &size);
void removeCar(string cars[], double rates[], int &size);
void handleInsurance(double &totalCost, int rentalDays);
// welcome message
void displayWelcomeMessage() {
    cout << "\n************\n";
    cout << " Welcome to the Car Rental System \n";
    cout << "**********\n\n";
}
//available cars
void displayCars(string cars[], double rates[], int size) {
    cout << "\nAvailable Cars for Rent:\n";
    cout << "--------------------------------\n";
    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". " << cars[i] << " - $" << rates[i] << " per day" << endl;
    }
    cout << "--------------------------------\n";
}
//save user data in file(filehandling)
void saveUserData(const string &username, const string &email) {
    ofstream file("users.csv", ios::app);

    if (file.is_open()) {
        file << username << "," << email << "\n";
        file.close();
        cout << "User data saved successfully.\n";
    } else {
        cout << "Error: Unable to save user data. Please check file permissions or directory.\n";
    }
}
//take feedback from user
void collectFeedback() {
    string feedback;
    ofstream feedbackFile("feedback.txt", ios::app);

    cout << "\nWe value your feedback! Please enter your comments about our service: \n";
    cin.ignore();
    getline(cin, feedback);

    if (feedbackFile.is_open()) {
        feedbackFile << feedback << "\n";
        feedbackFile.close();
        cout << "Thank you for your feedback!\n";
    } else {
        cout << "Error: Unable to save feedback.\n";
    }
}
//user panel
void displayUsers() {
    ifstream file("users.csv");
    string line;

    cout << "\nRegistered Users:\n";
    cout << "--------------------------------\n";

    if (file.is_open()) {
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Error: Unable to read user data. Please check if the file exists or is accessible.\n";
    }
    cout << "--------------------------------\n";
}
//display feedback
void displayFeedback() {
    ifstream feedbackFile("feedback.txt");
    string line;

    cout << "\nUser Feedback:\n";
    cout << "--------------------------------\n";

    if (feedbackFile.is_open()) {
        while (getline(feedbackFile, line)) {
            cout << line << endl;
        }
        feedbackFile.close();
    } else {
        cout << "Error: Unable to read feedback.\n";
    }
    cout << "--------------------------------\n";
}
//add new car
void addCar(string cars[], double rates[], int &size) {
    if (size >= 100) {
        cout << "Cannot add more cars. Maximum limit reached.\n";
        return;
    }

    string carName;
    double rate;

    cout << "Enter the name of the car: ";
    cin.ignore();
    getline(cin, carName);

    cout << "Enter the rental rate: ";
    cin >> rate;

    cars[size] = carName;
    rates[size] = rate;
    size++;

    cout << "Car added successfully!\n";
}
//remove previous car
void removeCar(string cars[], double rates[], int &size) {
    int carIndex;

    displayCars(cars, rates, size);
    cout << "\nEnter the number corresponding to the car you want to remove: ";
    cin >> carIndex;

    if (cin.fail() || carIndex < 1 || carIndex > size) {
        cout << "Invalid input.\n";
        return;
    }

    for (int i = carIndex - 1; i < size - 1; i++) {
        cars[i] = cars[i + 1];
        rates[i] = rates[i + 1];
    }

    size--;
    cout << "Car removed successfully!\n";
}
//insurance policy
void handleInsurance(double &totalCost, int rentalDays) {
    char addInsurance;
    double insuranceRate = 15.0;

    cout << "\nWould you like to add insurance for $15 per day? (y/n): ";
    cin >> addInsurance;

    if (addInsurance == 'y' || addInsurance == 'Y') {
        totalCost += insuranceRate * rentalDays;
        cout << "Insurance has been added to your total cost.\n";
    } else {
        cout << "No insurance added.\n";
    }
}
//admin portal
void adminPanel() {
    string cars[100] = {"Toyota Corolla", "Honda Civic", "Suzuki Alto", "Fortuner", "Ferrari"};
    double rates[100] = {30.0, 35.0, 50.0, 60.0, 70.0};
    int carCount = 5;

    int choice;

    do {
        cout << "\nAdmin Panel:\n";
        cout << "1. View Users\n";
        cout << "2. View Feedback\n";
        cout << "3. Add Car\n";
        cout << "4. Remove Car\n";
        cout << "5. Exit Admin Panel\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayUsers();
                break;
            case 2:
                displayFeedback();
                break;
            case 3:
                addCar(cars, rates, carCount);
                break;
            case 4:
                removeCar(cars, rates, carCount);
                break;
            case 5:
                cout << "Exiting Admin Panel...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
}
//user portal
void userPanel() {
    string username, email;
    string cars[] = {"Toyota Corolla", "Honda Civic", "Suzuki Alto", "Fortuner", "Ferrari"};
    double rates[] = {30.0, 35.0, 50.0, 60.0, 70.0};
    int carCount = sizeof(rates) / sizeof(rates[0]);

    cout << "Please log in:\n";
    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, username);
    cout << "Enter your email: ";
    getline(cin, email);

    saveUserData(username, email);

    displayCars(cars, rates, carCount);

    int selectedCarIndex;
    cout << "\nEnter the number corresponding to the car you want to rent: ";
    cin >> selectedCarIndex;

    if (cin.fail() || selectedCarIndex < 1 || selectedCarIndex > carCount) {
        cout << "Invalid input.\n";
        return;
    }
//rent days user wants
    int rentalDays;
    cout << "Enter the number of days you want to rent the car: ";
    cin >> rentalDays;

    if (cin.fail() || rentalDays <= 0) {
        cout << "Invalid input.\n";
        return;
    }

    double totalCost = rates[selectedCarIndex - 1] * rentalDays;

    handleInsurance(totalCost, rentalDays);

    cout << "\nYour total cost is: $" << totalCost << endl;

    collectFeedback();
}

int main() {
    int role;

    displayWelcomeMessage();

    cout << "Select your role:\n";
    cout << "1. User\n";
    cout << "2. Admin\n";
    cout << "Enter your choice: ";
    cin >> role;

    if (role == 1) {
        userPanel();
    } else if (role == 2) {
        adminPanel();
    } else {
        cout << "Invalid role selected. Exiting program.\n";
    }

    return 0;
}