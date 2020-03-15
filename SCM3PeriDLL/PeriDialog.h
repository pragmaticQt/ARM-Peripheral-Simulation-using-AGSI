#if !defined(AFX_PERIDIALOG_H__E0F678AC_5AD0_41BF_9D4E_425AEEAF27E5__INCLUDED_)
#define AFX_PERIDIALOG_H__E0F678AC_5AD0_41BF_9D4E_425AEEAF27E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PeriDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPeriDialog dialog

class CPeriDialog : public CDialog
{
// Construction
public:
   CPeriDialog::CPeriDialog (AGSIMENU *pMen, CWnd *pWnd);  // new constructor

   void Update (void);  // Update dialog function

// Dialog Data
   AGSIMENU *pM;

   DWORD     adcrd;
   DWORD     addrd;

   DWORD     rated;

   float     aind[8];
   float     v3ad;

   DWORD     initflag;

// Dialog Data
	//{{AFX_DATA(CPeriDialog)
	enum { IDD = IDD_ADC };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPeriDialog)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPeriDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnClose();
	afx_msg void OnKillfocusAdcAdcr();
	afx_msg void OnSelchangeAdcClks();
	afx_msg void OnSelchangeAdcStart();
	afx_msg void OnKillfocusAdcSel();
	afx_msg void OnKillfocusAdcClkdiv();
	afx_msg void OnAdcPdn();
	afx_msg void OnAdcBurst();
	afx_msg void OnAdcEdge();
	afx_msg void OnKillfocusAdcAddr();
	afx_msg void OnKillfocusAdcChn();
	afx_msg void OnKillfocusAdcVv3a();
	afx_msg void OnAdcDone();
	afx_msg void OnAdcOverun();
	afx_msg void OnKillfocusAdcV3a();
	afx_msg void OnKillfocusAdcAin0();
	afx_msg void OnKillfocusAdcAin1();
	afx_msg void OnKillfocusAdcAin2();
	afx_msg void OnKillfocusAdcAin3();
	afx_msg void OnKillfocusAdcAin4();
	afx_msg void OnKillfocusAdcAin5();
	afx_msg void OnKillfocusAdcAin6();
	afx_msg void OnKillfocusAdcAin7();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PERIDIALOG_H__E0F678AC_5AD0_41BF_9D4E_425AEEAF27E5__INCLUDED_)
