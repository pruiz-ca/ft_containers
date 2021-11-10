/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruiz-ca <pruiz-ca@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:40:11 by pruiz-ca          #+#    #+#             */
/*   Updated: 2021/10/11 18:40:12 by pruiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft {
	/*-----
	Pair
	-----*/
	template<typename T1, typename T2>
	class pair {
		public:
			typedef ft::pair<T1,T2>		value_type;
			typedef T1					key_type;
			typedef T2					mapped_type;

			T1		first;
			T2		second;

			/*-- Constructor --*/
			pair() : first(key_type()), second(mapped_type()) {}
			pair(const T1& x, const T2& y) : first(x), second(y) {}
			~pair() {}

			template<typename U1, typename U2>
			pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {}

			/*-- Operator = --*/
			pair&	operator=(const pair& other) {
				if (this == &other)
					return *this;
				first = other.first;
				second = other.second;
				return *this;
			}
	};

	/*-----
	Non-member overloads
	------*/
	template<typename T1, typename T2>
	ft::pair<T1, T2>	make_pair(const T1& t, const T2& u) {
		return pair<T1, T2>(t, u);
	}

	template<typename T1, typename T2>
	bool	operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return (lhs.first == rhs.first && lhs.second == rhs.second); }
	template<typename T1, typename T2>
	bool	operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return !(lhs == rhs); }
	template<typename T1, typename T2>
	bool	operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return (lhs.first < rhs.first || lhs.second < rhs.second); }
	template<typename T1, typename T2>
	bool	operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return rhs < lhs; }
	template<typename T1, typename T2>
	bool	operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return (lhs == rhs || lhs < rhs); }
	template<typename T1, typename T2>
	bool	operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return (lhs == rhs || rhs < lhs); }
}