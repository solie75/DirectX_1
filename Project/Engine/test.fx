#ifndef _TEST
#define _TEST

cbuffer TRANSFORM : register(b0) // type �� ��� �����̰� registr ��ȣ�� 0 �̴�. 
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

// vs �Է� ����ü
struct VS_IN
{
    float3 vPos : POSITION; // semantic, ���̾ƿ����� ������ �����´�.
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};

// ���̴����� �䱸�ϴ� ��Ȯ�� ������ ���� �ȿ� ��� �ִ����� �˷��ִ� ���� ���̾ƿ� ����ü�̴�.

struct VS_OUT
{
    float4 vPosition : SV_Position; // ���⿡�� SV �� system value ���� ���Ѵ�.
    float4 vOutColor : COLOR;
    float2 vOutUV : TEXCOORD;
};

// vertex shader
// Local Space ��ü�� NDC ��ǥ��� �̵�
VS_OUT VS_TEST(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f; // �ʱ�ȭ ��
    
    // �Է����� ���� ���� ��ǥ�� ��� ���� ���� ���ؼ� ����Ѵ�.
    //float3 vPos = _in.vPos;
    //vPos.xy += vPlayerPos.xy;
    //
    //output.vPosition = float4(vPos, 1.f);
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWorld);

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