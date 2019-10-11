template<class ItemType>
TreeType<ItemType>::TreeType()
// Constructor
{
    root = NULL;
}

template<class ItemType>
TreeType<ItemType>::TreeType(const TreeType<ItemType>& originalTree)
// Copy constructor:  copies tree pointed to by originalTree to itself.
{
  CopyTree(root, originalTree.root);
}

template<class ItemType>
void CopyTree(TreeNode<ItemType>*& copy,
    const TreeNode<ItemType>* originalTree)
// Post: copy is the root of a tree that is a duplicate
//       of tree pointed to by originalTree.
{
  if (originalTree == NULL)
    copy = NULL;
  else
  {
    copy = new TreeNode<ItemType>;
    copy->info = originalTree->info;
    CopyTree(copy->left, originalTree->left);
    CopyTree(copy->right, originalTree->right);
  }
}

template<class ItemType>
TreeType<ItemType>::~TreeType()
// Destructor
{
  MakeEmpty();
}

template<class ItemType>
void TreeType<ItemType>::MakeEmpty()
// Remove all nodes of the tree.
{
  Destroy(root);
  root = NULL;    // flaw found by Gabe Leonard 11/15/13
}

template<class ItemType>
void Destroy(TreeNode<ItemType>*& tree)
// Post: Tree is empty; nodes have been deallocated.
{
  if (tree != NULL)
  {
    Destroy(tree->left);
    Destroy(tree->right);
    delete tree;
  }
}

template<class ItemType>
bool TreeType<ItemType>::IsEmpty() const
// Returns whether the tree is empty.
{
  return root == NULL;
}

template<class ItemType>
bool TreeType<ItemType>::IsFull() const
// Returns whether the tree is full.
{
  return false;
}

template<class ItemType>
int TreeType<ItemType>::NumberOfNodes() const
// Post: returns the number of nodes in the tree.
{
  return CountNodes(root);
}

template<class ItemType>
int CountNodes(TreeNode<ItemType>* tree)
// Post: returns the number of nodes in the tree.
{
  if (tree == NULL)
    return 0;
  else
    return CountNodes(tree->left) +
      CountNodes(tree->right) + 1;
}

template<class ItemType>
void TreeType<ItemType>::RetrieveItem(ItemType& item, bool& found)
// Calls recursive function Retrieve to search the tree for item.
{
  Retrieve(root, item, found);
}

template<class ItemType>
void Retrieve(TreeNode<ItemType>* tree, 
		 ItemType& item, bool& found)
// Recursively searches tree for item.
// Post: If there is an element someItem whose key matches item’s, 
//       found is true and item is set to a copy of someItem; 
//       otherwise found is false and item is unchanged.
{
  if (tree == NULL)
    found = false;                      // item is not found.
  else if (item < tree->info)
    Retrieve(tree->left, item, found);  // Search left subtree.
  else if (item > tree->info)
    Retrieve(tree->right, item, found); // Search right subtree.
  else
  {
    item = tree->info;                   // item is found.
    found = true;
  }
}

template<class ItemType>
void TreeType<ItemType>::InsertItem(ItemType item)
// Calls recursive function Insert to insert item into tree.
{
  Insert(root, item);
}

template<class ItemType>
void Insert(TreeNode<ItemType>*& tree, ItemType item)
// Inserts item into tree.
// Post:  item is in tree; search property is maintained.
{
  if (tree == NULL)
  {// Insertion place found.
    tree = new TreeNode<ItemType>;
    tree->right = NULL;
    tree->left = NULL;
    tree->info = item;
  }
  else if (item < tree->info)
	Insert(tree->left, item);    // Insert in left subtree.
  else
    Insert(tree->right, item);   // Insert in right subtree.
}

template<class ItemType>
void TreeType<ItemType>::DeleteItem(ItemType item)
// Calls recursive function Delete to delete item from tree.
{
    Delete(root, item);
}

template<class ItemType>
void Delete(TreeNode<ItemType>*& tree, ItemType item)
// Deletes item from tree.
// Post:  item is not in tree.
{
  if (item < tree->info)
    Delete(tree->left, item);   // Look in left subtree.
  else if (item > tree->info)
    Delete(tree->right, item);  // Look in right subtree.
  else
    DeleteNode(tree);           // Node found; call DeleteNode.
}

template<class ItemType>
void DeleteNode(TreeNode<ItemType>*& tree)
// Deletes the node pointed to by tree.
// Post: The user’s data in the node pointed to by tree is no
//       longer in the tree. If tree is a leaf node or has only
//       one non-NULL child pointer, the node pointed to by tree is
//       deleted; otherwise, the user’s data is replaced by its
//       logical predecessor and the predecessor’s node is deleted.
{
  ItemType data;
  TreeNode<ItemType>* p;
  
  p = tree;
  if (tree->left == NULL)
  {
    tree = tree->right;
    delete p;
  }
  else if (tree->right == NULL)
  {
    tree = tree->left;
    delete p;
  }
  else
  {
    GetPredecessor(tree->left, data);
    tree->info = data;
    Delete(tree->left, data);  // Delete predecessor node.
  }
}

template<class ItemType>
void GetPredecessor(TreeNode<ItemType>* tree, ItemType& data)
// Sets data to the info member of the  t node in tree.
{
  while (tree->right != NULL)
    tree = tree->right;
  data = tree->info;
}

template<class ItemType>
void TreeType<ItemType>::PrintTree(std::ostream& out) const
// Calls recursive function Print to print items in the tree.
{
  Print(root, out);
}

template<class ItemType>
void Print(TreeNode<ItemType>* tree, std::ostream& out)
// Prints info member of items in tree in sorted order on outFile.
{
  if (tree != NULL)
  {
    Print(tree->left, out);   // Print left subtree.
    out << tree->info << " "; // Print the current node, followed by a space
    Print(tree->right, out);  // Print right subtree.
  }
}

template<class ItemType>
void TreeType<ItemType>::
operator=(const TreeType<ItemType>& originalTree)
// Calls recursive function CopyTree to copy tree pointed to by
// originalTree into self.
{
  if (&originalTree == this)
    return;                      // Ignore assigning self to self.
  Destroy(root);                 // Deallocate existing tree nodes.
  CopyTree(root, originalTree.root);
}

// Pre:   Item occurs in some node in the tree
// Post:  Prints (to cout) ancestors from the root down to item (including item itself)
template<class ItemType>
void TreeType<ItemType>::PrintAncestorsDown(ItemType item) {
	PrintRecoveredAncestors(item, root);
}

template<class ItemType>
void PrintRecoveredAncestors(ItemType item, TreeNode<ItemType>* tree) {
	if (item < tree->info) {
		std::cout << tree->info << ' ';
		PrintRecoveredAncestors(item, tree->left);  // Search left subtree.
	}
	else if (item > tree->info) {
		std::cout << tree->info << ' ';
		PrintRecoveredAncestors(item, tree->right);
	}
	else
		std::cout << tree->info << std::endl;
}

// Pre:   Item occurs in some node in the tree
// Post:  Prints (to cout) ancestors from item (including item itself) up to the root
template<class ItemType>
void TreeType<ItemType>::PrintAncestorsUp(ItemType item) {
	PrintRecoveredAncestorsUp(item, root);
}

template<class ItemType>
void PrintRecoveredAncestorsUp(ItemType item, TreeNode<ItemType>* tree) {
	if (item < tree->info) {
		PrintRecoveredAncestorsUp(item, tree->left);  // Search left subtree.
		std::cout << tree->info << ' ';
	}
	else if (item > tree->info) {
		PrintRecoveredAncestorsUp(item, tree->right);
		std::cout << tree->info << ' ';
	}
	else
		std::cout << tree->info << ' ';
}

// Post:  Return the number of levels in the tree.
template<class ItemType>
int TreeType<ItemType>::NumLevels() {
	return max(getNumLevels(root) - 1, 0);
}

template<class ItemType>
int getNumLevels(TreeNode<ItemType>* tree) {
	if (tree == NULL)
		return 0;
	else {
		return max((getNumLevels(tree->right) + 1) , ((getNumLevels(tree->left))) + 1);
	}
}

int max(int x, int y) {
	return x > y ? x : y;
}

// Post:  Returns whether the tree is full (all leaves are at the last level and every non-leaf node 
//           has two children).
//            Assume the empty tree is full.
template<class ItemType>
bool TreeType<ItemType>::ShapeIsFull() {
	if (root == NULL)
		return true;
	else
		return NumberOfNodes() == (pow(2, NumLevels() + 1) - 1);
}

// Post:  Returns whether the tree is skewed (every node has one or no children).
//            Assume the empty tree is skewed.
template<class ItemType>
bool TreeType<ItemType>::ShapeIsSkewed() {
	if (root == NULL)
		return true;
	else
		return IsShapeSkewed(root);
}

template<class ItemType>
bool IsShapeSkewed(TreeNode<ItemType>* tree) {
	if (tree->right == NULL && tree->left == NULL) {
		return true;
	}
	else if (tree->right == NULL) {
		return IsShapeSkewed(tree->left);
	}
	else if (tree->left == NULL) {
		return IsShapeSkewed(tree->right);
	}
	else {
		return false;
	}
}