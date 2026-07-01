// TransactionManager.h

#ifndef TRANSACTION_MANAGER_H
#define TRANSACTION_MANAGER_H

#include <vector>
#include <string>
#include "Transaction.h" 

/**
 * @class TransactionManager
 * @brief Manages a collection of Transaction objects.
 *
 * This class is the core engine of the finance tracker. It handles all
 * business logic, including adding, editing, deleting, and viewing transactions.
 * It is also responsible for file persistence (saving to and loading from a CSV file).
 */
class TransactionManager {
private:
    std::vector<Transaction> transactions;
    int nextId;

    /**
     * @brief A private helper method to find a transaction by its ID.
     * @param id The ID of the transaction to find.
     * @return An iterator to the found transaction, or transactions.end() if not found.
     */
    std::vector<Transaction>::iterator findTransactionById(int id);

public:
    /**
     * @brief Constructs a TransactionManager, initializing the next available ID.
     */
    TransactionManager();

    // --- Core Data Manipulation Methods ---
    void addTransaction(const std::string& date, const std::string& type, double amount, const std::string& category, const std::string& description);
    void deleteTransaction(const std::string& filename);
    void editTransaction(const std::string& filename);

    // --- View and Report Methods ---
    void viewAllTransactions() const;
    void generateSummary() const;
    void viewByCategory(const std::string& category) const;
    void viewByDateRange(const std::string& startDate, const std::string& endDate) const;

    // --- File Persistence Methods ---
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif // TRANSACTION_MANAGER_H