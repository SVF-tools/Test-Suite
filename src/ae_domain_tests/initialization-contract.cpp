// Standalone preparation fixture; not evidence of AE integration correctness.
#include "AE/Core/BoxAddressDomain.h"

#include <iostream>
#include <stdexcept>
#include <string>

using namespace SVF;

static void require(bool condition, const char* message)
{
    if (!condition)
        throw std::runtime_error(message);
}

int main(int argc, char** argv)
{
    using State = InitializationState;
    using Domain = InitializationDomain;
    if (argc == 2 && std::string(argv[1]) == "--invalid-state")
    {
        std::cerr << "checking invalid initialization state" << std::endl;
        Domain::uniform(static_cast<State>(4));
        return 0;
    }
    const Variable x(1), y(1000000);
    for (unsigned a = 0; a != 4; ++a)
    {
        for (unsigned b = 0; b != 4; ++b)
        {
            const auto lhs = Domain::uniform(static_cast<State>(a));
            const auto rhs = Domain::uniform(static_cast<State>(b));
            auto joined = lhs;
            joined.joinWith(rhs);
            require(joined.value(x) == static_cast<State>(a | b), "uniform join");
            auto met = lhs;
            met.meetWith(rhs);
            require(met.value(x) == static_cast<State>(a & b), "uniform meet");
            require((lhs.isSubsetOf(rhs) == CheckResult::True) == ((a & b) == a),
                    "uniform inclusion");
            auto widened = lhs;
            widened.widenWith(rhs);
            require(widened.isEquivalentTo(joined) == CheckResult::True,
                    "finite-height widening");
        }
    }

    auto fresh = Domain::uniform(State::Uninitialized);
    auto initialized = fresh;
    initialized.assign(x, State::Initialized);
    require(fresh.value(x) == State::Uninitialized, "copy isolation");
    require(initialized.value(y) == State::Uninitialized, "sparse default");
    auto merged = fresh;
    merged.joinWith(initialized);
    require(merged.value(x) == State::Top, "branch initialization join");
    require(merged.value(y) == State::Uninitialized, "untouched branch variable");
    merged.narrowWith(initialized);
    require(merged.isEquivalentTo(initialized) == CheckResult::True, "narrowing");
    auto contradiction = initialized;
    contradiction.meetWith(fresh);
    require(contradiction.isBottom(), "one contradictory key makes state bottom");
    initialized.forget(x);
    require(initialized.value(x) == State::Top, "forget means unknown");
    initialized.assign(x, State::Uninitialized);
    require(initialized.nonDefaultVariables().empty(), "default canonicalization");

    auto top = Domain::top();
    auto clone = top.clone();
    top.assign(y, State::Initialized);
    require(clone->isTop(), "clone isolation");
    top.assign(x, State::Bottom);
    require(top.isBottom(), "assign bottom");
    top.forget(x);
    require(top.isBottom(), "bottom remains unreachable");
    std::cout << "PASS: 16 uniform pairs and sparse/COW/branch contract checks\n";
}
