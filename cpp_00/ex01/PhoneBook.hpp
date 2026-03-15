/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 10:18:20 by shkondo           #+#    #+#             */
/*   Updated: 2026/03/15 10:18:22 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp"
# include <string>

class PhoneBook
{
public:
	PhoneBook(void);
	~PhoneBook(void);

	void	addContact(void);
	void	searchContact(void) const;

private:
	static const int	_maxContacts = 8;
	Contact				_contacts[8];
	int					_currentIndex;
	int					_contactCount;

	std::string			_readField(const std::string &prompt) const;
	std::string			_truncate(const std::string &str) const;
	void				_displayAllContacts(void) const;
	void				_displayOneContact(int index) const;
};

#endif
