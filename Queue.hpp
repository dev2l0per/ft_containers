#ifndef QUEUE_HPP
# define QUEUE_HPP

# include "list.hpp"

namespace ft {
	template < typename _T, typename _Container = ft::list< _T > >
	class queue {
		public:
			typedef _T	value_type;
			typedef _Container	container_type;
			typedef std::size_t	size_type;
		
		private:
			container_type	_container;
		
		private:
			template < typename _Type, typename _ContainerType>
			friend bool	operator== (const queue< _Type, _ContainerType >& lhs, const queue< _Type, _ContainerType >& rhs);
			template < typename _Type, typename _ContainerType>
			friend bool	operator!= (const queue< _Type, _ContainerType >& lhs, const queue< _Type, _ContainerType >& rhs);
			template < typename _Type, typename _ContainerType>
			friend bool	operator< (const queue< _Type, _ContainerType >& lhs, const queue< _Type, _ContainerType >& rhs);
			template < typename _Type, typename _ContainerType>
			friend bool	operator<= (const queue< _Type, _ContainerType >& lhs, const queue< _Type, _ContainerType >& rhs);
			template < typename _Type, typename _ContainerType>
			friend bool	operator> (const queue< _Type, _ContainerType >& lhs, const queue< _Type, _ContainerType >& rhs);
			template < typename _Type, typename _ContainerType>
			friend bool	operator>= (const queue< _Type, _ContainerType >& lhs, const queue< _Type, _ContainerType >& rhs);

		public:
			explicit queue(const container_type& cntr = container_type()) : _container(cntr) {}
			queue(const queue& x) : _container(x._container) {}
			virtual ~queue() {}
		
		public:
			queue&	operator= (const queue& x)
			{
				if (this == &x)
					return (*this);
				this->_container = x._container;
				return (*this);
			}

			bool	empty(void) const
			{
				return (this->_container.empty());
			}

			size_type	size(void) const
			{
				return (this->_container.size());
			}

			value_type&	front(void)
			{
				return (this->_container.front());
			}

			const value_type&	front(void) const
			{
				return (this->_container.front());
			}

			value_type&	back(void)
			{
				return (this->_container.back());
			}

			const value_type&	back(void) const
			{
				return (this->_container.back());
			}

			void	push(const value_type& val)
			{
				this->_container.push_back(val);
			}

			void	pop(void)
			{
				this->_container.pop_front();
			}
	};

	template < typename _Type, typename _ContainerType >
	bool	operator== (const queue< _Type, _ContainerType >& lhs, const queue< _Type, _ContainerType >& rhs)
	{
		return (lhs._container == rhs._container);
	}

	template < typename _Type, typename _ContainerType >
	bool	operator!= (const queue< _Type, _ContainerType >& lhs, const queue< _Type, _ContainerType >& rhs)
	{
		return (lhs._container != rhs._container);
	}

	template < typename _Type, typename _ContainerType >
	bool	operator< (const queue< _Type, _ContainerType >& lhs, const queue< _Type, _ContainerType >& rhs)
	{
		return (lhs._container < rhs._container);
	}

	template < typename _Type, typename _ContainerType >
	bool	operator<= (const queue< _Type, _ContainerType >& lhs, const queue< _Type, _ContainerType >& rhs)
	{
		return (lhs._container <= rhs._container);
	}

	template < typename _Type, typename _ContainerType >
	bool	operator> (const queue< _Type, _ContainerType >& lhs, const queue< _Type, _ContainerType >& rhs)
	{
		return (lhs._container > rhs._container);
	}

	template < typename _Type, typename _ContainerType >
	bool	operator>= (const queue< _Type, _ContainerType >& lhs, const queue< _Type, _ContainerType >& rhs)
	{
		return (lhs._container >= rhs._container);
	}
}

#endif