// Transaction.h

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

/**
 * @class Transaction
 * @brief Represents a single financial transaction (either income or expense).
 *
 * This class encapsulates all the properties of a transaction, such as its ID,
 * date, type, amount, category, and a description. It provides methods to
 * access and modify these properties, as well as a method to display the
 * transaction's details.
 */
class Transaction {
private:
    int id;
    std::string date;
    std::string type; // "income" or "expense"
    double amount;
    std::string category;
    std::string description;

public:
    /**
     * @brief Constructs a new Transaction object.
     * @param id The unique identifier for the transaction.
     * @param date The date of the transaction (in YYYY-MM-DD format).
     * @param type The type of transaction ("income" or "expense").
     * @param amount The monetary value of the transaction.
     * @param category A user-defined category for the transaction (e.g., "Groceries").
     * @param description A brief description of the transaction.
     */
    Transaction(int id, const std::string& date, const std::string& type, double amount, const std::string& category, const std::string& description);

    // --- Getters (Accessors) ---
    // These methods provide read-only access to the private member variables.
    
    int getID() const;
    std::string getDate() const;
    std::string getType() const;
    double getAmount() const;
    std::string getCategory() const;
    std::string getDescription() const;
    
    // --- Setters (Mutators) ---
    // These methods allow for the modification of private member variables.

    void setDate(const std::string& newDate);
    void setAmount(double newAmount);
    void setCategory(const std::string& newCategory);
    void setDescription(const std::string& newDescription);

    /**
     * @brief Displays the details of the transaction to the console.
     * @details Formats and prints all member variables in a single, readable line.
     */
    void display() const;
};

#endif // TRANSACTION_H