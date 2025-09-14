#include "User.h"

#include <algorithm>
#include <ctime>
#include <iomanip>
#include <sstream>

static std::time_t to_time_t(const std::string& date)
{
  std::tm            tm{};
  std::istringstream ss(date);
  ss >> std::get_time(&tm, "%Y-%m-%d");
  if (ss.fail())
    return -1;
  tm.tm_hour = 0;
  tm.tm_min  = 0;
  tm.tm_sec  = 0;
  return std::mktime(&tm);
}

static int daysBetween(const std::string& start, const std::string& end)
{
  std::time_t s = to_time_t(start);
  std::time_t e = to_time_t(end);
  if (s == -1 || e == -1)
    return 0;
  const double seconds = std::difftime(e, s);
  return static_cast<int>(seconds / (60 * 60 * 24));
}

User::User(const std::string& id, const std::string& name, int maxBooks, int maxDays)
    : id(id), name(name), maxBooks(maxBooks), maxDays(maxDays)
{
}

std::string User::getId() const
{
  return id;
}
std::string User::getName() const
{
  return name;
}
int User::getMaxDays() const
{
  return maxDays;
}

bool User::borrowBook(std::shared_ptr<Book> book, const std::string& date)
{
  if (borrowedBooks.size() >= static_cast<size_t>(maxBooks) || !book->isAvailable())
    return false;

  borrowedBooks.push_back({book, date});
  book->setAvailable(false);
  return true;
}

bool User::returnBook(const std::string& isbn)
{
  auto it = std::remove_if(borrowedBooks.begin(), borrowedBooks.end(),
                           [&](const BorrowedItem& b) { return b.book->getIsbn() == isbn; });

  if (it != borrowedBooks.end())
  {
    // mark returned books as available
    for (auto itr = it; itr != borrowedBooks.end(); ++itr)
    {
      if (itr->book)
        itr->book->setAvailable(true);
    }
    borrowedBooks.erase(it, borrowedBooks.end());
    return true;
  }
  return false;
}

const std::vector<BorrowedItem>& User::getBorrowedBooks() const
{
  return borrowedBooks;
}
