#include "../Inc/DXTKWrapper.h"
#include "../../resource.h"

namespace DXTKWrapper
{
	CDXTKWrapper::CDXTKWrapper(ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pContext)
	{
		pDevice = m_pDevice;
		pContext = m_pContext;

		Initialize();
	}

	CDXTKWrapper::~CDXTKWrapper()
	{
	}

	void CDXTKWrapper::ResetAdapters()
	{
		this->Reset();
		this->Init = false;
	}

	void CDXTKWrapper::Initialize()
	{
		if(pDevice == nullptr || pContext == nullptr )
		{
			Init = false;
			return;
		}

		spriteBatch.reset(new SpriteBatch(pContext));
		primitive.reset(new PrimitiveBatch<VertexPositionColor>(pContext));
		basicEffect.reset(new BasicEffect(pDevice));

		// TODO: Refactor resource loading
		BuildFontFromResources();

		D3D11_BUFFER_DESC bufferDesc;

		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.ByteWidth = 4 * sizeof(VertexPositionColor);
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.MiscFlags = 0;

		if( FAILED( pDevice->CreateBuffer( &bufferDesc, NULL, &m_pVertexBuffer ) ) )
		{
			Init = false;
			return;
		}

		Init = true;
	}

	void CDXTKWrapper::Reset()
	{
		if (Init)
		{
			font12.release();
			font14.release();
			font16.release();
			font20.release();
			fontTitle.release();
			fontText.release();
			fontInfo.release();
			fontMessage.release();


			m_pVertexBuffer = nullptr;
			pDevice = nullptr;
			pContext = nullptr;
		}

		Init = false;
	}

	void CDXTKWrapper::DrawRectangle(float x, float y, float width, float height, Color rectangleColor)
	{
		if( pDevice == nullptr || pContext == nullptr || Init == false ) return;	

		VertexPositionColor start(Vector3(x, y, 0), rectangleColor);
		VertexPositionColor end(Vector3(x, y + height, 0), rectangleColor);
		VertexPositionColor start2(Vector3(x + width, y + height, 0), rectangleColor);
		VertexPositionColor end2(Vector3(x + width, y, 0), rectangleColor);

		PrepareEffect();
		
		primitive->Begin();
		primitive->DrawQuad(start, end, start2, end2);
		primitive->End();
	}

	void CDXTKWrapper::DrawLine(float x, float y, float x2, float y2, Color Color)
	{
		if( pDevice == nullptr || pContext == nullptr || Init == false ) return;

		VertexPositionColor start(Vector3(x, y, 0), Color);
		VertexPositionColor end(Vector3(x2, y2, 0), Color);

		PrepareEffect();

		primitive->Begin();
		primitive->DrawLine(start, end);
		primitive->End();
	}

	void CDXTKWrapper::DrawDxText(wstring text, float x, float y, Color color, E_DX_SYSTEM_FONTS systemFont)
	{
		SpriteFont* font = this->retSystemFont(systemFont);

		spriteBatch->Begin();
		font->DrawString(spriteBatch.get(), text.c_str(), XMFLOAT2(x, y), color);
		spriteBatch->End();
	}

	void CDXTKWrapper::DrawOutlinedText(wstring text, float x, float y, Color color, E_DX_SYSTEM_FONTS systemFont)
	{
		SpriteFont* font = this->retSystemFont(systemFont);

		spriteBatch->Begin();
		font->DrawString(spriteBatch.get(), text.c_str(), XMFLOAT2(x + 1, y), color);
		font->DrawString(spriteBatch.get(), text.c_str(), XMFLOAT2(x, y + 1), color);
		font->DrawString(spriteBatch.get(), text.c_str(), XMFLOAT2(x - 1, y), color);
		font->DrawString(spriteBatch.get(), text.c_str(), XMFLOAT2(x, y - 1), color);
		font->DrawString(spriteBatch.get(), text.c_str(), XMFLOAT2(x + 1, y), color);
		spriteBatch->End();
	}

	void CDXTKWrapper::DrawOutlinedTextEx(wstring text, float x, float y, Color col, Color glowColor, E_DX_SYSTEM_FONTS systemFont)
	{
		SpriteFont* font = this->retSystemFont(systemFont);

		spriteBatch->Begin();
		font->DrawString(spriteBatch.get(), text.c_str(), XMFLOAT2(x + 1, y), glowColor);
		font->DrawString(spriteBatch.get(), text.c_str(), XMFLOAT2(x, y + 1), glowColor);
		font->DrawString(spriteBatch.get(), text.c_str(), XMFLOAT2(x - 1, y), glowColor);
		font->DrawString(spriteBatch.get(), text.c_str(), XMFLOAT2(x, y - 1), glowColor);
		font->DrawString(spriteBatch.get(), text.c_str(), XMFLOAT2(x + 1, y), col);
		spriteBatch->End();
	}

	void CDXTKWrapper::DrawBorder(float x, float y, float width, float height, Color color)
	{
		DrawLine(x,y,x + width,y,color);
		DrawLine(x,y,x,y + height,color);
		DrawLine(x,y + height,x + width,y + height,color);
		DrawLine(x + width,y + height,x + width,y,color);
	}

	void CDXTKWrapper::DrawBox(float x, float y, float width, float height, Color BoxColor, Color BorderColor )
	{
		DrawRectangle(x,y,width,height,BoxColor);
		DrawBorder(x,y,width,height,BorderColor);
	}

	void CDXTKWrapper::GradientRectangle(float x, float y, float width, float height, Color startCol, Color endCol, E_DX_GRADIENT_ORIENTATION orientation )
	{
		if( pDevice == nullptr || pContext == nullptr || Init == false ) return;

		VertexPositionColor start(Vector3(x, y, 0), orientation == DX_ORIENTATION_VERTICAL ? endCol : startCol);
		VertexPositionColor end(Vector3(x, y + height, 0), orientation == DX_ORIENTATION_FORWARD_DIAGONAL ? endCol : startCol);
		VertexPositionColor start2(Vector3(x + width, y + height, 0), orientation == DX_ORIENTATION_FORWARD_DIAGONAL ? startCol : endCol);
		VertexPositionColor end2(Vector3(x + width, y, 0), orientation == DX_ORIENTATION_VERTICAL ? startCol : endCol);

		PrepareEffect();

		primitive->Begin();
		primitive->DrawQuad(start, end, start2, end2);
		primitive->End();
	}

	void CDXTKWrapper::DrawBoxGradient(float x, float y, float width, float height, Color boxColor, Color endColor, Color borderColor, E_DX_GRADIENT_ORIENTATION orientation)
	{
		GradientRectangle(x,y,width,height,boxColor,endColor,orientation);

		DrawBorder(x,y,width,height,borderColor);
	}

	void CDXTKWrapper::DrawCrosshair(float size, Color color)
	{
		if( pDevice == nullptr || pContext == nullptr || Init == false) return;

		D3D11_VIEWPORT vp2;
	
		UINT viewPortNumber = 1;

		pContext->RSGetViewports(&viewPortNumber, &vp2);

		float iCenterX = vp2.Width / 2 - size / 2;
		float iCenterY = vp2.Height / 2 + size / 2;

		DrawBox(iCenterX,iCenterY - size / 2,size,2,color, Colors::Black.v);
		DrawBox(iCenterX + size / 2 - 1,iCenterY - size + 1,2,size,color, Colors::Black.v);
	}

	float CDXTKWrapper::GetScreenWidth()
	{
		UINT viewPortNumber = 1;

		pContext->RSGetViewports(&viewPortNumber, &this->vp);
		return vp.Width;
	}

	float CDXTKWrapper::GetScreenHeight()
	{
		UINT viewPortNumber = 1;

		pContext->RSGetViewports(&viewPortNumber, &this->vp);
		return vp.Height;
	}

	bool CDXTKWrapper::IsInitialized()
	{
		return Init;
	}

	SpriteFont* CDXTKWrapper::retSystemFont(E_DX_SYSTEM_FONTS font) const
	{
		switch(font)
		{
		case 0:
			return this->font12.get();
		case 1:
			return this->font14.get();
		case 2:
			return this->font16.get();
		case 3:
			return this->font20.get();
		case 4:
			return this->fontTitle.get();
		case 5:
			return this->fontText.get();
		case 6:
			return this->fontInfo.get();
		case 7:
			return this->fontMessage.get();
		default:
			return this->fontText.get();
		}
	}

	void CDXTKWrapper::BuildFontFromResources()
	{
		auto font12Resource = FindResource(nullptr, MAKEINTRESOURCE(IDR_FONT121), "font12");
		auto font14Resource = FindResource(nullptr, MAKEINTRESOURCE(IDR_FONT141), "font14");
		auto font16Resource = FindResource(nullptr, MAKEINTRESOURCE(IDR_FONT161), "font16");
		auto font20Resource = FindResource(nullptr, MAKEINTRESOURCE(IDR_FONT201), "font20");
		auto fontTitleResource = FindResource(nullptr, MAKEINTRESOURCE(IDR_FONTINFO1), "fontTitle");
		auto fontTextResource = FindResource(nullptr, MAKEINTRESOURCE(IDR_FONTMESSAGE1), "fontText");
		auto fontInfoResource = FindResource(nullptr, MAKEINTRESOURCE(IDR_FONTTEXT1), "fontInfo");
		auto fontMessageResource = FindResource(nullptr, MAKEINTRESOURCE(IDR_FONTTITLE1), "fontMessage");

		const unsigned char* font12ResourceData = static_cast<unsigned char*>(LockResource(LoadResource(nullptr, font12Resource)));
		const unsigned char* font14ResourceData = static_cast<unsigned char*>(LockResource(LoadResource(nullptr, font14Resource)));
		const unsigned char* font16ResourceData = static_cast<unsigned char*>(LockResource(LoadResource(nullptr, font16Resource)));
		const unsigned char* font20ResourceData = static_cast<unsigned char*>(LockResource(LoadResource(nullptr, font20Resource)));
		const unsigned char* fontTitleResourceData = static_cast<unsigned char*>(LockResource(LoadResource(nullptr, fontTitleResource)));
		const unsigned char* fontTextResourceData = static_cast<unsigned char*>(LockResource(LoadResource(nullptr, fontTextResource)));
		const unsigned char* fontInfoResourceData = static_cast<unsigned char*>(LockResource(LoadResource(nullptr, fontInfoResource)));
		const unsigned char* fontMessageResourceData = static_cast<unsigned char*>(LockResource(LoadResource(nullptr, fontMessageResource)));

		font12.reset(new SpriteFont(pDevice, font12ResourceData, SizeofResource(nullptr, font12Resource)));
		font14.reset(new SpriteFont(pDevice, font14ResourceData, SizeofResource(nullptr, font14Resource)));
		font16.reset(new SpriteFont(pDevice, font16ResourceData, SizeofResource(nullptr, font16Resource)));
		font20.reset(new SpriteFont(pDevice, font20ResourceData, SizeofResource(nullptr, font20Resource)));
		fontTitle.reset(new SpriteFont(pDevice, fontTitleResourceData, SizeofResource(nullptr, fontTitleResource)));
		fontText.reset(new SpriteFont(pDevice, fontTextResourceData, SizeofResource(nullptr, fontTextResource)));
		fontInfo.reset(new SpriteFont(pDevice, fontInfoResourceData, SizeofResource(nullptr, fontInfoResource)));
		fontMessage.reset(new SpriteFont(pDevice, fontMessageResourceData, SizeofResource(nullptr, fontMessageResource)));
	}

	void CDXTKWrapper::PrepareEffect()
	{
		D3D11_VIEWPORT vp2;

		UINT viewPortNumber = 1;

		pContext->RSGetViewports(&viewPortNumber, &vp2);

		basicEffect->SetProjection(XMMatrixOrthographicOffCenterRH(0, vp2.Width, vp2.Height, 0, 0, 1));
		basicEffect->SetVertexColorEnabled(true);

		void const* shaderByteCode;
		size_t byteCodeLength;

		basicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

		pDevice->CreateInputLayout(VertexPositionColor::InputElements,
			VertexPositionColor::InputElementCount,
			shaderByteCode, byteCodeLength,
			inputLayout.GetAddressOf());

		CommonStates states(pDevice);
		pContext->OMSetBlendState(states.Opaque(), nullptr, 0xFFFFFFFF);
		pContext->OMSetDepthStencilState(states.DepthNone(), 0);
		pContext->RSSetState(states.CullNone());

		basicEffect->Apply(pContext);
		pContext->IASetInputLayout(inputLayout.Get());
	}

	void CDXTKWrapper::DrawHealthBar(float x, float y, float health, float maxHealth)
	{
		if(health <= 0.0f) return;

		if(this->Init == false) return;
	
		if(health > maxHealth) health = maxHealth;
	
		    float BarLength = 50;
			float RealWert = health / maxHealth;
			float Color = 255;

			float BarRealLength = BarLength * RealWert;
			float RealColor = Color *RealWert;
			float OtherColor = Color - RealColor;

			SimpleMath::Color NeuColor(OtherColor, RealColor, 0, 255);

			DrawBorder(x,y,BarLength,5,Colors::Black.v);
			DrawRectangle(x +1,y + 1 ,BarRealLength - 1,4,NeuColor);
	}

	void CDXTKWrapper::DrawBoundingBox(float x, float y, float distance, Color color)
	{
		if(this->Init == false) return;

		if(distance <= 0) return; 

		DrawBorder( x - 700 / distance / 2, y - 1200 / distance / 2, 600 / distance, 1200 / distance, color);
	}
};