// banker_algorithm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<vector>
#include<queue>
using namespace std;
queue<int> process;
int p;//process you want
int SAFETY(int row, int col, vector<vector<int>> &ALLOCATION, vector<vector<int>> &NEED, vector<int> &WORK,vector<bool>& FINISH)
{
	bool found = false;
	bool flag = true;
	int k = 0;
	while (1)
	{
		found = false;
		for (int i = 0; i < row; i++)
		{
			if (FINISH[i] == true)
				continue;
			for (int j = 0; j < col; j++)
			{
				if (NEED[i][j] <= WORK[j])
					k++;
				else
					break;
			}
			if (k == col)
			{
				for (int m = 0; m < col; m++)
					WORK[m] = ALLOCATION[i][m] + WORK[m];
				process.push(i);
				FINISH[i] = true;
				found = true;
			}
			k = 0;
		}
		if (found == false)
			break;
	}
	for (int i = 0; i < row; i++)
	{
		if (FINISH[i] == 0)
		{
			flag = false;
			break;
		}

	}
	if (flag)
		return 1;
	else
		return 0;
}
int main()
{
	while (1)
	{
		int row, col;
		int a;//flag to determine safe or not
		int choose;//to choose between safe or request
		bool check = true;
		cout << "Enter rows&columns" << endl;
		cin >> row >> col;
		vector<vector<int>> ALLOCATION(row, vector<int>(col));
		vector<vector<int>> MAX(row, vector<int>(col));
		vector<vector<int>>NEED(row, vector<int>(col));
		vector<int>AVAILABLE(col);
		vector<bool>FINISH(row);
		vector<int>REQUEST(col);
		cout << "ENTER ALLOCATION MATRIX" << endl;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
				cin >> ALLOCATION[i][j];
		}
		cout << "ENTER MAX MATRIX" << endl;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
				cin >> MAX[i][j];
		}
		cout << "ENTER AVAILABLE MATRIX" << endl;
		for (int i = 0; i < col; i++)
			cin >> AVAILABLE[i];
		cout << endl;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
				NEED[i][j] = MAX[i][j] - ALLOCATION[i][j];
		}
		cout << "Needed Matrix" << endl;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
				cout << NEED[i][j] << " ";
			cout << endl;
		}
		cout << "Choose which operation you want" << endl;
		cout << "1-Safety Algorithm" << endl;
		cout << "2-Request Algorithm" << endl;
		cin >> choose;
		if (choose == 1)
		{
			vector<int> WORK(AVAILABLE);
			for (int i = 0; i < row; i++)
				FINISH[i] = 0;
			a = SAFETY(row, col, ALLOCATION, NEED, WORK, FINISH);
			if (a)
			{
				cout << "Yes,Safe State <";
				for (int i = 0; i < row; i++)
				{
					cout << "P" << process.front();
					if (i < row - 1)
						cout << ",";
					process.pop();
				}
				cout << ">";
			}
			else
				cout << "NO";
		}
		else if (choose == 2)
		{
			cout << "Enter a process you need to request" << endl;
			cin >> p;
			cout << "Enter numbers you want to request" << endl;
			for (int i = 0; i < col; i++)
				cin >> REQUEST[i];
			for (int i = 0; i < col; i++)
			{
				if (REQUEST[i] > NEED[p][i])
				{
					check = false;
					break;
				}
			}
			if (!check)
			{
				cout << "ERROR REQUEST AS NEED GREATER THAN WORK ";
				return 0;
			}
			check = true;
			for (int i = 0; i < col; i++)
			{
				if (REQUEST[i] > AVAILABLE[i])
				{
					check = false;
					break;
				}
			}
			if (!check)
			{
				cout << "REQUESTS MORE THAN AVAILABLE,SO IT WILL BE NOT SAFE ";
				return 0;
			}
			for (int i = 0; i < col; i++)
				AVAILABLE[i] -= REQUEST[i];
			for (int i = 0; i < col; i++)
				ALLOCATION[p][i] += REQUEST[i];
			for (int i = 0; i < col; i++)
				NEED[p][i] -= REQUEST[i];
			vector<int> WORK(AVAILABLE);
			a = SAFETY(row, col, ALLOCATION, NEED, WORK, FINISH);
			if (a)
			{
				cout << "Yes request can be granted with safe state, Safe state <";
				cout << "P" << p << "req,";
				for (int i = 0; i < row; i++)
				{
					cout << "P" << process.front();
					if (i < row - 1)
						cout << ",";
					process.pop();
				}
				cout << ">";
			}
			else
				cout << "NO";
		}
		cout << endl;
	}
}




























































































































































































































































































































































































// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
