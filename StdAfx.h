#pragma once
/////////////////////////////////////////////////////////////////
// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
/////////////////////////////////////////////////////////////////

#ifndef _ACADVER
#error "Not Define _ACADVER"
#endif

#define DllExport	__declspec( dllexport )
#define DllImport	__declspec( dllimport )
#include "resource.h"
//#include "../resource.h"   // 못찾아서 바꿔줌.  ganadara 25.4.21

// AutoCAD 2000 버젼에서 사용하기 위한 수정 <- 한성훈 2000.12.18
//#ifndef _ARX2000
//#ifdef _ARX14
#if _ACADVER < 2000


#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#if defined( _DEBUG) && !defined(DEBUG_AUTOCAD)
#pragma message("Building debug version of arx_application.arx to be used with non-debug/Prod AutoCAD")
#define _DEBUG_WAS_DEFINED
#undef _DEBUG
#endif

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
//#include <afxole.h>         // MFC OLE classes
//#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC OLE automation classes
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

// Turn on the _DEBUG symbol if it was defined, before including
// non-MFC header files.
//
#ifdef _DEBUG_WAS_DEFINED
#define _DEBUG
#undef _DEBUG_WAS_DEFINED
#endif

#include <afxcoll.h>

#include "acdb.h"
#include "aced.h"
#include "acgi.h"
#include "actrans.h"			 
#include "adesk.h"
#include "adeskabb.h"
#include "adslib.h"
#include "assert.h"
#include "dbcfilrs.h"
#include "dbents.h"
#include "dbid.h"
#include "dbidmap.h"
#include "dbproxy.h"
#include "dbspline.h"
#include "dbsymtb.h"
#include "gearc3d.h"
#include "gelnsg3d.h"
#include "gepnt3d.h"
#include "gevec3d.h"
#include "rxmfcapi.h"
#include "rxregsvc.h"

//#elif _ARX2000
#elif _ACADVER == 2000

#define LOCK_DOC acDocManager->lockDocument(curDoc(), AcAp::kWrite)
#define UNLOCK_DOC  acDocManager->unlockDocument(curDoc())
// AutoCAD 14나 15에서 모두 코드를 사용하기 위하여 포함
#include "migrtion.h"
// StdAfx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif

#pragma warning(disable: 4786)

// 'DEBUG workaround' below prevents the MFC or ATL #include-s 
// from pulling in "afx.h" that would force the debug CRT through
// #pragma-s.
#ifdef _DEBUG
#define _DEBUG_WAS_DEFINED
#undef _DEBUG
#define NDEBUG
#endif

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>          // MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>         // MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>       // MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>         // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

// AutoCAD MFC Extensions:
#include "adui.h"
#include "acui.h"
#include "acuiComboBox.h"
#include "acuiDialog.h"

#ifdef _DEBUG_WAS_DEFINED
#undef NDEBUG
#define _DEBUG
#undef _DEBUG_WAS_DEFINED
#endif

#define CTemporaryResourceOverride CAcModuleResourceOverride

// RX Includes
//#include "rxdebug.h"
#include "acdb.h"               // acdb definitions
#include "rxregsvc.h"           // ARX linker
#include "dbapserv.h"           // Host application services
#include "aced.h"               // aced stuff
#include "adslib.h"             // RXADS definitions
#include "acdocman.h"           // MDI document manager
#include "rxmfcapi.h"           // ObjectARX MFC support
#include "AcExtensionModule.h"  // Utility class for extension dlls

//#elif _ARX2013
#elif _ACADVER >= 2004

#define LOCK_DOC acDocManager->lockDocument(curDoc(), AcAp::kWrite)
#define UNLOCK_DOC  acDocManager->unlockDocument(curDoc())
// AutoCAD 14나 15에서 모두 코드를 사용하기 위하여 포함
#include "migrtion.h"
// StdAfx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#pragma warning(disable: 4786)

// 'DEBUG workaround' below prevents the MFC or ATL #include-s 
// from pulling in "afx.h" that would force the debug CRT through
// #pragma-s.
#ifdef _DEBUG
#define _DEBUG_WAS_DEFINED
#undef _DEBUG
#define NDEBUG
#endif

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>          // MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>         // MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>       // MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>         // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

// AutoCAD MFC Extensions:
#include "adui.h"
#include "acui.h"
#include "acuiComboBox.h"
#include "acuiDialog.h"

#if _ACADVER >= 2007
#include "arxHeaders.h"		// 2012-08-24 jsy : VS2002는 제외
#endif

#ifdef _DEBUG_WAS_DEFINED
#undef NDEBUG
#define _DEBUG
#undef _DEBUG_WAS_DEFINED
#endif

#define CTemporaryResourceOverride CAcModuleResourceOverride

// RX Includes
//#include "rxdebug.h"
#include "acdb.h"               // acdb definitions
#include "rxregsvc.h"           // ARX linker
#include "dbapserv.h"           // Host application services
#include "aced.h"               // aced stuff
#include "adslib.h"             // RXADS definitions
#include "acdocman.h"           // MDI document manager
#include "rxmfcapi.h"           // ObjectARX MFC support
#include "AcExtensionModule.h"  // Utility class for extension dlls

#endif

// CRichEditCtrl
//#include <afxrich.h>


