#include "Void.h"

Void::Void() : Type(true)
{
}

bool Void::isPrintable() const
{
    return false;
}

std::string Void::toString() const
{
    return "";
}
