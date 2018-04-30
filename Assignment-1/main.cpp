#include "PVertex.h"
#include "PEdge.h"
#include "PPlane.h"
#include "Funcky.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <cstdlib>


using namespace std;


int main(){
	const char* fnamex = "vxinput.txt";
	const char* fnamey = "vyinput.txt";
	const char* fnamez = "vzinput.txt";

	const char* enamex = "exinput.txt";
	const char* enamey = "eyinput.txt";
	const char* enamez = "ezinput.txt";

	vector< vector<PVertex> > pv(3);
	pv[0] = PVReader( fnamex );
	pv[1] = PVReader( fnamey );
	pv[2] = PVReader( fnamez );
	vector<PVertex> pv3d = GeneratePVertices( pv );
	CleanPVertices( pv3d, pv );

	vector< map< pair<int, int>, int > > pemap(3);
	PEReader(enamex, enamey, enamez, pemap);

	vector<PEdge> pedv = GeneratePEdges3(pemap, pv3d);

	PEPrinter(pedv);
	PVPrinter(pv3d);

	cout << endl << " have fun "<< endl;
	cout << pv3d.size() << endl;
	cout << pedv.size() << endl;

	
	return 0;
}