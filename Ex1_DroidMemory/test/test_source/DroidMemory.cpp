#include "../test_include/DroidMemory.hpp"

DroidMemory::DroidMemory(void) :    Fingerprint(random()), Exp(0)
{
}

DroidMemory::~DroidMemory(void)
{
}

size_t          DroidMemory::getFingerprint(void) const
{
    return Fingerprint;
}

size_t          DroidMemory::getExp(void) const
{
    return Exp;
}

void            DroidMemory::setFingerprint(size_t fingerprint)
{
    Fingerprint = fingerprint;
}

void            DroidMemory::setExp(size_t exp)
{
    Exp = exp;
}

DroidMemory     &DroidMemory::operator+=(const size_t &rhs)
{
    Exp += rhs;
    Fingerprint ^= rhs;
    return *this;
}

DroidMemory     &DroidMemory::operator+=(const DroidMemory &rhs)
{
    Exp += rhs.Exp;
    Fingerprint ^= rhs.Fingerprint;
    return *this;
}

DroidMemory     &DroidMemory::operator<<(const DroidMemory &rhs)
{
    Exp += rhs.Exp;
    Fingerprint ^= rhs.Fingerprint;
    return *this;
}

DroidMemory     &DroidMemory::operator>>(DroidMemory &lhs) const
{
    lhs.Exp += Exp;
    lhs.Fingerprint ^= Fingerprint;
    return lhs;
}

std::ostream    &operator<<(std::ostream &ostream, const DroidMemory &rhs)
{
    return ostream  << "DroidMemory '" << rhs.getFingerprint() 
                    << "', " << rhs.getExp();

}