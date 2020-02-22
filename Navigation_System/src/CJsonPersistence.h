/*
 * CJsonPersistence.h
 *
 *  Created on: 10-Jan-2018
 *      Author: AMRUTH
 */

#ifndef MYCODE_CJSONPERSISTENCE_H_
#define MYCODE_CJSONPERSISTENCE_H_


#include <cstring>
#include <ostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <map>
#include "CPersistentStorage.h"


enum t_event {waitfor_first_token,waitfor_name_db,waitfor_name_sep,waitfor_begin_db,waitfor_att_name,
	waitfor_value,waitfor_value_sep,waitfor_end_db,waitfor_end_obj};

/*Double quotes*/
#define DQ '"'
/*Space*/
#define SPACE ' '

class CJsonPersistence:public CPersistentStorage
{
private:
	std::string m_file;

public:

		/* @methodName : CJsonPersistence::CJsonPersistence()
		 * @description : Constructor - Define and initialize the input parameters.
		 */
		CJsonPersistence();

		/* @methodName : CJsonPersistence::~CJsonPersistence()
		 * @description : Destructor - to delete allocated memory when the object of the class is destroyed.
		 */
		virtual ~CJsonPersistence();

		/* @methodName : CJsonPersistence::setMediaName(std::string name)
		 * @description : Sets the file name to which the information has to be written or read from
		 */
		void setMediaName(std::string name);

		/* @methodName : CJsonPersistence::writeData(const CWpDatabase& wpDb, const CPoiDatabase& poiDb)
		 * @description : Write data to the file
		 */
		bool writeData(const CWpDatabase& wpDb, const CPoiDatabase& poiDb);

		/* @methodName : CJsonPersistence::readData(CWpDatabase& waypointDb, CPoiDatabase& poiDb,MergeMode mode)
		 * @description : Read data from the file and store the content in the respective Databases
		 */
		bool readData(CWpDatabase& waypointDb, CPoiDatabase& poiDb, MergeMode mode);

};

#endif /* MYCODE_CJSONPERSISTENCE_H_ */
