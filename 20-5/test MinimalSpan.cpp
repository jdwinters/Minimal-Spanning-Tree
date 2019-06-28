#include <iostream>
#include "minimalSpanTreeType.h"

using namespace std;
 
int main()  
{
	msTreeType spanTree(50);

	cout << "********* Using Prim2 Algorithm *********" <<endl;

	spanTree.createSpanningGraph();
	spanTree.prim2(0);
	spanTree.printTreeAndWeight();
	
	system ("Pause");
	return 0;
	
}