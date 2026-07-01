#include "transaction.h"
#include <iostream>
#include <iomanip>


Transaction::Transaction(int id, const std::string& date, const std::string& type, double amount, const std::string& category, const std::string& description)
    : id(id), date(date), type(type), amount(amount), category(category), description(description) {
}

// Implementation of the getID getter method.
// 'const' here must match the declaration in the .h file.
int Transaction::getID() const {
    return id;
}

// Implementation of the getDate getter method.
std::string Transaction::getDate() const {
    return date;
}

// Implementation of the getType getter method.
std::string Transaction::getType() const {
    return type;
}

// Implementation of the getAmount getter method.
double Transaction::getAmount() const {
    return amount;
}

// Implementation of the getCategory getter method.
std::string Transaction::getCategory() const {
    return category;
}

// Implementation of the getDescription getter method.
std::string Transaction::getDescription() const {
    return description;
}

// Implementation of the setDate setter method.
void Transaction::setDate(const std::string& newDate) {
    date = newDate;
}

// Implementation of the setAmount setter method.
void Transaction::setAmount(double newAmount) {
    amount = newAmount;
}

// Implementation of the setCategory setter method.
void Transaction::setCategory(const std::string& newCategory) {
    category = newCategory;
}

// Implementation of the setDescription setter method.
void Transaction::setDescription(const std::string& newDescription) {
    description = newDescription;
}

// Implementation of the display method.
void Transaction::display() const {
    std::cout << std::left
              << std::setw(5) << id
              << std::setw(15) << date
              << std::setw(12) << type
              << std::setw(15) << std::fixed << std::setprecision(2) << amount
              << std::setw(20) << category
              << std::setw(30) << description << std::endl;
}