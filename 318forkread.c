#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define TEST_NAME "318_forkread"
#include "318_test-tapish.h"

// You may wish to consider adding TEST_DIAG(who " foo"); statements, but
// being too chatty increases the risk of exposing the nonatomicity of
// print statements on xv6.
#define READ_TEST(who) \
    TEST_EXIT_IF(read(fd, buf1, 16) != 16, who " read buf1"); \
    TEST_EXIT_IF(read(fd, buf2, 16) != 16, who " read buf2");

char buf1[16];

int main(int argc, char **argv) {
  TEST_STRT(2);

  int sd = atoi(argv[1]);

  char buf2[16];

  int fd = open("318_forkread", O_RDONLY);
  TEST_EXIT_IF(fd < 0, "open fail");

  int f1 = fork();
  TEST_EXIT_IF(f1 < 0, "fork fail");
  if(f1 == 0) {
    sleep(sd);
    READ_TEST("child");
    TEST_EXIT_IF(wait() >= 0, "child wait ok?");
  } else {
    sleep(2 - sd);
    READ_TEST("parent");
    TEST_EXIT_IF(wait() != f1, "parent wait");
    TEST_EXIT_IF(wait() >= 0, "parent wait 2 ok?");
  }

  TEST_FINI();
  exit();
}
