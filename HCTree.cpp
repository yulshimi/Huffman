#include "HCTree.h"
#include <vector>
#include <queue>
using namespace std;

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
  }
  if(0 < myQueue.size())
  {
    root = myQueue.top();
  }    
}

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


















































