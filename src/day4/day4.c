#define CHIMERA_IMPLEMENTATION
#define CHIMERA_STRIP_PREFIX
#include <chimera.h>
#undef log
#include <ctype.h>
#include <inttypes.h>
#include <math.h>

static int ROW_SIZE = -1;

uint64_t part1(StringBuilder input) {
  assert(ROW_SIZE > 0);
  uint64_t count = 0;
  for (int i = 0; i < (int)input.count; ++i) {
    if (input.items[i] == '\n')
      continue;
    if (input.items[i] == '.')
      continue;
    if (input.items[i] == '@') {
      uint64_t roll_counter = 0;
      for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
          if (dx == 0 && dy == 0)
            continue;
          if (i + dx + ROW_SIZE * dy < 0 || i + dx + ROW_SIZE * dy >= (int)input.count)
            continue;
          if (input.items[i + dx + (ROW_SIZE * dy)] == '@')
            roll_counter++;
        }
      }
      if (roll_counter < 4)
        count++;
    }
  }
  return count;
}

bool can_remove(StringBuilder input) {
  bool can_remove = false;
  for (int i = 0; i < (int)input.count; ++i) {
    if (input.items[i] == '\n')
      continue;
    if (input.items[i] == '.')
      continue;
    if (input.items[i] == '@') {
      uint64_t roll_counter = 0;
      for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
          if (dx == 0 && dy == 0)
            continue;
          int index = i + dx + ROW_SIZE * dy;
          if (index < 0 || index >= (int)input.count)
            continue;
          if (input.items[index] == '@') {
            roll_counter++;
          }
        }
      }
      if (roll_counter < 4) {
        can_remove = true;
      }
    }
  }
  return can_remove;
}

uint64_t part2(StringBuilder input) {
  assert(ROW_SIZE > 0);

  StringBuilder this = input;

  StringBuilder next = {0};
  next.items = malloc(input.count);
  memcpy(next.items, input.items, input.count);
  next.count = input.count;
  next.cap = input.cap;
  uint64_t count = 0;
  while (can_remove(this)) {
    for (int i = 0; i < (int)this.count; ++i) {
      if (this.items[i] == '\n')
        continue;
      if (this.items[i] == '.')
        continue;
      if (this.items[i] == '@') {
        uint64_t roll_counter = 0;
        for (int dx = -1; dx <= 1; ++dx) {
          for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0)
              continue;
            int index = i + dx + ROW_SIZE * dy;
            if (index < 0 || index >= (int)this.count)
              continue;
            if (this.items[index] == '@') {
              roll_counter++;
            }
          }
        }
        if (roll_counter < 4) {
          next.items[i] = 'x';
          count++;
        }
      }
    }
    this = next;
  }
  return count;
}

int main() {
  StringBuilder input = {0};
  read_file("inputs/day4.txt", &input);
  ROW_SIZE = 0;
  while (input.items[ROW_SIZE] != '\n')
    ROW_SIZE++;
  ROW_SIZE++;
  println("part1 => %" PRIu64, part1(input));
  println("part2 => %" PRIu64, part2(input));
  return 0;
}
