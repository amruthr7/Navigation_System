/*
 * CRoute.h
 *
 *  Created on: 27-Oct-2017
 *      Author: AMRUTH
 */

#ifndef CROUTE_H_
#define CROUTE_H_

#include <cstring>
#include "CPOI.h"
#include "CPoiDatabase.h"
#include "CWpDatabase.h"
#include "CJsonPersistence.h"
#include <list>
#include <vector>

using namespace std;

class CPOI;
class CWaypoint;
class CPoiDatabase;

class CRoute
{


private:
    /**
     * @supplierCardinality 0..*
     * @link aggregationByValue
     * @clientCardinality 1 
     */
	CPoiDatabase* m_pPoiDatabase;
	CWpDatabase* m_pWpDatabase;
	list<CWaypoint*> myRoute;


//	vector<CWaypoint*> myRoute;

public:

    /* @methodName : CRoute::CRoute(unsigned int maxWp, unsigned int maxPoi)
     * @description : Constructor - Define and initialize the input parameters.
     */
	CRoute(unsigned int maxWp=4, unsigned int maxPoi=10);

    /* @methodName : CRoute::CRoute(CRoute const &origin)
     * @description : Copy Constructor - copy and initializing the object in the same class.
     */
	CRoute(const CRoute& origin);

    /* @methodName : CRoute::~CRoute()
     * @description : Destructor - to delete allocated memory when the object of the class is destroyed.
     */
	~CRoute();

	/* @methodName : CRoute& CRoute::operator=(const CRoute& croute)
	 * @description : Overloaded operator for =
	 * @paramOutput : return CRoute object
	 */
	CRoute& operator=(const CRoute& croute);

	/* @methodName : CRoute CRoute::operator+(const CRoute& routeadd)
	 * @description : Overloaded operator for =
	 * @paramOutput : return CRoute object
	 */
	CRoute operator+(const CRoute& routeadd);

	/* @methodName : CRoute CRoute::operator +=(string name)
	 * @description : Overloaded operator for +=
	 * @paramOutput : return CRoute object
	 */
	CRoute operator +=(string name);

	/* @methodName : CRoute::connectToPoiDatabase(CPoiDatabase* pPoiDB)
	 * @description : Connect the route to POI Database.
	 */
	void connectToPoiDatabase(CPoiDatabase* pPoiDB);

	/* @methodName : CRoute::connectToWpDatabase(CWpDatabase* pWpDB)
	 * @description : Connect the route to WP Database.
	 */
	void connectToWpDatabase(CWpDatabase* pWpDB);

	/* @methodName : CRoute::addWaypoint(string name)
	 * @description : Add the waypoints to the route.
	 */
	void addWaypoint(string name);

    /* @methodName : CRoute::addPoi(string namePoi,string afterWp)
     * @description : Add POI's to database.
     */
	void addPoi(string namePoi, string afterWp);

    /* @methodName : CRoute::getDistanceNextPoi(CWaypoint const &wp, CPOI &poi)
     * @description : For a specific Waypoint, the distance to all poi's are calculated
     *  and the distance to nearest poi is returned.
     *  @paramOutput : double distance
     */
	double getDistanceNextPoi(CWaypoint const &wp, CPOI &poi);

    /* @methodName : CRoute::print()
     * @description : Prints the number of waypoints and POI's, and the latitude and longitude of the waypoints.
     */
	void print();

	/* @methodName : const std::vector<const CWaypoint*> CRoute::getRoute()
	 * @description : Gets the route
	 */
	const std::vector < const CWaypoint*> getRoute();
};

#endif /* CROUTE_H_ */
