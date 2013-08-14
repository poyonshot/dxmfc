#pragma once


//  [連載! とことん VC++]
//  第 10 回 ネイティブ VC++ におけるグラフィックスオーバービュー、および Direct2D の基本的な利用方法
//  http://code.msdn.microsoft.com/windowsdesktop/VisualC-7e652493


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
    dx::Direct2D::SolidColorBrush m_SolidBrush;             //!< ソリッドブラシ
    dx::Direct2D::LinearGradientBrush m_GradientBrush;      //!< グラデーションブラシ

    DECLARE_MESSAGE_MAP()
};

