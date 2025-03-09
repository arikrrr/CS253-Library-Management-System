# Library Management System (LMS)

This is a C++ program that simulates a Library Management System (LMS) using Object-Oriented Programming (OOP) concepts. The system allows different types of users (Students, Faculty, and Librarians) to interact with the library, manage books, and track borrowing history.

## Features

- **Student and Faculty** can:
  - Borrow books.
  - Return books.
  - View their borrowing history.
  - View their current borrowing status.
  - List all books available in the library.

- **Librarian** can:
  - Add or remove books.
  - Add or remove users (Students and Faculty).
  - List all books and users in the library.

- **Data Persistence**:
  - The system saves all data (books, users, and borrowing records) to a CSV file (`library_data_output.csv`) when the program exits.
  - The system loads data from a CSV file (`library_data_input.csv`) when the program starts.

## How to Run the Program

1. **Compile the Program**:
   - Ensure you have a C++ compiler installed (e.g., `g++`).
   - Compile the program using the following command:
     ```bash
     g++ -o lms main.cpp
     ```
   - This will generate an executable file named `lms`.

2. **Prepare the Input File**:
   - The program expects an input file named `library_data_input.csv` in the same directory as the executable. This file should contain the initial data for the library (books, users, and borrowing records).
   - If the file does not exist, the program will start with an empty library.

3. **Run the Program**:
   - Run the program using the following command:
     ```bash
     ./lms
     ```
   - The program will load the data from `library_data_input.csv` and display the main menu.

## Main Menu

When the program starts, you will see the following options:

- **Student**: Log in as a student to borrow, return, or view books.
- **Faculty**: Log in as a faculty member to borrow, return, or view books.
- **Librarian**: Log in as a librarian to manage books and users.
- **Exit**: Save the data to `library_data_output.csv` and exit the program.

## Student and Faculty Login

1. **Enter your unique ID**:
   - You will be prompted to enter your unique ID. If the ID is not found, the program will return to the main menu.

2. **Enter your password**:
   - After entering a valid ID, you will be prompted to enter your password. If the password is incorrect, the program will return to the main menu.

3. **Options**:
   - Once logged in, you will see the following options:
     ```
     What would you like to do?
     1. Borrow Book
     2. Return Book
     3. View Booking History
     4. View Current Booking Status
     5. List Books in Library
     6. Log Out
     ```
   - **Borrow Book**: Borrow a book by entering the book's ID. You can only borrow up to 3 books (for students) or 5 books (for faculty) at a time.
   - **Return Book**: Return a book by entering the book's ID. If the book is overdue, you will be prompted to pay a fine. Book will be ussued to the first person in the queue who does not violates the condition, that is if it is a student he must not have a due fine or 3 bookings and if it is a faculty, it must not have a book for more than 90 days.
   - **View Booking History**: View your past borrowing history.
   - **View Current Booking Status**: View the books you currently have borrowed that includes reservations too.
   - **List Books in Library**: List all books in the library with their availability status.
   - **Log Out**: Log out and return to the main menu.

## Librarian Login

1. **Enter your unique ID**:
   - You will be prompted to enter your unique ID. If the ID is not found, the program will return to the main menu.

2. **Enter your password**:
   - After entering a valid ID, you will be prompted to enter your password. If the password is incorrect, the program will return to the main menu.

3. **Options**:
   - Once logged in, you will see the following options:
     ```
     What would you like to do?
     1. Add User
     2. Add Books
     3. List Users
     4. List Books
     5. Remove Books
     6. Remove Users
     7. Log Out
     ```
   - **Add User**: Add a new user (Student or Faculty) to the system.
   - **Add Books**: Add a new book to the library.
   - **List Users**: List all users (Students and Faculty) in the system.
   - **List Books**: List all books in the library.
   - **Remove Books**: Remove a book from the library by entering its ID. A book can be removed only when it is AVAILABLE in the Library that is it is not borrowed by anyone.
   - **Remove Users**: Remove a user from the system by entering their ID.
   - **Log Out**: Log out and return to the main menu.

## Exiting the Program

- When you choose the **Exit** option from the main menu, the program will save all data (books, users, and borrowing records) to `library_data_output.csv` and then terminate.

## Data Files

- **Input File**: `library_data_input.csv`
  - This file contains the initial data for the library (books, users, and borrowing records). The program loads this data when it starts.
  
- **Output File**: `library_data_output.csv`
  - This file is generated when the program exits. It contains the updated data (books, users, and borrowing records) after the program has run.

## Notes

- Ensure that the input file (`library_data_input.csv`) is formatted correctly. The program expects specific columns for books, users, and borrowing records.
- The program uses random IDs for books and users. These IDs are generated randomly when new books or users are added.
- The program calculates fines for overdue books based on the number of days overdue (10 rupees per day for students, no fines for faculty).
- You may change the name of output file in the code to (`library_data_input.csv`) if you want to overwrite in the input data file.
