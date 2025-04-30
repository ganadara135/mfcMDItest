#include "stdafx.h"
#include "resource.h"
#include "SampleDoc.h"
#include "ChildFrameSample.h"
#include "SampleView.h"
#include <stdexcept>
#include <eh.h>

#include "rxregsvc.h"            // declare acrxDynamicLinker, etc.
//#include "AcModuleResourceOverride.h"

// Define your DLL’s one-and-only extension module:
AC_IMPLEMENT_EXTENSION_MODULE(MDItest)

// our translator: will pop up a dialog telling you the SEH code & address
void seh_translator(unsigned int code, _EXCEPTION_POINTERS* ep)
{
    CString tmp;
    tmp.Format(
        _T("SEH exception: code=0x%08X\naddress=0x%p"),
        code, ep->ExceptionRecord->ExceptionAddress);
    AfxMessageBox(tmp);
    // re-throw as C++ so your catch(…) will also see it
    throw std::runtime_error("SEH");
}


CMultiDocTemplate* g_pSampleTemplate = nullptr;

// this is your “SAMPLE_NEW” command callback
//void SampleNewCommand()
//{
//    AFX_MANAGE_STATE(AfxGetStaticModuleState());
//    // switch to our ARX resources
//    HINSTANCE hOld = AfxGetResourceHandle();
//    AfxSetResourceHandle(AfxGetInstanceHandle());
//
//    if (g_pSampleTemplate) {
//        try {
//            CDocument* pDoc = g_pSampleTemplate->OpenDocumentFile(nullptr);
//            if (!pDoc)
//                throw std::runtime_error("OpenDocumentFile failed");
//        }
//        catch (...) {
//            AfxMessageBox(_T("Caught exception creating the MDI document!"));
//        }
//    }
//
//    // restore AutoCAD’s resources
//    AfxSetResourceHandle(hOld);
//}


void SampleNewCommand()
{
    // 1) AutoCAD → 우리 ARX 로 리소스 전환
    CAcModuleResourceOverride resSwitch;     // ObjectARX 2022 표준 RAII

    // 2) doc / frame / view 전부 생성
    try
    {
        CDocument* pDoc = g_pSampleTemplate->CreateNewDocument();
        CFrameWnd* pFrame = g_pSampleTemplate->CreateNewFrame(pDoc, nullptr);
        g_pSampleTemplate->InitialUpdateFrame(pFrame, pDoc);
    }
    catch (CException* e)
    {
        TCHAR buf[256]; e->GetErrorMessage(buf, 256);
        AfxMessageBox(CString(_T("MFC exception: ")) + buf);
        e->Delete();
    }
    catch (const std::exception& ex)
    {
        AfxMessageBox(CString(_T("std::exception: ")) + CA2T(ex.what()));
    }
}

void SampleNewCommand_detail()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    // switch to our ARX resources
    HINSTANCE hOld = AfxGetResourceHandle();
    AfxSetResourceHandle(AfxGetInstanceHandle());

    // assume pTpl is your CMultiDocTemplate*
    CDocument* pDoc = nullptr;
    CFrameWnd* pFrame = nullptr;

    /*if (g_pSampleTemplate) {
        try {
            CDocument* pDoc = g_pSampleTemplate->OpenDocumentFile(nullptr);
            if (!pDoc)
                throw std::runtime_error("OpenDocumentFile failed");
        }
        catch (...) {
            AfxMessageBox(_T("Caught exception creating the MDI document!"));
        }
    }*/

    // 1) create the document
    try {
        pDoc = g_pSampleTemplate->CreateNewDocument();
        if (!pDoc) throw std::runtime_error("CreateNewDocument returned NULL");
        AfxMessageBox(_T("✅ CreateNewDocument OK"));
    }
    catch (const std::exception& e) {
        AfxMessageBox(CString(_T("std::exception: ")) + CA2T(e.what()));
        return;
    }
    catch (CException* e) {
        TCHAR buf[256]; e->GetErrorMessage(buf, 256);
        AfxMessageBox(CString(_T("MFC exception: ")) + buf);
        e->Delete();
        return;
    }
    catch (...) {
        AfxMessageBox(_T("Unknown exception after CreateNewDocument!"));
        return;
    }


    // 2) create the frame
    try {
        pFrame = g_pSampleTemplate->CreateNewFrame(pDoc, nullptr);
        if (!pFrame) throw std::runtime_error("CreateNewFrame returned NULL");
        AfxMessageBox(_T("✅ CreateNewFrame OK"));
    }
    catch (const std::exception& e) {
        AfxMessageBox(CString(_T("std::exception: ")) + CA2T(e.what()));
        return;
    }
    catch (CException* e) {
        TCHAR buf[256]; e->GetErrorMessage(buf, 256);
        AfxMessageBox(CString(_T("MFC exception: ")) + buf);
        e->Delete();
        return;
    }
    catch (...) {
        AfxMessageBox(_T("Unknown exception after CreateNewFrame!"));
        return;
    }

    // 3) initialize it
    try {
        g_pSampleTemplate->InitialUpdateFrame(pFrame, pDoc);
        AfxMessageBox(_T("✅ InitialUpdateFrame OK"));
    }
    catch (...) {
        AfxMessageBox(_T("Exception during InitialUpdateFrame!"));
        return;
    }

    // restore AutoCAD’s resources
    AfxSetResourceHandle(hOld);
}

// ARX entry point
extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
    // install translator exactly once
    _set_se_translator(seh_translator);

    switch (msg) {
    case AcRx::kInitAppMsg:
        // allow MDIAware
        acrxDynamicLinker->unlockApplication(pkt);
        acrxDynamicLinker->registerAppMDIAware(pkt);

        // set up our MFC doc–template
        g_pSampleTemplate = new CMultiDocTemplate(
            IDR_SAMPLE,            // string‐table ID
            RUNTIME_CLASS(CSampleDoc),
            RUNTIME_CLASS(CChildFrameSample),
            RUNTIME_CLASS(CSampleView)
        );
        //g_pSampleTemplate->SetContainerInfo(IDR_SAMPLE_MENU);
        acedGetAcadWinApp()->AddDocTemplate(g_pSampleTemplate);

        // register our “SAMPLE_NEW” command
        acedRegCmds->addCommand(
            _T("SAMPLE_GROUP"),          // command group
            _T("SAMPLE_NEW"),            // command name
            _T("SampleNew"),             // alias
            ACRX_CMD_MODAL,              // flags
            &SampleNewCommand     // callback
        );
        break;

    case AcRx::kUnloadAppMsg:
        // remove our commands & template
        acedRegCmds->removeGroup(_T("SAMPLE_GROUP"));
        // --- delete your template (no need to call RemoveDocTemplate)
        if (g_pSampleTemplate) {
            delete g_pSampleTemplate;
            g_pSampleTemplate = nullptr;
        }
        break;
    }
    return AcRx::kRetOK;
}
