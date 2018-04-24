#ifndef PPLANE_H
#define PPLANE_H

#include <vector>
#include "PEdge.h"


using namespace std;

/*! A class for planar surfaces*/
class PPlane
{
public:
	int id; /*!< an integer value for id*/
	    /** Plane being represented as ax + by + cz + d = 0. 
     *  The values are given below 
     */
	vector<float> normalv; /*!< a vector for representing the normal to the plane*/
    vector<int> lines; /*!< a vector for storing the edges which form this plane*/

    PPlane(PEdge l1, PEdge l2, int id_1, int com){
    	id = id_1;
    	vector<float> pc;
    	vector<float> p1;
    	vector<float> p2;
    	if(com == 0){
    		for(int i = 1;i < 4;i++){
    			pc.push_back( l1.vert1.coor[i] );
    			p1.push_back( l1.vert2.coor[i] );
    			p2.push_back( l2.vert2.coor[i] );
    		}
    	}
    	if(com == 1){
    		for(int i = 1;i < 4;i++){
    			pc.push_back( l1.vert1.coor[i] );
    			p1.push_back( l1.vert2.coor[i] );
    			p2.push_back( l2.vert1.coor[i] );
    		}
    	}
    	if(com == 2){
    		for(int i = 1;i < 4;i++){
    			pc.push_back( l1.vert2.coor[i] );
    			p1.push_back( l1.vert1.coor[i] );
    			p2.push_back( l2.vert2.coor[i] );
    		}
    	}
    	if(com == 3){
    		for(int i = 1;i < 4;i++){
    			pc.push_back( l1.vert2.coor[i] );
    			p1.push_back( l1.vert1.coor[i] );
    			p2.push_back( l2.vert1.coor[i] );
    		}
    	}

    	normalv.push_back( (p1[1] - pc[1])*(p2[2] - pc[2]) - (p1[2] - pc[2])*(p2[1] - pc[1]) );
    	normalv.push_back( (p1[2] - pc[2])*(p2[0] - pc[0]) - (p1[0] - pc[0])*(p2[2] - pc[2]) );
    	normalv.push_back( (p1[0] - pc[0])*(p2[1] - pc[1]) - (p1[1] - pc[1])*(p2[0] - pc[0]) );
    	normalv.push_back( -1*( normalv[0]*pc[0] + normalv[1]*pc[1] + normalv[2]*pc[2] ) );
    	lines.push_back( l1.id );
    	lines.push_back( l2.id );

    } //!< constructor.


};

#endif