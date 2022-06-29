#include "common.h"

Polynom::Polynom() : _name(""), _coef(0), _degree(0) {}

Polynom::Polynom(std::string name, std::vector<double> coef) : _name(name), _coef(coef) {
	_degree = coef.size() - 1;
}

Polynom::Polynom(const Polynom& a) {
	_name = a._name;
	_degree = a._degree;
	_coef = a._coef;
}

int Polynom::degree() const {
	return _degree;
}

std::string Polynom::name() const {
	return _name;
}

double& Polynom::at(size_t idx) {
	return _coef[idx]; //schutz fehlt
}

double Polynom::at(size_t idx) const {
	return _coef[idx];
}

bool Polynom::operator<(const Polynom& a) const {
	return (_name < a._name);
}

double Polynom::eval(double in) {
	double sum = 0;
	int degPos = 0;
	for (double val : _coef) {
		sum += val * pow(in, degPos);
		degPos += 1;
	}
	return sum;
}

void Polynom::setName(std::string name) {
	_name = name;
}

Polynom operator +(const Polynom a, const Polynom b) {
	int lowerDegree;
	int higherDegree;
	std::vector<double> newCoef;
	if (a.degree() > b.degree()) {
		lowerDegree = b.degree();
		higherDegree = a.degree();
		for (int i = lowerDegree+1; i <= higherDegree; ++i) {
			newCoef.push_back(a.at(i));
		}
	}
	else {
		lowerDegree = a.degree();
		higherDegree = b.degree();
		for (int i = lowerDegree+1; i <= higherDegree; ++i) {
			newCoef.push_back(b.at(i));
		}
	}
	for (int i=lowerDegree; i >= 0; --i) {
		newCoef.insert(newCoef.begin(), a.at(i) + b.at(i));
	}


	return Polynom (a.name() + "+" + b.name(), newCoef);
}

Polynom operator*(const Polynom a, const Polynom b) {
	int degA = a.degree();
	int degB = b.degree();
	std::vector<double> newCoef (degA + degB + 1);
	for (; degA >= 0; --degA) {
		for (; degB >= 0; --degB) {
			newCoef[degA + degB] += a.at(degA) * b.at(degB);
		}
		degB = b.degree();
	}
	return Polynom(a.name() + "*" + b.name(), newCoef);
}

std::ostream& operator<<(std::ostream& out, Polynom p) {
	out << p.name() << ": ";
	int i = p.degree();
	while (p.at(i) == 0)
		i -= 1;

	for (;i > 1; i-=1) {
		if (p.at(i) != 0)
			out << p.at(i) << "*x**" << i <<" ";
		if (p.at(i - 1) > 0)
			out << "+" << " ";
		else if (p.at(i - 1) < 0){
			p.at(i - 1) *= -1;
			out << "-" << " ";
		}
	}

	if (p.at(1) != 0)
		out << p.at(1) << "*x ";
	if (p.at(0) > 0)
		out << "+" << " ";
	else if (p.at(0) < 0){
		p.at(0) *= -1;
		out << "-" << " ";
	}
	if (p.at(0) != 0)
		out << p.at(0);
	return out;
}





