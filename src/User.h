#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Book.h"

struct BorrowedItem {
    std::shared_ptr<Book> book;
    std::string borrowDate; // "YYYY-MM-DD"
};

class User {
protected:
    std::string id;
    std::string name;
    int maxBooks;
    int maxDays;
    std::vector<BorrowedItem> borrowedBooks;

public:
    User(const std::string& id, const std::string& name, int maxBooks, int maxDays);
    virtual ~User() = default;

    std::string getId() const;
    std::string getName() const;
    int getMaxDays() const;

    // borrow/return using date string YYYY-MM-DD
    virtual bool borrowBook(std::shared_ptr<Book> book, const std::string& date);
    virtual bool returnBook(const std::string& isbn);

    const std::vector<BorrowedItem>& getBorrowedBooks() const;
};
