/*
 * addWaypoint.h
 *
 *  Created on: 18-Jan-2018
 *      Author: AMRUTH
 */

#ifndef ADDWAYPOINT_H_
#define ADDWAYPOINT_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "../myCode/CRoute.h"

class addWaypoint: public CppUnit::TestFixture {

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

	void testAddWaypoint() {
		json->setMediaName("test");
		json->readData(*wpdb, *poidb, CJsonPersistence::REPLACE);
		route->connectToWpDatabase(wpdb);
		route->addWaypoint("Amsterdam");
		CPPUNIT_ASSERT(route->getRoute().size() == 1);
	}

	void testNoAddWaypoint() {
		json->setMediaName("test");
		json->readData(*wpdb, *poidb, CJsonPersistence::REPLACE);
		route->connectToWpDatabase(wpdb);
		route->addWaypoint("NULL");
		CPPUNIT_ASSERT(route->getRoute().size() == 0);
	}

	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Load Tests");
		suite->addTest(
				new CppUnit::TestCaller<addWaypoint>("Load Existing",
						&addWaypoint::testAddWaypoint));
		suite->addTest(
				new CppUnit::TestCaller<addWaypoint>("Load Existing",
						&addWaypoint::testNoAddWaypoint));

		return suite;
	}
};



#endif /* ADDWAYPOINT_H_ */
