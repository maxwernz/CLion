 #include <vector>
#include <string>
#include <deque>
#include <iostream>
#include <stdexcept>
#include <math.h>

#ifndef COMMON_H_
#define COMMON_H_

class Polynom {
public:
	Polynom();
	Polynom(std::string name, std::vector<double> coef);
	Polynom(const Polynom& a);
	std::string name() const;
	int degree() const;
	double& at(size_t idx);
	double at(size_t idx) const;
	bool operator<(const Polynom& a) const;
	double eval (double in);
	void setName(std::string name);
private:
	std::string _name;
	std::vector<double> _coef;
	int _degree;
};

std::ostream& operator<<(std::ostream& out, Polynom p);
Polynom operator+(const Polynom a, const Polynom b);
Polynom operator*(const Polynom a, const Polynom b);

#endif /* COMMON_H_ */
