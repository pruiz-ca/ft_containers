/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruiz-ca <pruiz-ca@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 12:46:42 by pruiz-ca          #+#    #+#             */
/*   Updated: 2021/10/04 16:39:53 by pruiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator_traits.hpp"

namespace ft {
	/*
	** VECTOR ITERATOR
	*/
	template <typename T>
	class vector_iterator {
		public:
			/*-- Iterator traits --*/
			typedef typename ft::iterator_traits<T>::value_type			value_type;
			typedef typename ft::iterator_traits<T>::difference_type	difference_type;
			typedef typename std::random_access_iterator_tag			iterator_category;
			typedef typename ft::iterator_traits<T>::pointer			pointer;
			typedef typename ft::iterator_traits<T>::reference			reference;

		private:
			pointer		_ptr;

		public:
			/*-- Coplien --*/
			vector_iterator() : _ptr(0) {}
			~vector_iterator() {}
			template <typename U>	vector_iterator(const vector_iterator<U> &u) {
				_ptr = u.base();
			}

			template <typename U>	vector_iterator&	operator=(const vector_iterator<U>& u) {
				_ptr = u.base();
				return *this;
			}

			/*-- Getter --*/
			pointer		base() const { return _ptr; }

			/*-- Constructor --*/
			explicit	vector_iterator(T x) : _ptr(x) {}

			/*-- Operators overload --*/
			reference			operator*() const { return *_ptr; }
			pointer				operator->() const { return _ptr; }
			vector_iterator		operator+(difference_type n) const { return vector_iterator(this->_ptr + n); }
			vector_iterator		operator-(difference_type n) const { return vector_iterator(this->_ptr - n); }
			reference			operator[](difference_type n) const { return *(*this + n); }

			vector_iterator&	operator+=(difference_type n) {
				this->_ptr += n;
				return *this;
			}

			vector_iterator&	operator-=(difference_type n) {
				this->_ptr -= n;
				return *this;
			}

			vector_iterator&	operator++() {
				this->_ptr++;
				return *this;
			}

			vector_iterator		operator++(int) {
				vector_iterator	tmp(*this);
				operator++();
				return tmp;
			}

			vector_iterator&	operator--() {
				this->_ptr--;
				return *this;
			}

			vector_iterator		operator--(int) {
				vector_iterator	tmp(*this);
				operator--();
				return tmp;
			}
	};

	template <typename U, typename V>
	bool	operator==(const vector_iterator<U>& lhs, const vector_iterator<V>& rhs) {
		return lhs.base() == rhs.base();
	}

	template <typename U, typename V>
	bool	operator!=(const vector_iterator<U>& lhs, const vector_iterator<V>& rhs) {
		return lhs.base() != rhs.base();
	}

	template <typename U, typename V>
	bool		operator>(const vector_iterator<U>& lhs, const vector_iterator<V>& rhs) {
		return lhs.base() > rhs.base();
	}

	template <typename U, typename V>
	bool		operator<(const vector_iterator<U>& lhs, const vector_iterator<V>& rhs) {
		return lhs.base() < rhs.base();
	}

	template <typename U, typename V>
	bool		operator>=(const vector_iterator<U>& lhs, const vector_iterator<V>& rhs) {
		return lhs.base() >= rhs.base();
	}

	template <typename U, typename V>
	bool		operator<=(const vector_iterator<U>& lhs, const vector_iterator<V>& rhs) {
		return lhs.base() <= rhs.base();
	}

	template <typename U, typename V>
	ptrdiff_t		operator-(const vector_iterator<U>& lhs, const vector_iterator<V>& rhs) {
		return lhs.base() - rhs.base();
	}

	template <typename U>
	vector_iterator<U>		operator+(typename vector_iterator<U>::difference_type n, const vector_iterator<U>& rhs) {
		return (vector_iterator<U>)(rhs.base() + n);
	}
}
