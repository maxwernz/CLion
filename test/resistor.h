
#ifndef RESISTOR_H_
#define RESISTOR_H_

class Widerstandsnw {
public:
	virtual double ohm() const = 0;
	virtual ~Widerstandsnw() {}
};

class Resistor : public Widerstandsnw {
public:
	Resistor(double ohm=0) : _ohm(ohm) {}
	Resistor(const Resistor& r) : _ohm(r._ohm) {}
	double ohm() const override { return _ohm; };
	void set_ohm(double ohm);
protected:
	double _ohm;
};

class Serial : public Widerstandsnw {
public:
	Serial(Widerstandsnw* r1, Widerstandsnw* r2) : _r1(r1), _r2(r2) {}
	double ohm() const override { return _r1->ohm() + _r2->ohm(); };
private:
	Widerstandsnw* _r1, *_r2;
};

class Parallel : public Widerstandsnw {
public:
	Parallel(Widerstandsnw* r1, Widerstandsnw* r2) : _r1(r1), _r2(r2) {}
	double ohm() const override { return (_r1->ohm() * _r2->ohm()) / (_r1->ohm() + _r2->ohm()); }
private:
	Widerstandsnw* _r1, *_r2;
};

class Poti : public Resistor {
public:
	Poti(double ohm) : _r(ohm) {}
private:
	Resistor _r;
};



#endif /* RESISTOR_H_ */
