/*
 * addPoi.h
 *
 *  Created on: 18-Jan-2018
 *      Author: AMRUTH
 */

#ifndef ADDPOI_H_
#define ADDPOI_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "../myCode/CRoute.h"

class addPoi: public CppUnit::TestFixture {

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

	void testAddPoi() {
		json->setMediaName("test");
		json->readData(*wpdb, *poidb, CJsonPersistence::REPLACE);
		route->connectToPoiDatabase(poidb);
		route->connectToWpDatabase(wpdb);
		route->addWaypoint("Amsterdam");
		route->addPoi("HDA MENSA", "Amsterdam");
		CPPUNIT_ASSERT(route->getRoute().size() == 2);
	}

	void testIncorrectPoi() {
		json->setMediaName("test");
		json->readData(*wpdb, *poidb, CJsonPersistence::REPLACE);
		route->connectToPoiDatabase(poidb);
		route->connectToWpDatabase(wpdb);
		route->addWaypoint("Amsterdam");
		route->addPoi("abcd", "Amsterdam");
		CPPUNIT_ASSERT(route->getRoute().size() == 1);
	}

	void testIncorrectWp() {
		json->setMediaName("test");
		json->readData(*wpdb, *poidb, CJsonPersistence::REPLACE);
		route->connectToPoiDatabase(poidb);
		route->connectToWpDatabase(wpdb);
		route->addWaypoint("Amsterdam");
		route->addPoi("HDA MENSA", "abcd");
		CPPUNIT_ASSERT(route->getRoute().size() == 1);
	}

	void testNoPoiAndWp() {
		json->setMediaName("test");
		json->readData(*wpdb, *poidb, CJsonPersistence::REPLACE);
		route->connectToPoiDatabase(poidb);
		route->connectToWpDatabase(wpdb);
		route->addWaypoint("Amsterdam");
		route->addPoi("abcd", "fgfg");
		CPPUNIT_ASSERT(route->getRoute().size() == 1);
	}

	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Load Tests");
		suite->addTest(
				new CppUnit::TestCaller<addPoi>("Load Existing",
						&addPoi::testAddPoi));
		suite->addTest(
				new CppUnit::TestCaller<addPoi>("Load Existing",
						&addPoi::testIncorrectWp));
		suite->addTest(
				new CppUnit::TestCaller<addPoi>("Load Existing",
						&addPoi::testIncorrectPoi));
		suite->addTest(
				new CppUnit::TestCaller<addPoi>("Load Existing",
						&addPoi::testNoPoiAndWp));
		return suite;
	}

};

#endif /* ADDPOI_H_ */
