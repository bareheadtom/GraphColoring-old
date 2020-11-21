// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<time.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
//初始化节点颜色
int* initialSolution(int* sol, int k, int n)
{
	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		if (i < k)
		{
			sol[i] = i;
		}
		else 
		{
			sol[i] = rand()%k;
		}
		cout << sol[i]<<" ";
		
	}
	sol[0] = 0;
	sol[2] = 0;
	sol[3] = 0;
	sol[1] = 1;
	sol[6] = 1;
	sol[7] = 1;
	sol[4] = 2;
	sol[5] = 2;
	sol[8] = 2;
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		cout << sol[i] << " ";

	}
	return sol;
}
//def initializeAdjacentColorTable(adjacent_Color_Table, edges, sol) :
//void initializeAdjacentColorTable(int *adjacent_Color_Table,)
//读取文件中的图
void readData(string fileUrl, vector<string>& edge, vector<vector<string>> &edges,int &n,int &e)
{
	ifstream infile;
	string line;
	string word;
	infile.open(fileUrl);
	if (!infile.is_open())//判断文件是否打开
	{
		std::cout << "Error opening file" << std::endl;
	}
	while (!infile.eof())
	{
		getline(infile, line);
		if (line != "") {
			//cout << line<<endl;
			stringstream stringin(line);
			edge.clear();
			while (stringin >> word)
			{
				edge.push_back(word);
			}
			if (edge[0] == "p") {
				n = stoi(edge[2]);
				e = stoi(edge[3]);

			}
			else 
			{
				edges.push_back(edge);
			}
			//cout << edge[0] << edge[1] << edge[2] << endl;
			//cout << edge[0] << endl;
			
		}

	}
}
//计算f值冲突数目
int calculateFValue(vector<vector<string>> &edges, int* sol)
{
	int f = 0;
	vector<string> edge;
	for (int i = 0; i < edges.size(); i++)
	{
		edge = edges[i];
		if (sol[stoi(edge[1]) - 1] == sol[stoi(edge[2]) - 1])
		{
			f += 1;
		}
	}
	return f;
}
//初始化邻接颜色表
void initializeAdjacentColorTable(int **Adjacent_Color_Table, vector<vector<string>> &edges, int *sol)
{
	for (int i = 0; i < edges.size(); i++)
	{
		int row = stoi(edges[i][1]) - 1;
		int col = sol[stoi(edges[i][2]) - 1];
		Adjacent_Color_Table[row][col] += 1;
		row = stoi(edges[i][2]) - 1;
		col = sol[stoi(edges[i][1]) - 1];
		Adjacent_Color_Table[row][col] += 1;
	}
}
//class Move
//{
//	private:
//		int from;
//		int to;
//	public:
//		Move(int i, int j) :from(i), to(j) {}
//		int getFrom() { return this->from; }
//		int getTo() { return this->to; }
//		void setFrom(int i) { this->from = i; }
//		void setTo(int j) { this->to = j; }
//};
class Move
{
public:
	int node;//node
	int color;//color
	Move(int i, int j) :node(i), color(j) {}
	void printFT() { cout << "node:" << node << " color:" << color << endl; }
};
int findMove(int **Adjacent_Color_Table, int *sol,int n,int k, int **TaBuTenureTable,int &node,int &color,int best_f,int f,int currIter)
{
	int delt = 99999;
	int tempDelt;
	int tabuDelt = 99999;
	int count = 0;
	int tabuCount = 0;
	int currColor;
	int *row_adjancent;
	int *row_tabu;
	int currColorAdjancentNum;
	vector<Move> equDeltMove;
	vector<Move> equTabuDeltMove;
	for (int i = 0; i < n; i++)
	{
		currColor = sol[i];
		row_adjancent = Adjacent_Color_Table[i];
		currColorAdjancentNum = row_adjancent[currColor];
		if (currColorAdjancentNum > 0)
		{
			row_tabu = TaBuTenureTable[i];
			for (int j = 0; j < k; j++)
			{
				if (currColor != j) 
				{
					tempDelt = row_adjancent[j] - currColorAdjancentNum;
					//cout << "node" << i <<" jcolor:"<<j<< "  tempDelt" << tempDelt << endl;
					//cout << "currIter" << currColor << " row_tabu[j]" << row_tabu[j] << endl;
					if (row_tabu[j] < currIter)
					{
						if (tempDelt < delt)
						{
							count = 0;
							delt = tempDelt;
							count++;
							equDeltMove.clear();
							Move move(i, j);
							equDeltMove.push_back(move);
						}
						else if(tempDelt == delt)
						{
							count++;
							Move move2(i, j);
							equDeltMove.push_back(move2);
						}
					}
					else
					{
						if (tempDelt < tabuDelt)
						{
							tabuCount = 0;
							tabuDelt = tempDelt;
							tabuCount++;
							equTabuDeltMove.clear();
							Move move(i, j);
							equTabuDeltMove.push_back(move);
						}
						else if(tempDelt == tabuDelt)
						{
							tabuCount++;
							Move move2(i, j);
							equTabuDeltMove.push_back(move2);
						}
					}
				}
			}
		}

	}
	tempDelt = 0;
	int randSelect = 0;
	cout << "equDeltMove " << endl;
	for (int i = 0; i < equDeltMove.size(); i++)
	{
		equDeltMove[i].printFT();
	}
	cout << "equTabuDeltMove " << endl;
	for (int i = 0; i < equTabuDeltMove.size(); i++)
	{
		equTabuDeltMove[i].printFT();
	}
	if (tabuDelt < best_f - f && tabuDelt < delt)
	{
		delt = tabuDelt;
		randSelect = rand() % tabuCount;
		node = equTabuDeltMove[randSelect].node;
		color = equTabuDeltMove[randSelect].color;
	}
	else
	{
		randSelect = rand() % count;
		node = equDeltMove[randSelect].node;
		color = equDeltMove[randSelect].color;
	}
	return delt;
}
//得到该节点的邻居节点
vector<int> getAdjacentVertices(int node, vector<vector<string>> &edges)
{
	vector<int> adjacentVertices;
	cout <<node << "adjacentVErtices:" << endl;
	for (int i = 0; i < edges.size(); i++)
	{
		if (stoi(edges[i][1]) == node)
		{
			adjacentVertices.push_back(stoi(edges[i][2]));
			cout << stoi(edges[i][2]) << " ";
		}
		else if (stoi(edges[i][2]) == node)
		{
			adjacentVertices.push_back(stoi(edges[i][1]));
			cout << stoi(edges[i][1]) << " ";
		}
	}
	return adjacentVertices;
}
void makeMove(int &f,int delt,int &best_f,int node,int color,int *sol, int **TaBuTenureTable,int currIter, int **Adjacent_Color_Table, vector<vector<string>> &edges)
{
	f = delt + f;
	if (f < best_f) { best_f = f; }
	vector<int> adjacentVertices;
	adjacentVertices = getAdjacentVertices(node + 1, edges);
	for (int i = 0; i < adjacentVertices.size(); i++)
	{
		//cout << "before Adjacent_Color_Table[adjacentVertices[i]-1][sol[node]]" << Adjacent_Color_Table[adjacentVertices[i] - 1][sol[node]] << "Adjacent_Color_Table[adjacentVertices[i] - 1][color]" << Adjacent_Color_Table[adjacentVertices[i] - 1][color] << endl;
		Adjacent_Color_Table[adjacentVertices[i] - 1][sol[node]] -= 1;
		Adjacent_Color_Table[adjacentVertices[i] - 1][color] += 1;
		//cout << "after Adjacent_Color_Table[adjacentVertices[i]-1][sol[node]]" << Adjacent_Color_Table[adjacentVertices[i] - 1][sol[node]] << "Adjacent_Color_Table[adjacentVertices[i] - 1][color]" << Adjacent_Color_Table[adjacentVertices[i] - 1][color] << endl;
	}
	int oldColor = sol[node];
	sol[node] = color;
	TaBuTenureTable[node][oldColor] = currIter + f + rand() % 10 + 1;
	


}

int main()
{
	int a[5];
	vector<string> edge;
	vector<vector<string>> edges;
	int  n = 0;
	int  e = 0;
	readData("./data/test.col",edge,edges,n,e);
	///infile.close();
	cout << "vector" << endl;
	//cout << edges[14][0]<<endl;

	cout << "size"<<edges.size() << endl;
	cout << "n " << n << "e " << e << endl;
	for (int i = 0; i < edges.size(); i++) {
		edge = edges[i];
		cout << edge[0]<<' ' << edge[1]<<' ' << edge[2] << endl;
		
	}
	int *sol;
	sol = new int[n];
	int k = 3;
	initialSolution(sol, 3, n);
	int f = calculateFValue(edges, sol);
	cout << "f " << f << endl;
    cout << "Hello World!\n";
	int best_f = f;
	int *bestSol = new int[n]();
	int **TaBuTenureTable = new int*[n];
	for (int i = 0; i < n; i++)
	{
		TaBuTenureTable[i] = new int[k]();
	}
	int **Adjacent_Color_Table = new int*[n];
	for (int i = 0; i < n; i++)
	{
		Adjacent_Color_Table[i] = new int[k]();
	}
	initializeAdjacentColorTable(Adjacent_Color_Table, edges, sol);
	cout << "Adjacent_Color_Table" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < k; j++) {
			cout << Adjacent_Color_Table[i][j] << " ";
		}
		cout << endl;
	}
	cout << "TaBuTenureTable" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < k; j++) {
			cout << TaBuTenureTable[i][j] << " ";
		}
		cout << endl;
	}
	int currIter = 0;
	int node = 0;
	int color = 0;
	cout << "f " << f << endl;

	while (f > 0)
	{
		int delt = 0;
		delt=findMove(Adjacent_Color_Table, sol, n, k, TaBuTenureTable, node, color, best_f, f, currIter);
		cout << "node:" << node << "  cuurColor:"<<sol[node]<<"   color:" << color << "   delt :"<<delt<<endl;
		makeMove(f, delt, best_f, node, color, sol, TaBuTenureTable, currIter, Adjacent_Color_Table, edges);
		currIter += 1;
		cout << " f" << f << endl;
	}
}


