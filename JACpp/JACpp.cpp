/*Przekszta³cenia morfologiczne obrazu
Goœciniak Hanna
Informatyka SSI 5 sem. 2020 / 21

Program wykonuje wybrane operacje morfologiczne(erozjê, dylatacje, otwarcie lub zamkniêcie) na obrazach typu bmp.
Po pobraniu nazwy obrazu podanej przez u¿ytkownika oraz poprawnym odczytaniu danych wykonywane s¹ nastêpuj¹ce kroki :
1. „binaryzacja”, czyli zamiana pikseli RGB na wartoœæ 0 lub 1,
2. dodanie ramki do obrazu(skopiowanie brzegów oraz rogów),
3. wykonanie jednej z operacji morfologicznych, które polega na sprawdzaniu w pêtli s¹siedztwa ka¿dego z pikseli i zwróceniu odpowiedniej wartoœci do tablicy wynikowej,
4. „debinaryzacja” – zamiana wartoœci z tablicy wynikowej na RGB oraz
5. zapis do pliku bmp.*/


#include "pch.h"
#include "JACpp.h"


/*void cppbinarization(BYTE* binary, int width, int height, BYTE* BMPData)
Funkcja wykonujaca "binaryzacje", czyli zamiana pikseli RGB na wartoœæ 0 lub 1.
BYTE * binary – wskaŸnik na zbinaryzowan¹ tablicê obrazu, która zostanie wype³niona zerami i jedynkami
int width – szerokoœæ obrazu, wykorzystana w pêtli oraz przy wyliczaniu indeksów tablic
int height – wysokoœæ obrazu, wykorzystana w pêtli
BYTE* BMPData – wskaŸnik na tablicê danych RGB, z której zostaj¹ pobrane odpowiednie wartoœci RGB kolejnych pikseli
*/
JACPP_API void cppbinarization(BYTE* binary, int width, int height, BYTE* BMPData)//binaryzacja
{
    int w = ((width * 3 + 3) & (-4)); //wyrównanie do 4 bajtów
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (((BMPData[(i * w) + j * 3] + BMPData[(i * w) + j * 3 + 1] + BMPData[(i * w) + j * 3 + 2]) / 3) >= 128) //zsumowanie sk³adowych piksela (R + G + B), podzielenie przez 3 i sprawdzenie czy jest wiêksze lub równe od 129
                binary[i * width + j] = 0; //jeœli wiêksze lub równe to do tablicy wynikowej zapisywane jest zero
            else binary[i * width + j] = 1; //jeœli mniejsze to jedynka
        }
    }
}


/*void cppAddFrame(BYTE* binary, int width, int height, BYTE* withFrame)
Funkcja dodaj¹ca ramkê do obrazu(skopiowanie brzegów, rogów oraz ca³ej tablicy binary).
BYTE * binary – wskaŸnik na zbinaryzowan¹ tablicê obrazu bêd¹c¹ Ÿród³em, z którego kopiowane s¹ dane do tablicy wynikowej withFrame
int width – szerokoœæ obrazu, wykorzystana w pêtli oraz przy wyliczaniu indeksów tablic
int height – wysokoœæ obrazu, wykorzystana w pêtli oraz przy wyliczaniu indeksów tablic
BYTE* withFrame - wskaŸnik na tablicê wynikow¹ (obraz z ramk¹)
*/
JACPP_API void cppAddFrame(BYTE* binary, int width, int height, BYTE* withFrame)
{
    //pêtle kopiuj¹ce œrodek (obraz bez ramki)
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            withFrame[(i + 1) * (width + 2) + j + 1] = binary[i * width + j];
        }
    }

    //pêtla kopiuj¹ca górn¹ i doln¹ krawêdŸ
    for (int i = 0; i < width; i++) {
        withFrame[i + 1] = binary[i];
        withFrame[(height + 1) * (width + 2) + 1 + i] = binary[(height - 1) * width + i];
    }

    //pêtla kopiuj¹ca prawy i lewy bok
    for (int i = 0; i < height + 2; i++) {
        withFrame[(width + 2) * i] = withFrame[(width + 2) * i + 1];
        withFrame[(width + 2) * (i + 1) - 1] = withFrame[(width + 2) * (i + 1) - 2];
    }

}

/*BYTE cppDilationCheckNeighbourhood(BYTE* b, int x, int w)
Funkcja sprawdzaj¹ca s¹siedztwo danego piksla x i w zale¿noœci od wyniku zwracaj¹ca odpowiedni¹ wartoœæ (0 lub 1)
BYTE* b - withFrame - wskaŸnik na tablicê zbinaryzowan¹ z dodan¹ ramk¹, w której bêdzie sprawdzane otoczenie piksela
int x - punkt centralny, wokó³ którego bêdzie sprawdzane s¹siedztwo
int w - szerokoœæ obrazu z ramk¹ (szerokoœæ obrazu + 2)
*/
JACPP_API BYTE cppDilationCheckNeighbourhood(BYTE* b, int x, int w)
{
    //sprawdzenie czy choæ jeden s¹siad punktu centralnego jest jedynk¹
    if (b[x - w - 1] == 1 || b[x - 1] == 1 || b[x + w - 1] == 1 || b[x - w] == 1 || b[x + w] == 1 || b[x - w + 1] == 1 || b[x + 1] == 1 || b[x + w + 1] == 1) {
        return 1; //jeœli tak to funkcja zwraca 1
    }
    else return 0; //jeœli ¿aden z s¹siadów nie jest jedynk¹ to funkcja zwraca 0
}

/*BYTE cppErosionCheckNeighbourhood(BYTE* b, int x, int w)
Funkcja sprawdzaj¹ca s¹siedztwo danego piksla x i w zale¿noœci od wyniku zwracaj¹ca odpowiedni¹ wartoœæ (0 lub 1)
BYTE* b - withFrame - wskaŸnik na tablicê zbinaryzowan¹ z dodan¹ ramk¹, w której bêdzie sprawdzane otoczenie piksela
int x - punkt centralny, wokó³ którego bêdzie sprawdzane s¹siedztwo
int w - szerokoœæ obrazu z ramk¹ (szerokoœæ obrazu + 2)
*/
JACPP_API BYTE cppErosionCheckNeighbourhood(BYTE* b, int x, int w)
{
    //sprawdzenie czy wszyscy s¹siedzi punktu centralnego s¹ jedynkami
    if (b[x - w - 1] == 1 && b[x - 1] == 1 && b[x + w - 1] == 1 && b[x - w] == 1 && b[x + w] == 1 && b[x - w + 1] == 1 && b[x + 1] == 1 && b[x + w + 1] == 1) {
        return 1; //jeœli tak to funkcja zwraca 1
    }
    else return 0; //jeœli choæ jeden s¹siad punktu centralnego jest zerem, funkcja zwraca 0
}
