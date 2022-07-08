// KolosPkTU2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>



///////////////////////////////////////////////////////////////////////////////////////
//BITOWANIE
///////////////////////////////////////////////////////////////////////////////////////
using text = char[50];

enum class TypLeku { antybiotyk, suplemnet, witamina, syrop };

struct Lek
{
	text producent, nazwa;
	int dawka;
	TypLeku typ;
	bool naRcepepte;
};

void wypelnijDane(Lek* l, const text producent, const text nazwa, int dawka, TypLeku typ, bool recepta)
{
	strcpy(l->producent, producent);
	strcpy(l->nazwa, nazwa);
	l->dawka = dawka;
	l->typ = typ;
	l->naRcepepte = recepta;
}

unsigned char kodowanie(Lek* l) {

	unsigned char kod = 0;

	kod = l->dawka;

	kod = (kod << 2);
	kod += (int)l->typ;

	kod = (kod << 1);
	kod += (bool)l->naRcepepte;
	return kod;
}

void dekodowanie(Lek* l, unsigned char kod) {

	l->naRcepepte = (bool)(kod % 2);
	kod = kod >> 1;

	l->typ = (TypLeku)(kod % 4);
	kod = kod >> 2;

	l->dawka = (int)kod % 16;
}

void zapisPlik(FILE* file, Lek* tab, int size) {
	if (file != nullptr) {
		for (int i = 0; i < size; i++) {
			fprintf(file, "%s;  %s; %hhx\n", tab[i].producent, tab[i].nazwa, kodowanie(tab));
		}
		fclose(file);
	}
}

void odczytPlik(FILE* file, int numer, Lek* l) {
	if (file != nullptr) {
		unsigned char kod;
		fscanf(file, "%s; ", l->producent);
		fscanf(file, "%s; ", l->nazwa);
		fscanf(file, "%hhx\n", &kod);

		dekodowanie(l, kod);
	}
}

std::ostream& operator<< (std::ostream& str, Lek& l)
{
	str << l.producent << " " << l.nazwa << " Czy na recepte " << (int)l.naRcepepte << " Typ leku: " << (int)l.typ << " Dawka: " << (int)l.dawka << endl;
	return str;
}

int main()
{
	Lek l1, l2, l3, l4;
	wypelnijDane(&l1, "Bayer", "Aviomarin", 2, TypLeku::syrop, true);
	wypelnijDane(&l2, "USP Zdrowie", "Ibuprom", 3, TypLeku::suplemnet, true);
	wypelnijDane(&l3, "Witaminki", "Witamina C++", 3, TypLeku::witamina, true);

	Lek tab[] = { l1, l2, l3 };
	const int rozmiarLeki = sizeof(tab) / sizeof(tab[0]);

	FILE* file = fopen("leki.txt", "w");
	zapisPlik(file, tab, rozmiarLeki);
	fclose(file);

	FILE* fileRead = fopen("leki.txt", "r");
	odczytPlik(fileRead, 1, &l4);
	fclose(fileRead);
	cout << l4;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///Dynamiczna alokacja
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
// Kodowanie.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

#define zad2



#ifdef zad1

using text = char[50];

enum class Plec { kobieta, mezczyzna };
enum class StanCywilny { wolny, wZwiazku, rozwodnik, wdowiec };


struct Osoba
{
	text imie, nazwisko;
	int wiek;
	Plec plec;
	StanCywilny stan;
};

void wypelnijDane(Osoba* o, const text imie, const text nazwisko, int rok, StanCywilny st, Plec pl)
{
	strcpy(o->imie, imie);
	strcpy(o->nazwisko, nazwisko);
	o->wiek = rok;
	o->stan = st;
	o->plec = pl;
}

short kodowanie(Osoba* os) {
	//Wiek
	short kod = 0;
	kod = os->wiek;

	//Stan cywilny
	kod = (kod << 2);
	kod += (int)os->stan;

	//Plec
	kod = (kod << 1);
	kod += (int)os->plec;
	return kod;
}

void dekodowanie(Osoba* os, short kod) {

	os->plec = (Plec)(kod % 2);

	kod = kod >> 1;
	os->stan = (StanCywilny)(kod % 4);

	kod = kod >> 2;
	os->wiek = (int)(kod % 128);
}

void zapisDoPliku(Osoba* tab, FILE* file, int size) {
	if (file != nullptr) {
		for (int i = 0; i < size; i++) {
			fprintf(file, "%s;  %s; %hu\n", tab[i].imie, tab[i].nazwisko, kodowanie(tab));
		}
		fclose(file);
	}
}

void odczyt(FILE* file, int numer, Osoba* os) {
	if (file != nullptr) {
		short kod;
		fscanf(file, "%s; ", os->imie);
		fscanf(file, "%s; ", os->nazwisko);
		fscanf(file, "%hu", &kod);

		dekodowanie(os, kod);
	}
}

std::ostream& operator<< (std::ostream& str, Osoba& os)
{
	str << os.imie << " " << os.nazwisko << " " << os.wiek << " " << (int)os.plec << std::endl;
	return str;
}

int main()
{
	Osoba o01, o02;
	wypelnijDane(&o01, "Andrzej", "Kowalski", 13, StanCywilny::rozwodnik, Plec::mezczyzna);
	wypelnijDane(&o02, "Jan", "Rapowanie", 13, StanCywilny::rozwodnik, Plec::mezczyzna);
	Osoba tab[] = { o01, o02 };

	FILE* file = fopen("zapisDoPliku.txt", "w");
	zapisDoPliku(tab, file, 2);
	fclose(file);

	Osoba o03;
	FILE* fileRead = fopen("zapisDoPliku.txt", "r");
	odczyt(fileRead, 1, &o03);
	fclose(fileRead);
	cout << o03;
}

#endif

#ifdef zad2

enum class TypPojazdu { motocykl, smaochodOsobowy, smaochodCiezarowy, Ciagnik };
using text = char[50];

struct Pojazd
{
	text marka, model;
	int rocznik;
	TypPojazdu typ;
	bool dopuszczonyDoRuchu;
};


short kodowanie(Pojazd* p) {
	short kod = 0;

	kod = p->rocznik;

	kod = kod << 2;
	kod += (int)p->typ;

	kod = kod << 1;
	kod += (int)p->dopuszczonyDoRuchu;
	return kod;
}

void dekodowanie(Pojazd* p, short kod) {
	p->dopuszczonyDoRuchu = (bool)(kod % 2);
	kod = kod >> 1;

	p->typ == (TypPojazdu)(kod % 4);
	kod = kod >> 2;

	p->rocznik = (int)(kod % 2048);
}

void zapisPlik(Pojazd* tab, FILE* file, int size) {
	if (file != nullptr) {
		for (int i = 0; i < size; i++) {
			fprintf(file, "%s; %s; %hu\n", tab[i].marka, tab[i].model, kodowanie(tab));
		}
		fclose(file);
	}
}

void odczytPlik(FILE* file, int numer, Pojazd* p) {
	if (file != nullptr) {
		short kod;
		fscanf(file, "%s; ", p->marka);
		fscanf(file, "%s; ", p->model);
		fscanf(file, "%hu\n", &kod);
		dekodowanie(p, kod);
	}
}

std::ostream& operator<< (std::ostream& str, Pojazd& p)
{
	str << p.marka << " " << p.model << " " << p.rocznik << " " << (int)p.dopuszczonyDoRuchu << std::endl;
	return str;
}

void wypelnijDane(Pojazd* p, const text marka, const text model, int rok, bool dopuszczony, TypPojazdu typ)
{
	strcpy(p->marka, marka);
	strcpy(p->model, model);
	p->rocznik = rok;
	p->dopuszczonyDoRuchu = dopuszczony;
	p->typ = typ;
}

int main()
{
	Pojazd p01, p02, p03, p04;
	wypelnijDane(&p01, "Opel", "Corsa", 2003, true, TypPojazdu::smaochodOsobowy);
	wypelnijDane(&p02, "Audi", "A3", 2005, true, TypPojazdu::smaochodOsobowy);
	wypelnijDane(&p03, "Mercedes", "AMG GT", 2019, true, TypPojazdu::smaochodOsobowy);
	Pojazd tab[] = { p01, p02, p03 };
	int sizePojazdTab = sizeof(tab) / sizeof(tab[0]);

	FILE* file = fopen("pojazdy.txt", "w");
	zapisPlik(tab, file, sizePojazdTab);
	fclose(file);

	FILE* fileRead = fopen("pojazdy.txt", "r");
	odczytPlik(fileRead, 0, &p04);
	fclose(fileRead);
	cout << p04;
}
