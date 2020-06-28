#include "pch.h"
#include "Work.h"

namespace paint {
	void CfirstWork::_DrawLine(int x1, int y1, int x2, int y2, RGBA* penColor, float thickness, int PenStyle)
	{
		if ((ColorConvertFloat4ToU32(Vec4(penColor->R / 255.0, penColor->G / 255.0, penColor->B / 255.0, penColor->A / 255.0)) & COL32_A_MASK) == 0)
			return;
		auto pStart = CPoint{ x1, y1 };
		auto pEnd = CPoint{ x2, y2 };
		CPen pen(PenStyle, thickness, RGB(penColor->R, penColor->G, penColor->B));
		pDC->SelectObject(static_cast<HGDIOBJ>(pen));
		pDC->MoveTo(pStart);
		pDC->LineTo(pEnd);
	}

	void CfirstWork::_DrawRect(int x, int y, int w, int h, RGBA *penColor, int thickness, int PenStyle, ...)
	{
		if ((ColorConvertFloat4ToU32(Vec4(penColor->R / 255.0, penColor->G / 255.0, penColor->B / 255.0, penColor->A / 255.0)) & COL32_A_MASK) == 0)
			return;
		auto rect = CRect(x, y, x + w, h + y);
		CPen pen(PenStyle, thickness, RGB(penColor->R, penColor->G, penColor->B));
		pDC->SelectObject(static_cast<HGDIOBJ>(pen));
		pDC->Rectangle(rect);

		va_list ArgumentList;
		va_start(ArgumentList, PenStyle);
		auto color = va_arg(ArgumentList, RGBA);
		auto brushStyle = va_arg(ArgumentList, int);
		va_end(ArgumentList);
		CBrush *brush;
		if (brushStyle < 0xff && brushStyle > 0)
			brush = new CBrush(brushStyle, RGB(color.R, color.G, color.B));
		else
			brush = new CBrush(RGB(color.R, color.G, color.B));
		auto exp = std::experimental::scope_guard([&]() { delete brush; });

		pDC->SelectObject(brush);

		pDC->Rectangle(rect);



	}

	void CfirstWork::_DrawCircle(int x, int y, int radius, RGBA *penColor, int thickness, int PenStyle, ...)
	{
		if ((ColorConvertFloat4ToU32(Vec4( penColor->R / 255.0, penColor->G / 255.0, penColor->B / 255.0, penColor->A / 255.0 )) & COL32_A_MASK) == 0)
			return;
		CRect rect{ x - radius, y - radius, x + radius, y + radius };
		CPen pen(PenStyle, thickness, RGB(penColor->R, penColor->G, penColor->B));
		pDC->SelectObject(pen);

		pDC->Ellipse(rect);

		va_list ArgumentList;
		va_start(ArgumentList, PenStyle);
		auto color = va_arg(ArgumentList, RGBA);
		auto brushStyle = va_arg(ArgumentList, int);
		va_end(ArgumentList);
		CBrush *brush;
		if (brushStyle < 0xff && brushStyle > 0)
			brush = new CBrush(brushStyle, RGB(color.R, color.G, color.B));
		else
			brush = new CBrush(RGB(color.R, color.G, color.B));

		auto exp = std::experimental::scope_guard([&]() { delete brush; });
		pDC->SelectObject(brush);
		pDC->Ellipse(rect);
	}

	void CsecondWork::_DDALine(CPoint& pStart, CPoint& pEnd, RGBA *penColor)
	{
		double k, delta_x, delta_y;
		delta_x = pStart.x - pEnd.x;
		delta_y = pStart.y - pEnd.y;

		CPoint p = pStart;
		pDC->SetPixelV(p, RGB(penColor->R, penColor->G, penColor->B));

		if (!delta_x)
		{
			while (p.y != pEnd.y)
			{
				p.y++;
				pDC->SetPixelV(p, RGB(penColor->R, penColor->G, penColor->B));
			}
		}
		else if ((k = delta_y / delta_x) < 1 && k > -1)
		{
			double temp = p.y;
			while (p.x != pEnd.x)
			{
				p.x++;
				temp += k;
				p.y = temp + 0.5;
				pDC->SetPixelV(p, RGB(penColor->R, penColor->G, penColor->B));
			}
		}
		else
		{
			double temp = p.x;
			while (p.y != pEnd.y)
			{
				p.y++;
				temp += 1 / k;
				p.x = temp + 0.5;
				pDC->SetPixelV(p, RGB(penColor->R, penColor->G, penColor->B));
			}
		}

	}

	void CsecondWork::_BhmLine(CPoint & pStart, CPoint & pEnd, RGBA * penColor)
	{
		double d, delta_x, delta_y, k;
		delta_x = pEnd.x - pStart.x;
		delta_y = pEnd.y - pStart.y;
		d = 2 * delta_y - delta_x;

		CPoint p = pStart;
		pDC->SetPixelV(p, RGB(penColor->R, penColor->G, penColor->B));

		if ((k = delta_y / delta_x) < 1 && k >= 0) {
			while (p.x != pEnd.x)
			{
				p.x++;
				if (d >= 0)
					p.y++;
				else
					p.y = p.y;
				pDC->SetPixelV(p, RGB(penColor->R, penColor->G, penColor->B));
				if (d >= 0)
					d = d + 2 * delta_y - 2 * delta_x;
				else
					d = d + 2 * delta_y;
			}
		}
		else
		{
			while (p.y != pEnd.y)
			{
				p.y++;
				if (d >= 0)
					p.x++;
				else
					p.x = p.x;
				pDC->SetPixelV(p, RGB(penColor->R, penColor->G, penColor->B));
				if (d >= 0)
					d = d + 2 * delta_x - 2 * delta_y;
				else
					d = d + 2 * delta_x;
			}
		}
	}

	void CthreadWork::_BhmCircle(CPoint & p, int radius, RGBA * penColor)
	{
		
		int tx = 0, ty = radius, d = 3 - 2 * radius;

		while (tx <= ty)
		{
			pDC->SetPixelV(p.x + tx, p.y + ty,  RGB(penColor->R, penColor->G, penColor->B));
			pDC->SetPixelV(p.x + tx, p.y - ty,  RGB(penColor->R, penColor->G, penColor->B));
			pDC->SetPixelV(p.x - tx, p.y + ty,  RGB(penColor->R, penColor->G, penColor->B));
			pDC->SetPixelV(p.x - tx, p.y - ty,  RGB(penColor->R, penColor->G, penColor->B));
			pDC->SetPixelV(p.x + ty, p.y + tx,  RGB(penColor->R, penColor->G, penColor->B));
			pDC->SetPixelV(p.x + ty, p.y - tx,  RGB(penColor->R, penColor->G, penColor->B));
			pDC->SetPixelV(p.x - ty, p.y + tx,  RGB(penColor->R, penColor->G, penColor->B));
			pDC->SetPixelV(p.x - ty, p.y - tx,  RGB(penColor->R, penColor->G, penColor->B));
									
			if (d < 0)		
				d += 4 * tx + 6;
			else			
				d += 4 * (tx - ty) + 10, ty--;

			tx++;
		}
	}

	void CfifthWork::PolygonFill(CPoint & p, RGBA * Color)
	{
		if ((ColorConvertFloat4ToU32(Vec4(Color->R / 255.0, Color->G / 255.0, Color->B / 255.0, Color->A / 255.0)) & COL32_A_MASK) == 0)
			return;
		std::list a = { 0, p };
		a.push_back(p);

		while (!a.empty())
		{
			CPoint point = a.back();
			a.pop_back();

			pDC->SetPixelV(point, RGB(Color->R, Color->G, Color->B));

			if (pDC->GetPixel(point.x + 1, point.y) != RGB(0, 0, 0) && pDC->GetPixel(point.x + 1, point.y) != RGB(Color->R, Color->G, Color->B))
			{
				CPoint rP = CPoint(point.x + 1, point.y);
				a.push_back(rP);
			}
			if (pDC->GetPixel(point.x - 1, point.y) != RGB(0, 0, 0) && pDC->GetPixel(point.x - 1, point.y) != RGB(Color->R, Color->G, Color->B))
			{
				CPoint lP = CPoint(point.x - 1, point.y);
				a.push_back(lP);
			}
			if (pDC->GetPixel(point.x, point.y + 1) != RGB(0, 0, 0) && pDC->GetPixel(point.x, point.y + 1) != RGB(Color->R, Color->G, Color->B))
			{
				CPoint tP = CPoint(point.x, point.y + 1);
				a.push_back(tP);
			}
			if (pDC->GetPixel(point.x, point.y - 1) != RGB(0, 0, 0) && pDC->GetPixel(point.x, point.y - 1) != RGB(Color->R, Color->G, Color->B))
			{
				CPoint bP = CPoint(point.x, point.y - 1);
				a.push_back(bP);
			}


		}

	}

	void CsixthWork::CohenSutherland()
	{
		bool done = false;
		int code1, code2;
		auto Lpoint = P.back();
		P.pop_back();
		
		CPoint p1(Lpoint.x1, Lpoint.y1);
		CPoint p2(Lpoint.x2, Lpoint.y2);

		unsigned int C1 = EnCode(p1.x, p1.y);
		unsigned int C2 = EnCode(p2.x, p2.y);
		unsigned int C;
		double k = (double)(p2.y - p1.y) / (double)(p2.x - p1.x);

		Color *col = new Color;
		auto exp = std::experimental::scope_guard([&]() { delete col; });

		while (C1 != 0 || C2 != 0)
		{

			if ((C1 & C2) != 0)
				return;

			if (C1 == 0)
			{
				CPoint p = p1;
				p1 = p2;
				p2 = p;

				C = C2;
			}
			else {
				C = C1;
			}


			CPoint p;
			if (C == 1)
			{
				p.x = 250;
				p.y = k * (p.x - p1.x) + p1.y;;
			}
			else if (C == 2)
			{
				p.x = 850;
				p.y = k * (p.x - p1.x) + p1.y;
			}
			else if (C == 8)
			{
				p.y = 450;
				p.x = (p.y - p1.y) / k + p1.x;
			}
			else
			{
				p.y = 250;
				p.x = (p.y - p1.y) / k + p1.x;
			}
			p1 = p;

			C1 = EnCode(p1.x, p1.y);
			C2 = EnCode(p2.x, p2.y);

		}

		paint::CfirstWork::instance()->_DrawLine(p1.x, p1.y, p2.x, p2.y, &col->黑色, 1);
	}

	void CseventhWork::initialize(CDC * _pDC)
	{
		this->pDC = _pDC;
		Color *col = new Color;
		auto exp = std::experimental::scope_guard([&]() { delete col; });

		pDC->TextOut(0 , 0 , L"(0,0)");
		CfirstWork::getInstance()._DrawLine(0 , 0 , 300 , 0 , &col->黑色, 1.5);
		pDC->TextOut(300 , 0 , L"X");
		CfirstWork::getInstance()._DrawLine(0 , 0 , 0 , 300 , &col->黑色, 1.5);
		pDC->TextOut(0 , 300 , L"Y");
		CfirstWork::getInstance()._DrawLine(0 , 0 , -225 , -225 , &col->黑色, 1.5);
		pDC->TextOut(-225 , -225 , L"Z");
		this->poi[0] = HYPoint(0, 0, 0);
		this->poi[1] = HYPoint(100, 0, 0);
		this->poi[2] = HYPoint(100, 100, 0);
		this->poi[3] = HYPoint(0, 100, 0);
		this->poi[4] = HYPoint(0, 0, 100);
		this->poi[5] = HYPoint(100, 0, 100);
		this->poi[6] = HYPoint(100, 100, 100);
		this->poi[7] = HYPoint(0, 100, 100);

		this->fac[0].num_p = 4;	this->fac[0].index[0] = 4;	this->fac[0].index[1] = 5;	this->fac[0].index[2] = 6;	this->fac[0].index[3] = 7;
		this->fac[1].num_p = 4;	this->fac[1].index[0] = 0;	this->fac[1].index[1] = 3;	this->fac[1].index[2] = 2;	this->fac[1].index[3] = 1;
		this->fac[2].num_p = 4;	this->fac[2].index[0] = 0;	this->fac[2].index[1] = 4;	this->fac[2].index[2] = 7;	this->fac[2].index[3] = 3;
		this->fac[3].num_p = 4;	this->fac[3].index[0] = 1;	this->fac[3].index[1] = 2;	this->fac[3].index[2] = 6;	this->fac[3].index[3] = 5;
		this->fac[4].num_p = 4;	this->fac[4].index[0] = 2;	this->fac[4].index[1] = 3;	this->fac[4].index[2] = 7;	this->fac[4].index[3] = 6;
		this->fac[5].num_p = 4;	this->fac[5].index[0] = 0;	this->fac[5].index[1] = 1;	this->fac[5].index[2] = 5;	this->fac[5].index[3] = 4;

		SetMatrix(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);

		TransIt();
	}

	void CseventhWork::TransIt()
	{
		int i, j, k;
		double ans[8][4];
		memset(ans, 0, sizeof(ans));
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 4; j++) {
				for (k = 0; k < 4; k++) {
					ans[i][j] += (this->poi[i].p[k] * this->Matrix[k][j]);
				}
			}
		}
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 4; j++) {
				this->poi[i].p[j] = ans[i][j];
			}
		}
	}

	void CseventhWork::SetMatrix(double x11, double x12, double x13, double x14, double x21, double x22, double x23, double x24, double x31, double x32, double x33, double x34, double x41, double x42, double x43, double x44)
	{
		this->Matrix[0][0] = x11;	this->Matrix[0][1] = x12;	this->Matrix[0][2] = x13;	this->Matrix[0][3] = x14;
		this->Matrix[1][0] = x21;	this->Matrix[1][1] = x22;	this->Matrix[1][2] = x23;	this->Matrix[1][3] = x24;
		this->Matrix[2][0] = x31;	this->Matrix[2][1] = x32;	this->Matrix[2][2] = x33;	this->Matrix[2][3] = x34;
		this->Matrix[3][0] = x41;	this->Matrix[3][1] = x42;	this->Matrix[3][2] = x43;	this->Matrix[3][3] = x44;
	}

	void CseventhWork::BaseMove(double xx, double yy, double zz)
	{
		SetMatrix(1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			xx, yy, zz, 1);
		TransIt();
	}

	void CseventhWork::ZRotateAngle(double Angle)
	{
		double xx = (this->poi[0].p[0] + this->poi[6].p[0]) / 2;
		double yy = (this->poi[0].p[1] + this->poi[6].p[1]) / 2;
		double zz = (this->poi[0].p[2] + this->poi[6].p[2]) / 2;
		BaseMove(-xx, -yy, -zz);
		SetMatrix(cos(-Angle / 360 * pi), sin(-Angle / 360 * pi), 0, 0,
			-sin(-Angle / 360 * pi), cos(-Angle / 360 * pi), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
		TransIt();
		BaseMove(xx, yy, zz);

	}

	void CseventhWork::MoveY(double Size)
	{
		BaseMove(0, Size, 0);
	}

	void CseventhWork::MoveX(double Size)
	{
		BaseMove(Size, 0, 0);
	}

	void CseventhWork::DrawIt()
	{
		int i, j, k, pot;
		double t[4][4] = { {1,0,0,0},
						{0,1,0,0},
						{-cos(pi / 4),-sin(pi / 4),0,0},
						{0,0,0,1} };
		double ans[8][4];
		memset(ans, 0, sizeof(ans));
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 4; j++) {
				for (k = 0; k < 4; k++) {
					ans[i][j] += (this->poi[i].p[k] * t[k][j]);
				}
			}
		}

		for (i = 1; i < 6; i++) {
			pot = this->fac[i].index[0];
			pDC->MoveTo((int)ans[pot][0], (int)ans[pot][1]);
			for (j = 0; j < this->fac[i].num_p; j++) {
				pot = this->fac[i].index[(j + 1) % (this->fac[i].num_p)];
				pDC->LineTo((int)ans[pot][0], (int)ans[pot][1]);
			}
		}

	}



}
