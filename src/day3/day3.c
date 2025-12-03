#define CHIMERA_IMPLEMENTATION
#define CHIMERA_STRIP_PREFIX
#include <chimera.h>
#undef log
#include <math.h>
#include <ctype.h>
#include <inttypes.h>


typedef struct {
  char *items;
  size_t count;
  size_t cap;
} Bank;

size_t parse_bank(size_t start_i, Bank *bank, StringBuilder input) {
  size_t i = start_i;
  for (; input.items[i] != '\n'; ++i)
    da_push(bank, input.items[i]);
  return i;
}

uint64_t get_largest_with_contraint_and_offset(size_t remaining, size_t offset, Bank bank, size_t *found_index) {
  uint64_t largest = 0;
  *found_index = offset;

  if (bank.count < remaining || offset > bank.count - remaining) {
    return 0;
  }

  for (size_t i = offset; i <= bank.count - remaining; ++i){
    uint64_t num = bank.items[i] - '0';
    if (num > largest) {
      largest = num;
      *found_index = i;
    }
  }
  return largest;
}


// Get largest combination of length `n`
// But the combination must be from left to right
uint64_t get_comb(size_t n, Bank bank) {
  uint64_t result = 0;
  size_t last_index = 0;

  for (size_t i = 0; i < n; ++i){
    size_t remaining = n - i;  // How many digits we still need (including this one)
    size_t found_index;
    uint64_t digit = get_largest_with_contraint_and_offset(remaining, last_index, bank, &found_index);
    result = result * 10 + digit;
    last_index = found_index + 1;  // Next search starts after this digit
  }
  return result;
}

uint64_t part1(StringBuilder input) {
  uint64_t count = 0;
  for (size_t i = 0; i < input.count; ++i) {
    Bank bank = {0};
    i = parse_bank(i, &bank, input);
    uint64_t largest = get_comb(2, bank);
    count += (uint64_t)largest;
  }
  return count;
}

uint64_t part2(StringBuilder input) {
  uint64_t count = 0;
  for (size_t i = 0; i < input.count; ++i) {
    Bank bank = {0};
    i = parse_bank(i, &bank, input);
    uint64_t largest = get_comb(12, bank);
    count += (uint64_t)largest;
  }
  return count;
}

int main() {
  StringBuilder input = {0};
  read_file("inputs/day3.txt", &input);
  println("part1 => %"PRIu64, part1(input));
  println("part2 => %"PRIu64, part2(input));
  return 0;
}
