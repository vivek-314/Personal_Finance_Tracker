# Console-Based Personal Finance Tracker in C++

A comprehensive, console-based application built with C++ to meticulously manage personal finances. This project demonstrates strong C++ fundamentals, object-oriented design, and robust data management practices.

## Description

This application provides a complete command-line interface (CLI) for tracking income and expenses. Users can add, view, edit, and delete transactions, which are persistently stored in a local `transactions.csv` file. The tracker is designed to be a reliable and user-friendly tool for gaining insight into one's financial habits, featuring financial summaries and powerful filtering capabilities. The code is organized into a clean, modular structure, separating logic into `Transaction` and `TransactionManager` classes.

## Core Features

*   **Full CRUD Functionality:**
    *   **Create:** Add new income and expense transactions with details like date, type, amount, category, and description.
    *   **Read:** View a formatted list of all recorded transactions.
    *   **Update:** Edit the details of any existing transaction by its unique ID.
    *   **Delete:** Safely remove any transaction with user confirmation.
*   **Data Persistence:** All transactions are automatically saved to `transactions.csv` upon any change or on exit, and loaded back into the application on startup, ensuring no data is ever lost between sessions.
*   **Financial Reporting:** Generate a summary report that calculates and displays total income, total expenses, and the net balance.
*   **Advanced Filtering:**
    *   Filter transactions by a specific **category**.
    *   Filter transactions by a given **date range**.
*   **Robust Error Handling:** Includes input validation to guide the user and prevent common errors.
*   **Professional Code Structure:** The project is refactored into modular components (`Transaction`, `TransactionManager`, `main`), demonstrating a strong grasp of Object-Oriented Programming (OOP) and clean code principles.

## Technology Stack

*   **Language:** C++ (C++11 or later)
*   **Core C++ Libraries:** `iostream`, `fstream`, `sstream`, `vector`, `string`, `iomanip`, `limits`, `algorithm`

## How to Compile and Run

This project is built using standard C++ and has no external dependencies. You can compile and run it using a C++ compiler like g++.

### 1. Compilation

Navigate to the project's root directory in your terminal and run the following command. This command compiles all the necessary source files and links them together into a single executable named `FinanceTracker`.

```bash
g++ main.cpp Transaction.cpp TransactionManager.cpp -o FinanceTracker