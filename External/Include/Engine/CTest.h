#pragma once

// Vertex Buffer
ComPtr<ID3D11Buffer> g_VB;

// Compiled Shader
ComPtr<ID3DBlob> g_VSBlob; // 컴파일 완료된 vertex shader binary 코드를 저장.
ComPtr<ID3DBlob> g_PSBlob; // 컴파일 완료된 pixel shader binary 코드를 저장.
ComPtr<ID3DBlob> g_ErrBlob; // 컴파일이 실패할 경우의 객체 <- 왜 실패하는 것에 대한 객체가 필요하지?

// shader
ComPtr<ID3D11VertexShader> g_VS; // Vertex shader 객체 g_VSBlob 으로 만든다.
ComPtr<ID3D11PixelShader> g_PS; // Pixel Shader 객체 g_PSBlob 으로 만든다.

// Input Layout
ComPtr<ID3D11InputLayout> g_Layout;

void TestInit();
void TestTick();
void TestRender();
void TestRelease();