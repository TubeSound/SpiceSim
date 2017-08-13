
// SpiceBasic.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CSpiceBasicApp:
// このクラスの実装については、SpiceBasic.cpp を参照してください。
//

class CSpiceBasicApp : public CWinApp
{
public:
	CSpiceBasicApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CSpiceBasicApp theApp;