/*
 * copyConstructor.h
 *
 *  Created on: 18-Jan-2018
 *      Author: AMRUTH
 */

#ifndef COPYCONSTRUCTOR_H_
#define COPYCONSTRUCTOR_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "../myCode/CRoute.h"

class copyConstructor: public CppUnit::TestFixture {

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

	void testCopyConstructor() {
		json->setMediaName("test");
		json->readData(*wpdb, *poidb, CJsonPersistence::REPLACE);
		route->connectToPoiDatabase(poidb);
		route->connectToWpDatabase(wpdb);
		route->addWaypoint("Amsterdam");
		route->addPoi("HDA MENSA", "Amsterdam");
		CRoute copyRoute(*route);
		CPPUNIT_ASSERT(route->getRoute().size() == 2);
	}
	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Load Tests");
		suite->addTest(
				new CppUnit::TestCaller<copyConstructor>("Load Existing",
						&copyConstructor::testCopyConstructor));

		return suite;
	}

};



#endif /* COPYCONSTRUCTOR_H_ */
