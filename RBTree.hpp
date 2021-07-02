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
				std::cout << "Delete Case 1 Checking.." << std::endl;
				if (node->_parent != NULL)
					this->_deleteCase2(node);
			}

			void	_deleteCase2(node_pointer node)
			{
				node_pointer	sibling = this->_getSibling(node);

				std::cout << "Delete Case 2 Checking.." << std::endl;
				if (sibling->_color == _RED) {
					node->_parent->_color = _RED;
					sibling->_color = _BLACK;
					if (node == node->_parent->_leftChild)
						this->_rotateLeft(node->_parent);
					else
						this->_rotateRight(node->_parent);
				}
				this->_deleteCase3(node);
			}

			void	_deleteCase3(node_pointer node)
			{
				node_pointer	sibling = this->_getSibling(node);

				std::cout << "Delete Case 3 Checking.." << std::endl;
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

				std::cout << "Delete Case 4 Checking.." << std::endl;
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

				std::cout << "Delete Case 5 Checking.." << std::endl;
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

				std::cout << "Delete Case 6 Checking.." << std::endl;
				sibling->_color = node->_parent->_color;
				node->_parent->_color = _BLACK;
				if (node == node->_parent->_leftChild) {
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
				node_pointer checkExisted = this->findNode(val);

				if (checkExisted != this->_nil)
					return ;

				node_pointer node = this->_createNode(val);

				std::cout << val << "is Creating.." << std::endl;

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
				
				node_pointer	delNode = this->findNode(val);
				if (delNode == this->_nil)
					return ;
				std::cout << val << " is deleting.." << std::endl;
				node_pointer	originPos;
				bool	tempColor;

				tempColor = delNode->_color;
				if (delNode->_leftChild == this->_nil) {
					// originPos = delNode->_rightChild;
					this->_transPlant(delNode, delNode->_rightChild);
				}
				else if (delNode->_rightChild == this->_nil) {
					// originPos = delNode->_leftChild;
					this->_transPlant(delNode, delNode->_leftChild);
				}
				else {
					node_pointer	tempNode;
					if (delNode->_leftChild != this->_nil) { // tempNode = 삭제 노드의 왼쪽 트리 중 최대값 노드
						tempNode = delNode->_leftChild;
						for (; tempNode->_rightChild != this->_nil; tempNode = tempNode->_rightChild)
							;
					}
					else { // tempNode = 삭제 노드의 오른쪽 트리 중 최솟값 노드
						tempNode = delNode->_rightChild;
						for (; tempNode->_leftChild != this->_nil; tempNode = tempNode->_leftChild)
							;
					}
					tempColor = delNode->_color;

					this->_transPlant(tempNode, tempNode->_rightChild);
					tempNode->_rightChild = delNode->_rightChild;
					tempNode->_rightChild->_parent = tempNode;

					this->_transPlant(delNode, tempNode);
					tempNode->_leftChild = delNode->_leftChild;
					tempNode->_leftChild->_parent = tempNode;
					tempNode->_color = tempColor;

					originPos = delNode;
				}
				std::cout << "Delete Node Complete" << std::endl;
				this->show_tree(this->_root, "", true);
				if (tempColor == _BLACK)
					this->_deleteCase1(originPos);
				std::cout << "Delete Case Checking Complete" << std::endl;
				this->show_tree(this->_root, "", true);
				this->_deleteNode(delNode);
			}

			node_pointer	findNode(const value_type& val)
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

			void show_tree(RBNode* root, std::string indent, bool last)
			{
				// print the tree structure on the screen
				if (root == this->_root && this->_root != this->_nil && this->_root != NULL && this->_root->_parent == NULL)
				{
					std::cout << indent;
					if (last)
					{
						// std::cout << "R----";
						indent += "    ";
					}
					else
					{
						// std::cout << "L----";
						indent += "|    ";
					}

					// std::string sColor = (root->_color == RED) ? "RED" : "BLACK";
					std::cout << "NULL " << std::endl;;
				}
				if (root == this->_nil)
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

					// std::string sColor = (root->_color == RED) ? "RED" : "BLACK";
					std::cout << "NIL" << std::endl;
				}
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