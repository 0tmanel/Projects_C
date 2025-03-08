#include <fcntl.h>
#include <unistd.h>
#define Size 100
int main (int argc, char **argv)
{
    int fld[argc - 1];
    char buffer[Size];
     int i = 1;
     if(argc == 1)
     {
        write(0, "No arguments", 11);
     }
        int fd = open(argv[argc - 1], O_RDWR);
    while ( i < argc - 1)
    {
         fld[i] = open(argv[i], O_RDWR);
         if(fld[i] == -1)
         return 1;

         int readl = read(fld[i], buffer, Size);
        write(fd, &buffer, readl);
        i++;

    close(fld[i]);
    }
    close(fd);
   
    return 0;
}