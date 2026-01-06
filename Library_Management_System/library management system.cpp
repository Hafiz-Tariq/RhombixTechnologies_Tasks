#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <fstream>

// Disable Visual Studio secure-function warnings
#define _CRT_SECURE_NO_WARNINGS

using namespace std;
using std::string;

/*
    Returns a due date string after adding given number of days
    Format: YYYY-MM-DD
*/
string getDueDate(int days) {
    time_t t = time(0);                   // Current time
    t += days * 24 * 60 * 60;             // Add days in seconds

    tm nowStruct;
    localtime_s(&nowStruct, &t);          // Safe localtime (Visual Studio)

    string month = to_string(nowStruct.tm_mon + 1);
    string day = to_string(nowStruct.tm_mday);

    return to_string(nowStruct.tm_year + 1900) + "-" + month + "-" + day;
}

/*
    Book class holds book-related data
*/
class Book {
private:
    int bookID;
    string title;
    bool isissued;

public:
    Book() {
        bookID = 0;
        title = "";
        isissued = false;
    }

    ~Book() {}

    int getBookID() const {
        return bookID;
    }

    string getTitle() {
        return title;
    }

    bool getIsIssued() const {
        return isissued;
    }

    void setBookID(int id) {
        bookID = id;
    }

    void setTitle(string t) {
        title = t;
    }

    void setIsIssued(bool issued) {
        isissued = issued;
    }
};

/*
    User class provides basic library features
*/
class User {
public:
    User() {}
    ~User() {}

    // Display all books from file
    void viewBooks() {
        ifstream file("books.txt");
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
    }

    // Search for a book by title or ID
    void searchBook() {
        string title;
        cout << "Enter book title or id to search: ";
        getline(cin, title);

        ifstream file("books.txt");
        string line;
        bool found = false;

        while (getline(file, line)) {
            if (line.find(title) != string::npos) {
                cout << line << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "Book not found." << endl;
        }
    }

    // Issue a book and assign due date
    void issueBook() {
        string title;
        cout << "Enter book title or id to search: ";
        getline(cin, title);

        ifstream file("books.txt");
        ofstream temp("temp.txt");

        string line;
        bool found = false;
        bool issued = false;

        while (getline(file, line)) {
            if (line.find(title) != string::npos) {
                found = true;

                if (line.find("Available") != string::npos) {
                    line.replace(line.find("Available"), 9, "Issued");

                    size_t pos = line.find("Due Date:");
                    if (pos != string::npos) {
                        line.replace(pos + 10, line.size() - (pos + 10), getDueDate(7));
                    }

                    issued = true;
                }
            }

            temp << line << endl;
        }

        file.close();
        temp.close();

        remove("books.txt");
        if (rename("temp.txt", "books.txt") != 0) {
            perror("Error renaming file");
        }

        if (!found)
            cout << "Book not found." << endl;
        else if (issued)
            cout << "Book issued successfully. Due in 7 days." << endl;
        else
            cout << "Book is already issued." << endl;
    }

    // Return a book and clear due date
    void returnBook() {
        string title;
        cout << "Enter book title or id to return: ";
        getline(cin, title);

        ifstream file("books.txt");
        ofstream temp("temp.txt");

        string line;
        bool found = false;
        bool returned = false;

        while (getline(file, line)) {
            if (line.find(title) != string::npos) {
                found = true;

                if (line.find("Issued") != string::npos) {
                    line.replace(line.find("Issued"), 6, "Available");

                    size_t pos = line.find("Due Date:");
                    if (pos != string::npos) {
                        line.replace(pos + 10, line.size() - (pos + 10), "N/A");
                    }

                    returned = true;
                }
            }

            temp << line << endl;
        }

        file.close();
        temp.close();

        remove("books.txt");
        if (rename("temp.txt", "books.txt") != 0) {
            perror("Error renaming file");
        }

        if (!found)
            cout << "Book not found." << endl;
        else if (returned)
            cout << "Book returned successfully." << endl;
        else
            cout << "Book was already available." << endl;
    }
};

/*
    Admin class extends User with management features
*/
class Admin : public User {
public:
    Admin() {}
    ~Admin() {}

    // Add a new book to library
    void addBook() {
        Book book;

        cout << "Enter Book ID: ";
        int id;
        cin >> id;
        cin.ignore();

        book.setBookID(id);

        cout << "Enter Book Title: ";
        string title;
        getline(cin, title);

        book.setTitle(title);
        book.setIsIssued(false);

        ofstream file("books.txt", ios::app);
        file << "Book ID: " << book.getBookID()
            << ", Title: " << book.getTitle()
            << ", Status: " << (book.getIsIssued() ? "Issued" : "Available")
            << ", Due Date: N/A" << endl;
    }

    // Remove a book from library
    void removeBook() {
        string bookID;
        cout << "Enter Book ID or name to remove: ";
        getline(cin, bookID);

        ifstream file("books.txt");
        ofstream temp("temp.txt");

        string line;
        bool found = false;

        while (getline(file, line)) {
            if (line.find(bookID) != string::npos) {
                found = true;
            }
            else {
                temp << line << endl;
            }
        }

        file.close();
        temp.close();

        remove("books.txt");
        if (rename("temp.txt", "books.txt") != 0) {
            perror("Error renaming file");
        }

        if (found)
            cout << "Book removed successfully" << endl;
        else
            cout << "Book not found." << endl;
    }
};

/*
    Main function with menu-driven system
*/
int main() {
    Admin admin;
    User user;
    string mainChoice;

    while (true) {
        cout << "\n===== Library Management System =====\n";
        cout << "1. Admin Menu\n";
        cout << "2. User Menu\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";

        cin >> mainChoice;
        cin.ignore();

        if (mainChoice == "1") {
            string adminChoice;

            while (true) {
                cout << "\n----- Admin Menu -----\n";
                cout << "1. View All Books\n";
                cout << "2. Search Book\n";
                cout << "3. Issue Book\n";
                cout << "4. Return Book\n";
                cout << "5. Add Book\n";
                cout << "6. Remove Book\n";
                cout << "7. Back\n";
                cout << "Enter choice: ";

                cin >> adminChoice;
                cin.ignore();

                if (adminChoice == "1") admin.viewBooks();
                else if (adminChoice == "2") admin.searchBook();
                else if (adminChoice == "3") admin.issueBook();
                else if (adminChoice == "4") admin.returnBook();
                else if (adminChoice == "5") admin.addBook();
                else if (adminChoice == "6") admin.removeBook();
                else if (adminChoice == "7") break;
                else cout << "Invalid choice.\n";
            }
        }
        else if (mainChoice == "2") {
            string userChoice;

            while (true) {
                cout << "\n----- User Menu -----\n";
                cout << "1. View All Books\n";
                cout << "2. Search Book\n";
                cout << "3. Issue Book\n";
                cout << "4. Return Book\n";
                cout << "5. Back\n";
                cout << "Enter choice: ";

                cin >> userChoice;
                cin.ignore();

                if (userChoice == "1") user.viewBooks();
                else if (userChoice == "2") user.searchBook();
                else if (userChoice == "3") user.issueBook();
                else if (userChoice == "4") user.returnBook();
                else if (userChoice == "5") break;
                else cout << "Invalid choice.\n";
            }
        }
        else if (mainChoice == "3") {
            cout << "Exiting program...\n";
            break;
        }
        else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
