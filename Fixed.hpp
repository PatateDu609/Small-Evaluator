#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed
{
public:
	Fixed();
	Fixed(const int nb);
	Fixed(const float floating);
	Fixed(const Fixed &other);
	~Fixed();

	Fixed &operator=(const Fixed &other);

	static int get_fractional();

	int getRawBits(void) const;
	void setRawBits(int const raw);

	float toFloat() const;
	int toInt() const;

	bool operator>(const Fixed& b) const;
	bool operator<(const Fixed& b) const;
	bool operator>=(const Fixed& b) const;
	bool operator<=(const Fixed& b) const;
	bool operator==(const Fixed& b) const;
	bool operator!=(const Fixed& b) const;

	Fixed operator+(const Fixed& b) const;
	Fixed operator-(const Fixed& b) const;
	Fixed operator*(const Fixed& b) const;
	Fixed operator/(const Fixed& b) const;

	Fixed& operator++();
	Fixed operator++(int);
	Fixed& operator--();
	Fixed operator--(int);

private:
	int _raw;
	static const int _fractional_bits;
};

std::ostream &operator<<(std::ostream &os, const Fixed &fixed);
std::istream &operator>>(std::istream &is, Fixed &fixed);

const Fixed& max(const Fixed& a, const Fixed& b);
Fixed& max(Fixed& a, Fixed& b);
const Fixed& min(const Fixed& a, const Fixed& b);
Fixed& min(Fixed& a, Fixed& b);

#endif
