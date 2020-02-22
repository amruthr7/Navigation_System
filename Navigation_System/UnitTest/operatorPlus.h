/*
 * operatorplus.h
 *
 *  Created on: 18-Jan-2018
 *      Author: AMRUTH
 */

#ifndef OPERATORPLUS_H_
#define OPERATORPLUS_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "../myCode/CRoute.h"

class operatorPlus: public CppUnit::TestFixture {

private:
	CJsonPersistence* json;
	CRoute* route;
	CWpDatabase* wpdb;
	CPoiDatabase* poidb;

public:

	void setUp() {
		json = new CJsonPersistence;
		route = new CRoute;
		wpdb = new CWpDatabase;
		poidb = new CPoiDatabase;
	}
	void tearDown() {
		delete json;
		delete route;
		delete wpdb;
		delete poidb;
	}

	void testAddOperator() {
		json->setMediaName("test");
		json->readData(*wpdb, *poidb, CJsonPersistence::REPLACE);
		route->connectToPoiDatabase(poidb);
		route->connectToWpDatabase(wpdb);
		route->addWaypoint("Amsterdam");
		route->addPoi("HDA MENSA", "Amsterdam");
		CRoute route1;
		CRoute route2;
		route1.connectToPoiDatabase(poidb);
		route1.connectToWpDatabase(wpdb);
		route2.connectToPoiDatabase(poidb);
		route2.connectToWpDatabase(wpdb);
		route2 = route1.operator +(*route);
		CPPUNIT_ASSERT(route->getRoute().size() == 2);
	}

	void testWrongDB() {
			json->setMediaName("test");
			json->readData(*wpdb, *poidb, CJsonPersistence::REPLACE);
			route->connectToPoiDatabase(poidb);
			route->connectToWpDatabase(wpdb);
			route->addWaypoint("Amsterdam");
			route->addPoi("HDA MENSA", "Amsterdam");
			CRoute route1;
			CRoute route2;
			/*route1.connectToPoiDatabase(poidb);
			route1.connectToWpDatabase(wpdb);
			route2.connectToPoiDatabase(poidb);
			route2.connectToWpDatabase(wpdb);*/
			route2 = route1.operator +(*route);
			CPPUNIT_ASSERT(route->getRoute().size() == 2);
		}


	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Load Tests");
		suite->addTest(
				new CppUnit::TestCaller<operatorPlus>("Load Existing",
						&operatorPlus::testAddOperator));
		suite->addTest(
						new CppUnit::TestCaller<operatorPlus>("Load Existing",
								&operatorPlus::testWrongDB));

		return suite;
	}

};




#endif /* OPERATORPLUS_H_ */
