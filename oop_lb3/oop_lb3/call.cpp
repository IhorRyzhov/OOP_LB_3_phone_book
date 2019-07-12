// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "call.hpp"

Call :: Call(const std::string &_call_number, CallType _type, DateTime _date_and_time, int _call_duration)
	: m_call_number(_call_number), m_type(_type), m_date_and_time(_date_and_time), m_call_duration(_call_duration)
{
	if (m_call_number.empty())
	{
		throw std::logic_error(Messages::EmptyPhoneNumber);
	}

	if (m_call_duration < 0)
	{
		throw std::logic_error(Messages::InvalidCallDuration);
	}

	DateTime t;

	if (m_date_and_time > t)
	{
		throw std::logic_error(Messages::InvalidCallTime);
	}
}

const std::string &Call:: getCallNumber() const
{
	return m_call_number;
}

const CallType Call::getCallType() const
{
	return m_type;
}

const DateTime Call::getCallDateTime() const
{
	return m_date_and_time;
}

const int Call::getCallDuration() const
{
	return m_call_duration;
}