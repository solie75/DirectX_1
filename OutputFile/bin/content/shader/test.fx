#ifndef _TEST
#define _TEST

cbuffer TRANSFORM : register(b0) // type 은 상수 버퍼이고 registr 번호는 0 이다. 
{
    float4 vPlayerPos;
};

Texture2D g_Tex_0 : register(t0);

SamplerState g_sam_0 : register(s0);

// vs 입력 구조체
struct VS_IN
{
    float3 vPos : POSITION; // semantic, 레이아웃에서 정보를 가져온다.
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};

// 쉐이더에서 요구하는 정확한 정보가 정점 안에 어디에 있는지를 알려주는 것이 레이아웃 구조체이다.

struct VS_OUT
{
    float4 vPosition : SV_Position; // 여기에서 SV 는 system value 임을 뜻한다.
    float4 vOutColor : COLOR;
    float2 vOutUV : TEXCOORD;
};

// vertex shader
// Local Space 물체를 NDC 좌표계로 이동
VS_OUT VS_TEST(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f; // 초기화 값
    
    // 입력으로 들어온 정점 좌표에 상수 버퍼 값을 더해서 출력한다.
    float3 vPos = _in.vPos;
    vPos.xy += vPlayerPos.xy;
    
    output.vPosition = float4(vPos, 1.f);
    output.vOutColor = _in.vColor;
    output.vOutUV = _in.vUV;
    
    return output;
}

// pixel shader
float4 PS_TEST(VS_OUT _in) : SV_Target
{
    float4 vColor = (float) 0.f;
    
    //vColor = _in.vOutColor;
    
    vColor = g_Tex_0.Sample(g_sam_0, _in.vOutUV);
    
    return vColor;
}

#endif