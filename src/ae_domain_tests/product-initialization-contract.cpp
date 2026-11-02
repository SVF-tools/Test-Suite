#include "AE/Core/BoxAddressDomain.h"

#include <iostream>
#include <stdexcept>
#include <vector>

using namespace SVF;

static void check(bool ok, const char* message)
{
    if (!ok)
        throw std::runtime_error(message);
}

int main()
{
    const Variable x(1), y(2), cell(100);
    const Location object(1);
    MemoryLayout layout;
    layout.extend(object, cell);
    const auto fresh = [&]()
    {
        return BoxAddressDomain(BoxDomain::top(), layout, true);
    };
    const Interval seven = Interval::singleton(Rational(7));
    const AddressSet target = AddressSet::singleton(object);
    auto empty = fresh();
    check(empty.interval(x).isBottom(), "fresh numeric projection");
    check(empty.addressSet(x).isBottom(), "fresh pointer projection");
    check(empty.numerical().bound(x).isTop(), "numeric physical default");
    check(empty.addresses().addressSet(x).isTop(), "address physical default");
    auto assigned = empty;
    assigned.setInterval(x, seven);
    auto unknown = empty;
    unknown.setInterval(x, Interval::top());
    unknown.setAddressSet(x, AddressSet::top());
    check(unknown.hasValue(x), "defined Top is a real definition");
    check(!empty.hasValue(x), "uninitialized is not a definition");
    auto joined = empty;
    joined.joinWith(assigned);
    check(joined.interval(x) == seven, "uninitialized join seven");
    auto joinedUnknown = unknown;
    joinedUnknown.joinWith(assigned);
    check(joinedUnknown.interval(x).isTop(), "initialized Top join seven");
    check(joinedUnknown.addressSet(x).isTop(), "initialized address Top preserved");
    check(empty.interval(x).isBottom(), "COW source preserved");
    check(unknown.initializedVariablesBefore(y) == unknown.initializedVariables(),
          "bounded initialization support includes numeric and pointer Top");
    check(unknown.initializedVariablesBefore(x).empty(), "exclusive range boundary");

    auto ptr = fresh();
    ptr.setAddressSet(x, target);
    auto ptrJoin = empty;
    ptrJoin.joinWith(ptr);
    check(ptrJoin.addressSet(x) == target, "empty pointer branch join");
    auto mixed = assigned;
    mixed.joinWith(ptr);
    check(mixed.interval(x) == seven && mixed.addressSet(x) == target,
          "independent union-cell facets");
    mixed.resetValue(x);
    check(!mixed.hasValue(x) && mixed.initializedVariables().empty(),
          "sparse projection removes guards");
    unknown.restoreMissingMemoryFrom(assigned, x);
    check(unknown.interval(x).isTop(), "caller restoration must not overwrite Top");
    auto restored = empty;
    restored.restoreMissingMemoryFrom(assigned, x);
    check(restored.interval(x) == seven, "caller restores missing numeric facet");

    auto memory = fresh();
    memory.setInterval(cell, seven);
    memory.setAddressSet(x, target);
    memory.load(y, x);
    check(memory.interval(y) == seven && memory.addressSet(y).isBottom(), "load guards");
    memory.setInterval(y, Interval::top());
    memory.assignMemory(object, y);
    check(memory.interval(cell).isTop() && memory.hasValue(cell), "store initialized Top");
    memory.assignMemory(object, cell);
    check(memory.interval(cell).isTop() && memory.hasValue(cell), "self-store guards");

    // Exercise product lattice laws over U, I, U|I, Top payloads and two facets.
    auto both = assigned;
    both.setAddressSet(x, target);
    std::vector<BoxAddressDomain> states = {empty, assigned, unknown, joined, ptr, both};
    auto bottom = BoxAddressDomain(BoxDomain::bottom(), layout, true);
    states.push_back(bottom);
    for (const auto& a : states)
    {
        for (const auto& b : states)
        {
            auto ab = a;
            ab.joinWith(b);
            auto ba = b;
            ba.joinWith(a);
            check(ab.isEquivalentTo(ba) == CheckResult::True, "join commutativity");
            check(a.isSubsetOf(ab) == CheckResult::True &&
                  b.isSubsetOf(ab) == CheckResult::True, "join upper bound");
            auto meet = a;
            meet.meetWith(b);
            check(meet.isSubsetOf(a) == CheckResult::True &&
                  meet.isSubsetOf(b) == CheckResult::True, "meet lower bound");
            auto widened = a;
            widened.widenWith(b);
            check(a.isSubsetOf(widened) == CheckResult::True &&
                  b.isSubsetOf(widened) == CheckResult::True, "widen upper bound");
            auto narrowed = ab;
            narrowed.narrowWith(a);
            check(narrowed.isEquivalentTo(a) == CheckResult::True, "narrowing included next");
        }
    }
    std::cout << "PASS: guarded payload, sparse projection, memory and 49 lattice pairs\n";
}
