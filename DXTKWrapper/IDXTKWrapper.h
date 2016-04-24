#pragma once

#include "DxIncludes.h"
#include "DxTypes.h"

namespace DXTKWrapper
{	
	using namespace std;

	class IDXTKWrapper
	{
		
	public:
		virtual ~IDXTKWrapper()
		{
		}

		virtual void ResetAdapters() = 0;

		virtual void DrawOutlinedText(wstring Text, float x, float y, Color col,E_DX_SYSTEM_FONTS Font) = 0;

		virtual void DrawOutlinedTextEx(wstring Text, float x, float y, Color col, Color GlowColor, E_DX_SYSTEM_FONTS Font) = 0;

		virtual void DrawDxText(wstring Text, float x, float y, Color fontColor, E_DX_SYSTEM_FONTS Font) = 0;

		virtual void GradientRectangle(float x, float y, float width, float height, Color startCol, Color endCol, E_DX_GRADIENT_ORIENTATION orientation) = 0;

		virtual void DrawBorder(float Xa, float Ya, float Width, float Height, Color Color) = 0;

		virtual void DrawRectangle(float x, float y, float width, float height, Color RecFarbe) = 0;

		virtual void DrawBox(float x, float y, float w, float h, Color BoxColor, Color BorderColor) = 0;

		virtual void DrawBoxGradient(float x, float y, float w, float h, Color BoxColor, Color EndColor, Color BorderColor, E_DX_GRADIENT_ORIENTATION orientation) = 0;

		virtual void DrawLine(float Xa, float Ya, float Xb, float Yb, Color Color) = 0;

		virtual void DrawHealthBar(float X, float Y, float Health, float MaxHealth = 100.0f) = 0;

		virtual void DrawBoundingBox(float X, float Y, float Distance, Color Color) = 0;

		virtual void DrawCrosshair(float size = 12, Color Color = Colors::Red.v) = 0;

		virtual float retScreenWidth() = 0;

		virtual float retScreenHeight() = 0;

		virtual bool IsInitialized() = 0;

		static Color retColorCode(E_DX_SYSTEM_COLORS Colors);

		static wchar_t* retColorName(int Colors);
	};
};