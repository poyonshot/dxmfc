#pragma once

// テキストレイアウトでヒットテストを実行する方法
// http://msdn.microsoft.com/ja-jp/library/windows/desktop/dd756613(v=vs.85).aspx

class CChildView : public dx::D2dWnd
{
protected:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

    virtual void DoCreateDeviceIndependentResources();
    virtual void DoCreateDeviceResources();
    virtual void DoDiscardDeviceResources();
    virtual void DoDraw();

private:
    dx::Direct2D::Factory1 m_d2dFactory;
    dx::DirectWrite::Factory1 m_dwFactory;
    dx::DirectWrite::TextFormat m_TextFormat;
    dx::DirectWrite::TextLayout m_TextLayout;
    
    dx::Direct2D::SolidColorBrush m_Brush;

    dx::Point2F m_orgText;
    dx::RectF m_rcText;
    dx::RectF m_rcHitText;

    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

