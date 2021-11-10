/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redblack_tree.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruiz-ca <pruiz-ca@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 12:47:02 by pruiz-ca          #+#    #+#             */
/*   Updated: 2021/10/11 17:50:19 by pruiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#define RED 0
#define BLACK 1

#define RDCOL "\001\e[38;5;206m"
#define BKCOL "\001\e[38;5;110m"
#define NOCOL "\001\e[0m\002"

#include <iostream>
#include <iomanip>
#include "pair.hpp"
#include "utils.hpp"
#include "../iterators/iterator_traits.hpp"
#include "../iterators/rbtree_iterator.hpp"
#include "../iterators/reverse_iterator.hpp"

namespace ft {
	template <typename T>
	class Node {
		public:
			Node*		left;
			Node*		right;
			Node*		parent;
			T			data;
			bool		color;

			Node(const T& value) : left(), right(), parent(), data(value), color(BLACK) {}
			~Node() {}

			bool	isLeft() {
				if (parent && parent->left)
					return parent->left == this;
				return false;
			}

			bool	isRight() {
				if (parent && parent->right)
					return parent->right == this;
				return false;
			}

			Node*	getGrandParent() {
				if (parent && parent->parent)
					return parent->parent;
				return NULL;
			}

			Node*	getUncle() {
				if (parent && parent->isLeft())
					return getGrandParent()->right;
				if (parent && !parent->isLeft())
					return getGrandParent()->left;
				return NULL;
			}
	};

	template <typename T, typename Compare, typename Allocator>
	class RbTree {
		public:
			typedef T															value_type;
			typedef size_t														size_type;
			typedef Allocator													allocator;
			typedef ft::Node<T>													node_type;
			typedef typename Allocator::template rebind<node_type>::other		node_allocator;
			typedef Compare														compare;
			typedef typename node_allocator::pointer							pointer;
			typedef typename node_allocator::const_pointer						const_pointer;
			typedef ft::rbtree_iterator<pointer, T >							iterator;
			typedef ft::rbtree_iterator<const_pointer, const T >				const_iterator;
			typedef ft::reverse_iterator<iterator>								reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;

			RbTree() : _compare(compare()) {
				nil = _node_allocator.allocate(1);
				_node_allocator.construct(nil, value_type());
				nil->color = BLACK;
				nil->parent = nil;
				root = nil;
				size = 0;
				nil->left = root;
				nil->right = root;
				root->parent = nil;
			}

			~RbTree() {
				cascadeDestructor(root);
				_node_allocator.destroy(nil);
				_node_allocator.deallocate(nil, 1);
			}

			RbTree(const RbTree& other) {
				*this = other;
			}

			RbTree&		operator=(const RbTree& other) {
				if (this != &other) {
					clear();
					_node_allocator.destroy(nil);
					_node_allocator.deallocate(nil, 1);
					_node_allocator = other._node_allocator;
					_pair_allocator = other._pair_allocator;
					_compare = other._compare;
					nil = _node_allocator.allocate(1);
					_node_allocator.construct(nil, value_type());
					nil->color = BLACK;
					nil->parent = nil;
					root = nil;
					clone(other.root, other.nil);
					rewire();
				}
				return *this;
			}

			void	clone(pointer other, pointer otherNil) {
				if (other != otherNil) {
					insertNode(other->data);
					if (other->right != otherNil)
						insertNode(other->right->data);
					clone(other->left, otherNil);
					clone(other->right, otherNil);
				}
			}

			size_type	getSize() const { return size; }
			size_type	max_size() const {
				return node_allocator().max_size();
			}
			pointer		getRootNode() const { return root; }
			pointer		getNilNode() const { return nil; }
			pair<iterator, bool>		insert(const T& value) {
				pair<iterator, bool>	ret_pair = insertNode(value);

				rewire();
				return ret_pair;
			}

			void						remove(const T& value) {
				removeNode(value);
				rewire();
			}

			void	clear() {
				if (root && root != nil) {
					cascadeDestructor(root);
					size = 0;
					root = nil;
				}
			}

			void	swap(RbTree& other) {
				ft::swap(root, other.root);
				ft::swap(size, other.size);
				ft::swap(nil, other.nil);
				ft::swap(_node_allocator, other._node_allocator);
				ft::swap(_compare, other._compare);
			}

			pointer		min() const {
				pointer		tmp = root;

				while (tmp != nil && tmp->left != nil)
					tmp = tmp->left;
				return tmp;
			}

			pointer		max() const {
				pointer		tmp = root;

				while (tmp != nil && tmp->right != nil)
					tmp = tmp->right;
				return tmp;
			}

			iterator		begin() { return iterator(min(), root, nil); }
			iterator		end() { return iterator(nil, root, nil); }
			const_iterator	begin() const { return const_iterator(min(), root, nil); }
			const_iterator	end() const { return const_iterator(nil, root, nil); }

			reverse_iterator		rbegin() { return reverse_iterator(end()); }
			reverse_iterator		rend() { return reverse_iterator(begin()); }
			const_reverse_iterator	rbegin() const { return const_reverse_iterator(end()); }
			const_reverse_iterator	rend() const { return const_reverse_iterator(begin()); }

			void print(const std::string& prefix = "", const ft::Node<T>* node = NULL, bool isLeft = false) {
				if (node == NULL)
					node = root;
				if (node != nil) {
					std::cout << BKCOL << prefix << NOCOL;
					std::cout << BKCOL << (isLeft ? "├──" : "└──" ) << NOCOL;
					if (node->color == RED)
						std::cout << RDCOL << node->data.first << NOCOL << std::endl;
					else {
						if (node->data.first == -1)
							std::cout << "nil" << NOCOL << std::endl;
						else
							std::cout << node->data.first << NOCOL << std::endl;
					}
					print(prefix + (isLeft ? "│   " : "    "), node->right, true);
					print(prefix + (isLeft ? "│   " : "    "), node->left, false);
				}
			}

			pointer	find(value_type const& find) const {
				pointer	tmp = root;

				while (tmp != nil) {
					if (_compare(find, tmp->data))
						tmp = tmp->left;
					else if (_compare(tmp->data, find))
						tmp = tmp->right;
					else
						return tmp;
				}
				return NULL;
			}

		public:
			pointer			root;
			pointer			nil;
			size_type		size;
			node_allocator	_node_allocator;
			allocator		_pair_allocator;
			compare			_compare;

			void	cascadeDestructor(pointer node) {
				if (node != nil) {
					cascadeDestructor(node->left);
					cascadeDestructor(node->right);
					_node_allocator.destroy(node);
					_node_allocator.deallocate(node, 1);
				}
			}

			/*-----
			Generic functions
			-----*/
			pointer	createNode(const T& value) {
				pointer	newNode = _node_allocator.allocate(1);
				_node_allocator.construct(newNode, value);
				newNode->parent = nil;
				newNode->left = nil;
				newNode->right = nil;
				newNode->color = RED;
				return newNode;
			}

			pointer	createNode(const T& value, pointer parent) {
				pointer	newNode = _node_allocator.allocate(1);
				_node_allocator.construct(newNode, value);
				newNode->parent = parent;
				newNode->left = nil;
				newNode->right = nil;
				newNode->color = RED;
				return newNode;
			}

			void	rotateLeft(pointer node) {
				pointer	tmpRight = node->right;

				node->right = tmpRight->left;
				if (tmpRight->left != nil)
					tmpRight->left->parent = node;
				tmpRight->parent = node->parent;
				updateChildren(node, tmpRight);
				tmpRight->left = node;
				node->parent = tmpRight;
			}

			void	rotateRight(pointer node) {
				pointer	tmpLeft = node->left;

				node->left = tmpLeft->right;
				if (tmpLeft->right != nil)
					tmpLeft->right->parent = node;
				tmpLeft->parent = node->parent;
				updateChildren(node, tmpLeft);
				tmpLeft->right = node;
				node->parent = tmpLeft;
			}

			void	updateChildren(pointer node, pointer tmp) {
				if (node->parent == nil)
					root = tmp;
				else if (node->isLeft())
					node->parent->left = tmp;
				else
					node->parent->right = tmp;
			}

			void	swapColor(pointer n1, pointer n2) {
				bool	tmp;

				tmp = n1->color;
				n1->color = n2->color;
				n2->color = tmp;
			}

			/*-----
			Insert
			-----*/
			pair<iterator, bool>	insertNode(const T& value) {
				if (root == nil) {
					root = createNode(value);
					size++;
					rewire();
					return ft::make_pair(iterator(root, root, nil), true);
				}
				else {
					pointer		tmp = root;

					while (tmp) {
						if (_compare(tmp->data, value)) {
							if (tmp->right == nil)
								break ;
							tmp = tmp->right;
						}
						else if (_compare(value, tmp->data)) {
							if (tmp->left == nil)
								break ;
							tmp = tmp->left;
						}
						else {
							rewire();
							return ft::make_pair(iterator(tmp, root, nil), false);
						}
					}
					if (_compare(tmp->data, value)) {
						tmp->right = createNode(value, tmp);
						tmp = tmp->right;
					}
					else if (_compare(value, tmp->data)) {
						tmp->left = createNode(value, tmp);
						tmp = tmp->left;
					}
					fixInsert(tmp);
					size++;
					rewire();
					return ft::make_pair(iterator(tmp, root, nil), true);
				}
			}

			/*-----
			Insert Helper functions
			-----*/
			void	rewire() {
				root->parent = nil;
				nil->left = root;
				nil->right = root;
			}

			void	fixInsert(pointer node) {
				if (node != root && node->color == RED && node->parent->color == RED) {
					if (node->getUncle() && node->getUncle()->color == RED)
						colorCase(node->parent, node->getUncle(), node->getGrandParent());
					else if (node->parent != root && node->parent->isLeft())
						leftCase(node, node->parent, node->getGrandParent());
					else if (node->parent != root && node->parent->isRight())
						rightCase(node, node->parent, node->getGrandParent());
				}
				root->color = BLACK;
				rewire();
			}

			void	colorCase(pointer parent, pointer uncle, pointer grandParent) {
				uncle->color = BLACK;
				parent->color = BLACK;
				grandParent->color = RED;
				fixInsert(grandParent);
			}

			void	leftCase(pointer node, pointer parent, pointer grandParent) {
				if (!node->isLeft()) {
					rotateLeft(parent);
					node = parent;
					parent = node->parent;
				}
				rotateRight(grandParent);
				swapColor(parent, grandParent);
				fixInsert(parent);
			}

			void	rightCase(pointer node, pointer parent, pointer grandParent) {
				if (node->isLeft()) {
					rotateRight(parent);
					node = parent;
					parent = node->parent;
				}
				rotateLeft(grandParent);
				swapColor(parent, grandParent);
				fixInsert(parent);
			}

			/*-----
			Remove
			-----*/
			void	removeNode(const T& value) {
				pointer	nodeToRemove = root;
				pointer	x;
				pointer	y;
				while (nodeToRemove != nil && (_compare(nodeToRemove->data, value) || _compare(value, nodeToRemove->data))) {
					if (_compare(nodeToRemove->data, value))
						nodeToRemove = nodeToRemove->right;
					else if (_compare(value, nodeToRemove->data))
						nodeToRemove = nodeToRemove->left;
				}
				if (nodeToRemove == nil)
					return ;
				bool	originalColor = nodeToRemove->color;
				if (nodeToRemove->left == nil) {
					x = nodeToRemove->right;
					replaceNode(nodeToRemove, x);
				}
				else if (nodeToRemove->right == nil) {
					x = nodeToRemove->left;
					replaceNode(nodeToRemove, x);
				}
				else {
					y = predecessor(nodeToRemove->right);
					originalColor = y->color;
					x = y->right;
					if (y->parent == nodeToRemove)
						x->parent = y;
					else {
						replaceNode(y, y->right);
						y->right = nodeToRemove->right;
						y->right->parent = y;
					}
					replaceNode(nodeToRemove, y);
					y->left = nodeToRemove->left;
					y->left->parent = y;
					y->color = nodeToRemove->color;
				}
				size--;
				_node_allocator.destroy(nodeToRemove);
				_node_allocator.deallocate(nodeToRemove, 1);
				if (originalColor == BLACK)
					fixRemove(x);
			}

			/*-----
			Remove Helper functions
			-----*/
			pointer	predecessor(pointer node) {
				while (node->left != nil)
					node = node->left;
				return node;
			}

			void	replaceNode(pointer node, pointer replacement) {
				if (node->parent == nil)
					root = replacement;
				else if (node->isLeft())
					node->parent->left = replacement;
				else
					node->parent->right = replacement;
				replacement->parent = node->parent;
			}

			void	fixRemove(pointer node) {
				pointer	s;
				while (node->parent != nil && node->color == BLACK) {
					if (node->isLeft()) {
						s = node->parent->right;
						if (s->color == RED) {
							s->color = BLACK;
							node->parent->color = RED;
							rotateLeft(node->parent);
							s = node->parent->right;
						}
						if (s->right->color == BLACK && s->left->color == BLACK) {
							s->color = RED;
							node = node->parent;
						}
						else {
							if (s->right->color == BLACK) {
								s->left->color = BLACK;
								s->color = RED;
								rotateRight(s);
								s = node->parent->right;
							}
							s->color = node->parent->color;
							node->parent->color = BLACK;
							s->right->color = BLACK;
							rotateLeft(node->parent);
							node = root;
						}
					}
					else {
						s = node->parent->left;
						if (s->color == RED) {
							s->color = BLACK;
							node->parent->color = RED;
							rotateRight(node->parent);
							s = node->parent->left;
						}
						if (s->right->color == BLACK && s->left->color == BLACK) {
							s->color = RED;
							node = node->parent;
						}
						else {
							if (s->left->color == BLACK) {
								s->right->color = BLACK;
								s->color = RED;
								rotateLeft(s);
								s = node->parent->left;
							}
							s->color = node->parent->color;
							node->parent->color = BLACK;
							s->left->color = BLACK;
							rotateRight(node->parent);
							node = root;
						}
					}
				}
				node->color = BLACK;
			}
	};
}
