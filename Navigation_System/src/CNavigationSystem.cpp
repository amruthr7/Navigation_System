/*
 * CNavigationSystem.cpp
 *
 *  Created on: 27-Oct-2017
 *      Author: AMRUTH
 */

#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <math.h>
#include "CNavigationSystem.h"
using namespace std;

CNavigationSystem::CNavigationSystem()
{
cout << "Welcome to the Navigation System! " <<endl;
}
void CNavigationSystem::run()
{
	enterRoute();
	//printRoute();
	//printDistanceCurPosNextPoi();
}
void CNavigationSystem::enterRoute()
{
#if 1
	//Create objects for waypoints
	CWaypoint amsterdam("Amsterdam", 52.370216, 4.895168);
	CWaypoint darmstadt("Darmstadt", 49.872825, 8.651193);

	//Create objects for POI's
	CPOI mensa(RESTAURANT, "HDA MENSA", "The best Mensa in the world" , 49.867269, 8.638176);
	CPOI hill (TOURISTIC, "Wayanad", "hill station in Kerala", 11.685358,76.131995);

	//Add waypoints to WP Database
	CWpDatabase wpdb;
	//CWpDatabase wpdb1;
	wpdb.addWaypoint(amsterdam);
	wpdb.addWaypoint(darmstadt);

	//Add POI's to POI Database
	//exercise2 : 2.1b testing if poi's are getting added to CPoiDatabase
	CPoiDatabase poidb;
	//CPoiDatabase poidb1;
	poidb.addPoi(mensa);
	poidb.addPoi(hill);
	/*poidb.addPoi(petrol);
	 poidb.addPoi(home);*/

	//Create and connect routes to Databases
	//exercise2 : 2.1fa CRoute addwaypoint - testing if waypoint is getting added to the route
	CRoute route;
	CRoute croute;
	CRoute croute2;
	CRoute croute3;
	route.connectToWpDatabase(&wpdb);
	route.connectToPoiDatabase(&poidb);
	croute.connectToWpDatabase(&wpdb);
	croute.connectToPoiDatabase(&poidb);
	//croute2.connectToWpDatabase(&wpdb);
	//croute2.connectToPoiDatabase(&poidb);
	croute3.connectToWpDatabase(&wpdb);
	croute3.connectToPoiDatabase(&poidb);

	//Add Waypoint to the route
	route.addWaypoint("Amsterdam");
	croute.addWaypoint("Darmstadt");
	//route.addWaypoint("Darmstadt");
	//croute.addWaypoint("Berlin");

	//Add POI to the route
	//exercise2 : 2.1fb CRoute addpoi - testing if poi is getting added to the route
	route.addPoi("HDA MENSA", "Amsterdam");
	croute.addPoi("Wayanad", "Darmstadt");
	/*route.addPoi("Shell Petro","Amserdam");
	 route.addPoi("Hom", "Berlin");*/

	route.print();							//Print route
	croute2 = route + croute;				//Add 2 routes
	croute2.print();
	croute3 += "HDA MENSA";					//Add WP and/or POI as a string at the end of the route
	croute3.print();
#endif
#if 0
	CWpDatabase wpdb, wpdb1,wpdb2,wpdb3,wpdb4;
	CPoiDatabase poidb, poidb1, poidb2,poidb3,poidb4;
	CStorageNavigation storage;

	//Define WP's and POI's
	CWaypoint amsterdam("Amsterdam", 52.370216, 4.895168);
	//CWaypoint darmstadt("Darmstadt", 49.872825, 8.651193);
	CPOI hill (TOURISTIC, "Wayanad", "hill station in Kerala", 11.685358,76.131995);
	//CPOI mensa(RESTAURANT, "HDA MENSA", "The best Mensa in the world" , 49.867269, 8.638176);

	wpdb.addWaypoint(amsterdam);
	//wpdb.addWaypoint(darmstadt);
	poidb.addPoi(hill);
	//poidb.addPoi(mensa);

	/*wpdb1.addWaypoint(amsterdam);
	//wpdb1.addWaypoint(darmstadt);
	poidb1.addPoi(hill);
	//poidb1.addPoi(mensa);*/

	/*wpdb2.addWaypoint(amsterdam);
	//wpdb2.addWaypoint(darmstadt);
	poidb2.addPoi(hill);
	//poidb2.addPoi(mensa);*/

	/*wpdb3.addWaypoint(amsterdam);
	//wpdb3.addWaypoint(darmstadt);
	poidb3.addPoi(hill);
	//poidb3.addPoi(mensa);*/

	/*wpdb4.addWaypoint(amsterdam);
	//wpdb4.addWaypoint(darmstadt);
	poidb4.addPoi(hill);
	//poidb4.addPoi(mensa);*/

//1. Write and read data to and from a file
	storage.setMediaName("storage");
	//storage.writeData(wpdb,poidb);
	storage.readData(wpdb,poidb,REPLACE);
	wpdb.printwpstorage();
	poidb.printpoistorage();

//2. Test if the number of parameters for a wp/poi is incorrect
	/*storage.setMediaName("params");
	//storage.writeData(wpdb1,poidb1);
	storage.readData(wpdb1,poidb1,REPLACE);
	wpdb1.printwpstorage();
	poidb1.printpoistorage();*/

//3. Test if a ',' is present as a delimiter instead of a ';'
	/*storage.setMediaName("delims");
	//storage.writeData(wpdb2,poidb2);
	storage.readData(wpdb2,poidb2,REPLACE);
	wpdb2.printwpstorage();
	poidb2.printpoistorage();*/

//4. Test if a text is present instead of a number
	/*storage.setMediaName("text");
	//storage.writeData(wpdb3,poidb3);
	storage.readData(wpdb3,poidb3,REPLACE);
	wpdb3.printwpstorage();
	poidb3.printpoistorage();*/

//5. Test if a comma is present instead of a dot in latitude/longitude
	/*storage.setMediaName("dot");
	//storage.writeData(wpdb4,poidb4);
	storage.readData(wpdb4, poidb4, REPLACE);
	wpdb4.printwpstorage();
	poidb4.printpoistorage();*/

/*
	CRoute route;
	route.connectToWpDatabase(&wpdb);
	route.connectToPoiDatabase(&poidb);
	route.addWaypoint("Amsterdam");
	route.addPoi("Wayanad", "Amsterdam");
	route.print();
*/
#endif
}

//print the entire route
void CNavigationSystem::printRoute()
{

}

//Print the distance from current location to the nearest POI
void CNavigationSystem::printDistanceCurPosNextPoi()
{
	/*CPOI poi;
	CWaypoint waypoint;
	waypoint = m_GPSSensor.getCurrentPosition();
	m_route.getDistanceNextPoi(waypoint, poi);
	//poi.print();
	*/
}
