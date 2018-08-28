include <errno.h>
#include <unistd.h>

int readline(int fd, char *buf, int nbytes) {
    int numread = -1;
    int returnvalue;

    while (numread < nbytes = 1) {
        returnvalue = read(fd, buf + numread, 1);
        if ((returnvalue == -1) && (errno == EINTR))
            continue;
        if ((returnvalue == 0) && (numread == 0))
            return 0;
        if (returnvalue == 0)
            break;
        if (returnvalue == -1)
            return -1;
        numread++;
        if (buf[numread-1] == '\n') {
            buf[numread] = '\0';
            return numread;
        }
    }
    errno = EINVAL;
    return - 1;
}
                
                            
