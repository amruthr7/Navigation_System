/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CSTORAGENAVIGATION.H
* Author          :
* Description     :
*
*
****************************************************************************/

#ifndef CSTORAGENAVIGATION_H
#define CSTORAGENAVIGATION_H

#include <cstring>
#include <ostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "CPersistentStorage.h"

#define wpparam 3						//maximum number of parameters in wp
#define poiparam 5						//maximum number of parameters in poi

enum MergeMode { MERGE, REPLACE };		//The mode to be used when reading the data bases.

class CStorageNavigation
{

private:
	std::string m_wpStorageNavigation;
	std::string m_poiStorageNavigation;

public:

	/* @methodName : CStorageNavigation::CStorageNavigation()
	 * @description : Constructor - Define and initialize the input parameters.
	 */
	CStorageNavigation();

	/* @methodName : CStorageNavigation::~CStorageNavigation(){}
	 * @description : Destructor - to delete allocated memory when the object of the class is destroyed.
	 */
	virtual ~CStorageNavigation();

	/* @methodName : CStorageNavigation:: setMediaName(std::string name)
	 * @description : Sets the file name to which the information has to be written or read from
	 */
	void setMediaName(std::string name);

	/* @methodName : CStorageNavigation:: writeData (const CWpDatabase& waypointDb, const CPoiDatabase& poiDb)
	 * @description : Write data to the file
	 */
	bool writeData(const CWpDatabase& waypointDb, const CPoiDatabase& poiDb);

	/* @methodName : CStorageNavigation::readData (CWpDatabase& waypointDb, CPoiDatabase& poiDb, MergeMode mode)
	 * @description : Read data from the file and store the content in the respective Databases
	 */
	bool readData(CWpDatabase& waypointDb, CPoiDatabase& poiDb, MergeMode mode);

	/* @methodName : CStorageNavigation::checkDigits(string a)
	 * @description : Check if the string has digits/alphabetic
	 */
	bool checkDigits(string param);

	/* @methodName : CStorageNavigation::checkDelim(string& myline, int maxparams)
	 * @description : Check if the file is read correctly for an incorrect delimiter
	 * @Example - If a comma is present instead of a dot in a latitude/longitude
	 */
	void checkDelim(string& myline, int maxparams);

};
/********************
**  CLASS END
*********************/
#endif /* CSTORAGENAVIGATION_H */
