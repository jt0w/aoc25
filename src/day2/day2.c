// TODO: clean this mess up
#define CHIMERA_IMPLEMENTATION
#define CHIMERA_STRIP_PREFIX
#define CHIMERA_NO_COLOR_LOG
#include <chimera.h>
#undef log
#include <math.h>
#include <ctype.h>
#include <inttypes.h>


bool validate_id_part1(uint64_t id) {
  char id_str[1024];
  sprintf(id_str, "%"PRId64, id);
  int id_str_len = strlen(id_str);
  if (id_str_len % 2 != 0) {
    return true;
  }
  int half = id_str_len / 2;
  if (strncmp(id_str + half, id_str, half) == 0)
    return false;
  return true;
}

uint64_t part1(StringBuilder input) {
  uint64_t count = 0;
  size_t i = 0;
  while (i < input.count) {
    uint64_t range_begin = 0;
    while (isdigit(input.items[i])) {
      range_begin = range_begin * 10 + input.items[i] - '0';
      ++i;
    }
    assert(input.items[i] == '-');
    ++i;
    uint64_t range_end = 0;
    while (isdigit(input.items[i])) {
      range_end = range_end * 10 + input.items[i] - '0';
      ++i;
    }
    // QS: why `input.items[i] != '\n'`
    if (input.items[i] != ',' && input.items[i] != '\n') {
      chimera_log(CHIMERA_ERROR, "at %d expected ',' but got '%c'", i, input.items[i]);
      exit(1);
    }
    ++i;
    for (uint64_t id = range_begin; id <= range_end; ++id) {
      if (validate_id_part1(id) == false) {
	count += id;
      }
    }
  }
  return count;
}


bool validate_id_part2(uint64_t id) {
  char id_str[1024];
  sprintf(id_str, "%"PRIu64, id);
  size_t id_str_len = strlen(id_str);
  for (size_t n = 1; n <= id_str_len / 2; ++n) {
    if (id_str_len % n != 0) continue;
    bool repeated = true;
    for (size_t i = n; i < id_str_len; i += n) {
      if (strncmp(id_str, id_str + i, n) != 0) {
	repeated = false;
	break;
      }
    }
    if (repeated) return false;
  }
  return true;
}

uint64_t part2(StringBuilder input) {
  uint64_t count = 0;
  size_t i = 0;
  while (i < input.count) {
    uint64_t range_begin = 0;
    while (isdigit(input.items[i])) {
      range_begin = range_begin * 10 + input.items[i] - '0';
      ++i;
    }
    assert(input.items[i] == '-');
    ++i;
    uint64_t range_end = 0;
    while (isdigit(input.items[i])) {
      range_end = range_end * 10 + input.items[i] - '0';
      ++i;
    }
    // QS: why `input.items[i] != '\n'`
    if (input.items[i] != ',' && input.items[i] != '\n') {
      chimera_log(CHIMERA_ERROR, "at %d expected ',' but got '%c'", i, input.items[i]);
      exit(1);
    }
    ++i;
    for (uint64_t id = range_begin; id <= range_end; ++id) {
      if (validate_id_part2(id) == false)
	count += id;
    }
  }
  return count;
}

int main() {
  StringBuilder input = {0};
  read_file("inputs/day2.txt", &input);
  println("part1 => %"PRId64, part1(input));
  println("part2 => %"PRId64, part2(input));
  return 0;
}
