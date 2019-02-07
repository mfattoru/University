#include <iostream>
#include <iomanip>
#include "Tree.h"
#include <cstdlib>  // rand()
#include <string>

using std::cout;
using std::endl;
using std::setw;
using std::cin;
using std::string;

void large_test(int n_trees, int tree_size, int seed);
BSTree<int> build_full_tree(int n_nodes, int minval);

int main()
{
  BSTree<string>  t1;
  int testnum = 1;

  cout << "Test" << testnum++ << ": Basic Constructor and size" << endl;

  cout << "t1 size: " << t1.size() << endl;

  t1.insert("wii");
  t1.insert("iPod");
  t1.insert("xbox");

  cout << "\nTest" << testnum++ << ": Simple insert and sizes" << endl;
  t1.insert("ps3");

  cout << "t1: " << t1.size() << " total nodes" << endl;

  cout << "\nTest" << testnum++ << ": printing tree" << endl;
  cout << "Preorder:  ";  t1.print_pre();  cout << endl;
  cout << "Inorder:   ";  t1.print_in();   cout << endl;
  cout << "Postorder: ";  t1.print_post(); cout << endl;

  cout << "\nTest" << testnum++ << ": height" << endl;
  cout << "t1 height: " << t1.height() << endl;

  cout << "\nTest" << testnum++ << ": Clear" << endl;
  t1.clear();
  cout << "t1 size: " << t1.size() << endl;

  cout << "\nTest" << testnum++ << ": Large tree statistics" << endl;
  cout << "Random number seed? ";
  int seed;
  cin >> seed;
  large_test(2000, 2000, seed);

  cout << "\nTest" << testnum++ << ": Copy constructor" << endl;
  BSTree<int> t2;

  t2 = build_full_tree(10, 23);

  BSTree<int> t3 = t2;

  cout << "t2: "; t2.print_in(); cout << endl;
  cout << "t3: "; t3.print_in(); cout << endl;
  cout << "New t2 values" << endl;
  t2.clear();
  t2 = build_full_tree(3, 65);
  cout << "t2: "; t2.print_in(); cout << endl;
  cout << "t3: "; t3.print_in(); cout << endl;

  cout << "\nTest" << testnum++ << ": Assignment operator" << endl;
  BSTree<int> t4, t5;

  t4 = build_full_tree(11, 46);
  t5 = build_full_tree(11, 22);

  cout << "t4: "; t4.print_in(); cout << endl;
  cout << "t5: "; t5.print_in(); cout << endl;

  t4 = t5;

  t5.insert(35);

  cout << "Change values" << endl;
  cout << "t4: "; t4.print_in(); cout << endl;
  cout << "t5: "; t5.print_in(); cout << endl;

  cout << "Assignment to self" << endl;
  t5 = t5;

  BSTree<int> t6;
  t6 = build_full_tree(7, 19);

  cout << "t5: "; t5.print_in(); cout << endl;

  cout << "Chained assignment" << endl;

  BSTree<int> t7;
  t7 = build_full_tree(11, 146);

  t5 = t6 = t7;

  cout << "t5: "; t5.print_in(); cout << endl;
  cout << "t6: "; t6.print_in(); cout << endl;
  cout << "t7: "; t7.print_in(); cout << endl;

  cout << "Sizes: " << endl;
  cout << "t5: " << t5.size() << endl;
  cout << "t6: " << t6.size() << endl;
  cout << "t7: " << t7.size() << endl;

  cout << "\nTest" << testnum++ << ": Empty tests" << endl;
  t5.clear();
  cout << "t5 size: " << t5.size() << endl;
  cout << "t5 height: " << t5.height() << endl;
  cout << "t5 Preorder: "; t5.print_pre(); cout << endl;
  cout << "t5 Inorder: "; t5.print_in(); cout << endl;
  cout << "t5 Postorder: "; t5.print_post(); cout << endl;

  cout << "\nTest" << testnum++ << ": Search test" << endl;
  int query = -42;
  if(t6.find(query) == BSTree<int>::BST_OK)
    cout << query << " is in t6" << endl;
  else
    cout << query << " is not in t6" << endl;

  return 0;
}

void large_test(int n_trees, int tree_size, int seed)
{

  int height_sum = 0;
  int size_sum = 0;
  int err;

  BSTree<int> tree;

  srand(seed);

  for(int i = 0; i < n_trees; i++)
    {
      tree.clear();
      for(int j = 0; j < tree_size; j++)
	do {
	  // Only count what gets inserted
	  err = tree.insert(rand());
	} while(err == BSTree<int>::BST_DUPLICATE);

      height_sum += tree.height();
      size_sum += tree.size();
    }

  cout << "Average height: " << height_sum / float(n_trees) << endl;
  cout << "Average size: " << size_sum / float(n_trees) << endl;
}

BSTree<int> build_full_tree(int n_nodes, int minval)
{
  BSTree<int> t;

  int count = 0;

  int step = n_nodes / 2;

  while(count < n_nodes)
    {
      for(int i = step; i < n_nodes; i += step)
	{
	  if(BSTree<int>::BST_OK == t.insert(i * 19 + minval))
	    count++;  // Only count things that actually get inserted
	  if(count >= n_nodes)
	    break;
	}
      step /= 2;

    }

  return t;
}
