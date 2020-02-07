// Yusuf Pisan pisan@uw.edu
// 15 Jan 2018

// BST class
// Creates a BST to store values
// Uses Node which holds the Data
// Uses templates to store any type of Data
// binarysearchtreee.cpp file is included at the bottom of the .h file
// binarysearchtreee.cpp is part of the template, cannot be compiled separately

#ifndef BST_HPP
#define BST_HPP

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

using namespace std;

template<class T>
class BST {
  // display BST tree in a human-readable format
  friend ostream &operator<<(ostream &Out, const BST &Bst) {
    Bst.printSideways(Out, Bst.Root);
    Out << endl;
    Bst.printVertical(Out, Bst.Root);
    return Out;
  }

private:
  // Node for BST
  struct Node {
    T Data;
    struct Node *Left;
    struct Node *Right;
  };

  // refer to data type "struct Node" as Node
  using Node = struct Node;

  // root of the tree
  Node *Root{nullptr};

  // height of a Node, nullptr is 0, Root is 1, static, no access to 'this'
  static int getHeight(const Node *N) {
      if (N == nullptr) {
          return 0;
      } else {
          int height1 = getHeight(N->Left);
          int height2 = getHeight(N->Right);
          if(height1 > height2){
              return height1+1;
          }else{
              return height2+1;
          }
      }
  }

  /**
   * print tree sideways with root on left
                6
            2
                5
        0
                4
            1
                3
   */

  static ostream &printSideways(ostream &Out, const Node *Curr, int Level = 0) {
    const static char SP = ' ';
    const static int ReadabilitySpaces = 4;
    if (!Curr)
      return Out;
    printSideways(Out, Curr->Right, ++Level);
    Out << setfill(SP) << setw(Level * ReadabilitySpaces) << SP;
    Out << Curr->Data << endl;
    printSideways(Out, Curr->Left, Level);
    return Out;
  }

  static ostream &centeredPrint(ostream &Out, int Space,
                                const string &Str, char FillChar = ' ') {
    auto StrL = static_cast<int>(Str.length());
    int Extra = (Space - StrL) / 2;
    if (Extra > 0) {
      Out << setfill(FillChar) << setw(Extra + StrL) << Str;
      Out << setfill(FillChar) << setw(Space - Extra - StrL) << FillChar;
    } else {
      Out << setfill(FillChar) << setw(Space) << Str;
    }
    return Out;
  }

  /**
   * print tree with the root at top
   *
      _____0______
   __1___      __2___
  3     4     5     6
   *
  **/
  static ostream &printTreeLevel(ostream &Out, queue<const Node *> &Q,
                                 int Width, int Depth, int MaxDepth) {
    const static char SP = ' ';
    const static char UND = '_';
    int Nodes = 0;
    int MaxN = pow(2, Depth - 1);
    int SpaceForEachItem = Width * pow(2, MaxDepth - 1) / MaxN; // NOLINT
    string
        Bigspace = string(static_cast<uint64_t>(SpaceForEachItem / 4), SP);
    while (Nodes++ < MaxN) {
      const Node *Tp = Q.front();
      Node *TpL = nullptr;
      Node *TpR = nullptr;
      Q.pop();
      string Label = "N";
      if (Tp) {
        stringstream Ss;
        Ss << Tp->Data;
        Label = Ss.str();
        TpL = Tp->Left;
        TpR = Tp->Right;
      }
      char Filler = Depth == MaxDepth ? SP : UND;
      if (Depth == MaxDepth) {
        centeredPrint(Out, SpaceForEachItem, Label, Filler);
      } else {
        Out << Bigspace;
        centeredPrint(Out, SpaceForEachItem / 2, Label, Filler);
        Out << Bigspace;
        Q.push(TpL);
        Q.push(TpR);
      }
    }
    Out << endl;
    return Out;
  }

  // helper function for displaying tree sideways, works recursively
  static ostream &printVertical(ostream &Out, Node *Curr) {
    const static int WIDTH = 6;  // must be even
    if (!Curr)
      return Out << "[__]";
    // figure out the maximum depth which determines how wide the tree is
    int MaxDepth = getHeight(Curr);
    queue<const Node *> Q;
    Q.push(Curr);
    for (int Depth = 1; Depth <= MaxDepth; ++Depth) {
      printTreeLevel(Out, Q, WIDTH, Depth, MaxDepth);
    }
    return Out;
  }

public:
  // constructor, empty tree
  BST() {
    this->Root = nullptr;
  }

  // constructor, tree with root
  explicit BST(const T &RootItem) {
      Root->Data = RootItem;
      Root->Right = nullptr;
      Root->Left = nullptr;
  }

  // given an array of length n
  // create a tree to have all items in that array
  // with the minimum height (i.e. rebalance)
  // Assignment specification
  // NOLINTNEXTLINE
  BST(const T Arr[], int N) {
    Root = BSTFromArray(Arr,0,N-1);
  }

  //Array to BST helper method
    Node* BSTFromArray(const T Arr[],int start, int end){
      if (start > end){
          return nullptr;
      }
      int mid = (start + end)/2;
      Node *current = newNode(Arr[mid]);
      current->Left = BSTFromArray(Arr, start,mid - 1);
      current->Right = BSTFromArray(Arr, mid + 1, end);

      return current;
  }


    // copy constructor
  BST(const BST<T> &Bst) {
    Root = nullptr;
    copy(Bst.getRoot());
  }

  //copy constructor helper method
  void copy(Node* N){
      if(N){
            add(N->Data);
            copy(N->Left);
            copy(N->Right);
      }
  }


  // destructor
  virtual ~BST() {
      this->eraseBst();
  }

  //helper function for destructor
  void eraseBst(){
      eraseBstHelper(this->Root);
  }

//helper helper function for destructor
  void eraseBstHelper(Node* curr){
      if(curr != nullptr){
          eraseBstHelper(curr->Left);
          eraseBstHelper(curr->Right);
          delete curr;
          curr = nullptr;
      }
  }

  // true if no nodes in BST
  bool isEmpty() const {
    if(Root == nullptr){
        return true;
    }
    return false;
  }

  // 0 if empty, 1 if only root, otherwise
  // height of root is max height of subtrees + 1
  int getHeight() const {
    return getHeightHelper(Root);
  }

  int getHeightHelper(Node* curr){
      if(curr == nullptr){
          return 0;
      }else{
          int LeftDeep = getHeightHelper(curr->Left);
          int RightDeep = getHeightHelper(curr->Right);
          if(LeftDeep > RightDeep){
              return LeftDeep + 1;
          }else{
              return RightDeep + 1;
          }
      }
  }

  // Number of nodes in BST
  int numberOfNodes() const {
    return countHelper(Root);
  }

  //number of nodes helper method
  int countHelper(Node* current) const{
      int n = 0;
      if(current == nullptr){
          return 0;
      }
      n++;
      if(current->Left != nullptr)
      {
          n+=countHelper(current->Left);
      }
      if(current->Right != nullptr)
      {
          n+=countHelper(current->Right);
      }
      return n;
  }

  //create new node
  Node* newNode(const T &Item){
      Node* node = new Node;
      node->Data = Item;
      node->Left = nullptr;
      node->Right = nullptr;

      return node;
  }

  // add a new item, return true if successful
  bool add(const T &Item) {
    Root = addHelper(Root,Item);
    return true;
  }

  //add helper method
  Node* addHelper(Node* current, const T &Item){
      if(current == nullptr){
            return newNode(Item);
      }
      if(Item < current->Data){
          current->Left = addHelper(current->Left, Item);
      }else{
          current->Right = addHelper(current->Right, Item);
      }
      return current;
  }

  // remove item, return true if successful
  bool remove(const T &Item) {
    Root = removeHelper(Root, Item);
    return true;
  }

  //remove helper
  Node* removeHelper(Node* current, const T &Item){
      if (current == nullptr){
          return current;
      }if(Item < current->Data){
          current->Left = removeHelper(current->Left, Item);
      }else if (Item > current->Data){
          current->Right = removeHelper(current->Right, Item);
      }else{
          if (current->Left == nullptr){
              Node* temp = current->Right;
              free(current);
              return temp;
          }else if (current->Right == nullptr){
              Node* temp = current->Left;
              free(current);
              return temp;
          }
          Node* temp = minValueNode(current->Right);
          current->Data = temp->Data;
          current->Right = removeHelper(current->Right, temp->Data);
      }
      return current;
  }
//get minimum node of the tree given the root
    Node* minValueNode(Node* head)
    {
        Node* current = head;
        while (current && current->Left != nullptr)
            current = current->Left;

        return current;
    }

    // true if item is in BST
  bool contains(const T &Item) const {
    if(isEmpty()){
        return false;
    }
    Node* current = Root;
    while(current != nullptr){
        if(current->Data > Item){
            current = current->Left;
        }else if(current->Data < Item){
            current = current->Right;
        }else{
            return true;
        }
    }
    return false;

  }

  // inorder traversal: left-root-right
  // takes a function that takes a single parameter of type T
  void inOrderTraverse(void Visit(const T &Item)) const {
    inOrderHelper(Visit,Root);
  }

  //in order helper
  void inOrderHelper(void Visit(const T &Item),Node* current) const{
    if(current != nullptr){
        inOrderHelper(Visit, current->Left);
        T theItem = current->Data;
        Visit(theItem);
        inOrderHelper(Visit, current->Right);
    }
  }

  // preorder traversal: root-left-right
  void preOrderTraverse(void Visit(const T &Item)) const {
    preOrderHelper(Visit, Root);
  }

  //pre order helper
    void preOrderHelper(void Visit(const T &Item),Node* current) const{
        if(current != nullptr){
            T theItem = current->Data;
            Visit(theItem);
            preOrderHelper(Visit, current->Left);
            preOrderHelper(Visit, current->Right);
        }
    }



  // postorder traversal: left-right-root
  void postOrderTraverse(void Visit(const T &Item)) const {
    postOrderHelper(Visit, Root);
  }

  //post order helper
    void postOrderHelper(void Visit(const T &Item),Node* current) const{
        if(current != nullptr){
            postOrderHelper(Visit, current->Left);
            postOrderHelper(Visit, current->Right);
            T theItem = current->Data;
            Visit(theItem);
        }
    }

  // create dynamic array, copy all the items to the array
  // and then read the array to re-create this tree from scratch
  // so that resulting tree is balanced
  void rebalance() {
    Root = rebalanceHelper(Root);
  }

    //rebalance helper
    Node* rebalanceHelper(Node* current)
    {
        vector<Node *> nodes;
        storeBSTNodes(current, nodes);
        int n = nodes.size();
        return buildTreeHelper(nodes, 0, n-1);
    }

    //put nodes into vector to be converted into balanced bst
    void storeBSTNodes(Node* current, vector<Node*> &nodes)
    {
        if (current == nullptr){
            return;
        }
        storeBSTNodes(current->Left, nodes);
        nodes.push_back(current);
        storeBSTNodes(current->Right, nodes);
    }

    //Method to build new bst
    Node* buildTreeHelper(vector<Node*> &nodes, int start, int end)
    {
        if (start > end){
            return nullptr;
        }
        int mid = (start + end)/2;
        Node *current = nodes[mid];
        current->Left  = buildTreeHelper(nodes, start, mid-1);
        current->Right = buildTreeHelper(nodes, mid+1, end);
        return current;
    }

    // delete all nodes in tree
  void clear() {
    clearHelper(Root);
  }

  //delete node helper
  void clearHelper(Node* current){
      if (current == nullptr){
          return;
      }
      clearHelper(current->Left);
      clearHelper(current->Right);
      delete(current);
  }

  // trees are equal if they have the same structure
  // AND the same item values at all the nodes
  bool operator==(const BST<T> &Other) const {
    return equalHelper(Root, Other.getRoot());
  }

  //operator overload helper
  bool equalHelper(Node* Root1, Node* Root2) const{
      if (Root1 == nullptr && Root2 == nullptr)
          return true;

      /* 2. both non-empty -> compare them */
      if (Root1 != nullptr && Root2 != nullptr)
      {
          return (Root1->Data == Root2->Data && equalHelper(Root1->Left, Root2->Left) && equalHelper(Root1->Right, Root2->Right));
      }
      return false;
  }

  //get root
  Node* getRoot()const{
      return Root;
  }

  // not == to each other
  bool operator!=(const BST<T> &Other) const {
      return !equalHelper(Root, Other.getRoot());
  }
};

#endif  // BST_HPP
