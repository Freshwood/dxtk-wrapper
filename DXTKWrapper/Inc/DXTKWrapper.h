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

		void BuildFontFromResources();

		void PrepareEffect();

    public:

		ID3D11Device * pDevice;
		ID3D11DeviceContext * pContext;
		unique_ptr<SpriteFont> font12, font14, font16, font20, fontTitle, fontText, fontInfo, fontMessage;
		shared_ptr<SpriteBatch> spriteBatch;
		D3D11_VIEWPORT vp;

		explicit CDXTKWrapper(ID3D11Device * m_pDevice, ID3D11DeviceContext * m_pContext);

		virtual ~CDXTKWrapper();

		void ResetAdapters() override;

		void DrawOutlinedText(wstring text, float x, float y, Color color, E_DX_SYSTEM_FONTS systemFont) override;

		void DrawOutlinedTextEx(wstring text, float x, float y, Color col, Color glowColor, E_DX_SYSTEM_FONTS systemFont) override;

		void DrawDxText(wstring text, float x, float y, Color color, E_DX_SYSTEM_FONTS systemFont) override;

		void GradientRectangle(float x, float y, float width, float height, Color startCol, Color endCol, E_DX_GRADIENT_ORIENTATION orientation) override;

		void DrawBorder(float x, float y, float width, float height, Color color) override;

		void DrawRectangle(float x, float y, float width, float height, Color rectangleColor) override;

		void DrawBox(float x, float y, float width, float height, Color boxColor, Color borderColor ) override;

		void DrawBoxGradient(float x, float y, float width, float height, Color boxColor,Color endColor, Color borderColor,E_DX_GRADIENT_ORIENTATION orientation) override;

		void DrawLine(float x, float y, float x2, float y2, Color color) override;

		void DrawHealthBar(float x, float y, float health, float maxHealth = 100.0f) override;

		void DrawBoundingBox(float x, float y, float distance, Color color) override;

		void DrawCrosshair(float size = 12, Color color = Colors::Red.v) override;

		float GetScreenWidth() override;

		float GetScreenHeight() override;

		bool IsInitialized() override;
	};	


};