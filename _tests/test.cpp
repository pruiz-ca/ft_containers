/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruiz-ca <pruiz-ca@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 13:11:35 by pruiz-ca          #+#    #+#             */
/*   Updated: 2021/11/10 16:38:52 by pruiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vector.hpp"
#include "../map.hpp"
#include <vector>
#include <map>
#include <iostream>

#define ITERATOR_TEST 0
#define VECTOR_CONSTR_TEST 0
#define VECTOR_CAPACITY_TEST 0
#define COMPARE_TEST 0
#define INSERT_TEST 0

#define MAP_TEST 1

#ifndef NSP
# define NSP ft
#endif

#define YEL "\001\e[0;33m\002"
#define CYN "\001\e[0;36m\002"
#define NOCOL "\001\e[0m\002"

int		main(void)
{
	/*
	** Iterator tests
	*/
	if (ITERATOR_TEST) {
		std::cout << std::endl << std::endl << "** ITERATOR TESTS **" << std::endl << std::endl;
		int		*array;

		array = (int *)malloc(sizeof(int) * 100);
		array[100] = '\0';
		for (int i = 0; i < 100; i++)
			array[i] = i + 42;

		NSP::vector_iterator<int*>		iterator(array);
		NSP::reverse_iterator<int*>	riterator(array + 100);

		std::cout << std::endl << CYN << "\t/* Print iterators initial value */" << NOCOL << std::endl;
		std::cout << "Iterator:\t" << *(iterator) << "  |  Reverse Iterator:\t" << *(riterator) << std::endl;

		std::cout << std::endl << CYN << "\t/* Test ++/-- iterators */" << NOCOL << std::endl;
		std::cout << "++Iterator:\t" << *(++iterator) << "  |  ++Reverse Iterator:\t" << *(++riterator) << std::endl;
		std::cout << "Iterator++:\t" << *(iterator++) << "  |  Reverse Iterator++:\t" << *(riterator++) << std::endl;
		std::cout << "Iterator:\t" << *(iterator) << "  |  Reverse Iterator:\t" << *(riterator) << std::endl;
		std::cout << "--Iterator:\t" << *(--iterator) << "  |  --Reverse Iterator:\t" << *(--riterator) << std::endl;
		std::cout << "Iterator--:\t" << *(iterator--) << "  |  Reverse Iterator--:\t" << *(riterator--) << std::endl;
		std::cout << "Iterator:\t" << *(iterator) << "  |  Reverse Iterator:\t" << *(riterator) << std::endl;

		std::cout << std::endl << CYN << "\t/* Test +/- iterators */" << NOCOL << std::endl;
		std::cout << "Iterator + 2:\t" << *(iterator + 2) << "  |  Reverse Iterator + 2:\t" << *(riterator + 2) << std::endl;
		std::cout << "Iterator - 2:\t" << *(iterator - 2) << "  |  Reverse Iterator - 2:\t" << *(riterator - 2) << std::endl;

		std::cout << std::endl << CYN << "\t/* Test +=/-= iterators */" << NOCOL << std::endl;
		std::cout << "Iterator += 2:\t" << *(iterator += 2) << "  |  Reverse Iterator += 2:\t" << *(riterator += 2) << std::endl;
		std::cout << "Iterator -= 2:\t" << *(iterator -= 2) << "  |  Reverse Iterator -= 2:\t" << *(riterator -= 2) << std::endl;

		std::cout << std::endl << CYN << "\t/* Test [] */" << NOCOL << std::endl;
		std::cout << "Iterator[10]:\t" << iterator[10] << "  |  Reverse Iterator[10]:\t" << riterator[10] << std::endl;
		std::cout << "Iterator[42]:\t" << iterator[42] << "  |  Reverse Iterator[42]:\t" << riterator[42] << std::endl;

		free(array);
	}

	/*
	** Vector tests
	*/
	if (VECTOR_CONSTR_TEST) {
		std::cout << std::endl << std::endl << "** VECTOR TESTS **" << std::endl << std::endl;
		NSP::vector<int>				vectorDefault;
		NSP::vector<int>				vectorFill(10, 97);
		NSP::vector<int>				vectorRange(10, 97);
		NSP::vector<int>				vectorCopy(vectorFill);
		NSP::vector<int>				vectorAssign = vectorCopy;

		NSP::vector<int>::reverse_iterator	it = vectorFill.rbegin();
		while (it != vectorFill.rend())
			std::cout << *it++ << std::endl;

		std::vector<int>			origvectorFill(10, 97);
		std::vector<int>::reverse_iterator	orig = origvectorFill.rbegin();
		while (orig != origvectorFill.rend())
			std::cout << CYN << *orig++ << std::endl << NOCOL;
	}

	/*
	** Capacity tests
	*/
	if (VECTOR_CAPACITY_TEST) {
		NSP::vector<int>			vectorcap1;
		std::vector<int>		origcap1;

		try{

		std::cout << "Size: " << vectorcap1.size() << std::endl;
		std::cout << "Max_size: " << vectorcap1.max_size() << std::endl;
		std::cout << "Capacity: " << vectorcap1.capacity() << std::endl;
		std::cout << "Empty: " << vectorcap1.empty() << std::endl;
		std::cout << std::endl << "===== " << std::endl;

		vectorcap1.reserve(10);
		for (int i = 0; i < 10; i++)
			vectorcap1.push_back(i);

		for (NSP::vector<int>::iterator it = vectorcap1.begin(); it != vectorcap1.end(); it++)
			std::cout << *it << std::endl;

		for (int i = 0; i < 10; i++)
			std::cout << vectorcap1[i] << std::endl;

		std::cout << "[4]: " << vectorcap1[4] << std::endl;
		std::cout << "At(2): " << vectorcap1.at(2) << std::endl;
		std::cout << "Front: " << vectorcap1.front() << std::endl;
		std::cout << "Back: " << vectorcap1.back() << std::endl;
		std::cout << "Size: " << vectorcap1.size() << std::endl;
		vectorcap1.pop_back();
		std::cout << "Back: " << vectorcap1.back() << std::endl;
		std::cout << "Size: " << vectorcap1.size() << std::endl;
		vectorcap1.resize(2);
		std::cout << "Resize(2): " << vectorcap1.size() << std::endl;
		vectorcap1.assign(9, 3);
		std::cout << "Assign(9, 3): " << vectorcap1.at(7) << std::endl;
		std::cout << "Size: " << vectorcap1.size() << std::endl;

		std::cout << std::endl << "===== " << std::endl;

		NSP::vector<int>		vectorinsert;
		vectorinsert.insert(vectorinsert.begin(), 8);
		vectorinsert.insert(vectorinsert.begin(), 7);
		vectorinsert.insert(vectorinsert.begin(), 6);
		vectorinsert.insert(vectorinsert.begin(), 5);

		for (size_t i = 0; i < vectorinsert.size(); i++)
			std::cout << vectorinsert[i] << std::endl;
		std::cout << std::endl;

		// vectorinsert.clear();
		// vectorinsert.insert(vectorinsert.begin() + 6, 8, 9);
		for (size_t i = 0; i < vectorinsert.size(); i++)
			std::cout << vectorinsert[i] << std::endl;
		vectorinsert.erase(vectorinsert.begin() + 1, vectorinsert.begin() + 4);

		std::cout << std::endl;
		for (size_t i = 0; i < vectorinsert.size(); i++)
			std::cout << vectorinsert[i] << std::endl;

		vectorinsert.swap(vectorcap1);
		std::cout << "Swap" << std::endl;
		for (size_t i = 0; i < vectorcap1.size(); i++)
			std::cout << vectorcap1[i] << std::endl;

		// origcap1.reserve(10);
		// for (int i = 0; i < 10; i++)
		// 	origcap1.push_back(i);
		// origcap1.erase(origcap1.begin() + 3);
		// for (int i = 0; i < origcap1.size(); i++)
		// 	std::cout << origcap1[i] << std::endl;
		}
		catch(...){ std::cout << "Exception thrown :')" << std::endl; }
	}

	if (COMPARE_TEST) {
		NSP::vector<int>			vectorcmp1;
		NSP::vector<int>			vectorcmp2;

		vectorcmp1.reserve(10);
		for (int i = 0; i < 10; i++)
			vectorcmp1.push_back(i);

		vectorcmp2.reserve(10);
		for (int i = 0; i < 10; i++)
			vectorcmp2.push_back(i);

		if (vectorcmp1 == vectorcmp2)
			std::cout << "EQUAL" << std::endl;
		else
			std::cout << "NOT EQUAL" << std::endl;

		vectorcmp1.pop_back();
		vectorcmp1.push_back(99);

		if (vectorcmp1 == vectorcmp2)
			std::cout << "EQUAL" << std::endl;
		else
			std::cout << "NOT EQUAL" << std::endl;

		if (vectorcmp1 < vectorcmp2)
			std::cout << "LESS" << std::endl;

		if (vectorcmp1 > vectorcmp2)
			std::cout << "MORE" << std::endl;

		NSP::swap(vectorcmp1, vectorcmp2);

		if (vectorcmp1 < vectorcmp2)
			std::cout << "LESS" << std::endl;

		if (vectorcmp1 > vectorcmp2)
			std::cout << "MORE" << std::endl;
	}

	if (INSERT_TEST) {
		NSP::vector<int>		vectorins1;

		for (int i = 1; i < 5; i++)
			vectorins1.push_back(i * 3);

		NSP::vector<int>				vectorins2;

		for (int i = 1; i < 5; i++)
			vectorins2.push_back(i * 5);

		vectorins2.insert(vectorins2.end(), vectorins1.begin(), vectorins1.end());

		for (NSP::vector<int>::iterator	it = vectorins2.begin(); it != vectorins2.end(); it++)
			std::cout << *it << std::endl;
	}

	if (MAP_TEST) {
		NSP::map<int,int>													map;
		// NSP::pair<ft::RbTree<value_type, key_compare>::iterator,bool>		pair;

		std::cout << (map.empty() == true ? "Empty" : "Not Empty") << std::endl;

		map.insert(ft::make_pair(12, 99));
		map.insert(ft::make_pair(13, 99));
		map.insert(ft::make_pair(14, 99));
		std::cout << (map.empty() == true ? "Empty" : "Not Empty") << std::endl;

		std::cout << "Size: " << map.size() << std::endl;
		std::cout << "Max size: " << map.max_size() << std::endl;

		std::cout << std::endl;

		std::cout << "Begin: " << map.begin()->first << std::endl;
		std::cout << "End: " << map.end()->first << std::endl;

		std::cout << "[13]: " << map[13] << std::endl;
		std::cout << "[16]: " << map[16] << std::endl;

		NSP::map<int,int>		mapClone = map;
		std::cout << "Clone Begin: " << map.begin()->first << std::endl;
		std::cout << "Clone End: " << map.end()->first << std::endl;

		std::cout << std::endl;

		std::cout << "Count 12: " << map.count(12) << std::endl;
		std::cout << "Count 42: " << map.count(42) << std::endl;

		std::cout << "Find 12: " << map.find(12)->first << std::endl;
		std::cout << "Find 42: " << map.find(42)->first << std::endl;

		std::cout << "LowerBound 14: " << map.lower_bound(14)->first << std::endl;
		std::cout << "UpperBound 14: " << map.upper_bound(14)->first << std::endl;
		// std::cout << "EqualRange 14: " << map.equal_range(14).first << std::endl;

	}
}
