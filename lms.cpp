#include <bits/stdc++.h>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Enum Definitions

// Enum to define the type of user (STUDENT, FACULTY, LIBRARIAN)
enum class UserType {STUDENT, FACULTY, LIBRARIAN};

// Enum to define the status of a book (AVAILABLE, BORROWED, RESERVED)
enum class BookStatus { AVAILABLE, BORROWED, RESERVED };

// Enum to define the type of booking (INSTANT, RESERVATION)
enum class BookingType {INSTANT, RESERVATION};

// Overloaded operator<< for BookStatus to print the status of a book
ostream& operator<<(ostream& os, const BookStatus& status) {
    switch (status) {
        case BookStatus::AVAILABLE: os << "AVAILABLE"; break;
        case BookStatus::BORROWED: os << "BORROWED"; break;
        case BookStatus::RESERVED: os << "RESERVED"; break;
    }
    return os;
}

// Overloaded operator<< for BookingType to print the type of booking
ostream& operator<<(ostream& os, const BookingType& status) {
    switch (status) {
        case BookingType::INSTANT: os << "INSTANT"; break;
        case BookingType::RESERVATION: os << "RESERVATION"; break;
    }
    return os;
}

// Overloaded operator<< for UserType to print the type of user
ostream& operator<<(ostream& os, const UserType& status) {
    switch (status) {
        case UserType::STUDENT: os << "STUDENT"; break;
        case UserType::FACULTY: os << "FACULTY"; break;
        case UserType::LIBRARIAN: os << "LIBRARIAN"; break;
    }
    return os;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BookBase Class

// Base class for Book, containing basic book details
class BookBase{
    public:
        string ID, title, author, publisher, ISBN;
        int year;

        // Constructor for BookBase
        BookBase(string title, string author, string publisher, int year, string ID, string ISBN){
            this->ID = ID;
            this->title = title;
            this->author = author;
            this->publisher = publisher;
            this->year = year;
            this->ISBN = ISBN;
        }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Book Class

// Derived class from BookBase, containing additional details like status and reservation queue
class Book:public BookBase{
    public:
        BookStatus status;
        queue<string> reservationQueue; // Queue to hold IDs of users who have reserved the book

        // Function to remove a user from the reservation queue
        void removeFromQ(string ID);

        // Constructor for Book class
        Book(string title, string author, string publisher, int year, string ID, string ISBN, BookStatus status = BookStatus::AVAILABLE, queue<string> reservationQueue = queue<string>())
            : BookBase(title, author, publisher, year, ID, ISBN){
            this->status = status;
            this->reservationQueue = reservationQueue;
        }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Booking Class

// Class to hold details of all bookings, including book details, booking ID, dates, and type
class Booking: public BookBase{
    public:
        string bookingID, bookingDate, returnDate;
        int fine;
        BookingType bookingType;

        // Function to print booking details
        void print(string currentDate, UserType type);
        
        // Function to calculate fine
        int giveFine(string date);
        
        // Function to calculate the number of days since booking
        int giveDays(string date);

        // Constructor for Booking class
        Booking(string title, string author, string publisher, int year, string ID, string ISBN,
            string bookingID = "xxxxxxxx", string bookingDate = "xxxxxxxx", string returnDate = "xxxxxxxx",
            BookingType type = BookingType::INSTANT, int fine = 0)
            : BookBase(title, author, publisher, year, ID, ISBN),
                bookingID(bookingID), bookingDate(bookingDate), returnDate(returnDate),
                bookingType(type), fine(fine) {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Account Class

// Class to hold current and historical bookings for a user
class Account{
    public:
        set<string> currentID; // Set of current booking IDs
        map<string, Booking*> current; // Map of current bookings

        set<string> historyID; // Set of historical booking IDs
        map<string, Booking*> history; // Map of historical bookings

        // Constructor for Account
        Account(){
            this->currentID = set<string>();
            this->current = map<string, Booking*>();
            this->historyID = set<string>();
            this->history = map<string, Booking*>();
        }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// User Class

// Base class for all users (Student, Faculty, Librarian)
class User{
    string password;
    public:
        string name, ID;
        Account account;
    
        // Function to get the password
        string getpass(){
            return this->password;
        }
        
        // Pure virtual functions to be implemented by derived classes
        virtual void borrowBook(string date) = 0;
        virtual void returnBook(string date) = 0;
        virtual bool canBorrow(string date) = 0;
        
        // Function to view booking history
        void viewHistory(string date, UserType type);
        
        // Function to view current bookings
        void viewCurrent(string date, UserType type);        
         
        // Function to authenticate the user
        bool authenticate(string pass){
            return pass == (this->password);
        }
        
        // Function to list all books in the library
        void listBooks();
        
        // Function to calculate total fine
        int fineBatao(string returnDate);
        
        // Function to remove a book from current bookings
        void removeFromCurrent(string bookID);
        
        // Constructor for User
        User(string name, string ID, string password){
            this->name = name;
            this->ID = ID;
            this->password = password;
            this->account = Account();
        }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Student Class

// Derived class from User, representing a student
class Student: public User{
    public:
    void borrowBook(string date);
    void returnBook(string date);
    bool payFine(string date, string bookingID);
    bool canBorrow(string date);
    
    // Constructor for Student
    Student(string name, string ID, string password) : User(name, ID, password){}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Faculty Class

// Derived class from User, representing a faculty member
class Faculty: public User{
    public:
    bool restrict(string date);
    void borrowBook(string date);
    void returnBook(string date);
    bool canBorrow(string date);
    
    // Constructor for Faculty
    Faculty(string name, string ID, string password): User(name, ID, password){}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Librarian Class

// Derived class from User, representing a librarian
class Librarian: public User{
    public:
        void borrowBook(string date);
        void returnBook(string date);
        bool canBorrow(string date);
        void addUser();
        void addBook();
        void listUsers();
        void removeBooks();
        void removeUsers();
        
        // Constructor for Librarian
        Librarian(string name, string ID, string password): User(name, ID, password){}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Library Class

// Class to hold all information about the library, including books, users, and librarians
class Library{
    public:
        set<string> bookID; // Set of book IDs
        set<string> studentID; // Set of student IDs
        set<string> facultyID; // Set of faculty IDs
        set<string> librarianID; // Set of librarian IDs

        map<string, Book*> books; // Map of books
        map<string, Student*> students; // Map of students
        map<string, Faculty*> faculties; // Map of faculties
        map<string, Librarian*> librarians; // Map of librarians

        map<string, UserType> userType; // Map to store user types

    // Constructor for Library
    Library(){
        this->bookID = set<string>();
        this->studentID = set<string>();
        this->facultyID = set<string>();
        this->librarianID = set<string>();
        this->books = map<string, Book*>();
        this->students = map<string, Student*>();
        this->faculties = map<string, Faculty*>();
        this->librarians = map<string, Librarian*>();
        this->userType = map<string, UserType>();
    }
};

// Global Library object to store all library data
Library library;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Utility Functions

// Function to generate a random string of given length
std::string gen_random(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return tmp_s;
}

// Function to convert string date to time_t
time_t stringToTimeT(const string& date) {
    tm timeStruct = {};
    istringstream ss(date);
    ss >> timeStruct.tm_mday;
    ss.ignore(); // Ignore 'delimiter'
    ss >> timeStruct.tm_mon;
    ss.ignore(); // Ignore 'delimiter'
    ss >> timeStruct.tm_year;
    
    timeStruct.tm_mon -= 1;   // Months are 0-based in tm
    timeStruct.tm_year -= 1900; // Year since 1900

    return mktime(&timeStruct); // Convert to time_t
}

// Function to calculate the difference in days between two dates
int giveDaysDiff(const string& borrowDate, const string& returnDate){
    time_t t1 = stringToTimeT(borrowDate);
    time_t t2 = stringToTimeT(returnDate);
    
    if (t1 == -1 || t2 == -1) {
        cerr << "Error in date conversion!" << endl;
        return 0;
    }
    double diff = difftime(t2, t1) / (60 * 60 * 24);
    return (int)diff;
}

// Function to calculate fine based on the number of days overdue
int calculateFine(const string& borrowDate, const string& returnDate) {
    int diff = giveDaysDiff(borrowDate, returnDate); // Difference in days
    if (diff > 15) {
        return static_cast<int>((diff - 15) * 10);
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Book Class Function Implementations

// Function to remove a user from the reservation queue
void Book::removeFromQ(string ID) {
    queue<string> tempQueue;
    bool found = false;
    while (!reservationQueue.empty()) {
        string currentID = reservationQueue.front();
        reservationQueue.pop();
        if (currentID == ID) {
            found = true;
        } else {
            tempQueue.push(currentID);
        }
    }
    if (found) {
        reservationQueue = tempQueue;
    } else {
        cout << "User ID " << ID << " not found in the reservation queue." << endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Booking Class Function Implementations

// Function to print booking details
void Booking::print(string currentDate, UserType type){
    cout << "Booking ID : " << this->bookingID << endl;
    cout << "Book ID : " << this->ID << endl;
    cout << "Title : " << this->title << endl;
    cout << "Booking Date : " << this->bookingDate << endl;
    cout << "Return Date : " << this->returnDate << endl;  
    cout << "Booking Type : " << this->bookingType << endl;
    cout << "Days : " << this->giveDays(currentDate) << endl;
    if(type == UserType::STUDENT)
        cout << "Fine : " << this->giveFine(currentDate) << endl;
}

// Function to calculate fine
int Booking::giveFine(string date){
    if(this->bookingType == BookingType::RESERVATION) return 0;

    int currfine = 0;
    if(this->returnDate == "xxxxxxxx"){
        currfine = calculateFine(this->bookingDate, date);
    }else{
        currfine = calculateFine(this->bookingDate, this->returnDate);
    }
    return currfine;
}

// Function to calculate the number of days since booking
int Booking::giveDays(string date){
    int days;
    if(this->returnDate == "xxxxxxxx")
        days = giveDaysDiff(this->bookingDate, date);
    else
        days = giveDaysDiff(this->bookingDate, this->returnDate);
    return days;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// User Class Function Implementations

// Function to view booking history
void User::viewHistory(string date, UserType type){
    cout << "----------------------------------------" << endl;

    if(this->account.history.empty()){
        cout << "No History Found" << endl;
        cout << "Returning......" << endl;
        return;
    }

    cout << "Showing History" << endl;
    int i = 1;

    for(auto j: this->account.history){
        Booking top = *j.second;
        cout << i << ' ';
        top.print(date, type);
        i++;
    }
}

// Function to view current bookings
void User::viewCurrent(string date, UserType type){
    cout << "----------------------------------------" << endl;

    if(this->account.current.empty()){
        cout << "No Current Records Found" << endl;
        cout << "Returning......" << endl;
        return;
    }

    cout << "Showing Current Booking Status" << endl;
    int i = 1;

    for(auto j: this->account.current){
        Booking top = *j.second;
        cout << i << ' ';
        top.print(date, type);
        i++;
    }
}

// Function to list all books in the library
void User::listBooks(){
    cout << "----------------------------------------" << endl;
    
    cout << "Listing Books in Library" << endl;
    int i = 1;
    for(auto j: library.books){
        Book kitaab = *(j.second);
        cout << i;
        cout << ". Book ID : " << kitaab.ID << " | Title : " << kitaab.title << endl;
        cout << "Author : " << kitaab.author << " | ISBN : " << kitaab.ISBN << endl;
        cout << "Status : " << kitaab.status << endl;
        i++;
    }
}

// Function to calculate total fine
int User::fineBatao(string returnDate){
    int total = 0;
    for(auto i: this->account.current){
        Booking booking = *(i.second);
        if(booking.bookingType == BookingType::INSTANT)
            total += calculateFine(booking.bookingDate, returnDate);
    }
    return total;
}

// Function to remove a book from current bookings
void User::removeFromCurrent(string bookID){
    for(auto i: this->account.current){
        Booking booking = *(i.second);
        if(booking.ID == bookID){
            // Ensure the book is in reservation
            assert(booking.bookingType == BookingType::RESERVATION);

            string bookingID = booking.bookingID;

            this->account.currentID.erase(bookingID);
            this->account.current.erase(bookingID);
            return;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Student Class Function Implementations

// Function for a student to borrow a book
void Student::borrowBook(string date){
    cout << "----------------------------------------" << endl;

    if(this->account.current.size() == 3){
        cout << "Current borrow size = 3" << endl;
        cout << "You may not borrow any more books" << endl;
        cout << "Please return those books to borrow more" << endl;
        return;
    }

    if(this->fineBatao(date)){ // Check if there are any fines
        cout << "Please clear your dues and return overdure books before borrowing more books" << endl;
        cout << "Current dues : " << this->fineBatao(date) << endl;
        return;
    }

    cout << "Borrowing Book" << endl; 

    string BookID;
    cout << "Enter Book ID : ";
    cin >> BookID;

    cout << "----------------------------------------" << endl;

    // Search for book in library
    if(library.bookID.find(BookID) == library.bookID.end()){
        cout << "Book not found" << endl;
        return;
    }else{
        Book* desire = library.books[BookID];
        
        char choice;
        switch (desire->status){
        case BookStatus::AVAILABLE:
            cout << "Do you want to borrow this book? (Y/N) : ";
            cin >> choice;

            if(choice == 'Y' || choice == 'y'){
                cout << "Book Borrowed" << endl;

                // Change status of book to borrowed
                desire->status = BookStatus::BORROWED;
                cout << "Changed the Book status in Library" << endl;

                // Add book to user account's current booking
                string bookingID = gen_random(10); // Generate random Booking ID.
                Booking* currentBooking = new Booking(desire->title, desire->author, desire->publisher, desire->year, desire->ID, desire->ISBN, bookingID, date, "xxxxxxxx", BookingType::INSTANT);

                this->account.currentID.insert(bookingID);
                this->account.current[bookingID] = currentBooking;

                cout << "Added the Book to User's Current Borrowing List" << endl;
            }
            break;

        case BookStatus::BORROWED:
        case BookStatus::RESERVED:
            cout << "The Book is already borrowed by some other user" << endl;
            cout << "Do you want to reserve this book? (Y/N) : ";
            cin >> choice;

            if(choice == 'Y' || choice == 'y'){
                cout << "Book Reserved" << endl;

                // Add user to reservation queue
                desire->reservationQueue.push(this->ID);
                cout << "Added the User to Reservation Queue" << endl;

                string bookingID = gen_random(10); // Generate random Booking ID
                Booking* currentBooking = new Booking(desire->title, desire->author, desire->publisher, desire->year, desire->ID, desire->ISBN, bookingID, date, "xxxxxxxx", BookingType::RESERVATION);

                this->account.current[bookingID] = currentBooking;
                this->account.currentID.insert(bookingID);

                cout << "Added the Book to User's Current Borrowing List as Reserved Book" << endl;
            }
            break;
            
        default:
            cout << "Wrong Option" << endl;
            break;
        }
    }
}

// Function for a student to return a book
void Student::returnBook(string date){
    cout << "----------------------------------------" << endl;

    if(this->account.current.empty()){
        cout << "Nothing to return\n";
        cout << "Exiting......\n";
        return;
    }

    cout << "Showing your list of borrowed/reserved books" << endl;

    int i = 1;
    for(auto it = this->account.current.begin(); it != this->account.current.end(); it++){
        cout << i << ". " << it->second->title << " | Booking ID : " << it->second->bookingID << " | Fine : " << it->second->giveFine(date)  << " | Type : " << it->second->bookingType << endl;
        i++;
    }

    string bookingID;
    cout << "Enter the Booking ID of the book you want to return : ";
    cin >> bookingID;
    
    // Check if this booking has a fine
    if(this->account.current[bookingID]->giveFine(date)){
        // Pay Fine
        bool chk = this->payFine(date, bookingID);
        if(!chk) return;
    }

    if(this->account.current[bookingID]->bookingType == BookingType::RESERVATION){ // If the book was in reservation, remove it

        string bookID = this->account.current[bookingID]->ID;

        // Remove from current
        this->account.current.erase(bookingID);
        this->account.currentID.erase(bookingID);

        // Remove the ID from book's reservation queue
        library.books[bookID]->removeFromQ(this->ID);

        cout << "Booking ID found to be a reservation" << endl;
        cout << "Removed Booking" << endl;
        cout << "Removed User from ReservationQueue of the Book" << endl;
        return;
    }

    // Set return date of book
    this->account.current[bookingID]->returnDate = date;

    // Get the BookID
    string BookID = this->account.current[bookingID]->ID;

    // Move booking to history
    this->account.historyID.insert(bookingID);
    this->account.history[bookingID] = this->account.current[bookingID];
    this->account.current.erase(bookingID);
    this->account.currentID.erase(bookingID);

    cout << "Book Returned" << endl;

    // Check the book's reservation queue for the next user
    while(!library.books[BookID]->reservationQueue.empty()){
        // Get the next user in the reservation queue
        string nextID = library.books[BookID]->reservationQueue.front();
        library.books[BookID]->reservationQueue.pop();

        if(library.studentID.find(nextID) != library.studentID.end()){ // Check if the next user is a student
            if(library.students[nextID]->canBorrow(date)){
                string bookingID = gen_random(10); // Generate new random Booking ID.

                // First remove from current of nextID
                library.students[nextID]->removeFromCurrent(BookID);

                Booking* newBooking = new Booking(library.books[BookID]->title, library.books[BookID]->author, library.books[BookID]->publisher, library.books[BookID]->year, library.books[BookID]->ID, library.books[BookID]->ISBN, bookingID, date, "xxxxxxxx", BookingType::INSTANT);
                library.students[nextID]->account.current[bookingID] = newBooking;
                library.students[nextID]->account.currentID.insert(bookingID);

                cout << "Book Borrowed by the next user in Reservation Queue" << endl;
                return;   
            }                
        }else if(library.facultyID.find(nextID) != library.facultyID.end()){ // Check if the next user is a faculty
            if(library.faculties[nextID]->canBorrow(date)){
                string bookingID = gen_random(10); // Generate new random Booking ID.

                // First remove from current of nextID
                library.faculties[nextID]->removeFromCurrent(BookID);

                Booking* newBooking = new Booking(library.books[BookID]->title, library.books[BookID]->author, library.books[BookID]->publisher, library.books[BookID]->year, library.books[BookID]->ID, library.books[BookID]->ISBN, bookingID, date, "xxxxxxxx", BookingType::INSTANT);
                library.faculties[nextID]->account.current[bookingID] = newBooking;
                library.faculties[nextID]->account.currentID.insert(bookingID);

                cout << "Book Borrowed by the next user in Reservation Queue" << endl;
                return; 
            }
        }
    }

    // If no one is in the reservation queue, set the book status to AVAILABLE
    library.books[BookID]->status = BookStatus::AVAILABLE;
    cout << "Changed the Book status in Library" << endl;
}

// Function for a student to pay fine
bool Student::payFine(string date, string bookingID){
    int TotalFine = this->account.current[bookingID]->giveFine(date);
    cout << "Current Outstanding Fine : " << TotalFine << endl;
    cout << "Enter [Y] to pay : ";
    char choice; cin >> choice;
    if(choice == 'Y' || choice == 'y'){
        this->account.current[bookingID]->fine = TotalFine;
        cout << "Fine Successfully paid\n";
        return true;
    }else{
        cout << "Fine Not paid\n";
        cout << "Book not returned\n";
        return false;
    }
}

// Function to check if a student can borrow a book
bool Student::canBorrow(string date){
    return (this->fineBatao(date) == 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Faculty Class Function Implementations

// Function to check if a faculty member has any books overdue for more than 90 days
bool Faculty::restrict(string date){
    bool f = false;
    for(auto i: this->account.current){
        Booking booking = *(i.second);
        if(giveDaysDiff(booking.bookingDate , date) > 90) f = true;
    }
    return f;
}

// Function for a faculty member to borrow a book
void Faculty::borrowBook(string date){
    cout << "----------------------------------------" << endl;

    if(this->account.current.size() == 5){
        cout << "Current borrow size = 5" << endl;
        cout << "You may not borrow any more books" << endl;
        cout << "Please return those books to borrow more" << endl;
        return;
    }

    // Check if any book is overdue for more than 90 days
    if(this->restrict(date)){
        cout << "Book(s) found which has(have) overdue for more than 60 days" << endl;
        cout << "Please return that book to borrow further" << endl;
        return;
    }            

    cout << "Borrowing Book" << endl;

    string BookID;
    cout << "Enter Book ID : ";
    cin >> BookID;
    // Search for book in library
    if(library.bookID.find(BookID) == library.bookID.end()){
        cout << "Book not found" << endl;
        return;
    }else{
        Book* desire = library.books[BookID];

        char choice;
        switch (desire->status){
        case BookStatus::AVAILABLE:
            cout << "Do you want to borrow this book? (Y/N) : ";
            cin >> choice;

            if(choice == 'Y' || choice == 'y'){
                cout << "Book Borrowed" << endl;

                // Change status of book to borrowed
                desire->status = BookStatus::BORROWED;
                cout << "Changed the Book status in Library" << endl;

                // Add book to user account's current booking
                string bookingID = gen_random(10); // Generate random Booking ID.
                Booking* currentBooking = new Booking(desire->title, desire->author, desire->publisher, desire->year, desire->ID, desire->ISBN, bookingID, date, "xxxxxxxx", BookingType::INSTANT);

                this->account.currentID.insert(bookingID);
                this->account.current[bookingID] = currentBooking;

                cout << "Added the Book to User's Current Borrowing List" << endl;
            }
            break;
        
        case BookStatus::BORROWED:
        case BookStatus::RESERVED:
            cout << "The Book is already borrowed by some other user" << endl;
            cout << "Do you want to reserve this book? (Y/N) : ";
            cin >> choice;

            if(choice == 'Y' || choice == 'y'){
                cout << "Book Reserved" << endl;

                // Add user to reservation queue
                desire->reservationQueue.push(this->ID);
                cout << "Added the User to Reservation Queue" << endl;

                string bookingID = gen_random(10); // Generate random Booking ID.
                Booking* currentBooking = new Booking(desire->title, desire->author, desire->publisher, desire->year, desire->ID, desire->ISBN, bookingID, date, "xxxxxxxx", BookingType::RESERVATION);

                this->account.current[bookingID] = currentBooking;
                this->account.currentID.insert(bookingID);

                cout << "Added the Book to User's Current Borrowing List as Reserved Book" << endl;
            }
            break;

        default:
            cout << "Wrong Option" << endl;
            break;
        }
    }
}

// Function for a faculty member to return a book
void Faculty::returnBook(string date){
    cout << "----------------------------------------" << endl;

    if(this->account.current.empty()){
        cout << "Nothing to return\n";
        cout << "Exiting......\n";
        return;
    }

    cout << "Showing your list of borrowed books" << endl;

    int i = 1;
    for(auto it = this->account.current.begin(); it != this->account.current.end(); it++){
        cout << i << ". " << it->second->title << " | Booking ID : " << it->second->bookingID << " | Days : "<< it->second->giveDays(date) << endl;
        i++;
    }

    string bookingID;
    cout << "Enter Booking ID you want to return : ";
    cin >> bookingID;

    if(this->account.current[bookingID]->bookingType == BookingType::RESERVATION){ // If the book was in reservation, remove it

        string bookID = this->account.current[bookingID]->ID;

        // Remove from current
        this->account.current.erase(bookingID);
        this->account.currentID.erase(bookingID);

        // Remove the ID from book's reservation queue
        library.books[bookID]->removeFromQ(this->ID);

        cout << "Booking ID found to be a reservation" << endl;
        cout << "Removed Booking" << endl;
        cout << "Removed User from ReservationQueue of the Book" << endl;
        return;
    }

    // Set return date of book
    this->account.current[bookingID]->returnDate = date;

    // Get the BookID
    string BookID = this->account.current[bookingID]->ID;

    // Move booking to history
    this->account.historyID.insert(bookingID);
    this->account.history[bookingID] = this->account.current[bookingID];
    this->account.current.erase(bookingID);
    this->account.currentID.erase(bookingID);

    cout << "Book Returned" << endl;

    // Check the book's reservation queue for the next user
    while(!library.books[BookID]->reservationQueue.empty()){
        // Get the next user in the reservation queue
        string nextID = library.books[BookID]->reservationQueue.front();
        library.books[BookID]->reservationQueue.pop();

        if(library.studentID.find(nextID) != library.studentID.end()){ // Check if the next user is a student
            if(library.students[nextID]->canBorrow(date)){
                string bookingID = gen_random(10); // Generate new random Booking ID.

                // First remove from current of nextID
                library.students[nextID]->removeFromCurrent(BookID);

                Booking* newBooking = new Booking(library.books[BookID]->title, library.books[BookID]->author, library.books[BookID]->publisher, library.books[BookID]->year, library.books[BookID]->ID, library.books[BookID]->ISBN, bookingID, date, "xxxxxxxx", BookingType::INSTANT);
                library.students[nextID]->account.current[bookingID] = newBooking;
                library.students[nextID]->account.currentID.insert(bookingID);

                cout << "Book Borrowed by the next user in Reservation Queue" << endl;
                return;   
            }                
        }else if(library.facultyID.find(nextID) != library.facultyID.end()){ // Check if the next user is a faculty
            if(library.faculties[nextID]->canBorrow(date)){
                string bookingID = gen_random(10); // Generate new random Booking ID.

                // First remove from current of nextID
                library.faculties[nextID]->removeFromCurrent(BookID);

                Booking* newBooking = new Booking(library.books[BookID]->title, library.books[BookID]->author, library.books[BookID]->publisher, library.books[BookID]->year, library.books[BookID]->ID, library.books[BookID]->ISBN, bookingID, date, "xxxxxxxx", BookingType::INSTANT);
                library.faculties[nextID]->account.current[bookingID] = newBooking;
                library.faculties[nextID]->account.currentID.insert(bookingID);

                cout << "Book Borrowed by the next user in Reservation Queue" << endl;
                return; 
            }
        }
    }

    // If no one is in the reservation queue, set the book status to AVAILABLE
    library.books[BookID]->status = BookStatus::AVAILABLE;
    cout << "Changed the Book status in Library" << endl;       
}

// Function to check if a faculty member can borrow a book
bool Faculty::canBorrow(string date){
    return !(this->restrict(date));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Librarian Class Function Implementations

// Function for a librarian to borrow a book (not implemented) no need
void Librarian::borrowBook(string date){}

// Function for a librarian to return a book (not implemented) no need
void Librarian::returnBook(string date){}

// Function to check if a librarian can borrow a book (always returns false) no need
bool Librarian::canBorrow(string date){return false;}

// Function for a librarian to add a new user
void Librarian::addUser(){
    cout << "----------------------------------------" << endl;

    cout << "Adding User" << endl;
    cout << "Which type of user do you want to add" << endl;
    cout << "1. Student" << endl;
    cout << "2. Faculty" << endl;
    int choice; cin >> choice;
    getchar();
    
    cout << "Enter Name" << endl;
    string name; getline(cin , name);

    string ID = gen_random(10); // Generate random User ID.

    cout << "Enter password" << endl;
    string pass; getline(cin , pass);

    switch(choice){
        case 1: {
            library.studentID.insert(ID);
            Student* student = new Student(name, ID, pass);
            library.students[ID] = student;
            library.userType[ID] = UserType::STUDENT;
            break;
        }
        case 2: {
            library.facultyID.insert(ID);
            Faculty* faculty = new Faculty(name, ID, pass);
            library.faculties[ID] = faculty;
            library.userType[ID] = UserType::FACULTY;
            break;
        }
        default:
            cout << "Invalid choice" << endl;
            break;
    }
    cout << "New User Added | ID : " << ID << " , save for future use" << endl;
}

// Function for a librarian to add a new book
void Librarian::addBook(){
    cout << "----------------------------------------" << endl;

    cout << "Adding Book" << endl;
    getchar();
    
    cout << "Enter Title" << endl;
    string title; getline(cin, title);
    cout << "Enter author" << endl;
    string author; getline(cin, author);
    cout << "Enter publisher" << endl;
    string publisher; getline(cin, publisher);
    cout << "Enter year" << endl;
    int year; cin >> year;
    getchar();
    cout << "Enter ISBN" << endl;
    string ISBN; getline(cin, ISBN);
    
    string ID = gen_random(10); // Generate random Book ID.

    Book* nayaBook = new Book(title, author, publisher, year, ID, ISBN);
    
    library.bookID.insert(ID);
    library.books[ID] = nayaBook;

    cout << "New book Added" << endl;
}

// Function for a librarian to list all users
void Librarian::listUsers(){
    cout << "----------------------------------------" << endl;

    cout << "Currently registered users" << endl;
    cout << "Students : " << endl;
    int i = 1;
    for(auto j: library.students){
        Student stu = *(j.second);
        cout << i << ". ID : " << stu.ID << " | Name : " << stu.name << endl;
        i++;
    }
    cout << "Faculties : " << endl;
    i = 1;
    for(auto j: library.faculties){
        Faculty fac = *(j.second);
        cout << i << ". ID : " << fac.ID << " | Name : " << fac.name << endl;
        i++;
    }
}

// Function for a librarian to remove a book
void Librarian::removeBooks(){
    cout << "----------------------------------------" << endl;

    cout << "Removing Books" << endl;
    cout << "Enter Book ID to remove" << endl;
    getchar();
    string ID; getline(cin, ID);

    if(library.bookID.find(ID) == library.bookID.end()){
        cout << "Book Not Found" << endl;
        return;
    }

    Book* book = library.books[ID];
    if(book->status == BookStatus::BORROWED){
        cout << "Book Borrowed, not found in Library" << endl;
        return;
    }

    cout << "Book Found" << endl;
    cout << "Do you want to remove this book (Y/N) : ";
    char choice; cin >> choice;
    if(choice == 'Y' || choice == 'y'){
        library.bookID.erase(ID);
        library.books.erase(ID);
        cout << "Book removed" << endl;
    }
}

// Function for a librarian to remove a user
void Librarian::removeUsers(){
    cout << "----------------------------------------" << endl;

    cout << "Removing User" << endl;
    cout << "Enter User ID to remove" << endl;
    getchar();
    string ID; getline(cin, ID);

    if(library.studentID.find(ID) != library.studentID.end()){
        Student* student = library.students[ID];

        cout << "Student found" << endl;

        if(student->account.current.size()){
            cout << "The Student has borrowed books, can't remove" << endl;
            return;
        }

        cout << "Do you want to remove this user (Y/N) : ";
        char choice; cin >> choice;
        if(choice == 'y' || choice == 'Y'){
            library.studentID.erase(ID);
            library.students.erase(ID);
            library.userType.erase(ID);
            cout << "User removed" << endl;
        }
    }else if(library.facultyID.find(ID) != library.facultyID.end()){
        Faculty* faculty = library.faculties[ID];
        
        cout << "Faculty found" << endl;

        if(faculty->account.current.size()){
            cout << "The Faculty has borrowed books, can't remove" << endl;
            return;
        }

        cout << "Do you want to remove this user (Y/N) : ";
        char choice; cin >> choice;
        if(choice == 'y' || choice == 'Y'){
            library.facultyID.erase(ID);
            library.faculties.erase(ID);
            library.userType.erase(ID);
            cout << "User removed" << endl;
        }
    }else{
        cout << "User Not Found, wrong ID entered" << endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Login Functions

// Function for student login
void StudentLogin(){
    cout << "----------------------------------------" << endl;
    
    cout << "Please Enter your unique ID : ";
    string ID; cin >> ID;
    
    cout << "----------------------------------------" << endl;
    
    // If the ID is not in library return to main
    if(library.studentID.find(ID) == library.studentID.end()){
        cout << "Student Not Found" << endl;
        cout << "Exiting......" << endl;
        return;
    }
    
    Student* student = library.students[ID];
    
    // Now the student is found
    cout << "Student Found" << endl;
    cout << "Welcome " << student->name << " !!"<< endl;

    cout << "----------------------------------------" << endl;

    cout << "Please enter today's date (DD/MM/YYYY or DD-MM-YYYY)" << endl;
    getchar();
    string date; getline(cin, date);

    // Doing authentication
    cout << "----------------------------------------" << endl;

    cout << "Enter your password" << endl;
    string pass; cin >> pass;

    if(student->authenticate(pass)){
        bool f = true;

        while(f){
            cout << "----------------------------------------" << endl;

            cout << "What would you like to do" << endl;
            cout << "1. Borrow Book" << endl;
            cout << "2. Return Book" << endl;
            cout << "3. View Booking History" << endl;
            cout << "4. View Current Booking Status" << endl;
            cout << "5. List Books in Library" << endl;
            cout << "6. Log Out" << endl;
            int choice; cin >> choice;
            switch (choice)
            {
            case 1:
                student->borrowBook(date);
                break;
            case 2:
                student->returnBook(date);
                break;
            case 3:
                student->viewHistory(date, UserType::STUDENT);
                break;
            case 4:
                student->viewCurrent(date, UserType::STUDENT);
                break;
            case 5:
                student->listBooks();
                break;
            case 6:
                cout << "Logging out......" << endl;
                f = false;
                break;
            default:
                cout << "Wrong Option" << endl;
                break;
            }
        }
    }else{
        cout << "Wrong password entered" << endl;
        cout << "Exiting......" << endl;
    }
}

// Function for faculty login
void FacultyLogin(){
    cout << "----------------------------------------" << endl;
    
    cout << "Please Enter your unique ID" << endl;
    string ID; cin >> ID;
    
    cout << "----------------------------------------" << endl;
    
    // If the ID is not in library return to main
    if(library.facultyID.find(ID) == library.facultyID.end()){
        cout << "Faculty Not Found" << endl;
        cout << "Exiting......" << endl;
        return;
    }
    
    Faculty* faculty = library.faculties[ID];
    
    // Now the Faculty is found
    cout << "Faculty Found" << endl;
    cout << "Welcome " << faculty->name << " !!"<< endl;
    
    cout << "----------------------------------------" << endl;

    cout << "Please enter today's date (DD/MM/YYYY or DD-MM-YYYY)" << endl;
    getchar();
    string date; getline(cin, date);

    // Doing authentication
    cout << "----------------------------------------" << endl;
    
    cout << "Enter your password" << endl;
    string pass; cin >> pass;

    if(faculty->authenticate(pass)){
        bool f = true;

        while(f){
            cout << "----------------------------------------" << endl;

            cout << "What would you like to do" << endl;
            cout << "1. Borrow Book" << endl;
            cout << "2. Return Book" << endl;
            cout << "3. View Booking History" << endl;
            cout << "4. View Current Booking Status" << endl;
            cout << "5. List Books in Library" << endl;
            cout << "6. Log Out" << endl;
            int choice; cin >> choice;
            switch (choice)
            {
            case 1:
                faculty->borrowBook(date);
                break;
            case 2:
                faculty->returnBook(date);
                break;
            case 3:
                faculty->viewHistory(date, UserType::FACULTY);
                break;
            case 4:
                faculty->viewCurrent(date, UserType::FACULTY);
                break;
            case 5:
                faculty->listBooks();
                break;
            case 6:
                cout << "Logging out......" << endl;
                f = false;
                break;
            default:
                cout << "Wrong Option" << endl;
                break;
            }
        }

    }else{
        cout << "Wrong password entered" << endl;
        cout << "Exiting......" << endl;
    }
}

// Function for librarian login
void LibrarianLogin(){
    cout << "----------------------------------------" << endl;
    
    cout << "Please Enter your unique ID : ";
    string ID; cin >> ID;
    
    cout << "----------------------------------------" << endl;
    
    // If the ID is not in library return to main
    if(library.librarianID.find(ID) == library.librarianID.end()){
        cout << "Librarian Not Found" << endl;
        cout << "Exiting......" << endl;
        return;
    }
    
    Librarian* librarian = library.librarians[ID];
    
    // Librarian found
    cout << "Librarian Found" << endl;
    cout << "Welcome " << librarian->name << " !!"<< endl;

    cout << "----------------------------------------" << endl;

    cout << "Please enter today's date (DD/MM/YYYY or DD-MM-YYYY) : ";
    getchar();
    string date; getline(cin , date);


    // Doing authentication
    cout << "----------------------------------------" << endl;

    cout << "Enter your password" << endl;
    string pass; cin >> pass;

    if(librarian->authenticate(pass)){
        bool f = true;
        while(f){    
            cout << "----------------------------------------" << endl;
            cout << "What would you like to do" << endl;
            cout << "1. Add User" << endl;
            cout << "2. Add Books" << endl;
            cout << "3. List Users" << endl;
            cout << "4. List Books" << endl;
            cout << "5. Remove Books" << endl;
            cout << "6. Remove Users" << endl;
            cout << "7. Log Out" << endl;
            int choice; cin >> choice;
            switch (choice)
            {
            case 1:
                librarian->addUser();
                break;
            case 2:
                librarian->addBook();
                break;
            case 3:
                librarian->listUsers();
                break;
            case 4:
                librarian->listBooks();
                break;
            case 5:
                librarian->removeBooks();
                break;
            case 6:
                librarian->removeUsers();
                break;
            case 7: 
                cout << "Logging out......" << endl;
                f = false;
                break;
            default:
                cout << "Wrong Option" << endl;
                break;
            }
        }

    }else{
        cout << "Wrong password entered" << endl;
        cout << "Exiting......" << endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Save and Load Functions

// Function to save library data to a CSV file
void saveToCSV(const string& filename) {
    ofstream file(filename);
    
    // Save Books
    file << "[Books]" << endl;
    for (const auto& book : library.books) {
        file << book.second->ID << "," << book.second->title << "," << book.second->author << "," 
             << book.second->publisher << "," << book.second->year << "," << book.second->ISBN << "," 
             << book.second->status;
        queue<string> tempQueue = book.second->reservationQueue;
        while (!tempQueue.empty()) {
            file << "," << tempQueue.front();
            tempQueue.pop();
        }
        file << endl;
    }
    
    // Save Users (Students, Faculty, and Librarians)
    file << "[Users]" << endl;
    for (const auto& student : library.students) {
        file << student.second->ID << "," << student.second->name << "," << student.second->getpass() << ",Student" << endl;
    }
    for (const auto& faculty : library.faculties) {
        file << faculty.second->ID << "," << faculty.second->name << "," << faculty.second->getpass() << ",Faculty" << endl;
    }
    for (const auto& librarian : library.librarians) {
        file << librarian.second->ID << "," << librarian.second->name << "," << librarian.second->getpass() << ",Librarian" << endl;
    }
    
    // Save Current Bookings
    file << "[CurrentBookings]" << endl;
    for (const auto& student : library.students) {
        for (const auto& booking : student.second->account.current) {
            file << student.second->ID << "," << booking.second->ID << "," << booking.second->bookingID << "," 
                 << booking.second->bookingDate << "," << booking.second->returnDate << "," 
                 << booking.second->bookingType << "," << booking.second->fine << endl;
        }
    }
    for (const auto& faculty : library.faculties) {
        for (const auto& booking : faculty.second->account.current) {
            file << faculty.second->ID << "," << booking.second->ID << "," << booking.second->bookingID << "," 
                 << booking.second->bookingDate << "," << booking.second->returnDate << "," 
                 << booking.second->bookingType << "," << booking.second->fine << endl;
        }
    }
    
    // Save History Bookings
    file << "[HistoryBookings]" << endl;
    for (const auto& student : library.students) {
        for (const auto& booking : student.second->account.history) {
            file << student.second->ID << "," << booking.second->ID << "," << booking.second->bookingID << "," 
                 << booking.second->bookingDate << "," << booking.second->returnDate << "," 
                 << booking.second->bookingType << "," << booking.second->fine << endl;
        }
    }
    for (const auto& faculty : library.faculties) {
        for (const auto& booking : faculty.second->account.history) {
            file << faculty.second->ID << "," << booking.second->ID << "," << booking.second->bookingID << "," 
                 << booking.second->bookingDate << "," << booking.second->returnDate << "," 
                 << booking.second->bookingType << "," << booking.second->fine << endl;
        }
    }
    
    file.close();
}

// Function to load library data from a CSV file
void loadFromCSV(const string& filename) {
    ifstream file(filename);
    string line;
    string section;
    
    while (getline(file, line)) {
        if (line.empty()) continue;
        if (line[0] == '[') {
            section = line;
            continue;
        }
        
        if (section == "[Books]") {
            stringstream ss(line);
            string ID, title, author, publisher, yearStr, ISBN, statusStr, reservationQueueStr;
            getline(ss, ID, ',');
            getline(ss, title, ',');
            getline(ss, author, ',');
            getline(ss, publisher, ',');
            getline(ss, yearStr, ',');
            getline(ss, ISBN, ',');
            getline(ss, statusStr, ',');
            getline(ss, reservationQueueStr, ',');
            
            int year = stoi(yearStr);
            BookStatus status = (statusStr == "AVAILABLE") ? BookStatus::AVAILABLE : 
                                (statusStr == "BORROWED") ? BookStatus::BORROWED : BookStatus::RESERVED;
            
            queue<string> reservationQueue;
            stringstream queueSS(reservationQueueStr);
            string userID;
            while (getline(queueSS, userID, ',')) {
                reservationQueue.push(userID);
            }
            
            Book* book = new Book(title, author, publisher, year, ID, ISBN, status, reservationQueue);
            library.books[ID] = book;
            library.bookID.insert(ID);
        } else if (section == "[Users]") {
            stringstream ss(line);
            string ID, name, password, type;
            getline(ss, ID, ',');
            getline(ss, name, ',');
            getline(ss, password, ',');
            getline(ss, type, ',');
            
            if (type == "Student") {
                Student* student = new Student(name, ID, password);
                library.students[ID] = student;
                library.studentID.insert(ID);
                library.userType[ID] = UserType::STUDENT;
            } else if (type == "Faculty") {
                Faculty* faculty = new Faculty(name, ID, password);
                library.faculties[ID] = faculty;
                library.facultyID.insert(ID);
                library.userType[ID] = UserType::FACULTY;
            } else if (type == "Librarian") {
                Librarian* librarian = new Librarian(name, ID, password);
                library.librarians[ID] = librarian;
                library.librarianID.insert(ID);
                library.userType[ID] = UserType::LIBRARIAN;
            }
        } else if (section == "[CurrentBookings]") {
            stringstream ss(line);
            string userID, bookID, bookingID, bookingDate, returnDate, bookingTypeStr, fineStr;
            getline(ss, userID, ',');
            getline(ss, bookID, ',');
            getline(ss, bookingID, ',');
            getline(ss, bookingDate, ',');
            getline(ss, returnDate, ',');
            getline(ss, bookingTypeStr, ',');
            getline(ss, fineStr, ',');
            
            BookingType bookingType = (bookingTypeStr == "INSTANT") ? BookingType::INSTANT : BookingType::RESERVATION;
            int fine = stoi(fineStr);
            
            Book* book = library.books[bookID];
            Booking* booking = new Booking(book->title, book->author, book->publisher, book->year, book->ID, book->ISBN, bookingID, bookingDate, returnDate, bookingType, fine);
            
            if (library.students.find(userID) != library.students.end()) {
                library.students[userID]->account.current[bookingID] = booking;
                library.students[userID]->account.currentID.insert(bookingID);
            } else if (library.faculties.find(userID) != library.faculties.end()) {
                library.faculties[userID]->account.current[bookingID] = booking;
                library.faculties[userID]->account.currentID.insert(bookingID);
            }
        } else if (section == "[HistoryBookings]") {
            stringstream ss(line);
            string userID, bookID, bookingID, bookingDate, returnDate, bookingTypeStr, fineStr;
            getline(ss, userID, ',');
            getline(ss, bookID, ',');
            getline(ss, bookingID, ',');
            getline(ss, bookingDate, ',');
            getline(ss, returnDate, ',');
            getline(ss, bookingTypeStr, ',');
            getline(ss, fineStr, ',');
            
            BookingType bookingType = (bookingTypeStr == "INSTANT") ? BookingType::INSTANT : BookingType::RESERVATION;
            int fine = stoi(fineStr);
            
            Book* book = library.books[bookID];
            Booking* booking = new Booking(book->title, book->author, book->publisher, book->year, book->ID, book->ISBN, bookingID, bookingDate, returnDate, bookingType, fine);
            
            if (library.students.find(userID) != library.students.end()) {
                library.students[userID]->account.history[bookingID] = booking;
                library.students[userID]->account.historyID.insert(bookingID);
            } else if (library.faculties.find(userID) != library.faculties.end()) {
                library.faculties[userID]->account.history[bookingID] = booking;
                library.faculties[userID]->account.historyID.insert(bookingID);
            }
        }
    }
    
    file.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Main Function

int main() {
    srand((unsigned)time(NULL) * getpid());

    // Load data from CSV
    loadFromCSV("library_data_input.csv");

    // START LIBRARY MANAGEMENT SYSTEM
    cout << "----------------------------------------" << endl;
    cout << "WELCOME TO THE LIBRARY MANAGEMENT SYSTEM" << endl;
    
    bool f = true;
    while (f) {
        cout << "----------------------------------------" << endl;
        cout << "How would you like to login" << endl;
        cout << "1. Student" << endl;
        cout << "2. Faculty" << endl;
        cout << "3. Librarian" << endl;
        cout << "4. Exit" << endl;
        cout << "----------------------------------------" << endl;

        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                StudentLogin();
                break;

            case 2:
                FacultyLogin();
                break;

            case 3:
                LibrarianLogin();
                break;

            case 4:
                f = false;
                break;

            default:
                break;
        }
    }
    
    // Save data to CSV
    saveToCSV("library_data_output.csv");

    cout << "System Closed" << endl;

    return 0;
}