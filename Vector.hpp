#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include "utils.hpp"
# include "VectorIterator.hpp"
# include <unistd.h>

namespace ft {
    template < typename _T, typename _Alloc = std::allocator< _T > >
    class vector {
        public:
            typedef _T	value_type;
			typedef _Alloc	allocator_type;
			typedef value_type&	reference;
			typedef const value_type&	const_reference;
			typedef value_type*	pointer;
			typedef const value_type*	const_pointer;
			typedef VectorIterator< value_type, false >	iterator;
			typedef VectorIterator< value_type, true > const_iterator;
			typedef ft::reverse_iterator< iterator > reverse_iterator;
			typedef ft::reverse_iterator< const_iterator > const_reverse_iterator;
			typedef typename ft::iterator_traits< iterator >::difference_type	difference_type;
			typedef	std::size_t	size_type;
		
		protected:
			value_type	*_arr;
			size_type	_size;
			size_type	_capacity;
			allocator_type	_alloc;
		
		private:
			void	_expandCapacity()
			{
				if (this->_capacity == 0) {
					this->_arr = this->_alloc.allocate(1);
					++this->_capacity;
				} else {
					this->_capacity *= 2;
					pointer	tempArr = this->_alloc.allocate(this->_capacity);
					memcpy(tempArr, (void *)this->_arr, sizeof(value_type) * this->_size);
					for (size_type i = 0; i < this->_size; ++i)
						this->_alloc.destroy(this->_arr + i);
					this->_alloc.deallocate(this->_arr, this->_size);
					this->_arr = tempArr;
				}
			}

			void	_expandCapacity(size_type capacity)
			{
				if (this->_capacity == 0) {
					this->_arr = this->_alloc.allocate(capacity);
					this->_capacity = capacity;
				} else {
					pointer	tempArr = this->_alloc.allocate(capacity);
					memmove(tempArr, reinterpret_cast<void *>(this->_arr), sizeof(value_type) * this->_size);
					for (size_type i = 0; i < this->_size; ++i)
						this->_alloc.destroy(this->_arr + i);
					this->_alloc.deallocate(this->_arr, this->_capacity);
					this->_capacity = capacity;
					this->_arr = tempArr;
				}
			}

		public:
			explicit vector (const allocator_type& alloc = allocator_type()) : _arr(NULL), _size(0), _capacity(0), _alloc(alloc) {}
			
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _arr(NULL), _size(0), _capacity(0), _alloc(alloc)
			{
				this->assign(n, val);
			}

			template <class _InputIterator>
        	vector (_InputIterator first, _InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if< !ft::is_integral< _InputIterator >::value, _InputIterator >::type* = NULL) : _arr(NULL), _size(0), _capacity(0), _alloc(alloc)
			{
				this->assign(first, last);
			}

			vector (const vector& x) : _arr(NULL), _size(0), _capacity(0), _alloc(x._alloc)
			{
				this->reserve(x._size);
				for (const_iterator iter = x.begin(); iter != x.end(); ++iter)
					this->push_back(*iter);
			}

			virtual ~vector()
			{
				if (this->_capacity > 0)
				{
					this->clear();
					this->_alloc.deallocate(this->_arr, this->_capacity);
				}
			}
		
		public:
			vector&	operator= (const vector& x)
			{
				if (this == &x)
					return (*this);
				this->reserve(x._size);
				this->assign(x.begin(), x.end());
				return (*this);
			}

			iterator	begin(void)
			{
				return (iterator(this->_arr));
			}

			const_iterator	begin(void) const
			{
				return (const_iterator(this->_arr));
			}

			iterator	end(void)
			{
				return (iterator(this->_arr + this->_size));
			}

			const_iterator	end(void) const
			{
				return (const_iterator(this->_arr + this->_size));
			}

			reverse_iterator	rbegin(void)
			{
				return (reverse_iterator(this->end()));
			}

			const_reverse_iterator	rbegin(void) const
			{
				return (const_reverse_iterator(this->end()));
			}

			reverse_iterator	rend(void)
			{
				return (reverse_iterator(this->begin()));
			}

			const_reverse_iterator	rend(void) const
			{
				return (const_reverse_iterator(this->begin()));
			}

			size_type	size(void) const
			{
				return (this->_size);
			}

			size_type	max_size(void) const
			{
				return (this->_alloc.max_size());
			}

			void	resize(size_type n, value_type val = value_type())
			{
				if (this->_size >= n) {
					for (size_type size = this->_size - n; size > 0; --size)
						this->pop_back();
				} else {
					if (this->_capacity < n && this->_capacity * 2 >= n)
						this->_expandCapacity();
					else
						this->reserve(n);
					for (size_type i = this->_size; i < n; ++i)
						this->_arr[i] = val;
					this->_size = n;
				}
			}

			size_type	capacity(void)	const
			{
				return (this->_capacity);
			}

			bool	empty(void)	const
			{
				return	(this->_size == 0);
			}

			void	reserve(size_type n)
			{
				if (this->_capacity >= n)
					return ;
				if (this->max_size() < n)
					throw	std::length_error("Length Error");
				this->_expandCapacity(n);
			}

			reference	operator[] (size_type n)
			{
				return (*(this->_arr + n));
			}

			const_reference	operator[] (size_type n) const
			{
				return (*(this->_arr + n));
			}

			reference	at(size_type n)
			{
				if (this->_size <= n)
					throw	std::out_of_range("Out Of Range!");
				return (*(this->_arr + n));
			}

			const_reference	at(size_type n) const
			{
				if (this->_size <= n)
					throw	std::out_of_range("Out of Range!");
				return (*(this->_arr + n));
			}

			reference	front(void)
			{
				return (*(this->_arr));
			}

			const_reference	front(void) const
			{
				return (*(this->_arr));
			}

			reference	back(void)
			{
				return (*(this->_arr + this->_size - 1));
			}

			const_reference	back(void) const
			{
				return (*(this->_arr + this->_size - 1));
			}

			template < typename _InputIterator >
			void	assign(_InputIterator first, _InputIterator last, typename ft::enable_if< !ft::is_integral< _InputIterator>::value, _InputIterator>::type* = NULL)
			{
				size_type	range = 0;

				this->clear();
				for (_InputIterator iter = first; iter != last; ++iter)
					++range;
				this->reserve(range);
				for (_InputIterator iter = first; iter != last; ++iter)
					this->push_back(*iter);
			}

			void	assign(size_type n, const value_type& val)
			{
				this->clear();
				this->reserve(n);
				for (size_type i = 0; i < n; i++)
					this->push_back(val);
			}

			void	push_back(const value_type&	val)
			{
				if (this->_capacity <= this->_size) {
					this->_expandCapacity();
				}
				this->_alloc.construct(this->_arr + this->_size, val);
				++this->_size;
			}

			void	pop_back(void)
			{
				this->_alloc.destroy(this->_arr + (--this->_size));
			}

			iterator	insert(iterator position, const value_type&	val)
			{
				size_type pos = 0;
				for (const_iterator iter = this->begin(); iter != position; ++iter)
					pos++;
				this->insert(position, 1, val);

				return (iterator(this->_arr + pos));
			}

			void	insert(iterator position, size_type n, const value_type& val)
			{
				size_type pos = 0;
				for (const_iterator iter = this->begin(); iter != position; ++iter)
					pos++;
				if (this->_capacity < this->_size + n && this->_capacity * 2 < this->_size + n)
					this->_expandCapacity(this->_size + n);
				else if (this->_capacity < this->_size + n)
					this->_expandCapacity();
				memmove(reinterpret_cast<void *>(&this->_arr[pos + n]), reinterpret_cast<void *>(&this->_arr[pos]), sizeof(value_type) * (this->_size - pos + n));
				for (size_type i = 0; i < n; ++i)
					this->_arr[pos + i] = val;
				this->_size += n;
			}

			template < typename _InputIterator >
			void	insert(iterator position, _InputIterator first, _InputIterator last, typename ft::enable_if< !ft::is_integral< _InputIterator >::value, _InputIterator >::type* = NULL)
			{
				size_type pos = 0;
				size_type n = 0;
				for (const_iterator iter = this->begin(); iter != position; ++iter)
					++pos;
				for (_InputIterator iter = first; iter != last; ++iter)
					++n;
				if (this->_capacity < this->_size + n && this->_capacity * 2 < this->_size + n)
					this->_expandCapacity(this->_size + n);
				else if (this->_capacity < this->_size + n)
					this->_expandCapacity();
				memmove(&this->_arr[pos + n], &this->_arr[pos], sizeof(value_type) * (this->_size - pos + n));
				n = 0;
				for (_InputIterator iter = first; iter != last; iter++)
					this->_arr[pos + n++] = *iter;
				this->_size += n;
			}

			iterator	erase(iterator position)
			{
				size_type	pos = 0;
				for (const_iterator iter = this->begin(); iter != position; ++iter)
					pos++;
				this->_alloc.destroy(this->_arr + pos);
				for (size_type i = 0; i < this->_size - pos - 1; ++i)
					this->_arr[pos + i] = this->_arr[pos + i + 1];
				--this->_size;
				return (position);
			}

			iterator	erase(iterator first, iterator last)
			{
				size_type	pos = 0, n = 0;
				iterator	iter = this->begin();
				for (; iter != first; ++iter)
					pos++;
				for (; iter != last; ++iter)
					this->_alloc.destroy(this->_arr + pos + n++);
				for (size_type i = 0; i < this->_size - pos - n; ++i)
					this->_arr[pos + i] = this->_arr[pos + i + n];
				this->_size -= n;
				return (first);
			}

			void	swap(vector& x)
			{
				char buf[sizeof(vector)];
				memcpy(reinterpret_cast<void *>(buf), reinterpret_cast<void *>(this), sizeof(vector));
				memcpy(reinterpret_cast<void *>(this), reinterpret_cast<void *>(&x), sizeof(vector));
				memcpy(reinterpret_cast<void *>(&x), reinterpret_cast<void *>(buf), sizeof(vector));
			}

			void	clear(void)
			{
				for (size_type i = 0; i < this->_size; ++i)
					this->_alloc.destroy(this->_arr + i);
				this->_size = 0;
			}

			allocator_type	get_allocator(void) const
			{
				return (this->_alloc);
			}
    };

	template < typename _T, typename _Alloc >
	bool	operator== (const vector< _T, _Alloc >& lhs, const vector< _T, _Alloc >& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template < typename _T, typename _Alloc >
	bool	operator!= (const vector< _T, _Alloc >& lhs, const vector< _T, _Alloc >& rhs)
	{
		return (!(lhs == rhs));
	}

	template < typename _T, typename _Alloc >
	bool	operator< (const vector< _T, _Alloc >& lhs, const vector< _T, _Alloc >& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template < typename _T, typename _Alloc >
	bool	operator<= (const vector< _T, _Alloc >& lhs, const vector< _T, _Alloc >& rhs)
	{
		return (!(rhs < lhs));
	}

	template < typename _T, typename _Alloc >
	bool	operator> (const vector< _T, _Alloc >& lhs, const vector< _T, _Alloc >& rhs)
	{
		return (rhs < lhs);
	}

	template < typename _T, typename _Alloc >
	bool	operator>= (const vector< _T, _Alloc >& lhs, const vector< _T, _Alloc >& rhs)
	{
		return (!(lhs < rhs));
	}

	template < typename _T, typename _Alloc >
	void	swap(vector< _T, _Alloc >& x, vector< _T, _Alloc >& y)
	{
		x.swap(y);
	}
}

#endif