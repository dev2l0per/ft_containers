#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <iostream>

namespace ft {
	class input_iterator_tag {};
	class output_iterator_tag {};
	class forward_iterator_tag : public input_iterator_tag {};
	class bidrectional_iterator_tag : public forward_iterator_tag {};
	class random_access_iterator_tag : public bidrectional_iterator_tag {};

	template < typename _Iterator >
	class iterator_traits {
		private:
		public:
			typedef typename _Iterator::difference_type	difference_type;
			typedef typename _Iterator::value_type	value_type;
			typedef typename _Iterator::pointer	pointer;
			typedef typename _Iterator::reference	reference;
			typedef typename _Iterator::iterator_category	iterator_category;
	};

	template < typename _T >
	class iterator_traits< _T* > {
		private:
		public:
			typedef std::ptrdiff_t	difference_type;
			typedef _T	value_type;
			typedef _T*	pointer;
			typedef _T&	reference;
			typedef random_access_iterator_tag iterator_category;
	};

	template < typename _T >
	class iterator_traits< const _T* > {
		typedef std::ptrdiff_t	difference_type;
		typedef _T	value_type;
		typedef const _T*	pointer;
		typedef const _T&	reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template < typename _T >
	class BaseIterator {
		public:
			typedef _T	value_type;
			typedef std::ptrdiff_t	difference_type;
			typedef _T*	pointer;
			typedef _T&	reference;
			typedef typename ft::iterator_traits< value_type >::iterator_category	iterator_category;
	};

	template < typename _T >
	class Iterator {
		public:
			typedef typename BaseIterator<_T>::value_type	value_type;
			typedef typename BaseIterator<_T>::difference_type	difference_type;
			typedef typename BaseIterator<_T>::pointer	pointer;
			typedef	typename BaseIterator<_T>::reference	reference;
			typedef typename BaseIterator<_T>::iterator_category	iterator_category;
		
		protected:
			pointer _ptr;
		
		public:
			Iterator() : _ptr(0) {}
			Iterator(pointer ptr) : _ptr(ptr) {}
			Iterator(const Iterator &src) : _ptr(src._ptr) {}
			virtual ~Iterator() {}

			Iterator&	operator= (const Iterator& rhs)
			{
				this->_ptr = rhs._ptr;
				return (*this);
			}

			Iterator&	operator++ ()
			{
				++this->_ptr;
				return (*this);
			}

			Iterator	operator++ (int)
			{
				Iterator	temp(*this);

				operator++();
				return (temp);
			}

			Iterator&	operator-- ()
			{
				--this->_ptr;
				return (*this);
			}

			Iterator	operator-- (int)
			{
				Iterator	temp(*this);

				operator--();
				return (temp);
			}

			bool	operator== (const Iterator&	rhs) const
			{
				return (this->_ptr == rhs._ptr);
			}

			bool	operator!= (const Iterator& rhs) const
			{
				return (this->_ptr != rhs._ptr);
			}

			reference	operator* ()
			{
				return (*this->_ptr);
			}
	};
}

#endif