/*
 * CWaypoint.h
 *
 *  Created on: 23-Oct-2017
 *      Author: AMRUTH
 */

#ifndef CWAYPOINT_H_
#define CWAYPOINT_H_

#include <iostream>
#include <ostream>
#include <stdlib.h>
#include <cstring>

using namespace std;

class CWaypoint
{

private:
    double m_longitude;
    double m_latitude;
    string m_name;
   //wp_type m_type;

	/* @methodName : CWaypoint::transformLongitude2degmmss(int & deg, int & mm, double & ss)
	 * @description : Converts the value of longitude to degree, mins and sec format
	 */
	void transformLongitude2degmmss(int & deg, int & mm, double & ss) const;

	/* @methodName : CWaypoint::transformLatitude2degmmss(int & deg, int & mm, double & ss)
	 * @description : Converts the value of latitude to degree, mins and sec format
	 */
	void transformLatitude2degmmss(int & deg, int & mm, double & ss) const;


public:

	/* @methodName : CWaypoint::CWaypoint(string name, double latitude, double longitude)
	 * @description : Constructor - Define and initialize the input parameters.
	 */
	CWaypoint(string name = "default", double latitude = 0, double longitude = 0);

	/* @methodName : CWaypoint::~CWaypoint()
	 * @description : Destructor - to delete allocated memory when the object of the class is destroyed.
	 */
	virtual ~CWaypoint();

	/* @methodName : CWaypoint::set(string name, double latitude, double longitude)
	 * @description : Set Values for all the attributes by defining a range.
	 */
	void set(string name, double latitude, double longitude);

	/* @methodName : CWaypoint::getName()
	 * @description : Returns the name of the object
	 * @paramOutput : string name
	 */
	string getName() const;

	/* @methodName : CWaypoint::getLatitude()
	 * @description : Returns the latitude of the object
	 * @paramOutput : double latitude
	 */
	double getLatitude() const;

	/* @methodName : CWaypoint::getLongitude()
	 * @description : Returns the longitude of the object
	 * @paramOutput : double longitude
	 */
	double getLongitude() const;

	/* @methodName : CWaypoint::getAllDataByReference(string &name, double &latitude, double &longitude)
	 * @description : Returns the name, latitude and longitude of the object that is called.
	 */
	void getAllDataByReference(string &name, double &latitude, double &longitude);

	/* @methodName : CWaypoint::calculateDistance(const CWaypoint &wp)
	 * @description : Calculate the distance between the 2 waypoints
	 * @paramOutput : double Distance
	 */
	double calculateDistance(const CWaypoint &wp);

	/* @methodName : CWaypoint::print(ostream& out,int format)
	 * @description : Prints the values of the attributes in the specified format
	 */
	virtual void print(ostream& out, int format) const;

	/* @methodName : ostream& operator<<(ostream& out, const CWaypoint& wp1)
	 * @description : Overloaded operator for <<
	 */
	friend ostream& operator<<(ostream& out, const CWaypoint & wp1);
};

#endif /* CWAYPOINT_H_ */
