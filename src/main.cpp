#include "src.h"

#include <iostream>
#include <limits>
#include <memory>
#include <string>

int main()
{
  Library library;

  // Test
  library.addBook(std::make_shared<Book>("001", "C++ Basics", "Bjarne Stroustrup"));
  library.addBook(std::make_shared<Book>("002", "Design Patterns", "Gamma, Helm, Johnson, Vlissides"));
  library.addBook(std::make_shared<Book>("003", "Clean Code", "Robert C. Martin"));

  library.addUser(std::make_shared<Student>("s1", "Alice"));
  library.addUser(std::make_shared<Faculty>("f1", "Dr. Smith"));
  library.addUser(std::make_shared<Guest>("g1", "Bob"));

  std::cout << "Library Management System\n";
  std::cout << "-------------------------\n";

  while (true)
  {
    std::cout << "\nMenu:\n"
              << "1) Add book\n"
              << "2) Remove book\n"
              << "3) Register user\n"
              << "4) Borrow book\n"
              << "5) Return book\n"
              << "6) List books\n"
              << "7) List users\n"
              << "8) Show overdue (enter date YYYY-MM-DD)\n"
              << "0) Exit\n"
              << "Choose: ";
    int choice;
    if (!(std::cin >> choice))
      break;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice == 0)
      break;
    if (choice == 1)
    {
      std::string isbn, title, author;
      std::cout << "ISBN: ";
      std::getline(std::cin, isbn);
      std::cout << "Title: ";
      std::getline(std::cin, title);
      std::cout << "Author: ";
      std::getline(std::cin, author);
      library.addBook(std::make_shared<Book>(isbn, title, author));
      std::cout << "Book added.\n";
    }
    else if (choice == 2)
    {
      std::string isbn;
      std::cout << "ISBN to remove: ";
      std::getline(std::cin, isbn);
      library.removeBook(isbn);
      std::cout << "Book removed (if existed).\n";
    }
    else if (choice == 3)
    {
      std::string id, name;
      int         type;
      std::cout << "User ID: ";
      std::getline(std::cin, id);
      std::cout << "Name: ";
      std::getline(std::cin, name);
      std::cout << "Type (1=Student,2=Faculty,3=Guest): ";
      std::cin >> type;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      if (type == 1)
        library.addUser(std::make_shared<Student>(id, name));
      else if (type == 2)
        library.addUser(std::make_shared<Faculty>(id, name));
      else
        library.addUser(std::make_shared<Guest>(id, name));
      std::cout << "User registered.\n";
    }
    else if (choice == 4)
    {
      std::string userId, isbn, date;
      std::cout << "User ID: ";
      std::getline(std::cin, userId);
      std::cout << "ISBN: ";
      std::getline(std::cin, isbn);
      std::cout << "Borrow date (YYYY-MM-DD): ";
      std::getline(std::cin, date);
      if (library.borrowBook(userId, isbn, date))
        std::cout << "Book borrowed.\n";
      else
        std::cout << "Failed to borrow book.\n";
    }
    else if (choice == 5)
    {
      std::string userId, isbn;
      std::cout << "User ID: ";
      std::getline(std::cin, userId);
      std::cout << "ISBN: ";
      std::getline(std::cin, isbn);
      if (library.returnBook(userId, isbn))
        std::cout << "Book returned.\n";
      else
        std::cout << "Failed to return book.\n";
    }
    else if (choice == 6)
    {
      library.listBooks();
    }
    else if (choice == 7)
    {
      library.listUsers();
    }
    else if (choice == 8)
    {
      std::string date;
      std::cout << "Date (YYYY-MM-DD): ";
      std::getline(std::cin, date);
      library.showOverdue(date);
    }
    else
    {
      std::cout << "Unknown choice.\n";
    }
  }

  std::cout << "Goodbye!\n";
  return 0;
}
