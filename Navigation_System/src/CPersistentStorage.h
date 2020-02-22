/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPERSISTENTSTORAGE.H
* Author          :
* Description     :
*
*
****************************************************************************/

#ifndef CPERSISTENTSTORAGE_H
#define CPERSISTENTSTORAGE_H

#include <cstring>
#include <ostream>
#include <fstream>
#include "CWpDatabase.h"
#include "CPoiDatabase.h"

class CPersistentStorage {

public:
/* @methodName : ~CPersistentStorage(){}
 * @description : Destructor - to delete allocated memory when the object of the class is destroyed.
 */
virtual ~CPersistentStorage(){}

/**
* Set the name of the media to be used for persistent storage.
* The exact interpretation of the name depends on the implementation
* of the component.
* @param name the media to be used
*/
virtual void setMediaName(std::string name) = 0;

/**
* Write the data to the persistent storage.
* @param waypointDb the data base with way points
* @param poiDb the database with points of interest
* @return true if the data could be saved successfully
*/
virtual bool writeData (const CWpDatabase& waypointDb, const CPoiDatabase& poiDb) = 0;
/**
* The mode to be used when reading the data bases.
*/
enum MergeMode { MERGE, REPLACE };

/*
* @param waypointDb the the data base with way points
* @param poiDb the database with points of interest
* @param mode the merge mode
* @return true if the data could be read successfully
*/
virtual bool readData (CWpDatabase& waypointDb, CPoiDatabase& poiDb, MergeMode mode) = 0;

};
/********************
**  CLASS END
*********************/
#endif /* CPERSISTENTSTORAGE_H */
