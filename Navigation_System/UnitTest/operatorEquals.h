/*
 * operatorEquals.h
 *
 *  Created on: 18-Jan-2018
 *      Author: AMRUTH
 */

#ifndef OPERATOREQUALS_H_
#define OPERATOREQUALS_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "../myCode/CRoute.h"

class operatorEquals: public CppUnit::TestFixture {

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

	void testEqualsOperator() {
		json->setMediaName("test");
		json->readData(*wpdb, *poidb, CJsonPersistence::REPLACE);
		route->connectToPoiDatabase(poidb);
		route->connectToWpDatabase(wpdb);
		route->addWaypoint("Amsterdam");
		route->addPoi("HDA MENSA", "Amsterdam");
		CRoute route1;
		route1.connectToPoiDatabase(poidb);
		route1.connectToWpDatabase(wpdb);
		route1.operator =(*route);
		//route1.print();
		CPPUNIT_ASSERT(route->getRoute().size() == 2);
	}
	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Load Tests");
		suite->addTest(
				new CppUnit::TestCaller<operatorEquals>("Load Existing",
						&operatorEquals::testEqualsOperator));

		return suite;
	}

};




#endif /* OPERATOREQUALS_H_ */
