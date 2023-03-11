#include "pch.h"
#include "CTest.h"
#include "CDevice.h"

#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"



// Buffer
ComPtr<ID3D11Buffer> g_VB;
ComPtr<ID3D11Buffer> g_IB; // index buffer
ComPtr<ID3D11Buffer> g_CB; // constant buffer

// Compiled Shader
ComPtr<ID3DBlob> g_VSBlob; // 컴파일 완료된 vertex shader binary 코드를 저장.
ComPtr<ID3DBlob> g_PSBlob; // 컴파일 완료된 pixel shader binary 코드를 저장.
ComPtr<ID3DBlob> g_ErrBlob; // 컴파일이 실패할 경우의 객체 <- 왜 실패하는 것에 대한 객체가 필요하지?

// shader
ComPtr<ID3D11VertexShader> g_VS; // Vertex shader 객체 g_VSBlob 으로 만든다.
ComPtr<ID3D11PixelShader> g_PS; // Pixel Shader 객체 g_PSBlob 으로 만든다.

// Input Layout
ComPtr<ID3D11InputLayout> g_Layout;

// vectex
Vtx g_arrVtx[4] = {}; // 정점을 자료형으로 하는 배열 -> 하나의 사각형을 만들예정이기 때문에 크기가 4
UINT g_arrIdx[6] = {}; // 왜 인덱스의 크기가 6이지?

void TestInit()
{
	// 0 --- 1 
	// |  \  |
	// 3 --- 2
	g_arrVtx[0].vPosition = Vec3(-0.5f, 0.5f, 0.5f);
	g_arrVtx[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	g_arrVtx[1].vPosition = Vec3(0.5f, 0.5f, 0.5f);
	g_arrVtx[1].vColor = Vec4(0.f, 1.f, 0.f, 1.f);

	g_arrVtx[2].vPosition = Vec3(0.5f, -0.5f, 0.5f);
	g_arrVtx[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);

	g_arrVtx[3].vPosition = Vec3(-0.5f, -0.5f, 0.5f);
	g_arrVtx[3].vColor = Vec4(0.f, 0.f, 0.f, 1.f);

	//Vtx arrVts[3] = {}; // 기본의 빨간색 삼각형

	//arrVts[0].vPosition = Vec3(0.f, 1.f, 0.5f);
	//arrVts[0].vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	//arrVts[1].vPosition = Vec3(1.f, -1.f, 0.5f);
	//arrVts[1].vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	//arrVts[2].vPosition = Vec3(-1.f, -1.f, 0.5f);
	//arrVts[2].vColor = Vec4(1.f, 1.f, 1.f, 1.f);

	D3D11_BUFFER_DESC tBufferDesc = {};

	tBufferDesc.ByteWidth = sizeof(Vtx) * 4; // 버퍼의 용량의 크기
	tBufferDesc.Usage = D3D11_USAGE_DYNAMIC; // cpu 에 접근하는 방식
	tBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER; // 버퍼의 용도 (버퍼는 형체가 확실하지 않은 단순 데이터 이지만 그 역할을 확실히 해주어야 한다.)
	tBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE; // 정점의 위치를 바꾸고 싶다면 사용자가 버퍼의 내용을 바꿔야 하기 때문.
	tBufferDesc.MiscFlags = 0;
	tBufferDesc.StructureByteStride = 0;
	// -> CPUAccessFlags 와 Usage를 조합하여 사용자는 cpu에 접근해 버퍼를 조작한다.

	// Subresource 설정
	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = g_arrVtx;
	tSub.SysMemPitch = 0;
	tSub.SysMemSlicePitch = 0;

	// 버퍼 생성
	if (FAILED(DEVICE->CreateBuffer(&tBufferDesc, &tSub, g_VB.GetAddressOf())))
	{
		assert(nullptr);
	}

	// index buffer 생성
	g_arrIdx[0] = 0;
	g_arrIdx[1] = 2;
	g_arrIdx[2] = 3;
	g_arrIdx[3] = 0;
	g_arrIdx[4] = 1;
	g_arrIdx[5] = 2;

	// 인덱스 버퍼 용도
	tBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;

	// 수정 불가능
	tBufferDesc.CPUAccessFlags = 0;
	tBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	// 버퍼의 크기
	tBufferDesc.ByteWidth = sizeof(UINT) * 6;

	// 인덱스 버퍼 subresource 생성
	tSub.pSysMem = g_arrIdx;
	// 버퍼 생성
	if (FAILED(DEVICE->CreateBuffer(&tBufferDesc, &tSub, g_IB.GetAddressOf())))
	{
		assert(nullptr);
	}

	// shader 파일 경로
	wstring strShaderFile = CPathMgr::GetInst()->GetContentPath();
	strShaderFile += L"shader\\test.fx";


	// VertexShader Compile
	if (FAILED(D3DCompileFromFile(strShaderFile.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, "VS_TEST", "vs_5_0", 0, 0, g_VSBlob.GetAddressOf(), g_ErrBlob.GetAddressOf())))
	{
		MessageBoxA(nullptr, (const char*)g_ErrBlob->GetBufferPointer(), "Vertex Shader Compile Failed!", MB_OK);
	}


	// PixelShader Compile
	if (FAILED(D3DCompileFromFile(strShaderFile.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, "PS_TEST", "ps_5_0", 0, 0, g_PSBlob.GetAddressOf(), g_ErrBlob.GetAddressOf())))
	{
		MessageBoxA(nullptr, (const char*)g_ErrBlob->GetBufferPointer(), "Pixel Shader Compile Failed!", MB_OK);
	}


	// 컴파일된 객체로 쉐이더를 생성한다.
	DEVICE->CreateVertexShader(g_VSBlob->GetBufferPointer(), g_VSBlob->GetBufferSize(), nullptr, g_VS.GetAddressOf());
	DEVICE->CreatePixelShader(g_PSBlob->GetBufferPointer(), g_PSBlob->GetBufferSize(), nullptr, g_PS.GetAddressOf());

	// Input Layer
	D3D11_INPUT_ELEMENT_DESC LayoutDesc[2] = {};

	// vPos
	LayoutDesc[0].SemanticName = "POSITION";
	LayoutDesc[0].SemanticIndex = 0;
	LayoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	LayoutDesc[0].InputSlot = 0;
	LayoutDesc[0].AlignedByteOffset = 0;
	LayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	LayoutDesc[0].InstanceDataStepRate = 0;

	// vColor
	LayoutDesc[1].SemanticName = "COLOR";
	LayoutDesc[1].SemanticIndex = 0;
	LayoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	LayoutDesc[1].InputSlot = 0;
	LayoutDesc[1].AlignedByteOffset = 12;
	LayoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	LayoutDesc[1].InstanceDataStepRate = 0;

	if (FAILED(DEVICE->CreateInputLayout(LayoutDesc, 2, g_VSBlob->GetBufferPointer(), g_VSBlob->GetBufferSize(), g_Layout.GetAddressOf())))
	{
		assert(nullptr);
	}

}



//typedef struct D3D11_INPUT_ELEMENT_DESC
//{
//	LPCSTR SemanticName;
//	UINT SemanticIndex;
//	DXGI_FORMAT Format;
//	UINT InputSlot;
//	UINT AlignedByteOffset;
//	D3D11_INPUT_CLASSIFICATION InputSlotClass;
//	UINT InstanceDataStepRate;
//} 	D3D11_INPUT_ELEMENT_DESC;

void TestTick()
{
	if (KEY_PRESSED(KEY::UP))
	{
		for (int i = 0; i < 4; ++i)
		{
			g_arrVtx[i].vPosition.y += DT * 1.f;
		}
	}

	if (KEY_PRESSED(KEY::DOWN))
	{
		for (int i = 0; i < 4; ++i)
		{
			g_arrVtx[i].vPosition.y -= DT * 1.f;
		}
	}

	if (KEY_PRESSED(KEY::RIGHT))
	{
		for (int i = 0; i < 4; ++i)
		{
			g_arrVtx[i].vPosition.x += DT * 1.f;
		}
	}

	if (KEY_PRESSED(KEY::LEFT))
	{
		for (int i = 0; i < 4; ++i)
		{
			g_arrVtx[i].vPosition.x -= DT * 1.f;
		}
	}

	D3D11_MAPPED_SUBRESOURCE tSubRes = {};
	
	CONTEXT->Map(g_VB.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &tSubRes);
	memcpy(tSubRes.pData, g_arrVtx, sizeof(Vtx) * 4);
	CONTEXT->Unmap(g_VB.Get(), 0);
}

void TestRender()
{
	// IA
	UINT iStride = sizeof(Vtx); 
	UINT iOffset = 0;

	CONTEXT->IASetVertexBuffers(0, 1, g_VB.GetAddressOf(), &iStride, &iOffset);
	CONTEXT->IASetInputLayout(g_Layout.Get());
	CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	CONTEXT->VSSetShader(g_VS.Get(), nullptr, 0);
	CONTEXT->PSSetShader(g_PS.Get(), nullptr, 0);
	CONTEXT->Draw(3, 0);

}

void TestRelease()
{
}

//void TestRender()
//{
//	// IA
//	UINT iStride = sizeof(Vtx); //  버퍼에서는 연달아 있는 메모리상에서 버퍼별로 끊어 주어야 하는 데 그 때 알아야할 각 버퍼의 크기;
//	UINT iOffset = 0; // 하나의 정점 버퍼 안에서 랜더링 을 시작하고 싶은 정점의 주소를 말한다. 현재는 전부 다 랜더링 할 것임으로 0;
//	CONTEXT->IASetVertexBuffers(0, 1, g_VB.GetAddressOf(), &iStride, &iOffset);
//	// 헨더링 파이프 라인의 과정이 시작되면 현재 지금 지정한 버퍼(g_VB)가 IA 단계가 시작 될때 전달된다.
//	// 그렇다고 IASetVertexBuffer호출이 랜더링 파이프 라인의 과정중 IA 에 속하는 것은 아니다. 단지 IA 단계에 사용될 VertexBuffer 가 G_VB 라는 것을 알리는 것.
//	CONTEXT->IASetInputLayout(g_Layout.Get());
//	CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//	// 정덤들을 기준으로 몇개씩 묶을지 정한다. 이때 TRIANGLELIST 이므로 세개의 정점을 묶어서 삼각형을 만들겠다는 의미.
//
//	CONTEXT->VSSetShader(g_VS.Get(), nullptr, 0);
//	CONTEXT->PSSetShader(g_PS.Get(), nullptr, 0);
//
//	CONTEXT->Draw(3, 0); // 실제로 랜더링 파이프 라인을 시작시키는 함수
//	// 첫번째 인자로 
//}
