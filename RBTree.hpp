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

				if ((uncle != this->_nil) && (uncle != NULL) && (uncle->_color == _RED))
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

			void	_rotateLeft(node_pointer node)
			{
				node_pointer	tempNode;

				tempNode = node->_rightChild;
				node->_rightChild = tempNode->_leftChild;

				if (tempNode->_leftChild != this->_nil)
					tempNode->_leftChild->_parent = node;
				tempNode->_parent = node->_parent;

				if (node->_parent == NULL)
					this->_root = tempNode;
				else if (node == node->_parent->_leftChild)
					node->_parent->_leftChild = tempNode;
				else
					node->_parent->_rightChild = tempNode;
				tempNode->_leftChild = node;
				node->_parent = tempNode;
				this->_root->_parent = NULL;
			}

			void	_rotateRight(node_pointer node)
			{
				node_pointer	tempNode;

				tempNode = node->_leftChild;
				node->_leftChild = tempNode->_rightChild;

				if (tempNode->_rightChild != this->_nil)
					tempNode->_rightChild->_parent = node;
				tempNode->_parent = node->_parent;

				if (node->_parent == NULL)
					this->_root = tempNode;
				else if (node == node->_parent->_leftChild)
					node->_parent->_leftChild = tempNode;
				else
					node->_parent->_rightChild = tempNode;
				tempNode->_rightChild = node;
				node->_parent = tempNode;
				this->_root->_parent = NULL;
			}

			node_pointer	_getSibling(node_pointer node)
			{
				if (node == node->_parent->_leftChild)
					return (node->_parent->_rightChild);
				else
					return (node->_parent->_leftChild);
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

			void	_transPlant(node_pointer swapA, node_pointer swapB)
			{
				if (swapA->_parent == NULL) {
					this->_root = swapB;
				}
				else if (swapA == swapA->_parent->_leftChild) {
					swapA->_parent->_leftChild = swapB;
				}
				else {
					swapA->_parent->_rightChild = swapB;
				}
				swapB->_parent = swapA->_parent;
			}

			void	_deleteFixUp(node_pointer node)
			{
				node_pointer	sibling = NULL;

				while ((node != this->_root) && (node->_color == _BLACK)) {
					if (node == node->_parent->_leftChild) {
						sibling = this->_getSibling(node);

						if (sibling->_color == _RED) {
							sibling->_color = _BLACK;
							node->_parent->_color = _RED;
							this->_rotateLeft(node->_parent);
							sibling = node->_parent->_rightChild;
						}

						if (sibling->_leftChild->_color == _BLACK && sibling->_rightChild->_color == _BLACK) {
							sibling->_color = _RED;
							node = node->_parent;
						}
						else if (sibling->_leftChild->_color == _RED && sibling->_rightChild->_color == _BLACK) {
							sibling->_color = _RED;
							sibling->_leftChild->_color = _BLACK;
							this->_rotateRight(sibling);
							sibling = this->_getSibling(node);
							// sibling = node->_parent->_rightChild;
						}

						if (sibling->_rightChild->_color == _RED) {
							sibling->_color = node->_parent->_color;
							sibling->_rightChild->_color = _BLACK;
							node->_parent->_color = _BLACK;
							this->_rotateLeft(node->_parent);
							node = this->_root;
						}
					}
					else {
						sibling = this->_getSibling(node);

						if (sibling->_color == _RED) {
							sibling->_color = _BLACK;
							node->_parent->_color = _RED;
							this->_rotateRight(node->_parent);
							sibling = this->_getSibling(node);
						}

						if (sibling->_leftChild->_color == _BLACK && sibling->_rightChild->_color == _BLACK) {
							sibling->_color = _RED;
							node = node->_parent;
						}
						else if (sibling->_rightChild->_color == _RED && sibling->_leftChild->_color == _BLACK) {
							sibling->_color = _RED;
							sibling->_rightChild->_color = _BLACK;
							this->_rotateLeft(sibling);
							sibling = this->_getSibling(node);
						}

						if (sibling->_leftChild->_color == _RED) {
							sibling->_color = node->_parent->_color;
							sibling->_leftChild->_color = _BLACK;
							node->_parent->_color = _BLACK;
							this->_rotateRight(node->_parent);
							node = this->_root;
						}
					}
				}
				node->_color = _BLACK;
			}

		public:
			explicit RBTree(const value_compare& comp) : _comp(comp) {
				this->_nil = _createNode();
				this->_nil->_color = _BLACK;
				this->_nil->_leftChild = this->_nil->_rightChild = this->_nil;
				this->_root = this->_nil;
			}

			RBTree(const RBTree& x) : _alloc(x._alloc), _comp(x._comp) {
				this->_nil = _createNode();
				this->_nil->_color = _BLACK;
				this->_nil->_leftChild = this->_nil->_rightChild = this->_nil;
				this->_root = this->_nil;

				this->copyTree(x, x._root);
			}

			virtual ~RBTree() {}

			RBTree&	operator= (const RBTree& x) {
				if (this == &x)
					return (*this);
				
				this->clearTree(this->_root);
				this->copyTree(x, x._root);
			}

			node_pointer	getRoot(void) const
			{
				return (this->_root);
			}

			node_alloc	getAlloc(void) const
			{
				return (this->_alloc);
			}

			node_pointer	getNil(void) const
			{
				return (this->_nil);
			}

			ft::pair< node_pointer, bool >	insertNode(const value_type& val)
			{
				node_pointer checkExisted = this->findNode(val);

				if (checkExisted != this->_nil)
					return (ft::make_pair< node_pointer, bool >(checkExisted, false)) ;

				node_pointer node = this->_createNode(val);

				// std::cout << val << "is Creating.." << std::endl;

				if (this->_root == this->_nil)
				{
					this->_root = node;
					node->_leftChild = this->_nil;
					node->_rightChild = this->_nil;
					node->_color = _BLACK;

					return (ft::make_pair< node_pointer, bool >(this->_root, true));
				}

				this->_insertNodeHelper(this->_root, node);

				node->_color = _RED;
				node->_leftChild = this->_nil;
				node->_rightChild = this->_nil;

				this->_insertCase1(node);
				return (ft::make_pair< node_pointer, bool >(node, true));
			}

			bool	deleteNode(const value_type& val)
			{
				if (this->_root == this->_nil)
					return (false);
				
				node_pointer	delNode = this->findNode(val);
				if (delNode == this->_nil)
					return (false);
				node_pointer	originPos;
				bool	tempColor;

				tempColor = delNode->_color;
				if (delNode->_leftChild == this->_nil) {
					originPos = delNode->_rightChild;
					this->_transPlant(delNode, delNode->_rightChild);
				}
				else if (delNode->_rightChild == this->_nil) {
					originPos = delNode->_leftChild;
					this->_transPlant(delNode, delNode->_leftChild);
				}
				else {
					node_pointer	tempNode;
					tempNode = delNode->_rightChild;
					for (; tempNode->_leftChild != this->_nil; tempNode = tempNode->_leftChild)
						;
					originPos = tempNode->_rightChild;
					tempColor = tempNode->_color;

					this->_transPlant(tempNode, tempNode->_rightChild);
					tempNode->_rightChild = delNode->_rightChild;
					tempNode->_rightChild->_parent = tempNode;

					this->_transPlant(delNode, tempNode);
					tempNode->_leftChild = delNode->_leftChild;
					tempNode->_leftChild->_parent = tempNode;
					tempNode->_color = delNode->_color;
					std::cout << this->_nil << std::endl;
				}
				// std::cout << "Delete Node Complete" << std::endl;
				// this->show_tree(this->_root, "", true);
				if (tempColor == _BLACK)
					this->_deleteFixUp(originPos);
				this->_nil->_parent = NULL; // 3번째 if 분기에서 nil 노드를 픽스업을 하기 위한 기준을 저장하기 위한 임시 노드로써 사용을 했기 때문에 원래 의도 대로 nil의 부모는 다시 NULL로써 초기화 하여 원래의 nil 노드의 의도로 되돌리기.
				// this->show_tree(this->_root, "", true);
				this->_deleteNode(delNode);
				return (true);
			}

			node_pointer	findNode(const value_type& val) const
			{
				for (node_pointer targetNode = this->_root; targetNode != this->_nil;)
				{
					if (this->_comp(targetNode->_data, val))
					{
						targetNode = targetNode->_rightChild;
					} else {
						if (this->_comp(val, targetNode->_data))
							targetNode = targetNode->_leftChild;
						else
							return (targetNode);
					}
				}

				return (this->_nil);
			}

			node_pointer	getFirstNode(void) const {
				if (this->_root == this->_nil)
					return (this->_nil);
				node_pointer curNode = this->_root;
				
				for (; curNode->_leftChild != this->_nil; curNode = curNode->_leftChild)
					;
				return (curNode);
			}

			node_pointer	getLastNode(void) const {
				if (this->_root == this->_nil)
					return (this->_nil);
				node_pointer curNode = this->_root;
				
				for (; curNode->_rightChild != this->_nil; curNode = curNode->_rightChild)
					;
				return (curNode);
			}

			node_pointer	getNextNode(const node_pointer node) const
			{
				if (node == this->_nil)
					return (this->getFirstNode());
				
				if (node->_rightChild != this->_nil) {
					node_pointer	curNode = node->_rightChild;
					for (; curNode->_leftChild != this->_nil; curNode = curNode->_leftChild)
						;
					return (curNode);
				}
				
				for (node_pointer curNode = node; true; curNode = curNode->_parent) {
					if (curNode->_parent == NULL)
						return (this->_nil);
					if (curNode == curNode->_parent->_leftChild)
						return (curNode->_parent);
				}
				return (this->_nil);
			}

			node_pointer	getPrevNode(const node_pointer node) const
			{
				if (node == this->_nil)
					return (this->getLastNode());
				
				if (node->_leftChild != this->_nil) {
					node_pointer curNode = node->_leftChild;
					for (; curNode->_rightChild != this->_nil; curNode = curNode->_rightChild)
						;
					return (curNode);
				}

				for (node_pointer curNode = node; true; curNode = curNode->_parent) {
					if (curNode->_parent == NULL)
						return (this->_nil);
					if (curNode == curNode->_parent->_rightChild)
						return (curNode->_parent);
				}
				return (this->_nil);
			}

			void	copyTree(const RBTree& toTree, node_pointer node)
			{
				if (node == toTree._nil)
					return ;
				this->insertNode(node->_data);
				this->copyTree(toTree, node->_leftChild);
				this->copyTree(toTree, node->_rightChild);
			}

			void	clearTree(node_pointer node)
			{
				if (node == this->_nil)
					return ;
				this->clearTree(node->_leftChild);
				this->clearTree(node->_rightChild);

				if (node == this->_root)
					this->_root = this->_nil;
				else {
					node_pointer	tempNode = node;
					
					if (node == node->_parent->_leftChild)
						node->_parent->_leftChild = this->_nil;
					else
						node->_parent->_rightChild = this->_nil;
					node = this->_nil;
					this->_deleteNode(tempNode);
				}
			}

			node_pointer	lowerBound(node_pointer node) {
				if (node == this->_nil)
					return (this->_nil);
				
				if (this->_comp(this->getMaxNode(this->_root)->_data, node->_data))
					return (this->_nil);
				for (node_pointer curNode = this->_root; ;) {
					if (this->_comp(curNode->_data, node->data)) {
						if (curNode->_rightChild == this->_nil)
							return (this->getNextNode(curNode));
						curNode = curNode->_rightChild;
					}
					else {
						if (!this->_comp(node->_data, curNode->_data))
							return (curNode);
						if (curNode->_leftChild == this->_nil)
							return (curNode);
						curNode = curNode->_leftChild;
					}
				}
			}

			node_pointer	upperBound(node_pointer node) {
				if (node == this->_nil)
					return (this->_nil);
				
				if (this->_comp(this->getMaxNode(this->_root)->_data, node->_data))
					return (this->_nil);
				for (node_pointer curNode = this->_root; ;) {
					if (this->_comp(curNode->_data, node->data)) {
						if (curNode->_rightChild == this->_nil)
							return (this->getNextNode(curNode));
						curNode = curNode->_rightChild;
					}
					else {
						if (curNode->_leftChild == this->_nil)
							return (curNode);
						curNode = curNode->_leftChild;
					}
				}
			}

			// void show_tree(RBNode* root, std::string indent, bool last)
			// {
			// 	// print the tree structure on the screen
			// 	if (root == this->_root && this->_root != this->_nil && this->_root != NULL && this->_root->_parent == NULL)
			// 	{
			// 		std::cout << indent;
			// 		if (last)
			// 		{
			// 			// std::cout << "R----";
			// 			indent += "    ";
			// 		}
			// 		else
			// 		{
			// 			// std::cout << "L----";
			// 			indent += "|    ";
			// 		}

			// 		// std::string sColor = (root->_color == RED) ? "RED" : "BLACK";
			// 		std::cout << "NULL " << std::endl;;
			// 	}
			// 	if (root == this->_nil)
			// 	{
			// 		std::cout << indent;
			// 		if (last)
			// 		{
			// 			std::cout << "R----";
			// 			indent += "     ";
			// 		}
			// 		else
			// 		{
			// 			std::cout << "L----";
			// 			indent += "|    ";
			// 		}

			// 		// std::string sColor = (root->_color == RED) ? "RED" : "BLACK";
			// 		std::cout << "NIL" << std::endl;
			// 	}
			// 	if (root != this->_nil)
			// 	{
			// 		std::cout << indent;
			// 		if (last)
			// 		{
			// 			std::cout << "R----";
			// 			indent += "     ";
			// 		}
			// 		else
			// 		{
			// 			std::cout << "L----";
			// 			indent += "|    ";
			// 		}

			// 		std::string sColor = (root->_color == _RED) ? "RED" : "BLACK";
			// 		std::cout << root->_data << "(" << sColor << ")" << std::endl;
			// 		show_tree(root->_leftChild, indent, false);
			// 		show_tree(root->_rightChild, indent, true);
			// 	}
			// }

			// void printInorder(RBNode* root)
			// {
			// 	if (root == this->_nil)
			// 		return ;
			// 	this->printInorder(root->_leftChild);
			// 	this->vector.push_back(root->_data);
			// 	std::cout << root->_data << " ";
			// 	this->printInorder(root->_rightChild);
			// }

			// void check_traversal()
			// {
			// 	RBNode* curr = this->_root;
			// 	RBNode* prev = NULL;
			// 	while (1)
			// 	{
			// 		// std::cout << curr->_data << std::endl;
			// 		this->vector.push_back(curr->_data);
			// 		if (prev == curr->_rightChild)
			// 		{
			// 			prev = curr;
			// 			if (curr->_parent != NULL)
			// 				curr = curr->_parent;
			// 			else
			// 				return ;
			// 			continue ;
			// 		}
			// 		else if (prev == curr->_leftChild)
			// 		{
			// 			prev = curr;
			// 			if (curr->_rightChild == this->_nil)
			// 				curr = curr->_parent;
			// 			else
			// 				curr = curr->_rightChild;
			// 			continue ;
			// 		}

			// 		if (curr->_leftChild != this->_nil)
			// 		{
			// 			prev = curr;
			// 			curr = curr->_leftChild;
			// 			continue ;	
			// 		}
			// 		if (curr->_rightChild != this->_nil)
			// 		{
			// 			prev = curr;
			// 			curr = curr->_rightChild;
			// 			continue ;
			// 		}
			// 		prev = curr;
			// 		curr = curr->_parent;
			// 		continue ;
			// 	}
			// }
	};
}

#endif