#pragma once

#include "DxIncludes.h"

namespace DXTKWrapper
{
	using namespace DirectX;
	using namespace SimpleMath;

	//Enum der Farben
	enum E_DX_SYSTEM_COLORS {
		DX_RED,DX_GREEN,Blue,Turkies,Azure,Yellow,Black,Gray,White,Orange,Purple
	};

	// Velauf Orientation
	enum E_DX_GRADIENT_ORIENTATION {
		DX_ORIENTATION_HORZIZONTAL = 0,
		DX_ORIENTATION_VERTICAL = 1,
		DX_ORIENTATION_FORWARD_DIAGONAL = 2,
		DX_ORIENTATION_BACKWARD_DIAGONAL = 3
	};

	enum E_DX_SYSTEM_FONTS{
		DX_SYSTEM_FONT_12,
		DX_SYSTEM_FONT_14,
		DX_SYSTEM_FONT_16,
		DX_SYSTEM_FONT_20,
		DX_SYSTEM_FONT_TITLE,
		DX_SYSTEM_FONT_TEXT,
		DX_SYSTEM_FONT_INFO,
		DX_SYSTEM_FONT_MESSAGE
	};
};