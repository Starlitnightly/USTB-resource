#include <iostream>
#include <string>

const int SEAT_NUM = 10;

class Seat {
    private:
        static int count;
    protected:
        // 申请资源
        void acquire(std::string name = "seat") {
            if (count < SEAT_NUM)
            {
                ++ count;
                std::cout << name << ": allocated "
                    << count << "/" << SEAT_NUM << std::endl;
            }
            else 
            {
                std::cout << "out of memory" << std::endl;
            }
        }

        // 释放资源
        void release()
        {
            if (count > 0)
            {
                std::cout << "release: " << count
                    << "/" << SEAT_NUM << std::endl;
                -- count;
            }
        }

    public:
        virtual ~Seat() {}
};

int Seat::count = 0;


class Boy : public Seat {
    private:
        bool flag;
        std::string name;
    public:
        Boy():flag(false) {
        }

        virtual ~Boy() {
        }

        // 拿座位
        void giao() {
            flag = true;
            Seat::acquire(name);
        }
};

Boy *b[26];
int op[100], op2[100];

int main(int argc, char *argv[])
{
    int round_;
    int n;
    std::cin >> round_ >> n;
    for (int i = 0; i < n; ++i)
    {
        char c;
        std::cin >> op[i] >> c;
        op2[i] = c - 'a';
    }

    for (int i = 0; i < 26; ++i)
    {
        b[i] = NULL;
    }

    for (int r = 0; r < round_; ++r)
    {
        std::cout << "#round: " << r << std::endl;
        for (int i = 0; i < n; ++i)
        {
            int d = op2[i];
            delete b[d];
            b[d] = NULL;
            if (op[i] == 0)
            {
                b[d] = new Boy();
                b[d]->giao();
            }
        }
    }

    for (int i = 0; i < 26; ++i)
    {
        delete b[i];
    }
    return 0;
}
