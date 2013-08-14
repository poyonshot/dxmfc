#pragma once
#include "dx.h"


// Created by poyonshot. http://d.hatena.ne.jp/poyonshot/
// Get the latest version here: https://github.com/poyonshot/dxmfc


namespace poyonshot
{
    /// @brief  Direct2Dを使うウィンドウクラス
    class D2dWnd : public CWnd
    {
        DECLARE_DYNAMIC(D2dWnd)

    protected:
        KennyKerr::Direct2D::HwndRenderTarget m_rt;        //!< レンダーターゲット
    
        virtual void DoCreateDeviceIndependentResources();
        virtual void DoCreateDeviceResources();
        virtual void DoDiscardDeviceResources();
        virtual void DoDraw();

        void CreateDeviceResources();
        void DiscardDeviceResources();

    public:
        DECLARE_MESSAGE_MAP()
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnDestroy();
        afx_msg void OnSize(UINT nType, int cx, int cy);
        afx_msg LRESULT OnDisplayChange(WPARAM wParam, LPARAM lParam);
        afx_msg BOOL OnEraseBkgnd(CDC* pDC);
        afx_msg void OnPaint();
    };
}
