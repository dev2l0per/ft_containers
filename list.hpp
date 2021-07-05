#ifndef LIST_HPP
# define LIST_HPP

# include <iostream>
# include "Iterator.hpp"
# include "ListNode.hpp"
# include "ListIterator.hpp"
# include "utils.hpp"

namespace ft {
	template < typename _T, typename _Alloc = std::allocator< _T > >
	class list {
		public:
			typedef _T	value_type;
			typedef _Alloc	allocator_type;
			typedef typename allocator_type::reference	reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer	pointer;
			typedef typename allocator_type::const_pointer	const_pointer;
			typedef ListIterator< value_type, false >	iterator;
			typedef ListIterator< value_type, true > const_iterator;
			typedef ft::reverse_iterator< iterator > reverse_iterator;
			typedef ft::reverse_iterator< const_iterator > const_reverse_iterator;
			typedef typename ft::iterator_traits< iterator >::difference_type	difference_type;
			typedef	std::size_t	size_type;

			typedef ListNode< value_type >	node_type;
			typedef ListNode< value_type >*	node_pointer;
			typedef ListNode< value_type >&	node_reference;

			typedef typename allocator_type::template rebind< node_type >::other node_alloc;

		protected:
			node_pointer	_head;
			size_type	_size;
			node_alloc	_alloc;

		private:
			node_pointer	_createNode(node_pointer prev, node_pointer next, value_type value)
			{
				node_pointer	newNode = this->_alloc.allocate(1);
				this->_alloc.construct(newNode, node_type(prev, next, value));
				return (newNode);
			}

			void	_deleteNode(node_pointer node)
			{
				this->_alloc.destroy(node);
				this->_alloc.deallocate(node, 1);
			}

			void	_swapNextNode(node_pointer node)
			{
				node_pointer	prevNode = node->getPrev();
				node_pointer	nextNode = node->getNext();
				node_pointer	nextTwiceNode = nextNode->getNext();

				prevNode->setNext(nextNode);
				nextTwiceNode->setPrev(node);
				node->setPrev(nextNode);
				node->setNext(nextTwiceNode);
				nextNode->setPrev(prevNode);
				nextNode->setNext(node);
			}
		
		public:
			explicit list (const allocator_type& alloc = allocator_type()) : _head(0), _size(0), _alloc(alloc)
			{
				this->_head = this->_createNode(this->_head, this->_head, value_type());
				this->_head->setNext(this->_head);
				this->_head->setPrev(this->_head);
			}

			explicit list (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _size(0), _alloc(alloc)
			{
				this->_head = this->_createNode(this->_head, this->_head, value_type());
				this->_head->setNext(this->_head);
				this->_head->setPrev(this->_head);
				for (size_type i = 0; i < n; i++)
					this->push_back(val);
			}

			template <typename InputIterator>
			list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if < !ft::is_integral < InputIterator >::value, InputIterator >::type* = NULL) : _size(0), _alloc(alloc)
			{
				this->_head = this->_createNode(this->_head, this->_head, value_type());
				this->_head->setNext(this->_head);
				this->_head->setPrev(this->_head);
				for (InputIterator iter = first; iter != last; ++iter)
					this->push_back(*iter);
			}

			list (const list& x) : _size(0), _alloc(x._alloc)
			{
				this->_head = this->_createNode(this->_head, this->_head, value_type());
				this->_head->setNext(this->_head);
				this->_head->setPrev(this->_head);
				*this = x;
			}

			virtual ~list()
			{
				this->clear();

				this->_alloc.destroy(this->_head);
				this->_alloc.deallocate(this->_head, 1);
			}
		
		public:
			list&	operator= (const list& x)
			{
				if (this != &x)
					this->assign(x.begin(), x.end());
				return (*this);
			}

			iterator	begin(void)
			{
				return (iterator(this->_head->getNext()));
			}

			const_iterator	begin(void) const
			{
				return (const_iterator(this->_head->getNext()));
			}

			iterator	end(void)
			{
				return (iterator(this->_head));
			}

			const_iterator	end(void) const
			{
				return (const_iterator(this->_head));
			}

			reverse_iterator rbegin(void)
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

			bool	empty(void) const
			{
				return (this->_size == 0);
			}

			size_type	size(void) const
			{
				return (this->_size);
			}

			size_type	max_size(void) const
			{
				return (this->_alloc.max_size());
			}

			reference	front(void)
			{
				return (this->_head->getNext()->getData());
			}

			const_reference	front(void) const
			{
				return (this->_head->getNext()->getData());
			}

			reference	back(void)
			{
				return (this->_head->getPrev()->getData());
			}

			const_reference	back(void) const
			{
				return (this->_head->getPrev()->getData());
			}

			template <class _InputIterator>
			void	assign(_InputIterator first, _InputIterator last, typename ft::enable_if< !ft::is_integral< _InputIterator >::value, _InputIterator >::type* = NULL )
			{
				this->clear();
				for (_InputIterator iter = first; iter != last; ++iter)
					this->push_back(*iter);
			}

			void	assign(size_type n, const value_type& val)
			{
				this->clear();
				for (size_type i = 0; i < n; ++i)
					this->push_back(val);
			}

			void	push_front(const value_type& val)
			{
				node_pointer	newNode = this->_createNode(this->_head, this->_head->getNext(), val);

				this->_head->getNext()->setPrev(newNode);
				this->_head->setNext(newNode);
				++this->_size;
			}

			void	pop_front(void)
			{
				node_pointer	node = this->_head->getNext()->getNext();

				this->_deleteNode(this->_head->getNext());
				this->_head->setNext(node);
				node->setPrev(this->_head);
				--this->_size;
			}

			void	push_back(const value_type& val)
			{
				node_pointer	newNode = this->_createNode(this->_head->getPrev(), this->_head, val);

				this->_head->getPrev()->setNext(newNode);
				this->_head->setPrev(newNode);
				++this->_size;
			}

			void	pop_back(void)
			{
				node_pointer	node = this->_head->getPrev()->getPrev();

				this->_deleteNode(this->_head->getPrev());
				this->_head->setPrev(node);
				node->setNext(this->_head);
				--this->_size;
			}

			iterator	insert(iterator position, const value_type&	val)
			{
				if (position == this->begin())
				{
					this->push_front(val);
					return (this->begin());
				} else if (position == this->end())
				{
					this->push_back(val);
					return (--this->end());
				}
				node_pointer	prevNode = position.getPtr()->getPrev();
				node_pointer	newNode = this->_createNode(position.getPtr()->getPrev(), position.getPtr(), val);

				position.getPtr()->setPrev(newNode);
				prevNode->setNext(newNode);
				++this->_size;
				return (--position);
			}

			void	insert(iterator position, size_type n, const value_type& val)
			{
				for (size_type i = 0; i < n; ++i)
					this->insert(position, val);
			}

			template <class _InputIterator>
			void	insert(iterator position, _InputIterator first, _InputIterator last, typename ft::enable_if < !ft::is_integral < _InputIterator >::value, _InputIterator >::type* = NULL )
			{
				for (_InputIterator iter = first; iter != last; iter++)
				{
					this->insert(position, *iter);
				}
			}

			iterator	erase(iterator position)
			{
				iterator	curIter = position++;

				curIter.getPtr()->getPrev()->setNext(position.getPtr());
				position.getPtr()->setPrev(curIter.getPtr()->getPrev());
				this->_deleteNode(curIter.getPtr());
				--this->_size;
				return (position);
			}

			iterator	erase(iterator first, iterator last)
			{
				for (iterator iter = first; iter != last; iter++)
					this->erase(iter);
				return (last);
			}

			void	swap(list& x)
			{
				char buf[sizeof(list)];
				memcpy(reinterpret_cast<void *>(buf), reinterpret_cast<void *>(this), sizeof(list));
				memcpy(reinterpret_cast<void *>(this), reinterpret_cast<void *>(&x), sizeof(list));
				memcpy(reinterpret_cast<void *>(&x), reinterpret_cast<void *>(buf), sizeof(list));
			}

			void	resize(size_type n, value_type val = value_type())
			{
				if (n < this->_size)
				{
					for (; this->_size != n; )
						this->pop_back();
				}
				else if (n > this->_size) {
					for (; this->_size != n; )
						this->push_back(val);
				}
				else 
					return ;
			}

			void	clear(void)
			{
				for (; this->_size != 0; )
					this->pop_back();
			}

			void	splice(iterator position, list& x)
			{
				this->splice(position, x, x.begin(), x.end());
			}

			void	splice(iterator position, list& x, iterator i)
			{
				i.getPtr()->getPrev()->setNext(i.getPtr()->getNext());
				i.getPtr()->getNext()->setPrev(i.getPtr()->getPrev());
				i.getPtr()->setPrev(position.getPtr()->getPrev());
				i.getPtr()->setNext(position.getPtr());
				position.getPtr()->getPrev()->setNext(i.getPtr());
				position.getPtr()->setPrev(i.getPtr());
				++this->_size;
				--x._size;
			}

			void	splice(iterator position, list& x, iterator first, iterator last)
			{
				iterator temp;
				for (iterator iter = first; iter != last; )
				{
					temp = iter;
					++iter;
					this->splice(position, x, temp);
				}
			}

			void	remove(const value_type& val)
			{
				iterator	tempIter;

				for (iterator iter = this->begin(); iter != this->end();)
				{
					tempIter = iter++;
					if (*tempIter == val)
						this->erase(tempIter);
				}
			}

			template <typename Predicate>
			void	remove_if(Predicate pred)
			{
				iterator	tempIter;

				for (iterator iter = this->begin(); iter != this->end();)
				{
					tempIter = iter++;
					if (pred(*tempIter))
						this->erase(tempIter);
				}
			}

			void	unique(void)
			{
				for (iterator iter = this->begin(); iter.getPtr() != this->end().getPtr(); ++iter)
				{
					while (1)
					{
						if (iter.getPtr()->getNext() != this->end().getPtr() && *iter == iter.getPtr()->getNext()->getData())
						{
							node_pointer	deleteNode = iter.getPtr()->getNext();

							iter.getPtr()->setNext(deleteNode->getNext());
							iter.getPtr()->getNext()->setPrev(iter.getPtr());
							this->_deleteNode(deleteNode);
							--this->_size;
						}
						else {
							break ;
						}
					}
				}
			}

			template <typename _BinaryPredicate>
			void	unique(_BinaryPredicate comp)
			{
				for (iterator iter = this->begin(); iter.getPtr() != this->end().getPtr(); ++iter)
				{
					while (1)
					{
						if (iter.getPtr()->getNext() != this->end().getPtr() && comp(*iter, iter.getPtr()->getNext()->getData()))
						{
							node_pointer	deleteNode = iter.getPtr()->getNext();

							iter.getPtr()->setNext(deleteNode->getNext());
							iter.getPtr()->getNext()->setPrev(iter.getPtr());
							this->_deleteNode(deleteNode);
							--this->_size;
						}
						else {
							break ;
						}
					}
				}
			}

			void	merge(list& x)
			{
				if (&x == this)
					return ;
				for (iterator thisIter = this->begin(), xIter = x.begin(); thisIter != this->end() && xIter != x.end();)
				{
					if (*xIter < *thisIter)
						this->splice(thisIter, x, xIter++);
					else
						thisIter++;
				}
				this->splice(this->end(), x);
			}

			template < typename _Compare >
			void merge(list& x, _Compare comp)
			{
				for (iterator thisIter = this->begin(), xIter = x.begin(); thisIter != this->end() && xIter != x.end();)
				{
					if (comp(*xIter, *thisIter))
						this->splice(thisIter, x, xIter++);
					else
						thisIter++;
				}
				this->splice(this->end(), x);
			}

			void	sort(void)
			{
				for (iterator iter = this->begin(); iter != --this->end();)
				{
					if (*iter > iter.getPtr()->getNext()->getData())
					{
						this->_swapNextNode(iter.getPtr());
						iter = this->begin();
					}
					else
						iter++;
				}
			}

			template < typename _Compare >
			void	sort(_Compare comp)
			{
				for (iterator iter = this->begin(); iter != --this->end();)
				{
					if (comp(iter.getPtr()->getNext()->getData(), *iter))
					{
						this->_swapNextNode(iter.getPtr());
						iter = this->begin();
					}
					else
						iter++;
				}
			}

			void	reverse(void)
			{
				list< value_type >	temp;
				for (iterator iter = this->begin(); iter != this->end(); ++iter)
					temp.push_front(*iter);
				*this = temp;
			}

			allocator_type	get_allocator() const
			{
				return (this->_alloc);
			}
	};

	template < typename _T, typename _Alloc >
	bool	operator== (const list< _T, _Alloc >& lhs, const list< _T, _Alloc >& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		// for (typename list< _T >::const_iterator lIter = lhs.begin(), rIter = rhs.begin(); lIter != lhs.end();)
		// {
		// 	if (*(lIter++) != *(rIter++))
		// 		return (false);
		// }
		// return (true);
	}

	template < typename _T >
	bool	operator!= (const list< _T >& lhs, const list< _T >& rhs)
	{
		return (!(lhs == rhs));
	}

	template < typename _T >
	bool	operator< (const list< _T >& lhs, const list< _T >& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		// for (typename list< _T >::const_iterator lIter = lhs.begin(), rIter = rhs.begin(); lIter != lhs.end(); ++lIter, ++rIter)
		// {
		// 	if (*lIter != *rIter)
		// 		return (*lIter < *rIter);
		// }
		// if (lhs.size() < rhs.size())
		// 	return (true);
		// if (lhs.size() > rhs.size())
		// 	return (false);
		// return (false);
	}

	template < typename _T >
	bool	operator<= (const list< _T >& lhs, const list< _T >& rhs)
	{
		return (!(rhs < lhs));
	}

	template < typename _T >
	bool	operator> (const list< _T >& lhs, const list< _T >& rhs)
	{
		return (rhs < lhs);
	}

	template < typename _T >
	bool	operator>= (const list< _T >& lhs, const list< _T >& rhs)
	{
		return (!(lhs < rhs));
	}

	template < typename _T, typename _Alloc >
	void	swap(list< _T, _Alloc >& x, list< _T, _Alloc >& y)
	{
		x.swap(y);
	}
}

#endif