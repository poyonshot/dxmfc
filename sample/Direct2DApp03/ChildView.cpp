#include "stdafx.h"
#include "Direct2DApp03.h"
#include "ChildView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



BEGIN_MESSAGE_MAP(CChildView, D2dWnd)
	ON_WM_PAINT()
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
    m_Brush = m_rt.CreateSolidColorBrush(dx::Color()); 
    m_Brush.SetColor(dx::Color(0.0F, 1.0F, 0.0F));
}


void CChildView::DoDiscardDeviceResources()
{
    m_rt.Reset();
}


void CChildView::DoDraw()
{
    //背景クリア 
    m_rt.Clear(D2D1::ColorF(D2D1::ColorF::White));

    //30度回転
    D2D1::Matrix3x2F matrix1 =
        D2D1::Matrix3x2F::Rotation(30, D2D1::Point2F(150.0F,125.0F)); 

    //2倍に拡大 
    D2D1::Matrix3x2F matrix2 =
        D2D1::Matrix3x2F::Scale(2.0F, 2.0F, D2D1::Point2F(150.0F,125.0F)); 

    //回転と拡大を合わせる 
    D2D1::Matrix3x2F matrix3 = matrix1 * matrix2;

    //変換を適用する 
    m_rt.SetTransform(matrix3);

    //四角形の描画 
    m_rt.FillRectangle(dx::RectF(100.0F, 100.0F, 200.0F, 150.F), m_Brush);
}