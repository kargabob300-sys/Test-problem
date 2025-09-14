#pragma once
#include "Book.h"
#include "User.h"

#include <memory>
#include <string>
#include <unordered_map>

class Library
{
private:
  std::unordered_map<std::string, std::shared_ptr<Book>> books;
  std::unordered_map<std::string, std::shared_ptr<User>> users;

public:
  void                  addBook(const std::shared_ptr<Book>& book);
  void                  removeBook(const std::string& isbn);
  std::shared_ptr<Book> findBook(const std::string& isbn);

  void                  addUser(const std::shared_ptr<User>& user);
  std::shared_ptr<User> findUser(const std::string& id);

  // console helpers
  void listBooks() const;
  void listUsers() const;

  // borrowing operations (date format YYYY-MM-DD)
  bool borrowBook(const std::string& userId, const std::string& isbn, const std::string& date);
  bool returnBook(const std::string& userId, const std::string& isbn);

  // show overdue items as of currentDate (YYYY-MM-DD)
  void showOverdue(const std::string& currentDate) const;
};
