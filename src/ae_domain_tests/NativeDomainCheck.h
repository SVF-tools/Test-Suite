#ifndef SVF_TEST_SUITE_NATIVE_DOMAIN_CHECK_H
#define SVF_TEST_SUITE_NATIVE_DOMAIN_CHECK_H

#include "AE/Core/NumericalDomain.h"

#include <functional>
#include <string>

namespace SVF
{
struct OctagonConfig;
}

extern const SVF::Variable x, y, z, realX, realY;

void check(bool valid, const char* message);
SVF::LinearExpression e(SVF::Variable variable);
SVF::LinearExpression c(int value);
void expectRange(const SVF::NumericalDomain& state, SVF::Variable variable, int lower, int upper);
void run(const std::string& name, const std::function<void()>& test);

void checkOctagonRegressions(const std::string& name, const SVF::OctagonConfig& config);
void checkPolyhedraRegressions();
int checkInvalidNarrowing(const std::string& input);

#endif
