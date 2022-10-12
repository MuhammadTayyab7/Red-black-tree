#include"RBTree.h"
#include<fstream>
#include<iostream>
using namespace std;
void Menu();
void Readfile(RBTree<int>& obj);
int main()
{
	int value = 0;
	RBTree<int> obj;
	cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
	cout << "                                                                                                                        \n";
	cout << "                                                [ RED BLACK TREE ]\n";
	cout << "                                                                                                                        \n";
	cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n\n";
	int choice = 0;
	while (choice != 13)
	{
		Menu();
		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "=======================================================================================================================\n\n";
			obj.insert(1);
			obj.insert(9);
			obj.insert(10);
			/*obj.insert(11);
			obj.insert(8);
			obj.insert(12);*/
			/*obj.insert(10);
			obj.insert(10);*/
			cout << "Value is inserted...:)" << endl;
			break;
		case 2:
			cout << "=======================================================================================================================\n\n";
			int value;
			cout << "Enter value: ";
			cin >> value;
			obj.SearchByValue(value);
			cout << endl;
			break;
		case 3:
			cout << "=======================================================================================================================\n\n";
			cout << "Pre-order1 display(NLR):" << endl;
			obj.preorder1();
			cout << endl;
			break;
		case 4:
			cout << "=======================================================================================================================\n\n";
			cout << "Inorder1 display(LNR):" << endl;
			obj.inorder1();
			cout << endl;
			break;
		case 5:
			cout << "=======================================================================================================================\n\n";
			cout << "Post-order1 display(LRN):" << endl;
			obj.postorder1();
			cout << endl;
			break;
		case 6:
			cout << "=======================================================================================================================\n\n";
			cout << "Pre-order2 display(NRL):" << endl;
			obj.preorder2();
			cout << endl;
			break;
		case 7:
			cout << "=======================================================================================================================\n\n";
			cout << "Inorder2 display(RNL):" << endl;
			obj.inorder2();
			cout << endl;
			break;
		case 8:
			cout << "=======================================================================================================================\n\n";
			cout << "Post-order2 display(RLN):" << endl;
			obj.postorder2();
			cout << endl;
			break;
		case 9:
			cout << "=======================================================================================================================\n\n";
			cout << "Enter node to find parent: ";
			cin >> value;
			obj.FindParent(value);
			cout << endl;
			break;
		case 10:
			cout << "=======================================================================================================================\n\n";
			Readfile(obj);
			break;
		case 11:
			cout << "=======================================================================================================================\n\n";
			cout << "this is not possible to delete dublicate values in Red Black becuase (in BST we can not insert dublicate values)." << endl;
			break;
		case 12:
			cout << "=======================================================================================================================\n\n";
			obj.DestroyallTree();
			cout << "Tree destroyed..." << endl;
			break;
		case 13:
			cout << "=======================================================================================================================\n";
			cout << "						Bye Bye 4th semester...:)" << endl;
			cout << "						Exiting..........." << endl;
			cout << "=======================================================================================================================\n";
			break;
		default:
			cout << "Invalid choice...!" << endl;
		}
	}
	return 0;
}

void Menu()
{
	cout << "=======================================================================================================================\n\n";
	cout << "Press 1 to insert values in the tree(one by one)" << endl;
	cout << "Press 2 for searching a value from the tree" << endl;
	cout << "Press 3 for pre - order traversal NLR" << endl;
	cout << "Press 4 for in - order traversal LNR" << endl;
	cout << "Press 5 for post - order traversal LRN" << endl;
	cout << "Press 6 for pre - order traversal 2 NRL" << endl;
	cout << "Press 7 for in - order traversal 2 RNL" << endl;
	cout << "Press 8 for post - order traversal 2 RLN" << endl;
	cout << "Press 9 for displaying parent of a node present in Tree" << endl;
	cout << "Press 10 to read integer values from the file “input.txt” to create a red - black tree" << endl;
	cout << "Press 11 to delete all duplicate values from the tree" << endl;
	cout << "Press 12 to destroy the complete tree" << endl;
	cout << "Press 13 to EXIT" << endl;

}
void Readfile(RBTree<int>& obj)
{
	ofstream fout;
	ifstream fin;
	int data;
	fin.open("input.txt");
	if (!fin.is_open())
	{
		cout << "Error in opening file";
	}
	else
	{
		while (!fin.eof())
		{
			fin >> data;
			obj.insert(data);
		}
		cout << "Values from file insert successfully...:)" << endl;
	}
}