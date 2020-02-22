/*
 * CJsonPersistence.cpp
 *
 *  Created on: 10-Jan-2018
 *      Author: AMRUTH
 */

#include <cstring>
#include <ostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <map>
#include "CJsonPersistence.h"
#include "CJsonScanner.h"
#include "CJsonToken.h"

using namespace APT;
using namespace std;

CJsonPersistence::CJsonPersistence()
{
}

void CJsonPersistence::setMediaName(std::string name)
{
	m_file = name + "-json.txt";
}

CJsonPersistence::~CJsonPersistence()
{
}

//write the data from the database to the file
bool CJsonPersistence::writeData(const CWpDatabase& wpDb,
		const CPoiDatabase& poiDb)
{
	ofstream file;
	bool flag = false;

	file.open(this->m_file.data());
	file.seekp(0);					//starts from the beginning of the file
	if (file.is_open())
	{
		map<string, CWaypoint>::const_iterator i;
		file << "{" << endl;
		file << SPACE << SPACE << DQ << "waypoints" << DQ << ": [" << endl;
		for (i = wpDb.m_val.begin(); i != wpDb.m_val.end(); ++i)
		{
			file << "\t" << "{ " << endl;
			file << "\t  " << DQ << "name" << DQ << ": " << DQ
					<< (i->second.getName()) << DQ << "," << endl;
			file << "\t  " << DQ << "latitude" << DQ << ": "
					<< (i->second.getLatitude()) << "," << endl;
			file << "\t  " << DQ << "longitude" << DQ << ": "
					<< (i->second.getLongitude()) << endl;
			file << "\t" << "}";
			if (i != --wpDb.m_val.end())
			{
				file << "," << endl;
			}
		}
		file << endl;
		file << SPACE << " ]," << endl;

		map<string, CPOI>::const_iterator j;
		file << SPACE << SPACE << DQ << "pois" << DQ << ": [" << endl;
		for (j = poiDb.m_val.begin(); j != poiDb.m_val.end(); j++)
		{
			file << "\t" << "{ " << endl;
			file << "\t  " << DQ << "name" << DQ << ": " << DQ
					<< (j->second.getName()) << DQ << "," << endl;
			file << "\t  " << DQ << "latitude" << DQ << ": "
					<< (j->second.getLatitude()) << "," << endl;
			file << "\t  " << DQ << "longitude" << DQ << ": "
					<< (j->second.getLongitude()) << "," << endl;
			file << "\t  " << DQ << "type" << DQ << ": " << DQ
					<< (j->second.getType()) << DQ << "," << endl;
			file << "\t  " << DQ << "description" << DQ << ": " << DQ
					<< (j->second.getDescription()) << DQ << endl;
			file << "\t" << "}";
			if (j != --poiDb.m_val.end())
			{
				file << "," << endl;
			}
		}
		file << endl;
		file << SPACE << " ]" << endl;
		file << "}" << endl;
		file.close();
		flag = true;
	}
	else
	{
		cout << m_file << " file is not open!" << endl;
	}
	return flag;
}

//read the data from the file to the db
bool CJsonPersistence::readData(CWpDatabase& waypointDb, CPoiDatabase& poiDb,
		MergeMode mode)
{

	CWaypoint wpobj;
	CPOI poiobj;
	ifstream object2;
	object2.open(this->m_file.data());
	object2.seekg(0);
	if (mode == REPLACE)
	{
		waypointDb.m_val.clear();
		poiDb.m_val.clear();
		//clear the databases
		m_file.clear();
		//cout << "the db's are cleared" << endl;
	}

	string dbvalue, name, attribute1 = "", desc, temp_type;
	t_poi type = RESTAURANT;
	int count = 0, attcounter = 0, dbcount = 0;
	bool flag = false;
	bool error = false;
	double latitude = 0, longitude = 0;

	CJsonStringToken* str = NULL;
	CJsonNumberToken* num = NULL;

	CJsonScanner jsonscnr(object2);
	t_event prev_state = waitfor_first_token;
	t_event next_state = waitfor_first_token;
	while (object2.is_open())
	{
		try
		{
			CJsonToken* ptr = jsonscnr.nextToken();
			switch (next_state)
			{
			case waitfor_first_token:
				if (ptr->getType() == CJsonToken::BEGIN_OBJECT)
				{
					if (prev_state == waitfor_begin_db)
					{
						next_state = waitfor_att_name;
						prev_state = waitfor_first_token;
					}
					else
					{
						next_state = waitfor_name_db;
						prev_state = waitfor_first_token;
					}
				}
				else
				{
					cout << "ERROR! - First token not found. " << "  In line : " << jsonscnr.scannedLine() << endl;
					return false;
				}
				//	cout << attribute1 << "1" << endl;
				break;
			case waitfor_name_db:
				str = dynamic_cast<CJsonStringToken*>(ptr);
				if (ptr->getType() == CJsonToken::STRING)
				{
					if (str->getValue() == "waypoints")
					{
						dbvalue = "waypoints";
						next_state = waitfor_name_sep;
						prev_state = waitfor_name_db;
						dbcount = 3;
					}
					else if (str->getValue() == "pois")
					{
						dbvalue = "pois";
						next_state = waitfor_name_sep;
						prev_state = waitfor_name_db;
						dbcount = 5;
					}
					else
					{
						cout << "ERROR. No such db name exists. "
								<< "  In line : " << jsonscnr.scannedLine()
								<< endl;
						next_state = waitfor_name_sep;
						prev_state = waitfor_name_db;
						object2.close();
					}
				}
				else
				{
					cout << "ERROR! - DB name is not a string. "
							<< "  In line : " << jsonscnr.scannedLine() << endl;
				}
				//cout << attribute1 << "2" << endl;
				break;
			case waitfor_name_sep:
				if (ptr->getType() == CJsonToken::NAME_SEPARATOR)
				{
					if (prev_state == waitfor_att_name)
					{
						next_state = waitfor_value;
						prev_state = waitfor_name_sep;
					}
					else
					{
						next_state = waitfor_begin_db;
						prev_state = waitfor_name_sep;
					}
				}
				else
				{
					cout << "ERROR! - Name separator not found. "
							<< "  In line : " << jsonscnr.scannedLine() << endl;
					return false;
				}
				//			cout << attribute1 << "3" << endl;
				break;
			case waitfor_begin_db:
				if (ptr->getType() == CJsonToken::BEGIN_ARRAY)
				{
					next_state = waitfor_first_token;
					prev_state = waitfor_begin_db;
				}
				else
				{
					cout << "ERROR! - Begin DB not found. " << "  In line : "
							<< jsonscnr.scannedLine() << endl;
					return false;
				}
				//		cout << attribute1 << "4" << endl;
				break;
			case waitfor_att_name:
				if (ptr->getType() == CJsonToken::STRING)
				{
					str = dynamic_cast<CJsonStringToken*>(ptr);
					num = dynamic_cast<CJsonNumberToken*>(ptr);
					attribute1 = str->getValue();
					//cout << attribute1 << endl;
					count++;
					attcounter++;
					next_state = waitfor_name_sep;
					prev_state = waitfor_att_name;
				}
				else
				{
					cout << "ERROR! - Attribute name is incorrect." << "  In line : " << jsonscnr.scannedLine() << endl;
				}
				//	cout << attribute1 << "5" << endl;
				break;
			case waitfor_value:
				str = dynamic_cast<CJsonStringToken*>(ptr);
				num = dynamic_cast<CJsonNumberToken*>(ptr);
				if (ptr->getType() == CJsonToken::STRING)
				{
					if (attribute1 == "name")
					{
						name = str->getValue();
						next_state = waitfor_value_sep;
						prev_state = waitfor_value;
					}
					else if (attribute1 == "type")
					{
						if (temp_type == "RESTAURANT")
						{
							type = RESTAURANT;
						}
						else if (temp_type == "TOURISTIC")
						{
							type = TOURISTIC;
						}
						else if (temp_type == "GASSTATION")
						{
							type = GASSTATION;
						}
						else if (temp_type == "UNIVERSITY")
						{
							type = UNIVERSITY;
						}
						next_state = waitfor_value_sep;
						prev_state = waitfor_value;
					}
					else if (attribute1 == "description")
					{
						desc = str->getValue();
						if (count == 5)
						{
							if (error == false)
							{
								poiDb.addPoi(*(new CPOI(type, name, desc, latitude,longitude)));
							}
							else
							{
								//do nothing
							}

						}
						else if (count > 5)
						{
							cout<< "ERROR! no of poi attributes is more than expected!"<< endl;
						}
						else
						{
							cout << "ERROR! not enough poi attributes!" << endl;
							//object2.close();
						}
						next_state = waitfor_end_obj;
						prev_state = waitfor_value;
						count = 0;
						error = false;
					}
					else
					{
						error = true;
						cout << "ERROR! Attribute is present as : " << attribute1 << "." << "  In line : " << jsonscnr.scannedLine() << endl;
						next_state = waitfor_value_sep;
						prev_state = waitfor_value;

					}
				}
				else if (ptr->getType() == CJsonToken::NUMBER)
				{
					if (attribute1 == "latitude")
					{
						latitude = num->getValue();
						next_state = waitfor_value_sep;
						prev_state = waitfor_value;
					}
					else if (attribute1 == "longitude")
					{
						longitude = num->getValue();
						if (dbvalue == "waypoints")
						{
							if (count == 3)
							{
								/*next_state = waitfor_end_obj;
								 prev_state = waitfor_value;*/
								if (error == false)
								{
									waypointDb.addWaypoint(
											*(new CWaypoint(name, latitude,
													longitude)));
								}
								else
								{
									//do nothing
								}

							}
							else if (count > 3)
							{
								cout
										<< "ERROR! Number of wp attributes is more than expected!"
										<< endl;
								//	object2.close();
							}
							else
							{
								cout << "ERROR! not enough wp attributes!"
										<< endl;
							}
							next_state = waitfor_end_obj;
							prev_state = waitfor_value;
							count = 0;
							error = false;

						}
						else
						{
							next_state = waitfor_value_sep;
							prev_state = waitfor_value;
						}
					}
					else
					{
						error = true;
						cout << "ERROR! Attribute is present as : "
								<< attribute1 << "." << "  In line : "
								<< jsonscnr.scannedLine() << endl;
						next_state = waitfor_value_sep;
						prev_state = waitfor_value;
					}

				}
				else
				{
					cout << "ERROR! - Value is neither a string nor a number."
							<< "  In line : " << jsonscnr.scannedLine() << endl;
				}
				break;
			case waitfor_value_sep:
				if (ptr->getType() == CJsonToken::VALUE_SEPARATOR)
				{
					next_state = waitfor_att_name;
					prev_state = waitfor_value_sep;
				}
				else
				{
					cout << "ERROR! - Value Separator ',' not found. "
							<< "  In line : " << jsonscnr.scannedLine() << endl;
					return false;
				}
				//		cout << attribute1 << "7" << endl;
				break;
			case waitfor_end_obj:

				if (flag == true)
				{
					if (ptr->getType() == CJsonToken::VALUE_SEPARATOR)
					{
						next_state = waitfor_name_db;
						prev_state = waitfor_value_sep;
						flag = false;
					}
					else
					{
						object2.close();
					}
				}
				else
				{
					if (ptr->getType() == CJsonToken::END_OBJECT)
					{
					}
					else if (ptr->getType() == CJsonToken::VALUE_SEPARATOR)
					{

						if (flag == true)
						{
							next_state = waitfor_name_db;
							prev_state = waitfor_value_sep;
							flag = false;
						}
					}
					else if (ptr->getType() == CJsonToken::BEGIN_OBJECT)
					{
						next_state = waitfor_att_name;
						prev_state = waitfor_end_obj;
					}
					else if (ptr->getType() == CJsonToken::END_ARRAY)
					{
						flag = true;
						/*next_state = waitfor_end_db;
						 prev_state = waitfor_end_obj;*/
					}
					else
					{

					}
				}
				//cout << attribute1 << "8" << endl;
				break;
			case waitfor_end_db:
				if (ptr->getType() == CJsonToken::END_ARRAY)
				{
				}
				else if (ptr->getType() == CJsonToken::VALUE_SEPARATOR)
				{
					next_state = waitfor_name_db;
					prev_state = waitfor_end_db;
					dbvalue = "";

				}
				else
				{
					next_state = waitfor_end_obj;
					prev_state = waitfor_end_db;
				}
				//cout << attribute1 << "9" << endl;
				break;
			default:
				cout << "No such event exists" << endl;
				break;
			}
		} catch (int x)
		{
			cout << "Invalid characters! " << x << endl;
		}
	}
return true;
}
