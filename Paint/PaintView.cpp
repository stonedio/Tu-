
// PaintView.cpp: CPaintView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Paint.h"
#endif

#include "PaintDoc.h"
#include "PaintView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPaintView

IMPLEMENT_DYNCREATE(CPaintView, CView)

BEGIN_MESSAGE_MAP(CPaintView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPaintView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CPaintView 构造/析构

CPaintView::CPaintView() noexcept
{
	// TODO: 在此处添加构造代码

}

CPaintView::~CPaintView()
{
}

BOOL CPaintView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CPaintView 绘图


#include "作业/Work.h"
#include <thread>
void CPaintView::OnDraw(CDC* pDC)
{
	CPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rect;      //定义矩形  
	GetClientRect(&rect);       //获得客户区矩形的大小               
	pDC->SetMapMode(MM_ANISOTROPIC);    	//自定义坐标系                
	pDC->SetWindowExt(rect.Width(), rect.Height());   	//设置窗口比例   
	pDC->SetViewportExt(rect.Width(), -rect.Height());   	//设置视区比例，且x轴水平向右，y轴垂直向上
	pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);	//设置客户区中心为坐标系原点
	rect.OffsetRect(-rect.Width() / 2, -rect.Height() / 2);  	//矩形与客户区重合

	Color *col = new Color;
	auto exp = std::experimental::scope_guard([&]() { delete col; });
	paint::CfirstWork::instance()->initialize(pDC);
	//paint::CsecondWork::instance()->initialize(pDC);
	//paint::CthreadWork::instance()->initialize(pDC);
	//paint::CfourthWork::instance()->initialize(pDC);
	//paint::CfifthWork::instance()->initialize(pDC);
	//paint::CsixthWork::instance()->initialize(pDC);
	paint::CseventhWork::instance()->initialize(pDC);
	/*
	paint::CfirstWork::instance()->_DrawLine(80, 80, 500, 80, &col->蓝色 , 3);
	paint::CfirstWork::instance()->_DrawRect(150, 150, 150, 150, &col->红色, 1, PS_DOT, col->蓝色);
	paint::CfirstWork::instance()->_DrawCircle(600, 350, 70, &col->绿色, 2, PS_SOLID, col->蓝色, HS_DIAGCROSS);
	*/
	
	/*
	paint::CsecondWork::instance()->_DDALine(CPoint(10, 40), CPoint(80, 40), &col->蓝色);
	paint::CsecondWork::instance()->_BhmLine(CPoint(10, 10), CPoint(40, 40), &col->品红);
	*/

	/*
	paint::CthreadWork::getInstance()._BhmCircle(CPoint(100, 100), 20, &col->玻璃黑);
	*/

	/*
	//不能detach 难受啊
	if (paint::CfourthWork::instance() != nullptr)
	{
		//std::bind或许更好用 偷懒直接lambda
		auto tDraw = std::thread([=] {
			paint::CfourthWork::getInstance().PolygonFill(
				col->白色, col->红色,
				paint::mPOINT(275, 200), paint::mPOINT(175, 300),
				paint::mPOINT(125, 175), paint::mPOINT(175, 25),
				paint::mPOINT(250, 125), paint::mPOINT(300, 25),
				paint::mPOINT(400, 225)
			);
		}
		);
		tDraw.detach();
	}
	*/
	
	/*
	paint::CfifthWork::getInstance().PolygonFill(CPoint(230, 21), &col->品红);
	*/

	/*paint::CsixthWork::LinePoint L1{ 350, 600, 700, 100 };
	paint::CsixthWork::LinePoint L2{ 500, 500 ,300, 500 };
	paint::CsixthWork::LinePoint L3{ 300, 300 ,600, 400 };
	paint::CsixthWork::getInstance().TestLine(L1, L2, L3);*/

	//画原始
	paint::CseventhWork::getInstance().DrawIt();
	paint::CseventhWork::getInstance().ZRotateAngle(15.f); // 旋转15°
	paint::CseventhWork::getInstance().MoveX(200.f); //右移200.f
	paint::CseventhWork::getInstance().MoveY(-200.f); //下移200.f
	//画变换后的
	paint::CseventhWork::getInstance().DrawIt();


}


// CPaintView 打印


void CPaintView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPaintView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CPaintView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CPaintView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CPaintView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPaintView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPaintView 诊断

#ifdef _DEBUG
void CPaintView::AssertValid() const
{
	CView::AssertValid();
}

void CPaintView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPaintDoc* CPaintView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPaintDoc)));
	return (CPaintDoc*)m_pDocument;
}
#endif //_DEBUG


// CPaintView 消息处理程序
