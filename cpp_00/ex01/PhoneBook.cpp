/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 22:59:30 by shkondo           #+#    #+#             */
/*   Updated: 2026/03/15 10:00:00 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>

PhoneBook::PhoneBook(void) : _currentIndex(0), _contactCount(0) {}

PhoneBook::~PhoneBook(void) {}

std::string	PhoneBook::_readField(const std::string &prompt) const
{
	std::string	input;

	while (true)
	{
		std::cout << prompt;
		if (!std::getline(std::cin, input))
			return "";
		if (!input.empty())
			return input;
		std::cout << "Field cannot be empty." << std::endl;
	}
}

std::string	PhoneBook::_truncate(const std::string &str) const
{
	if (str.length() > 10)
		return str.substr(0, 9) + ".";
	return str;
}

void	PhoneBook::addContact(void)
{
	Contact		contact;
	std::string	value;

	value = _readField("First name: ");
	if (value.empty())
		return ;
	contact.setFirstName(value);
	value = _readField("Last name: ");
	if (value.empty())
		return ;
	contact.setLastName(value);
	value = _readField("Nickname: ");
	if (value.empty())
		return ;
	contact.setNickname(value);
	value = _readField("Phone number: ");
	if (value.empty())
		return ;
	contact.setPhoneNumber(value);
	value = _readField("Darkest secret: ");
	if (value.empty())
		return ;
	contact.setDarkestSecret(value);
	_contacts[_currentIndex % _maxContacts] = contact;
	_currentIndex++;
	if (_contactCount < _maxContacts)
		_contactCount++;
	std::cout << "Contact added." << std::endl;
}

void	PhoneBook::_displayAllContacts(void) const
{
	std::cout << std::setw(10) << "Index" << "|"
			  << std::setw(10) << "First Name" << "|"
			  << std::setw(10) << "Last Name" << "|"
			  << std::setw(10) << "Nickname" << std::endl;
	std::cout << std::string(43, '-') << std::endl;
	for (int i = 0; i < _contactCount; i++)
	{
		std::cout << std::setw(10) << i << "|"
				  << std::setw(10) << _truncate(_contacts[i].getFirstName()) << "|"
				  << std::setw(10) << _truncate(_contacts[i].getLastName()) << "|"
				  << std::setw(10) << _truncate(_contacts[i].getNickname()) << std::endl;
	}
}

void	PhoneBook::_displayOneContact(int index) const
{
	std::cout << "First name: " << _contacts[index].getFirstName() << std::endl;
	std::cout << "Last name: " << _contacts[index].getLastName() << std::endl;
	std::cout << "Nickname: " << _contacts[index].getNickname() << std::endl;
	std::cout << "Phone number: " << _contacts[index].getPhoneNumber() << std::endl;
	std::cout << "Darkest secret: " << _contacts[index].getDarkestSecret() << std::endl;
}

void	PhoneBook::searchContact(void) const
{
	std::string	input;
	int			index;

	if (_contactCount == 0)
	{
		std::cout << "Phone book is empty." << std::endl;
		return ;
	}
	_displayAllContacts();
	std::cout << "Enter index: ";
	if (!std::getline(std::cin, input))
		return ;
	index = std::atoi(input.c_str());
	if (input.empty() || input.find_first_not_of("0123456789") != std::string::npos
		|| index < 0 || index >= _contactCount)
	{
		std::cout << "Invalid index." << std::endl;
		return ;
	}
	_displayOneContact(index);
}
