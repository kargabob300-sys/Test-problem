#include <iostream>
#include "Library.h"
#include "Student.h"
#include "Faculty.h"
#include "Guest.h"

int main() {
    Library library;

    // Добавим тестовые данные
    library.addBook(std::make_shared<Book>("001", "C++ Basics", "Bjarne Stroustrup"));
    library.addBook(std::make_shared<Book>("002", "Design Patterns", "GoF"));

    library.addUser(std::make_shared<Student>("s1", "Alice"));
    library.addUser(std::make_shared<Faculty>("f1", "Dr. Smith"));
    library.addUser(std::make_shared<Guest>("g1", "Bob"));

    std::cout << "Library Management System (skeleton)" << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    std::cout << "Books and users initialized." << std::endl;

    return 0;
}
