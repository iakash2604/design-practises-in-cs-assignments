#ifndef PEDGE_H
#define PEDGE_H

#include "PVertex.h"

/*! A class for edges*/
class PEdge
{
public:
    int id; /*!< an integer value for id*/
    PVertex vert1; /*!< a PVertex for endpoint1*/
    PVertex vert2; /*!< a PVertex for endpoint2*/

    PEdge(PVertex p1, PVertex p2,int id_1){
        vert1 = p1;
        vert2 = p2;
        id = id_1;
    }//!< constructor.

};


#endif