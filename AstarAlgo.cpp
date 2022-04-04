#include<iostream>
#include<math.h>
#include<list>
#include<cmath>
using namespace std;
#define INFINITE 10000
#define VAL 200		//To distinguish path travelled from actual grid (It can take any value apart from 0 and 1)
#define GRIDSIZE_X 10
#define GRIDSIZE_Y 10

//float h(int ,int ,int ,int );
//float g(int ,int );
float g12(int curx,int cury);
//float g13(int curx,int cury);
//float f(int ,int );

class node
{
	public:
	float f;	//Evaluation function f(n) = g(n) + h(n)
	float g;	//Distance till now from source to current node i.e. Actual operating cost having been already traversed or cost from start
	float h; 	//It is heuristics : calculates distance from destination to current node i.e. Information used to find the promising node to traverse or estimate of cost to goal
	int x,y;	//Current node coordinates
	int px,py;	//saves previous node coordinates/ predecessors' co-ordinates 
				
	node *next;

};

int find1(node *temp);
void remove1(node *temp);
node *min();
node *findpnode(int px,int py);

//OPen list contains nodes for expansion
list <node> open1;

//close list contains nodes nodes which we have explored
list <node> close1;

int srcx1,srcy1;
int desx1,desy1;


float g12(int curx,int cury)
{

	list<node>::iterator i = close1.end();

	if(!(curx == desx1 && cury == desy1))
	{
		float g = (i->f) - (sqrt(pow(i->x - desx1, 2) + pow(i->y - desy1, 2)));
		g = g + sqrt(pow(curx - i->x, 2) + pow(cury - i->y, 2));
		return g;
	}
	else
	{
		return (sqrt( pow(srcx1 - i->x, 2) + pow(srcy1 - i->y, 2) ));
	}

}

//Find previous node
node *findpnode(int px,int py)
{
	list<node>::iterator i;
	node *temp=new node();

	for(i = close1.begin(); i != close1.end(); i++)
	{

		if(px == i->x && py == i->y)
		{
			temp->f = i->f;
			temp->x = i->x;
			temp->y = i->y;
			temp->px = i->px;
			temp->py = i->py;
			return temp;
			// break;
		}
	}

}

//Remove node from openlist
void remove1(node *temp)
{
	list<node>::iterator i;

	for(i = open1.begin(); i != open1.end(); i++)
	{
		if(temp->x == i->x && temp->y == i->y)
		{
			i->f = INFINITE;
			break;
		}
	}

}

//Check if particular node is in open list
int find1(node *temp)
{
	list<node>::iterator i;

	for(i = open1.begin(); i != open1.end(); i++)
	{
		if(temp->x == i->x && temp->y == i->y)
		{
			return 0;
		}
	}
	return 1;

}

//Find the minimum node from open list
node *min()
{
	list<node>::iterator i;
	float min1 = INFINITE;
	node *temp = new node();

	for(i = open1.begin(); i != open1.end(); i++)
	{

		if(i->f < min1 && (i->x != srcx1 || i->y != srcy1))
		{
			min1 = i->f;
			temp->f = min1;
			temp->x = i->x;
			temp->y = i->y;
			temp->py = i->py;
			temp->px = i->px;

		}
	}
	return temp;

}

int main()
{

	int a[GRIDSIZE_X][GRIDSIZE_Y];

	//Creating a basic obstacle grid
	// 0 represents obstacle free path
	// 1 represents obstacles in the 2D grid
	for(int i = 0;i < GRIDSIZE_X; i++)
	{
		for(int j = 0;j < GRIDSIZE_Y; j++)
		{
			a[i][j] = 0;

			if(j == 5 && i != 8 )
			{
				a[i][j] = 1;
			}

			if(j==3 && i != 1 )
			{
				a[i][j]=1;
			}

			if(j==7 && i!=1 )
			{
				a[i][j]=1;
			}
		}
	}

	//Show the grid
	for(int i = 0;i < GRIDSIZE_X; i++)
	{
		for(int j = 0;j < GRIDSIZE_Y; j++)
		{
			cout<<a[i][j]<<"\t";
		}
		cout<<endl;
	}


	node *src,*goal,*curr;
	src = new node();


	cout<<"Please provide Source co-ordinates (x,y)"<<endl;
	cin>>srcx1;
	cin>>srcy1;

	cout<<"Please provide Destination co-ordinates (x,y)"<<endl;
	cin>>desx1;
	cin>>desy1;


	src->f = 0;
	src->x = srcx1;
	src->y = srcy1;
	src->g = 0;


	goal = new node();
	//goal->f=0;
	goal->x = desx1;
	goal->y = desy1;

	curr=new node();

	close1.push_back(*src);
	curr=src;
	//curr->x!=goal->x && curr->y!=goal->y

	//Search optimaized path in forward direction i.e. ffrom source to destination
	while(!(curr->x == goal->x && curr->y == goal->y))
	{
		float g1 = g12(curr->x,curr->y);

		//Finding successors/neighbours of a particular cell in a grid(-1 0 1)
		for(int i = -1; i < 2; i++)
		{
			for(int j = -1; j < 2; j++)
			{
				//Successors co-ordinates
				int x = (curr->x) - i;
				int y = (curr->y) - j;
				
				//Boundary checking and checkif that cell is obstacle
				if(x < GRIDSIZE_X && y < GRIDSIZE_Y && x > -1 && y > -1 && (x != srcx1 || y != srcy1) && a[x][y] != 1)
				{
					node *temp1;
					temp1 = new node();
					
					temp1->x = x;
					temp1->y = y;

					temp1->px = x + i;
					temp1->py = y + j;

					if(find1(temp1))
					{ 
						//not already in open list
						temp1->g = g1 + sqrt((pow(curr->x - x,2) + pow(curr->y - y,2)));
						temp1->h = (sqrt(pow(temp1->x - desx1,2) + pow(temp1->y - desy1,2) ));
						temp1->f = temp1->g + temp1->h;

						//if not thecurrent node itself, then push it to the open list
						if(!(i == 0 && j == 0))
						{

							cout<<"\n---Push-------"<<endl;
							cout << temp1->f << '\t';
							cout <<temp1->x << '\t';
							cout << temp1->y << '\t';
							cout<<temp1->px;
							cout<<temp1->py;
							open1.push_back(*temp1);
						}
					}

					else
					{
						//if in open list-then update g, h, f values wrt current node
						if(temp1->g > g1 + sqrt((pow(curr->x - x, 2) + pow(curr->y - y, 2))))
						{
							temp1->g = g1 + sqrt((pow(curr->x - x, 2) + pow(curr->y - y, 2)));
							temp1->h = (sqrt(pow(temp1->x - desx1, 2) + pow(temp1->y - desy1, 2) ));
							temp1->f = temp1->g + temp1->h;
						}
					}
				}

			}
		}

		//Find minimum of all nodes in open list
		curr = min();
		cout<<"\n-----MIN-----"<<endl;
		cout << curr->f << '\t';
		cout <<curr->x << '\t';
		cout << curr->y << '\t';

		//Remove it from open list and add it to close list
		remove1(curr);
		close1.push_back(*curr);
		//i1++;

	}


	cout<<"\n----all visited nodes list------"<<endl;
	for(int i = 0; i < GRIDSIZE_X; i++)
	{
		for(int j = 0; j < GRIDSIZE_Y; j++)
		{
			cout<<a[i][j]<<"\t";
		}
		cout<<endl;
	}

	node *temp2;
	temp2 = new node();

	//Find previous node of destination node - path will be traced backwards from  destination
	temp2 = findpnode(desx1,desy1);;
	int i2 = VAL;
	
	//Keep on finding previous node until sorce node is reached
	while(!(temp2->x == srcx1 && temp2->y == srcy1))
	{
		cout<<"inside while";

		a[temp2->px][temp2->py] = i2;
		i2++;
		temp2 = findpnode(temp2->px, temp2->py);

		cout<<"x-----"<<temp2->x<<endl;
		cout<<"y ------"<<temp2->y<<endl;
		cout<<"px-----"<<temp2->px<<endl;
		cout<<"py ------"<<temp2->py<<endl;
	}

	cout<<"----final path------"<<endl;
	for(int i = 0; i < GRIDSIZE_X; i++)
	{
		for(int j = 0; j < GRIDSIZE_Y; j++)
		{
			cout<<a[i][j]<<"\t";
		}
		cout<<endl;
	}
	
	return 0;
} 

