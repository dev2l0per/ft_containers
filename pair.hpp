#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft {
	template < typename _T1, typename _T2 >
	class pair {
		public:
			typedef _T1	first_type;
			typedef _T2	second_type;

			first_type	first;
			second_type	second;

			pair() : first(_T1()), second(_T2()) {}
			template < typename _U, typename _V >
			pair(const pair< _U, _V >& pr) : first(pr.first), second(pr.second) {}
			pair(const first_type& a, const second_type& b) : first(a), second(b) {}

			virtual ~pair() {}

			pair&	operator= (const pair& pr)
			{
				if (this == &pr)
					return (*this);
				this->first = pr.first;
				this->second = pr.second;
				return (*this);
			}
	};

	template < typename _Type1, typename _Type2 >
	bool	operator== (const pair< _Type1, _Type2 >& lhs, const pair< _Type1, _Type2 >& rhs)
	{
		return ((lhs.first == rhs.first) && (lhs.second == rhs.second));
	}

	template < typename _Type1, typename _Type2 >
	bool	operator!= (const pair< _Type1, _Type2 >& lhs, const pair< _Type1, _Type2 >& rhs)
	{
		return (!(lhs == rhs));
	}
	
	template < typename _Type1, typename _Type2 >
	bool	operator< (const pair< _Type1, _Type2 >& lhs, const pair< _Type1, _Type2 >& rhs)
	{
		return ((lhs.first < rhs.first) || (!(rhs.first < lhs.first) && (lhs.second < rhs.second)));
	}

	template < typename _Type1, typename _Type2 >
	bool	operator<= (const pair< _Type1, _Type2 >& lhs, const pair< _Type1, _Type2 >& rhs)
	{
		return (!(rhs < lhs));
	}

	template < typename _Type1, typename _Type2 >
	bool	operator> (const pair< _Type1, _Type2 >& lhs, const pair< _Type1, _Type2 >& rhs)
	{
		return (rhs < lhs);
	}

	template < typename _Type1, typename _Type2 >
	bool	operator>= (const pair< _Type1, _Type2 >& lhs, const pair< _Type1, _Type2 >& rhs)
	{
		return (!(lhs < rhs));
	}

	template < typename _T1, typename _T2 >
	ft::pair< _T1, _T2 >	make_pair (_T1 x, _T2 y) {
		return (ft::pair< _T1, _T2 >(x, y));
	}
}

#endif