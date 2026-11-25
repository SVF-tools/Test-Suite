// Run this same operation stream against frozen and optimized production
// libraries. Digest logical guards/projections/subsets, not physical storage.
#include "AE/Core/BoxAddressDomain.h"
#include <cstdint>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

using namespace SVF;
static std::uint64_t digest = 14695981039346656037ULL;
static void add(const std::string& text)
{
    for (unsigned char c : text)
    {
        digest ^= c;
        digest *= 1099511628211ULL;
    }
    digest ^= 255;
    digest *= 1099511628211ULL;
}
static void observe(const BoxAddressDomain& s, const std::vector<Variable>& keys)
{
    add(s.isBottom() ? "bottom" : "reachable");
    if (s.isBottom()) return;
    for (auto key : keys)
    {
        add(std::to_string(static_cast<unsigned>(s.numericalInitialization().value(key))));
        add(std::to_string(static_cast<unsigned>(s.addressInitialization().value(key))));
        add(s.interval(key).toString());
        add(s.addressSet(key).toString());
        add(s.hasValue(key) ? "present" : "absent");
    }
    add(s.lifetimes().toString());
}

int main()
{
    std::vector<Variable> keys;
    for (unsigned id :
            {
                0U, 1U, 7U, 8U, 15U, 16U, 63U, 64U, 127U, 128U,
                1000000U, 4294967295U
            }) keys.emplace_back(id);
    for (unsigned id = 256; id < 352; ++id)
        keys.emplace_back(id, id % 2 ? NumericType::real() : NumericType::integer());
    const auto fresh = [] { return BoxAddressDomain(BoxDomain::top(), MemoryLayout(), true); };
    std::vector<BoxAddressDomain> states(24, fresh());
    std::mt19937 rng(0x513512U);
    for (unsigned round = 0; round < 8000; ++round)
    {
        const auto a = rng() % states.size(), b = rng() % states.size();
        const auto key = keys[rng() % keys.size()];
        const auto op = rng() % 16;
        const auto n = static_cast<int>(rng() % 19) - 9;
        const auto interval = Interval::singleton(Rational(n));
        if (op == 0) states[a].setInterval(key, interval);
        if (op == 1) states[a].setInterval(key, Interval::top());
        if (op == 2) states[a].setInterval(key, Interval::bottom());
        if (op == 3) states[a].setAddressSet(key, AddressSet::singleton(Location(rng()%64)));
        if (op == 4) states[a].setAddressSet(key, AddressSet::top());
        if (op == 5) states[a].setAddressSet(key, AddressSet::bottom());
        if (op == 6) states[a].joinWith(states[b]);
        if (op == 7) states[a].meetWith(states[b]);
        if (op == 8) states[a].widenWith(states[b]);
        if (op == 9)
        {
            auto next = states[a];
            next.meetWith(states[b]);
            states[a].narrowWith(next);
        }
        if (op == 10) states[a] = states[b];
        if (op == 11) states[a] = fresh();
        if (op == 12) states[a].resetValue(key);
        // Raw mutations exercise inactive/latent constraints as well as the
        // canonical setter paths. The product must still normalize correctly.
        if (op == 13) states[a].numerical().assign(key, LinearExpression(Rational(n)));
        if (op == 14) states[a].addresses().assign(key, AddressSet::singleton(Location(33)));
        if (op == 15) states[a].lifetimes().release(Location(rng()%64));
        observe(states[a], keys);
        observe(states[b], keys);
        add(states[a].isSubsetOf(states[b]) == CheckResult::True ? "subset" : "not-subset");
        add(states[b].isSubsetOf(states[a]) == CheckResult::True ? "reverse" : "not-reverse");
    }
    // Top-only support must participate through guards without needing payload
    // materialization, even across page boundaries and after a range projection.
    auto dense = fresh();
    for (unsigned id = 0; id < 8192; ++id)
    {
        dense.setInterval(Variable(id), Interval::top());
        if (id % 7 == 0) dense.setAddressSet(Variable(id), AddressSet::top());
    }
    auto branch = dense;
    for (unsigned id = 0; id < 8192; id += 17) branch.resetValue(Variable(id));
    branch.joinWith(dense);
    observe(branch, keys);
    add(branch.isSubsetOf(dense) == CheckResult::True ? "included" : "not-included");
    std::cout << "semantic-digest " << std::hex << digest << '\n';
}
