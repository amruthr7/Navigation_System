#include <iostream>
#include "CStorageNavigation.h"

/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CSTORAGENAVIGATION.CPP
* Author          :
* Description     :
*
*
****************************************************************************/


//System Include Files

//Own Include Files

//Method Implementations

CStorageNavigation::CStorageNavigation()
{
}

CStorageNavigation::~CStorageNavigation(){}

void CStorageNavigation:: setMediaName(std::string name){
	m_wpStorageNavigation = name + "-wp.txt";
	m_poiStorageNavigation = name + "-poi.txt";
}

bool CStorageNavigation:: writeData (const CWpDatabase& waypointDb, const CPoiDatabase& poiDb)
{
	ofstream object1;
	bool flag = false;

	object1.open(this->m_wpStorageNavigation.data());
	object1.seekp(0);						//starts from the beginning of the file

	if (object1.is_open())
	{
		waypointDb.print(object1);
		object1.close();
		flag = true;
	}
	else
	{
		cout << m_wpStorageNavigation << " waypoint file is not open!" << endl;
	}

	object1.open(this->m_poiStorageNavigation.data());
	object1.seekp(0);

	if (object1.is_open())
	{
		poiDb.print(object1);
		object1.close();
		flag = true;
	}
	else
	{
		cout << m_poiStorageNavigation << " poi file is not open!" << endl;
	}
	return flag;
}


bool CStorageNavigation::readData (CWpDatabase& waypointDb, CPoiDatabase& poiDb, MergeMode mode)
{
	ifstream object2;
	unsigned int wpcounter = 0;
	unsigned int poicounter = 0;
	char delim = ';';
	bool err_flag = false;
	int wplinenumber = 0;
	int poilinenumber = 0;
	int max;
	string myparam, myline;

	// WP parameters
	string name, latitude, longitude;
	double mlat = 0;
	double mlong = 0;

	// POI parameters
	string name1, latitude1, longitude1, description;
	t_poi type;
	double mlat1 = 0;
	double mlong1 = 0;

	if (mode == REPLACE)
	{
		waypointDb.wpclear();							//clear the databases
		poiDb.poiclear();
		//cout << "the db's are cleared" << endl;
	}

	object2.open(this->m_wpStorageNavigation.data());
	object2.seekg(0);
	if (object2.is_open())
	{
		while (getline(object2, myline))
		{
			int wptext_flag = 0;
			max = wpparam-1;
			checkDelim(myline,max);
			wplinenumber++;
			stringstream mystream(myline);
			while (getline(mystream, myparam, delim))
			{
				wpcounter++;
				switch (wpcounter)
				{
				case 1:
					name = myparam;
					break;
				case 2:
					latitude = myparam;
					if (checkDigits(latitude)){					// to check if any text is present instead a number for latitude
						mlat = atof(latitude.c_str());
						//wptext_flag = 0;
						break;
					}
					else{
						wptext_flag=1;
						break;
					}
				case 3:
					longitude = myparam;
					if (checkDigits(longitude))					// to check if any text is present instead a number for longitude
					{
						mlong = atof(longitude.c_str());
						//wptext_flag = 0;
						break;
					}
					else
					{
						wptext_flag = 1;
						break;
					}
				default:
					cout << "Cannot read wp details from file! " << endl;
				}
			}
			if (wpcounter == 3)									//to check if the number of attributes are as expected
			{
				if (wptext_flag==0){
				wpcounter = 0;
				waypointDb.addWaypoint(*(new CWaypoint(name, mlat, mlong)));
				}
				else {
					wpcounter=0;
					cout << "Error: <Number is expected instead of a string> in line <"
							<< wplinenumber << ">:<" << myline << ">" << endl;
				}
			}
			else if ((wpcounter < 3) || (wpcounter > 3))
			{
				wpcounter = 0;
				cout<< "Error: <Number of parameters in the wp is incorrect> in line <"
						<< wplinenumber << ">:<" << myline << ">" << endl;
			}
		}
		object2.close();
		err_flag = true;
	}
	else
	{
		cout << "The wp file is not open" << endl;
	}

//***************POI*************//
	object2.open(this->m_poiStorageNavigation.data());
	object2.seekg(0);
	if (object2.is_open())
	{
		while (getline(object2, myline))
		{
			int poitext_flag = 0;
			max = poiparam-1;
			checkDelim(myline,max);
			poilinenumber++;
			stringstream mystream(myline);
			while (getline(mystream, myparam, delim))
			{
				poicounter++;
				switch (poicounter)
				{
				case 1:
					name1 = myparam;
					break;
				case 2:
					if (myparam == "RESTAURANT")
					{
						type = RESTAURANT;
					}
					else if (myparam == "TOURISTIC")
					{
						type = TOURISTIC;
					}
					else if (myparam == "GASSTATION")
					{
						type = GASSTATION;
					}
					else if (myparam == "UNIVERSITY")
					{
						type = UNIVERSITY;
					}
					break;
				case 3:
					description = myparam;
					break;
				case 4:
					latitude1 = myparam;
					if (checkDigits(latitude1))
					{
						mlat1 = atof(latitude1.c_str());
						break;
					}
					else
					{
						poitext_flag = 1;
						break;
					}
				case 5:
					longitude1 = myparam;
					if (checkDigits(longitude1))
					{
						mlong1 = atof(longitude1.c_str());
						break;
					}
					else
					{
						poitext_flag = 1;
						break;
					}
				default:
					cout << "Cannot read poi details from file! " << endl;
				}
			}
			if (poicounter == 5)
			{
				if (poitext_flag==0){
				poicounter = 0;
				poiDb.addPoi(*(new CPOI(type, name1, description, mlat1, mlong1)));
				}
				else {
					poicounter=0;
					cout << "Error: <A Number is expected instead of a string> in line <"
							<< poilinenumber << ">:<" << myline << ">" << endl;
				}
			}
			else if ((poicounter < 5) || (poicounter > 5))
			{
				poicounter = 0;
				cout<< "Error: <Number of parameters in the poi is incorrect> in line <"
						<< poilinenumber << ">:<" << myline << ">" << endl;
			}
		}
		object2.close();
		err_flag = true;
	}
	else
	{
		cout << "The poi file is not open" << endl;
	}
	return err_flag;
}

bool CStorageNavigation::checkDigits(string param)
{
	for (string::iterator i = param.begin(); i != param.end(); ++i){
		if (isalpha(*i)){										//Check if string that is passed is alphabetic
			return false;
		}
	}
	return true;
}

//Check for delimiter- comma/dot/semicolon
void CStorageNavigation::checkDelim(string& myline, int maxparams)
{
	int count = 0;
	size_t found = myline.find(',');
	while (found != string::npos)
	{
		count++;
		myline[found] = ',';
		found = myline.find(',', found + 1);
	}
	if (count > maxparams)
	{
		size_t found = myline.find(',');
		while (found != string::npos)
		{
			myline[found] = ';';
			found = myline.find(',', found + 1);
		}
	}
	else if (count == maxparams)
	{
		size_t found = myline.find(';');
		if (found != string::npos)
		{
			size_t found = myline.find(',');
			while (found != string::npos)
			{
				myline[found] = '.';
				found = myline.find(',', found + 1);
			}
		}
		found = myline.find(',');
		while (found != string::npos)
		{
			myline[found] = ';';
			found = myline.find(',', found + 1);
		}
	}
	else if (count < maxparams)
	{
		size_t found = myline.find(',');
		while (found != string::npos)
		{
			myline[found] = '.';
			found = myline.find(',', found + 1);
		}
	}

}
