/*
 * connectToWpDatabase.h
 *
 *  Created on: 18-Jan-2018
 *      Author: AMRUTH
 */

#ifndef CONNECTTOWPDATABASE_H_
#define CONNECTTOWPDATABASE_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "../myCode/CRoute.h"

class connectToWpDatabase: public CppUnit::TestFixture {

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

	void testConnectWpDb() {
		json->setMediaName("test");
		json->readData(*wpdb, *poidb, CJsonPersistence::REPLACE);
		route->connectToWpDatabase(wpdb);
		route->addWaypoint("Amsterdam");
		CPPUNIT_ASSERT(route->getRoute().size() == 1);
	}

	void testNoConnectWpDb() {
		json->setMediaName("test");
		json->readData(*wpdb, *poidb, CJsonPersistence::REPLACE);
		route->connectToWpDatabase(NULL);
		route->addWaypoint("Amsterdam");
		CPPUNIT_ASSERT(route->getRoute().size() == 0);
	}

	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Load Tests");
		suite->addTest(
				new CppUnit::TestCaller<connectToWpDatabase>("Load Existing",
						&connectToWpDatabase::testConnectWpDb));
		suite->addTest(
				new CppUnit::TestCaller<connectToWpDatabase>("Load Existing",
						&connectToWpDatabase::testNoConnectWpDb));

		return suite;
	}
};


#endif /* CONNECTTOWPDATABASE_H_ */
