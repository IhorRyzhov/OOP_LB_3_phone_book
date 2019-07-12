// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "contact.hpp"
#include <iostream>

Contact :: Contact(const std::string &_contact_name, const std::string &_contact_number)
	: m_contact_name(_contact_name), m_contact_number(_contact_number)
{
	if (m_contact_name.empty())
	{
		throw std::logic_error(Messages::EmptyFullName);
	}

	if (m_contact_number.empty())
	{
		throw std::logic_error(Messages::EmptyPhoneNumber);
	}
}

const std::string &Contact:: getContactName() const
{
	return m_contact_name;
}

const std::string &Contact:: getContactNumber() const
{
	return m_contact_number;
}