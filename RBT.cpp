#include<iostream>
#include<fstream>
using namespace std;

//Ignore the commented sections (Code or Comment).

template<typename T>
class Stack
{
private:
	T * arr;
	int top;
	int size;

public:
	Stack()
	{
		arr = nullptr;
		top = -1;
		size = 0;
	}
	Stack(int size)
	{
		arr = new T[size];
		this->size = size;
		top = -1;
	}
	~Stack()
	{
		for (int i = 0; i < size; i++)
		{
			arr[i] = nullptr;
		}
		delete[]arr;

		//cout << "Stack Deleted Successfully!" << endl;
	}
	void push(T node)
	{
		top++;
		arr[top] = node;
	}
	void pop()
	{
		top--;
	}
	T Top()
	{
		return arr[top];
	}
	bool isEmpty()
	{
		if (top == -1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool isFull()
	{
		if (top == size - 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

struct Node
{
	int val;
	Node * leftChild;
	Node * rightChild;
	char color;

	Node()
	{
		val = -1;
		leftChild = nullptr;
		rightChild = nullptr;
		color = '\0';
	}
	Node(int value)
	{
		val = value;
		leftChild = nullptr;
		rightChild = nullptr;
		color = 'R';
	}
};

class RBT
{
private:
	int val;
	Node * leftChild;
	Node * rightChild;
	char color;
	Node * root;

	void preorder1(Node * start)
	{
		if (start != nullptr)
		{
			cout << start->val << "(" << start->color << ")-->";
			preorder1(start->leftChild);
			preorder1(start->rightChild);
		}
		else
		{
			return;
		}
	}
	void preorder2(Node * start)
	{
		if (start != nullptr)
		{
			cout << start->val << "(" << start->color << ")-->";
			preorder2(start->rightChild);
			preorder2(start->leftChild);
		}
		else
		{
			return;
		}
	}
	void inorder1(Node * start)
	{
		if (start != nullptr)
		{
			inorder1(start->leftChild);
			cout << start->val << "(" << start->color << ")-->";
			inorder1(start->rightChild);
		}
		else
		{
			return;
		}
	}
	void inorder2(Node * start)
	{
		if (start != nullptr)
		{
			inorder2(start->rightChild);
			cout << start->val << "(" << start->color << ")-->";
			inorder2(start->leftChild);
		}
		else
		{
			return;
		}
	}
	void postorder1(Node * start)
	{
		if (start != nullptr)
		{
			postorder1(start->leftChild);
			postorder1(start->rightChild);
			cout << start->val << "(" << start->color << ")-->";
		}
		else
		{
			return;
		}
	}
	void postorder2(Node * start)
	{
		if (start != nullptr)
		{
			postorder2(start->rightChild);
			postorder2(start->leftChild);
			cout << start->val << "(" << start->color << ")-->";
		}
		else
		{
			return;
		}
	}
	void deleteTree(Node * traversePoint)
	{
		if (traversePoint != nullptr)
		{
			return;
		}

		deleteTree(traversePoint->leftChild);
		deleteTree(traversePoint->rightChild);

		cout << "Deleted Node : " << traversePoint->val;
		delete traversePoint;
	}

public:
	RBT()
	{
		this->root = nullptr;
	}
	void insert(int value)
	{
		Stack<Node *> * stk = nullptr;
		stk = new Stack<Node *>(20);

		if (root == nullptr)
		{
			root = new Node(value);
			root->color = 'B';

			delete stk;
			return;
		}
		else
		{
			Node * parent = root;
			Node * child = root;

			while (value != parent->val && child != nullptr)
			{
				parent = child;

				if (value < parent->val)
				{
					child = parent->leftChild;
					stk->push(parent);
				}
				else if (value > parent->val)
				{
					child = parent->rightChild;
					stk->push(parent);
				}
			}

			if (value == parent->val)
			{
				cout << "Can't Add Repeated Value. Please Enter a Unique Value!" << endl;
				return;
			}
			else if (value < parent->val && child == nullptr)
			{
				parent->leftChild = new Node(value);
				child = parent->leftChild;
			}
			else if (value > parent->val && child == nullptr)
			{
				parent->rightChild = new Node(value);
				child = parent->rightChild;
			}

			if (child->color == 'R' && parent->color == 'R')
			{
				Node * Parent = stk->Top();
				stk->pop(); // poping out the recent Prev Node i.e the Parent which was in Stack we maybe needing the GrandParent for the next process
				Node * grandparent = stk->Top();
				stk->pop();

				if (grandparent->rightChild == nullptr && grandparent->leftChild != nullptr)
				{
					if (parent->rightChild != nullptr && parent->leftChild == nullptr)
					{
						parent->leftChild = new Node(parent->val);
						parent->val = child->val;
						delete child;
						child = nullptr;
						parent->rightChild = nullptr;
						child = parent->leftChild;

						if (grandparent->val == root->val)
						{
							root->leftChild = nullptr;
							root->color = 'R';
							parent->rightChild = root;
							root = parent;
							root->color = 'B';

							delete stk;
							return;
						}
						else
						{
							grandparent->rightChild = new Node(grandparent->val);
							grandparent->val = parent->val;
							parent->val = child->val;
							delete child;
							child = nullptr;
							parent->leftChild = nullptr;

							delete stk;
							return;
						}
					}
					else if (parent->leftChild != nullptr && parent->rightChild == nullptr)
					{
						if (grandparent->val == root->val)
						{
							root->leftChild = nullptr;
							root->color = 'R';
							parent->rightChild = root;
							root = parent;
							root->color = 'B';

							delete stk;
							return;
						}
						else
						{
							grandparent->rightChild = new Node(grandparent->val);
							grandparent->val = parent->val;
							parent->val = child->val;
							delete child;
							child = nullptr;
							parent->leftChild = nullptr;

							delete stk;
							return;
						}
					}
				}
				else if ((grandparent->leftChild != nullptr && grandparent->rightChild != nullptr) && (grandparent->rightChild->val != parent->val && grandparent->rightChild->color == 'R'))
				{
					grandparent->leftChild->color = grandparent->color;
					grandparent->rightChild->color = grandparent->color;

					if (grandparent->val == root->val)
					{
						grandparent->color = 'B';

						delete stk;
						return;
					}
					else
					{
						if (grandparent->color == 'R')
						{
							grandparent->color = 'B';
						}
						else
						{
							grandparent->color = 'R';
						}

						if (!stk->isEmpty())
						{
							Node * GGfather = stk->Top();
							stk->pop();

							if (!stk->isEmpty())
							{
								Node * forefather = stk->Top();
								stk->pop();

								if (grandparent->color == 'R' && GGfather->color == 'R')
								{
									if (forefather->val == root->val)
									{
										if (forefather->rightChild == nullptr || (forefather->rightChild != nullptr && forefather->rightChild->color == 'B'))
										{
											if (GGfather->rightChild == nullptr)
											{
												forefather->leftChild = nullptr;
												forefather->color = 'R';
												GGfather->rightChild = forefather;
												root = GGfather;
												root->color = 'B';

												delete stk;
												return;
											}
											else
											{
												/*Node * tempNode = new Node(GGfather->leftChild->val);
												tempNode->color = 'B';
												delete GGfather->leftChild;
												GGfather->leftChild = nullptr;*/

												forefather->color = 'R';
												forefather->leftChild = GGfather->rightChild;
												GGfather->rightChild = nullptr;
												GGfather->rightChild = forefather;
												root = GGfather;
												root->color = 'B';

												delete stk;
												return;
											}
										}
										else if (forefather->rightChild != nullptr && forefather->rightChild->color == 'R')
										{
											forefather->leftChild->color = forefather->color;
											forefather->rightChild->color = forefather->color;

											forefather->color = 'B';

											delete stk;
											return;
										}
									}
								}
							}
							else
							{
								delete stk;
								return;
							}
						}
						else
						{
							delete stk;
							return;
						}
					}
				}
				else if (grandparent->leftChild == nullptr && grandparent->rightChild != nullptr)
				{
					if (parent->leftChild != nullptr  && parent->rightChild == nullptr)
					{
						parent->rightChild = new Node(parent->val);
						parent->val = child->val;
						delete child;
						child = nullptr;
						parent->leftChild = nullptr;
						child = parent->rightChild;

						if (grandparent->val == root->val)
						{
							root->rightChild = nullptr;
							root->color = 'R';
							parent->leftChild = root;
							root = parent;
							root->color = 'B';

							delete stk;
							return;
						}
						else
						{
							grandparent->leftChild = new Node(grandparent->val);
							grandparent->val = parent->val;
							parent->val = child->val;
							delete child;
							child = nullptr;
							parent->rightChild = nullptr;

							delete stk;
							return;
						}
					}
					else if (parent->rightChild != nullptr && parent->leftChild == nullptr)
					{
						if (grandparent->val == root->val)
						{
							root->rightChild = nullptr;
							root->color = 'R';
							parent->leftChild = root;
							root = parent;
							root->color = 'B';

							delete stk;
							return;
						}
						else
						{
							grandparent->leftChild = new Node(grandparent->val);
							grandparent->val = parent->val;
							parent->val = child->val;
							delete child;
							child = nullptr;
							parent->rightChild = nullptr;

							delete stk;
							return;
						}
					}
				}
				else if ((grandparent->leftChild != nullptr && grandparent->rightChild != nullptr) && (grandparent->leftChild->val != parent->val && grandparent->leftChild->color == 'R'))
				{
					grandparent->leftChild->color = grandparent->color;
					grandparent->rightChild->color = grandparent->color;

					if (grandparent->val == root->val)
					{
						grandparent->color = 'B';

						delete stk;
						return;
					}
					else
					{
						if (grandparent->color == 'R')
						{
							grandparent->color = 'B';
						}
						else
						{
							grandparent->color = 'R';
						}
					}

					if (!stk->isEmpty())
					{
						Node * GGfather = stk->Top();
						stk->pop();

						if (!stk->isEmpty())
						{
							Node * forefather = stk->Top();
							stk->pop();

							if (grandparent->color == 'R' && GGfather->color == 'R')
							{
								if (forefather->val == root->val)
								{
									if (forefather->leftChild == nullptr || (forefather->leftChild != nullptr && forefather->leftChild->color == 'B'))
									{
										if (GGfather->leftChild == nullptr)
										{
											forefather->rightChild = nullptr;
											forefather->color = 'R';
											GGfather->leftChild = forefather;
											root = GGfather;
											root->color = 'B';

											delete stk;
											return;
										}
										else
										{
											/*Node * tempNode = new Node(GGfather->rightChild->val);
											tempNode->color = 'B';
											delete GGfather->rightChild;
											GGfather->rightChild = nullptr;*/

											forefather->color = 'R';
											forefather->rightChild = GGfather->leftChild;
											GGfather->leftChild = nullptr;
											GGfather->leftChild = forefather;
											root = GGfather;
											root->color = 'B';

											delete stk;
											return;
										}
									}
									else if (forefather->leftChild != nullptr && forefather->leftChild->color == 'R')
									{
										forefather->leftChild->color = forefather->color;
										forefather->rightChild->color = forefather->color;

										forefather->color = 'B';

										delete stk;
										return;
									}
								}
							}
						}
						else
						{
							delete stk;
							return;
						}
					}
					else
					{
						delete stk;
						return;
					}
				}
			}
			else
			{
				delete stk;
				return;
			}
		}
	}
	void search(int value)
	{
		if (root == nullptr)
		{
			cout << "Tree Doesn't Exisit , Kindly make one First!" << endl;
		}
		else
		{
			Node * traverseTrail = root;
			Node * traverseForward = root;

			while (value != traverseTrail->val && traverseForward != nullptr)
			{
				traverseTrail = traverseForward;

				if (value < traverseTrail->val)
				{
					traverseForward = traverseTrail->leftChild;
				}
				else if (value > traverseTrail->val)
				{
					traverseForward = traverseTrail->rightChild;
				}
			}

			if (value == traverseTrail->val)
			{
				cout << "Value FOUND!" << endl;
				return;
			}
			else
			{
				cout << "The Entered value was NOT FOUND!" << endl;
				return;
			}
		}
	}
	void preOrder1()
	{
		if (root == nullptr)
		{
			cout << "Tree Doesn't Exisit , Kindly make one First!" << endl;
		}
		else
		{
			cout << endl;
			this->preorder1(root);
			cout << endl << "Root Value : " << root->val << endl;
		}
	}
	void preOrder2()
	{
		if (root == nullptr)
		{
			cout << "Tree Doesn't Exisit , Kindly make one First!" << endl;
		}
		else
		{
			cout << endl;
			this->preorder2(root);
			cout << endl << "Root Value : " << root->val << endl;
		}
	}
	void inOrder1()
	{
		if (root == nullptr)
		{
			cout << "Tree Doesn't Exisit , Kindly make one First!" << endl;
		}
		else
		{
			cout << endl;
			this->inorder1(root);
			cout << endl << "Root Value : " << root->val << endl;
		}
	}
	void inOrder2()
	{
		if (root == nullptr)
		{
			cout << "Tree Doesn't Exisit , Kindly make one First!" << endl;
		}
		else
		{
			cout << endl;
			this->inorder2(root);
			cout << endl << "Root Value : " << root->val << endl;
		}
	}
	void postOrder1()
	{
		if (root == nullptr)
		{
			cout << "Tree Doesn't Exisit , Kindly make one First!" << endl;
		}
		else
		{
			cout << endl;
			this->postorder1(root);
			cout << endl << "Root Value : " << root->val << endl;
		}
	}
	void postOrder2()
	{
		if (root == nullptr)
		{
			cout << "Tree Doesn't Exisit , Kindly make one First!" << endl;
		}
		else
		{
			cout << endl;
			this->postorder2(root);
			cout << endl << "Root Value : " << root->val << endl;
		}
	}
	void deleteWholeTree()
	{
		if (root == nullptr)
		{
			cout << "Tree Doesn't Exisit , Kindly make one First!" << endl;
		}
		else
		{
			this->deleteTree(root);
			delete root;
			root = nullptr;
			cout << "Successfully Delete the Tree!" << endl;
		}
	}
	void findParent(int value)
	{
		if (root == nullptr)
		{
			cout << "Tree Doesn't Exisit , Kindly make one First!" << endl;
		}
		else
		{
			Node * parent = root;
			Node * child = root;

			while (value != child->val && child != nullptr)
			{
				parent = child;

				if (value < parent->val)
				{
					child = parent->leftChild;
				}
				else if (value > parent->val)
				{
					child = parent->rightChild;
				}
			}

			if (value == child->val)
			{
				if (value == root->val)
				{
					cout << "The value is of the (ROOT Node)" << endl;
					return;
				}
				else
				{
					cout << "The Parent of the Entered NODE is : " << parent->val << "(" << parent->color << ")" << endl;
					return;
				}
			}
			else if (child == nullptr)
			{
				cout << "The Node you Entered doesn't exisit!" << endl;
				return;
			}
		}
	}
};

int main()
{
	RBT tree;

	int choice = 0;
	int value = 0;

	while (1)
	{
		system("cls");

		cout << "			MENU			" << endl << endl;
		cout << "1. Insert Value in Red-Black Tree!" << endl;
		cout << "2. Search (a) Value from Red-Black Tree!" << endl;
		cout << "3. for Pre-Order Traversal (NLR)!" << endl;
		cout << "4. for In-Order Traversal (LNR)!" << endl;
		cout << "5. for Post-Order Traversal (LRN)!" << endl;
		cout << "6. for Pre-Order Traversal-2 (NRL)!" << endl;
		cout << "7. for In-Order Traversal-2 (RNL)!" << endl;
		cout << "8. for Post-Order Traversal-2 (RLN)!" << endl;
		cout << "9. Destroy The Whole Tree (delete all nodes)!" << endl;
		cout << "10. Display the Parent of a Specific Node!" << endl;
		cout << "11. Create Red-Black Tree from the file (input.txt)!" << endl;
		cout << "12. EXIT!" << endl;

		cout << endl << "Enter Choice : ";
		cin >> choice;

		system("PAUSE");

		if (choice == 1)
		{
			system("cls");

			cout << "Enter Value to Enter in Tree : ";
			cin >> value;

			tree.insert(value);

			cout << "Successfull!" << endl;

			system("pause");
		}
		else if (choice == 2)
		{
			system("cls");

			cout << "Enter Value to Search : ";
			cin >> value;

			tree.search(value);

			system("pause");
		}
		else if (choice == 3)
		{
			system("cls");

			cout << "Pre-Order Traversal (NLR) : ";
			tree.preOrder1();

			system("pause");
		}
		else if (choice == 4)
		{
			system("cls");

			cout << "In-Order Traversal (LNR) : ";
			tree.inOrder1();

			system("pause");
		}
		else if (choice == 5)
		{
			system("cls");

			cout << "Post-Order Traversal (LRN) : ";
			tree.postOrder1();

			system("pause");
		}
		else if (choice == 6)
		{
			system("cls");

			cout << "Pre-Order Traversal-2 (NRL) : ";
			tree.preOrder2();

			system("pause");
		}
		else if (choice == 7)
		{
			system("cls");

			cout << "In-Order Traversal-2 (RNL) : ";
			tree.inOrder2();

			system("pause");
		}
		else if (choice == 8)
		{
			system("cls");

			cout << "Post-Order Traversal-2 (RLN) : ";
			tree.postOrder2();

			system("pause");
		}
		else if (choice == 9)
		{
			system("cls");

			tree.deleteWholeTree();

			system("pause");
		}
		else if (choice == 10)
		{
			system("cls");

			cout << "Enter the Value whose Parent you want : ";
			cin >> value;

			tree.findParent(value);

			system("pause");
		}
		else if (choice == 11)
		{
			system("cls");

			ifstream fin("input.txt");

			if (!fin.is_open())
			{
				cout << "Either the File is Empty or File NOT FOUND!" << endl;
			}
			else
			{
				while (fin >> value)
				{
					tree.insert(value);
				}

				cout << "Successfully Read the File Data and Made the Red-Black Tree!" << endl;

				fin.close();
			}

			system("pause");
		}
		else if (choice == 12)
		{
			system("cls");

			cout << "Programe Terminated!" << endl << "Thank You!" << endl;
			break;
		}
	}

	return 0;
}
