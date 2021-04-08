/*Przekszta�cenia morfologiczne obrazu
Go�ciniak Hanna
Informatyka SSI 5 sem. 2020 / 21

Program wykonuje wybrane operacje morfologiczne(erozj�, dylatacje, otwarcie lub zamkni�cie) na obrazach typu bmp.
Po pobraniu nazwy obrazu podanej przez u�ytkownika oraz poprawnym odczytaniu danych wykonywane s� nast�puj�ce kroki :
1. �binaryzacja�, czyli zamiana pikseli RGB na warto�� 0 lub 1,
2. dodanie ramki do obrazu(skopiowanie brzeg�w oraz rog�w),
3. wykonanie jednej z operacji morfologicznych, kt�re polega na sprawdzaniu w p�tli s�siedztwa ka�dego z pikseli i zwr�ceniu odpowiedniej warto�ci do tablicy wynikowej,
4.��debinaryzacja� � zamiana warto�ci z tablicy wynikowej na RGB oraz
5. zapis do pliku bmp.*/


#include "pch.h"
#include "JACpp.h"


/*void cppbinarization(BYTE* binary, int width, int height, BYTE* BMPData)
Funkcja wykonujaca "binaryzacje", czyli zamiana pikseli RGB na warto�� 0 lub 1.
BYTE * binary � wska�nik na zbinaryzowan� tablic� obrazu, kt�ra zostanie wype�niona zerami i jedynkami
int width � szeroko�� obrazu, wykorzystana w p�tli oraz przy wyliczaniu indeks�w tablic
int height � wysoko�� obrazu, wykorzystana w p�tli
BYTE* BMPData � wska�nik na tablic� danych RGB, z kt�rej zostaj� pobrane odpowiednie warto�ci RGB kolejnych pikseli
*/
JACPP_API void cppbinarization(BYTE* binary, int width, int height, BYTE* BMPData)//binaryzacja
{
    int w = ((width * 3 + 3) & (-4)); //wyr�wnanie do 4 bajt�w
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (((BMPData[(i * w) + j * 3] + BMPData[(i * w) + j * 3 + 1] + BMPData[(i * w) + j * 3 + 2]) / 3) >= 128) //zsumowanie sk�adowych piksela (R + G + B), podzielenie przez 3 i sprawdzenie czy jest wi�ksze lub r�wne od 129
                binary[i * width + j] = 0; //je�li wi�ksze lub r�wne to do tablicy wynikowej zapisywane jest zero
            else binary[i * width + j] = 1; //je�li mniejsze to jedynka
        }
    }
}


/*void cppAddFrame(BYTE* binary, int width, int height, BYTE* withFrame)
Funkcja dodaj�ca ramk� do obrazu(skopiowanie brzeg�w, rog�w oraz ca�ej tablicy binary).
BYTE * binary � wska�nik na zbinaryzowan� tablic� obrazu b�d�c� �r�d�em, z kt�rego kopiowane s� dane do tablicy wynikowej withFrame
int width � szeroko�� obrazu, wykorzystana w p�tli oraz przy wyliczaniu indeks�w tablic
int height � wysoko�� obrazu, wykorzystana w p�tli oraz przy wyliczaniu indeks�w tablic
BYTE* withFrame - wska�nik na tablic� wynikow� (obraz z ramk�)
*/
JACPP_API void cppAddFrame(BYTE* binary, int width, int height, BYTE* withFrame)
{
    //p�tle kopiuj�ce �rodek (obraz bez ramki)
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            withFrame[(i + 1) * (width + 2) + j + 1] = binary[i * width + j];
        }
    }

    //p�tla kopiuj�ca g�rn� i doln� kraw�d�
    for (int i = 0; i < width; i++) {
        withFrame[i + 1] = binary[i];
        withFrame[(height + 1) * (width + 2) + 1 + i] = binary[(height - 1) * width + i];
    }

    //p�tla kopiuj�ca prawy i lewy bok
    for (int i = 0; i < height + 2; i++) {
        withFrame[(width + 2) * i] = withFrame[(width + 2) * i + 1];
        withFrame[(width + 2) * (i + 1) - 1] = withFrame[(width + 2) * (i + 1) - 2];
    }

}

/*BYTE cppDilationCheckNeighbourhood(BYTE* b, int x, int w)
Funkcja sprawdzaj�ca s�siedztwo danego piksla x i w zale�no�ci od wyniku zwracaj�ca odpowiedni� warto�� (0 lub 1)
BYTE* b - withFrame - wska�nik na tablic� zbinaryzowan� z dodan� ramk�, w kt�rej b�dzie sprawdzane otoczenie piksela
int x - punkt centralny, wok� kt�rego b�dzie sprawdzane s�siedztwo
int w - szeroko�� obrazu z ramk� (szeroko�� obrazu + 2)
*/
JACPP_API BYTE cppDilationCheckNeighbourhood(BYTE* b, int x, int w)
{
    //sprawdzenie czy cho� jeden s�siad punktu centralnego jest jedynk�
    if (b[x - w - 1] == 1 || b[x - 1] == 1 || b[x + w - 1] == 1 || b[x - w] == 1 || b[x + w] == 1 || b[x - w + 1] == 1 || b[x + 1] == 1 || b[x + w + 1] == 1) {
        return 1; //je�li tak to funkcja zwraca 1
    }
    else return 0; //je�li �aden z s�siad�w nie jest jedynk� to funkcja zwraca 0
}

/*BYTE cppErosionCheckNeighbourhood(BYTE* b, int x, int w)
Funkcja sprawdzaj�ca s�siedztwo danego piksla x i w zale�no�ci od wyniku zwracaj�ca odpowiedni� warto�� (0 lub 1)
BYTE* b - withFrame - wska�nik na tablic� zbinaryzowan� z dodan� ramk�, w kt�rej b�dzie sprawdzane otoczenie piksela
int x - punkt centralny, wok� kt�rego b�dzie sprawdzane s�siedztwo
int w - szeroko�� obrazu z ramk� (szeroko�� obrazu + 2)
*/
JACPP_API BYTE cppErosionCheckNeighbourhood(BYTE* b, int x, int w)
{
    //sprawdzenie czy wszyscy s�siedzi punktu centralnego s� jedynkami
    if (b[x - w - 1] == 1 && b[x - 1] == 1 && b[x + w - 1] == 1 && b[x - w] == 1 && b[x + w] == 1 && b[x - w + 1] == 1 && b[x + 1] == 1 && b[x + w + 1] == 1) {
        return 1; //je�li tak to funkcja zwraca 1
    }
    else return 0; //je�li cho� jeden s�siad punktu centralnego jest zerem, funkcja zwraca 0
}
