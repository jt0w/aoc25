#include "solution.h"
#include <sys/param.h>

typedef struct {
  int64_t beg, end;
} Range;

bool is_in_range(Range range, int64_t n) {
  return (range.beg - n <= 0) && (range.end - n >= 0);
}

typedef struct {
  Range *items;
  size_t count;
  size_t cap;
} Ranges;

bool is_in_ranges(Ranges ranges, int64_t n) {
  for (size_t i = 0; i < ranges.count; ++i) {
    if (is_in_range(ranges.items[i], n))
      return true;
  }
  return false;
}

int ranges_cmp(const void *a, const void *b) {
  Range *ar = (Range *)a;
  Range *br = (Range *)b;
  if (ar->beg < br->beg) return -1;
  if (ar->beg > br->beg) return 1;
  return 0;
}

Ranges merge_ranges(Ranges ranges) {
  assert(ranges.count > 0);
  qsort(ranges.items, ranges.count, sizeof(Range), ranges_cmp);

  Ranges merged = {0};
  Range curr = ranges.items[0];
  for (size_t i = 1; i < ranges.count; ++i) {
    if (ranges.items[i].beg <= curr.end + 1) {
      curr.end = MAX(ranges.items[i].end, curr.end);
    } else {
      da_push(&merged, curr);
      curr = ranges.items[i];
    }
  }
  da_push(&merged, curr);

  return merged;
}

typedef struct {
  const char *input;
  size_t size;

  size_t cur;
} Lex;

Range parse_range(Lex *lex) {
  Range r = {0};
  while (isalnum(lex->input[lex->cur]))
    r.beg = r.beg * 10 + (lex->input[lex->cur++] - '0');
  assert(lex->input[lex->cur++] == '-');
  while (isalnum(lex->input[lex->cur]))
    r.end = r.end * 10 + (lex->input[lex->cur++] - '0');
  assert(lex->input[lex->cur++] == '\n');
  return r;
}

int64_t solve_part1(StringBuilder input) {
  Lex lex = {
      .input = input.items,
      .size = input.count,
      .cur = 0,
  };
  Ranges ranges = {0};
  while (lex.input[lex.cur] != '\n') {
    da_push(&ranges, parse_range(&lex));
  }
  assert(lex.input[lex.cur++] == '\n');
  int64_t count = 0;
  while (lex.cur < lex.size) {
    int64_t n = 0;
    while (isalnum(lex.input[lex.cur]))
      n = n * 10 + (lex.input[lex.cur++] - '0');
    assert(lex.input[lex.cur++] == '\n');
    if (is_in_ranges(ranges, n)) {
      count++;
    }
  }
  return count;
}

int64_t solve_part2(StringBuilder input) {
  Lex lex = {
      .input = input.items,
      .size = input.count,
      .cur = 0,
  };
  Ranges ranges = {0};
  while (lex.input[lex.cur] != '\n') {
    da_push(&ranges, parse_range(&lex));
  }
  assert(lex.input[lex.cur++] == '\n');
  int64_t count = 0;
  Ranges merged = merge_ranges(ranges);

  for (size_t i = 0; i < merged.count; ++i) {
    count += merged.items[i].end - merged.items[i].beg + 1;
  }

  da_free(ranges);
  da_free(merged);
  return count;
}
