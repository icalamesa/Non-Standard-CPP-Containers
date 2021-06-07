#include <memory>

namespace nstd
{
    template <typename T>
    class list
    {
	struct Node
	{
	    Node* prev = nullptr;
	    Node* next = nullptr;
	    std::unique_ptr<T> data_ptr;
	    Node();
	    Node(const T& new_data);
	    Node(const T& new_data, Node* prev, Node* next);
	    T& get_data();
	};

	Node* _first = new Node;
	Node* _last = new Node;
	size_t _size = 0;

	//Deletes the Node pointed by the first pointer, too.
	void recursive_removal(Node* current);

	public:
	    list();
	    ~list();

	    class iterator
	    {
		//tags
		using iterator_category = std::bidirectional_iterator_tag;
		using difference_type   = uint64_t;
		using value_type        = T;
		using pointer           = T*;  // or also value_type*
		using reference         = T&;
		
		//internal elements
		Node* current;
		
		friend iterator list<T>::begin();
		friend iterator list<T>::end();

		public:
		    //operators
		    iterator operator++();
		    iterator operator++(int unused);
		    iterator operator--();
		    iterator operator--(int unused);
		    uint64_t operator-(const iterator& it);
		    T& operator*();

		    bool operator== (const iterator& other);
		    bool operator!= (const iterator& other);
	    };

	//iterators
	    iterator begin();
	    iterator end();

	//element access
	    T& front();
	    T& back();

	//capacity
	    bool empty() const;
	    int size() const;

	//modifiers
	    void clear();
	    //void insert(const T& new_data);
	    //erase?
	    void push_back(const T& new_data);
	    void push_front(const T& new_data);

	    void pop_back();
	    void pop_front();

	    //TO DO

	    iterator insert(const iterator& it);

	    void erase(iterator& it);
	    void erase(iterator& first, iterator& end);
	    
	    //removes element following specific criteria
	    template<class unary_predicate>
	    void remove_if(unary_predicate foo);

	    template<class unary_predicate>
	    void remove_if(iterator& begin, iterator& end, unary_predicate foo);

	    void remove(iterator& begin, iterator& end, const T& value);
	    
	    void remove(const T& value);

	    //removes equal consecutive elements from the list
	    void unique();
	    void unique(iterator& first, iterator& end);

	    //reverses the elements of the list
	    void reverse();
	    void reverse(iterator& first, iterator& end);
    };
    
    template<typename T>
    void list<T>::recursive_removal(Node* current)
    {
	if (current != this->_last)
	{
	    recursive_removal(current->next);
	    delete current;
	    this->_size--;
	}
    }

    template<typename T>
    void list<T>::clear()
    {
	recursive_removal(this->_first->next);
    }

    template<typename T>
    bool list<T>::empty() const
    {
	return not this->_size;
    }

    template<typename T>
    int list<T>::size() const
    {
	return this->_size;
    }

    //ITERADORES

    template<typename T>
    typename list<T>::iterator list<T>::begin()
    {
	typename list<T>::iterator it;
	it.current = this->_first->next;
	return it;
    }

    template<typename T>
    typename list<T>::iterator list<T>::end()
    {
	typename list<T>::iterator it;
	it.current = this->_last;
	return it;
    }

    template <typename T>
    typename list<T>::iterator list<T>::iterator::operator++()
    {
	this->current = this->current->next;
	return *this;
    }

    template <typename T>
    typename list<T>::iterator list<T>::iterator::operator++(int unused)
    {
	return ++*this;
    }

    template <typename T>
    typename list<T>::iterator list<T>::iterator::operator--()
    {
	this->current = this->current->prev;
	return *this;
    }

    template <typename T>
    typename list<T>::iterator list<T>::iterator::operator--(int unused)
    {
	return --*this;
    }

    template <typename T>
    uint64_t list<T>::iterator::operator-(const iterator& it)
    {
	iterator aux = *this;
	uint64_t counter = 0;
	while (aux != it)
	{
	    counter++;
	    aux++;
	}
	return counter;
    }
    template <typename T>
    bool list<T>::iterator::operator== (const iterator& other)
    {
	return this->current == other.current;
    }
    template <typename T>
    bool list<T>::iterator::operator!= (const iterator& other)
    {
	return this->current != other.current;
    }

    template <typename T>
    T& list<T>::iterator::operator*()
    {
	return current->get_data();
    }
       
    template<typename T>
    list<T>::Node::Node(const T& new_data)
    {
	this->data_ptr = std::make_unique<T>(new_data);
    }
    
    template <typename T>
    list<T>::Node::Node()
    {
	//EMPTY
    }
    
    template <typename T>
    list<T>::Node::Node(const T& new_data, Node* prev, Node* next)
    {
	this->data_ptr = std::make_unique<T>(new_data);
	this->prev = prev;
	this->next = next;
    }
    
    template<typename T>
    list<T>::~list()
    {
	//EMPTY FOR THE MOMENT
    }
    template <typename T>
    T& list<T>::Node::get_data()
    {
	return *data_ptr;
    }
    
    template<typename T>
    list<T>::list()
    {
	this->_first->next = this->_last;
    }
    
    template<typename T>
    T& list<T>::front()
    {
	return this->_first->next->get_data();
    }

    template<typename T>
    T& list<T>::back()
    {
	return this->_last->prev->get_data();
    }

    template<typename T>
    void list<T>::push_back(const T& new_data)
    {
	Node* old_pre_last = this->_last->prev;
	Node* aux = new Node(new_data, old_pre_last, this->_last);
	old_pre_last->next = aux;
	this->_last->prev = aux;
	
	this->_size++;
    }

    template<typename T>
    void list<T>::push_front(const T& new_data)
    {
	Node* old_next_first = this->_first->next;
	Node* aux = new Node(new_data, this->_first, old_next_first);
	old_next_first->prev = aux;
	this->_first->next = aux;

	this->_size++;
    }

    template<typename T>
    void list<T>::pop_back()
    {
	Node* aux = this->_last->prev->prev;
	delete this->_last->prev;
	this->_last->prev = aux;
	aux->next = this->_last;

	this->_size--;
    }
    
    template<typename T>
    void list<T>::pop_front()
    {
	Node* aux = this->_first->next->next;
	delete this->_first->next;
	this->_first->next = aux;
	aux->prev = this->_first;

	this->_size--;
    }
};





