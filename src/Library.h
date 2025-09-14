#pragma once
#include <unordered_map>
#include <memory>
#include "Book.h"
#include "User.h"

class Library {
private:
    std::unordered_map<std::string, std::shared_ptr<Book>> books;
    std::unordered_map<std::string, std::shared_ptr<User>> users;

public:
    void addBook(const std::shared_ptr<Book>& book);
    void removeBook(const std::string& isbn);
    std::shared_ptr<Book> findBook(const std::string& isbn);

    void addUser(const std::shared_ptr<User>& user);
    std::shared_ptr<User> findUser(const std::string& id);
};
