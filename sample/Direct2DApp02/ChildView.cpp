#include "stdafx.h"
#include "Direct2DApp02.h"
#include "ChildView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_MESSAGE_MAP(CChildView, D2dWnd)
    ON_WM_TIMER()
    ON_WM_DESTROY()
    ON_WM_SIZE()
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

    //タイマーイベントを設定
    m_nIDEvent = SetTimer(0, 500, 0);
}


void CChildView::DoCreateDeviceResources()
{
    // レンダーターゲットの作成
    m_rt = m_d2dFactory.CreateHwndRenderTarget(*this);
    
    //ブラシの作成
    m_StrokeBrush = m_rt.CreateSolidColorBrush(dx::Color()); 
    m_StrokeBrush.SetColor(dx::Color(0.0F, 0.0F, 0.0F));

    //
    CalculateLayout();
}



void CChildView::CalculateLayout()
{
    //時計を描画するための情報を取得します。
    {
        auto fSize = m_rt.GetSize();
        const float x = fSize.Width / 2.0f;
        const float y = fSize.Height / 2.0f;
        const float radius = min(x, y) - 10;
        m_ellipse = dx::Direct2D::Ellipse(dx::Point2F(x, y), radius, radius);
    }

    // Calculate tick marks.
    {
        dx::Point2F pt1(
            m_ellipse.Center.X,
            m_ellipse.Center.Y - (m_ellipse.RadiusY * 0.9f)
        );

        dx::Point2F pt2(
            m_ellipse.Center.X,
            m_ellipse.Center.Y - m_ellipse.RadiusY
        );

        for(DWORD i = 0; i < 12; i++)
        {
            D2D1::Matrix3x2F mat = D2D1::Matrix3x2F::Rotation(
                (360.0f / 12) * i, m_ellipse.Center.Ref()
            );
    
            m_Ticks[i*2] = mat.TransformPoint(pt1.Ref());
            m_Ticks[i*2 + 1] = mat.TransformPoint(pt2.Ref());
        }
    }

    // Define the gradient stops for the brush.
    {
        dx::Direct2D::GradientStop stops[2];
        stops[0].Position = 0.0f;
        stops[0].Color = dx::Color(D2D1::ColorF(D2D1::ColorF::Yellow, 1));
        stops[1].Position = 1.0f;
        stops[1].Color = dx::Color(D2D1::ColorF(D2D1::ColorF::ForestGreen, 1));

        // Create the gradient stop collection.
        m_GradientStops = m_rt.CreateGradientStopCollection(stops, 2);

        m_FillBrush = m_rt.CreateRadialGradientBrush(
            dx::Direct2D::RadialGradientBrushProperties(
                  m_ellipse.Center
                , D2D1::Point2F(0, 0)
                , m_ellipse.RadiusX
                , m_ellipse.RadiusY
            )
            , dx::Direct2D::BrushProperties()
            , m_GradientStops
        );
    }
}



void CChildView::DoDiscardDeviceResources()
{
    m_StrokeBrush.Reset();
    m_rt.Reset();
}


void CChildView::DoDraw()
{
    //背景クリア 
    m_rt.Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));

    //時計の背景の描画
    m_rt.FillEllipse(m_ellipse, m_FillBrush);
    m_rt.DrawEllipse(m_ellipse, m_StrokeBrush);

    // Draw tick marks
    for(DWORD i = 0; i < 12; i++)
    {
        m_rt.DrawLine(m_Ticks[i*2], m_Ticks[i*2+1], m_StrokeBrush, 2.0f);
    }

    // Draw hands
    SYSTEMTIME time;
    GetLocalTime(&time);

    // 60 minutes = 30 degrees, 1 minute = 0.5 degree
    const float fHourAngle = (360.0f / 12) * (time.wHour) + (time.wMinute * 0.5f); 
    const float fMinuteAngle = (360.0f / 60) * (time.wMinute);
    const float fSecondAngle = (360.0f / 60) * (time.wSecond);

    DrawClockHand(0.6f,  fHourAngle,   6);
    DrawClockHand(0.85f, fMinuteAngle, 4);
    DrawClockHand(0.85f, fSecondAngle, 1);

    // Restore the identity transformation.
    m_rt.SetTransform(D2D1::Matrix3x2F::Identity());
}


void CChildView::DrawClockHand(float fHandLength, float fAngle, float fStrokeWidth)
{
    m_rt->SetTransform(D2D1::Matrix3x2F::Rotation(fAngle, m_ellipse.Center.Ref()));

    // endPoint defines one end of the hand.
    dx::Point2F endPoint(
        m_ellipse.Center.X, m_ellipse.Center.Y - (m_ellipse.RadiusY * fHandLength)
    );

    // Draw a line from the center of the ellipse to endPoint.
    m_rt.DrawLine(m_ellipse.Center, endPoint, m_StrokeBrush, fStrokeWidth);
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
    Invalidate(FALSE);
    D2dWnd::OnTimer(nIDEvent);
}


void CChildView::OnDestroy()
{
    D2dWnd::OnDestroy();
    KillTimer(m_nIDEvent);
}


void CChildView::OnSize(UINT nType, int cx, int cy)
{
    D2dWnd::OnSize(nType, cx, cy);

    if(m_rt)
    {
        CalculateLayout();
    }
}