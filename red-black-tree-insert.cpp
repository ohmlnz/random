#include <iostream>
#include <math.h> // for asserting height
#include <queue>
#include <cassert>

using namespace std;

#define RED 0
#define BLACK 1

template <class T>
class RBT;

// swapColor swaps the color from red to black and vice versa
int swapColor(int c) {
	return (c == 0) ? 1 : 0;
}

template <class T>
class RBTNode {
	RBTNode<T> *parent, *left, *right;
	T data;
	int color;

public:
	RBTNode(T data)
		: data(data),
		color(RED),
		parent(nullptr),
		left(nullptr),
		right(nullptr) {}
	friend class RBT<T>;
	void prettyPrint(int indent) const;

	template <class T1>
	friend void swapColor(RBTNode<T1> *);
	template <class T1>
	friend int getColor(RBTNode<T1> *);
	int height() const;
	T getData() const;
};

template <class T>
int RBTNode<T>::height() const {
	int left_h = 0;
	if (left != nullptr) {
		left_h = left->height();
	}
	int right_h = 0;
	if (right != nullptr) {
		right_h = right->height();
	}
	return 1 + max(left_h, right_h);
}

template <class T>
void RBTNode<T>::prettyPrint(int indent) const {
	if (right != nullptr) {
		right->prettyPrint(indent + 1);
	}
	int margin = indent * 2;
	for (int i = 0; i < margin; ++i) {
		cout << '\t';
	}
	cout << "DATA: " << data << endl;
	for (int i = 0; i < margin; ++i) {
		cout << '\t';
	}
	cout << "COLOR: " << (color == RED ? "RED" : "BLACK") << endl;
	if (left != nullptr) {
		left->prettyPrint(indent + 1);
	}
}

template <class T>
void swapColor(RBTNode<T> *node) {
	if (node != nullptr) {
		node->color = swapColor(node->color);
	}
}

// getColor handles null nodes
template <class T>
int getColor(RBTNode<T> *node) {
	if (node != nullptr) {
		return node->color;
	}
	return BLACK;
}

template <class T>
T RBTNode<T>::getData() const
{
	return data;
}

template <class T>
class RBT {
	RBTNode<T> *root;
	void singleCCR(RBTNode<T> *&point);
	void doubleCR(RBTNode<T> *&point);
	void singleCR(RBTNode<T> *&point);
	void doubleCCR(RBTNode<T> *&point);
	void rotate(RBTNode<T>* point);
public:
	RBT() : root(nullptr) {}

	void insert(const T &);
	void insert(const T &, RBTNode<T> *&point, RBTNode<T> *parent);
	void prettyPrint() const { root->prettyPrint(0); }

	int height() const { return root->height(); }
	void normalize();
};

template <class T>
void RBT<T>::doubleCCR(RBTNode<T> *&point) {
	singleCR(point->right);
	singleCCR(point);
}

template <class T>
void RBT<T>::doubleCR(RBTNode<T> *&point) {
	singleCCR(point->left);
	singleCR(point);
}

template <class T>
void RBT<T>::singleCR(RBTNode<T> *&point) {
	RBTNode<T>* grandparent = point;
	RBTNode<T>* parent = point->left;

	parent->parent = grandparent->parent;
	grandparent->parent = parent;
	grandparent->left = parent->right;
	parent->right = grandparent;

	if (parent->parent == nullptr)
	{
		root = parent;
		if (getColor(parent) == 0)
		{
			swapColor(parent);
		}
	}
	else if (parent->parent->left = grandparent)
	{
		parent->parent->left = parent;
	}
	else
	{
		parent->parent->right = parent;
	}

	if (getColor(parent) == 0)
	{
		swapColor(parent);
		swapColor(grandparent);
	}
}

template <class T>
void RBT<T>::singleCCR(RBTNode<T> *&point) {
	RBTNode<T>* grandparent = point;
	RBTNode<T>* parent = point->right;

	parent->parent = grandparent->parent;
	grandparent->parent = parent;
	grandparent->right = parent->left;
	parent->left = grandparent;

	if (grandparent->right != nullptr)
	{
		grandparent->right->parent = grandparent;
	}

	if (parent->parent == nullptr)
	{
		root = parent;
		if (getColor(parent) == 0)
		{
			swapColor(parent);
		}
	}
	else if (parent->parent->right = grandparent)
	{
		parent->parent->right = parent;
	}
	else
	{
		parent->parent->left = parent;
	}

	if (getColor(parent) == 0)
	{
		swapColor(parent);
		swapColor(grandparent);
	}
}

template <class T>
void RBT<T>::rotate(RBTNode<T>* point)
{
	// swap colors if a node is black with two red children
	if (point != nullptr && getColor(point) == 1 && getColor(point->left) == 0 && getColor(point->right) == 0)
	{
		swapColor(point);
		swapColor(point->left);
		swapColor(point->right);
	}

	if (point != nullptr && point->parent != nullptr && point->parent->parent != nullptr)
	{
		if (getColor(point) == 0 && getColor(point->parent) == 0)
		{
			// if the uncle node is black and is on the left side of the tree
			if (getColor(point->parent->parent->left) != 0)
			{
				// if node outside
				if (point->parent->right = point)
				{
					singleCCR(point->parent->parent);
				}
				else
				{
					doubleCCR(point->parent->parent);
				}
			}
			else if (getColor(point->parent->parent->right) != 0)
			{
				// if node outside
				if (point->parent->left = point)
				{
					singleCR(point->parent->parent);
				}
				else
				{
					doubleCR(point->parent->parent);
				}
			}
		}
	}
}

template <class T>
void RBT<T>::normalize()
{
	if (getColor(root) == 0)
	{
		swapColor(root);
	}
}

template <class T>
void RBT<T>::insert(const T &toInsert, RBTNode<T> *&point, RBTNode<T> *parent) {
	if (point == nullptr) {               // leaf location is found so insert node
		point = new RBTNode<T>(toInsert); // modifies the pointer itself since *point
										  // is passed by reference
		point->parent = parent;

		RBTNode<T> *curr_node = point; // curr_node will be set appropriately when walking up the tree
		rotate(point);
	}
	else if (toInsert < point->data) { // recurse down the tree to left to find correct leaf location
		rotate(point);
		insert(toInsert, point->left, point);
	}
	else { // recurse down the tree to right to find correct leaf location
		rotate(point);
		insert(toInsert, point->right, point);
	}
}

template <class T>
void RBT<T>::insert(const T &toInsert) {
	insert(toInsert, root, nullptr);
}

int main() {
	RBT<int> b;
	int count = 10;
	for (int i = 0; i < 10; i++) {
		b.insert(i);
	}
	b.normalize();
	b.prettyPrint();
	int height = b.height();
	assert(height <= 2 * log2(count));
}
