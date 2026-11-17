#include "AE/Core/OctagonDomain.h"
#include <iostream>
#include <stdexcept>
#include <string>
using namespace SVF;
const Variable x(1), y(2), old(3), firstContent(100), secondContent(101);
LinearExpression e(Variable v)
{
    return LinearExpression(v);
}
LinearExpression k(int n)
{
    return LinearExpression(Rational(n));
}
int checks = 0;
void verify(const OctagonDomain& s, const LinearConstraint& q, bool expected,
            const std::string& name)
{
    ++checks;
    if (s.isBottom() || (s.entails(q) == CheckResult::True) != expected)
        throw std::runtime_error(name + ": " + s.toString());
}
int main()
{
    for (auto storage :
            {
                OctagonStorageKind::DenseHalf,
                OctagonStorageKind::SparseFinite,
                OctagonStorageKind::ComponentDense
            })
    {
        OctagonConfig config;
        config.storage = storage;
        auto base = OctagonDomain::top(config);
        base.assignInterval(x, Interval::closed(Rational(0), Rational(10)));
        for (int id = 1; id <= 12; ++id)
        {
            auto s = base;
            const std::string name = std::to_string(id) + ":" + octagonStorageKindName(storage);
            switch (id)
            {
            case 1:
                s.assign(firstContent, e(x));
                s.assign(y, e(firstContent));
                verify(s, equal(e(y), e(x)), true, name);
                break;
            case 2:
                s.assign(firstContent, e(x) + k(1));
                s.assign(y, e(firstContent));
                verify(s, equal(e(y), e(x) + k(1)), true, name);
                break;
            case 3:
            case 4:
            case 12:
            {
                auto other = s;
                s.assign(firstContent, e(x) + k(1));
                other.assign(firstContent, e(x) + k(id == 3 ? 1 : 2));
                s.joinWith(other);
                if (id == 12)
                {
                    other = base;
                    other.assign(firstContent, e(x) + k(3));
                    s.joinWith(other);
                }
                s.assign(y, e(firstContent));
                verify(s, greaterThan(e(y), e(x)), true, name);
                verify(s, lessEqual(e(y), e(x) + k(id == 12 ? 3 : id == 3 ? 1 : 2)), true, name);
                break;
            }
            case 5:
            {
                s.assign(firstContent, e(x));
                auto other = s;
                s.assign(y, e(firstContent) + k(1));
                other.assign(y, e(firstContent) + k(2));
                s.joinWith(other);
                verify(s, greaterThan(e(y), e(x)), true, name);
                verify(s, lessEqual(e(y), e(x) + k(2)), true, name);
                break;
            }
            case 6:
            case 11:
            {
                s.assign(firstContent, e(x));
                auto other = s;
                s.assign(secondContent, e(firstContent) + k(1));
                other.assign(secondContent, e(x) + k(1));
                s.joinWith(other);
                s.assign(y, e(secondContent));
                verify(s, equal(e(y), e(x) + k(1)), true, name);
                break;
            }
            case 7:
            {
                s.assign(firstContent, e(x));
                auto other = s;
                s.assume(lessThan(e(firstContent), k(5)));
                other.assume(greaterEqual(e(firstContent), k(5)));
                verify(s, lessThan(e(x), k(5)), true, name);
                verify(other, greaterEqual(e(x), k(5)), true, name);
                break;
            }
            case 8:
            {
                s.assign(firstContent, e(x));
                s.assign(old, e(firstContent));
                auto other = s;
                s.assign(firstContent, e(x) + k(1));
                other.assign(firstContent, e(x) + k(2));
                s.joinWith(other);
                s.assign(y, e(firstContent));
                verify(s, equal(e(old), e(x)), true, name);
                verify(s, greaterThan(e(y), e(old)), true, name);
                break;
            }
            case 9:
            {
                s.assign(firstContent, e(x));
                s.assign(secondContent, e(x) + k(1));
                auto other = s;
                s.assign(firstContent, e(x) + k(2));
                other.assign(secondContent, e(x) + k(2));
                s.joinWith(other);
                s.assign(y, e(firstContent));
                verify(s, equal(e(y), e(x)), false, name);
                break;
            }
            case 10:
            {
                s.assign(firstContent, e(x));
                auto other = s;
                s.assign(firstContent, e(x) + k(1));
                s.joinWith(other);
                s.assign(y, e(firstContent));
                verify(s, equal(e(y), e(x)), false, name);
                break;
            }
            }
            std::cout << "PASS " << name << '\n';
        }
    }
    std::cout << "checks=" << checks << " scenarios=36\n";
}
