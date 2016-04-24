#include "stdafx.h"
#include "DXTKWrapper.h"

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

		wchar_t mediaDir[1000];
		swprintf_s(mediaDir, L"%S", "C:\\");

		wstring fontLocation12(mediaDir);
		wstring fontLocation14(mediaDir);
		wstring fontLocation16(mediaDir);
		wstring fontLocation20(mediaDir);
		wstring fontLocationTitle(mediaDir);
		wstring fontLocationText(mediaDir);
		wstring fontLocationInfo(mediaDir);
		wstring fontLocationMessage(mediaDir);

		font12.reset(new SpriteFont(pDevice, fontLocation12.append(L"font12.spritefont").c_str()));
		font14.reset(new SpriteFont(pDevice, fontLocation14.append(L"font14.spritefont").c_str()));
		font16.reset(new SpriteFont(pDevice, fontLocation16.append(L"font16.spritefont").c_str()));
		font20.reset(new SpriteFont(pDevice, fontLocation20.append(L"font20.spritefont").c_str()));
		fontTitle.reset(new SpriteFont(pDevice, fontLocationTitle.append(L"fontTitle.spritefont").c_str()));
		fontText.reset(new SpriteFont(pDevice, fontLocationText.append(L"fontText.spritefont").c_str()));
		fontInfo.reset(new SpriteFont(pDevice, fontLocationInfo.append(L"fontInfo.spritefont").c_str()));
		fontMessage.reset(new SpriteFont(pDevice, fontLocationMessage.append(L"fontMessage.spritefont").c_str()));

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


	void CDXTKWrapper::DrawRectangle(float x, float y, float width, float height, Color RecFarbe)
	{
		if( pDevice == nullptr || pContext == nullptr || Init == false ) return;	

		VertexPositionColor start(Vector3(x, y, 0), RecFarbe);
		VertexPositionColor end(Vector3(x, y + height, 0), RecFarbe);
		VertexPositionColor start2(Vector3(x + width, y + height, 0), RecFarbe);
		VertexPositionColor end2(Vector3(x + width, y, 0), RecFarbe);

		prepareEffect();
		
		primitive->Begin();
		primitive->DrawQuad(start, end, start2, end2);
		primitive->End();
	}


	void CDXTKWrapper::DrawLine(float x, float y, float x2, float y2, Color Color)
	{
		if( pDevice == nullptr || pContext == nullptr || Init == false ) return;

		VertexPositionColor start(Vector3(x, y, 0), Color);
		VertexPositionColor end(Vector3(x2, y2, 0), Color);

		prepareEffect();

		primitive->Begin();
		primitive->DrawLine(start, end);
		primitive->End();
	}

	void CDXTKWrapper::DrawDxText(wstring Text, float x, float y, Color Color, E_DX_SYSTEM_FONTS Font)
	{
		SpriteFont* font = this->retSystemFont(Font);

		spriteBatch->Begin();
		font->DrawString(spriteBatch.get(), Text.c_str(), XMFLOAT2(x, y), Color);
		spriteBatch->End();
	}


	void CDXTKWrapper::DrawOutlinedText(wstring Text, float x, float y, Color Color, E_DX_SYSTEM_FONTS Font)
	{
		SpriteFont* font = this->retSystemFont(Font);

		spriteBatch->Begin();
		font->DrawString(spriteBatch.get(), Text.c_str(), XMFLOAT2(x + 1, y), Color);
		font->DrawString(spriteBatch.get(), Text.c_str(), XMFLOAT2(x, y + 1), Color);
		font->DrawString(spriteBatch.get(), Text.c_str(), XMFLOAT2(x - 1, y), Color);
		font->DrawString(spriteBatch.get(), Text.c_str(), XMFLOAT2(x, y - 1), Color);
		font->DrawString(spriteBatch.get(), Text.c_str(), XMFLOAT2(x + 1, y), Color);
		spriteBatch->End();
	}


	void CDXTKWrapper::DrawOutlinedTextEx(wstring Text, float x, float y, Color col, Color GlowColor, E_DX_SYSTEM_FONTS Font)
	{
		SpriteFont* font = this->retSystemFont(Font);

		spriteBatch->Begin();
		font->DrawString(spriteBatch.get(), Text.c_str(), XMFLOAT2(x + 1, y), GlowColor);
		font->DrawString(spriteBatch.get(), Text.c_str(), XMFLOAT2(x, y + 1), GlowColor);
		font->DrawString(spriteBatch.get(), Text.c_str(), XMFLOAT2(x - 1, y), GlowColor);
		font->DrawString(spriteBatch.get(), Text.c_str(), XMFLOAT2(x, y - 1), GlowColor);
		font->DrawString(spriteBatch.get(), Text.c_str(), XMFLOAT2(x + 1, y), col);
		spriteBatch->End();
	}


	void CDXTKWrapper::DrawBorder(float x, float y, float width, float height, Color Color)
	{
		DrawLine(x,y,x + width,y,Color);
		DrawLine(x,y,x,y + height,Color);
		DrawLine(x,y + height,x + width,y + height,Color);
		DrawLine(x + width,y + height,x + width,y,Color);
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

		prepareEffect();

		primitive->Begin();
		primitive->DrawQuad(start, end, start2, end2);
		primitive->End();
	}

	void CDXTKWrapper::DrawBoxGradient(float x, float y, float width, float height, Color BoxColor, Color EndColor, Color BorderColor, E_DX_GRADIENT_ORIENTATION orientation)
	{
		GradientRectangle(x,y,width,height,BoxColor,EndColor,orientation);

		DrawBorder(x,y,width,height,BorderColor);
	}


	void CDXTKWrapper::DrawCrosshair(float size, Color Color)
	{
		if( pDevice == nullptr || pContext == nullptr || Init == false) return;

		D3D11_VIEWPORT vp2;
	
		UINT viewPortNumber = 1;

		pContext->RSGetViewports(&viewPortNumber, &vp2);

		float iCenterX = vp2.Width / 2 - size / 2;
		float iCenterY = vp2.Height / 2 + size / 2;

		DrawBox(iCenterX,iCenterY - size / 2,size,2,Color, Colors::Black.v);
		DrawBox(iCenterX + size / 2 - 1,iCenterY - size + 1,2,size,Color, Colors::Black.v);
	}

	float CDXTKWrapper::retScreenWidth()
	{
		UINT viewPortNumber = 1;

		pContext->RSGetViewports(&viewPortNumber, &this->vp);
		return vp.Width;
	}

	float CDXTKWrapper::retScreenHeight()
	{
		UINT viewPortNumber = 1;

		pContext->RSGetViewports(&viewPortNumber, &this->vp);
		return vp.Height;
	}

	bool CDXTKWrapper::IsInitialized()
	{
		return Init;
	}

	SpriteFont* CDXTKWrapper::retSystemFont(E_DX_SYSTEM_FONTS Font) const
	{
		switch(Font)
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

	void CDXTKWrapper::prepareEffect()
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

	void CDXTKWrapper::DrawHealthBar(float X, float Y, float Health, float MaxHealth)
	{
		if(Health <= 0.0f) return;

		if(this->Init == false) return;
	
		if(Health > MaxHealth) Health = MaxHealth;
	
		    float BarLength = 50;
			float RealWert = Health / MaxHealth;
			float Color = 255;

			float BarRealLength = BarLength * RealWert;
			float RealColor = Color *RealWert;
			float OtherColor = Color - RealColor;

			SimpleMath::Color NeuColor(OtherColor, RealColor, 0, 255);

			DrawBorder(X,Y,BarLength,5,Colors::Black.v);
			DrawRectangle(X +1,Y + 1 ,BarRealLength - 1,4,NeuColor);
	}


	void CDXTKWrapper::DrawBoundingBox(float X, float Y, float Distance, Color Color)
	{
		if(this->Init == false) return;

		if(Distance <= 0) return; 

		DrawBorder( X - 700 / Distance / 2, Y - 1200 / Distance / 2, 600 / Distance, 1200 / Distance, Color);
	}
};