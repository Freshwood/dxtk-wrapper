#pragma once

#include "../Src/DxIncludes.h"
#include "../Src/DxTypes.h"
#include "IDXTKWrapper.h"

namespace DXTKWrapper
{
	using namespace std;

	class CDXTKWrapper : public IDXTKWrapper
	{

    private:

        ID3D11Buffer * m_pVertexBuffer;

		bool Init;

		void Initialize();
		void Reset();
		SpriteFont* retSystemFont(E_DX_SYSTEM_FONTS Font) const;

		shared_ptr<PrimitiveBatch<VertexPositionColor>> primitive;
		shared_ptr<BasicEffect> basicEffect;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;

		void prepareEffect();

    public:

		ID3D11Device * pDevice;
		ID3D11DeviceContext * pContext;
		unique_ptr<SpriteFont> font12, font14, font16, font20, fontTitle, fontText, fontInfo, fontMessage;
		shared_ptr<SpriteBatch> spriteBatch;
		D3D11_VIEWPORT vp;

		explicit CDXTKWrapper(ID3D11Device * m_pDevice, ID3D11DeviceContext * m_pContext);

		virtual ~CDXTKWrapper();

		void ResetAdapters() override;

		void DrawOutlinedText(wstring Text, float x, float y, Color Color, E_DX_SYSTEM_FONTS Font) override;

		void DrawOutlinedTextEx(wstring Text, float x, float y, Color col, Color GlowColor, E_DX_SYSTEM_FONTS Font) override;

		void DrawDxText(wstring Text, float x, float y, Color Color, E_DX_SYSTEM_FONTS Font) override;

		void GradientRectangle(float x, float y, float width, float height, Color startCol, Color endCol, E_DX_GRADIENT_ORIENTATION orientation) override;

		void DrawBorder(float x, float y, float width, float height, Color Color) override;

		void DrawRectangle(float x, float y, float width, float height, Color RecFarbe) override;

		void DrawBox(float x, float y, float width, float height, Color BoxColor, Color BorderColor ) override;

		void DrawBoxGradient(float x, float y, float width, float height, Color BoxColor,Color EndColor, Color BorderColor,E_DX_GRADIENT_ORIENTATION orientation) override;

		void DrawLine(float x, float y, float x2, float y2, Color Color) override;

		void DrawHealthBar(float X,float Y,float Health,float MaxHealth=100.0f) override;

		void DrawBoundingBox(float X,float Y,float Distance,Color Color) override;

		void DrawCrosshair(float size = 12, Color Color = Colors::Red.v) override;

		float retScreenWidth() override;

		float retScreenHeight() override;

		bool IsInitialized() override;
	};	


};