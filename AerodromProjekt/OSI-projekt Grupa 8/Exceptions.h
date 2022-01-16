#pragma once
#include <iostream>
#include <stdexcept>

class KorisnikNePostoji : virtual public std::exception
{
	std::string error;
public:
	explicit KorisnikNePostoji(const std::string& msg) : error(msg) {}
	virtual const char* what() const throw() {
		return error.c_str();
	}
};

class KorisnikSuspendovan : public std::exception
{
	std::string error;
public:
	explicit KorisnikSuspendovan(const std::string& msg) : error(msg) {}
	const char* what() const throw() {
		return error.c_str();
	}
};

class NeispravnaLozinka : public std::exception
{
	std::string error;
public:
	explicit NeispravnaLozinka(const std::string& msg) : error(msg) {}
	const char* what() const throw() {
		return error.c_str();
	}
};