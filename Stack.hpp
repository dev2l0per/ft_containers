#ifndef STACK_HPP
# define STACK_HPP

# include "list.hpp"

namespace ft {
	template < typename _T, typename _Container = ft::list< _T > >
	class stack
	{
		public:
			typedef _T	value_type;
			typedef _Container	container_type;
			typedef std::size_t	size_type;
		
		private:
			container_type	_container;

		private:
			template < typename _Type, typename _ContainerType>
			friend bool	operator== (const stack< _Type, _ContainerType >& lhs, const stack< _Type, _ContainerType >& rhs);
			template < typename _Type, typename _ContainerType>
			friend bool	operator!= (const stack< _Type, _ContainerType >& lhs, const stack< _Type, _ContainerType >& rhs);
			template < typename _Type, typename _ContainerType>
			friend bool	operator< (const stack< _Type, _ContainerType >& lhs, const stack< _Type, _ContainerType >& rhs);
			template < typename _Type, typename _ContainerType>
			friend bool	operator<= (const stack< _Type, _ContainerType >& lhs, const stack< _Type, _ContainerType >& rhs);
			template < typename _Type, typename _ContainerType>
			friend bool	operator> (const stack< _Type, _ContainerType >& lhs, const stack< _Type, _ContainerType >& rhs);
			template < typename _Type, typename _ContainerType>
			friend bool	operator>= (const stack< _Type, _ContainerType >& lhs, const stack< _Type, _ContainerType >& rhs);

		public:
			explicit stack(const container_type& ctnr = container_type()) : _container(ctnr) {}
			stack(const stack& x) : _container(x.c) {}
			virtual ~stack() {}
		
		public:
			stack&	operator= (const stack& x)
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

			value_type&	top(void)
			{
				return (this->_container.back());
			}

			const value_type&	top(void) const
			{
				return (this->_container.back());
			}

			void	push(const value_type& val)
			{
				this->_container.push_back(val);
			}

			void	pop(void)
			{
				this->_container.pop_back();
			}
	};

	template < typename _Type, typename _ContainerType >
	bool	operator== (const stack< _Type, _ContainerType >& lhs, const stack< _Type, _ContainerType >& rhs)
	{
		return (lhs._container == rhs._container);
	}

	template < typename _Type, typename _ContainerType >
	bool	operator!= (const stack< _Type, _ContainerType >& lhs, const stack< _Type, _ContainerType >& rhs)
	{
		return (lhs._container != rhs._container);
	}

	template < typename _Type, typename _ContainerType >
	bool	operator< (const stack< _Type, _ContainerType >& lhs, const stack< _Type, _ContainerType >& rhs)
	{
		return (lhs._container < rhs._container);
	}

	template < typename _Type, typename _ContainerType >
	bool	operator<= (const stack< _Type, _ContainerType >& lhs, const stack< _Type, _ContainerType >& rhs)
	{
		return (lhs._container <= rhs._container);
	}

	template < typename _Type, typename _ContainerType >
	bool	operator> (const stack< _Type, _ContainerType >& lhs, const stack< _Type, _ContainerType >& rhs)
	{
		return (lhs._container > rhs._container);
	}

	template < typename _Type, typename _ContainerType >
	bool	operator>= (const stack< _Type, _ContainerType >& lhs, const stack< _Type, _ContainerType >& rhs)
	{
		return (lhs._container >= rhs._container);
	}
}

#endif