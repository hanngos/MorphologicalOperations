#include "LibraryHandler.h"

using namespace std;
using namespace System::Windows::Forms;
using namespace System::Collections;
using namespace System::Threading;
using namespace System::Threading::Tasks;


void LibraryHandler::dilSquare(Object^ obj)
{
    Tuple<bool, BMP^, int, int>^ params = (Tuple<bool, BMP^, int, int>^) obj;

    if (params->Item1 == true) {
        for (int s = params->Item3; s < params->Item3 + params->Item4; s++) {
            int j = (s - 1) % (params->Item2->width) + 1;
            int i = (s - j) / (params->Item2->width);
            int x = (i * (params->Item2->width + 2)) + j;
            params->Item2->result[((i - 1) * (params->Item2->width)) + (j - 1)] = cppDilationCheckNeighbourhood(params->Item2->withFrame, x, (params->Item2->width + 2));
        }
    }
    else {
        for (int s = params->Item3; s < params->Item3 + params->Item4; s++) {
            int j = (s - 1) % (params->Item2->width) + 1;
            int i = (s - j) / (params->Item2->width);
            int x = (i * (params->Item2->width + 2)) + j;
            params->Item2->result[((i - 1) * (params->Item2->width)) + (j - 1)] = asmDilationCheckNeighbourhood(params->Item2->withFrame, x, (params->Item2->width + 2));
        }
    }
}

void LibraryHandler::eroSquare(Object^ obj)
{
    Tuple<bool, BMP^, int, int>^ params = (Tuple<bool, BMP^, int, int>^) obj;

    if (params->Item1 == true) {
        for (int s = params->Item3; s < params->Item3 + params->Item4; s++) {
            int j = (s - 1) % (params->Item2->width) + 1;
            int i = (s - j) / (params->Item2->width);
            int x = (i * (params->Item2->width + 2)) + j;
            params->Item2->result[((i - 1) * (params->Item2->width)) + (j - 1)] = cppErosionCheckNeighbourhood(params->Item2->withFrame, x, (params->Item2->width + 2));
        }
    }
    else {
        for (int s = params->Item3; s < params->Item3 + params->Item4; s++) {
            int j = (s - 1) % (params->Item2->width) + 1;
            int i = (s - j) / (params->Item2->width);
            int x = (i * (params->Item2->width + 2)) + j;
            params->Item2->result[((i - 1) * (params->Item2->width)) + (j - 1)] = asmErosionCheckNeighbourhood(params->Item2->withFrame, x, (params->Item2->width + 2));
        }
    }
}

void LibraryHandler::erosion(BMP^ bmp, bool cpp, int numberOfThreads)
{
    Generic::List<Task^>^ listOfThreads = gcnew Generic::List<Task^>();
    
    bmp->withFrame = new BYTE[(bmp->height + 2) * (bmp->width + 2)];

    if (cpp == true) {
        cppAddFrame(bmp->binary, bmp->width, bmp->height, bmp->withFrame);
    }
    else {
        asmAddFrame(bmp->binary, bmp->width, bmp->height, bmp->withFrame);
    }

    int l = bmp->width * bmp->height / numberOfThreads;
    int s = bmp->width + 1;
    for (int i = 0; i < numberOfThreads; i++) {
       
        Tuple<bool, BMP^, int, int>^ param;
        if (i == numberOfThreads - 1) {
            int d = l + ((bmp->width * bmp->height) % numberOfThreads);
            param = gcnew Tuple<bool, BMP^, int, int>(cpp, bmp, s, d);
        }
        else {
            param = gcnew Tuple<bool, BMP^, int, int>(cpp, bmp, s, l);
        }
        listOfThreads->Add(Task::Factory->StartNew((Action<Object^>^)(gcnew Action<Object^>(this, &LibraryHandler::eroSquare)), param));
        s += l;

        //Tuple<bool, BMP^, int, int>^ param;
        //if (i == numberOfThreads - 1) {
        //    int d = l + ((bmp->width * bmp->height) % numberOfThreads);
        //    param = gcnew Tuple<bool, BMP^, int, int>(cpp, bmp, s, d);
        //}
        //else {
        //    param = gcnew Tuple<bool, BMP^, int, int>(cpp, bmp, s, l);
        //}
        //Thread^ t = gcnew Thread(gcnew ParameterizedThreadStart(eroSquare));
        //t->Start(param);
        //t->Join();
        //s += l;
    }
    Task::WaitAll(listOfThreads->ToArray());
}

void LibraryHandler::dilation(BMP^ bmp, bool cpp, int numberOfThreads)
{
    Generic::List<Task^>^ listOfThreads = gcnew Generic::List<Task^>();
    
    bmp->withFrame = new BYTE[(bmp->height + 2) * (bmp->width + 2)];

    if (cpp == true) {
        cppAddFrame(bmp->binary, bmp->width, bmp->height, bmp->withFrame);
    }
    else {
        asmAddFrame(bmp->binary, bmp->width, bmp->height, bmp->withFrame);
    }

    int l = bmp->width * bmp->height / numberOfThreads;
    int s = bmp->width + 1;
    for (int i = 0; i < numberOfThreads; i++) {
        Tuple<bool, BMP^, int, int>^ param;
        if (i == numberOfThreads - 1) {
            int d = l + ((bmp->width * bmp->height) % numberOfThreads);
            param = gcnew Tuple<bool, BMP^, int, int>(cpp, bmp, s, d);
        }
        else {
            param = gcnew Tuple<bool, BMP^, int, int>(cpp, bmp, s, l);
        }

        listOfThreads->Add(Task::Factory->StartNew((Action<Object^>^)(gcnew Action<Object^>(this, &LibraryHandler::dilSquare)), param));
        s += l;

        /*Thread^ t = gcnew Thread(gcnew ParameterizedThreadStart(this, &LibraryHandler::dilSquare));
        t->Start(param);
        t->Join();
        s += l;*/
    }
    Task::WaitAll(listOfThreads->ToArray());
}

void LibraryHandler::opening(BMP^ bmp, bool cpp, int numberOfThreads)
{
    erosion(bmp, cpp, numberOfThreads);
    bmp->binary = bmp->result;  
    dilation(bmp, cpp, numberOfThreads);
}

void LibraryHandler::closing(BMP^ bmp, bool cpp, int numberOfThreads)
{
    dilation(bmp, cpp, numberOfThreads);
    bmp->binary = bmp->result;
    erosion(bmp, cpp, numberOfThreads);   
}
