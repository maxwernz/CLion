#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include "ooptool.h"
#include "common.h"
#include "ooptoolg.h"



void pickFunc(std::string key, std::vector<std::string> values, std::map<std::string, Polynom>& polys);

void showFunc(std::vector<std::string> values, std::map<std::string, Polynom> polys);

void dumpFunc(std::map<std::string, Polynom> polys);

void delFunc(std::vector<std::string> values, std::map<std::string, Polynom>& polys);

void clearFunc(std::map<std::string, Polynom>& polys);

void evalFunc(std::vector<std::string> values, std::map<std::string, Polynom> polys);

void echoFunc(std::vector<std::string> values);

void addFunc(std::vector<std::string> values, std::map<std::string, Polynom>& polys);

void plotFunc(std::vector<std::string> values, std::map<std::string, Polynom> polys);

void multFunc (std::vector<std::string> values, std::map<std::string, Polynom>& polys);

bool findKey(std::string key, std::map<std::string, Polynom> polys);

void insertPoly(std::string key, Polynom p, std::map<std::string, Polynom>& polys);

int main (int argc, char* argv[]) {

	std::string file = argv[1];
	std::vector<std::string> lines = read_lines("samples/" + file);
	std::string name;
	std::vector<double> coef;
	std::vector<std::string> values;
	double number;
	std::string key;
	std::string value;
	std::map<std::string, Polynom> polys;
	for (std::string line : lines) {
		if (line.find(":") != std::string::npos) {
			std::stringstream pol (line);
			pol >> name;
			name.erase(name.find(":"));

			while (pol >> number)
				coef.insert(coef.begin(), number);
			Polynom p(name, coef);
			insertPoly(name, p, polys);
			coef.clear();
		}
		else {
			std::istringstream cmd (line);
			cmd >> key;
			while (cmd >> value)
				values.push_back(value);
			pickFunc(key, values, polys);
			values.clear();
		}
	}

//	for(const auto& p : polys) {
//		std::cout << p.second << std::endl;
//	}
}

void pickFunc(std::string key, std::vector<std::string> values, std::map<std::string, Polynom>& polys) {
	std::map<std::string, int> map { {"show", 1}, {"dump", 2}, {"del", 3}, {"clear", 4}, {"eval", 5}, {"echo", 6}, {"add", 7}, {"mul", 8}, {"plot", 9}};
	switch (map[key]) {
		case 1:
			showFunc(values, polys);
			break;
		case 2:
			dumpFunc(polys);
			break;
		case 3:
			delFunc(values, polys);
			break;
		case 4:
			clearFunc(polys);
			break;
		case 5:
			evalFunc(values, polys);
			break;
		case 6:
			echoFunc(values);
			break;
		case 7:
			addFunc(values, polys);
			break;
		case 8:
			multFunc(values, polys);
			break;
		case 9:
			plotFunc(values, polys);
			break;
	}
}

void insertPoly(std::string key, Polynom p, std::map<std::string, Polynom>& polys) {
	if (findKey(key, polys))
		polys[key] = p;
	else
		polys.emplace(key, p);
}

bool findKey(std::string key, std::map<std::string, Polynom> polys) {
	for (const auto& it : polys) {
		if (key == it.first)
			return true;
	}
	return false;
}

void showFunc(std::vector<std::string> values, std::map<std::string, Polynom> polys) {
	for (std::string value : values) {
		std::cout << polys[value] << std::endl;
	}
}

void dumpFunc(std::map<std::string, Polynom> polys) {
	for(const auto& p : polys) {
		std::cout << p.second << std::endl;
	}
}

void delFunc(std::vector<std::string> values, std::map<std::string, Polynom>& polys) {
	for (std::string value : values) {
		polys.erase(value);
	}
}

void clearFunc(std::map<std::string, Polynom>& polys) {
	polys.clear();
}

void evalFunc(std::vector<std::string> values, std::map<std::string, Polynom> polys) {
	std::string poly = values[0];
	double sum;
	double in;
	for (size_t i=1; i < values.size(); ++i) {
		in = stof(values[i]);
		sum = polys[poly].eval(in);
		std::cout << poly << "(" << in << ")" << " = " << sum << std::endl;
	}

}

void echoFunc(std::vector<std::string> values) {
	for (std::string value : values) {
		std:: cout << value << " ";
	}
	std::cout << std::endl;
}

void addFunc(std::vector<std::string> values, std::map<std::string, Polynom>& polys) {
	Polynom p = polys[values[1]] + polys[values[2]];
	p.setName(values[0]);
	insertPoly(values[0], p, polys);
}

void multFunc (std::vector<std::string> values, std::map<std::string, Polynom>& polys) {
	Polynom p = polys[values[1]] * polys[values[2]];
	p.setName(values[0]);
	insertPoly(values[0], p, polys);
}

void plotFunc(std::vector<std::string> values, std::map<std::string, Polynom> polys) {
	 Pixels pxs(600);
	 std::string poly = values[0];
	 double x_begin = stof(values[1]);
	 double x_end = stof(values[2]);
	 double width = abs(x_begin) + abs(x_end);
	 double mult = 600.0 / width;
	 double stepSize = 1.0 / mult;
	 int ms = stoi(values[3]) * 1000;
	 double max=polys[poly].eval(x_begin);
	 double min=polys[poly].eval(x_begin);
	 double maxIdx=0;
	 for(double x = x_begin; x < x_end; x+=stepSize) {
		 double y = polys[poly].eval(x);
		 if(y > max) {
			 maxIdx = x;
			 max = y;
		 }
		 if(y < min) {
			 min = y;
		 }
	 }
	 double height = abs(max) + abs(min);
	 double yOffset = (polys[poly].eval(maxIdx)/height)*400;
	 if(yOffset < 0)
		 yOffset = 400 + yOffset;
	 for(double x = x_begin; x<x_end; x+=stepSize) {
		 double y = polys[poly].eval(x);
		 pxs.set((x-x_begin)*100, -((y/height)*400 - yOffset), Gelb);
	 }
	 schlafeMs(ms);
}



