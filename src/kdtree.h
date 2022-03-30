/* \author Aaron Brown */
// Quiz on implementing kd tree

#include "./render/render.h"


// Structure to represent node of kd tree
using namespace std;
struct Node
{
	std::vector<float> point;
	int id;
	Node* left;
	Node* right;

	Node(std::vector<float> arr, int setId)
	:	point(arr), id(setId), left(NULL), right(NULL)
	{}
};

struct KdTree
{
	Node* root;

	KdTree()
	: root(NULL)
	{}

	void insertHelper(Node** node,uint depth, std::vector<float> point, int id)
	{
		if (*node==NULL)
		   *node = new Node(point,id);
		else
		{
			uint cd=depth%3;
			if(point[cd]<((*node)->point[cd]))
				insertHelper(&((*node)->left),depth+1,point,id);
			else
				insertHelper(&((*node)->right),depth+1,point,id);
			
		}
		
	}

	void insert(std::vector<float> point, int id)
	{
		// TODO: Fill in this function to insert a new point into the tree
		// the function should create a new node and place correctly with in the root 
		insertHelper(&root,0,point,id);

	}

	void searchHelper(std::vector<float> target, Node* node, int depth, float distanceTol, std::vector<int>& ids)
	{
		//cout<<"depth "<<depth<<endl;

		if(node!=NULL)
		{   //cout<<"node is not NULL"<<endl;
			//cout<<"node point[0]="<<node->point[0]<<endl;
     		//cout<<"node point[1]="<<node->point[1]<<endl;
			if((node->point[0]>=(target[0]-distanceTol)&&node->point[0]<=(target[0]+distanceTol))&&(node->point[1]>=(target[1]-distanceTol)&&node->point[1]<=(target[1]+distanceTol))&&(node->point[2]>=(target[2]-distanceTol)&&node->point[2]<=(target[2]+distanceTol)))
			{  //cout<<"target is near this node"<<endl;
			   float distance=sqrt((node->point[0]-target[0])*(node->point[0]-target[0])+(node->point[1]-target[1])*(node->point[1]-target[1])+(node->point[2]-target[2])*(node->point[2]-target[2]));
			   if(distance<=distanceTol)
			       {//cout<<"found and confirmed the nearest node"<<endl;
				   ids.push_back(node->id);}
			}

		

		// check accross boundary
			if((target[depth%3]-distanceTol)<node->point[depth%3])
				{ //cout<<"go to left tree"<<endl;
		    	searchHelper(target,node->left,depth+1,distanceTol,ids);}
			if((target[depth%3]+distanceTol)>node->point[depth%3])
		    	{   //cout<<"go to right tree"<<endl;
				searchHelper(target,node->right,depth+1,distanceTol,ids);}
		}

	}

	// return a list of point ids in the tree that are within distance of target
	std::vector<int> search(std::vector<float> target, float distanceTol)
	{
		std::vector<int> ids;
		//cout<<"target[0]"<<target[0]<<endl;
		//cout<<"target[1]"<<target[1]<<endl;
		//cout<<"distanceTol"<<distanceTol<<endl;
		searchHelper(target,root,0,distanceTol,ids);

		return ids;
	}
	

};




