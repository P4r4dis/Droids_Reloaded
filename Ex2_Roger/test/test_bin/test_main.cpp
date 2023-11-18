#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include <criterion/logging.h>
#include <criterion/parameterized.h>
#include <signal.h>

#include "../test_include/Droid.hpp"
#include "../test_include/DroidMemory.hpp"

void    redirect_all_stdout(void) {
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(Droid, test_Droid_constructor_with_parameters, .init = redirect_all_stdout)
{
    {
        Droid  d("Avenger");

        cr_assert(d.getId() == "Avenger");
        cr_assert(d.getEnergy() == 50);
        cr_assert(d.getAttack() == 25);
        cr_assert(d.getToughness() == 15);
        cr_assert(d.getStatus()->compare("Standing by") == 0);
        cr_assert_str_eq(d.getStatus()->data(), "Standing by");
    }

    cr_assert_stdout_eq_str("Droid 'Avenger' Activated\nDroid 'Avenger' Destroyed\n");
}

Test(Droid, test_Droid_copy_Constructor, .init = redirect_all_stdout)
{
    {    
        Droid  d0("Avenger");
        Droid  d(d0);

        cr_assert(d.getId() == "Avenger");
        cr_assert(d.getEnergy() == 50);
        cr_assert(d.getAttack() == 25);
        cr_assert(d.getToughness() == 15);
        cr_assert(d.getStatus()->compare("Standing by") == 0);
        cr_assert_str_eq(d.getStatus()->data(), "Standing by");
    }
    cr_assert_stdout_eq_str("Droid 'Avenger' Activated\n"
    "Droid 'Avenger' Activated, Memory Dumped\n"
    "Droid 'Avenger' Destroyed\n"
    "Droid 'Avenger' Destroyed\n");
}

Test(Droid, test_Droid_setId, .init = redirect_all_stdout)
{
    Droid   d("");

    cr_assert(d.getId() == "");
    d.setId("Droid");
    cr_assert(d.getId() == "Droid");
}

Test(Droid, test_Droid_setEnergy, .init = redirect_all_stdout)
{
    Droid   d("Avenger");

    cr_assert(d.getEnergy() == 50);
    d.setEnergy(100);
    cr_assert(d.getEnergy() == 100);
}

Test(Droid, test_Droid_setStatus, .init = redirect_all_stdout)
{
    Droid   d("Avenger");

    cr_assert_str_eq(d.getStatus()->data(), "Standing by");
    d.setStatus(new std::string("Pending"));
    cr_assert_str_eq(d.getStatus()->data(), "Pending");
    d.setStatus(new std::string("Updated"));
    d.~Droid();
}

Test(Droid, test_Droid_operator_equal_overloading, .init = redirect_all_stdout)
{
    Droid d("Avanger");
    Droid d1("Avenger");

    cr_assert(d.getId() != d1.getId());
    cr_assert(d.getEnergy() == d1.getEnergy());
    cr_assert(d.getAttack() == d1.getAttack());
    cr_assert(d.getToughness() == d1.getToughness());
    cr_assert(d.getStatus()->data() != d1.getStatus()->data());

    d = d1;

    cr_assert(d.getId() == d1.getId());
    cr_assert(d.getEnergy() == d1.getEnergy());
    cr_assert(d.getAttack() == d1.getAttack());
    cr_assert(d.getToughness() == d1.getToughness());
    cr_assert_str_eq(d.getStatus()->data(), d1.getStatus()->data());
}

Test(Droid, test_Droid_left_stream_operator_overloading, .init = redirect_all_stdout)
{
    {
        Droid d("Avenger");

        std::cout << d << std::endl;
    }
    cr_assert_stdout_eq_str(
        "Droid 'Avenger' Activated\n"
        "Droid 'Avenger', Standing by, 50\n"
        "Droid 'Avenger' Destroyed\n");
}

Test(Droid, test_Droid_reload_with_left_stream_operator_overloading, .init = redirect_all_stdout)
{
    {
        Droid d("Avenger");
        size_t Durasel = 200;
        cr_assert(d.getEnergy() == 50);
        d << Durasel;
        cr_assert(d.getEnergy() == 100);
        cr_assert(Durasel == 150);
        std::cout << d << std::endl;
        d.setEnergy(200);
        d << Durasel;
        cr_assert(d.getEnergy() == 100);
    }
    cr_assert_stdout_eq_str(
        "Droid 'Avenger' Activated\n"
        "Droid 'Avenger', Standing by, 100\n"
        "Droid 'Avenger' Destroyed\n");
}

Test(Droid, test_Droid_equal_equal_operator_overloading, .init = redirect_all_stdout)
{
    {
        Droid d("Avenger");
        Droid d2("Avenger");
        cr_assert_eq(d, d);
    }
    cr_assert_stdout_eq_str(
        "Droid 'Avenger' Activated\n"
        "Droid 'Avenger' Activated\n"
        "Droid 'Avenger' Destroyed\n"
        "Droid 'Avenger' Destroyed\n");
}

Test(Droid, test_Droid_different_operator_overloading, .init = redirect_all_stdout)
{
    {
        Droid d("Avenger");
        d.setStatus(new std::string("Pending"));
        Droid d2("Avenger");
        cr_assert_neq(d, d2);
    }
    cr_assert_stdout_eq_str(
        "Droid 'Avenger' Activated\n"
        "Droid 'Avenger' Activated\n"
        "Droid 'Avenger' Destroyed\n"
        "Droid 'Avenger' Destroyed\n");
}

Test(Droid, test_Droid_battleData, .init = redirect_all_stdout)
{
    {
        Droid d("Avenger");

        cr_assert(not(zero(d.getBattleData())));
        cr_assert(d.getBattleData()->getExp() == 0);
    }

}

Test(Droid, test_Droid_main_function, .init = redirect_all_stdout)
{
    {
        Droid d("Avenger");
        Droid d1("Avenger");
        size_t Durasel = 200;

        std::cout << d <<std::endl;
        std::cout << d1 <<std::endl;
        d = d1;
        d.setStatus(new std::string("Kill Kill Kill!"));
        d << Durasel;
        std::cout << d << "--" << Durasel << std::endl;
        Droid d2 = d;
        d.setId("Rex");
        std::cout << (d2 != d) << std::endl;
    }
    cr_assert_stdout_eq_str(
        "Droid 'Avenger' Activated\n"
        "Droid 'Avenger' Activated\n"
        "Droid 'Avenger', Standing by, 50\n"
        "Droid 'Avenger', Standing by, 50\n"
        "Droid 'Avenger', Kill Kill Kill!, 100--150\n"
        "Droid 'Avenger' Activated, Memory Dumped\n"
        "0\n"
        "Droid 'Avenger' Destroyed\n"
        "Droid 'Avenger' Destroyed\n"
        "Droid 'Rex' Destroyed\n");
}

Test(DroidMemory, test_DroidMemory_constructor_without_parameters)//, .init = redirect_all_stdout)
{
    {
        DroidMemory mem1;

        cr_assert(mem1.getFingerprint() > 0 && mem1.getFingerprint() <= SIZE_MAX);
        mem1.setFingerprint(1804289357);
        cr_assert(mem1.getFingerprint() == 1804289357);

        cr_assert(mem1.getExp() == 0);
        mem1.setExp(42);
        cr_assert(mem1.getExp() == 42);
    }
}

Test(DroidMemory, test_DroidMemory_copy_constructor)//, .init = redirect_all_stdout)
{
    {
        DroidMemory mem1;

        cr_assert(mem1.getFingerprint() > 0 && mem1.getFingerprint() <= SIZE_MAX);
        mem1.setFingerprint(1804289357);
        cr_assert(mem1.getFingerprint() == 1804289357);

        cr_assert(mem1.getExp() == 0);
        mem1.setExp(42);
        cr_assert(mem1.getExp() == 42);

        DroidMemory mem2(mem1);
        cr_assert(mem2.getFingerprint() == 1804289357);
        cr_assert(mem2.getExp() == 42);
    }
}

Test(DroidMemory, test_DroidMemory_Plus_Equal_operator_overloading)//, .init = redirect_all_stdout)
{
    {
        DroidMemory mem1;

        mem1 += 42;
        cr_assert(mem1.getExp() == 42);
        cr_assert(mem1.getFingerprint() == 1804289357);

        DroidMemory mem2;
        DroidMemory mem3;
        mem3.setExp(42);
        size_t result = (mem2.getFingerprint() ^ mem3.getFingerprint());
        mem2 += mem3;
        cr_assert(mem2.getFingerprint() == result);
        
        size_t result2 = (mem1.getFingerprint() ^ mem2.getFingerprint() ^ mem3.getFingerprint());
        mem1 += mem2 += mem3;
        cr_assert(mem1.getFingerprint() == result2);
    }
}

Test(DroidMemory, test_DroidMemory_Equal_operator_overloading)//, .init = redirect_all_stdout)
{
    {
        DroidMemory mem1;
        DroidMemory mem2;
        mem1 += 42;

        mem2 = mem1;
        cr_assert(mem2.getExp() == mem1.getExp());
        cr_assert(mem2.getFingerprint() == mem1.getFingerprint());
    }
}

Test(DroidMemory, test_DroidMemory_left_insertion__operator_overloading, .init = redirect_all_stdout)
{
    {
        DroidMemory mem1;
        mem1 += 42;

        DroidMemory mem2 = mem1;
        std::cout << mem1 << std::endl;

        DroidMemory mem3;
        mem3 << mem1;
        mem3 >> mem1;
        mem3 << mem1;
        std::cout << mem3 << std::endl;
    }
    cr_assert_stdout_eq_str("DroidMemory '1804289357', 42\n"
    "DroidMemory '1804289357', 126\n");
}

Test(DroidMemory, test_DroidMemory_Plus_operator_overloading)//, .init = redirect_all_stdout)
{
    {
        DroidMemory mem1;
        size_t var = 42;
        mem1 = mem1 + var + var;
        cr_assert(mem1.getExp() == 84);
        size_t result = mem1.getFingerprint() ^ mem1.getFingerprint();
        mem1.setFingerprint(mem1.getFingerprint() ^ mem1.getFingerprint());
        cr_assert(mem1.getFingerprint() == result);

        DroidMemory mem2;
        size_t result2 = mem2.getFingerprint() ^ mem1.getFingerprint() ^ mem1.getFingerprint();
        mem2 = mem2 + mem1 + mem1;
        cr_assert(mem2.getExp() == 168);
        cr_assert(mem2.getFingerprint() == result2);
    }
}

Test(DroidMemory, test_DroidMemory_right_insertion__operator_overloading, .init = redirect_all_stdout)
{
    {
        DroidMemory mem1;
        mem1 += 42;

        DroidMemory mem2 = mem1;
        std::cout << mem1 << std::endl;

        DroidMemory mem3;
        mem3 << mem1;
        mem3 >> mem1;
        mem3 << mem1;
        std::cout << mem3 << std::endl;
        std::cout << mem1 << std::endl;
    }
    cr_assert_stdout_eq_str("DroidMemory '1804289357', 42\n"
    "DroidMemory '1804289357', 126\n"
    "DroidMemory '846930886', 84\n");
}

Test(DroidMemory, test_DroidMemory_Equal_Equal_operator_overloading)//, .init = redirect_all_stdout)
{
    {
        DroidMemory mem1;
        mem1 += 42;

        DroidMemory mem2;

        cr_assert(not(eq(type(DroidMemory), mem1, mem2)));
        mem2 = mem1;
        cr_assert_eq(mem1, mem2);
    }
}

Test(DroidMemory, test_DroidMemory_Different_operator_overloading)//, .init = redirect_all_stdout)
{
    {
        DroidMemory mem1;
        DroidMemory mem2;

        mem1 = mem2;
        cr_assert_eq(mem1, mem2);
        mem1 += 42;
        cr_assert_neq(mem1, mem2);
    }
}

Test(DroidMemory, test_DroidMemory_lower_operator_overloading)//, .init = redirect_all_stdout)
{
    {
        DroidMemory mem1;
        DroidMemory mem2;

        mem1 += 42;
        cr_assert_lt(mem2, mem1);
    }
}

Test(DroidMemory, test_DroidMemory_mainFunction, .init = redirect_all_stdout)
{
    {
        DroidMemory mem1;
        mem1 += 42;

        DroidMemory mem2 = mem1;
        std::cout << mem1 << std::endl;

        DroidMemory mem3;
        mem3 << mem1;
        mem3 >> mem1;
        mem3 << mem1;
        std::cout << mem3 << std::endl;
        std::cout << mem1 << std::endl;
    }
    cr_assert_stdout_eq_str("DroidMemory '1804289357', 42\n"
    "DroidMemory '1804289357', 126\n"
    "DroidMemory '846930886', 84\n");
}