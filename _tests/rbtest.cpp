#include "../utils/redblack_tree.hpp"
#include "../iterators/rbtree_iterator.hpp"
#include <iostream>
#include <iomanip>
#include <memory>

#ifndef LEAKS
# define LEAKS 0
#endif

#define REDCOL "\001\e[38;5;206m"
#define GRNCOL "\001\e[38;5;110m"
#define NOCOL "\001\e[0m\002"

void	checkLeaks(void) {
	system("leaks a.out");
}

void	createTree(ft::RbTree<ft::pair<int, int>, std::less<int> >& rbtree) {
	rbtree.insert(ft::make_pair(12, -1));
	rbtree.insert(ft::make_pair(13, -1));
	rbtree.insert(ft::make_pair(14, -1));
	// rbtree.insert(ft::make_pair(13, -1));
	// rbtree.insert(ft::make_pair(17, -1));
	// rbtree.insert(ft::make_pair(8, -1));
	// rbtree.insert(ft::make_pair(1, -1));
	// rbtree.insert(ft::make_pair(11, -1));
	// rbtree.insert(ft::make_pair(6, -1));
	// rbtree.insert(ft::make_pair(15, -1));
	// rbtree.insert(ft::make_pair(25, -1));
	// rbtree.insert(ft::make_pair(22, -1));
	// rbtree.insert(ft::make_pair(27, -1));
}

void	createRandomTree(ft::RbTree<ft::pair<int, int>, std::less<int> >& rbtree) {
	srand(time(NULL));
	for (int i = 0; i < 10; i++)
		rbtree.insert(ft::make_pair(rand() % 100 + 1, rand() % 200 + 100));
}

void	testDelete(int value) {
	ft::RbTree<ft::pair<int, int>, std::less<int> >		rbtree;

	createTree(rbtree);
	std::cout << "===== Deleted " << value << " =====" << std::endl;
	rbtree.print();
	rbtree.remove(ft::make_pair(value, -1));
	rbtree.print();
	std::cout << std::endl;
	rbtree.clear();
}

void	testClone() {
	ft::RbTree<ft::pair<int, int>, std::less<int> >		rbtree;
	srand(time(NULL));
	for (int i = 0; i < 10; i++)
		rbtree.insert(ft::make_pair(rand() % 100 + 1, rand() % 200 + 100));
	// createTree(rbtree);
	ft::RbTree<ft::pair<int, int>, std::less<int> >		rbtreeClone(rbtree);

	rbtree.print();
	rbtree.clear();
	rbtreeClone.print();
	std::cout << std::endl;

	rbtreeClone.clear();
}

void	testIterator() {
	ft::RbTree<ft::pair<int, int>, std::less<int> >			rbtree;
	ft::rbtree_iterator<ft::Node<ft::pair<int, int> > *>	it;
	ft::rbtree_iterator<ft::Node<ft::pair<int, int> > *>	ite;

	// createRandomTree(rbtree);
	createTree(rbtree);
	rbtree.print();
	it = rbtree.begin();
	ite = rbtree.end();
	std::cout << "iterator begin: " << (*it).first << std::endl;

	for (int i = 0; i < 10; i++)
		std::cout << "iterator++: " << (*++it).first << std::endl;
	for (int i = 0; i < 10; i++)
		std::cout << "iterator--: " << (*--it).first << std::endl;

	std::cout << "iterator end: " << (*ite).first << std::endl;
}

int		main() {
	if (LEAKS)
		atexit(checkLeaks);

	// srand(time(NULL));
	// for (int i = 0; i < 20; i++)
	// 	rbtree.insert(rand() % 100 + 1, rand() % 200 + 100);
	// printBT("", rbtree.getRootNode(), false);

	// for (int i = 0; i < 10; i++)
	// 	rbtree.insert(i * 5, rand() % 200 + 100);

	// testDelete(6);
	// testDelete(1);
	// testDelete(17);
	// testDelete(25);
	// testDelete(8);
	// testDelete(13);
	// testDelete(888888);

	testClone();

	// testIterator();
}
