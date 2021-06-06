#ifndef NSTD_STACK_H
#define NSTD_STACK_H
namespace nstd
{
	template <typename T>
	class stack
	{
	private:

		struct Node
		{
			T data;
			Node* ptr_below;
			Node(const T& data_to_construct);
			Node();
		};

		Node* _top;
		int _size = 0;

	public:

		stack();
		~stack();

		T& top();
		bool empty();
		int size();

		void push(const T& new_data);
		void pop();

	};
};

template <typename T>
nstd::stack<T>::stack()
{
    //EMPTY
}

template <typename T>
nstd::stack<T>::~stack()
{
    //EMPTY
}

template <typename T>
nstd::stack<T>::Node::Node(const T& data_to_construct)
{
    this->data = data_to_construct;
}

template <typename T>
nstd::stack<T>::Node::Node()
{
    //EMPTY
}

template <typename T>
T& nstd::stack<T>::top()
{
    return this->_top->data;
}


template <typename T>
bool nstd::stack<T>::empty()
{
    return not this->size();
}

template <typename T>
int nstd::stack<T>::size()
{
    return this->_size;
}

template <typename T>
void nstd::stack<T>::push(const T& new_data)
{
    nstd::stack<T>::Node* old_head = this->_top;
    this->_top = new Node;
    *_top = Node(new_data);
    _top->ptr_below = old_head;

    this->_size++;
}


template <typename T>
void nstd::stack<T>::pop()
{
    nstd::stack<T>::Node* next_head = this->_top->ptr_below;
    delete this->_top;
    this->_top = next_head;

    this->_size--;
}

////explicit instantiation
//template class
//nstd::stack<int>;

#endif
