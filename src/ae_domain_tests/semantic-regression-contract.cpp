#include "AE/Core/BoxAddressDomain.h"

#include <iostream>
#include <stdexcept>

using namespace SVF;

static void check(bool condition, const char* message)
{
    if (!condition)
        throw std::runtime_error(message);
}

static Interval open(const Rational& lower, const Rational& upper)
{
    return Interval(Bound::finite(lower, true), Bound::finite(upper, true));
}

int main()
{
    const Interval positive = remainder(
                                  Interval::closed(Rational(0), Rational(512)),
                                  Interval::singleton(Rational(2)));
    check(positive.contains(Rational(0)), "positive remainder contains zero");
    check(positive.contains(Rational(1)), "positive remainder contains one");
    check(!positive.contains(Rational(2)), "positive remainder excludes divisor");

    const Interval negative = remainder(
                                  Interval::closed(Rational(-512), Rational(0)),
                                  Interval::singleton(Rational(2)));
    check(negative.contains(Rational(-1)), "negative remainder contains minus one");
    check(negative.contains(Rational(0)), "negative remainder contains zero");
    check(!negative.contains(Rational(-2)), "negative remainder excludes divisor");

    const Interval mixed = remainder(
                               Interval::closed(Rational(-512), Rational(512)),
                               Interval::singleton(Rational(2)));
    check(mixed == open(Rational(-2), Rational(2)),
          "mixed-sign remainder bound");

    const Interval dividendLimited = remainder(
                                         Interval::closed(Rational(0), Rational(1)),
                                         Interval::closed(Rational(2), Rational(3)));
    check(dividendLimited == Interval::closed(Rational(0), Rational(1)),
          "dividend-limited endpoint remains attainable");

    const Variable pointer(1), target(2), firstCell(100), secondCell(101);
    const Location firstObject(10), secondObject(11);
    MemoryLayout layout;
    layout.extend(firstObject, firstCell);
    layout.extend(secondObject, secondCell);
    BoxAddressDomain state(BoxDomain::top(), layout, true);
    state.setInterval(secondCell, Interval::singleton(Rational(7)));
    AddressSet pointees = AddressSet::singleton(firstObject);
    pointees.insert(secondObject);
    state.setAddressSet(pointer, pointees);
    state.load(target, pointer);
    check(state.numericalMayBeUninitialized(target),
          "load preserves an uninitialized alias alternative");
    check(state.interval(target) == Interval::singleton(Rational(7)),
          "initialized payload remains conditional on its guard");

    BoxAddressDomain initialized(BoxDomain::top(), layout, true);
    initialized.setInterval(firstCell, Interval::singleton(Rational(7)));
    BoxAddressDomain uninitialized(BoxDomain::top(), layout, true);
    initialized.joinValueFrom(firstCell, uninitialized, firstCell);
    check(initialized.numericalMayBeUninitialized(firstCell),
          "coordinate join preserves uninitialized alternative");
    check(initialized.interval(firstCell) == Interval::singleton(Rational(7)),
          "coordinate join preserves conditional payload");

    std::cout << "PASS: remainder endpoints and load initialization guard\n";
}
