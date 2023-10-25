/**
 * @file insert_sorted_or_sort.cpp
 * @author Joakim Englund (joakimenglund@protonmail.com)
 * @brief This was a test because I couldn't decide whether or not to just
 *          insert all tasks in a list and then call sort(), or if I should
 *          make my own insert_sorted() function so the list would always
 *          be sorted. This reminded me that insert_sorted() (how I'd do it)
 *          looks messy in C++, so sort() at the end it is!
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <list>

class Tuple
{
public:
    int x;
    int y;
    Tuple(int a, int b)
    {
        this->x = a;
        this->y = b;
    }
};

int main(void)
{
    std::list<Tuple *> my_list;
    my_list.push_back(new Tuple(1, 2));
    my_list.push_back(new Tuple(3, 4));
    my_list.push_back(new Tuple(5, 6));
    auto it = my_list.begin();
    int val = 6;
    for (; it != my_list.end(); ++it)
    {
        if ((*it)->x > val)
        {
            my_list.insert(it, new Tuple(val, val));
            break;
        }
    }
    if (it == my_list.end())
    {
        my_list.push_back(new Tuple(val, val));
    }

    for (const auto &t : my_list)
    {
        std::cout << t->x << " " << t->y << "\n";
    }
    std::cout << "\n";
    return 0;
}