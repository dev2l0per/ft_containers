#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft {
	template < bool _Cond, typename _T = void >
	class enable_if {

	};

	template < typename _T >
	class enable_if < true, _T > {
		public:
			typedef _T type;
	};

	template < typename _T >
	class is_integral {
		public:
			static const bool	value = false;
	};

	template <>
	class is_integral < bool > {
		public:
			static const bool	value = true;
	};

	template <>
	class is_integral < char > {
		public:
			static const bool	value = true;
	};

	template <>
	class is_integral < wchar_t > {
		public:
			static const bool	value = true;
	};

	template <>
	class is_integral < int > {
		public:
			static const bool	value = true;
	};

	template <>
	class is_integral < short > {
		public:
			static const bool	value = true;
	};

	template <>
	class is_integral < long > {
		public:
			static const bool	value = true;
	};

	template <>
	class is_integral < long long > {
		public:
			static const bool	value = true;
	};

	template <>
	class is_integral < unsigned char > {
		public:
			static const bool	value = true;
	};

	template <>
	class is_integral < unsigned short > {
		public:
			static const bool	value = true;
	};

	template <>
	class is_integral < unsigned int > {
		public:
			static const bool	value = true;
	};

	template <>
	class is_integral < unsigned long > {
		public:
			static const bool	value = true;
	};

	template <>
	class is_integral < unsigned long long > {
		public:
			static const bool	value = true;
	};

	template < typename _Type, typename _constType, bool isConst = false >
	class typeSelector {
		public:
			typedef _Type	type;
	};

	template < typename _Type, typename _constType>
	class typeSelector< _Type, _constType, true > {
		public :
			typedef _constType	type;
	};

	template < typename _T >
	class less {
		public:
			bool	operator() (const _T& x, const _T& y) const
			{
				return (x < y);
			}
	};

	template < typename _InputIterator1, typename _InputIterator2 >
	bool	equal (_InputIterator1 first1, _InputIterator1 last1, _InputIterator2 first2) {
		while (first1 != last1) {
			if (!(*first1 == *first2))
				return (false);
			++first1;
			++first2;
		}
		
		return (true);
	}

	template < typename _InputIterator1, typename _InputIterator2 >
	bool	lexicographical_compare (_InputIterator1 first1, _InputIterator1 last1, _InputIterator2 first2, _InputIterator2 last2) {
		while (first1 != last1) {
			if (first2 == last2 || *first2 < *first1)
				return (false);
			else if (*first1 < *first2)
				return (true);
			++first1;
			++first2;
		}

		return (first2 != last2);
	}
}

#endif