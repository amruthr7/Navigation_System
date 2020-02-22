/*
 * operatorPlusEquals.h
 *
 *  Created on: 18-Jan-2018
 *      Author: AMRUTH
 */

#ifndef OPERATORPLUSEQUALS_H_
#define OPERATORPLUSEQUALS_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "../myCode/CRoute.h"

class operatorPlusEquals: public CppUnit::TestFixture {

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

	void testPlusEqualsWp() {
		json->setMediaName("test");
		json->readData(*wpdb, *poidb, CJsonPersistence::REPLACE);
		route->connectToPoiDatabase(poidb);
		route->connectToWpDatabase(wpdb);
		route->addWaypoint("Darmstadt");
		route->addPoi("HDA MENSA", "Amsterdam");
		CRoute route1;
		route1.connectToPoiDatabase(poidb);
		route1.connectToWpDatabase(wpdb);
		route1.operator +=("Darmstadt");
		//route1.print();
		CPPUNIT_ASSERT(route->getRoute().size() == 2);
	}

	void testPlusEqualsPoi() {
		json->setMediaName("test");
		json->readData(*wpdb, *poidb, CJsonPersistence::REPLACE);
		route->connectToPoiDatabase(poidb);
		route->connectToWpDatabase(wpdb);
		route->addWaypoint("Darmstadt");
		route->addPoi("HDA MENSA", "Darmstadt");
		CRoute route1;
		route1.connectToPoiDatabase(poidb);
		route1.connectToWpDatabase(wpdb);
		route1.operator +=("HDA MENSA");
		//route1.print();
		CPPUNIT_ASSERT(route->getRoute().size() == 2);
	}

	void testWpAndPoi() {
		json->setMediaName("test");
		json->readData(*wpdb, *poidb, CJsonPersistence::REPLACE);
		route->connectToPoiDatabase(poidb);
		route->connectToWpDatabase(wpdb);
		route->addWaypoint("Amsterdam");
		route->addPoi("HDA MENSA", "Amsterdam");
		CRoute route1;
		route1.connectToPoiDatabase(poidb);
		route1.connectToWpDatabase(wpdb);
		route1.operator +=("Amsterdam");
		//route1.print();
		CPPUNIT_ASSERT(route->getRoute().size() == 2);
	}

	void testNoWpAndPoi() {
		json->setMediaName("test");
		json->readData(*wpdb, *poidb, CJsonPersistence::REPLACE);
		route->connectToPoiDatabase(poidb);
		route->connectToWpDatabase(wpdb);
		route->addWaypoint("Amsterdam");
		route->addPoi("HDA MENSA", "Amsterdam");
		CRoute route1;
		route1.connectToPoiDatabase(poidb);
		route1.connectToWpDatabase(wpdb);
		route1.operator +=("abcd");
		//route1.print();
		CPPUNIT_ASSERT(route->getRoute().size() == 2);
	}

	void testDbNotConnected() {
		json->setMediaName("test");
		json->readData(*wpdb, *poidb, CJsonPersistence::REPLACE);
		route->connectToPoiDatabase(poidb);
		route->connectToWpDatabase(wpdb);
		route->addWaypoint("Amsterdam");
		route->addPoi("HDA MENSA", "Amsterdam");
		CRoute route1;
		/*route1.connectToPoiDatabase(poidb);
		 route1.connectToWpDatabase(wpdb);
		 */
		route1.operator +=("Amsterdam");
		//route1.print();
		CPPUNIT_ASSERT(route->getRoute().size() == 2);
	}

	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Load Tests");
		suite->addTest(
				new CppUnit::TestCaller<operatorPlusEquals>("Load Existing",
						&operatorPlusEquals::testPlusEqualsWp));
		suite->addTest(
				new CppUnit::TestCaller<operatorPlusEquals>("Load Existing",
						&operatorPlusEquals::testPlusEqualsPoi));
		suite->addTest(
				new CppUnit::TestCaller<operatorPlusEquals>("Load Existing",
						&operatorPlusEquals::testWpAndPoi));
		suite->addTest(
				new CppUnit::TestCaller<operatorPlusEquals>("Load Existing",
						&operatorPlusEquals::testNoWpAndPoi));
		suite->addTest(
				new CppUnit::TestCaller<operatorPlusEquals>("Load Existing",
						&operatorPlusEquals::testDbNotConnected));
		return suite;
	}

};

#endif /* OPERATORPLUSEQUALS_H_ */
