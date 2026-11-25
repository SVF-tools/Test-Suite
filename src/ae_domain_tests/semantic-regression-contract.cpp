#include "AE/Core/BoxAddressDomain.h"

#include <cstdint>
#include <iostream>
#include <limits>
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

static void checkIntegerAndIntervalArithmetic()
{
    const Rational smallest(std::numeric_limits<std::int64_t>::min());
    const Rational largest(std::numeric_limits<std::int64_t>::max());
    const Rational firstWide("9223372036854775808");
    const Rational one(1);
    check(-smallest == firstWide, "negating INT64_MIN preserves the exact result");
    check(largest + one == firstWide, "integer addition beyond INT64_MAX remains exact");
    check(smallest - one == -firstWide - one, "integer subtraction below INT64_MIN remains exact");
    check(smallest - smallest == Rational(0), "INT64_MIN minus itself is zero");
    check(smallest * Rational(-1) == firstWide, "integer multiplication remains exact");
    check(smallest / Rational(-1) == firstWide, "integer division remains exact");
    check((firstWide - one).toInt64() == std::numeric_limits<std::int64_t>::max(),
          "a wide integer can return to the 64-bit range");

    const auto exact = [](std::int64_t value)
    {
        return Interval::singleton(Rational(value));
    };
    const Interval machineRange = Interval::closed(smallest, largest);
    const Interval unit = exact(1);
    const Interval minimum = Interval::singleton(smallest);
    check(subtract(unit, machineRange) == Interval::closed(smallest + Rational(2), firstWide + one),
          "interval subtraction preserves the wide upper endpoint");
    check(subtract(machineRange, unit) == Interval::closed(smallest - one, largest - one),
          "interval subtraction preserves the wide lower endpoint");
    check(multiply(unit, machineRange) == machineRange, "multiplication by one preserves the interval");
    check(divide(minimum, exact(-1)) == Interval::singleton(firstWide),
          "interval division preserves the wide result");
    check(remainder(minimum, exact(-1)).isZero(), "INT64_MIN has zero remainder modulo minus one");

    check(divide(exact(4), Interval::bottom()).isBottom(), "division propagates bottom");
    check(divide(exact(-3), exact(2)) == exact(-1), "signed division rounds towards zero");
    check(remainder(exact(-3), exact(2)) == exact(-1), "remainder keeps the dividend's sign");
    check(shiftLeft(exact(2), exact(3)) == exact(16), "left shift multiplies by a power of two");
    check(shiftRight(exact(-15), exact(2)) == exact(-4), "arithmetic shift preserves the sign");
    check(bitwiseAnd(exact(-3), exact(2)) == exact(0), "bitwise and of singleton intervals");
    check(bitwiseOr(exact(-3), exact(2)) == exact(-1), "bitwise or of singleton intervals");
    check(bitwiseXor(exact(3), exact(2)) == exact(1), "bitwise xor of singleton intervals");
}

static void checkLoadsFromDistinctObjects()
{
    const Variable sourceA(1), sourceB(2), pointerA(3), pointerB(4);
    const Variable contentA(7, NumericType::integer(), Variable::Role::ObjectContent);
    const Variable contentB(8, NumericType::integer(), Variable::Role::ObjectContent);
    const Location cellA(7), cellB(8);
    const Interval intervalA = Interval::closed(Rational(1), Rational(3));
    const Interval intervalB = Interval::closed(Rational(2), Rational(7));
    const MemoryLayout layout({{cellA, contentA}, {cellB, contentB}});
    BoxAddressDomain state(BoxDomain::top(), layout);
    state.setInterval(sourceA, intervalA);
    state.setInterval(sourceB, intervalB);
    state.setAddressSet(pointerA, AddressSet::singleton(cellA));
    state.setAddressSet(pointerB, AddressSet::singleton(cellB));
    state.assignMemory(cellA, sourceA);
    state.assignMemory(cellB, sourceB);
    state.load(Variable(5), pointerA);
    state.load(Variable(6), pointerB);
    check(state.interval(Variable(5)) == intervalA, "first load reads the first object's interval");
    check(state.interval(Variable(6)) == intervalB, "second load reads the second object's interval");
}

int main()
{
    checkIntegerAndIntervalArithmetic();
    checkLoadsFromDistinctObjects();

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
