#pragma once


//  Direct2D の時計描画のサンプル
//  http://msdn.microsoft.com/ja-jp/library/windows/desktop/ff819063(v=vs.85).aspx


class CChildView : public dx::D2dWnd
{
protected:
    virtual void DoCreateDeviceIndependentResources();
    virtual void DoCreateDeviceResources();
    virtual void DoDiscardDeviceResources();
    virtual void DoDraw();

    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    void CalculateLayout();
    void DrawClockHand(float fHandLength, float fAngle, float fStrokeWidth);

private:
    dx::Direct2D::Factory1 m_d2dFactory;    //!< ファクトリオブジェクト

    dx::Direct2D::RadialGradientBrush m_FillBrush;
    dx::Direct2D::SolidColorBrush m_StrokeBrush;
    dx::Direct2D::GradientStopCollection m_GradientStops;
    dx::Direct2D::Ellipse m_ellipse;
    dx::Point2F m_Ticks[24];
    UINT m_nIDEvent;                        //!< タイマーイベントID

    DECLARE_MESSAGE_MAP()
    afx_msg void OnDestroy();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnSize(UINT nType, int cx, int cy);
};

