#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Book.h"

class User {
protected:
    std::string id;
    std::string name;
    int maxBooks;
    int maxDays;
    std::vector<std::shared_ptr<Book>> borrowedBooks;

public:
    User(const std::string& id, const std::string& name, int maxBooks, int maxDays);
    virtual ~User() = default;

    std::string getId() const;
    std::string getName() const;

    virtual bool borrowBook(std::shared_ptr<Book> book);
    virtual void returnBook(const std::string& isbn);

    const std::vector<std::shared_ptr<Book>>& getBorrowedBooks() const;
};
