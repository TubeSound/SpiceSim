
// SpiceBasicDlg.cpp : �����t�@�C��
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



// CSpiceBasicDlg �_�C�A���O
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


// CSpiceBasicDlg ���b�Z�[�W �n���h���[

BOOL CSpiceBasicDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

	

	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
}

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CSpiceBasicDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N���C�A���g�̎l�p�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R���̕`��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
HCURSOR CSpiceBasicDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSpiceBasicDlg::OnBnClickedButtonOpen()
{
	CString filter = "Net List�i*.net)|*.net|�S��(*.*)|*.*||";
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
