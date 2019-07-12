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
		Node *root;
		void _add(Node *root, T value, Node *node);
		void _get(T value, T *_value, Node *root);		
        
	public:
		const bool _search(T value, Node *root);
		const size_t getsize() { return this->size; }
		void get(T value, T *_value);
		void add(T value);
		const bool search( T value);
		Tree(T value) : size(0)
		{
			Node node = Node(value);
			this->root = &node;
		}

};


template <class T>
void Tree<T>::_add(Node *_root, T value, Node *node)
{
	std::cout << "used" << std::endl;
	if (value < _root->data && _root->left)
		_add(_root->left, value, node);
	else if (value > _root->data && _root->right)
		_add(_root->right, value, node);
	else if(value < _root->data && !_root->left)
	{
		_root->left = node;
		this->size += 1;
	}
	else if (value > _root->data && !_root->right)
	{
		_root->right = node;
		this->size += 1;
	}
}


template <class T>
void Tree<T>::add(T value)
{	
	Node *_root = this->root;
	Node *node = new Node {value};
	if (root == NULL)  { this->root = node; }
	
	else if (value < _root->data && _root->left)
		_add(_root->left, value, node);
	else if (value > _root->data && _root->right)
		_add(_root->right, value, node);
	else if(value < _root->data && !_root->left)
		_root->left = node;
	else if (value > _root->data && !_root->right)
		_root->right = node;
}


template <class T>
void Tree<T>::_get(T value, T *_value ,Tree::Node *root)
{
	if (value == root->data) _value = &root->data;
	else if (value < root->data) 
	{
		if (root->left) {_get(value, _value, root->left); }
		else { std::cout << "There is no that value" << std::endl; }
		
	}
	else if (value > root->data) 
	{
		if (root->right) {_get(value, _value, root->right); }
		else { std::cout << "There is no that value" << std::endl; }	
	}
}


template <class T>
void Tree<T>::get(T value, T *_value)
{
	if (!this->root) {std::cout << "Error, tree is empty" << std::endl; }
	else if (value == this->root->data) _value = &root->data;
	else if (value < this->root->data) 
	{
		if (this->root->left) {_get(value, _value, this->root->left); }
		else { std::cout << "There is no that value" << std::endl; }
	}
	else if (value > this->root->data) 
	{
		if (this->root->right) {_get(value, _value, this->root->right); }
		else { std::cout << "There is no that value" << std::endl; }	
	}
}


template <class T>
const bool Tree<T>::_search(T value, Node *root)
{
	if (value == root->data) return true;
	else if (value < root->data) 
	{
		if (root->left) {_search(value, root->left); }
		else return false;
		
	}
	else if (value > root->data) 
	{
		if (root->right) {_search(value, root->right); }
		else return false;
	}
	return false;
}


template <class T>
const bool Tree<T>::search(T value)
{
	st:
	if (!this->root) {std::cout << "Error, tree is empty" << std::endl; }
	else if (value == this->root->data) return true;
	else if (value < this->root->data) 
	{
		if (this->root->left) {_search(value, this->root->left); }
		else return false;
	}
	else if (value > this->root->data) 
	{
		if (this->root->right) {_search(value, this->root->right); }
		else return false;	
	}
	return false;
}



#endif