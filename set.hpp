/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruiz-ca <pruiz-ca@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 19:47:37 by pruiz-ca          #+#    #+#             */
/*   Updated: 2021/11/10 16:39:20 by pruiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "utils/redblack_tree.hpp"

namespace ft {
	/*
	** SET
	*/
	template <typename Key, typename Compare = std::less<Key>, typename Allocator = std::allocator<Key> >
	class set {
		public:
			/*-----
			Definitions
			------*/
			typedef Key														key_type;
			typedef Key														value_type;
			typedef Compare													key_compare;
			typedef Compare													value_compare;
			typedef Allocator												allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::size_type						size_type;
			typedef typename allocator_type::difference_type				difference_type;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef ft::Node<value_type>									node_type;
			typedef node_type*												node_pointer;

			typedef ft::RbTree<value_type, key_compare, allocator_type>		tree_type;
			typedef typename tree_type::const_iterator						iterator;
			typedef typename tree_type::const_iterator						const_iterator;
			typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;

		private:
			tree_type		_rbtree;
			key_compare		_compare;
			allocator_type	_allocator;

		public:
			/*-----
			Constructors
			------*/
			/*-- Default --*/
			explicit set(Compare const& comp = Compare(), Allocator const& alloc = Allocator()) : _compare(comp), _allocator(alloc) {}

			/*-- Range --*/
			template <typename InputIterator>
			set(InputIterator first, InputIterator last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) {
				_compare = comp;
				_allocator = alloc;
				for (InputIterator tmp = first; tmp != last; tmp++)
					_rbtree.insert(*tmp);
			}

			/*-- Copy --*/
			set(const set<Key, Compare, Allocator>& other) { *this = other; }

			/*-- Assign --*/
			set&	operator=(const set& other) {
				if (this != &other) {
					_rbtree = other._rbtree;
					_allocator = other._allocator;
					_compare = other._compare;
				}
				return *this;
			}

			/*-----
			Destructor
			------*/
			~set() {}

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
			void	swap(set& other) {
				ft::swap(_allocator, other._allocator);
				ft::swap(_compare, other._compare);
				_rbtree.swap(other._rbtree);
			}

			/*-- Clear --*/
			void	clear() { _rbtree.clear(); }

			/*-----
			Operations
			------*/
			/*-- Find --*/
			iterator	find(Key const& key) {
				node_pointer		found = _rbtree.find(key);

				if (found != NULL)
					return iterator(found, _rbtree.getRootNode(), _rbtree.getNilNode());
				return end();
			}

			const_iterator	find(Key const& key) const {
				node_pointer		found = _rbtree.find(key);

				if (found != NULL)
					return const_iterator(found, _rbtree.getRootNode(), _rbtree.getNilNode());
				return end();
			}

			/*-- Count --*/
			size_type	count(const Key& key) const {
				if (_rbtree.find(key) != NULL)
					return 1;
				return 0;
			}

			/*-- Lower bound --*/
			iterator	lower_bound(const Key& key) {
				for (iterator it = begin(); it != end(); it++)
					if (_compare(key, it.getNode()->data) || !_compare(it.getNode()->data, key))
						return it;
				return end();
			}

			const_iterator	lower_bound(const Key& key) const {
				for (const_iterator it = begin(); it != end(); it++)
					if (_compare(key, it.getNode()->data) || !_compare(it.getNode()->data, key))
						return it;
				return end();
			}

			/*-- Upper bound --*/
			iterator	upper_bound(const Key& key) {
				for (iterator it = begin(); it != end(); it++)
					if (_compare(key, it.getNode()->data))
						return it;
				return end();
			}

			const_iterator	upper_bound(const Key& key) const {
				for (const_iterator it = begin(); it != end(); it++)
					if (_compare(key, it.getNode()->data))
						return it;
				return end();
			}

			/*-- Equal range --*/
			pair<iterator, iterator>	equal_range(const Key& key) {
				return make_pair(lower_bound(key), upper_bound(key));
			}

			pair<const_iterator, const_iterator>	equal_range(const Key& key) const {
				return make_pair(lower_bound(key), upper_bound(key));
			}

			/*-----
			Observers
			------*/
			/*-- Key_comp --*/
			key_compare	key_comp() const { return _compare; }

			/*-- Value_comp --*/
			value_compare	value_comp() const { return _compare; }

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
	template<typename Key, typename Compare, typename Alloc>
	bool	operator==(const ft::set<Key, Compare, Alloc> &lhs, const ft::set<Key, Compare, Alloc> &rhs) {
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template<typename Key, typename Compare, typename Alloc>
	bool	operator!=(const ft::set<Key, Compare, Alloc> &lhs, const ft::set<Key, Compare, Alloc> &rhs) {
		return !(lhs == rhs);
	}

	template<typename Key, typename Compare, typename Alloc>
	bool	operator<(const ft::set<Key, Compare, Alloc> &lhs, const ft::set<Key, Compare, Alloc> &rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template<typename Key, typename Compare, typename Alloc>
	bool	operator>(const ft::set<Key, Compare, Alloc> &lhs, const ft::set<Key, Compare, Alloc> &rhs) {
		return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}

	template<typename Key, typename Compare, typename Alloc>
	bool	operator<=(const ft::set<Key, Compare, Alloc> &lhs, const ft::set<Key, Compare, Alloc> &rhs) {
		return (lhs == rhs || lhs < rhs);
	}

	template<typename Key, typename Compare, typename Alloc>
	bool	operator>=(const ft::set<Key, Compare, Alloc> &lhs, const ft::set<Key, Compare, Alloc> &rhs) {
		return (lhs == rhs || lhs > rhs);
	}

	/*-- Swap --*/
	template<typename Key, typename Compare, typename Alloc>
	void	swap(set<Key, Compare, Alloc>& x, set<Key, Compare, Alloc>& y) {
		x.swap(y);
	}
}