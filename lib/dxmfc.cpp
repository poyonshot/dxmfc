#include "stdafx.h"
#include "dxmfc.h"
#include <afxanimationcontroller.h>


namespace poyonshot
{


//------------------------------------------------------------------------------
//  D2dWnd
//------------------------------------------------------------------------------


IMPLEMENT_DYNAMIC(D2dWnd, CWnd)


/// @brief  デバイス非依存オブジェクトを初期化します。
/// @return なし。
/// @throw  失敗するとKennyKerr::Exceptionをthrowします。
void D2dWnd::DoCreateDeviceIndependentResources()
{
}


/// @brief  デバイス依存オブジェクトを初期化します。
/// @return なし。
/// @throw  失敗するとKennyKerr::Exceptionをthrowします。
void D2dWnd::DoDiscardDeviceResources()
{
}


/// @brief  デバイス依存オブジェクトを初期化します。
/// @return なし。
/// @throw  失敗するとKennyKerr::Exceptionをthrowします。
void D2dWnd::DoCreateDeviceResources()
{
}


/// @brief  描画します。
/// @return なし。
void D2dWnd::DoDraw()
{
}


/// @brief  デバイス非依存オブジェクトを初期化します。
/// @return なし。
/// @throw  失敗するとKennyKerr::Exceptionをthrowします。
void D2dWnd::CreateDeviceResources()
{
    if(!m_rt)
    {
        DoCreateDeviceResources();
    }
}


/// @brief  デバイス依存オブジェクトを後始末します。
/// @return なし。
/// @throw  失敗するとKennyKerr::Exceptionをthrowします。
void D2dWnd::DiscardDeviceResources()
{
    if(m_rt)
    {
        DoDiscardDeviceResources();
        
        // レンダーターゲットの破棄
        m_rt.Reset();
    }
}


BEGIN_MESSAGE_MAP(D2dWnd, CWnd)
    ON_WM_CREATE()
    ON_WM_DESTROY()
    ON_WM_SIZE()
    ON_MESSAGE(WM_DISPLAYCHANGE, &D2dWnd::OnDisplayChange)
    ON_WM_ERASEBKGND()
    ON_WM_PAINT()
END_MESSAGE_MAP()


int D2dWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if(CWnd::OnCreate(lpCreateStruct) == -1)
    {
        return -1;
    }

    try
    {
        //デバイス非依存オブジェクトを初期化します。
        DoCreateDeviceIndependentResources();
    }
    catch(KennyKerr::Exception &)
    {
        return -1;
    }

    return 0;
}


void D2dWnd::OnDestroy()
{
    CWnd::OnDestroy();
    
    DiscardDeviceResources();
}


void D2dWnd::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);

    if(m_rt)
    {
        if(FAILED(m_rt.Resize(KennyKerr::SizeU(cx, cy))))
        {
            DiscardDeviceResources();
            Invalidate(FALSE);
        }
    }
}


LRESULT D2dWnd::OnDisplayChange(WPARAM wParam, LPARAM lParam)
{
    InvalidateRect(0);
    return 0;
}


BOOL D2dWnd::OnEraseBkgnd(CDC* pDC)
{
    return TRUE;
}


void D2dWnd::OnPaint() 
{
	CPaintDC dc(this);

    try
    {
        CreateDeviceResources();
    }
    catch(KennyKerr::Exception &)
    {
        return;
    }

    if(m_rt.CheckWindowState() == KennyKerr::Direct2D::WindowState::Occluded)
    {
        return;
    }

    //描画開始
    m_rt.BeginDraw();

    DoDraw();

    if(m_rt.EndDraw() == D2DERR_RECREATE_TARGET)
    {
        DiscardDeviceResources();
    }
}


}