#include "pch.h"
#include "CConstBuffer.h"
#include "CDevice.h"

CConstBuffer::CConstBuffer(UINT _iRegisterNum)
	: m_Desc{}
	, m_iRegisterNum(_iRegisterNum)
	, m_iElementSize(0)
	, m_iElementCount(0)
{
}

CConstBuffer::~CConstBuffer()
{
}


void CConstBuffer::CreateConstBuffer(UINT _iElementSize, UINT _iElementCount)
{
	m_iElementSize = _iElementSize;
	m_iElementCount = _iElementCount;

	UINT iBufferSize = m_iElementSize * _iElementCount;

	// 16바이트 단위 메모리 정렬. Constant buffer 의 경우 byteWidth 가 16의 배수여야 한다.
	assert(!(iBufferSize % 16));

	// 상수 버퍼 생성
	m_Desc.ByteWidth = iBufferSize;
	m_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	m_Desc.Usage = D3D11_USAGE_DYNAMIC;
	m_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	if (FAILED(DEVICE->CreateBuffer(&m_Desc, nullptr, m_CB.GetAddressOf())))
	{
		assert(nullptr);
	}
}

void CConstBuffer::SetConstBufferData(void* _vRelativePos, UINT _iSize)
{
	UINT buffersize = _iSize;
	// 크기가 지정되지 않은 데이터는 상수 버퍼 크기로 본다.
	if (0 == _iSize)
	{
		buffersize = m_iElementSize * m_iElementCount;
	}

	// 상수 버퍼 크기보다 더 큰 데이터가 입력된 경우
	assert(!(buffersize > m_iElementSize * m_iElementCount));

	// SysMem -> GPU Mem
	D3D11_MAPPED_SUBRESOURCE tSubRes = {};
	if (!FAILED(CONTEXT->Map(m_CB.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &tSubRes)))
	{
		memcpy(tSubRes.pData, _vRelativePos, buffersize);
		CONTEXT->Unmap(m_CB.Get(), 0);
	}
}

void CConstBuffer::UpdateConstBufferData()
{
	CONTEXT->VSSetConstantBuffers(m_iRegisterNum, 1, m_CB.GetAddressOf());
	CONTEXT->HSSetConstantBuffers(m_iRegisterNum, 1, m_CB.GetAddressOf());
	CONTEXT->DSSetConstantBuffers(m_iRegisterNum, 1, m_CB.GetAddressOf());
	CONTEXT->GSSetConstantBuffers(m_iRegisterNum, 1, m_CB.GetAddressOf());
	CONTEXT->PSSetConstantBuffers(m_iRegisterNum, 1, m_CB.GetAddressOf());
}

