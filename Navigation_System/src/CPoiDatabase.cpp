/*
 * CPoiDatabase.cpp
 *
 *  Created on: 27-Oct-2017
 *      Author: AMRUTH
 */

#include <iostream>
#include <cstring>
#include "CPoiDatabase.h"
using namespace std;


CPoiDatabase::CPoiDatabase()
{

}

//add POI's to database
void CPoiDatabase::addPoi(CPOI const& poi)
{
CTempClass::addValue(poi);
/*
	m_POI.insert(pair<string, CPOI>(poi.getName(), poi));
	//cout << poi.getName() << " : POI added to DB"<<endl;
*/
}

//Validate if the name of POI is present in database
CPOI* CPoiDatabase::getPointerToPoi(string name)
{
return CTempClass::getPointerToVal(name);

}


//print contents of the DB
void CPoiDatabase::print(ostream& out) const
{
	/*map<string, CPOI>::const_iterator i;
	for (i = m_POI.begin(); i != m_POI.end(); i++)
	{
		out << (i->second.getName());
		out << ";";
		out << (i->second.getType());
		out << ";";
		out << (i->second.getDescription());
		out << ";";
		out << (i->second.getLatitude());
		out << ";";
		out << (i->second.getLongitude());
		out << endl;
	}*/
}


//print contents of the DB
void CPoiDatabase::printpoistorage()
{
	CTempClass::printValue();
	/*cout << "the content in poi db are : " << endl;
	map<string, CPOI>::const_iterator i;
	for (i = m_POI.begin(); i != m_POI.end(); i++)
	{
		cout << (i->second.getName());
		cout << ";";
		cout << (i->second.getType());
		cout << ";";
		cout << (i->second.getDescription());
		cout << ";";
		cout << (i->second.getLatitude());
		cout << ";";
		cout << (i->second.getLongitude());
		cout << endl;
		cout << "===========" << endl;
	}
	//cout << m_POI <<endl;*/
}

void CPoiDatabase::poiclear()
{
	CTempClass::cleardb();
//	m_POI.clear();
}
