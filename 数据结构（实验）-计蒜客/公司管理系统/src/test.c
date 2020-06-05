#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int test1();

int test2();

int usage();

int main(int argc, char *argv[]) {
    if (argc > 2) {
        usage();
    }
    if (argc == 1) {
        test1();
        test2();
    } else if (!strcmp(argv[1], "part1")) {
        test1();
    } else if (!strcmp(argv[1], "part2")) {
        test2();
    } else {
        usage();
    }
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
