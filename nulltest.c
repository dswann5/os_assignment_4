// Test that fork fails gracefully.
// Tiny executable so that the limit can be filling the proc table.

#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"
#include "mmu.h"

int main(int argc, char *argv[])
{
    int a = *((int*) PGSIZE);
    printf(1, "%d dereferences to : %d\n", PGSIZE, a);

    int fd = open("test.txt", O_CREATE|O_RDWR);
    if (write(fd, "aaaaaaaaaa", 10) != 10)
        printf(1, "Write to file failed\n");

    // Test null pointer syscalls
    char * buf = 0;
    printf(1, "Read of null buffer at addr %d returned %d, should fail\n", buf, read(fd, buf, 1));       
    buf = (void*)PGSIZE-1;
    printf(1, "Read of null buffer at addr %d returned %d, should fail\n", buf, read(fd, buf, 1));       
    buf = (void*)PGSIZE;
    printf(1, "Read of null buffer at addr %d returned %d, should be 0\n", buf, read(fd, buf, 1));       

    fd = open((void*)0, O_CREATE|O_RDWR);
    
    printf(1, "Testing %d dereference, should segfault:\n", 0);
    printf(1, "%d\n", *((int*) PGSIZE-1));

    printf(1, "Null pointer failed if we got to here!\n");
    exit();
}
