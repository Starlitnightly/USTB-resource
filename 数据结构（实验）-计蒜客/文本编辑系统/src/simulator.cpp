#include "stack.h"
#include "queue.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "editor.cpp"

int exit_flag;

std::string *info_fetch();
int exit_gracefully();

int exit_gracefully() {
    if (history != NULL) {
        delete history;
    }
    if (tmp != NULL) {
        delete tmp;
    }
    return 0;
}

std::string *info_fetch() {
    char buffer_[128];
    fgets(buffer_, 128, stdin);
    for (int i = 0; i < 128; i++) {
        if (buffer_[i] == '\n') {
            buffer_[i] = '\0';
        }
    }
    if (buffer_[0] == '\0') {
        return NULL;
    }
    std::string *buffer = new std::string(buffer_);
    return buffer;
}

void int_handle(int sig) {
    if (sig == SIGINT) {
        undo();
        history->print();
        printf("\n");
    }
}

void quit_handle(int sig) {
    if (sig == SIGQUIT) {
        if (exit_flag == 0) {
            printf("==========内存被清理=========\n");
            exit_gracefully();
            printf("====再按一次 Ctrl+\\ 可以退出====\n");
            exit_flag = 1;
        } else {
            printf("==========优雅地退出=========\n");
            exit(0);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 1) {
        printf("Usage: ./main\n");
        exit(1);
    }
    signal(SIGINT, int_handle);
    signal(SIGQUIT, quit_handle);
    printf("\n===========================\n请依照提示输入\n按下 Ctrl+c 以回到上一步。\n按下 Ctrl+\\ 以退出\n===========================\n");
    printf("请输入一条指令, 或者输入 resume 重做\n");
    while (true) {
        std::string *buffer = info_fetch();
        
        if (buffer == NULL) {
            continue;
        }
        if (buffer->compare("resume") == 0) {
            printf("==========重做上一步=========\n");
            resume();
            continue;
        }
        
        printf("=========收到操作指令========\n");
        if (history == NULL) {
            history = new Stack<std::string>();
        }
        history->push(buffer);
    }
    return 0;
}
