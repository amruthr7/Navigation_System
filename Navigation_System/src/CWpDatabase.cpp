/*
 * CWpDatabase.cpp
 *
 *  Created on: 22-Nov-2017
 *      Author: AMRUTH
 */

#include <iostream>
#include <cstring>
#include "CWpDatabase.h"
#include <map>
using namespace std;

CWpDatabase::CWpDatabase()
{

}

//add WP's to database
void CWpDatabase::addWaypoint(CWaypoint const& wp){
	CTempClass::addValue(wp);
/*
	m_wp.insert(pair<string, CWaypoint>(wp.getName(), wp));
	//cout <<wp.getName() << " : WP added to DB" << endl;
*/
}

//Validate if the name of wp is present in database
CWaypoint* CWpDatabase::getPointerToWaypoint(string name)
{
	return CTempClass::getPointerToVal(name);
/*
	map<string, CWaypoint>::iterator i;
	for (i = m_wp.begin(); i != m_wp.end(); i++)
	{
		if (i->first == name)
		{
			//Return the int identifier
			return &(i->second);
		}
		else
		 {
		 cout << "the wp is not present in db!" << endl;
		 }
	}
*/
	//return name;

}

//print contents of the db : Being used to write the contents of DB to an external file
void CWpDatabase::print(ostream& out) const
{
	/*map<string, CWaypoint>::const_iterator i;
	for (i = m_wp.begin(); i != m_wp.end(); i++)
		{
			out << (i->second.getName());
			out << ";";
			out << (i->second.getLatitude());
			out << ";";
			out << (i->second.getLongitude());
			out << endl;
		}*/
}

//print contents of the db
void CWpDatabase::printwpstorage()
{
	CTempClass::printValue();
/*
	cout << "the content in wp db are : " << endl;
	map<string, CWaypoint>::const_iterator i;
	for (i = m_wp.begin(); i != m_wp.end(); i++)
	{
		cout << (i->second.getName());
		cout << ";";
		cout << (i->second.getLatitude());
		cout << ";";
		cout << (i->second.getLongitude());
		cout << endl;
		cout << "===========" << endl;
	}
	//cout << " " << m_wp << endl;
*/
}

void CWpDatabase::wpclear()
{
	CTempClass::cleardb();
//m_wp.clear();
}
