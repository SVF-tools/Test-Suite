// Differential storage test. The oracle is the frozen total-map semantics,
// deliberately independent of the candidate's page and bit encoding.
#include "AE/Core/BoxAddressDomain.h"
#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <random>
#include <stdexcept>

using namespace SVF;
using State = InitializationState;
using Domain = InitializationDomain;

static void check(bool condition, const char* message)
{
    if (!condition) throw std::runtime_error(message);
}

struct Oracle
{
    unsigned fallback;
    std::map<Variable, unsigned> facts;
    unsigned value(Variable v) const
    {
        const auto it = facts.find(v);
        return it == facts.end() ? fallback : it->second;
    }
    void assign(Variable v, unsigned s)
    {
        if (!fallback) return;
        if (!s)
        {
            fallback = 0;
            facts.clear();
        }
        else if (s == fallback) facts.erase(v);
        else facts[v] = s;
    }
    void combine(const Oracle& other, bool join)
    {
        if (!other.fallback)
        {
            if (!join) *this = other;
            return;
        }
        if (!fallback)
        {
            if (join) *this = other;
            return;
        }
        const auto op = [join](unsigned a, unsigned b)
        {
            return join ? a | b : a & b;
        };
        Oracle result{op(fallback, other.fallback), {}};
        for (const auto& item : facts)
            result.assign(item.first, op(item.second, other.value(item.first)));
        for (const auto& item : other.facts)
            result.assign(item.first, op(value(item.first), item.second));
        *this = std::move(result);
    }
    bool leq(const Oracle& other) const
    {
        if (!fallback) return true;
        if ((fallback & other.fallback) != fallback) return false;
        for (const auto& item : facts)
            if ((item.second & other.value(item.first)) != item.second) return false;
        for (const auto& item : other.facts)
            if ((value(item.first) & item.second) != value(item.first)) return false;
        return true;
    }
};

static void verify(const Domain& domain, const Oracle& oracle,
                   const std::vector<Variable>& keys)
{
    check(static_cast<unsigned>(domain.defaultState()) == oracle.fallback, "default");
    check(domain.isBottom() == (oracle.fallback == 0), "global bottom");
    check(domain.isTop() == (oracle.fallback == 3 && oracle.facts.empty()), "global top");
    std::vector<Variable> support;
    for (const auto& item : oracle.facts) support.push_back(item.first);
    check(domain.nonDefaultVariables() == support, "canonical sorted typed support");
    for (const Variable end :
            {
                Variable(0), Variable(64, NumericType::real()),
                Variable(300), Variable(4294967295U)
            })
    {
        const std::vector<Variable> prefix(support.begin(), std::lower_bound(support.begin(), support.end(), end));
        check(domain.nonDefaultVariablesBefore(end) == prefix, "range-limited typed support");
    }
    for (const auto key : keys)
        check(static_cast<unsigned>(domain.value(key)) == oracle.value(key), "lookup");
}

int main()
{
    std::vector<Variable> keys;
    for (unsigned id :
            {
                0U, 1U, 62U, 63U, 64U, 65U, 127U, 128U,
                1000000U, 2147483648U, 4294967295U
            })
        for (const auto type :
                {
                    NumericType::integer(), NumericType::real(),
                    NumericType::ieee(FloatFormat::binary32()),
                    NumericType::ieee(FloatFormat::binary64())
                })
            keys.emplace_back(id, type);
    for (unsigned id = 256; id < 512; ++id) keys.emplace_back(id);
    std::mt19937 rng(0x51f2026U);
    std::vector<Domain> states;
    std::vector<Oracle> oracles;
    for (unsigned d = 0; d < 4; ++d)
    {
        states.push_back(Domain::uniform(static_cast<State>(d)));
        oracles.push_back({d, {}});
    }
    for (unsigned round = 0; round < 12000; ++round)
    {
        const auto a = rng() % states.size(), b = rng() % states.size();
        const auto key = keys[rng() % keys.size()];
        const auto op = rng() % 9;
        if (op < 3)
        {
            const auto value = 1 + rng() % 3;
            states[a].assign(key, static_cast<State>(value));
            oracles[a].assign(key, value);
        }
        else if (op == 3)
        {
            auto copy = states[b];
            auto oracleCopy = oracles[b];
            if (states.size() < 40)
            {
                states.push_back(std::move(copy));
                oracles.push_back(std::move(oracleCopy));
            }
            else
            {
                states[a] = std::move(copy);
                oracles[a] = std::move(oracleCopy);
            }
        }
        else if (op < 8)
        {
            if (op == 4) states[a].joinWith(states[b]);
            if (op == 5) states[a].meetWith(states[b]);
            if (op == 6) states[a].widenWith(states[b]);
            if (op == 7)
            {
                auto next = states[a];
                next.meetWith(states[b]);
                states[a].narrowWith(next);
            }
            oracles[a].combine(oracles[b], op == 4 || op == 6);
        }
        else
        {
            const auto value = rng() % 4;
            states[a] = Domain::uniform(static_cast<State>(value));
            oracles[a] = {value, {}};
        }
        verify(states[a], oracles[a], keys);
        verify(states[b], oracles[b], keys);
        check((states[a].isSubsetOf(states[b]) == CheckResult::True) ==
              oracles[a].leq(oracles[b]), "differential subset");
    }
    // Dense pages and repeated edits of snapshots; sources must stay intact.
    auto dense = Domain::uniform(State::Uninitialized);
    Oracle oracle{1, {}};
    for (auto key : keys)
    {
        dense.assign(key, State::Initialized);
        oracle.assign(key, 2);
    }
    for (auto key : keys)
    {
        auto changed = dense;
        changed.assign(key, State::Uninitialized);
        auto expected = oracle;
        expected.assign(key, 1);
        verify(changed, expected, keys);
        verify(dense, oracle, keys);
    }
    auto bottom = dense;
    bottom.assign(keys.front(), State::Bottom);
    check(bottom.isBottom() && bottom.nonDefaultVariables().empty(), "bottom clears pages");
    std::cout << "PASS: 12000 differential operations, typed IDs, boundary IDs, COW snapshots\n";
}
