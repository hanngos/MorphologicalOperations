#pragma once

#ifdef JACPP_EXPORTS
#define JACPP_API __declspec(dllexport)
#else
#define JACPP_API __declspec(dllimport)
#endif

extern "C" JACPP_API void cppbinarization(BYTE * binary, int width, int height, BYTE * BMPData);
extern "C" JACPP_API void cppAddFrame(BYTE* binary, int width, int height, BYTE* withFrame);
//extern "C" JACPP_API void cppDilationCheckNeighbourhood(BYTE * b, int i, int j, int w, BYTE * result);
extern "C" JACPP_API BYTE cppDilationCheckNeighbourhood(BYTE * b, int x, int w);
extern "C" JACPP_API BYTE cppErosionCheckNeighbourhood(BYTE * b, int x,  int w);
