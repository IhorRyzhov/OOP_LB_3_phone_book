#pragma once

// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONTACT_HPP_
#define _CONTACT_HPP_

#include <iostream>
#include "messages.hpp"
/*****************************************************************************/

class Call;

/*****************************************************************************/

class Contact
{

public:

	Contact(const std::string &_contact_name, const std::string &_contact_number);

	Contact(const Contact &t) = delete;

	Contact & operator = (const Contact &y) = delete;

	const std::string &getContactName() const;

	const std::string &getContactNumber() const;

private:

	const std::string m_contact_name;

	const std::string m_contact_number;

};

/*****************************************************************************/
 

#endif // _CONTACT_HPP_