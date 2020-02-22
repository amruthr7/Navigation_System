/*
 * CPOI.h
 *
 *  Created on: 27-Oct-2017
 *      Author: AMRUTH
 */


#ifndef CPOI_H_
#define CPOI_H_

#include <cstring>
#include <ostream>
#include "CWaypoint.h"

using namespace std;

typedef enum { RESTAURANT, TOURISTIC, GASSTATION, UNIVERSITY }t_poi; 	//defining the 4 type of POI's using enum

class CPOI : public CWaypoint
{

private:
	t_poi m_type;
	string m_description;
public:

    /* @methodName : CPOI::CPOI(t_poi type, string name, string description, double latitude, double longitude)
     * @description : Constructor - Define and initialize the input parameters.
     */
	CPOI(t_poi m_type=RESTAURANT, string name="", string description="", double latitude=0, double longitude=0);

	/* @methodName : CPOI::~CPOI()
	 * @description : Destructor - to delete allocated memory when the object of the class is destroyed.
	 */
	virtual ~CPOI();

    /* @methodName : CPOI::print(ostream& out,int format) const
     * @description : prints the type of POI along with the description
     */
	virtual void print(ostream& out, int format) const;

	/* @methodName : ostream& operator<<(ostream& out, const CPOI & poi1)
	 * @description : Overloaded operator for <<
	 */
	friend ostream& operator<<(ostream& out, const CPOI & poi1);

    /* @methodName : CPOI::getAllDataByReference(t_poi &type, string &name, string &description ,double &latitude, double &longitude)
     * @description : Returns the type, name, description, latitude and longitude of the object that is called.
     */
	void getAllDataByReference(t_poi &type, string &name, string &description ,double &latitude, double &longitude);

	/* @methodName : CPOI::getType() const
	 * @description : Returns the type of poi
	 * @paramOutput : string type
	 */
	 string getType() const;

	 /* @methodName : CPOI::getDescription() const
	 * @description : Returns the description of the poi
	 * @paramOutput : string description
	 */
	string getDescription() const;
};

#endif /* CPOI_H_ */
