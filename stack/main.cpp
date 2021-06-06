#include <iostream>
#include "nstd_stack.hh"

int main()
{
    nstd::stack<int> the_stack;
    the_stack.push(1);
    the_stack.push(3);
    the_stack.push(6);

    while (not the_stack.empty())
    {
	std::cout << the_stack.top() << ' ';
	the_stack.pop();
    }
    std::cout << std::endl;
}

