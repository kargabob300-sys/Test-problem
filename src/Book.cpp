#include "Book.h"

Book::Book(const std::string& isbn, const std::string& title, const std::string& author)
    : isbn(isbn), title(title), author(author), available(true) {}

std::string Book::getIsbn() const { return isbn; }
std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }

bool Book::isAvailable() const { return available; }
void Book::setAvailable(bool status) { available = status; }
