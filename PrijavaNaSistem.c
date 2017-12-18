#include "PrijavaNaSistem.h"
/*
NAPOMENA:
U ulaznoj datoteci podaci su redom upisani kao:
-Ime, Prezime, Korisnicko ime, PIN, Korisnicka grupa (redom!)
Svaka rijec je u novom redu!
*/

void citanjeIzDatoteke(KORISNIK** arr)
{
	FILE* file;
	if (file = fopen("Korisnici.txt", "r"))
	{
		char line[21];
		while (fgets(line, sizeof(line), file)) //Broji koliko ima linija u fajlu
			brojKorisnika++;
		brojKorisnika /= 5; //Broj linija u fajlu podijeljen sa 5 je broj korisnika
		*arr = (KORISNIK*)malloc((brojKorisnika) * sizeof(KORISNIK));
		rewind(file);
		for (int i = 0; i < brojKorisnika; i++)
		{
			fscanf(file, "%s", (*arr)[i].ime);
			fscanf(file, "%s", (*arr)[i].prezime);
			fscanf(file, "%s", (*arr)[i].korisnicko_ime);
			fscanf(file, "%s", (*arr)[i].PIN);
			fscanf(file, "%s", (*arr)[i].korisnicka_grupa);
		}
		fclose(file);
		return arr;
	}
	else
		printf("%s\n", _ERROR_VALUE);
	return NULL;
}


int provjeraKorisnika(char* k_ime, char* pin, KORISNIK* arr, KORISNIK* ret)  
{
	for (int i = 0; i < brojKorisnika; ++i)
		if (!strcmp(arr[i].korisnicko_ime, k_ime) && !strcmp(arr[i].PIN, pin))
		{
			*ret = arr[i];
			return 1;
		}
	return 0;
}


int prijavaNaSistem(KORISNIK* arr, KORISNIK* ret)  //Pomocu 'KORISNIK* ret' se vraca ulogovani korisnik!
{
	char k_ime[21], pin[10];
	printf("\n	Unesite korisnicko ime: ");
	scanf("%s", k_ime);
	printf("\n	Unesite PIN: ");
	scanf("%s", pin);
	if (!provjeraPINa(pin))
	{
		printf("Nepravilno unesen PIN!");
		return 0;
	}
	return provjeraKorisnika(k_ime, pin, arr, ret);
}


int provjeraPINa(char* pin) //Provjerava duzinu PIN-a i da li su sve cifre
{
	if (strlen(pin) != 4)
		return 0;
	for (int i = 0; i < 4; ++i)
		if (!isdigit(pin[i]))
			return 0;
	return 1;
}