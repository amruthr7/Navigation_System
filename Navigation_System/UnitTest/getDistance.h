/*
 * getDistance.h
 *
 *  Created on: 18-Jan-2018
 *      Author: AMRUTH
 */

#ifndef GETDISTANCE_H_
#define GETDISTANCE_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "../myCode/CRoute.h"

class getDistance: public CppUnit::TestFixture {

private:
	CJsonPersistence* json;
	CRoute* route;
	CWpDatabase* wpdb;
	CPoiDatabase* poidb;
	CPOI* poi;

public:

	void setUp() {
		json = new CJsonPersistence;
		route = new CRoute;
		wpdb = new CWpDatabase;
		poidb = new CPoiDatabase;
		poi = new CPOI;
	}
	void tearDown() {
		delete json;
		delete route;
		delete wpdb;
		delete poidb;
	}

	void testDistanceWp() {
		json->setMediaName("test");
		json->readData(*wpdb, *poidb, CJsonPersistence::REPLACE);
		route->connectToPoiDatabase(poidb);
		route->connectToWpDatabase(wpdb);
		route->addWaypoint("Amsterdam");
		route->addPoi("HDA MENSA", "Amsterdam");
		double dist = route->getDistanceNextPoi(*wpdb->getPointerToVal("Amsterdam"), *poi);
		CPPUNIT_ASSERT(dist!=1000000);
	}



	void testDistanceWithoutPoi() {
			json->setMediaName("test");
			json->readData(*wpdb, *poidb, CJsonPersistence::REPLACE);
			route->connectToPoiDatabase(poidb);
			route->connectToWpDatabase(wpdb);
			route->addWaypoint("Amsterdam");
			double dist = route->getDistanceNextPoi(*wpdb->getPointerToVal("Amsterdam"), *poi);
			CPPUNIT_ASSERT(dist==1000000);
		}


	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Load Tests");
		suite->addTest(
				new CppUnit::TestCaller<getDistance>("Load Existing",
						&getDistance::testDistanceWp));
		/*suite->addTest(
						new CppUnit::TestCaller<getDistance>("Load Existing",
								&getDistance::testDistanceWithoutPoi));
*/
		return suite;
	}

};




#endif /* GETDISTANCE_H_ */
