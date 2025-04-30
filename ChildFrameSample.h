// ChildFrameSample.h
#pragma once
#include <afxext.h>   // for CMDIChildWnd
#include "resource.h"

class CChildFrameSample : public CMDIChildWnd {
    DECLARE_DYNCREATE(CChildFrameSample)
public:
    CChildFrameSample();
    virtual ~CChildFrameSample() {}

public:
    // optionally tweak your CREATESTRUCT
    //virtual BOOL PreCreateWindow(CREATESTRUCT& cs) override {
    //    // pick up the MENU you gave us:
    //   /* cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
    //    cs.style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;*/
    //    cs.hMenu = ::LoadMenu(
    //        AfxGetResourceHandle(),
    //        MAKEINTRESOURCE(IDR_SAMPLE)
    //    );
    //    return CMDIChildWnd::PreCreateWindow(cs);
    //}
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg BOOL PreCreateWindow(CREATESTRUCT& cs);

    // hook OnCreate if you want a toolbar, statusbar, etc.
//protected:
//    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct) {
//        if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
//            return -1;
//        // no toolbar here—keep it minimal
//        return 0;
//    }
    DECLARE_MESSAGE_MAP()
};
