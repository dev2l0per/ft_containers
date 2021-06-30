#ifndef VECTORITERATOR_HPP
# define VECTORITERATOR_HPP

# include "Iterator.hpp"
# include "utils.hpp"

namespace ft {
	template < typename _T, bool _isConst >
	class VectorIterator {
		public:
			typedef _T  value_type;
			typedef std::ptrdiff_t  difference_type;
			typedef std::size_t size_type;
			typedef typename ft::typeSelector< value_type*, const value_type*, _isConst >::type pointer;
			typedef typename ft::typeSelector< value_type&, const value_type&, _isConst >::type reference;
			typedef typename ft::random_access_iterator_tag iterator_category;

		private:
			pointer _ptr;
		
		public:
			VectorIterator() : _ptr(0) {}
			VectorIterator(pointer rhs) : _ptr(rhs) {}
			VectorIterator(const VectorIterator< value_type, false >& rhs) : _ptr(rhs.getPtr()) {}
			virtual ~VectorIterator() {}

			pointer getPtr(void) const
			{
				return (this->_ptr);
			}

			void    setPtr(pointer ptr)
			{
				this->_ptr = ptr;
			}

			VectorIterator& operator= (const VectorIterator& rhs)
			{
				this->_ptr = rhs._ptr;
				return (*this);
			}

			bool    operator== (const VectorIterator< value_type, false >& rhs) const
			{
				return (this->_ptr == rhs.getPtr());
			}

			bool    operator== (const VectorIterator< value_type, true >& rhs) const
			{
				return (this->_ptr == rhs.getPtr());
			}

			bool    operator!= (const VectorIterator< value_type, false >& rhs) const
			{
				return (this->_ptr != rhs.getPtr());
			}

			bool    operator!= (const VectorIterator< value_type, true >& rhs) const
			{
				return (this->_ptr != rhs.getPtr());
			}

			reference   operator* () const
			{
				return (*(this->_ptr));
			}

			pointer operator-> () const
			{
				return (this->_ptr);
			}

			VectorIterator& operator++ ()
			{
				++this->_ptr;
				return (*this);
			}

			VectorIterator  operator++ (int)
			{
				VectorIterator  temp(*this);

				operator++();
				return (temp);
			}

			VectorIterator& operator-- ()
			{
				--this->_ptr;
				return (*this);
			}

			VectorIterator  operator-- (int)
			{
				VectorIterator  temp(*this);

				operator--();
				return (temp);
			}

			VectorIterator  operator+ (const int& n) const
			{
				return (VectorIterator(this->_ptr + n));
			}
			
			VectorIterator  operator- (const int& n) const
			{
				return (VectorIterator(this->_ptr - n));
			}

			difference_type  operator- (const VectorIterator< value_type, false >& rhs) const
			{
				return (this->_ptr - rhs.getPtr());
			}

			difference_type  operator- (const VectorIterator< value_type, true >& rhs) const
			{
				return (this->_ptr - rhs.getPtr());
			}

			VectorIterator& operator+= (const difference_type n)
			{
				this->_ptr += n;

				return (*this);
			}

			VectorIterator& operator-= (const difference_type n)
			{
				this->_ptr -= n;

				return (*this);
			}

			bool	operator< (const VectorIterator< value_type, false >& rhs) const
			{
				return (this->_ptr < rhs.getPtr());
			}

			bool	operator< (const VectorIterator< value_type, true >& rhs) const
			{
				return (this->_ptr < rhs.getPtr());
			}

			bool	operator<= (const VectorIterator< value_type, false >& rhs) const
			{
				return (this->_ptr <= rhs.getPtr());
			}

			bool	operator<= (const VectorIterator< value_type, true >& rhs) const
			{
				return (this->_ptr <= rhs.getPtr());
			}

			bool	operator> (const VectorIterator< value_type, false >& rhs) const
			{
				return (this->_ptr > rhs.getPtr());
			}

			bool	operator> (const VectorIterator< value_type, true >& rhs) const
			{
				return (this->_ptr > rhs.getPtr());
			}

			bool	operator>= (const VectorIterator< value_type, false >& rhs) const
			{
				return (this->_ptr >= rhs.getPtr());
			}

			bool	operator>= (const VectorIterator< value_type, true >& rhs) const
			{
				return (this->_ptr >= rhs.getPtr());
			}

			reference	operator[] (difference_type n) const
			{
				return (*(this->_ptr + n));
			}
	};

	template < typename _T, bool _isConst >
	VectorIterator< _T, _isConst >	operator+ (const typename VectorIterator< _T, _isConst>::difference_type n, const VectorIterator< _T, _isConst >& iter)
	{
		return (VectorIterator< _T, _isConst >(iter.getPtr() + n));
	}
}

#endif