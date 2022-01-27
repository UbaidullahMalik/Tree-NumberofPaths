#include<iostream>
#include<queue>
using namespace std;

template <class T>
struct Node
{
	T data;
	Node<T>* leftchild;
	Node<T>* rightchild;

	Node()
	{
		data = T();
		leftchild = NULL;
		rightchild = NULL;
	}
};

template <class T>
class Tree
{
private:
	Node<T>* root;
	int path;
	void paths(Node<T>* root, T value, T sum = T())
	{ 
		if (root != NULL)
		{
			sum = sum + root->data; //adding the previous value of sum and the data of curr node

			//if sum equals the value passed in the arguments the path increments
			if (sum == value)
			{
				path++;
			}

			//recursively calling the function for left and right child and the process repeats
			paths(root->leftchild, value, sum);
			paths(root->rightchild, value, sum);
		}
	}

public:
	Tree()//default constructor
	{
		root = NULL;
		path = -1;//setting the path value to -1 by default
	}
	void insert(T d)
	{
		queue<Node<T>*> Queue;
		if (root == NULL)
		{
			root = new Node<T>;
			root->data = d;
		}
		else
		{
			Queue.push(root);
			Node<T>* temp = NULL;

			while (true)
			{
				temp = Queue.front();
				Queue.pop();

				if (temp->leftchild == NULL)
				{
					temp->leftchild = new Node<T>;
					temp->leftchild->data = d;
					break;
				}
				else if (temp->rightchild == NULL)
				{
					temp->rightchild = new Node<T>;
					temp->rightchild->data = d;
					break;

				}
				else
				{
					Queue.push(temp->leftchild);
					Queue.push(temp->rightchild);
				}

			}

		}
	}
	void display()
	{
		queue<Node<T>*> Queue;
		if (root == NULL)
		{
			cout << "Tree doesn't exist" << endl;
			return;
		}
		else
		{
			Queue.push(root);
			Node<T>* temp = root;
			cout << temp->data << " ";

			while (true)
			{
				temp = Queue.front();
				Queue.pop();
				if (temp->leftchild != NULL)
				{
					cout << temp->leftchild->data << " ";
				}

				if (temp->rightchild != NULL)
				{
					cout << temp->rightchild->data << " ";

				}

				if (temp->leftchild != NULL && temp->rightchild != NULL)
				{

					Queue.push(temp->leftchild);
					Queue.push(temp->rightchild);
				}
				else
				{
					break;
				}

			}

		}
	}
	bool replace(T olditem, T newitem)
	{
		queue<Node<T>*> Queue;
		if (root == NULL)
		{
			cout << "Tree doesn't Exist" << endl;
			return false;
		}
		else
		{
			Queue.push(root);
			Node<T>* temp = root;
			if (temp->data == olditem)//root case;
			{
				temp->data = newitem;
				return true;
			}

			while (true)
			{
				temp = Queue.front();
				Queue.pop();

				if (temp->leftchild != NULL && temp->leftchild->data == olditem)
				{
					temp->leftchild->data = newitem;
					return true;
				}

				if (temp->rightchild != NULL && temp->rightchild->data == olditem)
				{
					temp->rightchild->data = newitem;
					return true;

				}

				if (temp->rightchild != NULL && temp->leftchild != NULL)
				{
					Queue.push(temp->leftchild);
					Queue.push(temp->rightchild);
				}
				else
				{
					return false;
				}

			}

		}
	}
	Node<T>* returnRoot()
	{
		return root;// getter for the root
	}
	void setpathvalue(int val)
	{
		path = val;
	}
	int no_of_paths(Node<T>* root, T value)
	{
		if (root==NULL)
		{
			cout << "Tree doesn't exist" << endl;
			return path;		//returns -1 if the tree doesn't exist
		}
		else
		{
			setpathvalue(0);//setting the value of path = 0
			queue<Node<T>*> Q1;		//traversal 

			Node<T>* temp = NULL; 

			Q1.push(root);	//pushing the root into the queue 

			while (!Q1.empty())//while the queue is not empty
			{
				temp = Q1.front();
				Q1.pop();

				paths(temp, value); //calculating path for curr node

				//pushing leftchild and rightchild if they exist
				if (temp->leftchild != NULL)
				{
					Q1.push(temp->leftchild);
				}

				if (temp->rightchild != NULL)
				{
					Q1.push(temp->rightchild);
				}
			}
			return path;
		}
		
	}
};

int main()
{
	Tree<int> T1;
	for (int i = 0; i < 7; i++)
	{
		T1.insert(i);
	}
	int path = T1.no_of_paths(T1.returnRoot(),8);
	cout<<"Number of paths for '8': " << path << endl;
	path = T1.no_of_paths(T1.returnRoot(),6);
	cout<<"Number of paths for '6': "<< path << endl;
	return 0;
}
