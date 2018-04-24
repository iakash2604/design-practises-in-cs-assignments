#ifndef PVERTEX_H
#define PVERTEX_H

#include <vector>


using namespace std;

/*! A class for vertices*/
class PVertex
{
public:
	vector<float> coor; /*!< id and coordinates of point*/
	vector<int> rays; /*!< a vector for storing the edges with this vertex as endpoint*/
	vector<int> projid; /*!< a vector for storing the projection vertices*/ 
	PVertex(){
		
	}

};

#endif