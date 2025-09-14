#include "User.h"
#include <algorithm>

User::User(const std::string& id, const std::string& name, int maxBooks, int maxDays)
    : id(id), name(name), maxBooks(maxBooks), maxDays(maxDays) {}

std::string User::getId() const { return id; }
std::string User::getName() const { return name; }

bool User::borrowBook(std::shared_ptr<Book> book) {
    if (borrowedBooks.size() >= static_cast<size_t>(maxBooks) || !book->isAvailable())
        return false;

    borrowedBooks.push_back(book);
    book->setAvailable(false);
    return true;
}

void User::returnBook(const std::string& isbn) {
    auto it = std::remove_if(borrowedBooks.begin(), borrowedBooks.end(),
        [&](std::shared_ptr<Book> b) { return b->getIsbn() == isbn; });

    if (it != borrowedBooks.end()) {
        (*it)->setAvailable(true);
        borrowedBooks.erase(it, borrowedBooks.end());
    }
}

const std::vector<std::shared_ptr<Book>>& User::getBorrowedBooks() const {
    return borrowedBooks;
}
