#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"
#include <sstream>

using namespace std;


TEST(test_empty) {
    BinarySearchTree<int> tree;
    ASSERT_EQUAL(tree.empty(), true);
    tree.insert(1);
    ASSERT_EQUAL(tree.empty(), false);
}

TEST(test_insert) {
    BinarySearchTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(0);

    ASSERT_EQUAL(tree.size(), 3u);
    ASSERT_EQUAL(tree.height(), 2u);
}

TEST(test_copy) {
    BinarySearchTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(0);

    BinarySearchTree<int> tree_copy(tree);
    BinarySearchTree<int>::Iterator it = tree_copy.begin();
    BinarySearchTree<int>::Iterator it2 = tree.begin();

    ASSERT_TRUE(*it == *it2);
    ASSERT_TRUE(*++it == *(++it2));
    ASSERT_TRUE(*++it == *(++it2));
}

TEST(test_end) {
    BinarySearchTree<int> tree;
    tree.insert(1);
    tree.insert(4);
    tree.insert(3);

    ASSERT_TRUE(tree.end() != tree.find(4));
    ASSERT_TRUE(tree.end() != tree.find(3));
    ASSERT_TRUE(tree.end() != tree.find(1));
    ASSERT_TRUE(tree.end() == tree.find(2));
}

TEST(test_assign) {
    BinarySearchTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(0);

    BinarySearchTree<int> tree_copy = tree;
    BinarySearchTree<int>::Iterator it = tree_copy.begin();
    BinarySearchTree<int>::Iterator it2 = tree.begin();

    ASSERT_TRUE(*it == *it2);
    ASSERT_TRUE(*++it == *(++it2));
    ASSERT_TRUE(*++it == *(++it2));
    ASSERT_TRUE(tree_copy.find(2) != tree.end());
}

TEST(test_inorder_empty){
    BinarySearchTree<int> tree;
    ostringstream oss;
    tree.traverse_inorder(oss);
    cout << "inorder" << endl;
    cout << oss.str() << endl << endl;
    ASSERT_TRUE(oss.str() == "");
}

TEST(test_inorder_one){
    BinarySearchTree<int> tree;
    tree.insert(3);
    ostringstream oss;
    tree.traverse_inorder(oss);
    cout << "inorder" << endl;
    cout << oss.str() << endl << endl;
    ASSERT_TRUE(oss.str() == "3 ");
}

TEST(test_inorder_twol){
    BinarySearchTree<int> tree;
    tree.insert(3);
    tree.insert(2);
    ostringstream oss;
    tree.traverse_inorder(oss);
    cout << "inorder" << endl;
    cout << oss.str() << endl << endl;
    ASSERT_TRUE(oss.str() == "2 3 ");
}

TEST(test_inorder_twor){
    BinarySearchTree<int> tree;
    tree.insert(3);
    tree.insert(5);
    ostringstream oss;
    tree.traverse_inorder(oss);
    cout << "inorder" << endl;
    cout << oss.str() << endl << endl;
    ASSERT_TRUE(oss.str() == "3 5 ");
}

TEST(test_inorder_three){
    BinarySearchTree<int> tree;
    tree.insert(3);
    tree.insert(5);
    tree.insert(1);
    ostringstream oss;
    tree.traverse_inorder(oss);
    cout << "inorder" << endl;
    cout << oss.str() << endl << endl;
    ASSERT_TRUE(oss.str() == "1 3 5 ");
}

TEST(test_inorder_four){
    BinarySearchTree<int> tree;
    tree.insert(3);
    tree.insert(5);
    tree.insert(1);
    tree.insert(2);
    ostringstream oss;
    tree.traverse_inorder(oss);
    cout << "inorder" << endl;
    cout << oss.str() << endl << endl;
    ASSERT_TRUE(oss.str() == "1 2 3 5 ");
}

TEST(test_inorder_five){
    BinarySearchTree<int> tree;
    tree.insert(3);
    tree.insert(5);
    tree.insert(1);
    tree.insert(2);
    tree.insert(4);
    ostringstream oss;
    tree.traverse_inorder(oss);
    cout << "inorder" << endl;
    cout << oss.str() << endl << endl;
    ASSERT_TRUE(oss.str() == "1 2 3 4 5 ");
}

TEST(test_preorder_empty){
    BinarySearchTree<int> tree;
    ostringstream oss;
    tree.traverse_preorder(oss);
    cout << "preorder" << endl;
    cout << oss.str() << endl << endl;
    ASSERT_TRUE(oss.str() == "");
}

TEST(test_preorder_one){
    BinarySearchTree<int> tree;
    tree.insert(3);
    ostringstream oss;
    tree.traverse_preorder(oss);
    cout << "preorder" << endl;
    cout << oss.str() << endl << endl;
    ASSERT_TRUE(oss.str() == "3 ");
}

TEST(test_preorder_twol){
    BinarySearchTree<int> tree;
    tree.insert(3);
    tree.insert(2);
    ostringstream oss;
    tree.traverse_preorder(oss);
    cout << "preorder" << endl;
    cout << oss.str() << endl << endl;
    ASSERT_TRUE(oss.str() == "3 2 ");
}

TEST(test_preorder_twor){
    BinarySearchTree<int> tree;
    tree.insert(3);
    tree.insert(5);
    ostringstream oss;
    tree.traverse_preorder(oss);
    cout << "preorder" << endl;
    cout << oss.str() << endl << endl;
    ASSERT_TRUE(oss.str() == "3 5 ");
}

TEST(test_preorder_three){
    BinarySearchTree<int> tree;
    tree.insert(3);
    tree.insert(5);
    tree.insert(1);
    ostringstream oss;
    tree.traverse_preorder(oss);
    cout << "preorder" << endl;
    cout << oss.str() << endl << endl;
    ASSERT_TRUE(oss.str() == "3 1 5 ");
}

TEST(test_preorder_four){
    BinarySearchTree<int> tree;
    tree.insert(3);
    tree.insert(5);
    tree.insert(1);
    tree.insert(2);
    ostringstream oss;
    tree.traverse_preorder(oss);
    cout << "preorder" << endl;
    cout << oss.str() << endl << endl;
    ASSERT_TRUE(oss.str() == "3 1 2 5 ");
}

TEST(test_preorder_five){
    BinarySearchTree<int> tree;
    tree.insert(3);
    tree.insert(5);
    tree.insert(1);
    tree.insert(2);
    tree.insert(4);
    ostringstream oss;
    tree.traverse_preorder(oss);
    cout << "preorder" << endl;
    cout << oss.str() << endl << endl;
    ASSERT_TRUE(oss.str() == "3 1 2 5 4 ");
}

TEST(test_sortinginvariantf){
    BinarySearchTree<int> tree;
    tree.insert(1);
    tree.insert(0);
    // change first datum to 2, resulting in the first broken tree above
    *tree.begin() = 2;
    ASSERT_FALSE(tree.check_sorting_invariant());
}

TEST(test_sortinginvariantt){
    BinarySearchTree<int> tree;
    tree.insert(1);
    tree.insert(0);
    ASSERT_TRUE(tree.check_sorting_invariant());
}

TEST(test_max){
    BinarySearchTree<int> tree;
    tree.insert(1);
    tree.insert(0);
    ASSERT_EQUAL(*(tree.max_element()), 1);
}

TEST(test_min){
    BinarySearchTree<int> tree;
    tree.insert(1);
    tree.insert(0);
    tree.insert(-1);
    ASSERT_EQUAL(*(tree.min_element()), -1);
}

TEST(test_mingreaterthan){
    BinarySearchTree<int> tree;
    tree.insert(1);
    tree.insert(0);
    tree.insert(-1);
    BinarySearchTree<int>::Iterator it = tree.min_element();
    ASSERT_TRUE(*(tree.min_greater_than(*it)) == 0);
}

TEST(test_find1){
    BinarySearchTree<int> tree;
    tree.insert(1);
    tree.insert(0);
    tree.insert(-1);
    ASSERT_TRUE(tree.find(-1) != tree.end());
}

TEST(test_find2){
    BinarySearchTree<int> tree;
    tree.insert(2);
    tree.insert(1);
    ASSERT_TRUE(tree.find(0) == tree.end());
}

TEST(bst_public_test) {
  BinarySearchTree<int> tree;

  tree.insert(5);

  ASSERT_TRUE(tree.size() == 1);
  ASSERT_TRUE(tree.height() == 1);

  ASSERT_TRUE(tree.find(5) != tree.end());

  tree.insert(7);
  tree.insert(3);

  ASSERT_TRUE(tree.check_sorting_invariant());
  ASSERT_TRUE(*tree.max_element() == 7);
  ASSERT_TRUE(*tree.min_element() == 3);
  ASSERT_TRUE(*tree.min_greater_than(5) == 7);

  cout << "cout << tree.to_string()" << endl;
  cout << tree.to_string() << endl << endl;

  cout << "cout << tree" << endl << "(uses iterators)" << endl;
  cout << tree << endl << endl;

  ostringstream oss_preorder;
  tree.traverse_preorder(oss_preorder);
  cout << "preorder" << endl;
  cout << oss_preorder.str() << endl << endl;
  ASSERT_TRUE(oss_preorder.str() == "5 3 7 ");

  ostringstream oss_inorder;
  tree.traverse_inorder(oss_inorder);
  cout << "inorder" << endl;
  cout << oss_inorder.str() << endl << endl;
  ASSERT_TRUE(oss_inorder.str() == "3 5 7 ");
}

TEST_MAIN()
