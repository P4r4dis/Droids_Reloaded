#include "../test_include/DroidFactory.hpp"

DroidFactory::DroidFactory(size_t ratio)    :   _ratio(ratio)
{}

DroidFactory::DroidFactory(const DroidFactory &obj) :   _ratio(obj._ratio)
{}

DroidFactory::~DroidFactory(void)
{}

DroidFactory            &DroidFactory::operator=(const DroidFactory &obj)
{
    _ratio = obj._ratio;
    return *this;
}

size_t                  DroidFactory::getRatio(void) const
{
    return _ratio;
}

void                    DroidFactory::setRatio(size_t ratio)
{
    _ratio = ratio;
}