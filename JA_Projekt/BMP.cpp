#include "BMP.h"
using namespace std;

BMP::BMP()
{
    this->width = 0;
    this->height = 0;
    this->size = 0;
    this->BMPData = nullptr;
    this->InfoHeader = nullptr;
    this->binary = nullptr;
    this->result = nullptr;
    this->filename = nullptr;
}

String^ BMP::readBMP(const char* filename)//funkcja wczytuj¹ca obraz BMP
{
    FILE* f;
    regex isbmp("(.)*(\\.bmp)$");

    if (regex_match(filename, isbmp)) {
        if (!(fopen_s(&f, filename, "rb"))) {

            this->filename = filename;
            this->InfoHeader = new unsigned char[54];

            // zczytanie headera
            fread(this->InfoHeader, sizeof(unsigned char), 54, f);

            // odczytanie szerokoœci i wysokoœci z headera
            width = *(int*)&InfoHeader[18];
            height = *(int*)&InfoHeader[22];

            size = ((width * 3 + 3) & (~3)) * height;//¿eby by³o podzielne przez 4

            BMPData = new BYTE[size];
            fread(BMPData, sizeof(BYTE), size, f);//zczytanie danych bmp
            fclose(f);

            return "ok";
        }
        else {
            return "Cannot open image!";
        }
    }
}

void BMP::writeBMP(String^ fname, string mo)
{
    debinarization(result);

    //for (int i = 0; i < height; i++) {
    //    for (int j = 0; j < width; j++) {
    //        cout << result[i * (width) + j];
    //    }
    //    cout << endl;
    //}
    //cout << endl;
    //cout << endl;


    string s = msclr::interop::marshal_as<string>(fname);
    string sub = s.substr(0, s.length() - 4) + mo;
    const char* filename = (sub).c_str();

    FILE* f;
    fopen_s(&f, filename, "wb");
    fwrite(this->InfoHeader, sizeof(unsigned char), 54, f);//zapisanie naglowka
    fwrite(this->BMPData, sizeof(unsigned char), size, f);//zapisanie reszty danych
    fclose(f);

}

void BMP::debinarization(BYTE* result)//bardzo u³omna debinaryzaja
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int w = (width * 3 + 3) & (~3);
            if (result[i * width + j] == 1) {
                this->BMPData[(i * w) + j * 3] = 0;
                this->BMPData[(i * w) + j * 3 + 1] = 0;
                this->BMPData[(i * w) + j * 3 + 2] = 0;
            }
            else {
                this->BMPData[(i * w) + j * 3] = 255;
                this->BMPData[(i * w) + j * 3 + 1] = 255;
                this->BMPData[(i * w) + j * 3 + 2] = 255;
            }
        }
    }
}

void BMP::clear() {
    this->width = 0;
    this->height = 0;
    this->size = 0;
    if (this->InfoHeader)
    {
        delete[] this->InfoHeader;
        this->InfoHeader = nullptr;
    }
    if (this->BMPData)
    {
        delete[] this->BMPData;
        this->BMPData = nullptr;
    }
    if (this->binary)
    {
        delete[] this->binary;
        this->binary = nullptr;
    }
    if (this->result)
    {
        delete[] this->result;
        this->result = nullptr;
    }
    if (this->filename) 
    {
        delete[] this->filename;
        this->filename = nullptr;
    }
}
