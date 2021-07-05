#ifndef MAPITERATOR_HPP
# define MAPITERATOR_HPP

# include "Iterator.hpp"
# include "RBTree.hpp"
# include "utils.hpp"

namespace ft {
	template < typename _T, typename _Compare, bool _isConst >
	class MapIterator {
		public:
			typedef _T	value_type;
			typedef _Compare	compare_type;
			typedef std::ptrdiff_t	difference_type;
			typedef typename ft::typeSelector< value_type*, const value_type*, _isConst >::type	pointer;
			typedef typename ft::typeSelector< value_type&, const value_type&, _isConst >::type	reference;
			typedef typename ft::bidrectional_iterator_tag	iterator_category;

			typedef const ft::RBTree< value_type, compare_type >*	tree_type;

			typedef typename ft::typeSelector< typename ft::RBTree< value_type, compare_type>::RBNode, const typename ft::RBTree< value_type, compare_type>::RBNode, _isConst>::type	node_type;
			// typedef node_type*	node_pointer;
			// typedef node_type&	node_reference;
			typedef typename ft::typeSelector< typename ft::RBTree< value_type, compare_type>::RBNode*, const typename ft::RBTree< value_type, compare_type>::RBNode*, _isConst>::type node_pointer;
			typedef typename ft::typeSelector< typename ft::RBTree< value_type, compare_type>::RBNode&, const typename ft::RBTree< value_type, compare_type>::RBNode&, _isConst>::type node_reference;

		protected:
			tree_type	_tree;
			node_pointer	_ptr;

		public:
			MapIterator(node_pointer ptr = NULL, ft::RBTree< value_type, compare_type >* tree = NULL) : _tree(tree), _ptr(ptr) {}
			// MapIterator(const MapIterator& rhs) : _ptr(rhs.getPtr()) {}
			MapIterator(const MapIterator< value_type, compare_type, false >& rhs) : _tree(rhs.getTree()), _ptr(rhs.getPtr()) {}
			virtual ~MapIterator() {}

			node_pointer	getPtr(void) const
			{
				return (this->_ptr);
			}

			void	setPtr(node_pointer ptr)
			{
				this->_ptr = ptr;
			}

			tree_type	getTree(void) const
			{
				return (this->_tree);
			}

			MapIterator&	operator= (const MapIterator& rhs)
			{
				if (this == &rhs)
					return (*this);
				this->_tree = rhs._tree;
				this->_ptr = rhs._ptr;

				return (*this);
			}

			bool	operator== (const MapIterator< value_type, compare_type, false >& rhs) const
			{
				return (this->_ptr == rhs.getPtr());
			}

			bool	operator== (const MapIterator< value_type, compare_type, true >&	rhs) const
			{
				return (this->_ptr == rhs.getPtr());
			}

			bool	operator!= (const MapIterator< value_type, compare_type, false >& rhs) const
			{
				return (this->_ptr != rhs.getPtr());
			}

			bool	operator!= (const MapIterator< value_type, compare_type, true >& rhs) const
			{
				return (this->_ptr != rhs.getPtr());
			}

			reference	operator* () const
			{
				return (this->_ptr->_data);
			}

			pointer	operator-> () const
			{
				return (&(this->_ptr->_data));
			}

			MapIterator&	operator++ ()
			{
				this->_ptr = this->_tree->getNextNode(this->_ptr);
				return (*this);
			}

			MapIterator	operator++ (int)
			{
				MapIterator	temp(*this);

				operator++();
				return (temp);
			}

			MapIterator&	operator-- ()
			{
				this->_ptr = this->_tree->getPrevNode(this->_ptr);
				return (*this);
			}

			MapIterator	operator-- (int)
			{
				MapIterator	temp(*this);

				operator--();
				return (temp);
			}

	};
}

#endif