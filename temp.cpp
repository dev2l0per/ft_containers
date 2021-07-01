#include "RBTree.hpp"
#include <algorithm>
#include <time.h>

int main(void)
{
    srand(time(NULL));
    ft::RBTree<int, std::less< int > > tree;

    // tree.insertNode(1);
    // tree.insertNode(2);
    // tree.insertNode(3);

    for (int i = 0; i < 100; ++i)
    {
        tree.insertNode(i);
        std::cout << i << "th Created!" << std::endl;
    }

    tree.show_tree(tree.getRoot(), "", true);
	tree.printInorder(tree.getRoot());
	std::cout << std::endl;

    for (int i = 0; i < 100; ++i)
    {
        tree.deleteNode(i);
        std::cout << i << "th Deleted!" << std::endl;
    }

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