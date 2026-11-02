#include "AE/Core/NumericalDomain.h"
#include <iostream>
#include <stdexcept>
using namespace SVF;

void check(bool valid, const char* message)
{
    if (!valid) throw std::runtime_error(message);
}

int main()
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
