#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<error.h>
#include<string.h>

int main()
{
    int fd = open("/dev/gtdev", O_RDWR);

    if(fd < 0)
    {
        perror("gtdev open fail\n");

        return -1;
    }
    
    int r;
    r = write(fd, "hello world", strlen("hello world"));
    if(r > 0)
    {
        printf("write completed\n");
    }
    else
    {
        perror("io error");
    }

    char buff[1024] = {0};
    r = read(fd, buff, sizeof(buff));
    if(r > 0)
    {
        printf("read for gtdev: %s\n", buff);
        printf("read data length: %d\n", r);
    }
    else
    {
        perror("read error");
    }

    close(fd);
    return 0;
}
