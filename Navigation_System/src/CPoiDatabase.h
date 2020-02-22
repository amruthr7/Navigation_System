/*
 * CPoiDatabase.h
 *
 *  Created on: 27-Oct-2017
 *      Author: AMRUTH
 */

#ifndef CPOIDATABASE_H_
#define CPOIDATABASE_H_

#include <iostream>
#include <stdlib.h>
#include <map>
#include "CPOI.h"
#include "CTempClass.h"
//using namespace std;

class CPoiDatabase:public CTempClass<std::string, CPOI>
{
private:
    /**
     * @link aggregationByValue
     * @clientCardinality 1 
     */
	//CPOI m_POI[10];
	//int m_noPoi;

public:

	/*
	 * Creating a container using a map
	 */
	//map<string, CPOI> m_POI;

	/* @methodName : CPoiDatabase::CPoiDatabase()
     * @description : Constructor - Initialize the input parameters.
     */
	CPoiDatabase();

    /* @methodName : CPoiDatabase::addPoi(CPOI const& poi)
     * @description : Add POI's to database.
     */
	void addPoi(CPOI const& poi);

    /* @methodName : CPoiDatabase::getPointerToPoi(string name)
     * @description : Check the input parameter if present in the database, else return error.
     * @paramOutput : Returns the address of the POI
     */
	CPOI* getPointerToPoi(string name);

	/* @methodName : CPoiDatabase::print(ostream& out) const
	 * @description : Prints the content of the poi database
	 */
	void print(ostream& out) const;

	/* @methodName : CPoiDatabase::printpoistorage() const
	 * @description : Prints the content of the poi database
	 */
	void printpoistorage() ;
	void poiclear();
};

#endif /* CPOIDATABASE_H_ */
