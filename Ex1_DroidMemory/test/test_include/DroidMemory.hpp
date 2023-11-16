#ifndef                     __DROIDMEMORY_HPP__
    #define                 __DROIDMEMORY_HPP__

#include <iostream>

class                       DroidMemory
{
    public:
        DroidMemory(void);
        ~DroidMemory(void);

        size_t              getFingerprint(void) const;
        size_t              getExp(void) const;

        void                setFingerprint(size_t fingerPrint);
        void                setExp(size_t exp);

        DroidMemory         &operator+=(const size_t &rhs);
        DroidMemory         &operator+=(const DroidMemory &rhs);
    private:
        size_t              Fingerprint;
        size_t              Exp;
};
#endif //                   !__DROIDMEMORY_HPP__