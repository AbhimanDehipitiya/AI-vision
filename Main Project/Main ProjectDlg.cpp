
// Main ProjectDlg.cpp : implementation file
//
#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/objdetect/objdetect.hpp>
#include<conio.h>
#include<chrono>

#pragma comment(lib, "Powrprof.lib")
#include "pch.h"
#include "framework.h"
#include "Main Project.h"
#include "Main ProjectDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;
using namespace cv;
using namespace std::chrono_literals;
using Clock = std::chrono::system_clock;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMainProjectDlg dialog



CMainProjectDlg::CMainProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAIN_PROJECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listBox);
}

BEGIN_MESSAGE_MAP(CMainProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMainProjectDlg::OnBnClickedButton1)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMainProjectDlg::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON4, &CMainProjectDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CMainProjectDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CMainProjectDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &CMainProjectDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CMainProjectDlg message handlers

BOOL CMainProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CString str = _T("");

		str.Format(_T("Blink Screen"));
		m_listBox.AddString(str);
		str.Format(_T("Warning"));
		m_listBox.AddString(str);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMainProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMainProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMainProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMainProjectDlg::OnBnClickedButton1()
{
	Mat frame;//Declaring a matrix to video frame in it//
	namedWindow("Detect");//Declaring a window to show our work//
	destroyAllWindows();
	VideoCapture image(0);//capturing video from default camera//
	if (!image.isOpened()) { //Error message if video source is not found//
		cout << "Couldn't load video from the source.Make sure your camera is working properly." << endl;
		system("pause");
		
	}
	double height = image.set(CAP_PROP_FRAME_HEIGHT, 480);//setting up height of each frame//
	double width = image.set(CAP_PROP_FRAME_WIDTH, 640);//setting up width of each frame//
	CascadeClassifier face_cascade, eyes_cascade;//declaring a CascadeClassifier object//
	face_cascade.load("C:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml");//loading the cascade classifier//
	eyes_cascade.load("C:/opencv/sources/data/haarcascades/haarcascade_eye.xml");
	//system("cls");
	size_t z = 0;
	int check = 0;
	
	auto delayT1 = 1s;
	auto delayT2 = 20s;
	auto timePaused = Clock::now() + delayT1;
	auto timeLimit = Clock::now() + delayT2;
	while (1) {
		bool temp = image.read(frame);//loading video frames from source to our matrix named frame//
		std::vector<Rect>faces;//Declaring a vector named faces//
		face_cascade.detectMultiScale(frame, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(100, 100));//detecting the face
		z = faces.size();
		for (int i = 0; i < faces.size(); i++) { //for locating the face
			Point center(faces[i].x + faces[i].width * 0.5, faces[i].y + faces[i].height * 0.5);//getting the center of the face//
			ellipse(frame, center, Size(faces[i].width * 0.5, faces[i].height * 0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);//draw an ellipse on the face//
			Mat faceROI = frame(faces[i]);//Taking area of the face as Region of Interest for eyes//
			std::vector<Rect> eyes;//declaring a vector named eyes//
			eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(5, 5));//detect eyes in every face//
			z = eyes.size();
			for (size_t j = 0; j < eyes.size(); j++) { //for locating eyes//
				Point center(faces[i].x + eyes[j].x + eyes[j].width * 0.5, faces[i].y + eyes[j].y + eyes[j].height * 0.5);//getting the centers of both eyes//
				int radius = cvRound((eyes[j].width + eyes[j].height) * 0.25);//declaring radius of the eye enclosing circles//
				circle(frame, center, radius, Scalar(255, 0, 0), 4, 8, 0);//drawing circle around both eyes//
				x_axis = eyes[j].x;//storing x axis location of eyes in x_axis//
				y_axis = eyes[j].y;//storing y axis location of eyes in y_axis//
				//cout << "Position of the eyes is:" << "(" << x_axis << "," << y_axis << ")" << faces.size() << " " << eyes.size() << endl;//showing co-ordinate values//
			}
		}
		if ((z == 0) && (check == 0))
		{
			timePaused = Clock::now() + delayT1;
			check = 1;
		}
		else if (z != 0)
		{
			check = 0;
		}
		if (check == 1)
		{
			if (Clock::now() > timePaused)
			{
				destroyAllWindows();
				check = 0;
				timeLimit = Clock::now() + delayT2;
			}
			
		}

		if (Clock::now() > timeLimit )
		{

			::MessageBox(NULL, L"You have seen on screen more than 20 minutes. \nIt's good to give a rest to your eyes", L"Warnning!", MB_ICONWARNING);
			Beep(523, 500);
			cout << '\a';
			destroyAllWindows();
			check = 0;
			timeLimit = Clock::now() + delayT2;
		}

		if (show == 1)
		{
			imshow("Detect", frame);//showing result in window named 'Detect'//
		}
		
		if (waitKey(10) == 27) { //wait time for each frame is 30 milliseconds//
			break;
		}
		if (terminate == 1)
		{
			terminate = 0;
			break;
		}
		
	}
	destroyAllWindows();
}


void CMainProjectDlg::OnLbnSelchangeList1()
{
	
}

void CMainProjectDlg::OnBnClickedButton2()
{
	terminate = 1;
}




void CMainProjectDlg::OnBnClickedButton3()
{
	show = 1;
}


void CMainProjectDlg::OnBnClickedButton4()
{
	show = 0;
	destroyAllWindows();
}

void CMainProjectDlg::BlinkScreen()
{
	// Turn off monitor
	
	::SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM)2);
	Sleep(500); // Eliminate user's interaction for 500 ms
	// Turn on monitor
	::SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM)-1);

	// Low power monitor
	//Sleep(500); // Eliminate user's interaction for 500 ms
	//::SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM)1);
	/*HDC hDC = GetDC();
	BitBlt(hDC, 0, 0, width, height, NULL, 0, 0, BLACKNESS);
	ReleaseDC(NULL, hDC);*/
}

void CMainProjectDlg::warnningMsg()
{

}

void CMainProjectDlg::OnBnClickedButton5()
{
	BlinkScreen();
}
