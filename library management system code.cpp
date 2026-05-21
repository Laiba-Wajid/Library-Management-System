#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Book {
    int bookID;
    string bookName;
    string author;
    string studentName;
    float price;
    int pages;
};

// Function to add a book to the file
void addBook() {
    Book book;
    ofstream file("books.dat", ios::app | ios::binary);
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    cout << "Enter Book ID: ";
    cin >> book.bookID;
    cin.ignore();
    cout << "Enter Book Name: ";
    getline(cin, book.bookName);
    cout << "Enter Author Name: ";
    getline(cin, book.author);
    cout << "Enter Student Name (if issued): ";
    getline(cin, book.studentName);
    cout << "Enter Book Price: ";
    cin >> book.price;
    cout << "Enter Number of Pages: ";
    cin >> book.pages;
    cin.ignore();

    file.write((char*)&book, sizeof(Book));
    file.close();
    cout << "Book added successfully!" << endl;
}

// Function to display all books
void displayBooks() {
    Book book;
    ifstream file("books.dat", ios::binary);
    if (!file) {
        cout << "No books available or error opening file!" << endl;
        return;
    }

    cout << "\nList of Books:\n";
    while (file.read((char*)&book, sizeof(Book))) {
        cout << "-------------------------\n";
        cout << "Book ID: " << book.bookID << "\n";
        cout << "Book Name: " << book.bookName << "\n";
        cout << "Author: " << book.author << "\n";
        cout << "Student Name (if issued): " << book.studentName << "\n";
        cout << "Price: " << book.price << "\n";
        cout << "Pages: " << book.pages << "\n";
    }
    cout << "-------------------------\n";
    file.close();
}

// Function to search a book by ID
void searchBookByID() {
    Book book;
    int bookID;
    ifstream file("books.dat", ios::binary);
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    cout << "Enter Book ID to search: ";
    cin >> bookID;
    bool found = false;
    while (file.read((char*)&book, sizeof(Book))) {
        if (book.bookID == bookID) {
            cout << "Book found: \n";
            cout << "Book ID: " << book.bookID << "\n";
            cout << "Book Name: " << book.bookName << "\n";
            cout << "Author: " << book.author << "\n";
            cout << "Student Name (if issued): " << book.studentName << "\n";
            cout << "Price: " << book.price << "\n";
            cout << "Pages: " << book.pages << "\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Book with ID " << bookID << " not found.\n";
    }
    file.close();
}

// Function to delete a book by ID
void deleteBook() {
    Book book;
    int bookID;
    ifstream file("books.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);
    if (!file || !temp) {
        cout << "Error opening file!" << endl;
        return;
    }

    cout << "Enter Book ID to delete: ";
    cin >> bookID;
    bool found = false;
    while (file.read((char*)&book, sizeof(Book))) {
        if (book.bookID != bookID) {
            temp.write((char*)&book, sizeof(Book));
        } else {
            found = true;
        }
    }
    file.close();
    temp.close();
    remove("books.dat");
    rename("temp.dat", "books.dat");
    if (found) {
        cout << "Book with ID " << bookID << " has been deleted.\n";
    } else {
        cout << "Book with ID " << bookID << " not found.\n";
    }
}

int main() {
    int option;
    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. View All Books\n";
        cout << "3. Search Book by ID\n";
        cout << "4. Delete Book by ID\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> option;
        cin.ignore();
        switch (option) {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                searchBookByID();
                break;
            case 4:
                deleteBook();
                break;
            case 5:
                cout << "Exiting the system...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (option != 5);
    return 0;
}
