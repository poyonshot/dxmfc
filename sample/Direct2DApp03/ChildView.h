#pragma once

//  Direct2D �ɂ����Ċg��/�k���A��]�Ȃǂ̕ϊ����s���T���v��
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
    dx::Direct2D::Factory1 m_d2dFactory;                    //!< �t�@�N�g���I�u�W�F�N�g
    dx::Direct2D::SolidColorBrush m_Brush;

protected:
    DECLARE_MESSAGE_MAP()
};

