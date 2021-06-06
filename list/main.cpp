#include <iostream>
#include <algorithm>
#include "nstd_list.hpp"

template <typename T>
void print_list(nstd::list<T>& my_list)
{
    std::cout << "Size of list is "<< my_list.size() << std::endl;
    if (not my_list.empty())
    {
	//
	for (const auto& elem : my_list)
	{
	    std::cout << elem << ' ';
	}
    }
    else
    {
	std::cout << "LISTA VACIA";
    }
    std::cout << std::endl;
}

int main()
{
    nstd::list<int> my_list;

    my_list.push_front(1);
    my_list.push_front(2);
    my_list.push_back(3);
    my_list.push_back(3);
    my_list.push_back(3);
    my_list.push_back(5);
    my_list.push_back(1);
    print_list(my_list);

    my_list.pop_back();
    my_list.pop_front();
    print_list(my_list);

    my_list.clear();
    print_list(my_list);

}
