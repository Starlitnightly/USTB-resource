#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
long xor_hash;  //very very important this one

int tester();
long sfold(std::string &s, int M);

int main() {
    //TODO
    int ret = 0;
    pid_t p = fork();
    if (p == 0) {
        int fd = open("result.txt", O_RDWR | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
        dup2(fd, STDOUT_FILENO);
        close(fd);
        execlp("./word_check", "./word_check", "the_road_not_taken.txt", NULL);
        perror("Execlp Failed: ");    //this line is not supposed to be executed
        exit(1);                      //this line is not supposed to be executed
    } else if (p > 0) {
        int status;
        pid_t w_result = waitpid(p, &status, 0);
        if (w_result == -1) {
            perror("Wait Failed: ");
            exit(1);
        }
        ret = tester();
        //printf("%ld\n", xor_hash);
    } else {
        perror("Fork Failed: ");
        exit(1);
    }
    return ret;
}

int tester() {
    FILE *fp = fopen("result.txt", "r");
    char *buffer = NULL;
    size_t n = 0;
    while (getline(&buffer, &n, fp) != -1) {
        std::string _line = std::string(buffer);
        xor_hash = xor_hash ^ sfold(_line, 1000000);
        free(buffer);
        buffer = NULL;
    }
    free(buffer);
    fclose(fp);
    if (xor_hash == 772855) {
        return 0;
    }
    return 1;
}

long sfold(std::string &s, int M) {
    int intLength = s.length() / 4;
    long sum = 0;
    for (int j = 0; j < intLength; j++) {
        std::string c = s.substr(j * 4, 4);
        long mult = 1;
        for (int k = 0; k < (int)c.length(); k++) {
            sum += (long)((int)c[k] * mult);
            mult = mult * 256;
        }
    }
    std::string c = s;
    long mult = 1;
    for (int k = 0; k < (int)c.length(); k++) {
        sum += (long)((int)c[k] * mult);
        mult = mult * 256;
    }
    long ret = (sum) % M;
    if (ret < 0) {
        ret = (-1) * ret;
    }
    return ret;
}
