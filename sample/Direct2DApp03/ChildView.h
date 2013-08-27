#pragma once

//  Direct2D において拡大/縮小、回転などの変換を行うサンプル
//  http://code.msdn.microsoft.com/VisualC-howto-96795643


class CChildView : public dx::D2dWnd
{
protected:
    virtual void DoCreateDeviceIndependentResources();
    virtual void DoCreateDeviceResources();
    virtual void DoDiscardDeviceResources();
    virtual void DoDraw();

    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

private:
    dx::Direct2D::Factory1 m_d2dFactory;                    //!< ファクトリオブジェクト
    dx::Direct2D::SolidColorBrush m_Brush;

protected:
    DECLARE_MESSAGE_MAP()
};

