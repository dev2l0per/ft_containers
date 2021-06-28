#ifndef LISTITERATOR_HPP
# define LISTITERATOR_HPP

# include "Iterator.hpp"
# include "ListNode.hpp"

namespace ft {
	template < typename _T >
	class ListIterator;
	template < typename _T >
	class ListConstIterator;
	template < typename _T >
	class ListReverseIterator;
	template < typename _T >
	class ListConstReverseIterator;

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
			ListIterator(node_pointer rhs) : _ptr(rhs) {}
			ListIterator(const ListIterator& rhs) : _ptr(rhs._ptr) {}
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

			bool	operator== (const ListIterator&	rhs)
			{
				return (this->_ptr == rhs._ptr);
			}

			bool	operator!= (const ListIterator& rhs)
			{
				return (this->_ptr != rhs._ptr);
			}

			bool	operator!= (const ListConstIterator< _T >& rhs)
			{
				return (this->_ptr != rhs.getPtr());
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

	template < typename _T >
	class ListConstIterator {
		public:
			typedef _T	value_type;
			typedef std::ptrdiff_t	difference_type;
			typedef _T*	pointer;
			typedef const _T*	const_pointer;
			typedef _T&	reference;
			typedef const _T&	const_reference;
			typedef typename ft::bidrectional_iterator_tag	iterator_category;

			typedef ListNode< value_type >	node_type;
			typedef const ListNode< value_type >*	node_pointer;
			typedef ListNode< value_type >&	node_reference;
		private:
			node_pointer	_ptr;

		public:
			ListConstIterator() : _ptr(0) {}
			ListConstIterator(node_pointer rhs) : _ptr(rhs) {}
			ListConstIterator(const ListIterator< _T >& rhs) : _ptr(rhs.getPtr()) {}
			ListConstIterator(const ListConstIterator& rhs) : _ptr(rhs._ptr) {}
			virtual ~ListConstIterator() {}

			node_pointer	getPtr(void) const
			{
				return (this->_ptr);
			}

			void	setPtr(node_pointer ptr)
			{
				this->_ptr = ptr;
			}

			ListConstIterator&	operator= (const ListConstIterator& rhs)
			{
				this->_ptr = rhs._ptr;
				return (*this);
			}

			bool	operator== (const ListConstIterator& rhs) const
			{
				return (this->_ptr == rhs._ptr);
			}

			bool	operator!= (const ListConstIterator& rhs) const
			{
				return (this->_ptr != rhs._ptr);
			}

			const_reference	operator* ()
			{
				return (this->_ptr->getData());
			}

			const_pointer	operator-> ()
			{
				return (&(this->_ptr->getData()));
			}

			ListConstIterator&	operator++ ()
			{
				this->_ptr = this->_ptr->getNext();
				return (*this);
			}

			ListConstIterator	operator++ (int)
			{
				ListConstIterator	temp(*this);

				operator++();
				return (temp);
			}

			ListConstIterator&	operator-- ()
			{
				this->_ptr = this->_ptr->getPrev();
				return (*this);
			}

			ListConstIterator	operator-- (int)
			{
				ListConstIterator	temp(*this);

				operator--();
				return (temp);
			}

	};

	template < typename _T >
	class ListReverseIterator {
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
			ListReverseIterator() : _ptr(0) {}
			ListReverseIterator(node_pointer rhs) : _ptr(rhs) {}
			ListReverseIterator(const ListIterator< _T >& rhs) : _ptr(rhs.getPtr()) {}
			ListReverseIterator(const ListConstIterator< _T >& rhs) : _ptr(rhs.getPtr()) {}
			ListReverseIterator(const ListReverseIterator& rhs) : _ptr(rhs._ptr) {}
			virtual ~ListReverseIterator() {}

			node_pointer	getPtr(void) const
			{
				return (this->_ptr);
			}

			void	setPtr(node_pointer ptr)
			{
				this->_ptr = ptr;
			}

			ListReverseIterator&	operator= (const ListReverseIterator& rhs)
			{
				this->_ptr = rhs._ptr;

				return (*this);
			}

			bool	operator== (const ListReverseIterator&	rhs)
			{
				return (*this->_ptr == rhs._ptr);
			}

			bool	operator!= (const ListReverseIterator& rhs)
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

			ListReverseIterator&	operator++ ()
			{
				this->_ptr = this->_ptr->getPrev();
				return (*this);
			}

			ListReverseIterator	operator++ (int)
			{
				ListReverseIterator	temp(*this);

				operator++();
				return (temp);
			}

			ListReverseIterator&	operator-- ()
			{
				this->_ptr = this->_ptr->getNext();
				return (*this);
			}

			ListReverseIterator	operator-- (int)
			{
				ListReverseIterator	temp(*this);

				operator--();
				return (temp);
			}

	};

	template < typename _T >
	class ListConstReverseIterator {
		public:
			typedef _T	value_type;
			typedef std::ptrdiff_t	difference_type;
			typedef _T*	pointer;
			typedef _T&	reference;
			typedef typename ft::bidrectional_iterator_tag	iterator_category;

			typedef ListNode< value_type >	node_type;
			typedef const ListNode< value_type >*	node_pointer;
			typedef ListNode< value_type >&	node_reference;
		private:
			node_pointer	_ptr;

		public:
			ListConstReverseIterator() : _ptr(0) {}
			ListConstReverseIterator(node_pointer rhs) : _ptr(rhs) {}
			ListConstReverseIterator(const ListIterator< _T >& rhs) : _ptr(rhs.getPtr()) {}
			ListConstReverseIterator(const ListConstIterator< _T >& rhs) : _ptr(rhs.getPtr()) {}
			ListConstReverseIterator(const ListReverseIterator< _T >& rhs) : _ptr(rhs.getPtr()) {}
			ListConstReverseIterator(const ListConstReverseIterator& rhs) : _ptr(rhs._ptr) {}
			virtual ~ListConstReverseIterator() {}

			node_pointer	getPtr(void) const
			{
				return (this->_ptr);
			}

			void	setPtr(node_pointer ptr)
			{
				this->_ptr = ptr;
			}

			ListConstReverseIterator&	operator= (const ListConstReverseIterator& rhs)
			{
				this->_ptr = rhs._ptr;

				return (*this);
			}

			bool	operator== (const ListConstReverseIterator&	rhs)
			{
				return (*this->_ptr == rhs._ptr);
			}

			bool	operator!= (const ListConstReverseIterator& rhs)
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

			ListConstReverseIterator&	operator++ ()
			{
				this->_ptr = this->_ptr->getNext();
				return (*this);
			}

			ListConstReverseIterator	operator++ (int)
			{
				ListConstReverseIterator	temp(*this);

				operator++();
				return (temp);
			}

			ListConstReverseIterator&	operator-- ()
			{
				this->_ptr = this->_ptr->getPrev();
				return (*this);
			}

			ListConstReverseIterator	operator-- (int)
			{
				ListConstReverseIterator	temp(*this);

				operator--();
				return (temp);
			}

	};
}

#endif