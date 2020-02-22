/*
 * CTempClass.h
 *
 *  Created on: 09-Jan-2018
 *      Author: AMRUTH
 */

#ifndef MYCODE_CTEMPCLASS_H_
#define MYCODE_CTEMPCLASS_H_

#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <map>

#include "CPOI.h"

using namespace std;


template<typename key, class val>

class CTempClass {

protected:

	map<key, val> m_val;

public:

//Constructor
CTempClass(){}

//Add the WP/POI value
void addValue(val const& value);

//Check the input parameter if present in the database, else return error.
val* getPointerToVal(key name);

//Print the value
void printValue();

//Clear the WP/POI Database
void cleardb();

friend class CJsonPersistence;
};


template<typename key, class val>
void CTempClass<key,val>::addValue(val const& value)
{
	m_val.insert(pair<key, val>(value.getName(), value));
}

template<typename key, class val>
val* CTempClass<key,val>::getPointerToVal(key name)
{
	typename map<key, val>::iterator i;
	for (i = m_val.begin(); i != m_val.end(); i++) {
		if (i->first == name) {
			return &(i->second);
		}
	}
	return NULL;
}

template<typename key, class val>
void CTempClass<key,val>::printValue()
{
	//cout << "the content in the db are : " << endl;
		typename map<key, val>::const_iterator i;
		for (i = m_val.begin(); i != m_val.end(); i++) {
			cout << i ->second << endl;
		}

}

template<typename key, class val>
void CTempClass<key,val>::cleardb()
{
	//cout << "the content in the db are : " << endl;
		typename map<key, val>::const_iterator i;
		for (i = m_val.begin(); i != m_val.end(); i++) {
			m_val.clear();
		}

}

#endif /* MYCODE_CTEMPCLASS_H_ */
