#ifndef TREE_HPP
#define TREE_HPP
#include <iostream>


template <class T>
class Tree
{
    private:
        struct Node
		{
			Node *right;
            Node *left;
			T data;
			Node(T _value) : right(nullptr), left(nullptr), data(_value)
            {}
		};
		int16_t size;
		int32_t get(T value, T *_value, Node *ptr);		
		void add(T value, Node *ptr);
		const bool search(T value, Node *ptr);
		void show(Node *ptr);
        
	public:
		Node *root;
		const size_t getsize() { return this->size; }
		int32_t get(T value, T *_value) { return(get(value, _value, root)); }
		void add(T value) { add(value, root); }
		const bool search(T value) { return(search(value, root)); }
		void show() {return(show(root)); };
		Tree() : size(0), root(nullptr)
		{
		}

};

template <class T>
void Tree<T>::add(T value, Node *ptr)
{
	std::cout << "Tree::add started" << '\n';
	if (root == nullptr)
	{
		size += 1;
		Node *node = new Node{value};
		ptr = node;
		root = node;
	}

	else if(value == ptr->data)
		std::cout << "error, Tree::add: data = value" << '\n';	
	
	else if(value < ptr->data)
	{
		if (ptr->left)
			add(value, ptr->left);
		
		else
		{
			std::cout << "Tree::add newleftnode" << '\n';
			size += 1;
			Node *node = new Node{value};
			ptr->left = node;
		}
	}

	else if(value > ptr->data)
	{
		if (ptr->right)
			add(value, ptr->right);
		
		else
		{
			std::cout << "Tree::add newrightnode" << '\n';
			size += 1;
			Node *node = new Node{value};
			ptr->right = node;
		}
	}

	std::cout << "Tree::add finished" << '\n';

}







template <class T>
int32_t Tree<T>::get(T value, T *_value, Node *ptr)
{
	std::cout << "Tree::get started" << '\n';
	int answer = 0;

	if (root != nullptr)

	if(value == ptr->data)
	{
		answer = 1;	
		_value = &ptr->data;
	}

	else if(value < ptr->data)
	{
		if (ptr->left)
			answer = search(value, ptr->left);
	}

	else if(value > ptr->data)
	{
		if (ptr->right)
			answer = search(value, ptr->right);
	}

	std::cout << "Tree::get finished" << '\n';
	return answer;
}





template <class T>
const bool Tree<T>::search(T value, Node *ptr)
{
	std::cout << "Tree::search started" << '\n';
	bool answer = false;

	if (root != nullptr)

	if(value == ptr->data)
		answer = true;	
	
	else if(value < ptr->data)
	{
		if (ptr->left)
			answer = search(value, ptr->left);
		std::cout << ptr->left << '\n';
	}

	else if(value > ptr->data)
	{
		if (ptr->right)
			answer = search(value, ptr->right);
	}

	std::cout << "Tree::search finished" << '\n';
	return answer;
}

template <class T>
void Tree<T>::show(Node *ptr)
{
	std::cout << "Tree::show started" << '\n';
	if (root == nullptr)
	{
		std::cout << "The tree is empty" << '\n';
		return ;
	}

	if (ptr->left) show(ptr->left);

	if (ptr)
		std::cout << ptr->data << '\n';
		
	if (ptr-> right) show(ptr->right);
	std::cout << "Tree::show finished" << '\n';
	return ;
	
}



#endif