#pragma once
#include <string>

class Book {
private:
    std::string isbn;
    std::string title;
    std::string author;
    bool available;

public:
    Book(const std::string& isbn, const std::string& title, const std::string& author);

    std::string getIsbn() const;
    std::string getTitle() const;
    std::string getAuthor() const;

    bool isAvailable() const;
    void setAvailable(bool status);
};
