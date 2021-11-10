/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruiz-ca <pruiz-ca@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 01:37:52 by pruiz-ca          #+#    #+#             */
/*   Updated: 2021/09/30 16:54:01 by pruiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdexcept>

namespace ft {
	/*-----
	Helper Functions
	------*/
	template< typename T>
	void	swap( T &x, T &y) {
		T	tmp;

		tmp = x;
		x = y;
		y = tmp;
	}

	template <typename InputIterator1, typename InputIterator2>
	bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
		while (first1 != last1) {
			if (*first1 != *first2)
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template <typename InputIterator1, typename InputIterator2>
	bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
		while(first1 != last1) {
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return first2 != last2;
	}

	/*-----
	Templates
	------*/
	/*-- Enable If --*/
	template <bool B, typename T = void>
	struct enable_if {};

	template <typename T>
	struct enable_if<true, T> { typedef T type; };

	/*-- Is Integral --*/
	template <typename T>
	struct	is_integral{ static bool const value = false; };

	template <>	struct	is_integral<bool>{ static bool const value = true; };
	template <>	struct	is_integral<char>{ static bool const value = true; };
	template <>	struct	is_integral<wchar_t>{ static bool const value = true; };
	template <>	struct	is_integral<signed char>{ static bool const value = true; };
	template <>	struct	is_integral<short int>{ static bool const value = true; };
	template <>	struct	is_integral<int>{ static bool const value = true; };
	template <>	struct	is_integral<long int>{ static bool const value = true; };
	template <>	struct	is_integral<long long int>{ static bool const value = true; };
	template <>	struct	is_integral<unsigned char>{ static bool const value = true; };
	template <>	struct	is_integral<unsigned short int>{ static bool const value = true; };
	template <>	struct	is_integral<unsigned int>{ static bool const value = true; };
	template <>	struct	is_integral<unsigned long int>{ static bool const value = true; };
	template <>	struct	is_integral<unsigned long long int>{ static bool const value = true; };

	/*-- Address of --*/
	template<class T>
	T*  addressof(T& arg) {
		return reinterpret_cast<T*>(&const_cast<char&>(reinterpret_cast<const volatile char&>(arg)));
	}
}
