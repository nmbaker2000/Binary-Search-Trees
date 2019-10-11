#include <cstdlib>
#include <iostream>
#include "tree.h"

int main()
{
  using namespace std;

  TreeType<int> t;

  cout << "# nodes = " << t.NumberOfNodes() << endl;
  cout << t.ShapeIsFull() << endl;

  t.InsertItem(25);
  t.InsertItem(20);
  t.InsertItem(35);
  t.InsertItem(30);

  cout << "tree (inorder) = ";
  t.PrintTree( cout );
  cout << endl;

  cout << "# nodes = " << t.NumberOfNodes() << endl;

  t.InsertItem(40);
  t.InsertItem(15);

  cout << "# nodes = " << t.NumberOfNodes() << endl;

  cout << t.NumLevels() << endl;
  cout << t.ShapeIsFull() << endl;
  cout << t.ShapeIsSkewed() << endl;
  //t.DeleteItem(10);
  //t.DeleteItem(20);
  //t.DeleteItem(35);

  //cout << "tree (inorder) = ";
  //t.PrintTree( cout );
  //cout << endl;

  //cout << "# nodes = " << t.NumberOfNodes() << endl;

  //int item;
  //bool found;

  //cout << endl << "Enter item to find:  " << endl;
  //cin >> item;
  //t.RetrieveItem( item, found );
  //if (found)
	 // cout << "Item was found" << endl;
  //else
	 // cout << "Item was NOT found" << endl;


  //TreeType<int> t2(t);

  return 0;
}
