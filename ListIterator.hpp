#ifndef LISTITERATOR_HPP
# define LISTITERATOR_HPP

# include "Iterator.hpp"
# include "ListNode.hpp"
# include "utils.hpp"

namespace ft {
	template < typename _T, bool _isConst >
	class ListIterator {
		public:
			typedef _T	value_type;
			typedef std::ptrdiff_t	difference_type;
			typedef typename ft::typeSelector< value_type*, const value_type*, _isConst >::type	pointer;
			typedef typename ft::typeSelector< value_type&, const value_type&, _isConst >::type	reference;
			typedef typename ft::bidrectional_iterator_tag	iterator_category;

			typedef typename ft::typeSelector< ListNode< value_type >, const ListNode< value_type >, _isConst>::type	node_type;
			typedef typename ft::typeSelector< ListNode< value_type >*, const ListNode< value_type >*, _isConst>::type node_pointer;
			typedef typename ft::typeSelector< ListNode< value_type >&, const ListNode< value_type >&, _isConst>::type node_reference;
		private:
			node_pointer	_ptr;

		public:
			ListIterator() : _ptr(0) {}
			ListIterator(node_pointer rhs) : _ptr(rhs) {}
			// ListIterator(const ListIterator& rhs) : _ptr(rhs.getPtr()) {}
			ListIterator(const ListIterator< value_type, false >& rhs) : _ptr(rhs.getPtr()) {}
			virtual ~ListIterator() {}

			node_pointer	getPtr(void) const
			{
				return (this->_ptr);
			}

			void	setPtr(node_pointer ptr)
			{
				this->_ptr = ptr;
			}

			ListIterator&	operator= (const ListIterator& rhs)
			{
				this->_ptr = rhs._ptr;

				return (*this);
			}

			bool	operator== (const ListIterator< value_type, false >& rhs) const
			{
				return (this->_ptr == rhs.getPtr());
			}

			bool	operator== (const ListIterator< value_type, true >&	rhs) const
			{
				return (this->_ptr == rhs.getPtr());
			}

			bool	operator!= (const ListIterator< value_type, false >& rhs) const
			{
				return (this->_ptr != rhs.getPtr());
			}

			bool	operator!= (const ListIterator< value_type, true >& rhs) const
			{
				return (this->_ptr != rhs.getPtr());
			}

			reference	operator* () const
			{
				return (this->_ptr->getData());
			}

			pointer	operator-> () const
			{
				return (&(this->_ptr->getData()));
			}

			ListIterator&	operator++ ()
			{
				this->_ptr = this->_ptr->getNext();
				return (*this);
			}

			ListIterator	operator++ (int)
			{
				ListIterator	temp(*this);

				operator++();
				return (temp);
			}

			ListIterator&	operator-- ()
			{
				this->_ptr = this->_ptr->getPrev();
				return (*this);
			}

			ListIterator	operator-- (int)
			{
				ListIterator	temp(*this);

				operator--();
				return (temp);
			}

	};
}

#endif