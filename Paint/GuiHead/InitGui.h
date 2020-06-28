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
	RGBA 红色 = { 255,0,0,255 };
	RGBA 品红 = { 255,0,255,255 };
	RGBA 黄色 = { 255,255,0,255 };
	RGBA 灰蓝 = { 128,128,255,255 };
	RGBA 嫩绿 = { 128,224,0,255 };
	RGBA 深绿 = { 0,224,128,255 };
	RGBA 棕色 = { 192,96,0,255 };
	RGBA 粉色 = { 255,168,255,255 };
	RGBA 暗黄 = { 216,216,0,255 };
	RGBA 银白 = { 236,236,236,255 };
	RGBA 紫色 = { 144,0,255,255 };
	RGBA 藏蓝 = { 88,48,224,255 };
	RGBA 天蓝 = { 0,136,255,255 };
	RGBA 灰绿 = { 128,160,128,255 };
	RGBA 青蓝 = { 0,96,192,255 };
	RGBA 橙黄 = { 255,128,0,255 };
	RGBA 桃红 = { 255,80,128,255 };
	RGBA 芙红 = { 255,128,192,255 };
	RGBA 深灰 = { 96,96,96,255 };
	RGBA 藏青 = { 0,0,128,255 };
	RGBA 墨绿 = { 0,128,0,255 };
	RGBA 深青 = { 0,128,128,255 };
	RGBA 红褐 = { 128,0,0,255 };
	RGBA 紫红 = { 128,0,128,255 };
	RGBA 绿色 = { 0,255,0,255 };
	RGBA 艳靑 = { 0,255,255,255 };
	RGBA 黑色 = { 0,0,0,255 };
	RGBA 灰色 = { 128,128,128,255 };
	RGBA 白色 = { 255,255,255,200 };

	RGBA 白色_ = { 255,255,255,200 };
	RGBA 灰色_ = { 128,128,128,200 };
	RGBA 黑色_ = { 0,0,0,200 };
	RGBA 红色_ = { 255,0,0,200 };
	RGBA 品红_ = { 255,0,255,200 };
	RGBA 黄色_ = { 255,255,0,200 };
	RGBA 灰蓝_ = { 128,128,255,200 };
	RGBA 嫩绿_ = { 128,224,0,200 };
	RGBA 深绿_ = { 0,224,128,200 };
	RGBA 棕色_ = { 192,96,0,200 };
	RGBA 粉色_ = { 255,168,255,200 };
	RGBA 暗黄_ = { 216,216,0,200 };
	RGBA 银白_ = { 236,236,236,200 };
	RGBA 紫色_ = { 144,0,255,200 };
	RGBA 藏蓝_ = { 88,48,224,200 };
	RGBA 天蓝_ = { 0,136,255,200 };
	RGBA 灰绿_ = { 128,160,128,200 };
	RGBA 青蓝_ = { 0,96,192,200 };
	RGBA 橙黄_ = { 255,128,0,200 };
	RGBA 桃红_ = { 255,80,128,200 };
	RGBA 芙红_ = { 255,128,192,200 };
	RGBA 深灰_ = { 96,96,96,200 };
	RGBA 藏青_ = { 0,0,128,200 };
	RGBA 墨绿_ = { 0,128,0,200 };
	RGBA 深青_ = { 0,128,128,200 };
	RGBA 红褐_ = { 128,0,0,200 };
	RGBA 紫红_ = { 128,0,128,200 };
	RGBA 绿色_ = { 0,255,0,200 };
	RGBA 艳靑_ = { 0,255,255,200 };

	RGBA 玻璃黑 = { 0, 0, 0,160 };
	RGBA 蓝色 = { 0, 0, 255,255 };
	RGBA 玻璃蓝 = { 65,105,225,80 };
	RGBA 玻璃黄 = { 255,255,0,160 };
	RGBA 玻璃 = { 200,200,200,60 };
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