#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include "utils.hpp"
# include "pair.hpp"
# include "RBTree.hpp"
# include "MapIterator.hpp"

namespace ft {
	template < typename _Key, typename _T, typename _Compare = ft::less< _Key >, typename _Alloc = std::allocator< ft::pair< const _Key, _T > > >
	class map {
		public:
			typedef _Key	key_type;
			typedef _T	mapped_type;
			typedef ft::pair< const key_type, mapped_type >	value_type;
			typedef _Compare	key_compare;
			typedef _Alloc	allocator_type;
			typedef	typename allocator_type::reference	reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer	pointer;
			typedef typename allocator_type::const_pointer	const_pointer;
			typedef std::size_t	size_type;

			class value_compare {
				protected:
					_Compare	comp;
					value_compare(_Compare c) : comp(c) {}
				
				public:
					typedef bool	result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;

					bool	operator() (const value_type& x, const valu_type& y) const
					{
						return (comp(x.first, y.first));
					}
			};

			typedef ft::MapIterator< value_type, value_compare, false >	iterator;
			typedef ft::MapIterator< value_type, value_compare, true >	const_iterator;
			typedef ft::reverse_iterator< iterator >	reverse_iterator;
			typedef ft::reverse_iterator< const_iterator >	const_reverse_iterator;
			typedef typename ft::iterator_traits< iterator >::difference_type	difference_type;
			
			typedef typename ft::RBTree< value_type, value_compare, allocator_type >	tree_type;
			typedef typename ft::RBTree< value_type, value_compare, allocator_type >*	tree_pointer;
			typedef typename ft::RBTree< value_type, value_compare, allocator_type >&	tree_reference;
			
		private:
			typedef typename allocator_type::template rebind< ft::RBTree< value_type, value_compare, allocator_type > >::other _treeAlloc;
			typedef typename tree_type::node_type	node_type;
			typedef typename tree_type::node_reference	node_reference;
			typedef typename tree_type::node_pointer	node_pointer;

		private:
			tree_pointer	_tree;
			key_compare	_comp;
			size_type	_size;
			allocator_type	_alloc;
		
		public:
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _comp(comp), _size(0), _alloc(alloc)
			{
				_treeAlloc	treeAlloc;
				this->_tree = treeAlloc.allocate(1);
				treeAlloc.construct(this->_tree, this->_alloc);
			}
	};
}

#endif