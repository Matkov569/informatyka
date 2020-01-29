#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>         
#include <ctime> 
#include <fstream>
#include <random>
using namespace std;

random_device device;
mt19937 generator(device());

enum TypAlbumu { KLASYCZNA, ROCK, POP, DISCOPOLO, RAP, JAZZ, INNA };

struct AlbumMuzyczny {
	string tytul;
	int liczbaUtworow;
	string* listaUtworow;
	TypAlbumu typ;
	void drukuj() {
		cout <<"\"" << tytul << "\"" << endl;
		for (int i = 0; i < liczbaUtworow; i++) {
			cout << i+1<<". "<< listaUtworow[i] << endl;
		}
	};
};



AlbumMuzyczny stworzAlbum(string tyt, int licz, string* lista, TypAlbumu typ) {
	AlbumMuzyczny obj;
	obj.tytul = tyt;
	obj.liczbaUtworow = licz;
	obj.listaUtworow = lista;
	obj.typ = typ;
	return obj;
}	

double calkowanieMC(double (*fun)(double), double a, double b, double d, int n) {
	double pole = d * (b - a);
	uniform_real_distribution<double> distribution(0, d);
	uniform_real_distribution<double> distribution1(a, b);
	int licznik = 0;
	double y, x;
	for (int i = 0; i < n; i++) {
		
		y = distribution(generator);
		x = distribution1(generator);

		if (fun(x) > y) licznik++;

	}
	return (licznik * pole / n );
}

double funkcja(double x) {
	return x * x;
}

void zapisz(double wyn, int n) {
	fstream plik;
	if (n == 50) {
		plik.open("wynik.txt", ios::out | ios::trunc);
	}
	else {
		plik.open("wynik.txt", ios::out | ios::app);
	}
	plik << "n = " << n << " wynik: " << wyn << endl;
	plik.close();
}

int main() {

	AlbumMuzyczny* album = new AlbumMuzyczny[4];

	string tab1[]{ "Toccata i fuga w g-dur","Fuga e-moll","Toccata cis-dur","Toccata i fuga w d-moll" };
	string tab2[]{ "Eine Kleine Nacht Music","Rondo alla Turca"};
	string tab3[]{ "Zly romans","Makarena","Numanej"};
	string tab4[]{"Wiatr","Tamagotchi","Deszcz na betonie","Fiji"};


	album[0] = stworzAlbum("J. S. Bach - skladanka biesiadna", 4, tab1, KLASYCZNA);
	album[1] = stworzAlbum("Mozart - nie za duzo, nie za malo", 2, tab2, KLASYCZNA);
	album[2] = stworzAlbum("Lejdi Zgaga i przyjaciele: hity minionego stulecia", 3, tab3, POP);
	album[3] = stworzAlbum("Taco Hemingway - album",4,tab4,RAP);

	for (int i = 0; i < 4; i++) {
		album[i].drukuj();
		cout << "=====" << endl;
	}


	double wyn = calkowanieMC(funkcja, 1, 3, 9, 50);
	zapisz(wyn, 50);
	wyn = calkowanieMC(funkcja, 1, 3, 9, 500);
	zapisz(wyn, 500);
	wyn = calkowanieMC(funkcja, 1, 3, 9, 2000);
	zapisz(wyn, 2000);
	cout << "Wyniki calkowania zostaly zapisane do pliku. \nNacisnij enter, aby zakonczyc...";
	delete[] album;
	getchar();
	return 0;
}