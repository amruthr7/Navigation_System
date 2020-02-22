/*
 * CGPSSensor.h
 *
 *  Created on: 27-Oct-2017
 *      Author: AMRUTH
 */

#ifndef CGPSSENSOR_H_
#define CGPSSENSOR_H_
#include "CWaypoint.h"

class CGPSSensor
{
public:

/* @methodName : CGPSSensor::CGPSSensor()
 * @description : Constructor
 */
    CGPSSensor();

/* @methodName : CGPSSensor::getCurrentPosition()
 * @description : User enters the current position by providing the name, latitude and longitude
 * @paramOutput : Returns current location. Output parameter of type - CWaypoint
 */
    CWaypoint getCurrentPosition();
};

#endif /* CGPSSENSOR_H_ */
