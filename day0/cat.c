#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[])
{
    int ret;
    /* allocate buffer */
    char *buffer = (char *)malloc(BUFFER_SIZE);

    /* get each filename */
    for (int i = 1; i < argc; i++) {
        /* open current file */
        int fd = open(argv[i], O_RDONLY);
        if (ret < 0) {
            perror("open");
            return -1;
        }

        /* read contents of current file*/
        while ((ret = read(fd, buffer, BUFFER_SIZE)) && ret > 0) {
            /* write contents of current file to STDOUT */
            int bytes_to_write = ret;
            int wr;
            while (bytes_to_write > 0) {
                wr = write(1, buffer, bytes_to_write);

                if (wr < 0) {
                    perror("write");
                    return -1;
                }

                bytes_to_write -= wr;
            }
        }
        if (ret < 0) {
            perror("read");
            return -1;
        }

        /* close file that was just processed */
        ret = close(fd);
        if (ret) {
            perror("close");
            return -1;
        }
    }

    /* free buffer */
    free(buffer);
    return 0;
}