#ifndef _TEST
#define _TEST

cbuffer TRANSFORM : register(b0) // type �� ��� �����̰� registr ��ȣ�� 0 �̴�. 
{
    float4 vPlayerPos;
};

// vs �Է� ����ü
struct VS_IN
{
    float3 vPos : POSITION; // semantic, ���̾ƿ����� ������ �����´�.
    float4 vColor : COLOR;
};

// ���̴����� �䱸�ϴ� ��Ȯ�� ������ ���� �ȿ� ��� �ִ����� �˷��ִ� ���� ���̾ƿ� ����ü�̴�.

struct VS_OUT
{
    float4 vPosition : SV_Position; // ���⿡�� SV �� system value ���� ���Ѵ�.
    float4 vOutColor : COLOR;
};

// vertex shader
// Local Space ��ü�� NDC ��ǥ��� �̵�
VS_OUT VS_TEST(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f; // �ʱ�ȭ ��
    
    output.vPosition = float4(_in.vPos, 1.f);
    // �Է����� ���� ���� ��ǥ�� ��� ���� ���� ���ؼ� ����Ѵ�.
    float3 vPos = _in.vPos;
    vPos.xy += vPlayerPos.xy;
    
    output.vPosition = float4(vPos, 1.f);
    output.vOutColor = _in.vColor;
    
    return output;
}

// pixel shader
float4 PS_TEST(VS_OUT _in) : SV_Target
{
    float4 vColor = (float) 0.f;
    
    vColor = _in.vOutColor;
    
    return vColor;
}

#endif