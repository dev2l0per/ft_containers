#include "RBTree.hpp"
#include <algorithm>
#include <time.h>

int main(void)
{
    srand(time(NULL));
    ft::RBTree<int, std::less< int > > tree;

    // tree.insertNode(4);
    // tree.insertNode(6);
    // tree.insertNode(2);
    // tree.insertNode(3);
    // tree.insertNode(8);
    // tree.insertNode(5);
    // tree.insertNode(7);
    // tree.insertNode(9);
    // tree.insertNode(1);

    for (int i = 0; i < 100; ++i)
    {
        tree.insertNode(rand() % 100);
    }
    // tree.insertNode(1);
    tree.show_tree(tree.getRoot(), "", true);
	// tree.printInorder(tree.getRoot());
	std::cout << std::endl;
    
    // tree.deleteNode(1);
    // tree.show_tree(tree.getRoot(), "", true);
	// tree.printInorder(tree.getRoot());
	// std::cout << std::endl;

    // for (int i = 0; i < 100; ++i)
    // {
    //     tree.deleteNode(rand() % 100);
    // }

    // for (int i = 0; i < 100; ++i)
    // {
    //     tree.insertNode(rand() % 100);
    // }

    // tree.deleteNode(4);
    // tree.show_tree(tree.getRoot(), "", true);
    // tree.deleteNode(7);
    // tree.show_tree(tree.getRoot(), "", true);
    // tree.deleteNode(2);
    // tree.show_tree(tree.getRoot(), "", true);
    // tree.deleteNode(3);
    // tree.show_tree(tree.getRoot(), "", true);

    // // std::cout << tree.getRoot() << std::endl;
    tree.vector.clear();
    tree.show_tree(tree.getRoot(), "", true);
	tree.printInorder(tree.getRoot());
	std::cout << std::endl;

    // tree.show_tree(tree.getRoot(), "", true);
	// tree.vector.clear();
	// tree.printInorder(tree.getRoot());
	// std::cout << std::endl;

    // for (int i = 0; i < tree.vector.size(); ++i)
	// {
	// 	// std::cout << tree.vector[i] << " ";
	// 	if (i != tree.vector.size() - 1)
	// 		if (tree.vector[i] > tree.vector[i+1])
	// 		{
	// 			std::cout << "error!" << std::endl;
	// 			break ;	
	// 		}
	// }

    return 0;
}