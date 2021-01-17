/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 19:56:43 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/17 02:30:30 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>
#include <cmath>

const int Fixed::_fractional_bits = 8;

Fixed::Fixed() : _raw(0)
{
}

Fixed::Fixed(const int nb) : _raw(nb << _fractional_bits)
{
}

Fixed::Fixed(const float floating) : _raw(roundf(floating * (1 << _fractional_bits)))
{
}

Fixed::Fixed(const Fixed &other)
{
	*this = other;
}

Fixed::~Fixed()
{
}

Fixed &Fixed::operator=(const Fixed &other)
{
	_raw = other._raw;

	return *this;
}

int Fixed::get_fractional()
{
	return _fractional_bits;
}

int Fixed::getRawBits() const
{
	return _raw;
}

void Fixed::setRawBits(const int raw)
{
	_raw = raw;
}

int Fixed::toInt() const
{
	return (_raw >> _fractional_bits);
}

float Fixed::toFloat() const
{
	return ((float)_raw / (1 << _fractional_bits));
}

std::ostream &operator<<(std::ostream &os, const Fixed &fixed)
{
	os << fixed.toFloat();
	return os;
}

std::istream &operator>>(std::istream &is, Fixed &fixed)
{
	double f;
	is >> f;
	fixed.setRawBits(f * (1 << Fixed::get_fractional()));
	return is;
}

bool Fixed::operator>(const Fixed& b) const
{
	return _raw > b._raw;
}

bool Fixed::operator<(const Fixed& b) const
{
	return _raw < b._raw;
}

bool Fixed::operator>=(const Fixed& b) const
{
	return !(*this < b);
}

bool Fixed::operator<=(const Fixed& b) const
{
	return !(*this > b);
}

bool Fixed::operator==(const Fixed& b) const
{
	return _raw == b._raw;
}

bool Fixed::operator!=(const Fixed& b) const
{
	return !(*this == b);
}

Fixed Fixed::operator+(const Fixed& b) const
{
	return Fixed(toFloat() + b.toFloat());
}

Fixed Fixed::operator-(const Fixed& b) const
{
	return Fixed(toFloat() - b.toFloat());
}

Fixed Fixed::operator*(const Fixed& b) const
{
	return Fixed(toFloat() * b.toFloat());
}

Fixed Fixed::operator/(const Fixed& b) const
{
	return Fixed(toFloat() / b.toFloat());
}


Fixed& Fixed::operator++()
{
	_raw++;
	return *this;
}

Fixed Fixed::operator++(int) //post increment
{
	Fixed f(*this);
	_raw++;
	return f;
}

Fixed& Fixed::operator--()
{
	_raw--;
	return *this;
}

Fixed Fixed::operator--(int) //post decrement
{
	Fixed f(*this);
	_raw--;
	return f;
}

Fixed& max(Fixed &a, Fixed &b)
{
	return a < b ? b : a;
}

const Fixed& max(const Fixed &a, const Fixed &b)
{
	return a < b ? b : a;
}

Fixed& min(Fixed &a, Fixed &b)
{
	return a > b ? b : a;
}

const Fixed& min(const Fixed &a, const Fixed &b)
{
	return a > b ? b : a;
}
