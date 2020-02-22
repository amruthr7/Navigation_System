/*
 * CPOI.cpp
 *
 *  Created on: 27-Oct-2017
 *      Author: AMRUTH
 */

#include <iostream>
#include <ostream>
#include <cstring>
#include <stdlib.h>
#include "CPOI.h"
#include "CWaypoint.h"

using namespace std;


CPOI::CPOI(t_poi type, string name, string description, double latitude, double longitude)
{
	m_type = type;
	m_description = description;
	set(name, latitude, longitude);			//setting values of name, latitude and longitude by inheriting CWaypoint class
}

CPOI::~CPOI()
{

}

//print POI type and description
void CPOI::print(ostream& out,int format) const
{
	//cout << "POINT OF INTEREST" << endl << "=====================" << endl;
	switch (m_type)
	{
	case RESTAURANT:
		out << "of type Restaurant : " << m_description << "." << endl;
		break;
	case TOURISTIC:
		out << "of type Touristic : " << m_description << "." << endl;
		break;
	case GASSTATION:
		out << "of type Gas station : " << m_description << "." << endl;
		break;
	case UNIVERSITY:
		out << "of type University : " << m_description << "." << endl;
		break;
	default:
		out << "Please enter a correct POI! " << endl;
	}
	CWaypoint::print(out,2);		//print the latitude and longitude in the degree, mins and sec format.*/
}

//Overloaded << operator
ostream& operator<<(ostream& out, const CPOI & poi1){
	poi1.print(out, 2);
	return out;
}

void CPOI::getAllDataByReference(t_poi &type, string &name, string &description ,double &latitude, double &longitude)
{
	type = m_type;
	name = CWaypoint::getName();
	description = m_description;
	latitude = CWaypoint::getLatitude();
	longitude = CWaypoint::getLongitude();
}

string CPOI::getType() const
{
	switch (m_type)
	{
		case RESTAURANT:
			return "RESTAURANT";
			break;
		case TOURISTIC:
			return "TOURISTIC";
			break;
		case GASSTATION:
			return "GASSTATION";
			break;
		case UNIVERSITY:
			return "UNIVERSITY";
			break;
		default:
			return "DEFAULT";
	}
}

string CPOI::getDescription() const
{
	return this->m_description;
}
