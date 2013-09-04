#include "stdafx.h"
#include "ChildView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_MESSAGE_MAP(CChildView, dx::D2dWnd)
    ON_WM_LBUTTONDOWN()
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
    
    //DirectWriteのファクトリオブジェクト
    m_dwFactory = dx::DirectWrite::CreateFactory();
    
    //テキストレイアウトに使用するテキスト形式オブジェクト
    m_TextFormat = m_dwFactory.CreateTextFormat(L"consolas", 32.0F);
    m_TextFormat.SetTextAlignment(dx::DirectWrite::TextAlignment::Leading);
    m_TextFormat.SetParagraphAlignment(dx::DirectWrite::ParagraphAlignment::Near);

    //テキストレイアウトオブジェクト
    CString msg = L"Click on this text.\nKlicken Sie auf diesen Text.\nこのテキストをクリックしてください。";
    m_TextLayout = m_dwFactory.CreateTextLayout(msg, msg.GetLength(), m_TextFormat, FLT_MAX, FLT_MAX);
    
    //テキストを描画する位置
    m_orgText.X = 10.0F;
    m_orgText.Y = 10.0F;

    //テキストの描画サイズ
    dx::DirectWrite::TextMetrics text_metrics;
    m_TextLayout->GetMetrics(text_metrics.Get());

    //テキストを描画する領域を計算します。
    m_rcText.Left = text_metrics.Left + m_orgText.X;
    m_rcText.Right = m_rcText.Left + text_metrics.Width;
    m_rcText.Top = text_metrics.Top + m_orgText.Y;
    m_rcText.Bottom = m_rcText.Top + text_metrics.Height;
}


void CChildView::DoCreateDeviceResources()
{
    // レンダーターゲットの作成
    m_rt = m_d2dFactory.CreateHwndRenderTarget(*this);

    //ブラシの作成
    m_Brush = m_rt.CreateSolidColorBrush(dx::Color());
}


void CChildView::DoDiscardDeviceResources()
{
    m_Brush.Reset();
}


void CChildView::DoDraw()
{
    //背景クリア 
    m_rt.Clear(dx::Color(1.0F, 1.0F, 1.0F));

    //文字列を描画します。
    m_Brush.SetColor(dx::Color(0.0F, 0.0F, 0.0F));
    m_rt.DrawTextLayout(m_orgText, m_TextLayout, m_Brush);

    //文字列の領域を描画します。
    m_Brush.SetColor(dx::Color(0.0F, 0.4F, 0.5F));
    m_rt.DrawRectangle(m_rcText, m_Brush);

    //ヒットテストでヒットした文字の領域を描画します。
    m_Brush.SetColor(dx::Color(1.0F, 0.0F, 0.0F));
    m_rt.DrawRectangle(m_rcHitText, m_Brush);
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
    DWRITE_HIT_TEST_METRICS hitTestMetrics;
    BOOL isTrailingHit;
    BOOL isInside;

    m_TextLayout->HitTestPoint(
                    (FLOAT)point.x - m_orgText.X, 
                    (FLOAT)point.y - m_orgText.Y,
                    &isTrailingHit,
                    &isInside,
                    &hitTestMetrics
                    );

    m_rcHitText.Left = hitTestMetrics.left + m_orgText.X;
    m_rcHitText.Right = m_rcHitText.Left + hitTestMetrics.width;
    m_rcHitText.Top = hitTestMetrics.top + m_orgText.Y;
    m_rcHitText.Bottom = m_rcHitText.Top + hitTestMetrics.height;

    if(isInside)
    {
        BOOL underline = m_TextLayout.GetUnderline(hitTestMetrics.textPosition);

        DWRITE_TEXT_RANGE textRange = {hitTestMetrics.textPosition, 1};

        m_TextLayout.SetUnderline(!underline, textRange);
    }

    //再描画
    Invalidate(FALSE);

    D2dWnd::OnLButtonDown(nFlags, point);
}
