#include "solution.h"

static int ROW_SIZE = -1;

int64_t solve_part1(StringBuilder input) {
  assert(ROW_SIZE > 0);
  int64_t count = 0;
  for (int i = 0; i < (int)input.count; ++i) {
    if (input.items[i] == '\n')
      continue;
    if (input.items[i] == '.')
      continue;
    if (input.items[i] == '@') {
      int64_t roll_counter = 0;
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
      int64_t roll_counter = 0;
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

int64_t solve_part2(StringBuilder input) {
  assert(ROW_SIZE > 0);

  StringBuilder this = input;

  StringBuilder next = {0};
  next.items = malloc(input.count);
  memcpy(next.items, input.items, input.count);
  next.count = input.count;
  next.cap = input.cap;
  int64_t count = 0;
  while (can_remove(this)) {
    for (int i = 0; i < (int)this.count; ++i) {
      if (this.items[i] == '\n')
        continue;
      if (this.items[i] == '.')
        continue;
      if (this.items[i] == '@') {
        int64_t roll_counter = 0;
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
