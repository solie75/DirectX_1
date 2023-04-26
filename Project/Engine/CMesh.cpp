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
	// �ʱ� nullptr ������ �ý��� ������ �޸� �ּҸ� �Ҵ� ���� ��� delete ó���ϴµ�
	// �̴� �ش� �ּҸ� ����ؼ� ����Ű�� �ٽ� �Ҵ���� �� �ִٴ� ���̴�. nullptr �̵ȴٴ� �ǹ̰� �ƴϴ�.
	// ���� m_pVtxSys ������ delete �� nullptr �� �����ؾ�  �ϴµ� �� ���� ����������? 
	// �ϳ��� �޽��� �ϳ��� �ý��ۿ� ���� �ּҸ��� ����ϱ� �����ΰ�?
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

	// SystemMem ������ ����
	m_pVtxSys = new Vtx[m_VtxCount];
	memcpy(m_pVtxSys, _VtxSysMem, sizeof(Vtx) * m_VtxCount);

	m_pIdxSys = new UINT[m_IdxCount];
	memcpy(m_pIdxSys, _IdxSysMem, sizeof(UINT) * m_IdxCount);

	// Vertex ���� ����
	m_tVBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	m_tVBDesc.CPUAccessFlags = 0;
	m_tVBDesc.Usage = D3D11_USAGE_DEFAULT;
	m_tVBDesc.ByteWidth = sizeof(Vtx) * m_VtxCount;

	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = _VtxSysMem; // �� �ⲯ memcpy �� ������ �Ű� ���� ���ڸ� �����ϴ� ���ΰ�?
	if (FAILED(DEVICE->CreateBuffer(&m_tVBDesc, &tSub, m_VB.GetAddressOf())))
	{
		assert(nullptr);
	}

	// Index ���� ����
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


	// ������ ������ ������ ������ ���۵Ǹ� IASetVertexBuffer �� ������ g_VB �� IA stage �� ���� �� �� ���ε� �ȴ�.
	// �̴� IASetVertexBuffer ȣ���� ������ ������ ������ ���� �߿� IA �� ���Ѵٴ� ���� �ƴϴ�. ���� IA stage �� ���� vertex buffer �� g_VB ��� ���� �˸��µ��� ��ģ��.
	CONTEXT->IASetVertexBuffers(0, 1, m_VB.GetAddressOf(), &iStride, &iOffset);
	CONTEXT->IASetIndexBuffer(m_IB.Get(), DXGI_FORMAT_R32_UINT, 0);
}

