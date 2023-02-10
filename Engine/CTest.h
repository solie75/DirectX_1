#pragma once

// Vertex Buffer
ComPtr<ID3D11Buffer> g_VB;

// Compiled Shader
ComPtr<ID3DBlob> g_VSBlob; // ������ �Ϸ�� vertex shader binary �ڵ带 ����.
ComPtr<ID3DBlob> g_PSBlob; // ������ �Ϸ�� pixel shader binary �ڵ带 ����.
ComPtr<ID3DBlob> g_ErrBlob; // �������� ������ ����� ��ü <- �� �����ϴ� �Ϳ� ���� ��ü�� �ʿ�����?

// shader
ComPtr<ID3D11VertexShader> g_VS; // Vertex shader ��ü g_VSBlob ���� �����.
ComPtr<ID3D11PixelShader> g_PS; // Pixel Shader ��ü g_PSBlob ���� �����.

// Input Layout
ComPtr<ID3D11InputLayout> g_Layout;

void TestInit();
void TestTick();
void TestRender();
void TestRelease();