#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include <criterion/logging.h>
#include <criterion/parameterized.h>
#include <signal.h>

#include "../test_include/Droid.hpp"
#include "../test_include/DroidMemory.hpp"
#include "../test_include/Carrier.hpp"

void    redirect_all_stdout(void) {
    cr_redirect_stdout();
    cr_redirect_stderr();
}

static void testMemory()
{
    DroidMemory mem1;
    mem1 += 42;
    std::cout << mem1 << std::endl;
    DroidMemory mem2;
    mem2 << mem1;
    mem2 >> mem1;
    mem2 << mem1;
    std::cout << mem2 << std::endl;
    std::cout << mem1 << std::endl;
    DroidMemory mem3 = mem1;
    DroidMemory mem4;
    mem4 = mem1 + mem3;
}

static void testDroids()
{
    Droid d("rudolf");
    Droid d2("gaston");
    size_t DuraSell = 40;

    d << DuraSell;
    d.setStatus (new std::string("having some reset"));
    d2.setStatus(new std::string("having some reset!"));
    if (d2 != d && !(d == d2))
        std::cout << "a droid is a droid, all its matter is what it's doing" << std::endl;
    
    d.setStatus (new std::string("having some reset"));
    d2.setStatus(new std::string("having some reset"));
    d(new std::string("take a coffee"), 20);
    std::cout << d << std::endl;
    while (d(new std::string("Patrol around"), 20))
    {
        if (!d(new std::string("Shoot some ennemies"), 50))
        {
            d(new std::string("Run Away"), 20);
        }
        std::cout << d << std::endl;
    }
    std::cout << d << std::endl;
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

        cr_assert(d.getId() == d0.getId());
        cr_assert(d.getEnergy() == d0.getEnergy());
        cr_assert(d.getAttack() == d0.getAttack());
        cr_assert(d.getToughness() == d0.getToughness());
        cr_assert_str_eq(d.getStatus()->data(), d0.getStatus()->data());
        cr_assert(d.getBattleData()->getExp() == d0.getBattleData()->getExp());
        cr_assert(d.getBattleData()->getFingerprint() == d0.getBattleData()->getFingerprint());

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
    cr_assert(d.getBattleData()->getExp() == d1.getBattleData()->getExp());
    cr_assert(d.getBattleData()->getFingerprint() == d1.getBattleData()->getFingerprint());

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
        d.getBattleData()->setExp(42);
        cr_assert(d.getBattleData()->getExp() == 42);
        DroidMemory *mem = new DroidMemory();
        d.setBattleData(mem);
        cr_assert(d.getBattleData()->getExp() == 0);
    }

}

Test(Droid, test_Droid_operator_brackets_overloading, .init = redirect_all_stdout)
{
    {
        Droid d("rudolf");
        size_t DuraSell = 40;

        d << DuraSell;

        d.setStatus(new std::string("having some reset"));
        d(new std::string("take a coffee"), 20);
        std::cout << d << std::endl;

        d.setEnergy(0);
        d.setStatus(new std::string("having some reset"));
        d(new std::string("take a coffee"), 20);
        std::cout << d << std::endl;

        d.setEnergy(100);
        d.setStatus(new std::string("having some reset"));
        d(new std::string("take a coffee"), 20);
        std::cout << d << std::endl;
    }
    cr_assert_stdout_eq_str(
        "Droid 'rudolf' Activated\n"
        "Droid 'rudolf', take a coffee - Failed!, 80\n"
        "Droid 'rudolf', Battery Low, 0\n"
        "Droid 'rudolf', take a coffee - Completed!, 90\n"
        "Droid 'rudolf' Destroyed\n");
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

Test(DroidMemory, test_DroidMemory_upper_operator_overloading)//, .init = redirect_all_stdout)
{
    {
        DroidMemory mem1;
        DroidMemory mem2;

        mem1 += 42;
        cr_assert_gt(mem1, mem2);
    }
}

Test(DroidMemory, test_DroidMemory_lowerOrEqual_operator_overloading)//, .init = redirect_all_stdout)
{
    {
        DroidMemory mem1;
        DroidMemory mem2;

        mem1 += 42;
        cr_assert_leq(mem2, mem1);
        mem2 = mem1;
        cr_assert_leq(mem2, mem1);
    }
}

Test(DroidMemory, test_DroidMemory_upperOrEqual_operator_overloading)//, .init = redirect_all_stdout)
{
    {
        DroidMemory mem1;
        DroidMemory mem2;

        mem1 += 42;
        cr_assert_geq(mem1, mem2);
        mem2 = mem1;
        cr_assert_geq(mem2, mem1);
    }
}

Test(DroidMemory, test_DroidMemory_comparison_operators)
{
    DroidMemory mem1;
    DroidMemory mem2;
    
    mem1 += 42;

    cr_assert_lt(mem2, mem1);  // mem2 < mem1
    cr_assert_leq(mem2, mem1); // mem2 <= mem1
    cr_assert_gt(mem1, mem2);  // mem1 > mem2
    cr_assert_geq(mem1, mem2); // mem1 >= mem2

    cr_assert_lt(mem2, 50);     // mem2 < 50
    cr_assert_leq(mem2, 50);    // mem2 <= 50
    cr_assert_gt(mem1, 30);     // mem1 > 30
    cr_assert_geq(mem1, 30);    // mem1 >= 30
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

Test(Ex2, test_main_Function, .init = redirect_all_stdout)
{
    {
        testMemory();
        testDroids();
    }
    cr_assert_stdout_eq_str(
    "DroidMemory '1804289357', 42\n"
    "DroidMemory '1804289357', 126\n"
    "DroidMemory '846930886', 84\n"
    "Droid 'rudolf' Activated\n"
    "Droid 'gaston' Activated\n"
    "a droid is a droid, all its matter is what it's doing\n"
    "Droid 'rudolf', take a coffee - Failed!, 80\n"
    "Droid 'rudolf', Run Away - Completed!, 50\n"
    "Droid 'rudolf', Shoot some ennemies - Completed!, 30\n"
    "Droid 'rudolf', Shoot some ennemies - Completed!, 10\n"
    "Droid 'rudolf', Battery Low, 0\n"
    "Droid 'gaston' Destroyed\n"
    "Droid 'rudolf' Destroyed\n"
    );
}

Test(Carrier, test_Carrier_construction, .init = redirect_all_stdout)
{
    {
        Carrier c("HellExpress");

        cr_assert(c.getId() == "HellExpress");
        c.setId("HellExpress2");
        cr_assert(c.getId() == "HellExpress2");

        cr_assert(c.getEnergy() == 300);
        c.setEnergy(301);
        cr_assert(c.getEnergy() == 301);

        cr_assert(c.getAttack() == 100);
        cr_assert(c.getToughness() == 90);

        cr_assert(c.getSpeed() == 0);
        c.setSpeed(100);
        cr_assert(c.getSpeed() == 100);
        c.setSpeed(0);

        Droid *d1 = new Droid("Commander");
        Droid *d2 = new Droid("Sergent");
        Droid *d3 = new Droid("Troufiont");
        Droid *d4 = new Droid("Groupie");
        Droid *d5 = new Droid("BeerHolder");

        cr_assert(c.getNbDroid() == 0);
        for (size_t i = 0; i < 5; i++)
        {
            cr_assert(zero(type(Droid *), c.getDroid(i)));
            switch (i)
            {
                case 0:
                    c.setDroid(i, d1);
                    cr_assert(c.getNbDroid() == 1);
                    break;
                case 1:
                    c.setDroid(i, d2);
                    cr_assert(c.getNbDroid() == 2);
                    break;
                case 2:
                    c.setDroid(i, d3);
                    cr_assert(c.getNbDroid() == 3);
                    break;
                case 3:
                    c.setDroid(i, d4);
                    cr_assert(c.getNbDroid() == 4);
                    break;
                case 4:
                    c.setDroid(i, d5);
                    cr_assert(c.getNbDroid() == 5);
                    break;
            }
            cr_assert(not(zero(type(Droid *), c.getDroid(i))));
        }
        c.setDroid(0, d1);
        cr_assert(c.getNbDroid() == 5);
        cr_assert(c.getSpeed() == 50);
    }
    cr_assert_stdout_eq_str(
    "Droid 'Commander' Activated\n"
    "Droid 'Sergent' Activated\n"
    "Droid 'Troufiont' Activated\n"
    "Droid 'Groupie' Activated\n"
    "Droid 'BeerHolder' Activated\n"
    "Droid 'Commander' Destroyed\n"
    "Droid 'Sergent' Destroyed\n"
    "Droid 'Troufiont' Destroyed\n"
    "Droid 'Groupie' Destroyed\n"
    "Droid 'BeerHolder' Destroyed\n");
}

Test(Carrier, test_Carrier_left_stream_operator_overloading, .init = redirect_all_stdout)
{
    {    
        Carrier c("HellExpress");

        Droid *d1 = new Droid("Commander");
        Droid *d2 = new Droid("Sergent");
        Droid *d3 = new Droid("Troufiont");
        Droid *d4 = new Droid("Groupie");
        Droid *d5 = new Droid("BeerHolder");

        for (size_t i = 0; i < 5; i++)
        {
            cr_assert(zero(type(Droid *), c.getDroid(i)));
        }

        c << d1 << d2 << d3 << d4 << d5;

        for (size_t i = 0; i < 5; i++)
        {
            cr_assert(not(zero(type(Droid *), c.getDroid(i))));
        }

        std::cout << c.getSpeed() << d1 << std::endl;
    }
    cr_assert_stdout_eq_str(
    "Droid 'Commander' Activated\n"
    "Droid 'Sergent' Activated\n"
    "Droid 'Troufiont' Activated\n"
    "Droid 'Groupie' Activated\n"
    "Droid 'BeerHolder' Activated\n"
    "500\n"
    "Droid 'Commander' Destroyed\n"
    "Droid 'Sergent' Destroyed\n"
    "Droid 'Troufiont' Destroyed\n"
    "Droid 'Groupie' Destroyed\n"
    "Droid 'BeerHolder' Destroyed\n"
    );
}


Test(Carrier, test_Carrier_right_stream_operator_overloading, .init = redirect_all_stdout)
{
    {    
        Carrier c("HellExpress");

        Droid *d1 = new Droid("Commander");
        Droid *d2 = new Droid("Sergent");
        Droid *d3 = new Droid("Troufiont");
        Droid *d4 = new Droid("Groupie");
        Droid *d5 = new Droid("BeerHolder");

        for (size_t i = 0; i < 5; i++)
        {
            cr_assert(zero(type(Droid *), c.getDroid(i)));
        }

        c << d1 << d2 << d3 << d4 << d5;

        for (size_t i = 0; i < 5; i++)
        {
            cr_assert(not(zero(type(Droid *), c.getDroid(i))));
        }

        std::cout << c.getSpeed() << d1 << std::endl;
        c >> d1 >> d2 >> d3;
        std::cout << c.getSpeed() << std::endl;
        cr_assert(c.getSpeed() == 80);
        for (size_t i = 0; i < 5; i++)
        {
            if (c.getDroid(i))
                cr_assert(not(zero(type(Droid *), c.getDroid(i))));
            else
                cr_assert(zero(type(Droid *), c.getDroid(i)));

        }
    }
    cr_assert_stdout_eq_str(
    "Droid 'Commander' Activated\n"
    "Droid 'Sergent' Activated\n"
    "Droid 'Troufiont' Activated\n"
    "Droid 'Groupie' Activated\n"
    "Droid 'BeerHolder' Activated\n"
    "500\n"
    "80\n"
    "Droid 'Groupie' Destroyed\n"
    "Droid 'BeerHolder' Destroyed\n"
    );
}