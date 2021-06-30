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
}

#endif