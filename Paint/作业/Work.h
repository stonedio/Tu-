#pragma once

#include "GuiHead/InitGui.h"
#include <list>
#include <vector>

namespace paint {
	class CfirstWork : public std::Singleton <CfirstWork>
	{
	public:
		void initialize(CDC* _pDC) { pDC = _pDC; }
		
		void _DrawLine(int x1, int y1, int x2, int y2, RGBA* penColor, float thickness, int PenStyle = PS_SOLID);
		void _DrawRect(int x, int y, int w, int h, RGBA *penColor, int thickness, int PenStyle = PS_SOLID, ...);
		void _DrawCircle(int x, int y, int radius, RGBA *penColor, int thickness, int PenStyle = PS_SOLID, ...);
	private:
		CDC* pDC;
	};

	class CsecondWork : public std::Singleton <CsecondWork>
	{
	public:
		void initialize(CDC* _pDC) { pDC = _pDC; }
		void _DDALine(CPoint& pStart, CPoint& pEnd, RGBA *penColor);
		void _BhmLine(CPoint& pStart, CPoint& pEnd, RGBA *penColor);
	private:
		CDC* pDC;
	};

	class CthreadWork : public std::Singleton <CthreadWork>
	{
	public:
		void initialize(CDC* _pDC) { pDC = _pDC; }
		void _BhmCircle(CPoint& p, int radius, RGBA *penColor);
	private:
		CDC* pDC;
	};

	struct mPOINT
	{
		mPOINT(double x, double y) :
			px(x)
			, py(y)
		{}
		mPOINT() :
			px(.0f)
			, py(.0f)
		{}
		double px;
		double py;
	};

	class CfourthWork : public std::Singleton <CfourthWork>
	{
	public:
		void initialize(CDC* _pDC) { pDC = _pDC; }	

		template <typename T, typename... Types>
		int getPointMax(const T& HeadArgs, const Types&...args)
		{
			mPOINT p1 = { HeadArgs };
			auto getmax = [&](double x) -> double {
				if (x > xmax)
					return x;
				return xmax;
			};
			xmax = getmax(p1.px);
			
			if constexpr (sizeof...(args) > 0)
				getPointMax(args...);

			return xmax;
		}

		int count = 0;
		template <typename T, typename... Types>
		void Setpoint( T& HeadArgs, const Types&...args)
		{
			//mPOINT p1 = { HeadArgs };
			P.push_back(HeadArgs);

			if constexpr (sizeof...(args) > 0)
				Setpoint(args...);

			count = 0;
		}


		template <typename... Types>
		void PolygonFill(RGBA fillcol, RGBA col, const Types&...args)
		{
			if ((ColorConvertFloat4ToU32(Vec4(col.R / 255.0, col.G / 255.0, col.B / 255.0, col.A / 255.0)) & COL32_A_MASK) == 0)
				return;
			if ((ColorConvertFloat4ToU32(Vec4(fillcol.R / 255.0, fillcol.G / 255.0, fillcol.B / 255.0, fillcol.A / 255.0)) & COL32_A_MASK) == 0)
				return;

			num = sizeof...(args) - 1;
			Setpoint(args...);

			xmax = getPointMax(args...);	
			

			for (int i = 0; i <= num; i++)
			{
				double xmin, ymin, ymax, m;
				if (i == num)
				{
					m = (P[i].px - P[0].px) / (P[i].py - P[0].py);
					if (P[i].py < P[0].py)
					{
						ymin = P[i].py;
						ymax = P[0].py;
						xmin = P[i].px;
					}
					else
					{
						ymin = P[0].py;
						ymax = P[i].py;
						xmin = P[0].px;
					}
				}
				else
				{
					m = (P[i + 1].px - P[i].px) / (P[i + 1].py - P[i].py);
					if (P[i].py < P[i + 1].py)
					{
						ymin = P[i].py;
						ymax = P[i + 1].py;
						xmin = P[i].px;
					}
					else
					{
						ymin = P[i + 1].py;
						ymax = P[i].py;
						xmin = P[i + 1].px;
					}
				}

				for (double y = ymin; y < ymax; y++)
				{
					for (double x = xmin; x < xmax; x++)
					{
						if (pDC->GetPixel(x, y) == RGB(col.R, col.G, col.B))
							pDC->SetPixel(x, y, RGB(fillcol.R, fillcol.G, fillcol.B));
						else
							pDC->SetPixel(x, y, RGB(col.R, col.G, col.B));
					}
					xmin += m;
				}

			}
		}

	private:
		CDC* pDC;
		double xmax;
		int num; 
		
		std::vector <mPOINT> P;
	};

	class CfifthWork : public std::Singleton <CfifthWork>
	{
	public:
		void initialize(CDC* _pDC) { pDC = _pDC; init(); }

		void PolygonFill(CPoint& p, RGBA* Color);
	private:
		void init()
		{
			CPoint Point[4] = { CPoint(0,0) };
			Point[0] = CPoint(20, 20);
			Point[1] = CPoint(20, 300);
			Point[2] = CPoint(60, 60);
			Point[3] = CPoint(300, 20);
			pDC->MoveTo(Point[0]);
			pDC->LineTo(Point[1]);
			pDC->MoveTo(Point[1]);
			pDC->LineTo(Point[2]);
			pDC->MoveTo(Point[2]);
			pDC->LineTo(Point[3]);
			pDC->MoveTo(Point[3]);
			pDC->LineTo(Point[0]);

		}
	private:
		CDC* pDC;	
	};


	class CsixthWork : public std::Singleton <CsixthWork>
	{
	public:
		typedef struct _LinePoint
		{
			float x1;
			float y1;
			float x2;
			float y2;
		}LinePoint, *pLinePoint;

		void initialize(CDC* _pDC) { pDC = _pDC; init(); }
		void CohenSutherland();

		template <typename T, typename... Types>
		void TestLine(T& HeadArgs, const Types&...args)
		{
			LinePoint Lpoint;
			Color *col = new Color;
			auto exp = std::experimental::scope_guard([&]() { delete col; });

			Lpoint = static_cast<LinePoint>(HeadArgs);
			P.push_back(Lpoint);
			paint::CfirstWork::instance()->_DrawLine(Lpoint.x1, Lpoint.y1, Lpoint.x2, Lpoint.y2, &col->ºìÉ«, 1);
			CohenSutherland();
			if constexpr (sizeof...(args) > 0)
				TestLine(args...);
		}
	private:
		uint32_t EnCode(float x, float y)
		{
			uint32_t code = 0;
			float wxl = 250, wxr = 850, wyb = 250, wyt = 450;
			if (x < wxl)
			{
				code |= 1;
			}
			if (x > wxr) {
				code |= 2;
			}
			if (y < wyb) {
				code |= 4;
			}
			if (y > wyt) {
				code |= 8;
			}
			return code;
		}
		void init()
		{
			CRect rect(250, 450, 850, 250);
			CPen pen1(PS_SOLID, 1, RGB(250, 0, 0));
			pDC->SelectObject(pen1);
			pDC->Rectangle(rect);
		}
	private:
		CDC* pDC;
		std::list <LinePoint> P;
	};

	class CseventhWork : public std::Singleton <CseventhWork>
	{
	public:
		void initialize(CDC* _pDC);
		using HYPoint = struct _HYPoint
		{
			_HYPoint(double x, double y, double z) 
			{
				p[0] = x;
				p[1] = y;
				p[2] = z;
				p[3] = 1;
			}
			_HYPoint(){}
			double p[4];
		};
		using HYFace = struct _HYFace
		{
			_HYFace(int x) :
				num_p(x)
			{}
			_HYFace() :
				num_p(0)
			{}
			int num_p;
			int index[10] = { };
		};
	public:
		void TransIt();
		void SetMatrix(double x11, double x12, double x13, double x14, double x21, double x22, double x23, double x24, double x31, double x32, double x33, double x34, double x41, double x42, double x43, double x44);
		void BaseMove(double xx, double yy, double zz);
		void ZRotateAngle(double Angle);
		void MoveY(double Size);
		void MoveX(double Size);
		void DrawIt();
	private:
		double pi = 3.1415926535897932384626;
		double Matrix[4][4] = { .0f };
		HYPoint poi[8] = {  };
		HYFace fac[6] = { 0 };
		CDC* pDC;
	};



}











