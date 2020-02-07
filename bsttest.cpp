/**
 * Testing BST - Binary Search Tree functions
 *
 * This file has series of tests for BST
 * Each test is independent and uses assert statements
 * Test functions are of the form
 *
 *      test_netidXX()
 *
 * where netid is UW netid and XX is the test number starting from 01
 *
 * Test functions can only use the public functions from BST
 * testBSTAll() is called from main in main.cpp
 * testBSTAll calls all other functions
 * @author Multiple
 * @date ongoing
 */

#include "bst.hpp"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>




using namespace std;

/**
 * Trying to avoid global variables,
 * by creating a singleton class with our visitor functions
 * stringstream SS contains the output from visitor
 */
class TreeVisitor {
public:
  // never create an instance of TreeVisitor object
  // we'll just use the static functions
  TreeVisitor() = delete;

  // insert output to SS rather than cout, so we can test it
  static stringstream SS;

  static string getSS() {
    return SS.str();
  }

  static void resetSS() {
    SS.str(string());
  }
  // instead of cout, insert item into a string stream
  static void visitor(const string &Item) {
    SS << Item;
  }

  // instead of cout, insert item into a string stream
  static void visitor(const int &Item) {
    SS << Item;
  }
};

// initialize the static variable
//  warning: initialization of 'SS' with static storage duration
//  may throw an exception that cannot be caught [cert-err58-cpp]
//  Not sure how to do it without making code harder to read
//  NOLINTNEXTLINE
stringstream TreeVisitor::SS;

/**
 * Test functions by Yusuf Pisan
 */

// Testing ==
void testPisan01() {
  cout << "Starting testPisan01" << endl;
  cout << "* Testing == and !=" << endl;
  BST<string> B1;
  BST<string> B2;
  BST<string> B3;
  // == and != for empty trees
  assert(B1 == B2 && (!(B1 != B2)));
  B1.add("c");
  B2.add("c");
  B3.add("b");
  // == and !- for 1-Node trees B1, B2, B3
  assert(B1 == B2 && (!(B1 != B2)));
  assert(B1 != B3 && (!(B1 == B3)));
  cout << "Ending testPisan01" << endl;
}

// Testing == in detail
void testPisan02() {
  cout << "Starting testPisan02" << endl;
  cout << "* Testing == and != with more detail" << endl;
  BST<string> B1;
  BST<string> B2;
  BST<string> B3;
  for (auto &S : vector<string>{"c", "a", "f", "g", "x"})
    B1.add(S);

  for (auto &S : vector<string>{"c", "f", "a", "g", "x"})
    B2.add(S);

  B3.add("b");

  cout << "1" << endl;
  // == for 5-Node trees B1, B2
  assert(B1 == B2 && (!(B1 != B2)));

    cout << "2" << endl;
  BST<string> B4(B3);
  // copy constructor for 1-Node trees B3, B4
  assert(B3 == B4 && (!(B3 != B4)));

    cout << "3" << endl;
  BST<string> B5(B1);
  // copy constructor for 5-Node trees B1, B5
  assert(B1 == B5 && (!(B5 != B1)));

    cout << "4" << endl;
  BST<string> B7("b");
  // 1-param constructor for 1-Node trees B3, B7
  assert(B3 == B7 && (!(B3 != B7)));

  cout << "Ending testPisan02" << endl;
}

// Testing traversal
void testPisan03() {
  cout << "Starting testPisan03" << endl;
  cout << "* Testing traversal" << endl;
  BST<string> B1;
  BST<string> B2;
  BST<string> B3;
  for (auto &S : vector<string>{"c", "a", "f", "g", "x"})
    B1.add(S);

  for (auto &S : vector<string>{"c", "f", "a", "g", "x"})
    B2.add(S);

  B3.add("b");

  TreeVisitor::resetSS();
  B1.inOrderTraverse(TreeVisitor::visitor);
  string Result = "acfgx";
  assert(TreeVisitor::getSS() == Result);

  TreeVisitor::resetSS();
  B1.preOrderTraverse(TreeVisitor::visitor);
  Result = "cafgx";
  assert(TreeVisitor::getSS() == Result);

  TreeVisitor::resetSS();
  B1.postOrderTraverse(TreeVisitor::visitor);
  Result = "axgfc";
  assert(TreeVisitor::getSS() == Result);

  cout << "Visual check B1:" << endl;
  cout << B1 << endl;
  cout << "Ending testPisan03" << endl;
}

/**
 * Test functions by Sample Sample
 */

// Testing samplefunctionality
void testSample01() {
  cout << "Starting custom testing" << endl;
  // assert(true);//false = 0 , true = 1
    
    //int nums[5] = {1,2,3,4,5};
    //BST<int> B1(nums,5);
    
    BST<int> B2;
    B2.add(3);
    B2.add(5);
    B2.add(1);
    B2.add(2);
    B2.add(7);

    BST<int> B1;
    B1.add(1);
    B1.add(2);
    B1.add(3);
    B1.add(4);
    B1.add(5);
    B1.add(6);
    B1.add(7);

    BST<string> B3;
    B3.add("a");
    B3.add("b");
    B3.add("c");
    B3.add("d");
    B3.add("e");
    B3.add("f");
    B3.add("g");

    cout << "Testing if BST is Empty: " <<B2.isEmpty() << endl;
    cout << B2 << endl;

    TreeVisitor::resetSS();
    B2.inOrderTraverse(TreeVisitor::visitor);
    string Result = "12357";
    cout << "ss is: " << TreeVisitor::getSS() << endl;
    assert(TreeVisitor::getSS() == Result);

    //cout << "bst has this many nodes: " << B2.numberOfNodes() << endl;

    cout << "Testing Degenerate BST rebalance" << endl;
    B1.rebalance();
    cout << B1 << endl;

    cout << "Testing Array to Bst constructor" << endl;
    int nums[5] = {1,2,3,4,5};
    BST<int> B4(nums,5);
    cout << B4 << endl;

    cout << "Testing Rebalance with strings" << endl;
    B3.rebalance();
    cout << B3 << endl;

    BST<string> B5(B3);
    cout << "Testing Copy Constructor" << endl;
    cout << B5 << endl;

    //cout << "does bst contain 5" << B2.contains(5) << endl;
  cout << "Ending custom testing" << endl;
}

// Calling all test functions
void testBSTAll() {
  testPisan01();
  //testPisan02();
  testPisan03();
  testSample01();
}
