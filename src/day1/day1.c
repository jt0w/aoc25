#define CHIMERA_IMPLEMENTATION
#define CHIMERA_STRIP_PREFIX
#include <chimera.h>
#undef log
#include <math.h>
#include <ctype.h>

static StringBuilder input = {0};
static size_t i = 0;

int part1() {
  int lock = 50;
  int count = 0;
  while (i < input.count - 1) {
    while (isspace(input.items[i])) i++;
    int d = input.items[i] == 'R' ? 1 : -1;
    ++i;
    int n = 0;
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

int part2() {
  int lock = 50;
  int count = 0;
  while (i < input.count - 1) {
    while (isspace(input.items[i])) i++;
    int d = input.items[i] == 'R' ? 1 : -1;
    ++i;
    int n = 0;
    while (isdigit(input.items[i])) {
      char c = input.items[i];
      n = n * 10 + (c - '0');
      i++;
    }
    for (int j = 0; j < n; ++j) {
      lock += d;
      lock = ((lock % 100) + 100) % 100;
      count += lock == 0;
    }
  }
  return count;
}
int main() {
  read_file("inputs/day1.txt", &input);
  println("part1 => %d", part1());
  i = 0;
  println("part2 => %d", part2());
  return 0;
}
