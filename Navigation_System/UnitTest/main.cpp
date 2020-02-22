/*
 * main.cpp
 *
 *  Created on: 17-Jan-2018
 *      Author: AMRUTH
 */
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include "connectToPoiDatabase.h"
#include "connectToWpDatabase.h"
#include "addWaypoint.h"
#include "addPoi.h"
#include "print.h"
#include "copyConstructor.h"
#include "operatorPlus.h"
#include "operatorEquals.h"
#include "operatorPlusEquals.h"
#include "getDistance.h"

using namespace CppUnit;

int main (){

	TextUi::TestRunner runner;
		runner.addTest (connectToPoiDatabase::suite() );
		runner.addTest(connectToWpDatabase::suite() );
		runner.addTest(addWaypoint::suite() );
		runner.addTest(addPoi::suite() );
		runner.addTest(print::suite() );
		runner.addTest(copyConstructor::suite() );
		runner.addTest(operatorPlus::suite() );
		runner.addTest(operatorEquals::suite() );
		runner.addTest(operatorPlusEquals::suite() );
		runner.addTest(getDistance::suite() );
		runner.run();

	return 0;
}


