#include "AE/Core/ConvexPolyhedraDomain.h"
#include "AE/Core/OctagonDomain.h"
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace SVF;

void check(bool valid, const char* message)
{
    if (!valid) throw std::runtime_error(message);
}

int checkBasicRelations()
{
    try
    {
        const Variable x(1), y(2);
        const LinearExpression ex(x), ey(y), one(Rational(1));
        const LinearConstraint relation(ex - ey - one, ConstraintKind::Equal);
        for (DomainKind kind :
                {
                    DomainKind::Octagon, DomainKind::ConvexPolyhedra
                })
        {
            auto state = makeNumericalDomain(kind, false);
            check(state->isTop(), "top construction");
            state->assign(x, ey + one);
            check(state->entails(relation) == CheckResult::True, "unbounded affine assignment");
            auto saved = NumericalDomain::deserializeRaw(state->serializeRaw());
            check(saved->isEquivalentTo(*state) == CheckResult::True, "serialization round trip");
            state->forget(x);
            check(state->isTop(), "forget relation");
            check(saved->entails(relation) == CheckResult::True, "copy independence");

            auto left = makeNumericalDomain(kind, false);
            left->assign(y, LinearExpression(Rational(0)));
            left->assign(x, ey + one);
            auto right = makeNumericalDomain(kind, false);
            right->assign(y, LinearExpression(Rational(2)));
            right->assign(x, ey + one);
            auto joined = NumericalDomain::deserializeRaw(left->serializeRaw());
            joined->joinWith(*right);
            check(left->isSubsetOf(*joined) == CheckResult::True, "join covers left");
            check(right->isSubsetOf(*joined) == CheckResult::True, "join covers right");
            check(joined->entails(relation) == CheckResult::True, "join preserves shared relation");
            joined->assume(LinearConstraint(ey - one, ConstraintKind::Equal));
            check(joined->bound(x).isSingleton() && joined->bound(x).singletonValue() == Rational(2),
                  "relational reduction after join");

            auto bottom = makeNumericalDomain(kind, true);
            bottom->joinWith(*left);
            check(bottom->isEquivalentTo(*left) == CheckResult::True, "bottom join identity");
            bottom->assume(LinearConstraint(ey - one, ConstraintKind::Equal));
            check(bottom->isBottom(), "inconsistent constraint produces bottom");

            auto widened = NumericalDomain::deserializeRaw(left->serializeRaw());
            widened->widenWith(*right);
            check(left->isSubsetOf(*widened) == CheckResult::True &&
                  right->isSubsetOf(*widened) == CheckResult::True, "widening covers both states");
            saved->project({x});
            check(saved->bound(x).isTop(), "projection of unconstrained partner");
        }
        std::cout << "native Octagon/Polyhedra contract checks: PASS\n";
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}


using Factory = std::function<std::unique_ptr<NumericalDomain>()>;
const Variable x(1), y(100), z(1000003);
const Variable realX(10, NumericType::real());
const Variable realY(11, NumericType::real());
int passed = 0;
int failed = 0;

LinearExpression e(Variable variable)
{
    return LinearExpression(variable);
}

LinearExpression c(int value)
{
    return LinearExpression(Rational(value));
}

void expectRange(const NumericalDomain& state, Variable variable, int lower, int upper)
{
    check(!state.isBottom(), "expected a nonempty state");
    check(state.bound(variable) == Interval::closed(Rational(lower), Rational(upper)),
          "unexpected variable bounds");
}

void run(const std::string& name, const std::function<void()>& test)
{
    try
    {
        test();
        ++passed;
        std::cout << "PASS " << name << '\n';
    }
    catch (const std::exception& error)
    {
        ++failed;
        std::cerr << "FAIL " << name << ": " << error.what() << '\n';
    }
}

void checkCommonOperations(const std::string& name, const Factory& make)
{
    run(name + "/parallel-swap", [&]
    {
        auto state = make();
        state->assign(x, c(2));
        state->assign(y, c(7));
        state->assignParallel(LinearAssignmentList{{x, e(y)}, {y, e(x)}, {z, e(x) + e(y)}});
        expectRange(*state, x, 7, 7);
        expectRange(*state, y, 2, 2);
        expectRange(*state, z, 9, 9);
    });
    run(name + "/parallel-cycle", [&]
    {
        auto state = make();
        state->assign(x, c(1));
        state->assign(y, c(4));
        state->assign(z, c(9));
        state->assignParallel(LinearAssignmentList{{x, e(y)}, {y, e(z)}, {z, e(x)}});
        expectRange(*state, x, 4, 4);
        expectRange(*state, y, 9, 9);
        expectRange(*state, z, 1, 1);
    });
    run(name + "/self-assignment", [&]
    {
        auto state = make();
        state->assignBound(x, Interval::closed(Rational(-4), Rational(6)));
        state->assign(x, c(3) - e(x));
        expectRange(*state, x, -3, 7);
    });
    run(name + "/backward-shift", [&]
    {
        auto state = make();
        state->assignBound(x, Interval::closed(Rational(8), Rational(12)));
        state->assignBound(y, Interval::closed(Rational(-2), Rational(2)));
        state->substitute(x, e(x) + c(5));
        expectRange(*state, x, 3, 7);
        expectRange(*state, y, -2, 2);
    });
    run(name + "/backward-parallel-swap", [&]
    {
        auto state = make();
        state->assignBound(x, Interval::closed(Rational(2), Rational(4)));
        state->assignBound(y, Interval::closed(Rational(9), Rational(11)));
        state->substituteParallel(LinearAssignmentList{{x, e(y) + c(1)}, {y, e(x) - c(2)}});
        expectRange(*state, x, 11, 13);
        expectRange(*state, y, 1, 3);
    });
    run(name + "/backward-constant", [&]
    {
        auto state = make();
        state->assignBound(x, Interval::closed(Rational(1), Rational(3)));
        auto impossible = NumericalDomain::deserializeRaw(state->serializeRaw());
        impossible->substitute(x, c(8));
        check(impossible->isBottom(), "an impossible assignment has no preimage");
        state->substitute(x, c(2));
        check(state->isTop(), "a permitted constant imposes no pre-state constraint");
    });
    run(name + "/projection", [&]
    {
        auto state = make();
        state->assignBound(x, Interval::closed(Rational(0), Rational(6)));
        state->assignBound(y, Interval::closed(Rational(8), Rational(9)));
        state->project({y});
        check(state->bound(x).isTop(), "a projected variable is unrestricted");
        expectRange(*state, y, 8, 9);
        state->project({});
        check(state->isTop(), "empty projection of a nonempty state is top");
        state->assume(lessThan(c(1), c(0)));
        state->project({});
        check(state->isBottom(), "projection preserves bottom");
    });
    run(name + "/independent-expansion", [&]
    {
        auto state = make();
        state->assignBound(x, Interval::closed(Rational(1), Rational(4)));
        state->expand(x, {y, z});
        expectRange(*state, y, 1, 4);
        expectRange(*state, z, 1, 4);
        state->assumeAll({equal(e(x), c(1)), equal(e(y), c(4)), equal(e(z), c(2))});
        check(!state->isBottom(), "expanded copies need not equal each other");
    });
    run(name + "/fold-bounds", [&]
    {
        auto state = make();
        state->assignBound(x, Interval::closed(Rational(-1), Rational(2)));
        state->assignBound(y, Interval::closed(Rational(5), Rational(8)));
        state->assignBound(z, Interval::closed(Rational(10), Rational(11)));
        state->fold(x, {y});
        expectRange(*state, x, -1, 8);
        expectRange(*state, z, 10, 11);
        check(state->bound(y).isTop(), "fold removes the other representative");
    });
    run(name + "/meet-and-join", [&]
    {
        auto left = make();
        auto right = make();
        left->assignBound(x, Interval::closed(Rational(0), Rational(3)));
        left->assignBound(y, Interval::closed(Rational(2), Rational(4)));
        right->assignBound(x, Interval::closed(Rational(2), Rational(8)));
        right->assignBound(y, Interval::closed(Rational(0), Rational(3)));
        auto joined = NumericalDomain::deserializeRaw(left->serializeRaw());
        joined->joinWith(*right);
        expectRange(*joined, x, 0, 8);
        expectRange(*joined, y, 0, 4);
        check(left->isSubsetOf(*joined) == CheckResult::True, "join covers its left input");
        check(right->isSubsetOf(*joined) == CheckResult::True, "join covers its right input");
        auto met = NumericalDomain::deserializeRaw(left->serializeRaw());
        met->meetWith(*right);
        expectRange(*met, x, 2, 3);
        expectRange(*met, y, 2, 3);
        check(met->isSubsetOf(*left) == CheckResult::True, "meet stays within its left input");
        check(met->isSubsetOf(*right) == CheckResult::True, "meet stays within its right input");
    });
    run(name + "/widen-and-narrow", [&]
    {
        auto previous = make();
        auto next = make();
        previous->assignBound(x, Interval::closed(Rational(0), Rational(1)));
        next->assignBound(x, Interval::closed(Rational(0), Rational(4)));
        auto widened = NumericalDomain::deserializeRaw(previous->serializeRaw());
        widened->widenWith(*next);
        check(previous->isSubsetOf(*widened) == CheckResult::True, "widening covers previous state");
        check(next->isSubsetOf(*widened) == CheckResult::True, "widening covers next state");
        auto narrowed = NumericalDomain::deserializeRaw(widened->serializeRaw());
        narrowed->narrowWith(*next);
        check(next->isSubsetOf(*narrowed) == CheckResult::True, "narrowing retains next state");
        check(narrowed->isSubsetOf(*widened) == CheckResult::True, "narrowing stays within widening");
    });
    run(name + "/integer-strict-bounds", [&]
    {
        auto state = make();
        state->assumeAll({
            greaterThan(e(x), LinearExpression(Rational("2/3"))),
            lessThan(e(x), LinearExpression(Rational("11/3")))});
        expectRange(*state, x, 1, 3);
    });
    run(name + "/real-strict-bounds", [&]
    {
        auto state = make();
        const Rational lower("1/3"), upper("7/3");
        state->assumeAll({
            greaterThan(e(realX), LinearExpression(lower)),
            lessThan(e(realX), LinearExpression(upper))});
        check(state->bound(realX) == Interval(Bound::finite(lower, true), Bound::finite(upper, true)),
              "real strict endpoints remain excluded");
        state->close();
        check(state->bound(realX) == Interval::closed(lower, upper),
              "topological closure includes real endpoints");
    });
    run(name + "/strict-contradiction", [&]
    {
        auto state = make();
        state->assumeAll({lessThan(e(realX), c(0)), greaterEqual(e(realX), c(0))});
        check(state->isBottom(), "strict and non-strict opposite bounds conflict");
    });
    run(name + "/canonical-round-trip", [&]
    {
        auto state = make();
        state->assignBound(x, Interval::closed(Rational(-2), Rational(5)));
        state->assign(y, c(3));
        auto rebuilt = make();
        rebuilt->assumeAll(state->toConstraints());
        check(rebuilt->isEquivalentTo(*state) == CheckResult::True, "constraint round trip");
        auto saved = NumericalDomain::deserializeRaw(state->serializeRaw());
        saved->canonicalize();
        check(saved->isEquivalentTo(*state) == CheckResult::True, "canonicalization preserves values");
        check(saved->hash() == state->hash(), "equivalent canonical states have equal hashes");
        saved->assign(x, c(99));
        expectRange(*state, x, -2, 5);
    });
    run(name + "/large-integer", [&]
    {
        auto state = make();
        const Rational large("18446744073709551619");
        state->assign(x, LinearExpression(large));
        state->assign(y, e(x) + c(3));
        check(state->bound(x) == Interval::singleton(large), "large integer is not truncated");
        check(state->bound(y) == Interval::singleton(large + Rational(3)), "large integer addition");
    });
    run(name + "/disjoint-variable-layouts", [&]
    {
        auto left = make();
        auto right = make();
        left->assign(x, c(2));
        right->assign(z, c(7));
        auto joined = NumericalDomain::deserializeRaw(left->serializeRaw());
        joined->joinWith(*right);
        check(joined->isTop(), "missing coordinates in a join are unrestricted");
        left->meetWith(*right);
        expectRange(*left, x, 2, 2);
        expectRange(*left, z, 7, 7);
    });
}

void checkRelationalOperations(const std::string& name, const Factory& make)
{
    run(name + "/transitive-projection", [&]
    {
        auto state = make();
        state->assign(y, e(x) + c(2));
        state->assign(z, e(y) + c(3));
        state->project({x, z});
        check(!state->isBottom(), "projection remains nonempty");
        check(state->entails(equal(e(z), e(x) + c(5))) == CheckResult::True,
              "projection preserves the relation through the removed variable");
        check(state->bound(x).isTop() && state->bound(y).isTop(), "unbounded and removed variables remain top");
    });
    run(name + "/backward-relation", [&]
    {
        auto state = make();
        state->assume(equal(e(x), e(y) + c(4)));
        state->substitute(x, e(z) + c(1));
        check(state->entails(equal(e(z), e(y) + c(3))) == CheckResult::True, "preimage transfers a relation");
        check(state->bound(x).isTop(), "overwritten pre-state variable is unrestricted");
    });
    run(name + "/backward-cyclic-relation", [&]
    {
        auto state = make();
        state->assume(equal(e(x), e(y) + c(4)));
        state->substituteParallel(LinearAssignmentList{{x, e(y)}, {y, e(x)}});
        check(state->entails(equal(e(y), e(x) + c(4))) == CheckResult::True, "cyclic substitution reads one post-state");
    });
    run(name + "/relational-expansion", [&]
    {
        auto state = make();
        state->assign(x, e(y) + c(2));
        state->expand(x, {z});
        check(state->entails(equal(e(z), e(y) + c(2))) == CheckResult::True, "expansion copies external relations");
        check(state->entails(equal(e(x), e(z))) == CheckResult::True, "shared exact relation implies equality");
        state->fold(x, {z});
        check(state->entails(equal(e(x), e(y) + c(2))) == CheckResult::True, "fold keeps common relation");
    });
    run(name + "/relational-fold", [&]
    {
        auto state = make();
        state->assign(x, e(y) + c(1));
        state->assign(z, e(y) + c(3));
        state->fold(x, {z});
        check(state->bound(e(x) - e(y)) == Interval::closed(Rational(1), Rational(3)),
              "fold joins both relational alternatives");
        check(state->bound(z).isTop(), "fold removes its other coordinate");
    });
    run(name + "/negative-cycle", [&]
    {
        auto state = make();
        state->assumeAll({
            lessEqual(e(x) - e(y), c(1)), lessEqual(e(y) - e(z), c(1)),
            lessEqual(e(z) - e(x), c(-3))});
        check(state->isBottom(), "three inconsistent differences have no solution");
    });
    run(name + "/insertion-order", [&]
    {
        auto first = make();
        auto second = make();
        const auto relation = equal(e(x), e(y) + c(1));
        const auto lower = greaterEqual(e(x), c(0));
        first->assume(relation);
        first->assume(lower);
        second->assume(lower);
        second->assume(relation);
        check(first->isEquivalentTo(*second) == CheckResult::True, "constraint insertion order preserves the set");
        first->canonicalize();
        second->canonicalize();
        check(first->hash() == second->hash(), "constraint order does not affect semantic hash");
    });
    run(name + "/sum-relation", [&]
    {
        auto state = make();
        state->assignBound(x, Interval::closed(Rational(1), Rational(4)));
        state->assume(equal(e(x) + e(y), c(6)));
        expectRange(*state, y, 2, 5);
        check(state->bound(e(x) + e(y)) == Interval::singleton(Rational(6)), "relational expression bound");
    });
}

void checkGenerators()
{
    run("polyhedra/triangle-generators", []
    {
        const std::vector<Variable> variables{realX, realY};
        auto state = ConvexPolyhedraDomain::fromGenerators(variables,
        {   {PolyhedraGeneratorKind::Point, {Rational(0), Rational(0)}},
            {PolyhedraGeneratorKind::Point, {Rational(3), Rational(0)}},
            {PolyhedraGeneratorKind::Point, {Rational(0), Rational(3)}}
        });
        check(state.entails(lessEqual(e(realX) + e(realY), c(3))) == CheckResult::True, "triangle diagonal facet");
        check(state.entails(greaterEqual(e(realX), c(0))) == CheckResult::True, "triangle x facet");
        check(state.entails(greaterEqual(e(realY), c(0))) == CheckResult::True, "triangle y facet");
        auto restored = ConvexPolyhedraDomain::fromGenerators(variables, state.toGenerators(variables));
        check(restored.isEquivalentTo(state) == CheckResult::True, "generator round trip");
    });
    run("polyhedra/open-segment-generators", []
    {
        auto state = ConvexPolyhedraDomain::fromGenerators({realX},
        {   {PolyhedraGeneratorKind::ClosurePoint, {Rational(0)}},
            {PolyhedraGeneratorKind::Point, {Rational(1)}},
            {PolyhedraGeneratorKind::ClosurePoint, {Rational(2)}}
        });
        check(state.bound(realX) == Interval(Bound::finite(Rational(0), true), Bound::finite(Rational(2), true)),
              "closure points do not include endpoints");
        auto restored = ConvexPolyhedraDomain::fromGenerators({realX}, state.toGenerators({realX}));
        check(restored.isEquivalentTo(state) == CheckResult::True, "open generator round trip");
        state.close();
        expectRange(state, realX, 0, 2);
    });
    run("polyhedra/ray-and-line-generators", []
    {
        auto state = ConvexPolyhedraDomain::fromGenerators({realX, realY},
        {   {PolyhedraGeneratorKind::Point, {Rational(2), Rational(0)}},
            {PolyhedraGeneratorKind::Ray, {Rational(1), Rational(0)}},
            {PolyhedraGeneratorKind::Line, {Rational(0), Rational(1)}}
        });
        check(state.bound(realX) == Interval(Bound::finite(Rational(2)), Bound::plusInfinity()),
              "ray retains its lower endpoint");
        check(state.bound(realY).isTop(), "line extends in both directions");
    });
}

int main()
{
    if (checkBasicRelations() != 0)
        ++failed;
    checkCommonOperations("box", [] { return makeNumericalDomain(DomainKind::Box, false); });
    for (auto storage :
            {
                OctagonStorageKind::DenseHalf, OctagonStorageKind::SparseFinite,
                OctagonStorageKind::ComponentDense
            })
    {
        const Factory make = [storage]
        {
            OctagonConfig config;
            config.storage = storage;
            return std::make_unique<OctagonDomain>(OctagonDomain::top(config));
        };
        const std::string name = std::string("octagon/") + octagonStorageKindName(storage);
        checkCommonOperations(name, make);
        checkRelationalOperations(name, make);
    }
    const Factory polyhedra = [] { return makeNumericalDomain(DomainKind::ConvexPolyhedra, false); };
    checkCommonOperations("polyhedra", polyhedra);
    checkRelationalOperations("polyhedra", polyhedra);
    checkGenerators();
    std::cout << "additional scenarios: " << passed << " passed, " << failed << " failed\n";
    return failed ? 1 : 0;
}
