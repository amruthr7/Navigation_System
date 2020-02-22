/*
 * CWpDatabase.h
 *
 *  Created on: 22-Nov-2017
 *      Author: AMRUTH
 */

#ifndef CWPDATABASE_H_
#define CWPDATABASE_H_

#include <iostream>
#include <stdlib.h>
#include <map>
#include "CWaypoint.h"
#include "CTempClass.h"
//using namespace std;

class CWpDatabase:public CTempClass<std::string, CWaypoint>
{

public:
	/*
	 * @description:Creating a container using a map
	 */
	//map<string, CWaypoint> m_wp;

	/* @methodName : CWpDatabase::CWpDatabase()
	 * @description : Constructor - Initialize the input parameters.
	 */
	CWpDatabase();

	/* @methodName : CWpDatabase::addWaypoint(CWaypoint const& wp)
	 * @description : Add WP's to database.
	 */
	void addWaypoint(CWaypoint const& wp);

	/* @methodName : CWaypoint* CWpDatabase::getPointerToWaypoint(string name)
	 * @description : Check the input parameter if present in the database, else return error.
	 * @paramOutput : Returns the address of the wp
	 */
	CWaypoint* getPointerToWaypoint(string name);

	/* @methodName : CWpDatabase::print(ostream& out) const
	 * @description : Prints the content of the wp database
	 */
	void print(ostream& out) const;

	/* @methodName : CWpDatabase::printwpstorage() const
	 * @description : Prints the content of the wp database
	 */
	void printwpstorage();

	void wpclear();
};

#endif /* CWPDATABASE_H_ */
