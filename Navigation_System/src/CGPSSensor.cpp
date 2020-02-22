/*
 * CGPSSensor.cpp
 *
 *  Created on: 27-Oct-2017
 *      Author: AMRUTH
 */

#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <math.h>
#include "CGPSSensor.h"

using namespace std;

CGPSSensor::CGPSSensor(){}

//Input the current position via keyboard
CWaypoint CGPSSensor::getCurrentPosition()
{
	CWaypoint current_location;
	string position;
	double latitude;
	double longitude;

	//to prompt user to input the current position, latitude and longitude in the defined range.
	do
	{
		cout << "GPS SENSOR" << endl
				<< "Please enter your 1. Current position, 2. Latitude"
						" and 3. Longitude in the same order" << endl;
		cin >> position >> latitude >> longitude;
	} while (!((latitude >= -90 && latitude <= 90) && (longitude >= -180 && longitude <= 180)));

	current_location.set(position, latitude, longitude);
	//cout<< "Your current location is : " << position << " , " << latitude << " , "<< longitude << endl;

	return current_location;
}

