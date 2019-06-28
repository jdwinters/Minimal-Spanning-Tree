#ifndef H_msTree
#define H_msTree 
 
#include <iostream>
#include <fstream>
#include <iomanip> 
#include <string>
#include <cfloat>
#include "graphType.h"

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
//* Program name    : minimalSpanTree                                                  * 
//*                                                                     * 
//* Written by      : Jonathan Winters, Audra Joslyn, Zachary Schunk, Gerry Francis                                      * 
//*                                                                     * 
//* Purpose         :    * 
//*                      * 
//*                      * 
//*                      * 
//*                                                                     * 
//* Inputs          : N/A    * 
//*                                                                     * 
//* Outputs         : Display of edges and their weights  * 
//*                                                                     * 
//* Calls           : Calls to functions of graphType and those declared below                     * 
//*                                                                     * 
//* Structure       : BEGIN                                             * 
//*                        Straight line code no sub-processes          * 
//*                   STOP                                              * 
//*                        End of Program                               * 
//*                                                                     * 
//*---------------------------------------------------------------------* 
//* Change Log:                                                         * 
//*                         Revision                                    * 
//*       Date    Changed  Rel Ver Mod Purpose                          * 
//* 05/10/16      jwinters 000.000.000 Initial release of program       * 
//*                                                                     * 
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

using namespace std;

class msTreeType: public graphType
{
public:
    void createSpanningGraph();
      //Function to create the graph and the weight matrix.
      //Postcondition: The graph using adjacency lists and 
      //               its weight matrix is created.

    void minimalSpanning(int sVertex);
      //Function to create a minimal spanning tree with
      //root as sVertex. 
      // Postcondition: A minimal spanning tree is created.
      //                The weight of the edges is also
      //                saved in the array edgeWeights.

    void printTreeAndWeight();
      //Function to output the edges of the minimal
      //spanning tree and the weight of the minimal
      //spanning tree.
      //Postcondition: The edges of a minimal spanning tree
      //               and their weights are printed.

	void prim2(int source);
	//Function to create a minimal spanning tree

    msTreeType(int size = 0); 
      //Constructor
      //Postcondition: gSize = 0; maxSize = size;
      //               graph is an array of pointers to linked
      //               lists.
      //               weights is a two-dimensional array to 
      //               store the weights of the edges.
      //               edges is an array to store the edges 
      //               of a minimal spanning tree.
      //               egdeWeight is an array to store the 
      //               weights of the edges of a minimal 
      //               spanning tree.

    ~msTreeType();
      //Destructor
      //The storage occupied by the vertices and the arrays
      //weights, edges, and edgeWeights is deallocated.

protected:
    int source;
    double **weights;
    int *edges;
    double *edgeWeights;
};
void msTreeType::createSpanningGraph()
{
	ifstream infile;
	double infinity = 31999;
	double nextWeight;
	int index;
	int vertex;
	int adjacentVertex;

		if (gSize != 0) 
			clearGraph();

	infile.open("Ch20_Ex5Data.txt");
	
	if (!infile)
	{
		cout << "Cannot Open Input File." <<endl;
		return;
	}

	infile >> gSize;	//Get the number of vertices

	for (index = 0; index < gSize; index++)
	{
		infile >> vertex;
		infile >> adjacentVertex;

		while (adjacentVertex != -999)
		{
			graph[vertex].insertLast(adjacentVertex);
			infile >> adjacentVertex;
		}//end while
	}//end for
	//-----------------Get the weights----------------------------
	for (int index = 0; index < gSize; index++)					// loop through the weight matrix, grab the weight corresponding to the edge, input the weight into weights[vertex][k]
		for(int j = 0; j <gSize; j++)
			weights[index][j] = infinity;
	infile >> vertex;
	while(infile)
	{
		infile >> adjacentVertex;								// inputs the first vertex of that root vertex

		while (adjacentVertex != -999)							// Continues grabbing the weights until the terminator is assigned to adjacentVertex
		{
			infile >> nextWeight;								//	gets the next weight
			weights[vertex][adjacentVertex] = nextWeight;		//  inputs the nth weights for the jth edge
			infile >> adjacentVertex;							//  gets the nth vertex
		}
		infile >> vertex;
	}
	//------------------------------------------------------------
	infile.close();
}//Does create the graph
 //			   v
 //		adjver{0, 1, 2, 3,
 //			   1, 0, 4, 6, 
 //			   2, 0, 5, 6 }
 //
void msTreeType::prim2(int sourceVert)
{
	double miniWeight;
	bool *visited;						// used to check if this node has been visited yet
	visited = new bool[gSize];			// 

	source = sourceVert;				// Store desired root into source
	//										  v
	//weights[vertex][adjacentVertex] = ajv { 6, 5, 2,
	//										  6, 2, 4,
	//										  5, 7, 5 }
	//
	//graph = { 0, 1, 2, 3,
	//			1, 0, 4, 6,
	//			2, 0, 5, 6 }
	//
	//edges ( i, j ) = ( edges[j], j )
	//
	//gSize = vertexes in graph
	//
	//edgeweights(0, 1) = weights[0][1] = 6
	//edgeweights(0, 2) = weights[0][2] = 5
	//edgeweights(0, 3) = weights[0][3] = 2
	//edgeweights(1, 0) - weights[1][0] = 6
	//edgeweights(1, 4) = weights[1][1] = 2
	//edgeweights(1, 6) = weights[1][2] = 4
	//edgeweights(2, 0) = weights[2][0] = 5
	//edgeweights(2, 5) = weights[2][1] = 7
	//edgeweights(2, 6) = weights[2][2] = 5
	
	for(int j = 0; j < gSize; j++)			// Needs editing in order to input the correct vertex for weights[vertex][j]; j being the other end of the edge if the edge was say from (0, 10) = weights [0][10]
	{
	edgeWeights[j] = weights[source][j];
	edges[j] = source;
	visited[j] = false;
	}

	edgeWeights[source] = 0; // 0 because it (source) can't have a weight between it and itself
	visited[source] = true;	 // source has been visited

	int k = 0; // basically the vertex, initialize
	int i = 0;

	while( i < gSize - 1 && k < gSize )
	{
		miniWeight;
		i++;

		if(!visited[k])
		{
			for(int j = 0; j < gSize; j++)
			{
				if(weights[k][j] < edgeWeights[j])
				{
				edgeWeights[j] = weights[k][j];
				edges[j] = k;
				visited[j] = true;
				}
			}
		}
		k++;
	}


	

	
}
void msTreeType::minimalSpanning(int sVertex)
{
    int startVertex, endVertex;
    double minWeight;

    source = sVertex;

    bool *mstv;
    mstv = new bool[gSize];

    for (int j = 0; j < gSize; j++)
    {
        mstv[j] = false;
        edges[j] = source;
        edgeWeights[j] = weights[source][j];
    }

    mstv[source] = true;
    edgeWeights[source] = 0;

    for (int i = 0; i < gSize - 1; i++)
    {
        minWeight = DBL_MAX;

        for (int j = 0; j < gSize; j++)
            if (mstv[j])
                for (int k = 0; k < gSize; k++)
                    if (!mstv[k] && weights[j][k] < minWeight)
                    {
                        endVertex = k;
                        startVertex = j;
                        minWeight = weights[j][k];
                    }

        mstv[endVertex] = true;
        edges[endVertex] = startVertex;
        edgeWeights[endVertex] = minWeight;
    } //end for
} //end minimalSpanning

void msTreeType::printTreeAndWeight()
{
    double treeWeight = 0;

    cout << "Source Vertex: " << source << endl;
    cout << "Edges    Weight" << endl;

    for (int j = 0; j < gSize; j++)
    {
        if (edges[j] != j)
        {
            treeWeight = treeWeight + edgeWeights[j];
            cout << "("<<edges[j] << ", " << j << ")    "
                 << edgeWeights[j] << endl;
        }
    }

    cout << endl;
    cout << "Minimal Spanning Tree Weight: " 
         << treeWeight << endl;
} //end printTreeAndWeight

    //Constructor
msTreeType::msTreeType(int size)
           :graphType(size)
{
    weights = new double*[size];

    for (int i = 0; i < size; i++)
        weights[i] = new double[size];

    edges  = new int[size];

    edgeWeights = new double[size];
}

    //Destructor
msTreeType::~msTreeType()
{
    for (int i = 0; i < gSize; i++)
       delete [] weights[i];

    delete [] weights;
    delete [] edges;
    delete edgeWeights;
}

#endif