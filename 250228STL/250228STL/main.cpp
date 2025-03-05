#include <iostream>

using namespace std;

struct Node
{
	int iData;
	Node* pLeft;
	Node* pRight;
};
Node* Root;

void Init_Tree(int _iData)
{
	Root = nullptr;
	Root = new Node;
	Root->iData = _iData;
}
Node* AddChild(Node* _Parent, int _iData, bool _bLeft)
{
	Node* New;
	New = new Node;
	New->iData = _iData;
	New->pLeft = nullptr;
	New->pRight = nullptr;
	if (_bLeft)
		_Parent->pLeft = New;
	else
		_Parent->pRight = New;
	return New;
}
void PreOrder(Node* R)
{
	cout << R->iData << " ";
	if (R->pLeft)PreOrder(R->pLeft);
	if (R->pRight)PreOrder(R->pRight);
}
void InOrder(Node* R)
{
	if (R->pLeft)InOrder(R->pLeft);
	cout << R->iData << " ";
	if (R->pRight)InOrder(R->pRight);
}
int main()
{
	Node* Left;
	Node* Right;

	Init_Tree(1);
	Left = AddChild(Root, 2, true);
	Right = AddChild(Root, 3, false);
	AddChild(Left, 4, true);
	AddChild(Left, 5, false);
	AddChild(Right, 6, true);

	PreOrder(Root);
	cout << '\n';
	InOrder(Root);
	cout << '\n';
	return 0;
}