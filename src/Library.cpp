#include "Library.h"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <iomanip>

static std::time_t to_time_t(const std::string& date) {
    std::tm tm {};
    std::istringstream ss(date);
    ss >> std::get_time(&tm, "%Y-%m-%d");
    if (ss.fail()) return -1;
    tm.tm_hour = 0; tm.tm_min = 0; tm.tm_sec = 0;
    return std::mktime(&tm);
}

static int daysBetween(const std::string& start, const std::string& end) {
    std::time_t s = to_time_t(start);
    std::time_t e = to_time_t(end);
    if (s == -1 || e == -1) return 0;
    const double seconds = std::difftime(e, s);
    return static_cast<int>(seconds / (60 * 60 * 24));
}

void Library::addBook(const std::shared_ptr<Book>& book) {
    books[book->getIsbn()] = book;
}

void Library::removeBook(const std::string& isbn) {
    books.erase(isbn);
}

std::shared_ptr<Book> Library::findBook(const std::string& isbn) {
    auto it = books.find(isbn);
    return (it != books.end()) ? it->second : nullptr;
}

void Library::addUser(const std::shared_ptr<User>& user) {
    users[user->getId()] = user;
}

std::shared_ptr<User> Library::findUser(const std::string& id) {
    auto it = users.find(id);
    return (it != users.end()) ? it->second : nullptr;
}

void Library::listBooks() const {
    std::cout << "Books in library:\n";
    for (const auto& kv : books) {
        auto b = kv.second;
        std::cout << "- ISBN: " << b->getIsbn()
                  << " | Title: " << b->getTitle()
                  << " | Author: " << b->getAuthor()
                  << " | Available: " << (b->isAvailable() ? "Yes" : "No") << "\n";
    }
}

void Library::listUsers() const {
    std::cout << "Registered users:\n";
    for (const auto& kv : users) {
        auto u = kv.second;
        std::cout << "- ID: " << u->getId()
                  << " | Name: " << u->getName()
                  << " | Borrowed: " << u->getBorrowedBooks().size() << "\n";
    }
}

bool Library::borrowBook(const std::string& userId, const std::string& isbn, const std::string& date) {
    auto user = findUser(userId);
    if (!user) {
        std::cerr << "User not found: " << userId << "\n";
        return false;
    }
    auto book = findBook(isbn);
    if (!book) {
        std::cerr << "Book not found: " << isbn << "\n";
        return false;
    }
    if (!book->isAvailable()) {
        std::cerr << "Book is currently not available: " << isbn << "\n";
        return false;
    }
    if (user->getBorrowedBooks().size() >= static_cast<size_t>(user->getBorrowedBooks().capacity())) {
        // capacity check meaningless here; skip
    }
    if (!user->borrowBook(book, date)) {
        std::cerr << "Cannot borrow book (limit reached or unavailable).\n";
        return false;
    }
    return true;
}

bool Library::returnBook(const std::string& userId, const std::string& isbn) {
    auto user = findUser(userId);
    if (!user) {
        std::cerr << "User not found: " << userId << "\n";
        return false;
    }
    if (!user->returnBook(isbn)) {
        std::cerr << "User does not have this book: " << isbn << "\n";
        return false;
    }
    return true;
}

void Library::showOverdue(const std::string& currentDate) const {
    std::cout << "Overdue items as of " << currentDate << ":\n";
    bool any = false;
    for (const auto& kv : users) {
        const auto& user = kv.second;
        for (const auto& item : user->getBorrowedBooks()) {
            int days = daysBetween(item.borrowDate, currentDate);
            if (days > user->getMaxDays()) {
                any = true;
                std::cout << "- User: " << user->getId() << " | Name: " << user->getName()
                          << " | ISBN: " << item.book->getIsbn()
                          << " | Title: " << item.book->getTitle()
                          << " | Borrowed on: " << item.borrowDate
                          << " | Days borrowed: " << days
                          << " | Allowed: " << user->getMaxDays() << "\n";
            }
        }
    }
    if (!any) std::cout << "No overdue items.\n";
}
