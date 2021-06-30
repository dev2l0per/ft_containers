#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include "utils.hpp"
# include "pair.hpp"
# include "RBTree.hpp"

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
			// iterator
			// const_iterator
			// reverse_iterator
			// const_reverse_iterator
			// difference_type
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
			}
		
			typedef typename ft::RBTree< value_type, value_compare, _Alloc >	node_type;
			typedef typename ft::RBTree< value_type, value_compare, _Alloc >*	node_pointer;
			typedef typename ft::RBTree< value_type, value_compare, _Alloc >&	node_reference;
		private:
	};
}

#endif