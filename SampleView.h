// SampleView.h
#pragma once
#include <afxext.h>   // for CView

class CSampleView : public CView {
    DECLARE_DYNCREATE(CSampleView)
protected:
    CSampleView() {}
    //virtual ~CSampleView() {}

public:
    virtual ~CSampleView() {}

    virtual void OnDraw(CDC* pDC) override {
        pDC->TextOutW(10, 10, L"Hello from ARX MDI View!");
    }
    

    DECLARE_MESSAGE_MAP()
};

