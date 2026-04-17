#include <iostream>

#include "BinarySearchTree.h"



namespace pic10b
{
	Tree::Tree() noexcept	// default constructor
	{
		root = nullptr; // set the root as null initially
		theSize = 0; // set the number of values in the tree as 0 initially
	}

	Tree::~Tree()	// destructor
	{
		destroyHelper(root); // calls the recursive helper function for destruction process
	}


	Tree::Tree(const Tree& rhs)		// copy constructor
		: root(nullptr), theSize(0)
	{
		traverseInsert(rhs.root); // calls the recursive helper function to copy
	}

	Tree::Tree(Tree&& that) noexcept	// move constructor
		: Tree() // invoke the default constructor
	{
		swap(*this, that); // use swap free function to swap two trees
	}


	Tree& Tree::operator=(Tree that)&	 // assignment operator
	{
		swap(*this, that); // use swap free function to swap two trees
		return *this; // return the swapped tree 'this'
	}
	

	void Tree::insert(double _double)
	{
		if (!root) // when the root is null, empty
		{
			root = new node(std::move(_double)); // set the root to be this node
			theSize++; // increase the size count
		}
		else // when the root is not null, not empty
		{
			node* n = new node(std::move(_double)); // create a new node
			theSize += root->insertNode(n); // add this new node into the tree and increase the count
		}
	}

	void Tree::erase(iterator itr)
	{
		if (itr.curr->left == nullptr && itr.curr->right == nullptr && itr.curr->parent != nullptr) // zero child and non-null parent
		{
			// set the parent's pointer to this node as null
			if (itr.curr->inLeftBranch) // when curr is in the left branch
			{
				itr.curr->parent->left = nullptr; // set the parent's left child to null
			}
			else // when curr is in the right branch
			{
				itr.curr->parent->right = nullptr; // set the parent's right child to null
			}
			
			// delete the node
			delete itr.curr;
		}
		else if ((itr.curr->left == nullptr || itr.curr->right == nullptr) && itr.curr->parent != nullptr) // one child and non-null parent
		{
			// go to the child
			if (itr.curr->right == nullptr) // when it has left child
			{
				// set the child's parent to be this node's parent
				itr.curr->left->parent = itr.curr->parent;

				// set the parent's child to be this node's child
				if (itr.curr->inLeftBranch) // in the left branch
				{
					itr.curr->parent->left = itr.curr->left;
				}
				else // in the right branch
				{
					itr.curr->parent->right = itr.curr->left;
				}
			}
			else // when it has right child
			{
				// set the child's parent to be this node's parent
				itr.curr->right->parent = itr.curr->parent;

				// set the parent's child to be this node's child
				if (itr.curr->inLeftBranch) // in the left branch
				{
					itr.curr->parent->left = itr.curr->right;
				}
				else // in the right branch
				{
					itr.curr->parent->right = itr.curr->right;
				}
			}

			// delete the node
			delete itr.curr;
		}
		else // two children
		{
			node* temp = itr.curr; // use temp to store the node to be removed
			itr.curr = itr.curr->right; // move right

			bool found = false;
			while (!found) // when the farest left child has not yet found
			{
				if (itr.curr->left != nullptr) // if it has left child
				{
					itr.curr = itr.curr->left; // set to the further left child
				}
				else // if it does not have left child
				{
					found = true; // found, temp is now the farest left element
				}
			}

			// overwrite the node's value to be the farest left value found
			temp->val = itr.curr->val;

			// remove the farest left node
			if (itr.curr->right != nullptr) // when it has right child
			{
				// set the child's parent to be this node's parent
				itr.curr->parent->left = itr.curr->right;

				// set the parent's child to be this node's child
				itr.curr->right->parent = itr.curr->parent;

				delete itr.curr;
			}
			else // when it does not have right child
			{
				delete itr.curr; // directly delete the farest left node
			}
		}
	}

	Tree::iterator Tree::begin() const
	{
		if (!root) // when the node is null, the tree is empty
		{
			return iterator(nullptr, this); // return iterator as a null
		}

		node* temp = root; // start checking from the root

		while (temp->left != nullptr) // while the left node is not null, the current one is not the smallest
		{
			temp = temp->left; // go left for a smaller node
		}

		return iterator(temp, this); // return the iterator of the smallest node
	}

	Tree::iterator Tree::end() const
	{
		return iterator(nullptr, this); // return the past-the-end iterator for a null
	}

	int Tree::size() const
	{
		return theSize; // return the number of elements in the Tree
	}

	Tree::iterator Tree::find(const double& _double) const
	{
		node* temp = root; // start from the root
		bool found = false; // initialize as false (not found yet)

		while(!found) // while the value has not found
		{
			if (temp->val > _double) // the value is smaller
			{
				temp = temp->left; // go left
			}
			else if (temp->val < _double) // the value is larger
			{
				temp = temp->right; // go right
			}
			else if (temp->val == _double) // values matched, value found in the tree
			{
				found = true; // found the value
			}
			else // when nothing matched
			{
				temp = nullptr; // to return the past-the-end iterator for a null
				break;
			}
		}

		return iterator(temp, this); // return the iterator of the node found in the tree
	}

	void Tree::destroyHelper(node* _node)
	{
		if (_node != nullptr) // when the starting node is not empty
		{
			destroyHelper(_node->left); // recursively delete its left child
			destroyHelper(_node->right); // recursively delete its right child

			delete _node; // self destroy
		}
	}

	void Tree::traverseInsert(node* _node)
	{
		if (_node != nullptr) // when the given node is not null
		{
			insert(_node->val); // insert the value into the tree

			if (_node->left != nullptr) // when the left child is not empty
			{
				traverseInsert(_node->left); // recursively checking and inserting the left child
			}
			
			if (_node->right != nullptr) // when the right child is not empty
			{
				traverseInsert(_node->right); // recursively checking and inserting the right child
			}
		}
	}


	void swap(Tree& left, Tree& right)
	{
		std::swap(left.root, right.root); // swap the root of the tree
		std::swap(left.theSize, right.theSize); // swap the number of element of the tree
	}




	Tree::node::node(double _val)
		: val(_val)
	{
		// initially set the parent, left child, and right child as null
		parent = nullptr;
		left = nullptr;
		right = nullptr;

		inLeftBranch = true; // set the initial node as 'in the left branch'
	}


	bool Tree::node::insertNode(node* _node)
	{
		bool canInsert = false; // can not insert (0)

		if (val < _node->val) // when the new node is larger, go to the right
		{
			canInsert = true; // can insert (1)

			if (right) // when it has right child
			{
				right->insertNode(_node); // recurse upon the right child
			}
			else // when it doesn't have right child
			{
				_node->inLeftBranch = false; // in right branch
				right = _node; // set the right child as the new node
				_node->parent = this; // set the right child's parent as itself
			}
		}
		else if (val > _node->val) // when the new node is smaller, go to the left
		{
			canInsert = true; // can insert (1)
			
			if (left) // when it has left child
			{
				left->insertNode(_node); // recurse upon the left child
			}
			else // when it doesn't have left child
			{
				_node->inLeftBranch = true; // in left branch
				left = _node; // set the left child as the new node
				_node->parent = this; // set the left child's parent as itself
			}
		}
		else // when the new node is neither larger nor smaller (is equal)
		{
			delete _node; // nothing to be added, delete the new node created (memory freed)
		}

		return canInsert; // return 1 (true) if successfully insert the node
	}




	Tree::iterator::iterator(node* n, const Tree* tree)		 // constructor
		: curr(n),container(tree)
	{
		/*empty*/
	}

	Tree::iterator& Tree::iterator::operator++()		// prefix++
	{
		if (curr == nullptr) // when the node is empty (past-the-end pointer)
		{
			return *this; // increased nothing
		}
		else if (curr->right != nullptr && curr->right->left == nullptr) // has right child, which has no left child
		{
			curr = curr->right; // the next is the right child
		}
		else if (curr->right != nullptr && curr->right->left != nullptr) // has right child, which has left child
		{
			curr = curr->right; // go to the right child

			bool found = false;
			while (!found) // while not yet found the farest left value
			{
				if (curr->left != nullptr) // if the further left node is not empty
				{
					curr = curr->left; // go to the further left node
				}
				else // if the further left node is empty
				{
					found = true; // the farest left value is found
				}
			}
		}
		else if (curr->right == nullptr) // has no right child
		{
			if (curr == container->root) // when the current node is the root
			{
				curr = nullptr; // set to the past-the-end nullptr
			}
			else if (curr->inLeftBranch) // in the left branch
			{
				curr = curr->parent; // the next one is its parent
			}
			else // in the right branch
			{
				// find the parent: left, ... , right
				while (curr->parent != nullptr && !curr->inLeftBranch) // while the parent is in the right branch
				{
					curr = curr->parent; // go left up
				}
				
				curr = curr->parent; // go right up once the parent is in the left branch
			}
		}
		
		return *this; // return the iterator for the next value found
	}

	Tree::iterator Tree::iterator::operator++(int unused)		// postfix++
	{
		iterator copy(*this); // make a copy for non increased iterator
		++(*this); // increment

		return copy; // return the non increased copy
	}

	Tree::iterator& Tree::iterator::operator--()			// prefix--
	{
		if (curr == nullptr) // past-the-end null node
		{
			// find the farst right node
			node* temp = container->root;  // make a copy of the root
			
			if (temp == nullptr) // when the root is empty
			{
				return *this; // return the current null iterator
			}
			
			while (temp->right != nullptr) // when the further right node is not empty
			{
				temp = temp->right; // go to the further right node
			}

			curr = temp; // set the current node to be the farest right node (the largest value) found
		}
		else if (curr->left != nullptr && curr->left->right == nullptr) // non-empty left child, which does not have right child 
		{
			curr = curr->left; // set to the left child
		}
		else if (curr->left != nullptr && curr->left->right != nullptr) // non-empty left child, which has right child 
		{
			curr = curr->left; // go left

			bool found = false;
			while (!found) // while not found
			{
				if (curr->right != nullptr) // when the right is not empty
				{
					curr = curr->right; // go right
				}
				else // when the right child is empty
				{
					found = true; // found the node
				}
			}
		}
		else if (curr->left == nullptr) // has no left child
		{
			if (curr == container->root) // no parent
			{
				return *this; // the decrement does nothing
			}
			else if (!curr->inLeftBranch) // in the right branch
			{
				curr = curr->parent; // the previoud one is its parent
			}
			else // in the left branch
			{
				node* temp = curr;

				// find the smaller parent: right, ... , left
				while (temp->parent != nullptr && temp->inLeftBranch)
				{
					temp = temp->parent; // go right up
				}

				temp = temp->parent; // go left up once the parent is in the right branch
				
				if (temp != nullptr) // when there exists smaller parent
				{
					curr = temp; // set the decreased curr to be the smaller node found

				} // otherwise the curr will stay the same as the farest left node
			}
		}

		return *this; // return the iterator for the previous value found
	}

	Tree::iterator Tree::iterator::operator--(int unused)		// postfix--
	{
		iterator copy(*this); // make a non-decreased copy
		--(*this); // decrement

		return copy; // return the non decreased copy
	}

	const double& Tree::iterator::operator*() const	// dereference operator
	{
		return curr->val; // return its relevant value
	} 



	bool operator==(const Tree::iterator& left, const Tree::iterator& right) // operator==
	{
		return ((left.curr == right.curr) && (left.container == right.container)); // true if two iterators are the same
	}

	bool operator!=(const Tree::iterator& left, const Tree::iterator& right) // operator!=
	{
		return !(left == right); // true if two iterators are NOT the same
	}
}