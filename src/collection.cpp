#include "include/collection.h"


collection::~collection() {
	figures.clear();
}

point collection::createPoint() {
	double x = 0;
	double y = 0;
	std::cout << "Podaj wspolrzedne punktu " <<std::endl <<
		"x= "; std::cin >> x;
	while (std::cin.fail()) {
		std::cout << "Blad. Podaj wspolrzedna x ponownie:";
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> x;
	}
	std::cout << std::endl << "y= "; std::cin >> y;
	while (std::cin.fail()) {
		std::cout << "Blad. Podaj wspolrzedna y ponownie:";
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> y;
	}
	system("cls");
	return point(x, y);
}

bool collection::areCollinear(std::vector<point> _points) {
	return (_points[0].getY() - _points[1].getY()) *
		(_points[0].getX() - _points[2].getX()) ==
		(_points[0].getY() - _points[2].getY()) *
		(_points[0].getX() - _points[1].getX());
}

bool collection::isRight(std::vector<point> _points) {
	std::vector<segment> triangleSides;
	std::vector<double> sides;
	auto j = 0;
	for (auto i = 0; i < 3; i++) {
		(i != 2) ? j++ : j = 0;
		triangleSides.push_back(segment(_points[i], _points[j]));
	}
	for (auto s : triangleSides) {
		sides.push_back(s.getLength());
	}
	sort(sides.begin(), sides.end());
	if (pow(sides[0], 2) + pow(sides[1], 2) == pow(sides[2], 2)) return true;
	return false;
}

void collection::checkPoints(std::vector<point>& _points) {
	for (auto i = 0; i < _points.size(); i++) {
		for (auto j = i + 1; j < _points.size(); j++) {
			if (_points[i] == _points[j]) {
				std::cout << "Punkt o indeksie " << i + 1 << " i " << j + 1 << " sa takie same" << std::endl;
				double x, y;
				std::cout << "Podaj nowe wspolrzedne punktu " << std::endl <<
					"x = "; std::cin >> x;
				while (std::cin.fail()) {
					std::cout << "Blad. Podaj wspolrzedna x ponownie:";
					std::cin.clear();
					std::cin.ignore(256, '\n');
					std::cin >> x;
				}
				std::cout << std::endl << "y = "; std::cin >> y;
				while (std::cin.fail()) {
					std::cout << "Blad. Podaj wspolrzedna y ponownie:";
					std::cin.clear();
					std::cin.ignore(256, '\n');
					std::cin >> y;
				}
				point new_point = { x, y };
				while (std::find(_points.begin(), _points.end(), new_point) != _points.end()) {
					std::cout << "Ten punkt juz istnieje w wektorze. Podaj inny punkt: ";
					std::cin >> x >> y;
					while (std::cin.fail()) {
						std::cout << "Blad. Podaj nowe wspolrzedne punktu:";
						std::cin.clear();
						std::cin.ignore(256, '\n');
						std::cin >> x >> y;
					}
					new_point = { x, y };
				}
				_points[j] = new_point;
			}
		}
	}
}

void collection::addFigure() {
	std::vector<point> points;
	int choice = 0;
	double x = 0;
	double y = 0;
	std::cout << "[1] Odcinek" << std::endl <<
		"[2] Trojkat" << std::endl
		<< "Nastepny krok: "; std::cin >> choice;
	switch (choice) {
	case 1:
		for (auto i = 0; i < 2; i++) {
			points.push_back(createPoint());
		}
		checkPoints(points);
		figures.push_back(std::make_unique<segment>(points[0], points[1]));
		std::cout << "Dodano odcinek" << std::endl;
		break;

	case 2:
		for (auto i = 0; i < 3; i++) {
			points.push_back(createPoint());
		}
		checkPoints(points);
		if (!areCollinear(points)) {
			if (isRight(points)) {
				figures.push_back(std::make_unique<right_triangle>(points[0], points[1], points[2]));
				std::cout << "Dodano trojkat prostokatny" << std::endl;
			}
			else {
				figures.push_back(std::make_unique<triangle>(points[0], points[1], points[2]));
				std::cout << "Dodano trojkat " << std::endl;
			}
		}
		else {
			std::cout << "Nie mozna stworzyc trojkata - punkty leza na jednej lini" << std::endl;
		}
		break;

	default:
		std::cout << "Blad. Sprobuj ponownie" << std::endl;
		choice = 0;
		system("cls");
		break;
	}
	points.clear();
}

void collection::displayFigures() const{
	auto i = 1;
	for (auto& f : figures) {
		std::cout << "[" << i << "] " << f->getObjectName() << "   " << f->getObjectCoordinate() << std::endl;
		i++;
	}
}

void collection::pickFigure(int* _choice) const {
	auto choice = 0;
	displayFigures();
	std::cout << "Wybierz figure : "; std::cin >> choice;
	while (std::cin.fail()) {
		std::cout << "Blad. Podaj indeks ponownie:";
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> choice;
	}
	choice--;
	if (choice < 0) {
		std::cout << "Sproboj ponownie";
		system("cls");
		return;
	}
	*_choice = choice;
}

void collection::displaySegments(int* _choice) const {
	int index = 0;
	std::vector<int> indexes;

	for (const auto& f : figures) {
		if (dynamic_cast<segment*>(f.get())) {
			std::cout << index + 1 << ". Odcinek\n";
			indexes.push_back(index);
		}
		index++;
	}

	int choice = -1;
	do {
		std::cout << "Podaj indeks: ";
		std::cin >> choice;
		while (std::cin.fail()) {
			std::cout << "Blad. Podaj indeks ponownie:";
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> choice;
		}
		if (std::find(indexes.begin(), indexes.end(), choice) == indexes.end()) {
			std::cout << "Pod tym indeksem nie ma odcinka, spróbuj ponownie.\n";
		}
	} while (choice < 0 || choice >= index || std::find(indexes.begin(), indexes.end(), choice) == indexes.end());

	*_choice = choice;
}

void collection::displayTriangles(int* _choice) const {
	auto choice = 0;
	auto index = 0;
	std::vector<int> indexes;
	for (const auto& f : figures) {
		if (auto rt = dynamic_cast<right_triangle*>(f.get())) {
			std::cout << index + 1 << ". Trojkat prostokatny " << rt->getObjectCoordinate() << std::endl;
			indexes.push_back(index);
		}
		else if (auto t = dynamic_cast<triangle*>(f.get())) {
			std::cout << index + 1 << ". Trojkat " << t->getObjectCoordinate() << std::endl;
			indexes.push_back(index);
		}
		index++;
	}
	std::cout << "Podaj indeks: "; std::cin >> choice;
	while (std::cin.fail()) {
		std::cout << "Blad. Podaj indeks ponownie:";
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> choice;
	}
	for (auto i : indexes) {
		if (choice - 1 == i) {
			*_choice = choice - 1;
			return;
		}
	}
	std::cout << "Pod tym indeksem nie ma trojkata ani trojkata prostokatnego, sproboj ponownie" << std::endl;
}

void collection::move() {
	auto choice = 0;
	double x = 0;
	double y = 0;
	pickFigure(&choice);
	std::cout << std::endl << "Podaj wektor: x="; std::cin >> x;
	while (std::cin.fail()) {
		std::cout << "Blad. Podaj wspolrzedna x ponownie:";
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> x;
	}
	std::cout << "y="; std::cin >> y;
	while (std::cin.fail()) {
		std::cout << "Blad. Podaj wspolrzedna y ponownie:";
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> y;
	}
	figures[choice]->moveByVector(x,y);
}

void collection::rotate() {
	auto choice = 0;
	pickFigure(&choice);
	double x = 0;
	double y = 0;
	double angle = 0;
	std::cout << std::endl << "Podaj wektor: x="; std::cin >> x;
	while (std::cin.fail()) {
		std::cout << "Blad. Podaj wspolrzedna x ponownie:";
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> x;
	}
	std::cout << "y="; std::cin >> y;
	while (std::cin.fail()) {
		std::cout << "Blad. Podaj wspolrzedna y ponownie:";
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> y;
	}
	std::cout << "Podaj kat (w stopniach):"; std::cin >> angle;
	while (std::cin.fail()) {
		std::cout << "Blad. Podaj kat ponownie:";
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> angle;
	}
	figures[choice]->rotateAroundPoint(x, y, angle);
}

void collection::distance() {
	auto p1 = createPoint();
	auto p2 = createPoint();
	std::cout << "Odleglosc pomiedzy punktami to " << p1.distanceBetweenPoints(p2) << std::endl;
}

void collection::length() {
	int choice = 0;
	displaySegments(&choice);
	if (auto s = dynamic_cast<segment*>(figures[choice].get()))
	{
		std::cout<<"Dlugosc odcinka to "<< s->getLength();
	}
}

void collection::pointOnSegment() const{
	double x, y = 0;
	auto choice = 0;
	std::cout << "Podaj wspolrzedne punktu. x="; std::cin >> x;
	while (std::cin.fail()) {
		std::cout << "Blad. Podaj wspolrzedna x ponownie:";
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> x;
	}
	std::cout << std::endl << "y="; std::cin >> y;
	while (std::cin.fail()) {
		std::cout << "Blad. Podaj wspolrzedna y ponownie:";
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> y;
	}
	std::cout << std::endl;
	auto p = point(x, y);
	displaySegments(&choice);
	if (auto s = dynamic_cast<segment*>(figures[choice].get()))
		(s->isPointOnSegment(p)) ? std::cout << "Punkt znajduje sie na odcinku" : 
			std::cout << "Punkt nie znajduje sie na odcinku";
}

void collection::parallel() {
	auto choice_first = 0;
	auto choice_second = 0;
	displaySegments(&choice_first);
	displaySegments(&choice_second);
	while (choice_first == choice_second) {
		std::cout << "Nie mozesz wybrac tego samego odcinka." << std::endl;
		displaySegments(&choice_second);
	}
	if (auto sf = dynamic_cast<segment*>(figures[choice_first].get())) {
		if (auto ss = dynamic_cast<segment*>(figures[choice_second].get())) {
			segment s = *ss;
			(sf->areParallel(s)) ? std::cout << "Odcinki sa rownolegle" : std::cout << "Odcinki nie sa rownolegle";
		}
	}
}

void collection::perpendicular() {
	auto choice_first = 0;
	auto choice_second = 0;
	displaySegments(&choice_first);
	displaySegments(&choice_second);
	while (choice_first == choice_second) {
		std::cout << "Nie mozesz wybrac tego samego odcinka." << std::endl;
		displaySegments(&choice_second);
	}
	if (auto sf = dynamic_cast<segment*>(figures[choice_first].get())) {
		if (auto ss = dynamic_cast<segment*>(figures[choice_second].get())) {
			segment s = *ss;
			(sf->arePerpendicular(s)) ? std::cout << "Odcinki sa prostopadle" : std::cout << "Odcinki nie sa prostopadle";
		}
	}
}

void collection::intersection() {
	auto choice_first = 0;
	auto choice_second = 0;
	displaySegments(&choice_first);
	displaySegments(&choice_second);
	while (choice_first == choice_second) {
		std::cout << "Nie mozesz wybrac tego samego odcinka." << std::endl;
		displaySegments(&choice_second);
	}
	if (auto sf = dynamic_cast<segment*>(figures[choice_first].get())) {
		if (auto ss = dynamic_cast<segment*>(figures[choice_second].get())) {
			segment s = *ss;
			sf->getIntersectionPoint(s);
		}
	}
}

void collection::areaAndPerimeter() {
	auto choice = 0;
	displayTriangles(&choice);
	if (auto t = dynamic_cast<triangle*>(figures[choice].get())) {
		std::cout << "Pole:" << t->area() << "    Obwod:" << t->perimeter();
	}
}

void collection::disconnected() {
	auto choice_first = 0;
	auto choice_second = 0;
	displayTriangles(&choice_first);
	displayTriangles(&choice_second);
	while (choice_first == choice_second) {
		std::cout << "Nie mozesz wybrac tego samego trojkata." << std::endl;
		displayTriangles(&choice_second);
	}
	if (auto tf = dynamic_cast<triangle*> (figures[choice_first].get())) {
		if (auto ts = dynamic_cast<triangle* > (figures[choice_second].get())) {
			triangle t = *ts;
			(tf->areDisconnected(t)) ? std::cout << "Sa rozlaczne " : std::cout << "Nie sa rozlaczne";
		}
	}
}

void collection::hypotenuse() {
	auto index = 0;
	auto choice = 0;
	auto flag = 0;
	for (auto& f : figures) {
		if (auto rt = dynamic_cast<right_triangle*> (f.get())) {
			std::cout << index + 1 << "Trojkat prostokatny" << rt->getObjectCoordinate() << std::endl;
			flag++;
		}
	}
	if (flag > 0) {
		std::cout << "Wybor: "; std::cin >> choice;
		while (std::cin.fail()) {
			std::cout << "Blad. Podaj indeks ponownie:";
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> choice;
		}
		if (auto rt = dynamic_cast<right_triangle*> (figures[choice].get())) {
			std::cout << "Przeciwprostokata ma wartosc: " << rt->getHypotenuse() << std::endl;
		}
	}
	else std::cout << "Brak trojkatow prostokatnych" << std::endl;
}

void collection::mainApp() {
	auto choice = 0;
	bool loopOn = true;
	while (loopOn) {
		menu(&choice);
		switch (choice) {
		case 1:
			addFigure();
			break;
		case 2:
			displayFigures();
			break;
		case 3:
			move();
			break;
		case 4:
			rotate();
			break;
		case 5:
			distance();
			break;
		case 6:
			length();
			break;
		case 7:
			pointOnSegment();
			break;
		case 8:
			parallel();
			break;
		case 9:
			perpendicular();
			break;
		case 10:
			intersection();
			break;
		case 11:
			areaAndPerimeter();
			break;
		case 12:
			disconnected();
			break;
		case 13:
			hypotenuse();
			break;
		case 14:
			loopOn = false;
			break;
		case 15:
			test();
			break;
		default:
			std::cout << "Blad. Sprobuj ponownie";
			choice = 0;
			break;
		}
		std::string click;
		std::cout << std::endl<<"Kliknij dowolny przycisk aby kontynuowac "; std::cin >> click;
		system("cls");
	}
}

void collection::menu(int* _choice) {
	int choice;
	std::cout << "MENU" << std::endl <<
		"[1] Dodaj figure" << std::endl <<
		"[2] Wyswietl figury" << std::endl <<
		"[3] Przesun figure o wektor" << std::endl <<
		"[4] Obroc figure dookola punktu o zadany kat" << std::endl <<
		"[5] Odleglosc miedzy dwoma punktami" << std::endl <<
		"[6] Obliczanie dlugosci odcinka" << std::endl <<
		"[7] Zbadaj czy punkt lezy na odcinku" << std::endl <<
		"[8] Sprawdz czy odcinki sa rownolegle" << std::endl <<
		"[9] Sprawdz czy odcinki sa prostopadle" << std::endl <<
		"[10] Wyznacz punkt przeciecia odcinkow" << std::endl <<
		"[11] Oblicz obwod i pole trojkata" << std::endl <<
		"[12] Sprawdz czy trojkaty sa rozlaczne" << std::endl <<
		"[13] Sprawdz przeciwprostokatna trojkata prostokatnego" << std::endl <<
		"[14] Wyjscie" << std::endl <<
		"[15] Test" << std::endl <<
		"Nastepny krok: "; std::cin >> choice;
	*(_choice) = choice;
}

int collection::test() {
	auto failedTests = 0;
	auto passedTests = 0;

	point p1 = { 0,0 };
	point p2 = { 3,3 };
	point p3 = { 3,5 };

	p1.movePointByVector(-10, -10);
	if (p1.getX() == -10 && p1.getY() == -10) passedTests++;
	else failedTests++;

	p1.rotatePoint(0, 0, 45);
	if (p1.getX() == 0 && p1.getY() == 0) passedTests++;
	else failedTests++;

	auto d = p2.distanceBetweenPoints(p3);
	(d == 2) ? passedTests++ : failedTests++;

	point p4 = { 0,0 };
	point p5 = { 0,10 };
	point p6 = { 0,5 };

	segment s = { p4,p5 };
	(s.isPointOnSegment(p3)) ? failedTests++ : passedTests++;

	point p7 = { 41,41 };
	point p8 = { 42,42 };
	point p9 = { 4,4 };

	segment s2 = { p2,p7 };
	segment s3 = { p9,p8 };

	(s3.areParallel(s2)) ? passedTests++ : failedTests++;
	(s2.arePerpendicular(s3)) ? failedTests++ : passedTests++;
	

	point p10 = { 0,0 };
	point p11 = { 2,2 };
	point p12 = { 0 , 2 };
	triangle t1 = { p10,p11,p12 };
	if(std::abs(t1.area()-2)<0.25)passedTests++;
	else failedTests++;

	point p13 = { 0,1 };
	point p14 = { 1,0 };

	triangle t2 = { p10,p13,p14 };
	if(std::abs(t2.perimeter() - (double)2 - sqrt(2))<0.6)passedTests++;
	else failedTests++;

	(t1.areDisconnected(t2))? passedTests++ : failedTests++;

	right_triangle rt = { p10,p13,p14 };
	if(std::abs(rt.getHypotenuse()-sqrt(2)<0.1))passedTests++;
	else failedTests++;

	std::cout << "Wynik testow: " << passedTests << "/10";

	return 0;
}