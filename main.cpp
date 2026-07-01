#include <iostream>
#include <string>
#include <iomanip>
#include <vector> 
#include <limits>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include "transactionManager.h"
using namespace std;

// A global constant for the filename makes it easy to change if needed.
const string FILENAME = " transactions.csv";



// Function to display the main menu to the user.
void displayMenu() {
    cout << "\n===== Personal Finance Tracker =====\n";
    cout << "1. Add Transaction\n";
    cout << "2. View All Transactions\n";
    cout << "3.Generate Financial Summary\n";
    cout << "4. Edit Transaction\n";
    cout << "5. Delete Transaction\n";
    cout << "6. Filter by Category\n";
    cout << "7. Filter by Data Range\n";
    cout << "8. Exit\n";
    cout << "====================================\n";
    cout << "Enter your choice: ";
}

/**
 * @brief The main entry point of the application.
 *
 * This function contains the main application loop. It initializes the
 * TransactionManager, handles user input, and calls the appropriate
 * manager methods based on the user's choice.
 */


int main() {
    TransactionManager manager;

    manager.loadFromFile(FILENAME);
    int choice =0;

    while(true){
        displayMenu();
        cin >> choice;

        if (cin.fail()) {
            cout << "\n[Error] Invalid input. Please enter a number corresponding to a menu option.\n";
            
            // 1. Clear the error flag on std::cin so we can use it again.
            cin.clear();
            
            // 2. Discard the rest of the line from the input buffer.
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            continue; 
        }

        switch (choice) {
            case 1: { 
                string date, type, category, description;
                double amount;

                // Prompt the user for each detail and read the input.
                cout << "Enter date (YYYY-MM-DD): ";
                cin >> date;

                cout << "Enter type (income/expense): ";
                cin >> type;

                cout << "Enter amount: ";
                cin >> amount;

                cout << "Enter category: ";
                cin >> category;

                cout << "Enter description: ";
                // This is the CRUCIAL step to handle the newline character left by `std::cin >> amount;`
                // `std::cin.ignore()` discards the leftover newline from the input buffer.
                std::cin.ignore(); 
                // `std::getline` reads the entire line of text, including spaces, into the description.
                std::getline(std::cin, description);

                // With all the data collected, call the manager to do its job.
                manager.addTransaction(date, type, amount, category, description);

                // Provide feedback to the user.
                cout << "\nTransaction added successfully!\n";
                break;
            }
            

            case 2:
                // Placeholder for "View All Transactions"
                manager.viewAllTransactions();
                break;

            case 3:

                manager.generateSummary();
                break;

            case 4: 
                manager.editTransaction(FILENAME);                
                break;
            
            case 5:
                manager.deleteTransaction(FILENAME);
                break;

            case 6:{
                cout << "Enter category to filter by:";

                // IMPORTANT: Clear the input buffer. The previous `std::cin >> choice;`
                // left a newline character ('\n') in the buffer. We must discard it
                // before we can use std::getline successfully.

                cin.ignore(numeric_limits<streamsize>:: max(),'\n');
                string category;
                getline(cin,category);
                manager.viewByCategory(category);
                break;
            }
            
            case 7: {
                cout << "Enter start date (YYYY-MM-DD): ";
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

                std::string startDate;
                std::getline(std::cin, startDate);

                // Prompt for the end date. No need for another cin.ignore() here,
                // as the previous input was handled by getline.
                cout << "Enter end date (YYYY-MM-DD): ";
                string endDate;
                getline(std::cin, endDate);

                // Call the corresponding method in TransactionManager with the two dates.
                manager.viewByDateRange(startDate, endDate);
                break;
            }

            case 8:
                
                manager.saveToFile(FILENAME);
            
                cout << "\nThank you for using the Personal Finance Tracker. Goodbye!\n";
                
                return 0;
   
            default:
                cout << "\nInvalid choice. Please select an option from the menu.\n";
                break;
        }
    }

    return 0;
}