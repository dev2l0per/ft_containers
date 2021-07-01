#ifndef RBTREE_HPP
# define RBTREE_HPP

# include <iostream>
# include <vector>

# define _RED	true
# define _BLACK	false

namespace ft {
	template < typename _T, typename _Compare, typename _Alloc = std::allocator< _T > >
	class RBTree {
		public:
			std::vector< _T > vector;
			typedef _T	value_type;
			typedef _Compare	value_compare;
			typedef _Alloc	allocator_type;
			typedef value_type*	pointer;
			typedef value_type&	reference;

			class RBNode {
				public:
					value_type	_data;
					RBNode*	_parent;
					RBNode*	_leftChild;
					RBNode*	_rightChild;
					bool	_color;
				
				public:
					RBNode() : _data(value_type()), _parent(NULL), _leftChild(NULL), _rightChild(NULL), _color(_RED) {}
					RBNode(const value_type& val) : _data(val), _parent(NULL), _leftChild(NULL), _rightChild(NULL), _color(_RED) {}
					
					virtual ~RBNode() {}
			};

			typedef RBNode	node_type;
			typedef RBNode& node_reference;
			typedef RBNode*	node_pointer;

			typedef typename allocator_type::template rebind< node_type >::other node_alloc;

		private:
			node_pointer	_root;
			node_pointer	_nil;
			node_alloc	_alloc;
			value_compare	_comp;

		private:
			node_pointer	_createNode(const value_type& val = value_type())
			{
				node_pointer node = this->_alloc.allocate(1);
				this->_alloc.construct(node, val);

				return (node);
			}

			void	_deleteNode(node_pointer node)
			{
				this->_alloc.destroy(node);
				this->_alloc.deallocate(node, 1);
			}

			node_pointer	_getGrandParent(node_pointer node)
			{
				if ((node != NULL) && (node->_parent != NULL))
					return (node->_parent->_parent);
				else
					return (NULL);
			}

			node_pointer	_getUncle(node_pointer node)
			{
				node_pointer	grandParent = this->_getGrandParent(node);
				if (grandParent == NULL)
					return (NULL);
				if (node->_parent == grandParent->_leftChild)
					return (grandParent->_rightChild);
				else
					return (grandParent->_leftChild);
			}

			void	_insertCase1(node_pointer node)
			{
				if (node->_parent == NULL)
					node->_color = _BLACK;
				else
					this->_insertCase2(node);
			}

			void	_insertCase2(node_pointer node)
			{
				if (node->_parent->_color == _BLACK)
					return ;
				else
					this->_insertCase3(node);
			}

			void	_insertCase3(node_pointer node)
			{
				node_pointer	uncle = this->_getUncle(node);
				node_pointer	grandParent;

				if ((uncle != NULL) && (uncle->_color == _RED))
				{
					node->_parent->_color = _BLACK;
					uncle->_color = _BLACK;
					grandParent = this->_getGrandParent(node);
					grandParent->_color = _RED;
					this->_insertCase1(grandParent);
				}
				else {
					this->_insertCase4(node);
				}
			}

			void	_insertCase4(node_pointer node)
			{
				node_pointer	grandParent = this->_getGrandParent(node);

				if ((node == node->_parent->_rightChild) && (node->_parent == grandParent->_leftChild)) {
					this->_rotateLeft(node->_parent);
					node = node->_leftChild;
				}
				else if ((node == node->_parent->_leftChild) && (node->_parent == grandParent->_rightChild)) {
					this->_rotateRight(node->_parent);
					node = node->_rightChild;
				}
				this->_insertCase5(node);
			}

			void	_insertCase5(node_pointer node)
			{
				node_pointer	grandParent = this->_getGrandParent(node);

				node->_parent->_color = _BLACK;
				grandParent->_color = _RED;
				if (node == node->_parent->_leftChild)
					this->_rotateRight(grandParent);
				else
					this->_rotateLeft(grandParent);
			}

			void	_deleteCase1(node_pointer node)
			{
				if (node->_parent != NULL)
					this->_deleteCase2(node);
			}

			void	_deleteCase2(node_pointer node)
			{
				node_pointer	sibling = this->_getSibling(node);

				if (sibling->_color == _RED) {
					node->_parent->_color = _RED;
					sibling->_color = _BLACK;
					if (node == node->_parent->_leftChild)
						this->_rotateLeft(node->_parent);
					else
						this->_rotateRight(node->_parent);
				}
			}

			void	_deleteCase3(node_pointer node)
			{
				node_pointer	sibling = this->_getSibling(node);

				if ((node->_parent->_color == _BLACK) && (sibling->_color == _BLACK) &&
				(sibling->_leftChild->_color == _BLACK) && (sibling->_rightChild->_color == _BLACK)) {
					sibling->_color = _RED;
					this->_deleteCase1(node->_parent);
				}
				else
					this->_deleteCase4(node);
			}

			void	_deleteCase4(node_pointer node)
			{
				node_pointer	sibling = this->_getSibling(node);

				if ((node->_parent->_color == _RED) && (sibling->_color == _BLACK) &&
				(sibling->_leftChild->_color == _BLACK) && (sibling->_rightChild->_color == _BLACK)) {
					sibling->_color = _RED;
					node->_parent->_color = _BLACK;
				}
				else
					this->_deleteCase5(node);
			}

			void	_deleteCase5(node_pointer node)
			{
				node_pointer	sibling = this->_getSibling(node);

				if (sibling->_color == _BLACK) {
					if ((node == node->_parent->_leftChild) && (sibling->_rightChild->_color == _BLACK) &&
					(sibling->_leftChild->_color == _RED)) {
						sibling->_color = _RED;
						sibling->_leftChild->_color = _BLACK;
						this->_rotateRight(sibling);
					}
					else if ((node == node->_parent->_rightChild) && (sibling->_leftChild->_color == _BLACK) &&
					(sibling->_rightChild->_color == _RED)) {
						sibling->_color = _RED;
						sibling->_rightChild->_color = _BLACK;
						this->_rotateLeft(sibling);
					}
				}
				this->_deleteCase6(node);
			}

			void	_deleteCase6(node_pointer node)
			{
				node_pointer	sibling = this->_getSibling(node);

				sibling->_color = node->_parent->_color;
				node->_parent->_color = _BLACK;
				if (node == node->_parent->_left) {
					sibling->_rightChild->_color = _BLACK;
					this->_rotateLeft(node->_parent);
				}
				else {
					sibling->_leftChild->_color = _BLACK;
					this->_rotateRight(node->_parent);
				}
			}

			void	_rotateLeft(node_pointer node)
			{
				node_pointer	rightChild = node->_rightChild;
				node_pointer	parent = node->_parent;

				if (rightChild->_leftChild != this->_nil)
					rightChild->_leftChild->_parent = node;
				

				node->_rightChild = rightChild->_leftChild;
				node->_parent = rightChild;
				rightChild->_leftChild = node;
				rightChild->_parent = parent;

				if (parent != NULL)
				{
					if (parent->_leftChild == node)
						parent->_leftChild = rightChild;
					else
						parent->_rightChild = rightChild;
					return ;
				}
				this->_root = rightChild;
			}

			void	_rotateRight(node_pointer node)
			{
				node_pointer	leftChild = node->_leftChild;
				node_pointer	parent = node->_parent;

				if (leftChild != this->_nil)
					leftChild->_rightChild->_parent = node;
				
				node->_leftChild = leftChild->_rightChild;
				node->_parent = leftChild;
				leftChild->_rightChild = node;
				leftChild->_parent = parent;

				if (parent != NULL)
				{
					if (parent->_rightChild == node)
						parent->_rightChild = leftChild;
					else
						parent->_leftChild = leftChild;
				}
				this->_root = leftChild;
			}

			node_pointer	_getSibling(node_pointer node)
			{
				if (node == node->_parent->_leftChild)
					return node->_parent->_rightChild;
				else
					return node->_parent->_leftChild;
			}

			void	_insertNodeHelper(node_pointer insertRoot, node_pointer node)
			{
				if (insertRoot->_data < node->_data) {
					if (insertRoot->_rightChild == this->_nil) {
						insertRoot->_rightChild = node;
						node->_parent = insertRoot;
					}
					else
						this->_insertNodeHelper(insertRoot->_rightChild, node);
				}
				else if (insertRoot->_data > node->_data) {
					if (insertRoot->_leftChild == this->_nil) {
						insertRoot->_leftChild = node;
						node->_parent = insertRoot;
					}
					else
						this->_insertNodeHelper(insertRoot->_leftChild, node);
				}
			}

			void	_deleteNodeHelper(node_pointer node)
			{
				if (node->_leftChild == this->_nil && node->_rightChild == this->_nil) {
					if (node == this->_root)
						this->_root = this->_nil;
					else if (node == node->_parent->_leftChild)
						node->_parent->_leftChild = this->_nil;
					else
						node->_parent->_rightChild = this->_nil;
				}
				else if (node->_leftChild != this->_nil && node->_rightChild == this->_nil) {
					if (node == this->_root)
						this->_root = node->_leftChild;
					else if (node == node->_parent->_leftChild)
						node->_parent->_leftChild = node->_leftChild;
					else
						node->_parent->_rightChild = node->_leftChild;
				}
				else if (node->_leftChild == this->_nil && node->_rightChild != this->_nil) {
					if (node == this->_root)
						this->_root = node->_rightChild;
					else if (node == node->_parent->_leftChild)
						node->_parent->_leftChild = node->_rightChild;
					else
						node->_parent->_rightChild = node->_rightChild;
				}
				else {
					node_pointer	curNode = node;
					node_pointer	findNode = node->_rightChild;
					for (; findNode->_leftChild != this->_nil; findNode = findNode->_leftChild) {
						curNode = findNode;
					}
					if (curNode->_leftChild == findNode)
						curNode->_leftChild = findNode->_rightChild;
					else
						curNode->_rightChild = findNode->_rightChild;
					node->_data = findNode->_data;
					node = findNode;
				}
				this->_root->_parent = NULL;
			}

		public:
			RBTree(const allocator_type& alloc = allocator_type()) : _alloc(alloc) {
				this->_nil = _createNode();
				this->_nil->_color = _BLACK;
				this->_nil->_leftChild = this->_nil->_rightChild = this->_nil;
				this->_root = this->_nil;
			}
			virtual ~RBTree() {}

			node_pointer	getRoot(void) const
			{
				return (this->_root);
			}

			void	insertNode(const value_type& val)
			{
				node_pointer node = this->_createNode(val);

				if (this->_root == this->_nil)
				{
					this->_root = node;
					node->_leftChild = this->_nil;
					node->_rightChild = this->_nil;
					node->_color = _BLACK;

					return ;
				}

				this->_insertNodeHelper(this->_root, node);

				node->_color = _RED;
				node->_leftChild = this->_nil;
				node->_rightChild = this->_nil;

				this->_insertCase1(node);
			}

			void	deleteNode(const value_type& val)
			{
				if (this->_root == this->_nil)
					return ;
				
				node_pointer delNode = this->findNode(val);
				
				if (delNode == this->_nil)
					return ;
				
				this->_deleteNodeHelper(delNode);
				this->_deleteNode(delNode);
				this->_deleteCase1(delNode);
			}

			node_pointer	findNode(const value_type& val)
			{
				node_pointer	curNode = this->_root;

				while (curNode != this->_nil)
				{
					if (this->_comp(curNode->_data, val))
						curNode = curNode->_leftChild;
					else
					{
						if (this->_comp(val, curNode->_data))
							curNode = curNode->_rightChild;
						else
							return (curNode);
					}
				}
				
				return (this->_nil);
			}

			void show_tree(RBNode* root, std::string indent, bool last)
			{
				// print the tree structure on the screen
				// if (root == this->_nil)
				// {
				// 	std::cout << indent;
				// 	if (last)
				// 	{
				// 		std::cout << "R----";
				// 		indent += "     ";
				// 	}
				// 	else
				// 	{
				// 		std::cout << "L----";
				// 		indent += "|    ";
				// 	}

				// 	// std::string sColor = (root->_color == RED) ? "RED" : "BLACK";
				// 	std::cout << "NIL" << std::endl;
				// }
				if (root != this->_nil)
				{
					std::cout << indent;
					if (last)
					{
						std::cout << "R----";
						indent += "     ";
					}
					else
					{
						std::cout << "L----";
						indent += "|    ";
					}

					std::string sColor = (root->_color == _RED) ? "RED" : "BLACK";
					std::cout << root->_data << "(" << sColor << ")" << std::endl;
					show_tree(root->_leftChild, indent, false);
					show_tree(root->_rightChild, indent, true);
				}
			}

			void printInorder(RBNode* root)
			{
				if (root == this->_nil)
					return ;
				this->printInorder(root->_leftChild);
				this->vector.push_back(root->_data);
				std::cout << root->_data << " ";
				this->printInorder(root->_rightChild);
			}

			void check_traversal()
			{
				RBNode* curr = this->_root;
				RBNode* prev = NULL;
				while (1)
				{
					// std::cout << curr->_data << std::endl;
					this->vector.push_back(curr->_data);
					if (prev == curr->_rightChild)
					{
						prev = curr;
						if (curr->_parent != NULL)
							curr = curr->_parent;
						else
							return ;
						continue ;
					}
					else if (prev == curr->_leftChild)
					{
						prev = curr;
						if (curr->_rightChild == this->_nil)
							curr = curr->_parent;
						else
							curr = curr->_rightChild;
						continue ;
					}

					if (curr->_leftChild != this->_nil)
					{
						prev = curr;
						curr = curr->_leftChild;
						continue ;	
					}
					if (curr->_rightChild != this->_nil)
					{
						prev = curr;
						curr = curr->_rightChild;
						continue ;
					}
					prev = curr;
					curr = curr->_parent;
					continue ;
				}
			}
	};
}

#endif