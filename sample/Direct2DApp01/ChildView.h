#pragma once


//  [�A��! �Ƃ��Ƃ� VC++]
//  �� 10 �� �l�C�e�B�u VC++ �ɂ�����O���t�B�b�N�X�I�[�o�[�r���[�A����� Direct2D �̊�{�I�ȗ��p���@
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
    dx::Direct2D::Factory1 m_d2dFactory;                    //!< �t�@�N�g���I�u�W�F�N�g
    dx::Direct2D::SolidColorBrush m_SolidBrush;             //!< �\���b�h�u���V
    dx::Direct2D::LinearGradientBrush m_GradientBrush;      //!< �O���f�[�V�����u���V

    DECLARE_MESSAGE_MAP()
};

