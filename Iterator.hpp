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

	template <class _Iterator>
	class reverse_iterator {
		public:
			typedef _Iterator	iterator_type;
			typedef typename iterator_traits < _Iterator >::iterator_category	iterator_category;
			typedef typename iterator_traits < _Iterator >::value_type	value_type;
			typedef typename iterator_traits < _Iterator >::difference_type	difference_type;
			typedef typename iterator_traits < _Iterator >::pointer	pointer;
			typedef typename iterator_traits < _Iterator >::reference	reference;

		private:
			_Iterator	_baseIterator;
		
		public:
			reverse_iterator() {};
			explicit reverse_iterator(iterator_type it) : _baseIterator(it) {};

			template < typename _Iter >
			reverse_iterator(const reverse_iterator< _Iter >& rev_it) : _baseIterator(rev_it.getBaseIterator()) {};

			iterator_type	getBaseIterator(void) const
			{
				return (this->_baseIterator);
			}

			iterator_type	base() const
			{
				return (this->_baseIterator);
			}

			reference	operator* () const
			{
				iterator_type	temp = this->_baseIterator;

				return (*(--temp));
			}

			reverse_iterator	operator+ (difference_type n) const
			{
				iterator_type	temp = this->_baseIterator;

				temp = temp - n;
				return (reverse_iterator(temp));
			}

			reverse_iterator&	operator++ ()
			{	
				--this->_baseIterator;

				return (*this);
			}

			reverse_iterator	operator++ (int)
			{
				reverse_iterator	temp = *this;

				--this->_baseIterator;
				return (temp);
			}

			reverse_iterator&	operator+= (difference_type n)
			{
				this->_baseIterator -= n;

				return (*this);
			}

			reverse_iterator	operator- (difference_type n) const
			{
				iterator_type	temp = this->_baseIterator;

				temp = temp + n;
				return (reverse_iterator(temp));
			}

			reverse_iterator&	operator-- ()
			{	
				++this->_baseIterator;

				return (*this);
			}

			reverse_iterator	operator-- (int)
			{
				reverse_iterator	temp = *this;

				++this->_baseIterator;
				return (temp);
			}

			reverse_iterator&	operator-= (difference_type n)
			{
				this->_baseIterator += n;

				return (*this);
			}

			pointer	operator-> () const
			{
				return (&(operator*()));
			}

			reference	operator[] (difference_type n) const
			{
				reverse_iterator	temp = *this;

				temp -= n;
				return (*temp);
			}

			template < typename _Iter1, typename _Iter2  >
			friend bool operator== (const reverse_iterator< _Iter1 >& lhs, const reverse_iterator< _Iter2 >& rhs)
			{
				return (lhs._baseIterator == rhs._baseIterator);
			}

			template < typename _Iter1, typename _Iter2 >
			friend bool operator!= (const reverse_iterator< _Iter1 >& lhs, const reverse_iterator< _Iter2 >& rhs)
			{
				return (lhs._baseIterator != rhs._baseIterator);
			}

			template < typename _Iter1, typename _Iter2 >
			friend bool operator<  (const reverse_iterator< _Iter1 >& lhs, const reverse_iterator< _Iter2 >& rhs)
			{
				return (lhs._baseIterator > rhs._baseIterator);
			}

			template < typename _Iter1, typename _Iter2 >
			friend bool operator<= (const reverse_iterator< _Iter1 >& lhs, const reverse_iterator< _Iter2 >& rhs)
			{
				return (lhs._baseIterator >= rhs._baseIterator);
			}

			template < typename _Iter1, typename _Iter2 >
			friend bool operator>  (const reverse_iterator< _Iter1 >& lhs, const reverse_iterator< _Iter2 >& rhs)
			{
				return (lhs._baseIterator < rhs._baseIterator);
			}

			template < typename _Iter1, typename _Iter2 >
			friend bool operator>= (const reverse_iterator< _Iter1 >& lhs, const reverse_iterator< _Iter2 >& rhs)
			{
				return (lhs._baseIterator <= rhs._baseIterator);
			}

			template < typename _Iter1, typename _Iter2 >
			friend typename reverse_iterator< _Iter1 >::difference_type	operator- (const reverse_iterator< _Iter1 >& lhs, const reverse_iterator< _Iter2 >& rhs)
			{
				return (rhs._baseIterator - lhs._baseIterator);
			}

			template < typename _Iter >
			friend reverse_iterator< _Iter > operator+ (typename reverse_iterator< _Iter >::difference_type n, const reverse_iterator< _Iter >& rev_it)
			{
				reverse_iterator< _Iter >	temp = rev_it;

				temp += n;
				return (temp);
			}
	};
}

#endif