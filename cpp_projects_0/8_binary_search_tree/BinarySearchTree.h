#ifndef _BINARY_SEARCH_TREE_
#define _BINARY_SEARCH_TREE_


namespace pic10b
{
	
	/**
	@class Tree is the binary search tree that will store and manage doubles in a binary order
	*/
	class Tree
	{
		/**
		this free function swaps two Trees and is set as a friend to Tree class 
			to access its private variables
		@param left is the first Tree argument to be swapped with
		@param right is the second Tree argument to be swapped with
		*/
		friend void swap(Tree& left, Tree& right);

	public:

		class iterator;		// public nested class

		Tree() noexcept;	// default constructor
		~Tree();			// destructor

		Tree(const Tree& that);			// copy constructor
		Tree(Tree&& that) noexcept;		// move constructor


		/**
		this is a assignment operator using copy-and-swap idom to assign one tree to another
		@param that is an argument in Tree type to be set equal to
		@return the current Tree object that had been swapped with (assigned to) the argument given
		*/
		Tree& operator=(Tree that) &;	// assignment operator


		/**
		this function adds an double to the tree and 
			increase the size count for the number of elements in the tree
		@param _double is the double type value to be added into the tree
		*/
		void insert(double _double);

		/**
		this function removes a node from the tree by using the given iterator argument
		@param itr is the input argument in iterator type indicating which node to be removed
		*/
		void erase(iterator itr);


		/**
		this function returns the iterator of the smallest element from the tree
			by finding its farest left node
		@return iterator of the node found from the farest left
		*/
		iterator begin() const;

		/**
		this function returns the iterator of the past-the-end iterator of the tree
		@return iterator of the past the final null node from the tree
		*/
		iterator end() const;


		/**
		this function allows the users to get access to the number of elements in the tree
		@return the number of values (doubles) in the tree in int type
		*/
		int size() const;


		/**
		this function finds the position of a double given in the tree, 
			it returns the relevant iterator when found, otherwise returns iterator to nullptr
		@param _double is the value to be found from the tree in double type
		@return iterator of the value found in the tree
		*/
		iterator find(const double& _double) const;

	private:

		class node;		// private nested class

		node* root;
		int theSize;
		

		/**
		this function helps the destructor to recursively delete each node from the tree
			 and free the memory on the heap
		@param _node is the node to begin deleting with
		*/
		void destroyHelper(node* _node);

		/**
		this function helps the copy constructor to recursively copy and insert the nodes
			from one tree to another
		@param _node is the node to begin copying and inserting with
		*/
		void traverseInsert(node* _node);
		
	};


	void swap(Tree& left, Tree& right); // free and friend function declared above

	


	/**
	@class node is a nested class inside Tree, and it stores each node in the tree with the information such as its left and right children,
		it also aids for inserting nodes by providing member variables stored in the nodes
	*/
	class Tree::node
	{
		friend Tree;		// Tree class is a friend
		friend iterator;	// iterator class is a friend

	private:
		
		node(double _val);		// constructor

		node* parent;
		node* left, * right;
		double val;
		bool inLeftBranch;


		/**
		this function helps the insert function from Tree class to insert each node into the tree
			by setting its information such as its parent and children nodes, 
			the relevant double value, and whether it is on the left or right branch from its parent
		@param _node is the node to be inserted
		@return whether or not the node gets successfully inserted (true if gets inserted)
		*/
		bool insertNode(node* _node); // member function for inserting node

	};



	/**
	@class iterator is a nested class inside Tree, it stores the information where the the iterator points to 
		such as the current node, and it also provides operators such as prefix/postfix increment/decrement
		and dereference operator for the user to traverse around the tree
	*/
	class Tree::iterator
	{
		friend Tree;	// Tree class is a friend

		/**
		this free function compares two nodes by using the iterator arguments, 
			and it is set to be a friend to iterator class to access its private variables
		@param left is the first iterator argument to be compared with
		@param right is the second iterator argument to be compared with
		@return whether or not the relevant nodes that the iterators point to are equal
		*/
		friend bool operator==(const iterator& left, const iterator& right); // comparison operator

	public:

		/**
		this function is a prefix increment that increases the iterator 
			and points to the next larger value in the tree
		@return the iterator that points to the next node in the tree
		*/
		iterator& operator++();				// prefix++ operator

		/**
		this function is a postfix increment that increases the iterator
			and points to the next larger value in the tree
		@param unused is an int parameter for the compiler to find the postfix function
		@return the iterator that points to the next node in the tree
		*/
		iterator operator++(int unused);	// postfix++ operator


		/**
		this function is a prefix decrement that decreases the iterator
			and points to the previous smaller value in the tree
		@return the iterator that points to the previous node in the tree
		*/
		iterator& operator--();				// prefix-- operator

		/**
		this function is a postfix decrement that decreases the iterator
			and points to the previous smaller value in the tree
		@param unused is an int parameter for the compiler to find the postfix function
		@return the iterator that points to the previous node in the tree
		*/
		iterator operator--(int unused);	// postfix-- operator


		/**
		this function is a dereference operator that returns the value that the relevant node stores
		@return the value of double type that the iterator's node stores
		*/
		const double& operator*() const;	// dereference operator

	private:

		iterator(node* n, const Tree* tree);	// constructor

		node* curr;
		const Tree* container;

	};


	bool operator==(const Tree::iterator& left, const Tree::iterator& right); // comparison operator==

	/**
	this free function compares two nodes by using the iterator arguments 
		and the friend function operator== that declared above
	@param left is the first iterator argument to be compared with
	@param right is the second iterator argument to be compared with
	@return whether or not the relevant nodes that the iterators point to are NOT equal
	*/
	bool operator!=(const Tree::iterator& left, const Tree::iterator& right); // comparison operator!=

}


#endif