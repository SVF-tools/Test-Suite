#include "NativeDomainCheck.h"
#include "AE/Core/PolyhedraDomain.h"
#include "AE/Core/OctagonDomain.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

using namespace SVF;

// Octagon scenarios from IKOS core/test/unit/domain/numeric/octagon.cpp
// at ac7f7c1738976cabc58c6a53413df6e458995c38, cases 1 through 9 in order.
void checkOctagonRegressions(const std::string& name, const OctagonConfig& config)
{
    const Variable saved(21), temporary(22);
    run(name + "/increment-preserves-old-value", [&]
    {
        auto state = OctagonDomain::top(config);
        check(state.isTop(), "fresh octagon is top");
        state.assign(x, c(0));
        state.assume(equal(e(saved), e(x)));
        state.assign(x, e(x) + c(1));
        state.assume(equal(e(y), e(x)));
        state.assume(greaterEqual(e(z), e(x)));
        state.canonicalize();
        expectRange(state, saved, 0, 0);
        expectRange(state, x, 1, 1);
        expectRange(state, y, 1, 1);
        check(state.bound(z) == Interval(Bound::finite(Rational(1)), Bound::plusInfinity()),
              "successor propagates a lower bound");
    });
    run(name + "/propagate-bounds-along-chain", [&]
    {
        auto state = OctagonDomain::top(config);
        state.assumeAll({greaterEqual(e(x), c(0)), greaterEqual(e(y), e(x)),
                         equal(e(z), c(11)), lessThan(e(x), e(z)),
                         lessThan(e(y), e(z)), equal(e(saved), e(y) + c(1))});
        state.canonicalize();
        expectRange(state, x, 0, 10);
        expectRange(state, y, 0, 10);
        expectRange(state, z, 11, 11);
        expectRange(state, saved, 1, 11);
    });
    run(name + "/copy-propagates-contradiction", [&]
    {
        auto state = OctagonDomain::fromConstraints(
            {equal(e(x), c(0)), equal(e(y), c(10)),
             greaterEqual(e(z), e(x)), lessThan(e(z), e(y))}, config);
        state.assign(saved, e(z));
        state.canonicalize();
        auto inconsistent = state;
        inconsistent.assume(lessThan(e(z), c(0)));
        check(inconsistent.isBottom(), "source contradicts its lower bound");
        inconsistent = state;
        inconsistent.assume(lessThan(e(saved), c(0)));
        check(inconsistent.isBottom(), "copy contradicts the same lower bound");
        expectRange(state, saved, 0, 9);
    });
    const auto guardedJoin = [&](bool explicitLimit)
    {
        auto first = OctagonDomain::top(config);
        if (explicitLimit)
            first.assume(greaterEqual(e(y), c(1)));
        first.assign(x, c(0));
        const auto guard = lessThan(e(x), e(y));
        first.assume(guard);
        first.assign(x, e(x) + c(1));
        auto joined = first;
        joined.assume(guard);
        joined.assign(x, e(x) + c(1));
        joined.joinWith(first);
        expectRange(joined, x, 1, 2);
        check(joined.entails(lessEqual(e(x), e(y))) == CheckResult::True,
              "join preserves the common relation");
        check(joined.bound(y) == Interval(Bound::finite(Rational(1)), Bound::plusInfinity()),
              "join keeps the lower bound on the loop limit");
        return joined;
    };
    run(name + "/guarded-increment-join", [&] { guardedJoin(false); });
    run(name + "/guarded-increment-join-and-refine", [&]
    {
        auto joined = guardedJoin(true);
        joined.assume(lessThan(e(x), e(y)));
        expectRange(joined, x, 1, 2);
        check(joined.bound(y) == Interval(Bound::finite(Rational(2)), Bound::plusInfinity()),
              "reapplying the guard raises the lower bound");
    });
    run(name + "/forget-temporaries", [&]
    {
        auto state = OctagonDomain::top(config);
        state.assign(x, c(0));
        state.assume(lessThan(e(x), e(y)));
        state.assign(x, e(x) + c(1));
        state.assign(saved, e(x) + c(2));
        state.assign(z, e(saved) + c(2));
        state.assign(temporary, e(z) + c(4));
        for (Variable removed : {x, y, temporary, saved})
        {
            state.forget(removed);
            check(state.bound(removed).isTop(), "forgotten coordinate is unrestricted");
            expectRange(state, z, 5, 5);
        }
        state.assign(saved, e(z) - c(1));
        expectRange(state, saved, 4, 4);
    });
    run(name + "/refine-through-offset-equality", [&]
    {
        auto state = OctagonDomain::fromConstraints(
            {greaterEqual(e(x), c(0)), lessEqual(e(x), c(10)),
             greaterEqual(e(y), c(1)), lessEqual(e(y), c(11)),
             equal(e(y), e(x) + c(1))}, config);
        state.assume(lessEqual(e(x), c(9)));
        expectRange(state, x, 0, 9);
        expectRange(state, y, 1, 10);
    });
    run(name + "/lockstep-widening", [&]
    {
        auto entry = OctagonDomain::top(config);
        entry.assign(x, c(0));
        entry.assign(y, c(0));
        auto header = entry;
        header.assign(x, e(x) + c(1));
        header.assign(y, e(y) + c(1));
        header.joinWith(entry);
        auto next = header;
        next.assign(x, e(x) + c(1));
        next.assign(y, e(y) + c(1));
        auto reverse = next;
        reverse.widenWith(header);
        check(header.isSubsetOf(reverse) == CheckResult::True &&
              next.isSubsetOf(reverse) == CheckResult::True,
              "reverse widening includes both iterates");
        check(reverse.entails(equal(e(x), e(y))) == CheckResult::True,
              "reverse widening retains equality of the counters");
        header.widenWith(next);
        check(next.isSubsetOf(header) == CheckResult::True, "widening includes the next iteration");
        check(header.entails(equal(e(x), e(y))) == CheckResult::True,
              "widening retains equality of the two counters");
        check(header.bound(x) == Interval(Bound::finite(Rational(0)), Bound::plusInfinity()),
              "widening keeps the lower bound and releases the upper bound");
    });
    run(name + "/guarded-loop-fixpoint", [&]
    {
        auto entry = OctagonDomain::top(config);
        entry.assign(x, c(0));
        entry.assign(y, c(0));
        const auto iterate = [&](OctagonDomain header)
        {
            header.assume(lessEqual(e(x), e(z)));
            header.assign(saved, e(x) + c(1));
            header.assign(temporary, e(y) + c(1));
            header.assign(x, e(saved));
            header.assign(y, e(temporary));
            check(header.entails(lessEqual(e(x), e(z) + c(1))) == CheckResult::True,
                  "successor retains the loop guard with its increment");
            header.forget(saved);
            header.forget(temporary);
            header.joinWith(entry);
            return header;
        };
        auto header = iterate(entry);
        header.widenWith(iterate(header));
        check(header.entails(equal(e(x), e(y))) == CheckResult::True,
              "guarded widening retains equality of the counters");
        const auto next = iterate(header);
        check(next.isSubsetOf(header) == CheckResult::True,
              "widened loop header contains its next iterate");
        auto secondWidening = header;
        secondWidening.widenWith(next);
        check(secondWidening.isEquivalentTo(header) == CheckResult::True,
              "a subsequent widening keeps the loop invariant");
    });
}

// These cases match the named tests in IKOS core/test/unit/domain/numeric/apron/
// polka_polyhedra.cpp and pkgrid_polyhedra_lin_congruences.cpp at
// ac7f7c1738976cabc58c6a53413df6e458995c38. The two files share their fixtures.
using Polyhedra = PolyhedraDomain;
const Variable lowerBounded(23), extra(24);

Interval range(int lower, int upper)
{
    return Interval::closed(Rational(lower), Rational(upper));
}

Polyhedra strip(int lower, int upper)
{
    auto state = Polyhedra::top();
    state.assignBound(x, range(lower, upper));
    return state;
}

void expectEquivalent(const Polyhedra& state, const Polyhedra& expected, const char* message)
{
    check(state.isEquivalentTo(expected) == CheckResult::True, message);
}

void expectSubset(const Polyhedra& left, const Polyhedra& right, bool expected)
{
    check(left.isSubsetOf(right) == (expected ? CheckResult::True : CheckResult::False),
          "unexpected inclusion result");
}

std::array<Polyhedra, 7> orderFixtures()
{
    const auto zero = strip(0, 0);
    auto left = zero;
    left.assignBound(y, range(-1, 1));
    auto right = zero;
    right.assignBound(y, range(0, 2));
    auto withZ = right;
    withZ.assume(lessEqual(e(z), c(0)));
    return {Polyhedra::bottom(), Polyhedra::top(), zero, strip(-1, 1), left, right, withZ};
}

std::pair<Polyhedra, Polyhedra> fiveVariableFixtures()
{
    auto left = Polyhedra::fromConstraints(
        {equal(e(x), c(1)), lessEqual(e(y), c(2)), equal(e(z), c(3)),
         greaterEqual(e(lowerBounded), c(4)), equal(e(extra), c(5))});
    auto right = Polyhedra::fromConstraints(
        {greaterEqual(e(x), c(-1)), lessEqual(e(x), c(1)), lessEqual(e(y), c(3)),
         equal(e(z), c(3)), greaterEqual(e(lowerBounded), c(1))});
    return {left, right};
}

// SVF requires a descending operand to narrow. Exercise rejected inputs in a
// subprocess since the invariant is enforced even in builds without assertions.
int checkInvalidNarrowing(const std::string& input)
{
    const auto top = Polyhedra::top();
    const auto bottom = Polyhedra::bottom();
    const auto bounded = strip(0, 1);
    const auto unbounded = Polyhedra::fromConstraints({greaterEqual(e(x), c(0))});
    if (input != "bottom-top" && input != "bottom-proper" &&
        input != "proper-top" && input != "bounded-unbounded")
        return 2;
    std::cerr << "checking narrowing precondition: " << input << std::endl;
    if (input == "bottom-top")
        bottom.narrow(top);
    else if (input == "bottom-proper")
        bottom.narrow(bounded);
    else if (input == "proper-top")
        unbounded.narrow(top);
    else
        bounded.narrow(unbounded);
    return 0;
}

// Convert the signed remainder to a Euclidean residue for a positive divisor.
// Both transfers operate on the same interval bounds used by the interpreter.
Interval positiveModulus(const Interval& dividend, const Interval& divisor)
{
    const auto signedRemainder = SVF::remainder(dividend, divisor);
    auto nonnegative = signedRemainder;
    auto negative = signedRemainder;
    nonnegative.meetWith(Interval(Bound::finite(Rational(0)), Bound::plusInfinity()));
    negative.meetWith(Interval(Bound::minusInfinity(), Bound::finite(Rational(-1))));
    nonnegative.joinWith(SVF::add(negative, divisor));
    nonnegative.meetWith(Interval::closed(Rational(0), divisor.upper().value() - Rational(1)));
    return nonnegative;
}

void checkPolyhedraArithmetic()
{
    auto state = strip(-1, 1);
    state.assignBound(y, range(1, 2));
    const auto left = state.bound(x);
    const auto right = state.bound(y);
    const auto three = range(3, 3);
    const auto four = range(4, 4);
    struct Transfer
    {
        const char* name;
        Interval (*apply)(const Interval&, const Interval&);
        std::array<Interval, 3> expected;
    };
    const Transfer transfers[] = {
        {"add", SVF::add, {range(0, 3), range(2, 4), range(5, 6)}},
        {"subtract", SVF::subtract, {range(-3, 0), range(-4, -2), range(2, 3)}},
        {"multiply", SVF::multiply, {range(-2, 2), range(-3, 3), range(4, 8)}},
        {"divide", [](const Interval& a, const Interval& b) { return SVF::divide(a, b); },
         {range(-1, 1), range(0, 0), range(2, 4)}},
        {"remainder", SVF::remainder, {range(-1, 1), range(-1, 1), range(0, 1)}},
        {"modulo", positiveModulus, {range(0, 1), range(0, 2), range(0, 1)}},
        {"left shift", SVF::shiftLeft, {range(-4, 4), range(-8, 8), range(8, 16)}},
        {"right shift", SVF::shiftRight, {range(-1, 0), range(-1, 0), range(1, 2)}},
        {"and", SVF::bitwiseAnd, {range(0, 2), range(0, 3), range(0, 2)}},
        {"or", SVF::bitwiseOr, {Interval::top(), Interval::top(), range(0, 7)}},
        {"xor", SVF::bitwiseXor, {Interval::top(), Interval::top(), range(0, 7)}},
    };
    for (const auto& transfer : transfers)
    {
        const std::array<Interval, 3> results = {
            transfer.apply(left, right), transfer.apply(left, three), transfer.apply(four, right)};
        for (std::size_t i = 0; i < results.size(); ++i)
        {
            state.assignBound(z, results[i]);
            const auto result = state.bound(z);
            if (result != transfer.expected[i])
                throw std::runtime_error(std::string(transfer.name) + " operand layout " +
                                         std::to_string(i) + ": got " + result.toString() +
                                         ", expected " + transfer.expected[i].toString());
        }
    }
    state.assign(x, c(-5));
    state.assign(y, c(3));
    const auto dividend = state.bound(x);
    const auto divisor = state.bound(y);
    check(SVF::divide(dividend, divisor) == range(-1, -1), "division truncates toward zero");
    check(SVF::remainder(dividend, divisor) == range(-2, -2), "remainder keeps the dividend sign");
    check(positiveModulus(dividend, divisor) == range(1, 1), "Euclidean residue is nonnegative");
}

// Introduce a witness for x = modulus * witness + residue. Eliminating it
// using the convex domain retains the bounds available in the relaxation.
const Variable residueWitness(25);

Polyhedra withResidueWitness(Polyhedra state, int modulus, int residue)
{
    state.assume(equal(e(x), Rational(modulus) * e(residueWitness) + c(residue)));
    return state;
}

Polyhedra projectCongruence(const Polyhedra& state, int modulus, int residue)
{
    auto projected = withResidueWitness(state, modulus, residue);
    projected.forget(residueWitness);
    return projected;
}

void checkBoundedResidueClass(const Polyhedra& state)
{
    const auto constrained = withResidueWitness(state, 3, 1);
    auto hull = Polyhedra::bottom();
    // For 2 <= x <= 9, the only integer witnesses are 1 and 2.
    for (int witness : {0, 1, 2, 3})
    {
        auto point = constrained;
        point.assume(equal(e(residueWitness), c(witness)));
        point.forget(residueWitness);
        if (witness == 0 || witness == 3)
            check(point.isBottom(), "out-of-range residue witness is infeasible");
        else
            expectRange(point, x, 3 * witness + 1, 3 * witness + 1);
        hull.joinWith(point);
    }
    expectRange(hull, x, 4, 7);
}

struct IntegerExpressionProjection
{
    Interval bounds = Interval::bottom();
    Interval parity = Interval::bottom();
};

IntegerExpressionProjection projectIntegerPoints(
    const Polyhedra& state, const LinearExpression& expression)
{
    IntegerExpressionProjection projection;
    for (int inputX : {1, 2})
        for (int inputY : {3, 4})
        {
            auto point = state;
            point.assumeAll({equal(e(x), c(inputX)), equal(e(y), c(inputY))});
            const auto value = point.bound(expression);
            check(value.isSingleton(), "the expression at a fixed integer point is exact");
            projection.bounds.joinWith(value);
            projection.parity.joinWith(positiveModulus(value, range(2, 2)));
        }
    return projection;
}

void checkPolyhedraRegressions()
{
    const auto top = Polyhedra::top();
    const auto bottom = Polyhedra::bottom();
    run("polyhedra/is-top-and-bottom", [&]
    {
        check(top.isTop() && !top.isBottom() && bottom.isBottom() && !bottom.isTop(),
              "top and bottom are distinct extrema");
        auto state = strip(1, 1);
        check(!state.isTop() && !state.isBottom(), "singleton is a proper element");
        state.assignBound(x, Interval::bottom());
        check(state.isBottom() && !state.isTop(), "empty strong update produces bottom");
    });
    run("polyhedra/set-to-top-and-bottom", [&]
    {
        auto state = top;
        state = bottom;
        check(state.isBottom() && !state.isTop(), "reset to bottom");
        state = top;
        check(state.isTop() && !state.isBottom(), "reset to top");
    });
    run("polyhedra/leq", [&]
    {
        const auto states = orderFixtures();
        const std::array<std::vector<std::size_t>, 7> supersets = {{
            {0, 1, 2, 3, 4, 5, 6}, {1}, {1, 2, 3}, {1, 3},
            {1, 2, 3, 4}, {1, 2, 3, 5}, {1, 2, 3, 5, 6}
        }};
        for (std::size_t i = 0; i < states.size(); ++i)
            for (std::size_t j = 0; j < states.size(); ++j)
                expectSubset(states[i], states[j],
                             std::find(supersets[i].begin(), supersets[i].end(), j) != supersets[i].end());

        auto point = strip(1, 1);
        auto upper = Polyhedra::fromConstraints({lessEqual(e(x), c(1))});
        expectSubset(point, upper, true);
        expectSubset(point, Polyhedra::fromConstraints({lessEqual(e(x), c(0))}), false);
        point.assign(y, c(2));
        expectSubset(point, upper, true);
        upper.assume(lessEqual(e(z), c(4)));
        expectSubset(point, upper, false);
        auto [left, right] = fiveVariableFixtures();
        expectSubset(left, right, true);
        right.assume(greaterEqual(e(lowerBounded), c(5)));
        expectSubset(left, right, false);
    });
    run("polyhedra/equals", []
    {
        const auto states = orderFixtures();
        for (std::size_t i = 0; i < states.size(); ++i)
            for (std::size_t j = 0; j < states.size(); ++j)
                check(states[i].isEquivalentTo(states[j]) ==
                      (i == j ? CheckResult::True : CheckResult::False), "unexpected equality result");
    });
    run("polyhedra/join", [&]
    {
        const auto bounded = strip(0, 1);
        const auto negative = strip(-1, 0);
        const auto checkJoin = [](const Polyhedra& left, const Polyhedra& right, const Polyhedra& expected)
        {
            expectEquivalent(left.join(right), expected, "join result");
            expectEquivalent(right.join(left), expected, "reverse join result");
        };
        checkJoin(top, top, top);
        checkJoin(bottom, bottom, bottom);
        checkJoin(top, bottom, top);
        checkJoin(bounded, top, top);
        checkJoin(bounded, bottom, bounded);
        checkJoin(bounded, bounded, bounded);
        checkJoin(bounded, negative, strip(-1, 1));
        auto withY = negative;
        withY.assign(y, c(0));
        checkJoin(negative, withY, negative);

        auto point = strip(1, 1);
        const auto upper = Polyhedra::fromConstraints({lessEqual(e(x), c(1))});
        checkJoin(point, upper, upper);
        checkJoin(point, Polyhedra::fromConstraints({lessEqual(e(x), c(0))}), upper);
        point.assign(y, c(2));
        checkJoin(point, upper, upper);
        auto withZ = upper;
        withZ.assume(lessEqual(e(z), c(4)));
        checkJoin(point, withZ, upper);

        auto [left, right] = fiveVariableFixtures();
        checkJoin(left, right, right);
        right.assume(greaterEqual(e(lowerBounded), c(5)));
        check(left.join(right).bound(lowerBounded) ==
              Interval(Bound::finite(Rational(4)), Bound::plusInfinity()), "joined lower bound");
    });
    run("polyhedra/widening", [&]
    {
        const auto small = strip(0, 1);
        const auto large = strip(0, 2);
        expectEquivalent(bottom.widen(top), top, "bottom widens to top");
        expectEquivalent(bottom.widen(bottom), bottom, "bottom widening is idempotent");
        expectEquivalent(top.widen(top), top, "top widening is idempotent");
        expectEquivalent(top.widen(bottom), top, "widening with bottom retains top");
        expectEquivalent(small.widen(top), top, "only unconstrained coordinates remain");
        expectEquivalent(top.widen(small), top, "top has no finite bounds to retain");
        expectEquivalent(small.widen(bottom), small, "widening with bottom preserves bounds");
        expectEquivalent(bottom.widen(small), small, "first widening initializes bounds");
        expectEquivalent(small.widen(small), small, "widening a stable state is idempotent");
        const auto unbounded = Polyhedra::fromConstraints({greaterEqual(e(x), c(0))});
        expectEquivalent(small.widen(large), unbounded, "widening drops the increasing upper bound");
        expectEquivalent(large.widen(small), large, "a descending step retains stable bounds");
    });
    run("polyhedra/meet", [&]
    {
        const auto bounded = strip(0, 1);
        const auto negative = strip(-1, 0);
        const auto checkMeet = [](const Polyhedra& left, const Polyhedra& right, const Polyhedra& expected)
        {
            expectEquivalent(left.meet(right), expected, "meet result");
            expectEquivalent(right.meet(left), expected, "reverse meet result");
        };
        checkMeet(top, top, top);
        checkMeet(bottom, bottom, bottom);
        checkMeet(top, bottom, bottom);
        checkMeet(bounded, top, bounded);
        checkMeet(bounded, bottom, bottom);
        checkMeet(bounded, bounded, bounded);
        checkMeet(bounded, negative, strip(0, 0));
        auto withY = bounded;
        withY.assign(y, c(0));
        auto zero = strip(0, 0);
        zero.assign(y, c(0));
        checkMeet(negative, withY, zero);

        auto point = strip(1, 1);
        const auto upper = Polyhedra::fromConstraints({lessEqual(e(x), c(1))});
        checkMeet(point, top, point);
        checkMeet(point, upper, point);
        checkMeet(point, Polyhedra::fromConstraints({lessEqual(e(x), c(0))}), bottom);
        point.assign(y, c(2));
        checkMeet(point, upper, point);
        auto withZ = upper;
        withZ.assume(lessEqual(e(z), c(4)));
        auto intersection = point;
        intersection.assume(lessEqual(e(z), c(4)));
        checkMeet(point, withZ, intersection);

        auto [left, right] = fiveVariableFixtures();
        checkMeet(left, right, left);
        const auto lower = greaterEqual(e(lowerBounded), c(5));
        right.assume(lower);
        auto expected = left;
        expected.assume(lower);
        checkMeet(left, right, expected);
    });
    run("polyhedra/narrowing", [&]
    {
        const auto bounded = strip(0, 1);
        const auto unbounded = Polyhedra::fromConstraints({greaterEqual(e(x), c(0))});
        expectEquivalent(bottom.narrow(bottom), bottom, "bottom narrowing is idempotent");
        expectEquivalent(top.narrow(top), top, "top narrowing is idempotent");
        expectEquivalent(top.narrow(bottom), bottom, "top narrows to bottom");
        expectEquivalent(unbounded.narrow(bottom), bottom, "proper element narrows to bottom");
        expectEquivalent(top.narrow(unbounded), unbounded, "top narrows to a proper element");
        expectEquivalent(unbounded.narrow(unbounded), unbounded, "proper element narrowing is idempotent");
        expectEquivalent(unbounded.narrow(bounded), bounded, "narrowing recovers the upper bound");
    });
    run("polyhedra/assign", [&]
    {
        auto state = top;
        state.assign(x, c(0));
        expectEquivalent(state, strip(0, 0), "constant assignment is a singleton");
        state = bottom;
        state.assign(x, c(0));
        check(state.isBottom(), "assignment preserves bottom");

        state = strip(-1, 1);
        state.assign(y, e(x));
        expectRange(state, y, -1, 1);
        state.assignBound(y, range(1, 2));
        const auto expression = Rational(2) * e(x) - Rational(3) * e(y) + c(1);
        state.assign(z, expression);
        expectRange(state, z, -7, 0);
        check(state.bound(e(z) - expression) == range(0, 0), "assignment retains the affine equality");
    });
    run("polyhedra/apply", checkPolyhedraArithmetic);
    run("polyhedra/add-constraints", []
    {
        const Variable realZ(12, NumericType::real());
        const auto ex = e(realX), ey = e(realY), ez = e(realZ);
        const auto weightedSum = Rational(2) * ex + Rational(3) * ey;
        const auto lower = [](int value)
        {
            return Interval(Bound::finite(Rational(value)), Bound::plusInfinity());
        };
        auto state = Polyhedra::top();
        state.assume(greaterEqual(ex, c(1)));
        check(state.bound(realX) == lower(1), "first lower bound");
        state.assume(greaterEqual(ey, ex + c(2)));
        check(state.bound(realX) == lower(1) && state.bound(realY) == lower(3),
              "affine offset propagates its lower bound");
        state.assume(lessEqual(weightedSum, ez));
        check(state.bound(realX) == lower(1) && state.bound(realY) == lower(3) &&
              state.bound(realZ) == lower(11), "weighted inequality propagates its lower bound");
        auto inconsistent = state;
        inconsistent.assume(lessEqual(ez, Rational(2) * ey));
        check(inconsistent.isBottom(), "incompatible weighted constraints produce bottom");

        state.assume(lessEqual(ez + ex, c(20)));
        check(state.bound(realX) == Interval::closed(Rational(1), Rational("7/3")),
              "projected x bound follows from 6*x + 6 <= 20");
        check(state.bound(realY) == Interval::closed(Rational(3), Rational("17/3")),
              "projected y bound follows from 3*x + 3*y <= 20 and x >= 1");
        expectRange(state, realZ, 11, 19);
        auto redundant = state;
        redundant.assume(lessEqual(Rational(3) * ey, ez));
        expectEquivalent(redundant, state, "an implied weighted inequality preserves the state");
        state.assume(equal(ex, ey));
        check(state.isBottom(), "equality is incompatible with the affine offset");
    });
    run("polyhedra/set", [&]
    {
        auto state = Polyhedra::fromConstraints({equal(e(x), e(y)), greaterEqual(e(y), c(0))});
        state.assignBound(x, range(1, 2));
        expectRange(state, x, 1, 2);
        check(state.bound(e(x) - e(y)) == Interval(Bound::minusInfinity(), Bound::finite(Rational(2))),
              "strong update drops the old relation");
        state.assignBound(x, Interval::bottom());
        check(state.isBottom(), "setting the empty interval produces bottom");

        expectRange(projectCongruence(top, 0, 1), x, 1, 1);
        check(projectCongruence(top, 3, 1).bound(x).isTop(), "an unbounded residue class has no convex bound");
        expectRange(projectCongruence(strip(1, 4), 3, 1), x, 1, 4);
    });
    run("polyhedra/refine", [&]
    {
        auto state = top;
        state.assumeAll({greaterEqual(e(x), c(1)), lessEqual(e(x), c(2))});
        expectRange(state, x, 1, 2);
        state.assumeAll({greaterEqual(e(x), c(3)), lessEqual(e(x), c(4))});
        check(state.isBottom(), "disjoint interval refinement produces bottom");

        expectRange(projectCongruence(top, 0, 1), x, 1, 1);
        check(projectCongruence(top, 3, 1).bound(x).isTop(), "refinement keeps the convex hull of the class");
        state = strip(2, 9);
        expectRange(projectCongruence(state, 3, 1), x, 2, 9);
        checkBoundedResidueClass(state);
        state.meetWith(strip(1, 7));
        expectRange(projectCongruence(state, 3, 1), x, 2, 7);
        checkBoundedResidueClass(state);
    });
    run("polyhedra/forget", []
    {
        auto state = strip(1, 2);
        state.assignBound(y, range(3, 4));
        state.forget(x);
        check(state.bound(x).isTop(), "forgotten coordinate is unrestricted");
        expectRange(state, y, 3, 4);
        state.forget(y);
        check(state.isTop(), "forgetting all coordinates restores top");
    });
    auto state = strip(1, 2);
    state.assignBound(y, range(3, 4));
    const auto odd = Rational(2) * e(x) + c(1);
    const auto mixed = odd - Rational(3) * e(y);
    run("polyhedra/to-interval", [&]
    {
        check(state.bound(odd) == range(3, 5), "project the unary affine expression");
        check(state.bound(mixed) == range(-9, -4), "project the binary affine expression");
    });
    run("polyhedra/to-congruence", [&]
    {
        check(projectIntegerPoints(state, odd).parity == range(1, 1), "unary expression is odd");
        check(projectIntegerPoints(state, mixed).parity == range(0, 1), "both parities are attainable");
    });
    run("polyhedra/to-interval-congruence", [&]
    {
        const auto unary = projectIntegerPoints(state, odd);
        const auto binary = projectIntegerPoints(state, mixed);
        check(unary.bounds == range(3, 5) && unary.parity == range(1, 1),
              "unary expression has the expected bounds and parity");
        check(binary.bounds == range(-9, -4) && binary.parity == range(0, 1),
              "binary expression has the expected bounds and parities");
        check(state.bound(odd) == unary.bounds && state.bound(mixed) == binary.bounds,
              "convex projections recover the attainable extrema");
    });
}
