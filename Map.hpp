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
				public:
					_Compare	comp;
					value_compare(_Compare c) : comp(c) {}
				
				public:
					typedef bool	result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;

					bool	operator() (const value_type& x, const value_type& y) const
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
				treeAlloc.construct(this->_tree, ft::RBTree< value_type, value_compare, allocator_type >(value_compare(this->_comp)));
			}

			template < typename _InputIterator >
			map (_InputIterator first, _InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(), typename ft::enable_if< !ft::is_integral< _InputIterator >::value, _InputIterator >::type* = NULL) : _tree(NULL), _comp(comp), _size(0), _alloc(alloc) {
				_treeAlloc	treeAlloc;
				this->_tree = treeAlloc.allocate(1);
				treeAlloc.construct(this->_tree, ft::RBTree< value_type, value_compare, allocator_type >(value_compare(this->_comp)));

				this->insert(first, last);
			}

			map (const map& x) : _comp(x._comp), _size(x._size), _alloc(x._alloc) {
				_treeAlloc	treeAlloc;
				this->_tree = treeAlloc.allocate(1);
				treeAlloc.construct(this->_tree, *(x._tree));
			}

			virtual ~map() {
				_treeAlloc	treeAlloc;
				treeAlloc.destroy(this->_tree);
				treeAlloc.deallocate(this->_tree, 1);
			}

			map&	operator= (const map& x) {
				if (this == &x)
					return (*this);

				this->_size = x._size;
				*this->_tree = *x.tree;
				return (*this);
			}

			mapped_type&	operator[] (const key_type& k) {
				return (*((this->insert(ft::make_pair(k, mapped_type()))).first).second);
			}

			iterator	begin(void) {
				return (iterator(this->_tree->getFirstNode(), this->_tree));
			}

			const_iterator	begin(void) const {
				return (const_iterator(this->_tree->getFirstNode(), this->_tree));
			}

			iterator	end(void) {
				return (iterator(this->_tree->getNil(), this->_tree));
			}

			const_iterator	end(void) const {
				return (const_iterator(this->_tree->getNil(), this->_tree));
			}

			reverse_iterator	rbegin(void) {
				return (reverse_iterator(this->end(), this->_tree));
			}

			const_reverse_iterator	rbegin(void) const {
				return (const_reverse_iterator(this->end(), this->_tree));
			}

			bool	empty(void) const {
				return (this->_size == 0);
			}

			size_type	size(void) const {
				return (this->_size);
			}

			size_type	max_size(void) const {
				return (this->_tree->getAlloc().max_size());
			}

			ft::pair< iterator, bool > insert (const value_type& val) {
				ft::pair< node_pointer, bool >	res = this->_tree->insertNode(val);
				if (res.second == true)
					++this->_size;
				return (ft::make_pair< iterator, bool >(iterator(res.first, this->_tree), res.second));
			}

			iterator	insert(iterator position, const value_type& val) {
				(void)position;
				ft::pair< node_pointer, bool >	res = this->_tree->insertNode(val);
				if (res.second == true)
					++this->_size;
				return (iterator(res.first, this->_tree));
			}

			template < typename _InputIterator >
			void	insert(_InputIterator first, _InputIterator last, typename ft::enable_if< !ft::is_integral< _InputIterator >::value, _InputIterator >::type* = NULL) {
				for (_InputIterator iter = first; iter != last; ++iter)
					this->insert(*iter);
			}

			void	erase(iterator position) {
				if (this->_tree->deleteNode(position->getPtr()->_data) == true)
					--this->_size;
			}

			size_type	erase(const key_type* k) {
				if (this->_tree->deleteNode(ft::make_pair(k, mapped_type())) == true)
					--this->_size;
				return (1);
			}

			void	erase(iterator first, iterator last) {
				for (iterator iter = first; iter != last; ++iter)
					this->erase(iter);
			}

			void	swap(map& x)
			{
				char buf[sizeof(map)];
				memcpy(reinterpret_cast<void *>(buf), reinterpret_cast<void *>(this), sizeof(map));
				memcpy(reinterpret_cast<void *>(this), reinterpret_cast<void *>(&x), sizeof(map));
				memcpy(reinterpret_cast<void *>(&x), reinterpret_cast<void *>(buf), sizeof(map));
			}

			void	clear(void) {
				this->_tree->clearTree(this->_tree->_nil);
				this->_size = 0;
			}

			key_compare	key_comp(void) const {
				return (this->_comp);
			}

			value_compare	value_comp(void) const {
				return (value_compare(this->_comp));
			}

			iterator	find(const key_type& k) {
				node_pointer	res = this->_tree->findNode(ft::make_pair(k, mapped_type()));
				if (res == this->_tree->_nil)
					return (this->end());
				return (iterator(res, this->_tree));
			}

			const_iterator	find(const key_type& k) const {
				node_pointer	res = this->_tree->findNode(ft::make_pair(k, mapped_type()));
				if (res == this->_tree->_nil)
					return (this->end());
				return (const_iterator(res, this->_tree));
			}

			size_type	count (const key_type& k) const {
				node_pointer	res = this->_tree->findNode(ft::make_pair(k, mapped_type()));
				if (res == this->_tree->_nil)
					return (0);
				return (1);
			}

			iterator	upper_bound (const key_type& k) {
				node_pointer	upperNode = this->_tree->upperBound(ft::make_pair(k, mapped_type()));

				if (upperNode == this->_tree->_nil)
					return (this->end());
				return (iterator(upperNode, this->_tree));
			}

			const_iterator	upper_bound (const key_type& k) const {
				node_pointer	upperNode = this->_tree->upperBound(ft::make_pair(k, mapped_type()));

				if (upperNode == this->_tree->_nil)
					return (this->end());
				return (const_iterator(upperNode, this->_tree));
			}

			iterator	lower_bound (const key_type& k) {
				node_pointer	lowerNode = this->_tree->lowerBound(ft::make_pair(k, mapped_type()));
				
				if (lowerNode == this->_tree->_nil)
					return (this->end());
				return (iterator(lowerNode, this->_tree));
			}

			const_iterator	lower_bound (const key_type& k) const {
				node_pointer	lowerNode = this->_tree->lowerBound(ft::make_pair(k, mapped_type()));

				if (lowerNode == this->_tree->_nil)
					return (this->end());
				return (const_iterator(lowerNode, this->_tree));
			}

			ft::pair< const_iterator, const_iterator >	equal_range (const key_type& k) const {
				return (ft::pair< const_iterator, const_iterator >(this->lower_bound(k), this->upper_bound(k)));
			}

			ft::pair< iterator, iterator >	equal_range (const key_type& k) {
				return (ft::pair< iterator, iterator >(this->lower_bound(k), this->upper_bound(k)));
			}

			allocator_type	get_allocator(void) const {
				return (this->_alloc);
			}
	};

	template < typename _Key, typename _T, typename _Compare, typename _Alloc >
	bool	operator== (const map< _Key, _T, _Compare, _Alloc >& lhs, const map< _Key, _T, _Compare, _Alloc >& rhs) {
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	template < typename _Key, typename _T, typename _Compare, typename _Alloc >
	bool	operator!= (const map< _Key, _T, _Compare, _Alloc >& lhs, const map< _Key, _T, _Compare, _Alloc >& rhs) {
		return (!(lhs == rhs));
	}
	template < typename _Key, typename _T, typename _Compare, typename _Alloc >
	bool	operator< (const map< _Key, _T, _Compare, _Alloc >& lhs, const map< _Key, _T, _Compare, _Alloc >& rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template < typename _Key, typename _T, typename _Compare, typename _Alloc >
	bool	operator<= (const map< _Key, _T, _Compare, _Alloc >& lhs, const map< _Key, _T, _Compare, _Alloc >& rhs) {
		return (!(rhs < lhs));
	}
	template < typename _Key, typename _T, typename _Compare, typename _Alloc >
	bool	operator> (const map< _Key, _T, _Compare, _Alloc >& lhs, const map< _Key, _T, _Compare, _Alloc >& rhs) {
		return (!(lhs < rhs));
	}
	template < typename _Key, typename _T, typename _Compare, typename _Alloc >
	bool	operator>= (const map< _Key, _T, _Compare, _Alloc >& lhs, const map< _Key, _T, _Compare, _Alloc >& rhs) {
		return (!(lhs < rhs));
	}

	template < typename _Key, typename _T, typename _Compare, typename _Alloc >
	void	swap (ft::map< _Key, _T, _Compare, _Alloc >& x, ft::map< _Key, _T, _Compare, _Alloc >& y) {
		x.swap(y);
	}
}

#endif