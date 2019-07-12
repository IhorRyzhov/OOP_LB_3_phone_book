// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "controller.hpp"
#include "messages.hpp"
#include <algorithm>    // std::sort

Controller::Controller()
{

}

Controller::~Controller()
{
	for (unsigned int i = 0; i < calls.size(); i++)
	{
		delete calls[i];
	}

	for (unsigned int i = 0; i < contacts.size(); i++)
	{
		delete contacts[i];
	}
}


void Controller::addContact(const std::string & _fullName, const std::string & _phoneNumber)
{
	for (unsigned int i = 0; i < contacts.size(); i++)
	{
		if (contacts[i]->getContactName() == _fullName)
		{
			throw std::logic_error(Messages::DuplicateContact);
		}

		if (contacts[i]->getContactNumber() == _phoneNumber)
		{
			throw std::logic_error(Messages::DuplicateContact);
		}
	}

	contacts.push_back(new Contact{ _fullName, _phoneNumber });
}

 const std::string & Controller :: getFullName(const std::string & _phoneNumber) const
{
	 for (unsigned int i = 0; i < contacts.size(); i++)
	 {
		 if (contacts[i]->getContactNumber() == _phoneNumber)
		 {
			const std::string &str = contacts[i]->getContactName();
			return str;
		 }
	 }
	
	throw std::logic_error(Messages::ContactCannotBeFound);
}

void Controller :: addCall(const std::string & _phoneNumber, CallType _callType, DateTime _callTime, int _callDuration)
{
	calls.push_back(new Call{ _phoneNumber, _callType, _callTime, _callDuration });
	m_calls_index++;
}

int Controller :: getCallsCount() const
{
	return calls.size();
}

const std::string & Controller :: getContactName(int _callIndex) const
{
	if (_callIndex > m_calls_index - 1)
	{
		throw std::logic_error(Messages::CallIndexOutOfRange);
	}	
	
	static std::string str;

	for (unsigned int i = 0; i < contacts.size(); i++)
	{
		if (calls[_callIndex]->getCallNumber() == contacts[i]->getContactNumber())
		{
			 return contacts[i]->getContactName();
		}
	}

	return str;
}

const std::string & Controller :: getPhoneNumber(int _callIndex) const
{
	if (_callIndex > m_calls_index - 1)
	{
		throw std::logic_error(Messages::CallIndexOutOfRange);
	}

	return calls[_callIndex]->getCallNumber();
}

CallType Controller :: getCallType(int _callIndex) const
{
	if (_callIndex > m_calls_index - 1)
	{
		throw std::logic_error(Messages::CallIndexOutOfRange);
	}

	return calls[_callIndex]->getCallType();
}

DateTime Controller :: getCallTime(int _callIndex) const
{
	if (_callIndex > m_calls_index - 1)
	{
		throw std::logic_error(Messages::CallIndexOutOfRange);
	}

	return calls[_callIndex]->getCallDateTime();
}

int Controller :: getCallDuration(int _callIndex) const
{
	if (_callIndex > m_calls_index - 1)
	{
		throw std::logic_error(Messages::CallIndexOutOfRange);
	}

	return calls[_callIndex]->getCallDuration();
}

double Controller :: getAverageBusinessTimeCallsDuration(DateTime _day) const
{
	DateTime day;

	if (_day.getDay() < day.getDay())
	{
		throw std::logic_error(Messages::InvalidCallTime);
	}

	double duration = 0;
	int count = 0;

	for (unsigned int i = 0; i < calls.size(); i++)
	{
		if ((calls[i]->getCallDateTime().getHours() >= 9) && (calls[i]->getCallDateTime().getHours() <= 17))
		{
			count++;
			duration += calls[i]->getCallDuration();
		}
	}

	if (count > 0)
	{
		duration = (double)duration / count;
		return duration;
	}
	else
	{
		return 0;
	}
}

std::vector< std::string > Controller :: getUnregisteredContactsFromCalls() const
{
	std::vector<std::string> unregistered_phone_numbers;
	char flag = 0;

	for (unsigned int i = 0; i < calls.size(); i++)
	{
		for (unsigned int j = 0; j < contacts.size(); j++)
		{
			if (calls[i]->getCallNumber() == contacts[j]->getContactNumber())
			{
				flag = 1;
			}
		}

		if (flag == 1)
		{
			flag = 0;
		}
		else
		{
			for (unsigned int k = 0; k < unregistered_phone_numbers.size(); k++)
			{
				if (calls[i]->getCallNumber() == unregistered_phone_numbers[k])
				{
					flag = 1;
				}
			}

			if (flag == 1)
			{
				flag = 0;
			}
			else
			{
				unregistered_phone_numbers.push_back(calls[i]->getCallNumber());
			}
		}
	}

	return unregistered_phone_numbers;
}

std::string Controller :: getMostFrequentIncomingContact() const
{
	std::vector<std::string> str;

	for (unsigned int i = 0; i < calls.size(); i++)
	{
		if (calls[i]->getCallType() == CallType::Incoming)
		{
			str.push_back(calls[i]->getCallNumber());
		}
	}	


	std::sort(str.begin(), str.end());

	std::string freqContact;
	unsigned int frequency = 0, frequency_max = 0, count = 0;

	for (unsigned int i = 0; i < str.size(); i++)
	{		
		while (str[i] == str[count])
		{
			frequency++;

			if (frequency > frequency_max)
			{
				frequency_max = frequency;
				freqContact = str[i];
			}
			count++;
		}

		i = count;
	}
	
	for (unsigned int i = 0; i < contacts.size(); i++)
	{
		if (contacts[i]->getContactNumber() == freqContact)
		{
			return contacts[i]->getContactName();
		}
	}

	return "";
}

std::string Controller :: getLongestOutgoingContact() const
{
	unsigned int duration_max = 0;
	std::string number;

	for (unsigned int i = 0; i < calls.size(); i++)
	{
		if (calls[i]->getCallDuration() > duration_max)
		{
			duration_max = calls[i]->getCallDuration();
			number = calls[i]->getCallNumber();
		}
	}

	for (unsigned int i = 0; i < contacts.size(); i++)
	{
		if (number == contacts[i]->getContactNumber())
		{
			return contacts[i]->getContactName();
		}
	}

	return "";
}
