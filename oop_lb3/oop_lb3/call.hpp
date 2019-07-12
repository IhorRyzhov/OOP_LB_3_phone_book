#pragma once

// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CALL_HPP_
#define _CALL_HPP_

/*****************************************************************************/

#include "calltype.hpp"
#include "datetime.hpp"
#include "messages.hpp"


/*****************************************************************************/

class Contact;

/*****************************************************************************/

class Call
{

public:


	Call(const Call &t) = delete;

	Call & operator = (const Call &y) = delete;
	
	Call(const std::string &_call_number, CallType _type, DateTime _date_and_time, int _call_duration);

	const std::string &getCallNumber() const;

	const CallType getCallType() const;

	const DateTime getCallDateTime() const;

	const int getCallDuration() const;
	
private:

	const std::string m_call_number;
	CallType m_type;
	DateTime m_date_and_time;
	int m_call_duration;

};



/*****************************************************************************/

#endif // _CALL_HPP_
