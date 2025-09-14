#pragma once
#include "User.h"

class Guest : public User
{
public:
  Guest(const std::string& id, const std::string& name);
};
