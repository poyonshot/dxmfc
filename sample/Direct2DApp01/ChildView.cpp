#include "stdafx.h"
#include "Direct2DApp01.h"
#include "ChildView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_MESSAGE_MAP(CChildView, D2dWnd)
END_MESSAGE_MAP()


BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
    if (!CWnd::PreCreateWindow(cs))
        return FALSE;

    cs.dwExStyle |= WS_EX_CLIENTEDGE;
    cs.style &= ~WS_BORDER;
    cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
        ::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

    return TRUE;
}


void CChildView::DoCreateDeviceIndependentResources()
{
    //Direct2Dのファクトリオブジェクト
    m_d2dFactory = dx::Direct2D::CreateFactory();
}


void CChildView::DoCreateDeviceResources()
{
    // レンダーターゲットの作成
    m_rt = m_d2dFactory.CreateHwndRenderTarget(*this);
    
    //ブラシの作成
    m_SolidBrush = m_rt.CreateSolidColorBrush(dx::Color()); 

    //ブラシの作成
    dx::Direct2D::GradientStop stops[2];
    stops[0].Position = 0.0f;
    stops[0].Color = dx::Color(0.0f, 1.0f, 1.0f, 1.0f);
    stops[1].Position = 1.0f;
    stops[1].Color = dx::Color(0.0f, 0.0f, 1.0f, 0.5f);

    m_GradientBrush = m_rt.CreateLinearGradientBrush(
          dx::Direct2D::LinearGradientBrushProperties(dx::Point2F(100.0F, 120.0F), dx::Point2F(100.0F, 270.0F))
        , dx::Direct2D::BrushProperties()
        , m_rt.CreateGradientStopCollection(stops)
    );
}


void CChildView::DoDiscardDeviceResources()
{
    m_SolidBrush.Reset();
    m_GradientBrush.Reset();
    m_rt.Reset();
}


void CChildView::DoDraw()
{
    //背景クリア 
    m_rt.Clear(dx::Color(1.0F, 1.0F, 1.0F));
    
    //円の描画 
    m_SolidBrush.SetColor(dx::Color(0.0F, 1.0F, 0.0F));
    dx::Direct2D::Ellipse ellipse1(dx::Point2F(120.0F, 120.0F), 100.0F, 100.0F); 
    m_rt.DrawEllipse(ellipse1, m_SolidBrush, 10.0F); 
    
    //1つ目の四角形の描画
    m_SolidBrush.SetColor(dx::Color(0.0F, 0.0F, 1.0F, 0.5F));
    m_rt.FillRectangle(dx::RectF(100.0F, 50.0F, 300.0F, 100.F), m_SolidBrush);
 
    //2つ目の四角形の描画
    m_rt.FillRectangle(dx::RectF(100.0F, 120.0F, 250.0F, 270.F), m_GradientBrush);
}

