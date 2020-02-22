/*
 * connectToPoiDb.h
 *
 *  Created on: 17-Jan-2018
 *      Author: AMRUTH
 */

#ifndef CONNECTTOPOIDATABASE_H_
#define CONNECTTOPOIDATABASE_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "../myCode/CRoute.h"

class connectToPoiDatabase: public CppUnit::TestFixture {

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

	void testConnectPoiDb() {
		json->setMediaName("test");
		json->readData(*wpdb, *poidb, CJsonPersistence::REPLACE);
		route->connectToPoiDatabase(poidb);
		route->connectToWpDatabase(wpdb);
		route->addWaypoint("Amsterdam");
		route->addPoi("HDA MENSA", "Amsterdam");
		CPPUNIT_ASSERT(route->getRoute().size() == 2);
	}

	void testNoConnectPoiDb() {
		json->setMediaName("test");
		json->readData(*wpdb, *poidb, CJsonPersistence::REPLACE);
		route->connectToPoiDatabase(NULL);
		route->connectToWpDatabase(wpdb);
		route->addWaypoint("Amsterdam");
		route->addPoi("HDA MENSA", "Amsterdam");
		CPPUNIT_ASSERT(route->getRoute().size() == 1);
	}

	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Load Tests");
		suite->addTest(
				new CppUnit::TestCaller<connectToPoiDatabase>("Load Existing",
						&connectToPoiDatabase::testConnectPoiDb));
		suite->addTest(
				new CppUnit::TestCaller<connectToPoiDatabase>("Load Existing",
						&connectToPoiDatabase::testNoConnectPoiDb));

		return suite;
	}

};

#endif /* CONNECTTOPOIDATABASE_H_ */
