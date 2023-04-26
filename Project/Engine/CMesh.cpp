#include "pch.h"
#include "CMesh.h"

#include "CDevice.h"

CMesh::CMesh()
	: CResource(RESOURCE_TYPE::MESH)
	, m_tVBDesc{}
	, m_VtxCount(0)
	, m_tIBDesc{}
	, m_IdxCount(0)
	, m_pVtxSys(nullptr)
	, m_pIdxSys(nullptr)
{
}

CMesh::~CMesh()
{
	// 초기 nullptr 상태인 시스템 변수가 메모리 주소를 할당 받은 경우 delete 처리하는데
	// 이는 해당 주소를 계속해서 가리키며 다시 할당받을 수 있다는 뜻이다. nullptr 이된다는 의미가 아니다.
	// 따라서 m_pVtxSys 변수는 delete 후 nullptr 을 대입해야  하는데 왜 하지 않은것이지? 
	// 하나의 메쉬당 하나의 시스템에 대한 주소만을 사용하기 위함인가?
	if (nullptr != m_pVtxSys)
	{
		delete m_pVtxSys;
	}
	if (nullptr != m_pIdxSys)
	{
		delete m_pIdxSys;
	}
}


void CMesh::CreateMesh(void* _VtxSysMem, UINT _iVtxCount, void* _IdxSysMem, UINT _IdxCount)
{
	m_VtxCount = _iVtxCount;
	m_IdxCount = _IdxCount;

	// SystemMem 데이터 복사
	m_pVtxSys = new Vtx[m_VtxCount];
	memcpy(m_pVtxSys, _VtxSysMem, sizeof(Vtx) * m_VtxCount);

	m_pIdxSys = new UINT[m_IdxCount];
	memcpy(m_pIdxSys, _IdxSysMem, sizeof(UINT) * m_IdxCount);

	// Vertex 버퍼 생성
	m_tVBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	m_tVBDesc.CPUAccessFlags = 0;
	m_tVBDesc.Usage = D3D11_USAGE_DEFAULT;
	m_tVBDesc.ByteWidth = sizeof(Vtx) * m_VtxCount;

	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = _VtxSysMem; // 왜 기껏 memcpy 로 데이터 옮겨 놓고 인자를 저장하는 것인가?
	if (FAILED(DEVICE->CreateBuffer(&m_tVBDesc, &tSub, m_VB.GetAddressOf())))
	{
		assert(nullptr);
	}

	// Index 버퍼 생성
	m_tIBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
	m_tIBDesc.CPUAccessFlags = 0;
	m_tIBDesc.Usage = D3D11_USAGE_DEFAULT;
	m_tIBDesc.ByteWidth = sizeof(UINT) * m_IdxCount;

	tSub.pSysMem = _IdxSysMem;
	if (FAILED(DEVICE->CreateBuffer(&m_tIBDesc, &tSub, m_IB.GetAddressOf())))
	{
		assert(nullptr);
	}
}

void CMesh::RenderMesh()
{
	UpdateResourceData();

	CONTEXT->DrawIndexed(m_IdxCount, 0, 0);
}

void CMesh::UpdateResourceData()
{
	UINT iStride = sizeof(Vtx);
	UINT iOffset = 0;


	// 렌더링 파이프 랑인의 과정이 시작되면 IASetVertexBuffer 로 지정한 g_VB 가 IA stage 가 시작 될 때 바인딩 된다.
	// 이는 IASetVertexBuffer 호출이 렌더링 파이프 라인의 과정 중에 IA 에 속한다는 것이 아니다. 단지 IA stage 에 사용될 vertex buffer 가 g_VB 라는 것을 알리는데에 그친다.
	CONTEXT->IASetVertexBuffers(0, 1, m_VB.GetAddressOf(), &iStride, &iOffset);
	CONTEXT->IASetIndexBuffer(m_IB.Get(), DXGI_FORMAT_R32_UINT, 0);
}

