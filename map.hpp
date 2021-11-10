/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruiz-ca <pruiz-ca@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 01:46:20 by pruiz-ca          #+#    #+#             */
/*   Updated: 2021/11/10 16:39:12 by pruiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "utils/redblack_tree.hpp"

namespace ft {
	/*
	** MAP
	*/
	template <typename Key, typename T, typename Compare = std::less<Key>, typename Allocator = std::allocator<ft::pair<const Key, T> > >
	class map {
		public:
			/*-----
			Definitions
			------*/
			typedef Key														key_type;
			typedef T														mapped_type;
			typedef ft::pair<const key_type, mapped_type>					value_type;
			typedef Compare													key_compare;
			typedef Allocator												allocator_type;
			typedef ft::Node<value_type>									node_type;
			typedef node_type*												node_pointer;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::size_type						size_type;
			typedef typename allocator_type::difference_type				difference_type;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;

			/*-----
			Value Compare
			------*/
			class value_compare {
				public:
					typedef key_compare		comp;
					bool	operator()(const value_type& x, const value_type& y) const {
						return comp()(x.first, y.first);
					}
			};

			typedef ft::RbTree<value_type, value_compare, allocator_type>	tree_type;
			typedef typename tree_type::iterator							iterator;
			typedef typename tree_type::const_iterator						const_iterator;
			typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;

		private:
			tree_type		_rbtree;
			key_compare		_compare;
			allocator_type	_allocator;
			value_compare	_value_compare;

		public:
			/*-----
			Constructors
			------*/
			/*-- Default --*/
			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _rbtree(), _compare(comp), _allocator(alloc), _value_compare(value_compare()) {}

			/*-- Range --*/
			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {
				_compare = comp;
				_allocator = alloc;
				_value_compare = value_compare();
				for (InputIterator tmp = first; tmp != last; tmp++)
					_rbtree.insert(*tmp);
			}

			/*-- Copy --*/
			map(const map& other) { *this = other; }

			/*-- Assign --*/
			map&	operator=(const map& other) {
				if (this != &other) {
					_rbtree = other._rbtree;
					_allocator = other._allocator;
					_compare = other._compare;
					_value_compare = other._value_compare;
				}
				return *this;
			}

			/*-----
			Destructor
			------*/
			~map() {}

			/*-----
			Iterators
			------*/
			/*-- Begin / End --*/
			iterator		begin() { return _rbtree.begin(); }
			const_iterator	begin() const { return _rbtree.begin(); }
			iterator		end() { return _rbtree.end(); }
			const_iterator	end() const { return _rbtree.end(); }

			/*-- Rbegin / Rend --*/
			reverse_iterator		rbegin() { return _rbtree.rbegin(); }
			const_reverse_iterator	rbegin() const { return _rbtree.rbegin(); }
			reverse_iterator		rend() { return _rbtree.rend(); }
			const_reverse_iterator	rend() const { return _rbtree.rend(); }

			/*-----
			Capacity
			------*/
			bool		empty() const { return _rbtree.getSize() == 0; }
			size_type	size() const { return _rbtree.getSize(); }
			size_type	max_size() const { return _rbtree.max_size(); }

			/*-----
			Element access
			------*/
			/*-- Operator[] --*/
			mapped_type&	operator[](const key_type& k) {
				iterator		result = find(k);
				if (result != end())
					return result->second;
				else {
					insert(ft::make_pair(k, mapped_type()));
					result = find(k);
					return result->second;
				}
			}

			/*-----
			Modifiers
			------*/
			/*-- Insert --*/
			pair<iterator, bool>	insert(const value_type& val) {
				return _rbtree.insert(val);
			}

			iterator				insert(iterator position, const value_type&  val) {
				(void)position;
				return _rbtree.insert(val).first;
			}

			template <typename InputIterator>
			void					insert(InputIterator first, InputIterator last) {
				for (InputIterator tmp = first; tmp != last;)
					_rbtree.insert(*(tmp++));
			}

			/*-- Erase --*/
			void	erase(iterator pos) {
				_rbtree.remove(*pos);
			}

			void	erase(iterator first, iterator last) {
				for (iterator it = first; it != last;)
					_rbtree.remove(*(it++));
			}

			size_type	erase(const key_type& key) {
				iterator	found = find(key);

				if (found != end()) {
					_rbtree.remove(*found);
					return 1;
				}
				return 0;
			}

			/*-- Swap --*/
			void	swap(map& other) {
				ft::swap(_allocator, other._allocator);
				ft::swap(_compare, other._compare);
				ft::swap(_value_compare, other._value_compare);
				_rbtree.swap(other._rbtree);
			}

			/*-- Clear --*/
			void	clear() { _rbtree.clear(); }

			/*-----
			Observers
			------*/
			/*-- Key_comp --*/
			key_compare	key_comp() const { return _compare; }

			/*-- Value_comp --*/
			value_compare	value_comp() const { return _value_compare; }

			/*-----
			Operations
			------*/
			/*-- Find --*/
			iterator	find(Key const& key) {
				node_pointer		found = _rbtree.find(ft::make_pair(key, mapped_type()));

				if (found != NULL)
					return iterator(found, _rbtree.getRootNode(), _rbtree.getNilNode());
				return end();
			}

			const_iterator	find(Key const& key) const {
				node_pointer		found = _rbtree.find(ft::make_pair(key, mapped_type()));

				if (found != NULL)
					return const_iterator(found, _rbtree.getRootNode(), _rbtree.getNilNode());
				return end();
			}

			/*-- Count --*/
			size_type	count(const Key& key) const {
				if (_rbtree.find(ft::make_pair(key, mapped_type())) != NULL)
					return 1;
				return 0;
			}

			/*-- Lower bound --*/
			iterator	lower_bound(const Key& key) {
				for (iterator it = begin(); it != end(); it++)
					if (_value_compare(ft::make_pair(key, mapped_type()), it.getNode()->data) || !_value_compare(it.getNode()->data, ft::make_pair(key, mapped_type())))
						return it;
				return end();
			}

			const_iterator	lower_bound(const Key& key) const {
				for (const_iterator it = begin(); it != end(); it++)
					if (_value_compare(ft::make_pair(key, mapped_type()), it.getNode()->data) || !_value_compare(it.getNode()->data, ft::make_pair(key, mapped_type())))
						return it;
				return end();
			}

			/*-- Upper bound --*/
			iterator	upper_bound(const Key& key) {
				for (iterator it = begin(); it != end(); it++)
					if (_value_compare(ft::make_pair(key, mapped_type()), it.getNode()->data))
						return it;
				return end();
			}

			const_iterator	upper_bound(const Key& key) const {
				for (const_iterator it = begin(); it != end(); it++)
					if (_value_compare(ft::make_pair(key, mapped_type()), it.getNode()->data))
						return it;
				return end();
			}

			/*-- Equal range --*/
			pair<iterator, iterator>	equal_range(const Key& key) {
				return ft::make_pair(lower_bound(key), upper_bound(key));
			}

			pair<const_iterator, const_iterator>	equal_range(const Key& key) const {
				return ft::make_pair(lower_bound(key), upper_bound(key));
			}

			/*-----
			Allocator
			------*/
			/*-- Get allocator --*/
			allocator_type	get_allocator() const { return _allocator; }
	};

	/*-----
	Non-member overloads
	------*/
	/*-- Relational operators --*/
	template<typename Key, typename T, typename Compare, typename Alloc>
	bool	operator==(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template<typename Key, typename T, typename Compare, typename Alloc>
	bool	operator!=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
		return !(lhs == rhs);
	}

	template<typename Key, typename T, typename Compare, typename Alloc>
	bool	operator<(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template<typename Key, typename T, typename Compare, typename Alloc>
	bool	operator>(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
		return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}

	template<typename Key, typename T, typename Compare, typename Alloc>
	bool	operator<=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
		return (lhs == rhs || lhs < rhs);
	}

	template<typename Key, typename T, typename Compare, typename Alloc>
	bool	operator>=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
		return (lhs == rhs || lhs > rhs);
	}

	/*-- Swap --*/
	template<typename Key, typename T, typename Compare, typename Alloc>
	void	swap(map<Key, T, Compare, Alloc>& x, map<Key, T, Compare, Alloc>& y) {
		x.swap(y);
	}
}