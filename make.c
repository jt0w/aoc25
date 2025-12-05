#include <stdbool.h>

#define CHIMERA_IMPLEMENTATION
#define CHIMERA_STRIP_PREFIX
#include <chimera.h>

Cmd cmd = {0};

#define build_dir "build/"

bool build_day(int day) {
  cmd = (Cmd){0};
  cmd_push(&cmd, CHIMERA_COMPILER);
  cmd_push(&cmd, "-O4","-Wall", "-Wextra", "-Wno-missing-braces","-std=c23", "-Wno-unused-parameter" , "-ggdb") ;
  cmd_push(&cmd, "-lm");
  cmd_push(&cmd, temp_sprintf("src/day%d/day%d.c", day, day));
  cmd_push(&cmd, "-o", temp_sprintf(build_dir"day%d", day));
  if (!cmd_exec(&cmd))
    return false;
  else
    return true;
}

bool build(int day) {
  if (!build_day(day)) {
    log(CHIMERA_ERROR, "failed to build day %d", day);
    return false;
  } else {
    log(CHIMERA_INFO, "succesfully build day %d", day);
    return true;
  }
}


#define build_count(day) if (!build((day))) failed++

int main(int argc, char **argv) {
  rebuild_file(argv, argc);
  create_dir(build_dir);
  int failed = 0;
  build_count(1);
  build_count(2);
  build_count(3);
  build_count(4);
  build_count(5);
  if (failed > 0) {
    log(CHIMERA_ERROR, "failed %d days", failed);
    return 1;
  }
}
