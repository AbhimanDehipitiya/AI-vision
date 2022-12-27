
// Main ProjectDlg.h : header file
//
#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/objdetect/objdetect.hpp>

#pragma once


// CMainProjectDlg dialog
class CMainProjectDlg : public CDialogEx
{
// Construction
public:
	CMainProjectDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN_PROJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1(); // start button
	afx_msg void OnBnClickedButton2(); // stop button
	afx_msg void OnBnClickedButton3(); // capture button
	afx_msg void OnBnClickedButton4(); // close button
	afx_msg void OnBnClickedButton5(); // help button
	afx_msg void OnLbnSelchangeList1();
	void BlinkScreen();
	void warnningMsg();
	CListBox m_listBox;
	int terminate = 0;
	int show = 0;
	int x_axis;//Declaring integer variables to store co-ordinate values//
	int y_axis;//Declaring integer variables to store co-ordinate values//
	
	
	
};
