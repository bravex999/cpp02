#include "Fixed.hpp"

Fixed::Fixed() : _fixedPointValue(0)
{
}

Fixed::Fixed(const int integer)
{
	this->_fixedPointValue = integer << _fractionalBits;
}

Fixed::Fixed(const float floatingPoint)
{
	this->_fixedPointValue = roundf(floatingPoint * (1 << _fractionalBits));
}

Fixed::Fixed(const Fixed& copy)
{
	*this = copy;
}

Fixed& Fixed::operator=(const Fixed& copy)
{
	if (this != &copy)
		this->_fixedPointValue = copy.getRawBits();
	return *this;
}

Fixed::~Fixed()
{
}

int Fixed::getRawBits(void) const
{
	return this->_fixedPointValue;
}

void Fixed::setRawBits(int const raw)
{
	this->_fixedPointValue = raw;
}

float Fixed::toFloat(void) const
{
	return (float)this->_fixedPointValue / (float)(1 << _fractionalBits);
}

int Fixed::toInt(void) const
{
	return this->_fixedPointValue >> _fractionalBits;
}

bool Fixed::operator>(const Fixed& other) const
{
	return this->_fixedPointValue > other.getRawBits();
}

bool Fixed::operator<(const Fixed& other) const
{
	return this->_fixedPointValue < other.getRawBits();
}

bool Fixed::operator>=(const Fixed& other) const
{
	return this->_fixedPointValue >= other.getRawBits();
}

bool Fixed::operator<=(const Fixed& other) const
{
	return this->_fixedPointValue <= other.getRawBits();
}

bool Fixed::operator==(const Fixed& other) const
{
	return this->_fixedPointValue == other.getRawBits();
}

bool Fixed::operator!=(const Fixed& other) const
{
	return this->_fixedPointValue != other.getRawBits();
}

Fixed Fixed::operator+(const Fixed& other) const
{
	Fixed result;
	result.setRawBits(this->_fixedPointValue + other.getRawBits());
	return result;
}

Fixed Fixed::operator-(const Fixed& other) const
{
	Fixed result;
	result.setRawBits(this->_fixedPointValue - other.getRawBits());
	return result;
}

Fixed Fixed::operator*(const Fixed& other) const
{
	Fixed result;
	long long temp = (long long)this->_fixedPointValue * (long long)other.getRawBits();
	result.setRawBits((int)(temp >> _fractionalBits));
	return result;
}

Fixed Fixed::operator/(const Fixed& other) const
{
	Fixed result;
	long long temp = (long long)this->_fixedPointValue << _fractionalBits;
	if (other.getRawBits() != 0)
		result.setRawBits((int)(temp / other.getRawBits()));
	return result;
}

Fixed& Fixed::operator++()
{
	this->_fixedPointValue++;
	return *this;
}

Fixed Fixed::operator++(int)
{
	Fixed temp(*this);
	this->_fixedPointValue++;
	return temp;
}

Fixed& Fixed::operator--()
{
	this->_fixedPointValue--;
	return *this;
}

Fixed Fixed::operator--(int)
{
	Fixed temp(*this);
	this->_fixedPointValue--;
	return temp;
}

Fixed& Fixed::min(Fixed& a, Fixed& b)
{
	if (a.getRawBits() < b.getRawBits())
		return a;
	return b;
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b)
{
	if (a.getRawBits() < b.getRawBits())
		return a;
	return b;
}

Fixed& Fixed::max(Fixed& a, Fixed& b)
{
	if (a.getRawBits() > b.getRawBits())
		return a;
	return b;
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b)
{
	if (a.getRawBits() > b.getRawBits())
		return a;
	return b;
}

std::ostream& operator<<(std::ostream& out, const Fixed& fixed)
{
	out << fixed.toFloat();
	return out;
}
