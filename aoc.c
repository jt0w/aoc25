#include <stdbool.h>
#define CHIMERA_IMPLEMENTATION
#define CHIMERA_STRIP_PREFIX
#include <chimera.h>
#include <dlfcn.h>
#include <errno.h>
#include <inttypes.h>

Cmd cmd = {0};

#define build_dir "build/"

bool build_day(int day) {
  cmd = (Cmd){0};
  cmd_push(&cmd, CHIMERA_COMPILER);
  cmd_push(&cmd, "-Wall", "-Wextra", "-Wno-missing-braces", "-std=c23",
           "-Wno-unused-parameter", "-ggdb");
  cmd_push(&cmd, "-lm");
  cmd_push(&cmd, "-shared", "-rdynamic");
  cmd_push(&cmd, temp_sprintf("src/day%d.c", day, day));
  cmd_push(&cmd, "-o", temp_sprintf(build_dir "day%d.so", day));
  if (!cmd_exec(&cmd))
    return false;
  else
    return true;
}

int main(int argc, char **argv) {
  rebuild_file(argv, argc);
  create_dir(build_dir);

  const char *program = shift(argv, argc);
  if (argc != 1) {
    println("usage: %s <day as number>", program);
    log(CHIMERA_ERROR, "Did not provide day");
    return 1;
  }

  errno = 0;
  const char *day_arg = shift(argv, argc);
  int day = strtol(day_arg, NULL, 10);
  if (errno == ERANGE) {
    log(CHIMERA_ERROR, "%s is not a valid day", day_arg);
    return 1;
  }
  if (!build_day(day)) {
    log(CHIMERA_ERROR, "Could not build day %d", day);
    return 1;
  }

  int64_t (*solve_part1)(StringBuilder input) = NULL;
  int64_t (*solve_part2)(StringBuilder input) = NULL;
  void *solution_handle =
      dlopen(temp_sprintf("./build/day%d.so", day), RTLD_NOW);

  if (!solution_handle) {
    log(CHIMERA_ERROR, "Could not open dynamic lib: %s", dlerror());
    return 1;
  }

  solve_part1 = dlsym(solution_handle, "solve_part1");
  if (!solve_part1) {
    log(CHIMERA_ERROR, "Could not find ´solve_part1´");
    return 1;
  }
  solve_part2 = dlsym(solution_handle, "solve_part2");
  if (!solve_part2) {
    log(CHIMERA_ERROR, "Could not find ´solve_part1´");
    return 1;
  }

  StringBuilder input = {0};
  read_file(temp_sprintf("inputs/day%d.txt", day), &input);
  int64_t part1_sol = solve_part1(input);
  println("part1: %s", part1_sol == -1 ? "TODO: Not Implemented" : temp_sprintf("%"PRId64, part1_sol));

  int64_t part2_sol = solve_part2(input);
  println("part2: %s", part2_sol == -1 ? "TODO: Not Implemented" : temp_sprintf("%"PRId64, part2_sol));

  if (dlclose(solution_handle) != 0) {
    log(CHIMERA_ERROR, "Could not close dynamic lib: %s", dlerror());
    return 1;
  }
  return 0;
}
