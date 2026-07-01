// TransactionManager.cpp
#include "TransactionManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <algorithm> 

using namespace std;

// Constructor implementation
TransactionManager::TransactionManager() : nextId(1) {}

// Implementation of addTransaction
void TransactionManager::addTransaction(const std::string& date, const std::string& type, double amount, const std::string& category, const std::string& description) {
    Transaction newTransaction(nextId, date, type, amount, category, description);
    transactions.push_back(newTransaction);
    nextId++;
}

// Implementation of findTransactionById (private helper)
std::vector<Transaction>::iterator TransactionManager::findTransactionById(int id) {
    for (auto it = transactions.begin(); it != transactions.end(); ++it) {
        if (it->getID() == id) {
            return it;
        }
    }
    return transactions.end();
}

// Implementation of viewAllTransactions
void TransactionManager::viewAllTransactions() const {
    std::cout << "\n--- All Transactions ---\n";
    if (transactions.empty()) {
        std::cout << "No transactions recorded yet.\n";
    } else {
        std::cout << std::left
                  << std::setw(5) << "ID"
                  << std::setw(15) << "Date"
                  << std::setw(12) << "Type"
                  << std::setw(15) << "Amount"
                  << std::setw(20) << "Category"
                  << std::setw(30) << "Description" << std::endl;
        std::cout << std::string(97, '-') << std::endl;
        for (const auto& transaction : transactions) {
            transaction.display();
        }
    }
    std::cout << "------------------------\n";
}

// Implementation of generateSummary
void TransactionManager::generateSummary() const {
    // ... copy the full implementation of generateSummary from main.cpp ...
    // Example:
    double totalIncome = 0.0;
    double totalExpenses = 0.0;
    for (const auto& t : transactions) {
        if (t.getType() == "income") {
            totalIncome += t.getAmount();
        } else {
            totalExpenses += t.getAmount();
        }
    }
    double netBalance = totalIncome - totalExpenses;

    std::cout << "\n--- Financial Summary ---\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Total Income:   $" << totalIncome << std::endl;
    std::cout << "Total Expenses: $" << totalExpenses << std::endl;
    std::cout << "-------------------------\n";
    std::cout << "Net Balance:    $" << netBalance << std::endl;
}

// Implementation of saveToFile
void TransactionManager::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error: Could not open file for writing: " << filename << std::endl;
        return;
    }
    for (const auto& t : transactions) {
        outFile << t.getID() << ","
                << t.getDate() << ","
                << t.getType() << ","
                << t.getAmount() << ","
                << t.getCategory() << ","
                << "\"" << t.getDescription() << "\"" << std::endl; // Quoting description to handle commas
    }
}

// Implementation of loadFromFile
void TransactionManager::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        // This is not an error, the file might not exist on first run.
        return;
    }

    transactions.clear();
    std::string line;
    int maxId = 0;

    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string field;
        
        int id;
        std::string date, type, category, description;
        double amount;

        std::getline(ss, field, ',');
        id = std::stoi(field);

        std::getline(ss, date, ',');
        std::getline(ss, type, ',');
        
        std::getline(ss, field, ',');
        amount = std::stod(field);

        std::getline(ss, category, ',');

        // Handle quoted description
        std::getline(ss, description);
        if (description.front() == '"' && description.back() == '"') {
            description = description.substr(1, description.length() - 2);
        }

        transactions.emplace_back(id, date, type, amount, category, description);
        maxId = std::max(maxId, id);
    }
    nextId = maxId + 1;
}

// Implementation of deleteTransaction
void TransactionManager::deleteTransaction(const std::string& filename) {
        int idToDelete = 0;
        cout << "\nEnter the ID of the transaction to delete: ";
        cin >> idToDelete;

        // Basic input validation
        if (cin.fail()) {
            cout << "[Error] Invalid ID. Please enter a number.\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
        }

        // Use our helper to find the transaction
        auto it = findTransactionById(idToDelete);

    //     // Check if the transaction was found
        if (it != transactions.end()) {
    //         // If found, display it and ask for confirmation
            cout << "\nTransaction found:\n";
            it->display(); // Show the user what they are about to delete

            char confirmation;
            cout << "\nAre you sure you want to delete this transaction? (y/n): ";
            cin >> confirmation;

            if (confirmation == 'y' || confirmation == 'Y') {
                transactions.erase(it);

                saveToFile(filename);

                cout << "Transaction deleted successfully.\n";
            } else {
                cout << "Deletion cancelled.\n";
            }
        } else {
            cout << "Transaction with ID " << idToDelete << " not found.\n";
        }
    }

// Implementation of editTransaction
void TransactionManager::editTransaction(const std::string& filename) {
    int idToEdit = 0;
        std::cout << "\nEnter the ID of the transaction to edit: ";
        std::cin >> idToEdit;

        // Basic input validation
        if (cin.fail()) {
            cout << "[Error] Invalid ID. Please enter a number.\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
        }
        
        // Clear the rest of the line in case the user entered extra characters
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Use our helper to find the transaction. The non-const iterator 'it'
        // is the key that allows us to modify the object in place.
        auto it = findTransactionById(idToEdit);

        if (it != transactions.end()) {
            // Transaction found, display its current state
            std::cout << "\nCurrent transaction details:\n";
            it->display();

            // Present the edit sub-menu
            cout << "\nWhich field would you like to edit?\n";
            cout << "1. Date\n";
            cout << "2. Amount\n";
            cout << "3. Category\n";
            cout << "4. Description\n";
            cout << "0. Cancel\n";
            cout << "Enter your choice: ";

            int fieldChoice;
            cin >> fieldChoice;
            
            // Input validation for the choice
             if (std::cin.fail()) {
                std::cout << "[Error] Invalid choice. Please enter a number.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Use a switch to handle which field to update
            switch (fieldChoice) {
                case 1: {
                    string newDate;
                    cout << "Enter new date (YYYY-MM-DD): ";
                    getline(std::cin, newDate);
                    it->setDate(newDate);
                    break;
                }
                case 2: {
                    double newAmount;
                    cout << "Enter new amount: ";
                    cin >> newAmount;
                    if (cin.fail()) {
                         cout << "[Error] Invalid amount. Edit cancel\n";
                         cin.clear();
                         cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                         return; // Exit on bad input
                    }
                    it->setAmount(newAmount);
                    break;
                }
                case 3: {
                    string newCategory;
                    cout << "Enter new category: ";
                    getline(std::cin, newCategory);
                    it->setCategory(newCategory);
                    break;
                }
                case 4: {
                    string newDescription;
                    cout << "Enter new description: ";
                    getline(std::cin, newDescription);
                    it->setDescription(newDescription);
                    break;
                }
                case 0:
                    cout << "Edit cancelled.\n";
                    return; // Exit without saving

                default:
                    cout << "Invalid field choice. Edit cancelled.\n";
                    return; // Exit without saving
            }

            // If we're here, an edit was made. Save immediately.
            saveToFile(filename);
            cout << "Transaction updated successfully in memory\n";

        } else {
            cout << "Transaction with ID " << idToEdit << " not found.\n";
        }
}

// Implementation of viewByCategory
void TransactionManager::viewByCategory(const std::string& category) const {
    cout << "\n--- Transactions in Category: " << category << " ---\n";
        bool foundOne= false;

        for (const auto& transaction : transactions){
            if(transaction.getCategory()== category){
                transaction.display();
                foundOne = true;
            }
        }

        if(!foundOne){
            cout << " No transaction found for the category.\n";
        }

        cout << "--------------------------------------------------\n";
}

// Implementation of viewByDateRange
void TransactionManager::viewByDateRange(const std::string& startDate, const std::string& endDate) const {
    cout << "\n--- Transactions from " << startDate << " to " << endDate << " ---\n";
        bool foundOne = false;
         for (const auto& transaction : transactions){
            if(transaction.getDate()>= startDate && transaction.getDate()<= endDate){
                transaction.display();
                foundOne = true;
            }
         }

         if(!foundOne){
            cout<< "No transactions found in this date range\n";
         }

         cout << "-----------------------------------------------\n";
}