/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruiz-ca <pruiz-ca@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 12:46:51 by pruiz-ca          #+#    #+#             */
/*   Updated: 2021/10/11 18:30:24 by pruiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "vector.hpp"

namespace ft {
	/*
	** STACK
	*/
	template<typename T, typename Container = vector<T> >
	class stack {
		public:
			/*-----
			Definitions
			------*/
			typedef Container									container_type;
			typedef typename container_type::value_type			value_type;
			typedef typename container_type::reference			reference;
			typedef typename container_type::const_reference	const_reference;
			typedef typename container_type::size_type			size_type;

		protected:
			container_type	c;

		public:
			/*-----
			Constructors
			------*/
			/*-- Default --*/
			virtual ~stack() {}
			explicit stack(const Container& other = Container()) : c(other) {}
			stack(const stack& other) : c(other.c) {}

			/*-- Operator = --*/
			stack&	operator=(const stack& other) {
				c = other.c;
				return *this;
			}

			/*-----
			Element Access
			------*/
			/*-- Top --*/
			reference	top() { return c.back(); }
			const_reference	top() const { return c.back(); }

			/*-----
			Capacity
			------*/
			/*-- Empty --*/
			bool		empty() const { return c.empty(); }

			/*-- Size --*/
			size_type	size() const { return c.size(); }

			/*-----
			Modifiers
			------*/
			/*-- Push --*/
			void	push( const value_type& value) {
				c.push_back(value);
			}

			/*-- Pop --*/
			void	pop() {
				c.pop_back();
			}

			template<class U, class V>
			friend bool	operator==(const stack<U, V> &lhs, const stack<U, V> &rhs);

			template<class U, class V>
			friend bool	operator<(const stack<U, V> &lhs, const stack<U, V> &rhs);
	};

	template<class T, class Container>
	bool	operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return lhs.c == rhs.c;
	}

	template<class T, class Container>
	bool	operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return !(lhs == rhs);
	}

	template<class T, class Container>
	bool	operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return lhs.c < rhs.c;
	}

	template<class T, class Container>
	bool	operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return rhs < lhs;
	}

	template<class T, class Container>
	bool	operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return (lhs < rhs || lhs == rhs);
	}

	template<class T, class Container>
	bool	operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return (rhs < lhs || lhs == rhs);
	}
}