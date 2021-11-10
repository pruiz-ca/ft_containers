/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruiz-ca <pruiz-ca@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 11:18:09 by pruiz-ca          #+#    #+#             */
/*   Updated: 2021/11/10 16:39:29 by pruiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "utils/utils.hpp"
#include "iterators/iterator_traits.hpp"
#include "iterators/vector_iterator.hpp"
#include "iterators/reverse_iterator.hpp"
// #include <iostream>

namespace ft {
	/*
	** VECTOR
	*/
	template <typename T, typename Allocator = std::allocator<T> >
	class vector {
		public:
			/*-----
			Definitions
			------*/
			typedef T											value_type;
			typedef Allocator									allocator_type;
			typedef typename Allocator::reference				reference;
			typedef typename Allocator::const_reference			const_reference;
			typedef typename Allocator::pointer					pointer;
			typedef typename Allocator::const_pointer			const_pointer;
			typedef ft::vector_iterator<pointer>				iterator;
			typedef ft::vector_iterator<const_pointer>			const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef typename Allocator::difference_type			difference_type;
			typedef typename Allocator::size_type				size_type;

		private:
			T*			_data;
			size_type	_size;
			size_type	_capacity;
			Allocator	_allocator;

		public:
			/*-----
			Constructors
			------*/
			/*-- Default --*/
			explicit vector (const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _allocator(alloc) {
				_data = _allocator.allocate(_capacity);
			}

			/*-- Fill --*/
			explicit vector (size_type n, const value_type& value = value_type(), const allocator_type& alloc = allocator_type()) : _size(n), _capacity(n), _allocator(alloc) {
				_data = _allocator.allocate(_capacity);
				for (size_type i = 0; i < _capacity; i++)
					_allocator.construct(&_data[i], value);
			}

			/*-- Range --*/
			template <typename InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) : _size(0), _capacity(0), _allocator(alloc) {
				size_type		elementNumber = 0;

				for (InputIterator it = first; it != last; it++)
					elementNumber++;
				_data = _allocator.allocate(elementNumber);
				_capacity = elementNumber;
				for (InputIterator it = first; it != last; it++)
					push_back(*it);
			}

			/*-- Copy --*/
			vector (const vector& x) : _size(x._size), _capacity(x._capacity), _allocator(x._allocator) {
				_data = _allocator.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_allocator.construct(&_data[i], x._data[i]);
			}

			/*-- Assign --*/
			vector& operator=(const vector& x) {
				if (this != &x) {
					clear();
					_allocator.deallocate(_data, _capacity);
					if (x._size > _capacity)
						_capacity = x._size;
					_data = _allocator.allocate(_capacity);
					_size = x._size;
					for (size_type i = 0; i < x._size; i++)
						_allocator.construct(&_data[i], x._data[i]);
				}
				return *this;
			}

			/*-----
			Destructor
			------*/
			virtual ~vector() { _allocator.deallocate(_data, _capacity); }

			/*-----
			Iterators
			------*/
			/*-- Begin / End --*/
			iterator		begin() { return iterator(_data); }
			iterator		end() { return iterator(_data + _size); }
			const_iterator	begin() const { return const_iterator(_data);	}
			const_iterator	end() const { return const_iterator(_data + _size); }

			/*-- Rbegin / Rend --*/
			reverse_iterator		rbegin() { return reverse_iterator(end()); }
			reverse_iterator		rend() { return reverse_iterator(begin()); }
			const_reverse_iterator	rbegin() const { return const_reverse_iterator(end()); }
			const_reverse_iterator	rend() const { return const_reverse_iterator(begin()); }

			/*-----
			Capacity
			------*/
			/*-- Size --*/
			size_type	size() const { return _size; }

			/*-- Max_size --*/
			size_type	max_size() const { return _allocator.max_size(); }

			/*-- Capacity --*/
			size_type	capacity() const { return _capacity; }

			/*-- Empty --*/
			bool		empty() const { return _size == 0; }

			/*-- Reserve --*/
			void		reserve(size_type new_cap) {
				if (new_cap > max_size())
					throw std::length_error("Max capacity reached");
				if (new_cap > _capacity) {
					pointer		reservedNew = _allocator.allocate(new_cap);
					for (size_type i = 0; i < _size; i++)
						_allocator.construct(&reservedNew[i], _data[i]);
					_allocator.deallocate(_data, _capacity);
					_capacity = new_cap;
					_data = reservedNew;
				}
			}

			/*-----
			Element access
			------*/
			/*-- Operator[] --*/
			reference		operator[](size_type n) { return _data[n]; }
			const reference operator[](size_type n) const { return _data[n]; }

			/*-- At --*/
			reference		 at(size_type n) {
				if (n > _capacity)
					throw std::out_of_range("Out of range");
				return _data[n];
			}

			const_reference	at(size_type n) const {
				if (n > _capacity)
					throw std::out_of_range("Out of range");
				return _data[n];
			}

			/*-- Front --*/
			reference front() { return _data[0]; }
			const_reference front() const { return _data[0]; }

			/*-- Back --*/
			reference back() { return _data[_size - 1]; }
			const_reference back() const { return _data[_size - 1]; }

			/*-----
			Modifiers
			------*/
			/*-- Assign --*/
			void	assign(size_type count, T const& value) {
				clear();
				if (_size + count > _capacity)
					reserve(_size + count);
				while (_size < count)
					push_back(value);
			}

			template<typename InputIterator>
			void	assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) {
				int count = 0;
				clear();
				for (InputIterator it = first; it != last; it++)
					count++;
				if (_size + count > _capacity)
					reserve(_size + count);
				InputIterator it = first;
				for(; it != last; it++)
					push_back(*it);
			}

			/*-- Push_back --*/
			void	push_back(T const& value) {
				if (_size == _capacity)
					reserve(_capacity < 1 ? 1 : _capacity * 2);
				_allocator.construct(&_data[_size], value);
				_size++;
			}

			/*-- Pop_back --*/
			void	pop_back() {
				if (size())
					_allocator.destroy(&_data[--_size]);
			}

			/*-- Insert --*/
			iterator	insert(iterator pos, value_type const& value) {
				size_type	match = pos - begin();

				if (_size >= _capacity)
					reserve(_size * 2 + 1);
				if (_size != 0) {
					for (size_type i = _size - 1; i >= match; i--) {
						_allocator.construct(&_data[i + 1], _data[i]);
						_allocator.destroy(&_data[i]);
					}
				}
				_allocator.construct(&_data[match], value);
				_size++;
				if (match == _size - 1)
					return --end();
				return pos;
			}

			void	insert(iterator pos, size_type n, value_type const& value) {
				ft::vector<T>	newVector(begin(), pos);
				ft::vector<T>	oldVector(pos, end());

				if (n + _size > _capacity) {
					newVector.reserve(_size * 2);
				}
				for (size_type i = 0; i < n; i++)
					newVector.push_back(value);
				for (iterator it = oldVector.begin(); it != oldVector.end(); it++) {
					newVector.push_back(*it);
				}
				*this = newVector;
			}

			template<typename InputIterator>
			void	insert(iterator pos, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) {
				ft::vector<T>	newVector(begin(), pos);
				ft::vector<T>	oldVector(pos, end());
				size_type		elementNumber = 0;

				for (InputIterator it = first; it != last; it++)
					elementNumber++;
				if (elementNumber + _size > _capacity)
					newVector.reserve(elementNumber + _size);
				for (InputIterator it = first; it != last; it++)
					newVector.push_back(*it);
				for (iterator it = oldVector.begin(); it != oldVector.end(); it++) {
					newVector.push_back(*it);
				}
				clear();
				*this = newVector;
			}

			/*-- Erase --*/
			iterator	erase(iterator pos) {
				iterator	it = this->begin();
				size_t		match = 0;

				while (it != pos) {
					it++;
					match++;
				}
				_allocator.destroy(_data + match);
				for (; match < _size - 1; match++)
					_allocator.construct(&_data[match], _data[match + 1]);
				_size--;
				return it;
			}

			iterator	erase(iterator first, iterator last) {
				size_type	count = last.base() - first.base();
				size_type	match = first.base() - _data;
				iterator	tmpEnd = this->end();

				for (size_type i = 0; i <= count; i++) {
					if (match + count < _size)
						_allocator.construct(&_data[match], _data[count + match]);
					match++;
				}
				_size -= count;
				if (first == tmpEnd)
					return this->end();
				return first;
			}

			/*-- Swap --*/
			void	swap(vector& other) {
				ft::swap(_allocator, other._allocator);
				ft::swap(_data, other._data);
				ft::swap(_size, other._size);
				ft::swap(_capacity, other._capacity);
			}

			/*-- Clear --*/
			void	clear() {
				while(_size > 0)
					pop_back();
			}

			/*-- Resize --*/
			void	resize(size_type count, T value = T()) {
				if (count > _capacity) {
					if (count < 20)
						reserve(_capacity * 2);
					else
						reserve(count);
				}
				while (_size > count)
					pop_back();
				while (_size < count)
					push_back(value);
			}

			/*-----
			Allocator
			------*/
			/*-- Get_allocator --*/
			allocator_type	get_allocator() const { return _allocator; }
	};

	/*-----
	Non-member overloads
	------*/
	/*-- Relational operators --*/
	template<typename T, typename Alloc>
	bool	operator==(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template<typename T, typename Alloc>
	bool	operator!=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
		return !(lhs == rhs);
	}

	template<typename T, typename Alloc>
	bool	operator<(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template<typename T, typename Alloc>
	bool	operator>(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
		return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}

	template<typename T, typename Alloc>
	bool	operator<=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
		return (lhs == rhs || lhs < rhs);
	}

	template<typename T, typename Alloc>
	bool	operator>=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
		return (lhs == rhs || lhs > rhs);
	}

	/*-- Swap --*/
	template<typename T, class Alloc>
	void	swap(vector<T, Alloc>& x, vector<T, Alloc>& y) {
		x.swap(y);
	}
}
