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

## Development Environment

- **Compiler**: GCC 14.2.0
- **C++ Standard**: C++23
- **System**: Windows

Ensure you have the required environment to run the program without errors.

Other versions might throw errors so use these versions only.

## How to Run the Program

1. **Comment and Uncomment some lines**
   - If you are on Unix-like systems(Linux, macOS) comment line 2 `#include <process.h>`.
   - If you are on Windows comment line 3 `#include <unistd.h>`.
2. **Compile the Program**:
   - Compile the code using the following command:
     ```bash
     g++ -o lms lms.cpp
     ```
   - This will generate an executable file named `lms`.
   - An executable file is already provided, you may use that too.

3. **Prepare the Input File**:
   - The program expects an input file named `library_data_input.csv` in the same directory as the executable. This file should contain the initial data for the library (books, users, and borrowing records).
   - If the file does not exist, the program will start with an empty library.

4. **Run the Program**:
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

- Please take a look at `library_data_input.csv` to get the Users' and Librarian's login infos.
- The info is in the format:
  ```
  [UserID], [Name], [Password], [UserType]
  ```
- I have considered that we have only one librarian already specified in the library_data_input.csv and we cannot add or remove a librarian.
- Ensure that the input file (`library_data_input.csv`) is formatted correctly. The program expects specific columns for books, users, and borrowing records. You can take a look at the `library_data_input.csv` to get the idea of how csv file is getting saved.
```
[Books]
B1001,The Great Gatsby,F. Scott Fitzgerald,Scribner,1925,9780743273565,AVAILABLE
B1002,To Kill a Mockingbird,Harper Lee,J.B. Lippincott & Co.,1960,9780061120084,AVAILABLE
[Users]
S1,Alice,pass,Student
F1,Dr. Smith,faculty1pass,Faculty
L1,Arihant,abcxyz,Librarian
[CurrentBookings]
S1,B1001,0UEG3BRMZM,09-03-2025,xxxxxxxx,INSTANT,0
[HistoryBookings]
S1,B1002,OKJH7897HG,09-03-2025,15-03-2025,INSTANT,0
```
- The program uses random IDs for books and users. These IDs are generated randomly when new books or users are added.

- The program calculates fines for overdue books based on the number of days overdue (10 rupees per day for students, no fines for faculty).

- You may change the name of output file in the code to (`library_data_input.csv`) if you want to overwrite in the input data file.