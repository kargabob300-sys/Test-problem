#include "DateUtils.h"

#include <iomanip>
#include <iostream>
#include <sstream>

bool validateBorrowDate(const std::string& date)
{
  std::tm            tm{};
  std::istringstream ss(date);
  ss >> std::get_time(&tm, "%Y-%m-%d");
  if (ss.fail())
  {
    std::cout << "Error: incorrect date format! Use YYYY-MM-DD.\n";
    return false;
  }

  std::time_t borrow_time = std::mktime(&tm);

  std::time_t now   = std::time(nullptr);
  std::tm*    t     = std::localtime(&now);
  t->tm_hour        = 0;
  t->tm_min         = 0;
  t->tm_sec         = 0;
  std::time_t today = std::mktime(t);

  if (borrow_time < today)
  {
    std::cout << "Error: you can not take the book on the past date!\n";
    return false;
  }
  return true;
}
