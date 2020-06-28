#pragma once

typedef struct
{
	DWORD R;
	DWORD G;
	DWORD B;
	DWORD A;
}RGBA;
class Color
{
public:
	RGBA ��ɫ = { 255,0,0,255 };
	RGBA Ʒ�� = { 255,0,255,255 };
	RGBA ��ɫ = { 255,255,0,255 };
	RGBA ���� = { 128,128,255,255 };
	RGBA ���� = { 128,224,0,255 };
	RGBA ���� = { 0,224,128,255 };
	RGBA ��ɫ = { 192,96,0,255 };
	RGBA ��ɫ = { 255,168,255,255 };
	RGBA ���� = { 216,216,0,255 };
	RGBA ���� = { 236,236,236,255 };
	RGBA ��ɫ = { 144,0,255,255 };
	RGBA ���� = { 88,48,224,255 };
	RGBA ���� = { 0,136,255,255 };
	RGBA ���� = { 128,160,128,255 };
	RGBA ���� = { 0,96,192,255 };
	RGBA �Ȼ� = { 255,128,0,255 };
	RGBA �Һ� = { 255,80,128,255 };
	RGBA ܽ�� = { 255,128,192,255 };
	RGBA ��� = { 96,96,96,255 };
	RGBA ���� = { 0,0,128,255 };
	RGBA ī�� = { 0,128,0,255 };
	RGBA ���� = { 0,128,128,255 };
	RGBA ��� = { 128,0,0,255 };
	RGBA �Ϻ� = { 128,0,128,255 };
	RGBA ��ɫ = { 0,255,0,255 };
	RGBA ���i = { 0,255,255,255 };
	RGBA ��ɫ = { 0,0,0,255 };
	RGBA ��ɫ = { 128,128,128,255 };
	RGBA ��ɫ = { 255,255,255,200 };

	RGBA ��ɫ_ = { 255,255,255,200 };
	RGBA ��ɫ_ = { 128,128,128,200 };
	RGBA ��ɫ_ = { 0,0,0,200 };
	RGBA ��ɫ_ = { 255,0,0,200 };
	RGBA Ʒ��_ = { 255,0,255,200 };
	RGBA ��ɫ_ = { 255,255,0,200 };
	RGBA ����_ = { 128,128,255,200 };
	RGBA ����_ = { 128,224,0,200 };
	RGBA ����_ = { 0,224,128,200 };
	RGBA ��ɫ_ = { 192,96,0,200 };
	RGBA ��ɫ_ = { 255,168,255,200 };
	RGBA ����_ = { 216,216,0,200 };
	RGBA ����_ = { 236,236,236,200 };
	RGBA ��ɫ_ = { 144,0,255,200 };
	RGBA ����_ = { 88,48,224,200 };
	RGBA ����_ = { 0,136,255,200 };
	RGBA ����_ = { 128,160,128,200 };
	RGBA ����_ = { 0,96,192,200 };
	RGBA �Ȼ�_ = { 255,128,0,200 };
	RGBA �Һ�_ = { 255,80,128,200 };
	RGBA ܽ��_ = { 255,128,192,200 };
	RGBA ���_ = { 96,96,96,200 };
	RGBA ����_ = { 0,0,128,200 };
	RGBA ī��_ = { 0,128,0,200 };
	RGBA ����_ = { 0,128,128,200 };
	RGBA ���_ = { 128,0,0,200 };
	RGBA �Ϻ�_ = { 128,0,128,200 };
	RGBA ��ɫ_ = { 0,255,0,200 };
	RGBA ���i_ = { 0,255,255,200 };

	RGBA ������ = { 0, 0, 0,160 };
	RGBA ��ɫ = { 0, 0, 255,255 };
	RGBA ������ = { 65,105,225,80 };
	RGBA ������ = { 255,255,0,160 };
	RGBA ���� = { 200,200,200,60 };
};
struct Vec4
{
	float     x, y, z, w;
	Vec4() { x = y = z = w = 0.0f; }
	Vec4(float _x, float _y, float _z, float _w) { x = _x; y = _y; z = _z; w = _w; }
};

#define COL32_A_MASK     0xFF000000
#define F32_TO_INT8_SAT(_VAL)        ((int)(ImSaturate(_VAL) * 255.0f + 0.5f))
#define COL32_R_SHIFT    0
#define COL32_G_SHIFT    8
#define COL32_B_SHIFT    16
#define COL32_A_SHIFT    24
static auto ImSaturate = [&](float f) {return (f < 0.0f) ? 0.0f : (f > 1.0f) ? 1.0f : f; };

inline unsigned int ColorConvertFloat4ToU32(const Vec4& in)
{
	unsigned int out;
	out = ((unsigned int)F32_TO_INT8_SAT(in.x)) << COL32_R_SHIFT;
	out |= ((unsigned int)F32_TO_INT8_SAT(in.y)) << COL32_G_SHIFT;
	out |= ((unsigned int)F32_TO_INT8_SAT(in.z)) << COL32_B_SHIFT;
	out |= ((unsigned int)F32_TO_INT8_SAT(in.w)) << COL32_A_SHIFT;
	return out;
}