#ifndef LISTNODE_HPP
# define LISTNODE_HPP

namespace ft {
	template < typename _T >
	class ListNode {
		private:
			ListNode *_prev;
			ListNode *_next;
			_T	_data;
		
		public:
			ListNode() : _prev(0), _next(0), _data(0) {}
			
			ListNode(const _T &data) : _prev(0), _next(0), _data(data) {}
			
			ListNode(ListNode *prev, ListNode *next, const _T &data) : _prev(prev), _next(next), _data(data)	{}

			ListNode(const ListNode &src) : _prev(src._prev), _next(src._next), _data(src._data) {}

			virtual ~ListNode(void) {}

			ListNode&	operator= (const ListNode &src)
			{
				this->_next = src._next;
				this->_prev = src._prev;
				this->_data = src._data;

				return (*this);
			}

			ListNode*	getPrev(void)
			{
				return (this->_prev);
			}

			const ListNode*	getPrev(void) const
			{
				return (this->_prev);
			}

			ListNode*	getNext(void)
			{
				return (this->_next);
			}

			const ListNode*	getNext(void) const
			{
				return (this->_next);
			}
			
			_T&	getData(void)
			{
				return (this->_data);
			}

			const _T&	getData(void) const
			{
				return (this->_data);
			}

			void	setData(const _T &data)
			{
				this->_data = data;
			}
			
			void	setPrev(ListNode *prev)
			{
				this->_prev = prev;
			}

			void	setNext(ListNode *next)
			{
				this->_next = next;
			}
	};
}

#endif