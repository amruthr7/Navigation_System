/*
 * CRoute.cpp
 *
 *  Created on: 27-Oct-2017
 *      Author: AMRUTH
 */

#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <math.h>
using namespace std;
#include "CRoute.h"
#include "CWaypoint.h"
#include "CPOI.h"
#include "CPoiDatabase.h"

CRoute::CRoute(unsigned int maxWp, unsigned int maxPoi)
{
	m_pPoiDatabase = 0;
	m_pWpDatabase = 0;
}

//Copy constructor - Deep copy and initializing the CRoute object.
CRoute::CRoute(const CRoute& origin)
{
	m_pPoiDatabase = 0;
	m_pWpDatabase = 0;

	list<CWaypoint*>::const_iterator i;
	for (i=origin.myRoute.begin(); i != origin.myRoute.end(); i++)
	{
		this->myRoute.push_back(*i);
	}
}

//Destructor
CRoute::~CRoute()
{

}

// Operational operator for = : Copies the content of a route to another route.
CRoute& CRoute::operator=(const CRoute& croute)
{
	list<CWaypoint*>::const_iterator i;
	this->myRoute.clear();
	for (i = croute.myRoute.begin(); i != croute.myRoute.end(); i++)
	{
		this->myRoute.push_back(*i);
		//cout << "assignment op1" << endl;
	}
	return *this;
}

// Operational operator for + : Adds 2 routes.
CRoute CRoute::operator +(const CRoute& routeadd)
{
	if ((routeadd.m_pWpDatabase == this->m_pWpDatabase)
			&& (routeadd.m_pPoiDatabase == this->m_pPoiDatabase))
	{
		list<CWaypoint*>::const_iterator i = myRoute.end();
		CRoute var = routeadd;
		list<CWaypoint*>::const_iterator j = routeadd.myRoute.begin();
		for (; j != routeadd.myRoute.end(); ++j)
		{
			this->myRoute.push_back(*j);
			//cout << "add operator" << endl;
		}
		return *this;
	}
	else
	{
		cout << "ERROR : the routes that you are trying to add belong to different db's!" << endl;
		return *(new CRoute);
	}

}

// Operational operator for += : Adds a WP/POI (as a string) to the end of the route.
CRoute CRoute::operator +=(string name)
{
	CPOI* var1;
	CWaypoint* var2;
	if ((m_pPoiDatabase == NULL) || (m_pWpDatabase == NULL))
	{
		cout << "db not connected!" << endl;
	}
	else
	{
		var1 = m_pPoiDatabase->getPointerToPoi(name);
		var2 = m_pWpDatabase->getPointerToWaypoint(name);

		if ((m_pWpDatabase->getPointerToWaypoint(name) != NULL)
				&& (m_pPoiDatabase->getPointerToPoi(name) != NULL))
		{
			myRoute.push_back(var2);
			cout << name << " (wp) added to route." << endl;
			myRoute.push_back(var1);
			cout << name << " (poi) added to route." << endl;
		}
		else if ((m_pWpDatabase->getPointerToWaypoint(name) != NULL)
				&& (m_pPoiDatabase->getPointerToPoi(name) == NULL))
		{
			myRoute.push_back(var2);
			cout << name << " (wp) added to route" << endl;
		}
		else if ((m_pWpDatabase->getPointerToWaypoint(name) == NULL)
				&& (m_pPoiDatabase->getPointerToPoi(name) != NULL))
		{
			myRoute.push_back(var1);
			cout << name << " (poi) added to route" << endl;
		}
		else if ((m_pWpDatabase->getPointerToWaypoint(name) == NULL)
				&& (m_pPoiDatabase->getPointerToPoi(name) == NULL))
		{
			cout << name << " doesnt exist either in WP db or in POI db!"<< endl;
		}
	}
	return *this;
}

void CRoute::connectToPoiDatabase(CPoiDatabase* pPoiDB)
{
	if (pPoiDB == 0)
	{
		cout << "ERROR : Database is empty!" << endl;
	}
	else
	{
		m_pPoiDatabase = pPoiDB;
	}
}

void CRoute::connectToWpDatabase(CWpDatabase* pWpDB)
{

	if (pWpDB == 0)
	{
		cout << "ERROR : Database is empty!" << endl;
	}
	else
	{
		m_pWpDatabase = pWpDB;
	}

}

//add the waypoints to the route
void CRoute::addWaypoint(string name)
{
	CWaypoint* myWp;
	if (m_pWpDatabase == NULL)
	{
		cout << "Error: Database is not connected!" << endl;
	}
	else
	{
		myWp = m_pWpDatabase->getPointerToWaypoint(name);
		if (myWp != NULL)
		{
			myRoute.push_back(m_pWpDatabase->getPointerToWaypoint(name));
			//myRoute.push_back(myWp);
			//cout << name << " : Waypoint added to the route!" << endl;
		}
		else
		{
			cout << "No such waypoint present in DB!" << endl;
		}
	}
}

//add the POI's to the database
void CRoute::addPoi(string namePoi, string afterWp)
{
	if (m_pPoiDatabase == NULL)
	{
		cout << "Error: Database is not connected!" << endl;
	}
	else
	{
		CWaypoint* p;
		//int flag = 0;
		list<CWaypoint*>::iterator i;
		for (i = myRoute.begin(); i != myRoute.end(); ++i)
		{
			if (m_pWpDatabase->getPointerToWaypoint(afterWp) != NULL)
			{
				p = m_pPoiDatabase->getPointerToPoi(namePoi);
				if (p != 0)
				{
					myRoute.insert(++i,
							m_pPoiDatabase->getPointerToPoi(namePoi));
					//cout << namePoi << " : POI is added to the route." << endl;
					return;
				}
				else
				{
					cout << namePoi << "  : No such POI is present in the db."
							<< endl;
					return;
				}
			}
			else
			{
				if (m_pPoiDatabase->getPointerToPoi(namePoi) != NULL)
				{
					cout << afterWp<< " : there is no such waypoint present. Please enter a correct Waypoint first."<< endl;
					return;
				}
				else
				{
					cout << "No such WP or POI exists in the db! " << endl;
					return;
				}
			}
		}
	}
}

//Calculate the nearest POI to the waypoint
double CRoute::getDistanceNextPoi(CWaypoint const &wp, CPOI &poi)
{
	double dist_min = 10000000;
	//int d=0;
	double calculate_dist = 0;
	list<CWaypoint*>::iterator i;
	for (i = myRoute.begin(); i != myRoute.end(); i++)
	{
		CPOI* pPoi = dynamic_cast<CPOI*>(*i);
		if (pPoi != NULL)
		{

			calculate_dist = pPoi->calculateDistance(wp);
			if (calculate_dist < dist_min)
			{
				dist_min = calculate_dist;
				poi = *pPoi;
			}
		}
	}
	cout << "Distance to next POI is : " << dist_min << endl;
	return dist_min;
}

//Print the waypoints and POI's
void CRoute::print()
{
	cout << "The route has the following WP's and/or POI's : " <<endl;
	list<CWaypoint*>::const_iterator i;
	for (i = myRoute.begin(); i != myRoute.end(); ++i)
	{
		CPOI* poiobject = dynamic_cast<CPOI*>(*i);	//Dynamic casting : Differentiating between CPOI and WP for print during runtime
		if (poiobject != 0)
		{
			cout << (**i) << endl;
		}
		else
		{
			cout << (**i) << endl;
/*
 * Since we have to print the contents of the waypoint, we perform double dereferencing.
 * Single dereference accesses the address of Waypoint and the double dereference accesses the parameters present in the Waypoint.
 * Hence, we use the double dereference.
 */
		}
	}
}


// getRoute
const std::vector<const CWaypoint*> CRoute::getRoute() {
	vector<const CWaypoint*> myRoute(this->myRoute.begin(),this->myRoute.end());
		return myRoute;
}
