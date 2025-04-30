// SampleDoc.h
#pragma once
#include <afxwin.h>

class CSampleDoc : public CDocument {
    DECLARE_DYNCREATE(CSampleDoc)
protected:
    CSampleDoc() {}
public:
    virtual ~CSampleDoc() {}
    virtual BOOL OnNewDocument() override {
        if (!CDocument::OnNewDocument())
            return FALSE;
        // initialize your data here
        SetTitle(_T("Sample Window"));
        return TRUE;
    }
    // no message handlers for now
    DECLARE_MESSAGE_MAP()
};