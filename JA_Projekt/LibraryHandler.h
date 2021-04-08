#pragma once
#include "BMP.h"
#include "JACpp.h"

extern "C" void asmAddFrame(BYTE* binary, int width, int height, BYTE * withFrame);
extern "C" BYTE asmDilationCheckNeighbourhood(BYTE* b, int x, int w);
extern "C" BYTE asmErosionCheckNeighbourhood(BYTE* b, int x, int w);

ref class LibraryHandler
{
public:
	void eroSquare(Object^ obj);
	void dilSquare(Object^ obj);
	void erosion(BMP^ bmp, bool cpp, int numberOfThreads);
	void dilation(BMP^ bmp, bool cpp, int numberOfThreads);
	void opening(BMP^ bmp, bool cpp, int numberOfThreads);
	void closing(BMP^ bmp, bool cpp, int numberOfThreads);
};

