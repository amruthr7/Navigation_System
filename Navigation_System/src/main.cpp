// GIT-Labor
// main.h

////////////////////////////////////////////////////////////////////////////////
// Header-Dateien
#include <iostream>		// Header für die Standard-IO-Objekte (z.B. cout, cin)
#include "CWaypoint.h"
#include "CPOI.h"
#include "CGPSSensor.h"
#include "CPoiDatabase.h"
#include "CRoute.h"
#include "CNavigationSystem.h"
#include "CStorageNavigation.h"
#include "CTempClass.h"
#include "CJsonPersistence.h"

#include <stdlib.h>
#include <math.h>
#include <cstring>


// TODO: Fügen Sie hier weitere benötigte Header-Dateien der
// Standard-Bibliothek ein z.B.
// #include <string>

using namespace std;	// Erspart den scope vor Objekte der
						// C++-Standard-Bibliothek zu schreiben
						// z.B. statt "std::cout" kann man "cout" schreiben

// Inkludieren Sie hier die Header-Files Ihrer Klassen, z.B.
// #include "CFraction.h"

// Hauptprogramm
// Dient als Testrahmen, von hier aus werden die Klassen aufgerufen
int main (void)
{
#if 0
	CNavigationSystem myNavSystem;
	myNavSystem.run();
#endif

#if 0

	CWaypoint amsterdam("Amsterdam", 52.370216, 4.895168);
	CWaypoint darmstadt("Darmstadt", 49.872825, 8.651193);
	CPOI mensa(RESTAURANT, "HDA MENSA", "The best Mensa in the world",
			49.867269, 8.638176);
	CPOI hill(TOURISTIC, "Wayanad", "hill station in Kerala", 11.685358,
			76.131995);
	CPOI obj;
	CWpDatabase wpdb;
	CPoiDatabase poidb;
	CRoute route;
	route.connectToWpDatabase(&wpdb);
	route.connectToPoiDatabase(&poidb);
	wpdb.addWaypoint(amsterdam);
	wpdb.addWaypoint(darmstadt);
	poidb.addPoi(mensa);
	poidb.addPoi(hill);
	poidb.addPoi(obj);
	route.addWaypoint("Amsterdam");
	route.addWaypoint("Darmstadt");
	route.addPoi("HDA MENSA", "Amsterdam");
	//route.addPoi("Wayanad", "Darmstadt");
	double dist = 0;
	dist = route.getDistanceNextPoi(amsterdam, obj);
	dist = route.getDistanceNextPoi(darmstadt,obj);
#endif

#if 0
	CJsonPersistence cjson;
	cjson.setMediaName("test");
	CWpDatabase wp;
	CPoiDatabase poi;
	CRoute route;
	cjson.readData(wp,poi,CPersistentStorage::REPLACE);
	route.connectToWpDatabase(&wp);
	route.connectToPoiDatabase(&poi);
	route.addWaypoint("Amsterdam");
	route.addPoi("HDA MENSA", "Amsterdam");
	route.print();
#endif

#if 0
	CWaypoint amsterdam("Amsterdam", 52.370216, 4.895168);
	//CWaypoint darmstadt("Darmstadt", 49.872825, 8.651193);
	CPOI mensa(RESTAURANT, "HDA MENSA", "The best Mensa in the world" , 49.867269, 8.638176);
	//CPOI hill (TOURISTIC, "Wayanad", "hill station in Kerala", 11.685358,76.131995);
	/*CTempClass<string, CWaypoint> obj;
	obj.addValue(amsterdam);
	obj.printValue();*/
	CWpDatabase wp;
	CPoiDatabase poi;
	wp.addWaypoint(amsterdam);
	//wp.addWaypoint(darmstadt);
	poi.addPoi(mensa);
	//poi.addPoi(hill);
	CJsonPersistence obj2;
	obj2.setMediaName("test");
	obj2.writeData(wp,poi);
#endif

#if 1
	CWpDatabase wp;
	CPoiDatabase poi;
	CJsonPersistence obj2;
	obj2.setMediaName("test");
	obj2.readData(wp,poi,CPersistentStorage::MERGE);
	cout << "The content in the wp db are:" << endl;
	wp.printwpstorage();
	cout << "The content in the poi db are:" << endl;
	poi.printpoistorage();

#endif

return 0;
}
