/*
 * CWaypoint.cpp
 *
 *  Created on: 23-Oct-2017
 *      Author: AMRUTH
 */

#include <iostream>
#include <cstring>
#include <ostream>
#include <stdlib.h>
#include <math.h>
#include "CWaypoint.h"

#define SHOWADDRESS		//1.1 c
#define DEGREE 60		//#define constants (1.1e)
#define MMSS 3600		//Since its a definition, we define it in the .cpp file
#define PI 3.14159		//PI
#define RADIUS 6378.17  //Radius of the Earth

using namespace std;

CWaypoint::CWaypoint(string name, double latitude, double longitude)
{
	m_name = name;
	m_latitude = latitude;
	m_longitude = longitude;
//	m_type = wp_type;

/*
	#ifdef SHOWADDRESS							//1.1 c - Verbose mode on
	cout << "the address of the object "<< name << " is " << this << endl;

	//Print address and value of the attributes.
	cout << "Address of Name is "<< &m_name <<" and its value is "<< m_name << endl;
	cout << "Address of Longitude is " << &m_longitude <<" and its value is "<< m_longitude<< endl;
	cout << "Address of Latitude is " << &m_latitude << " and its value is "<< m_latitude << endl;

	//Print the memory occupied by the attributes
	cout << "the size of parameter name is: " << sizeof(m_name) << endl;
    cout << "the size of parameter latitude is: " << sizeof(m_latitude) << endl;
	cout << "the size of parameter longitude is: " << sizeof(m_longitude) << endl;
	//COMMENT : the memory occupied by all attributes is given by sizeof function.

	 #endif
*/

	 #ifndef SHOWADDRESS						//Verbose mode off
	 cout<<"The Verbose mode is Off!" << endl;
	 #endif

}

CWaypoint::~CWaypoint(){}

void CWaypoint::set(string name, double latitude, double longitude)
{
	if ((latitude >= -90 && latitude <= 90)&& (longitude >= -180 && longitude <= 180))	//<--latitudes and longitudes exist in this range
	{
		m_name = name;
		m_latitude = latitude;
		m_longitude = longitude;
	}
	else
	{
		m_name = name;
		m_latitude = 0;
		m_longitude = 0;
	}
	//cout<< m_name << " on latitude = " << m_latitude << " and longitude = "<< m_longitude << endl;
}

string CWaypoint::getName() const
{
	return m_name;
}

double CWaypoint::getLatitude() const
{
	//cout << "The latitude of "<< m_name <<" on latitude " << m_latitude << endl;
	return m_latitude;
}

double CWaypoint::getLongitude() const
{
	//cout << "The longitude of "<< m_name <<" on latitude " << m_longitude << endl;
	return m_longitude;
}

// Print the latitude and longitude for the format type
void CWaypoint::print(ostream& out,int format) const
{
	int deg, mm;
	double ss;
	{
		switch (format)
		{
		case 1:						//print latitude and longitude in decimals format
			out << m_name << " on latitude = " << m_latitude << " and longitude = " << m_longitude << endl;
			break;
		case 2:						//print latitude and longitude in deg/min/ss format
			transformLatitude2degmmss(deg, mm, ss);
			out << m_name << " on latitude = " << abs(deg) << "deg " << abs(mm) << "min " << abs(ss) << "s and ";
			transformLongitude2degmmss(deg, mm, ss);
			out << " on longitude = " << abs(deg) << "deg " << abs(mm) << "min " << abs(ss) << "s "<< endl;
			out<< "=====================";
			break;
		default:
			out << "Incorrect format! " << endl;
		}
	}
}

//overloaded << operator
ostream& operator<<(ostream& out, const CWaypoint& wp1)
{
	wp1.print(out,2);
	return out;
}

// transform the latitude from decimals to degree, mins and sec
void CWaypoint::transformLatitude2degmmss(int &deg, int &mm, double &ss) const
{
	deg = int(m_latitude);
	mm = int((m_latitude - deg) * DEGREE);
	ss = MMSS * (m_latitude - deg) - (mm * DEGREE);
}

// transform the longitude from decimals to degree, mins and sec
void CWaypoint::transformLongitude2degmmss(int &deg, int &mm, double &ss) const
{
	deg = int(m_longitude);
	mm = int((m_longitude - deg) * DEGREE);
	ss = MMSS * (m_longitude - deg) - (mm * DEGREE);
}
void CWaypoint::getAllDataByReference(string &name, double &latitude, double &longitude)
{
	name = m_name;
	latitude = m_latitude;
	longitude = m_longitude;
	cout << "the address of " << name << " is " << &name << " , " << &latitude << " and " << &longitude << endl;
}

//calculate the distance between 2 waypoints
double CWaypoint::calculateDistance(const CWaypoint &wp)
{
	double D;
	D = RADIUS* (acos(((sin(m_latitude * PI / 180))* (sin(wp.m_latitude * PI / 180)))+ ((cos(m_latitude * PI / 180))
					* (cos(wp.m_latitude * PI / 180))* (cos((wp.m_longitude - m_longitude) * PI/ 180)))));
	cout << "The distance between "<< wp.m_name << " and " << m_name << " is : " << D << endl;
	return D;
}
