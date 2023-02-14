class CMainWnd : public CFrameWnd
{
public:
	CMainWnd();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT,int,int);
	afx_msg int OnCreate(LPCREATESTRUCT cs);
	afx_msg void OnAbout();
	afx_msg void OnFourierData();
	afx_msg void OnExit();
	DECLARE_MESSAGE_MAP()
};

class CTheApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

class CFourierDataDialog : public CModalDialog
{
public:
	CFourierDataDialog(CWnd* pParentWnd = NULL) 
		: CModalDialog(_T("FourierData"),pParentWnd)
		{ }
protected:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
};
