//
// Fourier.cpp
// Disegno di una serie di Fourier utilizzando
// la libreria MFC.
// Copyright (C) William H. Murray and Chris H. Pappas, 1997
// Settaggi di Progetto: Set di caratteri UNICODE - usa MFC in una DLL condivisa
// Un'applicazione per serie di Fourier pag. 689
//

#include <afxwin.h>
#include <string.h>
#include <math.h>
#include "FourierR-06.h"   //identificativi delle risorse
#include "Fourier-06.h"

int m_cxClient,m_cyClient;
TCHAR mytitle[80] = _T("Analisi di Fourier");
int nterms = 2;

CTheApp theApp;

CMainWnd::CMainWnd()
{
	Create((AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW,
		LoadCursor(NULL,IDC_CROSS),
		(HBRUSH) (GetStockObject(WHITE_BRUSH)),NULL)),
		_T("Applicazione per serie di Fourier con MFC"),
		WS_OVERLAPPEDWINDOW,rectDefault,NULL,_T("FourierMenu"));
}

void CMainWnd::OnSize(UINT,int x,int y)
{
	m_cxClient=x;
	m_cyClient=y;
}

void CMainWnd::OnPaint()
{
	CPaintDC dc(this);
	static DWORD dwColor[9] = {RGB(0,0,0),        //nero 0
							   RGB(245,0,0),      //rosso 1
							   RGB(0,245,0),      //verde 2
							   RGB(0,0,245),      //blu 3
							   RGB(245,245,0),    //giallo 4
							   RGB(245,0,245),    //magenta 5
							   RGB(0,245,245),    //ciano 6
							   RGB(127,127,127),  //grigio 7
							   RGB(245,245,245),  //bianco 8
	};
	int i,j,ang;
	double y,yp;
	CBrush newbrush;
	CBrush* oldbrush;
	CPen newpen;
	CPen* oldpen;

	// crea una superficie di disegno personalizzata
	dc.SetMapMode(MM_ISOTROPIC);
	dc.SetWindowExt(900,900);
	dc.SetViewportExt(m_cxClient,-m_cyClient);
	dc.SetWindowOrg(m_cxClient/20,m_cyClient/2);

	ang=0;
	yp=0,0;

	newpen.CreatePen(BS_SOLID,2,RGB(0,0,0));
	oldpen = dc.SelectObject(&newpen);

	// disegna gli assi x e y
	dc.MoveTo(150,240);
	dc.LineTo(150,-240);
	dc.MoveTo(150,0);
	dc.LineTo(1000,0);
	dc.MoveTo(150,0);

	// disegna l'effettiva forma d'onda di Fourier
	for (i=150; i<=950; i++) {
		for (j = 1; j <= nterms; j++) {
			y = (150.0 / ((2.0 * j) - 1.0)) * sin(((j * 2.0) - 1.0) * 0.015708 * ang);
			yp = yp + y;
		}
		dc.LineTo(i,(int) yp);
		yp-=yp;
		ang++;
	}

	// prepara un nuovo pennello per riempire l'interno della forma d'onda
	newbrush.CreateSolidBrush(dwColor[6]);
	oldbrush=dc.SelectObject(&newbrush);
	dc.ExtFloodFill(200,10,dwColor[0],FLOODFILLBORDER);
	dc.ExtFloodFill(400,-10,dwColor[0],FLOODFILLBORDER);
	dc.ExtFloodFill(700, 10, dwColor[0], FLOODFILLBORDER);
	dc.ExtFloodFill(800, -10, dwColor[0], FLOODFILLBORDER);

	// scrive il titolo della forma d'onda
	TextOut(dc, 300-(_tcslen(mytitle)*8/2),285,mytitle,_tcslen(mytitle));

	// cancella gli oggetti pennello
	dc.SelectObject(oldbrush);
	newbrush.DeleteObject();
	}

	int CMainWnd::OnCreate(LPCREATESTRUCT)
	{
		UpdateWindow();
		return(0);
	}

	void CMainWnd::OnAbout()
	{
		CModalDialog about(_T("AboutBox"),this);
		about.DoModal();
	}

	BOOL CFourierDataDialog::OnInitDialog()
	{
		CModalDialog::OnInitDialog();
		SetDlgItemText(IDD_TITLE, mytitle);
		SetDlgItemInt(IDD_TERMS, nterms);
		return TRUE;
	}

	void CFourierDataDialog::OnOK()
	{
		GetDlgItemText(IDD_TITLE, mytitle, 80);		
		nterms = GetDlgItemInt(IDD_TERMS,NULL,0);
		CModalDialog::OnOK();
	}

	void CMainWnd::OnFourierData()
	{
		CFourierDataDialog dlgFourierData(this);
		if (dlgFourierData.DoModal()==IDOK) {
			InvalidateRect(NULL,TRUE);
			UpdateWindow();
		}
	};

	void CMainWnd::OnExit()
	{
		DestroyWindow();
	}

	BEGIN_MESSAGE_MAP(CMainWnd,CFrameWnd)
		ON_WM_PAINT()
		ON_WM_SIZE()
		ON_WM_CREATE()
		ON_COMMAND(IDM_ABOUT,OnAbout)
		ON_COMMAND(IDM_FOUR,OnFourierData)
		ON_COMMAND(IDM_EXIT,OnExit)
	END_MESSAGE_MAP()

	BOOL CTheApp::InitInstance()
	{
		m_pMainWnd=new CMainWnd();
		m_pMainWnd->ShowWindow(m_nCmdShow);
		m_pMainWnd->UpdateWindow();
		return TRUE;
	}
