#ifndef FUNCKY_H
#define FUNCKY_H

#include "PVertex.h"
#include "PEdge.h"
#include "PPlane.h"
#include <vector>
#include <map>

using namespace std;

/*! PVertex part */

/*!<for taking the vertex input*/
vector<PVertex> PVReader(const char* s);

/*!<for printing vertices*/
void PVPrinter(vector<PVertex> pv);

/*!<for generating 3D probable vertices from 2 planes*/
vector<PVertex> GeneratePVertices2Planes(vector<PVertex> pv1, vector<PVertex> pv2, int axes);

/*!<for generating 3D probable vertices from 3 planes*/
vector<PVertex> GeneratePVertices(vector< vector<PVertex> > pv);

/*!<for cleaning 3D probable vertices list of duplicates*/
void CleanPVertices(vector<PVertex> &pc, vector< vector<PVertex> > &pv);

/*!<for comparision between two class objects*/
bool Compare( const PVertex& lhs, const PVertex& rhs );

/*!<for equating two classes*/
bool Equalise( const PVertex& lhs, const PVertex& rhs );

/*!<for checking whether projection or not*/
bool ProjCheck( PVertex pv, PVertex pp, int axis );

/*! PEdge part */


//for taking the Edge input from one plane
void PEReaderSmall(const char* s1, vector< map< pair<int, int>, int > > &peh, int axis);

//for taking the Edge input
void PEReader(const char* s1, const char* s2, const char* s3, vector< map< pair<int, int>, int > > &peh);


/*!<for generating 3D probable edges from 3D vertices, primary level, generating and testing for projection*/
vector<PEdge> GeneratePEdges1( vector<PVertex> &pv3d, vector< map< pair<int, int>, int > > pemap);

/*!<for generating 3D probable edges from 3D vertices, secondary level, removing colinear containment*/
void GeneratePEdges2(map<float, int> VertexAddr, vector<PVertex> &pv3d, vector<PEdge> &pedv);


/*!<for generating 3D probable edges from 3D vertices, teritiary level, removing fake vertices*/
vector<PEdge> GeneratePEdges3(vector< map< pair<int, int>, int > > pemap, vector<PVertex> &pv3d);

/*!<for checking colinear containment of line in another line*/
int ContainLine( PEdge pe1, PEdge pe2 );

/*!<for checking containment of a point on line*/
bool ContainPoint( PEdge pe1, PVertex pv1 );

/*!<for checking projection of line on single plane*/
bool ProjLinePlane( PVertex lhs, PVertex rhs, int axis,  vector< map< pair<int, int>, int > > pemap);

/*!<for checking projection of line on all planes*/
bool ProjLine( PVertex lhs, PVertex rhs, vector< map< pair<int, int>, int > > pemap);

/*!<for printing Edges*/
void PEPrinter(vector<PEdge> pedv);

/*!<to delete edge element for GeneratePEdges2 function*/
bool Delete(PEdge pe1);

/*!<to store the id and index relationship of elements in vertex vector and edge vector*/
void BuildOrReconfig(vector<PVertex> pv3d, map<float, int> &VertexAddr,int br );

/*!<to find the common vertex of 2 PEdges*/
int CommonVertex(PEdge pe1, PEdge pe2);

/*!<to know if a line is on a plane*/
int OnPlane(PEdge pe1, PPlane p1);

/*!<for generating 3D probable planes from 3D PEdges*/
vector<PPlane> GeneratePPlanes( vector<PVertex> pv3d );

/*
//for generating 3D probable vertices from 2 planes
vector<PVertex> GeneratePVertices2Planes(vector<PVertex> pv1, vector<PVertex> pv2, int axes);

//for generating 3D probable vertices from 3 planes
vector<PVertex> GeneratePVertices(vector<PVertex> pv1, vector<PVertex> pv2, vector<PVertex> pv3);

//for cleaning 3D probable vertices list of duplicates
vector<PVertex> CleanPVertices(vector<PVertex> pv);

//for comparision between two class objects
bool compare( const PVertex& lhs, const PVertex& rhs );

//for equating two classes
bool equalise( const PVertex& lhs, const PVertex& rhs );
*/


#endif