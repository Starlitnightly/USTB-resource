#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int test1();

int test2();

int test3();

int usage();

int main() {
    test1();
    test2();
    test3();
    return 0;
}

int usage() {
    printf("Usage: ./test [option]\n[option]: 选择 part1 或 part2\n");
    exit(1);
}

int test1() {
    pid_t p1 = fork();
    if (p1 == 0) {          //child process
        int fd = open("output/part1.txt", O_RDWR | O_CLOEXEC | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG);
        if (fd < 0) {
            perror("Failed to open txt file ");
            exit(1);
        }
        dup2(fd, STDOUT_FILENO);
        execlp("./part1", "./part1", NULL);
        perror("Execlp Failed: ");    //this line is not supposed to be executed
        exit(1);                      //this line is not supposed to be executed
    } else if (p1 > 0) {       //parent process
        int status;
        pid_t w_result = waitpid(p1, &status, 0);

        if (w_result == -1) {
            perror("Failed to wait");
            exit(1);
        }

        pid_t p2 = fork();
        if (p2 == 0) {
            int fd_null = open("/dev/null", O_RDWR);
            dup2(fd_null, STDOUT_FILENO);
            execlp("diff", "diff", "output/part1.txt", "output/part1_sol.txt", NULL);
            perror("Execlp diff Failed: ");    //this line is not supposed to be executed
            exit(1);
        } else if (p2 > 0) {
            int status2;
            waitpid(p2, &status2, 0);
            if (WIFEXITED(status2)) {
                if (WEXITSTATUS(status2) != 0) {
                    printf("[失败] 测试 1\n");
                } else {
                    printf("[通过] 测试 1\n本地测试比较简单，请再三检查之后再上传！\n");
                }
            }
        } else {
            perror("Failed to fork");
            exit(1);
        }
    } else {
        perror("Failed to fork");
        exit(1);
    }
    return 1;
}

int test2() {
    pid_t p1 = fork();
    if (p1 == 0) {          //child process
        int fd = open("output/part2.txt", O_RDWR | O_CLOEXEC | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG);
        if (fd < 0) {
            perror("Failed to open txt file ");
            exit(1);
        }
        dup2(fd, STDOUT_FILENO);
        execlp("./part2", "./part2", NULL);
        perror("Execlp Failed: ");    //this line is not supposed to be executed
        exit(1);                      //this line is not supposed to be executed
    } else if (p1 > 0) {       //parent process
        int status;
        pid_t w_result = waitpid(p1, &status, 0);

        if (w_result == -1) {
            perror("Failed to wait");
            exit(1);
        }

        pid_t p2 = fork();
        if (p2 == 0) {
            int fd_null = open("/dev/null", O_RDWR);
            dup2(fd_null, STDOUT_FILENO);
            execlp("diff", "diff", "output/part2.txt", "output/part2_sol.txt", NULL);
            perror("Execlp diff Failed: ");    //this line is not supposed to be executed
            exit(1);
        } else if (p2 > 0) {
            int status2;
            waitpid(p2, &status2, 0);
            if (WIFEXITED(status2)) {
                if (WEXITSTATUS(status2) != 0) {
                    printf("[失败] 测试 2\n");
                } else {
                    printf("[通过] 测试 2\n本地测试比较简单，请再三检查之后再上传！\n");
                }
            }
        } else {
            perror("Failed to fork");
            exit(1);
        }
    } else {
        perror("Failed to fork");
        exit(1);
    }
    return 1;
}

int test3() {
    pid_t p = fork();
    if (p == 0) {
        int fd = open("output/part3.txt", O_RDWR | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
        dup2(fd, STDERR_FILENO);
        close(fd);

        int fd_null = open("/dev/null", O_RDWR);
        if (fd_null < 0) {
            perror("Failed to open txt file ");
            exit(1);
        }
        dup2(fd_null, STDOUT_FILENO);

        system("time ./part2");

        perror("Execlp Failed: ");    //this line is not supposed to be executed
        exit(1);                      //this line is not supposed to be executed
    } else if (p > 0) {
        int status;
        pid_t w_result = waitpid(p, &status, 0);
        if (w_result == -1) {
            perror("Wait Failed: ");
            exit(1);
        }

        FILE *fp = fopen("output/part3.txt", "r");
        char *buffer = NULL;
        size_t n = 0;
        //int min;
        float m = 0, sec = -1;
        getline(&buffer, &n, fp);
        if (getline(&buffer, &n, fp) != -1) {
            sscanf(buffer, "real    %fm%f", &m, &sec);
            free(buffer);
            buffer = NULL;

            free(buffer);
            buffer = NULL;
        }
        free(buffer);
        fclose(fp);
        //printf("Hash result 2: %ld\n", xor_hash_2);
        if (sec < 0.03 && sec != -1) {
            printf("[通过] 测试 3\n本地测试比较简单，请再三检查之后再上传！\n");
            return 1;
        } else {
            printf("[失败] 测试 3\n");
            return 0;
        }
    } else {
        perror("Fork Failed: ");
        exit(1);
    }
    return 0;
}
