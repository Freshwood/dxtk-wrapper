#include "IDXTKWrapper.h"

namespace DXTKWrapper
{
	Color IDXTKWrapper::retColorCode(E_DX_SYSTEM_COLORS Colors)
	{
		switch (Colors){
		case 0: return Colors::Red.v;
		case 1: return Colors::Green.v;
		case 2: return Colors::Blue.v;
		case 3: return Colors::Turquoise.v;
		case 4: return Colors::Azure.v;
		case 5: return Colors::Yellow.v;
		case 6: return Colors::Black.v;
		case 7: return Colors::Gray.v;
		case 8: return Colors::White.v;
		case 9: return Colors::Orange.v;
		case 10: return Colors::Purple.v;
		default: return Colors::Blue.v;
		}	
	}

	wchar_t* IDXTKWrapper::retColorName(int Colors)
	{
		switch (Colors){
		case 0: return L"Red";
		case 1: return L"Green";
		case 2: return L"Blue";
		case 3: return L"Cyan";
		case 4: return L"Light Blue";
		case 5: return L"Yellow";
		case 6: return L"Black";
		case 7: return L"Gray";
		case 8: return L"White";
		case 9: return L"Orange";
		case 10: return L"Purple";
		default: return L"Blue";
		}	
	}
};