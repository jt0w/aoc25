#include "solution.h"

int64_t solve_part1(StringBuilder input) {
  int64_t lock = 50;
  int64_t count = 0;
  for (size_t i = 0; i < input.count; ++i) {
    while (isspace(input.items[i]))
      i++;
    int64_t d = input.items[i] == 'R' ? 1 : -1;
    ++i;
    int64_t n = 0;
    while (isdigit(input.items[i])) {
      char c = input.items[i];
      n = n * 10 + (c - '0');
      i++;
    }
    lock += d * n;
    lock = ((lock % 100) + 100) % 100;
    count += lock == 0;
  }
  return count;
}

int64_t solve_part2(StringBuilder input) {
  int64_t lock = 50;
  int64_t count = 0;
  for (size_t i = 0; i < input.count; ++i) {
    while (isspace(input.items[i]))
      i++;
    int64_t d = input.items[i] == 'R' ? 1 : -1;
    ++i;
    int64_t n = 0;
    while (isdigit(input.items[i])) {
      char c = input.items[i];
      n = n * 10 + (c - '0');
      i++;
    }
    for (int64_t j = 0; j < n; ++j) {
      lock += d;
      lock = ((lock % 100) + 100) % 100;
      count += lock == 0;
    }
  }
  return count;
}

