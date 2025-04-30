// ChildFrameSample.cpp
#include "ChildFrameSample.h"

IMPLEMENT_DYNCREATE(CChildFrameSample, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrameSample, CMDIChildWnd)
    ON_WM_CREATE()
END_MESSAGE_MAP()


CChildFrameSample::CChildFrameSample()
{

}


int CChildFrameSample::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    // e.g. you could create a toolbar here

    return 0;
}


// ChildFrameSample.cpp
BOOL CChildFrameSample::PreCreateWindow(CREATESTRUCT& cs)
{
    // ① 브레이크-포인트
    if (!CMDIChildWnd::PreCreateWindow(cs))
        return FALSE;

    // ② 현재 구조체를 바로 확인
    CString msg;
    msg.Format(_T("class=%s  hInst=0x%p  hMenu=0x%p"),
        cs.lpszClass ? cs.lpszClass : _T("(null)"),
        cs.hInstance, cs.hMenu);
    AfxMessageBox(msg);               // ← 값이 모두 0 인지 확인

    /* …여기서 보정 … */
    return TRUE;
}