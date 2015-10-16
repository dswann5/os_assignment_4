// Test that fork fails gracefully.
// Tiny executable so that the limit can be filling the proc table.

#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"

int main(int argc, char *argv[])
{
      int a = *((int*) PGSIZE);
      printf(1, "%d dereferences to : %d\n", PGSIZE, a);
      printf(1, "Testing %d dereference, should segfault:\n", 0);
      printf(1, "%d\n", *((int*) PGSIZE-1));

      printf(1, "Null pointer failed if we got to here!\n");
      exit();
}
