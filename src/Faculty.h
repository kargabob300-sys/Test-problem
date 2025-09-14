#pragma once
#include "User.h"

class Faculty : public User {
public:
    Faculty(const std::string& id, const std::string& name);
};
