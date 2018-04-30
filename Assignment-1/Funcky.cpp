#include "PVertex.h"
#include "PEdge.h"
#include "PPlane.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <cstdlib>
#include <algorithm>

using namespace std;

/*!<for taking the vertex input*/
vector<PVertex> PVReader(const char* s){
	ifstream myfile (s);
	int v_size;
	string line;
	if (!myfile.is_open())
    {
        cerr << "Unable to open file" << "\n";
        exit(-1);
    }
	getline (myfile,line);
	istringstream ss(line);
	ss >> v_size;
	vector<PVertex> pv(v_size);

	for(int i = 0;i < v_size;i++){
		getline (myfile,line);
		istringstream iss(line);
		float temp;
		do{
			iss >> temp;
			(pv[i].coor).push_back(temp);
		}while(iss);
	}
	myfile.close();
	return pv;
	
}

/*!<for printing vertices*/
void PVPrinter(vector<PVertex> pv){
	int v_size = pv.size();

	for(int i = 0;i < v_size;i++){
		cout << " id: " << pv[i].coor[0] << endl;
		for(int j = 1;j < 4;j++){
			cout << pv[i].coor[j] << "	";
		}
		cout << endl;
		int p_size = (pv[i].projid).size();
		cout << " projid: " << endl;
		for(int j = 0;j < p_size;j++){
			cout << pv[i].projid[j] << "	";
		}
		cout << endl;
		int r_size = (pv[i].rays).size();
		cout << " rays: " << endl;
		for(int j = 0;j < r_size;j++){
			cout << pv[i].rays[j] << "	";
		}

		cout << endl;
		cout << endl;
	}
}


/*!<for checking whether projection or not*/
bool ProjCheck( PVertex lhs, PVertex rhs, int axis ){
	int val1 = axis%3 + 1;
	int val2 = val1%3 + 1;
	return (lhs.coor[val1] == rhs.coor[val1] && lhs.coor[val2] == rhs.coor[val2] && rhs.coor[axis] == 0.0);
}


/*!<for generating 3D probable vertices*/
vector<PVertex> GeneratePVertices2Planes(vector<PVertex> pv1, vector<PVertex> pv2, int axes,vector<PVertex> pv3){
	vector<PVertex> pv3d;
	int v_size1 = pv1.size();
	int v_size2 = pv2.size();
	int v_size3 = pv3.size();
	for(int i = 0;i < v_size1;i++){
		for(int j = 0;j < v_size2;j++){
			int axi = axes;
			if( pv1[i].coor[axi] == pv2[j].coor[axi] ){
				PVertex baby3D;
				(baby3D.coor).push_back(0.0);
				(baby3D.coor).push_back(0.0);
				(baby3D.coor).push_back(0.0);
				(baby3D.coor).push_back(0.0);
				baby3D.coor[axi] = pv1[i].coor[axi];
				axi = axi%3 + 1;
				baby3D.coor[axi] = ( pv1[i].coor[axi] + pv2[j].coor[axi] );
				axi = axi%3 + 1;
				baby3D.coor[axi] = ( pv1[i].coor[axi] + pv2[j].coor[axi] );
				for(int k = 0;k < v_size3;k++){
					if( ProjCheck(baby3D , pv3[k], axes) ){
						pv3d.push_back(baby3D);
						break;
					}
				}
			}
		}
	}

	return pv3d;
}

/*!<for generating 3D probable vertices from 3 planes*/
vector<PVertex> GeneratePVertices( vector< vector<PVertex> > pv ){
	vector<PVertex> pv3d = GeneratePVertices2Planes( pv[0], pv[1], 3, pv[2]);
	vector<PVertex> temp1 = GeneratePVertices2Planes( pv[1], pv[2], 1, pv[0]);
	vector<PVertex> temp2 = GeneratePVertices2Planes( pv[2], pv[0], 2, pv[1]);
	pv3d.insert( pv3d.end(), temp1.begin(), temp1.end() );
	pv3d.insert( pv3d.end(), temp2.begin(), temp2.end() );
	return pv3d;
}

/*!<for comparision between two class objects*/
bool Compare( const PVertex& lhs, const PVertex& rhs ){
	bool ans;
	if(lhs.coor[1] != rhs.coor[1]){
		ans =  lhs.coor[1] < rhs.coor[1];
	}else{
		if(lhs.coor[2] != rhs.coor[2]){
			ans = lhs.coor[2] < rhs.coor[2];
		}else{
			ans = lhs.coor[3] < rhs.coor[3];
		}
	}

	return ans;
}

/*!<for equating two classes*/
bool Equalise( const PVertex& lhs, const PVertex& rhs ){
	return (lhs.coor[1] == rhs.coor[1] && lhs.coor[2] == rhs.coor[2] && lhs.coor[3] == rhs.coor[3]);
}

/*!<for cleaning 3D probable vertices list of duplicates*/
void CleanPVertices(vector<PVertex> &pv, vector< vector<PVertex> > &pc){
	int v_size = pv.size();
	sort( pv.begin( ), pv.end( ), Compare );
	vector<PVertex>::iterator it;
	it = unique(pv.begin(), pv.end(), Equalise );
	pv.resize(distance(pv.begin(),it) );
	v_size = pv.size();

	for(int i = 0;i < v_size;i++){
		pv[i].coor[0] = i;
	}

	vector<int> sizy(3);
	for(int i = 0;i < 3;i++){
		sizy[i] = pc[i].size();
	}
	for(int i = 0;i < v_size;i++){
		for(int j = 0;j < 3;j++){
			for(int k = 0;k < sizy[j];k++){
				if( ProjCheck(pv[i] , pc[j][k], j + 1) ){
					(pv[i].projid).push_back( static_cast<int>( pc[j][k].coor[0] ) );
					(pc[j][k].projid).push_back( static_cast<int>( pv[i].coor[0] ) );
				}
			}
		}
	}
	
}


/*!<for taking the Edge input from one plane*/
void PEReaderSmall(const char* s1, vector< map< pair<int, int>, int > > &peh, int axis){
	int e_size;
	string line;

	ifstream myfile1 (s1);
	if (!myfile1.is_open())
    {
        cerr << "Unable to open file" << "\n";
        exit(-1);
    }
	getline (myfile1,line);
	istringstream ss(line);
	ss >> e_size;

	for(int i = 0;i < e_size;i++){
		getline (myfile1,line);
		istringstream iss(line);
		int temp1;
		int temp2;
		iss >> temp1;
		iss >> temp1;
		iss >> temp2;
		peh[axis].insert( make_pair(make_pair( min( temp1, temp2 ), max( temp1, temp2 ) ), i) );
	}
	myfile1.close();
	
}

/*!<for taking the Edge input*/
void PEReader(const char* s1, const char* s2, const char* s3, vector< map< pair<int, int>, int > > &peh){
	PEReaderSmall(s1, peh, 0);
	PEReaderSmall(s2, peh, 1);
	PEReaderSmall(s3, peh, 2);
}

/*!<for checking projection of line on single plane*/
bool ProjLinePlane( PVertex lhs, PVertex rhs, int axis,  vector< map< pair<int, int>, int > > pemap){
	map< pair<int, int>, int >::iterator it;
	bool truth = false;
	int temp1 = lhs.projid[axis];
	int temp2 = rhs.projid[axis];
	it = pemap[axis].find( make_pair( min( temp1, temp2 ), max( temp1, temp2 ) ) );
	if( it != pemap[axis].end() ){
		truth = true;
	}else{
		if( lhs.projid[axis] == rhs.projid[axis] ){
			truth = true;
		}
	}

	return truth;
}

/*!<for checking projection of line on all planes*/
bool ProjLine( PVertex lhs, PVertex rhs, vector< map< pair<int, int>, int > > pemap){
	bool truth0 = ProjLinePlane( lhs, rhs, 0, pemap);
	bool truth1 = ProjLinePlane( lhs, rhs, 1, pemap);
	bool truth2 = ProjLinePlane( lhs, rhs, 2, pemap);
	bool final = truth0 && truth1 && truth2;

	return final;
}


/*!<for generating 3D probable edges from 3D vertices, primary level*/
vector<PEdge> GeneratePEdges1( vector<PVertex> &pv3d, vector< map< pair<int, int>, int > > pemap ){
	vector<PEdge> pedv;
	int size1 = pv3d.size();
	int id = 0;

	for(int i = 1;i < size1;i++){
		for(int j = 0;j < i;j++){
			if( ProjLine( pv3d[i], pv3d[j], pemap ) ){
				PEdge baby3D( pv3d[i], pv3d[j], id );
				pedv.push_back(baby3D);
				pv3d[i].rays.push_back(id);
				pv3d[j].rays.push_back(id);
				id++;
			}
		}
	}

	return pedv;
}


/*!<for printing Edges*/
void PEPrinter(vector<PEdge> pedv){
	int size1 = pedv.size();
	for(int i = 0;i < size1;i++){
		cout << pedv[i].id << " ";
		cout << pedv[i].vert1.coor[0] << " ";
		cout << pedv[i].vert2.coor[0] << endl;
	}
}


/*!<for checking containment of a point on line*/
bool ContainPoint( PEdge pe1, PVertex pv1 ){
	float tot = 0.0;
	float tot1 = 0.0;
	float tot2 = 0.0;
	
	bool ans = true;

	for(int i = 1;i < 4;i++){
		tot += (pe1.vert2.coor[i] - pe1.vert1.coor[i])*(pe1.vert2.coor[i] - pe1.vert1.coor[i]);
		tot1 += (pv1.coor[i] - pe1.vert1.coor[i])*(pv1.coor[i] - pe1.vert1.coor[i]);
		tot2 += (pv1.coor[i] - pe1.vert2.coor[i])*(pv1.coor[i] - pe1.vert2.coor[i]);
	}
	tot = sqrt(tot);
	tot1 = sqrt(tot1);
	tot2 = sqrt(tot2);

	ans = (fabs(tot - (tot1 + tot2)) <= 0.001);

	return ans;
}


/*!<for checking colinear containment of line in another line*/
int ContainLine( PEdge pe1, PEdge pe2 ){
	bool ans1 = ContainPoint( pe2, pe1.vert1) && ContainPoint( pe2, pe1.vert2);
	bool ans2 = ContainPoint( pe1, pe2.vert1) && ContainPoint( pe1, pe2.vert2);
	int answ = 0;
	if(ans1){
		answ = 1;
	}else if(ans2){
		answ = -1;
	}else{
		answ = 0;
	}
	return answ;
}


/*!<to delete edge element for GeneratePEdges2 function*/
bool Delete(PEdge pe1){
	return (pe1.id == -1);
}


/*!<for generating 3D probable edges from 3D vertices, secondary level, removing colinear containment*/
void GeneratePEdges2(map<float, int> VertexAddr, vector<PVertex> &pv3d, vector<PEdge> &pedv){
	int sizee = pedv.size();
	vector<int> flay(sizee);

	for(int i = 1;i < sizee;i++){
		for(int j = 0;j < i;j++){
			if(flay[j] == 0){
				if(ContainLine( pedv[i], pedv[j]) == 1){
					flay[j] = 1;
					int id1 = VertexAddr[ pedv[j].vert1.coor[0] ];
					int id2 = VertexAddr[ pedv[j].vert2.coor[0] ];
					int tid = pedv[j].id;
					pv3d[id1].rays.erase( remove(pv3d[id1].rays.begin(), pv3d[id1].rays.end(), tid),
					 	pv3d[id1].rays.end());
					pv3d[id2].rays.erase( remove(pv3d[id2].rays.begin(), pv3d[id2].rays.end(), tid), 
						pv3d[id2].rays.end());
					pedv[j].id = -1;
				}else if(ContainLine( pedv[i], pedv[j]) == -1){
					flay[i] = 1;
					int id1 = VertexAddr[ pedv[j].vert1.coor[0] ];
					int id2 = VertexAddr[ pedv[j].vert2.coor[0] ];
					int tid = pedv[i].id;
					pv3d[id1].rays.erase( remove(pv3d[id1].rays.begin(), pv3d[id1].rays.end(), tid), 
						pv3d[id1].rays.end());
					pv3d[id2].rays.erase( remove(pv3d[id2].rays.begin(), pv3d[id2].rays.end(), tid), 
						pv3d[id2].rays.end());
					pedv[i].id = -1;
				}else{
					continue;
				}
			}
		}
	}

	pedv.erase( remove_if (pedv.begin(), pedv.end(), Delete), pedv.end() );
}

/*!<to store the id and index relationship of elements in vertex vector and edge vector*/
void BuildOrReconfig(vector<PVertex> pv3d, map<float, int> &VertexAddr,int br ){
	int vsize = pv3d.size();

	if(br == 0){
		for(int i = 0;i < vsize;i++){
			VertexAddr.insert( make_pair( pv3d[ i ].coor[ 0 ], i ) );
		}
	}else{
		for(int i = 0;i < vsize;i++){
			VertexAddr[ pv3d[ i ].coor[ 0 ] ] = i;
		}
	}
}


/*!<for generating 3D probable edges from 3D vertices, teritiary level, removing fake vertices*/
vector<PEdge> GeneratePEdges3(vector< map< pair<int, int>, int > > pemap, vector<PVertex> &pv3d){
	map<float, int> VertexAddr;

	BuildOrReconfig(pv3d, VertexAddr, 0);

	vector<PEdge> pedv = GeneratePEdges1( pv3d, pemap );
	GeneratePEdges2(VertexAddr, pv3d, pedv);
	int vsize = pv3d.size();
	int flag = 0;

	for(int i = 0;i < vsize;i++){
		int tesize = pv3d[i].rays.size();
		if(tesize < 3){
			pv3d.erase( pv3d.begin() + i );
			flag = 1;
			break;
		}
	}

	if(flag == 0){
		return pedv;
	}else{
		int v_size = pv3d.size();
		for(int i = 0;i < v_size;i++){
			pv3d[i].rays.clear();
		}
		return GeneratePEdges3(pemap, pv3d);
	}
	
	return pedv;
}


/*!<to find the common vertex of 2 PEdges*/
int CommonVertex(PEdge pe1, PEdge pe2){
	int ans = -1;
	if( pe1.vert1.coor[0] == pe2.vert1.coor[0] ){
		ans = 0;
	}
	if( pe1.vert1.coor[0] == pe2.vert2.coor[0] ){
		ans = 1;
	}
	if( pe1.vert2.coor[0] == pe2.vert1.coor[0] ){
		ans = 2;
	}
	if( pe1.vert2.coor[0] == pe2.vert2.coor[0] ){
		ans = 3;
	}

	return ans;
}

