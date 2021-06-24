#ifndef LISTITERATOR_HPP
# define LISTITERATOR_HPP

# include "Iterator.hpp"
# include "ListNode.hpp"

namespace ft {
	template < typename _T >
	class ListIterator {
		public:
			typedef _T	value_type;
			typedef std::ptrdiff_t	difference_type;
			typedef _T*	pointer;
			typedef _T&	reference;
			typedef typename ft::bidrectional_iterator_tag	iterator_category;

			typedef ListNode< value_type >	node_type;
			typedef ListNode< value_type >*	node_pointer;
			typedef ListNode< value_type >&	node_reference;
		private:
			node_pointer	_ptr;

		public:
			ListIterator() : _ptr(0) {}
			ListIterator(node_reference rhs) : _ptr(&rhs) {}
			ListIterator(const ListIterator& rhs) : _ptr(rhs._ptr) {}
			virtual ~ListIterator() {}

			node_pointer	getPtr(void)
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

			bool	operator== (const ListIterator&	rhs)
			{
				return (*this->_ptr == rhs._ptr);
			}

			bool	operator!= (const ListIterator& rhs)
			{
				return (*this->_ptr != rhs._ptr);
			}

			reference	operator* ()
			{
				return (this->_ptr->getData());
			}

			pointer	operator-> ()
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