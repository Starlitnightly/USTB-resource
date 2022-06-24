#include "heap.h"
#define LEFT true
#define RIGHT false

#define LIST_SIZE 2000

Heap::~Heap()
{
    delete[] arr;
    num = 0;
}

Heap::Heap(Heap &other)
{
    arr = new Player_info[LIST_SIZE];
    for (int i = 0; i < LIST_SIZE; i++)
    {
        arr[i] = other.arr[i];
    }
    num = other.num;
}

Heap &Heap::operator=(Heap &other)
{
    arr = new Player_info[LIST_SIZE];
    for (int i = 0; i < LIST_SIZE; i++)
    {
        arr[i] = other.arr[i];
    }
    num = other.num;
    return *this;
}

#define SWAP(x, y)         \
    do                     \
    {                      \
        Player_info t = x; \
        x = y;             \
        y = t;             \
    } while (0)

void Heap::heapify_up()
{
    int cur = num - 1;
    if (cur < 0)
        return;
    int father = 0;
    while (1)
    {
        father = get_father(cur);
        if (father >= 0)
        {
            if (arr[cur] < arr[father])
            {
                SWAP(arr[cur], arr[father]);
                cur = father;
                continue;
            }
        }
        return;
    }
}

void Heap::heapify_down()
{
    int cur = 0;
    int left, right;
    int smaller;
    while (1)
    {
        left = get_child(LEFT, cur);
        right = get_child(RIGHT, cur);
        if ((0 <= left && left < num) && (0 <= right && right < num))
        {
            smaller = (arr[left] < arr[right]) ? left : right;
        }
        else if (0 <= left && left < num)
        {
            smaller = left;
        }
        else
        {
            smaller = right;
        }
        //如果有子结点则尝试交换
        if (0 <= smaller && smaller < num)
        {
            if (arr[cur] > arr[smaller])
            {
                SWAP(arr[cur], arr[smaller]);
                cur = smaller;
                continue;
            }
        }
        return;
    }
}

int Heap::get_child(bool direction, int index)
{
    if (!(0 <= index && index < num))
        return -1;
    int child;
    switch (direction)
    {
    case LEFT:
        child = index * 2 + 1;
        break;
    case RIGHT:
        child = index * 2 + 2;
        break;
    }
    if (0 <= child && child < num)
    {
        return child;
    }
    else
        return -1;
}

int Heap::get_father(int index)
{
    if (!(0 <= index && index < num) || !index)
        return -1;
    int father = (index - 1) / 2;
    if (0 <= father && father < num)
    {
        return father;
    }
    else
        return -1;
}

int Heap::insert(Player_info &p)
{
    //未满
    if (num < LIST_SIZE)
    {
        //问题代码
        arr[num] = p;
        heapify_up();
        num++;
        //问题代码
        return 1;
    }
    //已满
    else
    {
        if (p > arr[0])
        {
            arr[0] = p;
            heapify_down();
            return 1;
        }
    }
    //插入失败
    return 0;
}

Player_info *Heap::sort()
{
    int num_copy = num;
    while (1)
    {
        num--;
        if (num <= 0)
            break;
        SWAP(arr[0], arr[num]);
        heapify_down();
    }
    num = num_copy;

    Player_info *result = new Player_info[LIST_SIZE];
    for (int i = 0; i < num; i++)
        result[i] = arr[i];
    return result;
}

/*
 =========================================================
 ================ WARNING ===== 警告 ======================
 ===Please Do Not Modify Any of the Following Functions===
 ===================请不要修改以下函数=======================
 =========================================================
 */

int Heap::get_num() const
{
    return num;
}

Heap::Heap()
{
    num = 0;
    arr = new Player_info[LIST_SIZE];
}

void Heap::print()
{
    for (int i = 0; i < num; i++)
    {
        arr[i].print();
    }
    printf("\nSize of the heap is %d\n", num);
}

Player_info::Player_info()
{
    username = std::string("#");
    uid = 0;
    score = 0;
}

Player_info::~Player_info()
{
}

Player_info::Player_info(Player_info &other)
{
    username = std::string((other.username));
    score = other.score;
    uid = other.uid;
}

Player_info::Player_info(std::string in_name, long in_uid, int in_score)
{
    username = std::string(in_name);
    score = in_score;
    uid = in_uid;
}

Player_info &Player_info::operator=(Player_info &other)
{
    username = std::string((other.username));
    score = other.score;
    uid = other.uid;
    return *this;
}

int Player_info::get_score() const
{
    return score;
}

const std::string &Player_info::get_name() const
{
    return username;
}

bool Player_info::operator==(Player_info &other) const
{
    if (score == other.score)
    {
        return true;
    }
    return false;
}

bool Player_info::operator!=(Player_info &other) const
{
    if (score == other.score)
    {
        return false;
    }
    return true;
}

bool Player_info::operator<(Player_info &other) const
{
    if (score < other.score)
    {
        return true;
    }
    return false;
}

bool Player_info::operator<=(Player_info &other) const
{
    if (score <= other.score)
    {
        return true;
    }
    return false;
}

bool Player_info::operator>(Player_info &other) const
{
    if (score > other.score)
    {
        return true;
    }
    return false;
}

bool Player_info::operator>=(Player_info &other) const
{
    if (score >= other.score)
    {
        return true;
    }
    return false;
}

void Player_info::print()
{
    printf("[%ld]%s - %d\n", uid, username.c_str(), score);
    return;
}
