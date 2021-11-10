/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruiz-ca <pruiz-ca@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 12:46:32 by pruiz-ca          #+#    #+#             */
/*   Updated: 2021/10/07 11:23:30 by pruiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator_traits.hpp"

namespace ft {
	/*
	** REVERSE VECTOR ITERATOR
	*/
	template <typename T>
	class reverse_iterator {
		public:
			/*-- Iterator traits --*/
			typedef typename ft::iterator_traits<T>::value_type			value_type;
			typedef typename ft::iterator_traits<T>::difference_type	difference_type;
			typedef typename ft::iterator_traits<T>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<T>::pointer			pointer;
			typedef typename ft::iterator_traits<T>::reference			reference;

		private:
			T		_ptr;

		public:
			/*-- Coplien --*/
			reverse_iterator() : _ptr() {}
			~reverse_iterator() {}
			template <typename U>	reverse_iterator(const reverse_iterator<U> &u) {
				_ptr = u.base();
			}
			template <typename U>	reverse_iterator&	operator=(const reverse_iterator<U> &u) {
				_ptr = u.base();
				return *this;
			}

			/*-- Constructor --*/
			explicit	reverse_iterator(T x) : _ptr(x) {}

			/*-- Operators overload --*/
			reference				operator*() const {
				T	tmp = _ptr;
				return *(--tmp);
			}

			pointer					operator->() const { return addressof(operator*()); }
			reverse_iterator		operator+(difference_type n) const { return reverse_iterator(_ptr - n); }
			reverse_iterator		operator-(difference_type n) const { return reverse_iterator(_ptr + n); }
			reference				operator[](difference_type n) const { return *(*this + n); }
			T						base() const { return _ptr; }

			reverse_iterator&	operator+=(difference_type n) {
				_ptr -= n;
				return *this;
			}

			reverse_iterator&	operator-=(difference_type n) {
				_ptr += n;
				return *this;
			}

			reverse_iterator&	operator++() {
				_ptr--;
				return *this;
			}

			reverse_iterator	operator++(int) {
				reverse_iterator	tmp(*this);
				operator++();
				return tmp;
			}

			reverse_iterator&	operator--() {
				_ptr++;
				return *this;
			}

			reverse_iterator	operator--(int) {
				reverse_iterator	tmp(*this);
				operator--();
				return tmp;
			}
	};

	template <typename U, typename V>
	bool	operator==(const reverse_iterator<U>& lhs, const reverse_iterator<V>& rhs) {
		return lhs.base() == rhs.base();
	}

	template <typename U, typename V>
	bool	operator!=(const reverse_iterator<U>& lhs, const reverse_iterator<V>& rhs) {
		return lhs.base() != rhs.base();
	}

	template <typename U, typename V>
	bool		operator>(const reverse_iterator<U>& lhs, const reverse_iterator<V>& rhs) {
		return lhs.base() < rhs.base();
	}

	template <typename U, typename V>
	bool		operator<(const reverse_iterator<U>& lhs, const reverse_iterator<V>& rhs) {
		return lhs.base() > rhs.base();
	}

	template <typename U, typename V>
	bool		operator>=(const reverse_iterator<U>& lhs, const reverse_iterator<V>& rhs) {
		return lhs.base() <= rhs.base();
	}

	template <typename U, typename V>
	bool		operator<=(const reverse_iterator<U>& lhs, const reverse_iterator<V>& rhs) {
		return lhs.base() >= rhs.base();
	}

	template <typename U, typename V>
	ptrdiff_t		operator-(const reverse_iterator<U>& lhs, const reverse_iterator<V>& rhs) {
		return rhs.base() - lhs.base();
	}

	template <typename U>
	reverse_iterator<U>		operator+(typename reverse_iterator<U>::difference_type n, const reverse_iterator<U>& rhs) {
		return (reverse_iterator<U>)(rhs.base() - n);
	}
}
