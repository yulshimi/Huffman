//Name: Phillip Jo, San Kang
//Date: 02/22/2017/Wed
//Overview: This is the implementation of "HCTree.h". Some new functions are added.
//Assignment#: PA3

#include "HCTree.h"
#include <vector>
#include <queue>
using namespace std;

//This function builds Huffman Coding Tree based on a vector
void HCTree::build(const vector<int>& freqs)
{
  buildLeaves(freqs);
  priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> myQueue;
  for(int i=0; i < leaves.size(); ++i)
  {
    if(leaves[i] != nullptr)
    {
      myQueue.push(leaves[i]);
    }
  }
  if(myQueue.size() < 2)
  {
    HCNode* nodePtr;
    HCNode* newNodePtr = new HCNode();
    nodePtr = myQueue.top();
    newNodePtr->c0 = nodePtr;
    nodePtr->p = newNodePtr;
    newNodePtr->count = nodePtr->count;
    myQueue.pop();
    myQueue.push(newNodePtr);
    ++numOfBit;
  }
  while(1 < myQueue.size())
  {
    HCNode* firstPtr;
    HCNode* secondPtr;
    HCNode* newNodePtr = new HCNode();
    firstPtr = myQueue.top();
    myQueue.pop();
    secondPtr = myQueue.top();
    myQueue.pop();
    newNodePtr->c0 = firstPtr;
    newNodePtr->c1 = secondPtr;
    newNodePtr->count = firstPtr->count + secondPtr->count;
    firstPtr->p = newNodePtr;
    secondPtr->p = newNodePtr;
    myQueue.push(newNodePtr);
    numOfBit = numOfBit + 2;
  }
  if(0 < myQueue.size())
  {
    root = myQueue.top();
  }    
}

//This function is called in "uncompress.cpp"
//This function builds Huffman Coding Tree based on a header in an encoded file
//Huffman Coding Tree is built without frequencies
void HCTree::build(int numOfBits, BitInputStream& ins)
{
  HCNode* nodePtr = new HCNode();
  HCNode* newNodePtr = nullptr;
  root = nodePtr;
  for(int i=0; i < numOfBits; ++i)
  {
    newNodePtr = new HCNode();
    if(ins.readBit() == 0)
    {
      nodePtr->c0 = newNodePtr;
      newNodePtr->p = nodePtr;
      nodePtr = nodePtr->c0;     
    }     
    else
    {
      nodePtr = nodePtr->p;
      while(nodePtr->c1 != nullptr)
      {
        nodePtr = nodePtr->p;
      }
      nodePtr->c1 = newNodePtr;
      newNodePtr->p = nodePtr;
      nodePtr = nodePtr->c1;  
    }
  }
}

int HCTree::getNumOfBit() const
{
  return numOfBit;
}

//This function builds leaves based on a vector
void HCTree::buildLeaves(const vector<int>& freqs)
{
  for(int i=0; i < freqs.size(); ++i)
  {
    if(0 < freqs[i])
    {
      leaves[i] = new HCNode();
      leaves[i]->count = freqs[i];
      leaves[i]->symbol = (char)i;
    }
  }
}

void HCTree::encode(byte symbol, ofstream& out) const
{
  stack<char> myStack;
  HCNode* searchPtr = leaves[(int)symbol];
  while(searchPtr->p != nullptr)
  {
    if(searchPtr == searchPtr->p->c0)
    {
      myStack.push('0');
      searchPtr = searchPtr->p;  
    }
    else
    {
      myStack.push('1');
      searchPtr = searchPtr->p;
    }
  }
  char myChar;
  while(!myStack.empty())
  {
    myChar = myStack.top();
    out << myChar;
    myStack.pop();  
  }
}

void HCTree::encode(byte symbol, BitOutputStream& out) const
{ 
  stack<char> myStack;
  HCNode* searchPtr = leaves[(int)symbol];
  while(searchPtr->p != nullptr)
  { 
    if(searchPtr == searchPtr->p->c0)
    { 
      myStack.push('0');
    }
    else
    { 
      myStack.push('1');
    }
    searchPtr = searchPtr->p;
  }
  char myChar;
  while(!myStack.empty())
  { 
    myChar = myStack.top();
    if(myChar == '0')
    {
      out.writeBit(0);  
    }
    else
    {
      out.writeBit(1);
    }
    myStack.pop();
  }
}


bool HCTree::isItLeaf(HCNode* leafPtr) const
{
  return leafPtr->c0 == nullptr && leafPtr->c1 == nullptr;
}

int HCTree::decode(ifstream& in) const
{
  HCNode* searchPtr = root;
  if(searchPtr == nullptr)
  {
    return 0;
  }
  char myChar;
  while(!isItLeaf(searchPtr))
  {
    myChar = (unsigned char)in.get();
    if(myChar == '0')
    {
      searchPtr = searchPtr->c0;
    }  
    else if(myChar == '1')
    {
      searchPtr = searchPtr->c1;
    }
    else
    {
      break;
    }
  }
  return (int)searchPtr->symbol;  
}

HCNode* HCTree::getRoot() const
{
  return root;
}

int HCTree::decode(BitInputStream& in) const
{
  HCNode* searchPtr = root;
  int myInt;
  while(!isItLeaf(searchPtr))
  {
    cout << "While";
    myInt = in.readBit();
    if(myInt == 0)
    {
      searchPtr = searchPtr->c0;
    }
    else if(myInt == 1)
    {
      searchPtr = searchPtr->c1;
    }
    else
    {
      break;
    }
  }
  return (int)searchPtr->symbol;
}

//This function sends a structure of Huffman Coding Tree to an encoded file
void HCTree::sendToTheFile(HCNode* nodePtr, BitOutputStream& out) const
{
  if(nodePtr->c0 != nullptr)
  {
    out.writeBit(0);
    sendToTheFile(nodePtr->c0, out);
  }
  
  if(nodePtr->c1 != nullptr)
  {
    out.writeBit(1);
    sendToTheFile(nodePtr->c1, out);
  }
}

//This function is to test whether Huffman Coding Tree is correctly constructed or not
//in "uncompress.cpp". This was used for debugging.
void HCTree::treeTest(HCNode* nodePtr) const
{
  if(nodePtr->c0 != nullptr)
  {
    cout << "0" << endl;
    treeTest(nodePtr->c0);
  }
  
  if(nodePtr->c1 != nullptr)
  {
    cout << "1" << endl;
    treeTest(nodePtr->c1);
  }
  cout << "symbol: " << (int)nodePtr->symbol << endl;
}

//This function writes values of symbols in leaves in a header in an encoded file
void HCTree::sendSymbolToTheFile(HCNode* nodePtr, ostream& out) const
{
  if(nodePtr != nullptr)
  {
    sendSymbolToTheFile(nodePtr->c0, out);
    sendSymbolToTheFile(nodePtr->c1, out);
    if(isItLeaf(nodePtr))
    {
      out.put(nodePtr->symbol);  
    }
  }
}

//This function assigns appropriate symbols to leaves of Huffman Coding Tree
//It is used to rebuild Huffman Coding Tree
void HCTree::writeSymbol(HCNode* nodePtr, istream& ins)
{
  if(nodePtr != nullptr)
  {
    writeSymbol(nodePtr->c0, ins);
    writeSymbol(nodePtr->c1, ins);
    if(isItLeaf(nodePtr))
    {
      unsigned char in_symbol = ins.get();
      nodePtr->symbol = in_symbol;
    } 
  }  
}

void HCTree::deleteAll(HCNode* deletePtr)
{
  if(deletePtr != nullptr)
  {
    deleteAll(deletePtr->c0);
    deleteAll(deletePtr->c1);
    delete deletePtr;
  }
}

HCTree::~HCTree()
{
  deleteAll(root);
}


















































