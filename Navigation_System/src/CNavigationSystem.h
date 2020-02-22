/*
 * CNavigationSystem.h
 *
 *  Created on: 27-Oct-2017
 *      Author: AMRUTH
 */

#ifndef CNAVIGATIONSYSTEM_H_
#define CNAVIGATIONSYSTEM_H_
#include "CRoute.h"
#include "CGPSSensor.h"
#include "CWpDatabase.h"
#include "CStorageNavigation.h"

class CNavigationSystem
{
private:

	//Define parameters for CGPS Sensor, CRoute, CPoiDatabase and CWpDatabase

    /**
     * @link aggregationByValue
     * @supplierCardinality 1
     * @clientCardinality 1 
     */
	CGPSSensor m_GPSSensor;
    /**
     * @link aggregationByValue
     * @clientCardinality 1
     * @supplierCardinality 1 
     */
    CRoute m_route;
    /**
     * @link aggregationByValue
     * @supplierCardinality 1
     * @clientCardinality 1 
     */
    CPoiDatabase m_PoiDatabase;

    CWpDatabase m_WpDatabase;

	/* @methodName : CNavigationSystem::printDistanceCurPosNextPoi()
     * @description : Calculates the distance between current position and all POI's. Returns the distance to nearest POI.
     */
    void printDistanceCurPosNextPoi();

	/* @methodName : CNavigationSystem::printRoute()
     * @description : print all POI's and waypoints of the route
     */
    void printRoute();

	/* @methodName : CNavigationSystem::enterRoute()
     * @description : Add waypoints, POI's and connect to Database
     */
    void enterRoute();

public:

    /* @methodName : CNavigationSystem::CNavigationSystem()
     * @description : Constructor
     */
    CNavigationSystem();

	/* @methodName : CNavigationSystem::run()
     * @description : Run the navigation system for all waypoints, POI's and current location.
     */
    void run();

};

#endif /* CNAVIGATIONSYSTEM_H_ */
