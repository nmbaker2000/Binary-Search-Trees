# Binary-Search-Trees
This holds my programming for Binary Search Trees

I created the following functions:
void PrintAncestorsDown(ItemType item);
  // Pre:   Item occurs in some node in the tree
  // Post:  Prints (to cout) ancestors from the root down to item (including item itself)

void PrintAncestorsUp(ItemType item);
  // Pre:   Item occurs in some node in the tree
  // Post:  Prints (to cout) ancestors from item (including item itself) up to the root

int NumLevels();
  // Post:  Return the number of levels in the tree.


bool ShapeIsFull();
  // Post:  Returns whether the tree is full (all leaves are at the last level and every non-leaf node 
  //           has two children).
  //            Assume the empty tree is full.

bool ShapeIsSkewed();
  // Post:  Returns whether the tree is skewed (every node has one or no children).
  //            Assume the empty tree is skewed.
