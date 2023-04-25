#ifndef _TEST
#define _TEST

cbuffer TRANSFORM : register(b0) // type 은 상수 버퍼이고 registr 번호는 0 이다. 
{
    row_major matrix g_matWorld;
    row_major matrix g_matView;
    row_major matrix g_matProjection;
};

cbuffer MATERIAL : register(b1)
{
    int g_int_0;
    int g_int_1;
    int g_int_2;
    int g_int_3;
    
    float g_float_0;
    float g_float_1;
    float g_float_2;
    float g_float_3;
    
    float2 g_vec2_0;
    float2 g_vec2_1;
    float2 g_vec2_2;
    float2 g_vec2_3;

    float4 g_vec4_0;
    float4 g_vec4_1;
    float4 g_vec4_2;
    float4 g_vec4_3;
    
    matrix g_mat_0;
    matrix g_mat_1;
    matrix g_mat_2;
    matrix g_mat_3;
}

Texture2D g_tex_0 : register(t0);
Texture2D g_tex_1 : register(t1);
Texture2D g_tex_2 : register(t2);
Texture2D g_tex_3 : register(t3);
Texture2D g_tex_4 : register(t4);
Texture2D g_tex_5 : register(t5);
Texture2D g_tex_6 : register(t6);
Texture2D g_tex_7 : register(t7);

SamplerState g_sam_0 : register(s0);
SamplerState g_sam_1 : register(s1);

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
    float4 vWorldPos = mul(float4(_in.vPos, 1.f), g_matWorld);
    float4 vViewPos = mul(vWorldPos, g_matView);
    float4 vProjPos = mul(vViewPos, g_matProjection);
    
    output.vPosition = vProjPos;
    output.vOutColor = _in.vColor;
    output.vOutUV = _in.vUV;
    
    return output;
}

// pixel shader
float4 PS_TEST(VS_OUT _in) : SV_Target
{
    float4 vColor = (float) 0.f;
    
    if(g_int_0 == 0)
    {
        vColor = g_tex_0.Sample(g_sam_0, _in.vOutUV);
    }
    else if (g_int_0 == 1)
    {
        vColor = g_tex_0.Sample(g_sam_1, _in.vOutUV);
    }
 
    return vColor;
}

#endif