/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 22:59:17 by shkondo           #+#    #+#             */
/*   Updated: 2026/03/15 10:00:00 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

Contact::Contact(void) {}

Contact::~Contact(void) {}

void	Contact::setFirstName(const std::string &value) { _firstName = value; }
void	Contact::setLastName(const std::string &value) { _lastName = value; }
void	Contact::setNickname(const std::string &value) { _nickname = value; }
void	Contact::setPhoneNumber(const std::string &value) { _phoneNumber = value; }
void	Contact::setDarkestSecret(const std::string &value) { _darkestSecret = value; }

std::string	Contact::getFirstName(void) const { return _firstName; }
std::string	Contact::getLastName(void) const { return _lastName; }
std::string	Contact::getNickname(void) const { return _nickname; }
std::string	Contact::getPhoneNumber(void) const { return _phoneNumber; }
std::string	Contact::getDarkestSecret(void) const { return _darkestSecret; }

bool	Contact::isEmpty(void) const
{
	return _firstName.empty();
}
