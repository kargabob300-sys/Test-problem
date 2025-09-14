#pragma once
#include <ctime>
#include <string>

// Checking that the date is correct and not in the past.
// Returns true if everything is fine, false if there is an error.
// Error messages are output inside the function.
bool validateBorrowDate(const std::string& date);
