/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruiz-ca <pruiz-ca@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 12:46:42 by pruiz-ca          #+#    #+#             */
/*   Updated: 2021/10/10 21:35:25 by pruiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator_traits.hpp"
#include "../utils/redblack_tree.hpp"

namespace ft {
	/*
	** RED BLACK TREE ITERATOR
	*/
	template <typename Node, typename Pair>
	class rbtree_iterator {
		public:
			/*-- Iterator traits --*/
 			typedef Pair										value_type;
			typedef ptrdiff_t									difference_type;
			typedef typename std::bidirectional_iterator_tag	iterator_category;
			typedef Node										node_pointer;
			typedef value_type*									pointer;
			typedef value_type&									reference;

		protected:
			node_pointer		_node;
			node_pointer		_root;
			node_pointer		_nil;

		public:
			/*-- Coplien --*/
			rbtree_iterator() {}
			~rbtree_iterator() {}
			template <typename U, typename P1> rbtree_iterator(const rbtree_iterator<U,P1>& u) {
				_node = u.getNode();
				_root = u.getRoot();
				_nil = u.getNil();
			}

			template <typename U, typename P1>	rbtree_iterator&	operator=(const rbtree_iterator<U,P1>& u) {
				_node = u.getNode();
				_root = u.getRoot();
				_nil = u.getNil();
				return *this;
			}

			/*-- Constructor --*/
			explicit rbtree_iterator(node_pointer node, node_pointer root, node_pointer nil) : _node(node), _root(root), _nil(nil) {}

			/*-- Getters --*/
			node_pointer	getNode() const { return _node; }
			node_pointer	getRoot() const { return _root; }
			node_pointer	getNil() const { return _nil; }

			/*-- Operators overload --*/
			reference		operator*() const { return _node->data; }
			pointer			operator->() const { return &_node->data; }

			rbtree_iterator&	operator++() {
				if (_node->right != _nil)
					_node = min(_node->right);
				else {
					while (_node->parent != _nil && _node == _node->parent->right)
						_node = _node->parent;
					_node = _node->parent;
				}
				return *this;
			}

			rbtree_iterator		operator++(int) {
				rbtree_iterator	tmp(*this);
				operator++();
				return tmp;
			}

			rbtree_iterator&	operator--() {
				if (_node->left != _nil)
					_node = max(_node->left);
				else {
					node_pointer	p = _node->parent;
					while (p != _nil && _node == p->left) {
						_node = p;
						p = p->parent;
					}
					_node = _node->parent;
				}
				return *this;
			}

			rbtree_iterator		operator--(int) {
				rbtree_iterator	tmp(*this);
				operator--();
				return tmp;
			}

			node_pointer		min(node_pointer node) {
				while (node->left != _nil)
					node = node->left;
				return node;
			}

			node_pointer		max(node_pointer node) {
				while (node->right != _nil)
					node = node->right;
				return node;
			}
	};

	template <typename U, typename V, typename P1, typename P2>
	bool	operator==(const rbtree_iterator<U,P1>& lhs, const rbtree_iterator<V,P2>& rhs) {
		return lhs.getNode() == rhs.getNode();
	}

	template <typename U, typename V, typename P1, typename P2>
	bool	operator!=(const rbtree_iterator<U,P1>& lhs, const rbtree_iterator<V,P2>& rhs) {
		return lhs.getNode() != rhs.getNode();
	}

	template <typename U, typename V, typename P1, typename P2>
	bool		operator>(const rbtree_iterator<U,P1>& lhs, const rbtree_iterator<V,P2>& rhs) {
		return lhs.getNode() > rhs.getNode();
	}

	template <typename U, typename V, typename P1, typename P2>
	bool		operator<(const rbtree_iterator<U,P1>& lhs, const rbtree_iterator<V,P2>& rhs) {
		return lhs.getNode() < rhs.getNode();
	}

	template <typename U, typename V, typename P1, typename P2>
	bool		operator>=(const rbtree_iterator<U,P1>& lhs, const rbtree_iterator<V,P2>& rhs) {
		return lhs.getNode() >= rhs.getNode();
	}

	template <typename U, typename V, typename P1, typename P2>
	bool		operator<=(const rbtree_iterator<U,P1>& lhs, const rbtree_iterator<V,P2>& rhs) {
		return lhs.getNode() <= rhs.getNode();
	}

	template <typename U, typename V, typename P1, typename P2>
	ptrdiff_t		operator-(const rbtree_iterator<U,P1>& lhs, const rbtree_iterator<V,P2>& rhs) {
		return lhs.getNode() - rhs.getNode();
	}

	template <typename U, typename P1>
	rbtree_iterator<U,P1>		operator+(typename rbtree_iterator<U,P1>::difference_type n, const rbtree_iterator<U,P1>& rhs) {
		return (rbtree_iterator<U,P1>)(rhs.getNode() + n);
	}
}
