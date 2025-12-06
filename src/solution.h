#ifndef SOLUTION_H
#define SOLUTION_H
#define CHIMERA_IMPLEMENTATION
#define CHIMERA_STRIP_PREFIX
#include <chimera.h>
#undef log
#include <math.h>
#include <ctype.h>
#include <inttypes.h>

// These can return -1 to indicate `TODO: not implemented`
int64_t solve_part1(StringBuilder input);
int64_t solve_part2(StringBuilder input);
#endif // endif SOLUTION_H
