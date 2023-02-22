#ifndef _TEST
#define _TEST

// vs 입력 구조체
struct VS_IN
{
    float3 vPos : POSITION; // semantic, 레이아웃에서 정보를 가져온다.
    float4 vColor : COLOR;
};
// 쉐이더에서 요구하는 정확한 정보가 정점 안에 어디에 있는지를 알려주는 것이 레이아웃 구조체이다.

struct VS_OUT
{
    float4 vPosition : SV_Position; // 여기에서 SV 는 system value 임을 뜻한다.
    float4 vOutColor : COLOR;
};

// vertex shader
// LocalSpace 물체를 NDC 좌표계로 이동
VS_OUT VS_TEST(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f; // 초기화 값
    
    output.vPosition = float4(_in.vPos, 1.f);
    
    return output;
}

// pixel shader
float4 PS_TEST(VS_OUT _in) : SV_Target
{
    float4 vColor = (float) 0.f;
    
    vColor = float4(1.f, 0.f, 0.f, 1.f);
    
    return vColor;
}

#endif