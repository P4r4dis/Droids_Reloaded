#ifndef                     __DROIDMEMORY_HPP__
    #define                 __DROIDMEMORY_HPP__

#include <iostream>

class                       DroidMemory
{
    public:
        DroidMemory(void);
        DroidMemory(const DroidMemory &obj);
        ~DroidMemory(void);

        size_t              getFingerprint(void) const;
        size_t              getExp(void) const;

        void                setFingerprint(size_t fingerPrint);
        void                setExp(size_t exp);

        DroidMemory         &operator+=(const size_t &rhs);
        DroidMemory         &operator+=(const DroidMemory &rhs);
        DroidMemory         &operator<<(const DroidMemory &rhs);
        DroidMemory         &operator>>(DroidMemory &lhs) const;
        DroidMemory         &operator+(const DroidMemory &rhs) const;
        DroidMemory         &operator+(const size_t &rhs) const;
        DroidMemory         &operator=(const DroidMemory &rhs);
        bool                operator==(const DroidMemory &rhs) const;
        bool                operator!=(const DroidMemory &rhs) const;
        bool                operator<(const DroidMemory &rhs) const;
        bool                operator>(const DroidMemory &rhs) const;
        bool                operator<=(const DroidMemory &rhs) const;
    private:
        size_t              Fingerprint;
        size_t              Exp;
};

std::ostream                &operator<<(std::ostream &ostream,
                                        const DroidMemory &rhs);
#endif //                   !__DROIDMEMORY_HPP__