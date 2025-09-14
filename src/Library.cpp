#include "Library.h"

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
