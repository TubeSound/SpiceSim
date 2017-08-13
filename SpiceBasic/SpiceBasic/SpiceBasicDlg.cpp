
// SpiceBasicDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "SpiceBasic.h"
#include "SpiceBasicDlg.h"
#include "afxdialogex.h"
#include "./Utility/StringUtility.h"
#include "./SpiceLibrary/NetList.h"
#include "./SpiceLibrary/Parse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CSpiceBasicDlg ダイアログ
using namespace SpiceLibrary;


CSpiceBasicDlg::CSpiceBasicDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SPICEBASIC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSpiceBasicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSpiceBasicDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CSpiceBasicDlg::OnBnClickedButtonOpen)
END_MESSAGE_MAP()


// CSpiceBasicDlg メッセージ ハンドラー

BOOL CSpiceBasicDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CSpiceBasicDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CSpiceBasicDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSpiceBasicDlg::OnBnClickedButtonOpen()
{
	CString filter = "Net List（*.net)|*.net|全て(*.*)|*.*||";
	CFileDialog dlg(true, "*.net", "", OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, filter, this);
	if (dlg.DoModal() != IDOK) {
		return;
	}
	CString path = dlg.GetPathName();
	string p = static_cast<string>(path);

	Parse parse;
	NetList netlist;
	parse.parseNetList(netlist, p);
	netlist.makeMatrix();

}
