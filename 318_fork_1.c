#include "types.h"
#include "stat.h"
#include "user.h"

#define TEST_NAME "318_fork_1"
#include "318_test-tapish.h"

int main() {
  int a = 0;
  TEST_STRT(3);

  int f1 = fork();
  TEST_EXIT_IF(f1 < 0, "fork fail");
  if(f1 == 0) {
    a++;
    TEST_EXIT_IF(a != 1, "middle child first observation: %d", a);
    int f2 = fork();
    TEST_EXIT_IF(f1 < 0, "fork fail");
    if (f2 == 0) {
      sleep(1);
      TEST_EXIT_IF(a != 1, "youngest child observation: %d", a);
      TEST_EXIT_IF(wait() >= 0, "youngest child wait ok?");
    } else {
      a++;
      TEST_EXIT_IF(a != 2, "middle child second observation: %d", a);
      TEST_EXIT_IF(wait() != f2, "middle child wait");
      TEST_EXIT_IF(wait() >= 0, "middle child wait 2 ok?");
    }
  } else {
    sleep(1);
    TEST_EXIT_IF(a != 0, "parent observation: %d", a);
    TEST_EXIT_IF(wait() != f1, "parent wait");
    TEST_EXIT_IF(wait() >= 0, "parent wait 2 ok?");
  }

  TEST_FINI();
  exit();
}
