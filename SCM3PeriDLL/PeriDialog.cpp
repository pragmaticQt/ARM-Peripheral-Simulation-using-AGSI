


// PeriDialog.cpp : implementation file
// Peripheral Dialog: A/D Converter (identical to LPC22xx A/D Conventer)

#include "stdafx.h"
#include "AGSI.h"
#include "SCM3PeriDLL.h"
#include "PeriDialog.h"
#include "Common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Protoyptes for forward references
static void PeriUpdate (void);
static void PeriKill   (AGSIDLGD *pM);
static void PeriDisp   (AGSIMENU *pM);

/////////////////////////////////////////////////////////////////////////////
// CPeriDialog dialog
static CPeriDialog  * pCPeriDialog;

// must not use 'const' here !
//                    iOpen  Hwnd   Dlg Proc.  Rect: -1 := default    Update       Kill
AGSIDLGD PeriDlg =  {   0,   NULL,      NULL,  { -1, -1, -1, -1, },  PeriUpdate,  PeriKill };

// The following line specifies the menu entry in the peripheral pull down menu. 
// The '&' and the following character in the sting specifies the keyboard shortcut. <Alt+A> in this case.  
//                    nDelim   *szText            *fp      nID   nDlgId         *pDlg;
AGSIMENU PeriMenu =  {  1,    "&A/D Converter", PeriDisp,  0,    IDD_ADC,       &PeriDlg   };  // Peripheral Dialog


static void PeriUpdate (void)  {            // Update Function
  if (pCPeriDialog) pCPeriDialog->Update();
}

static void PeriKill (AGSIDLGD *pM)  {      // Kill Function
  if (pCPeriDialog == NULL) return;
  pCPeriDialog->SendMessage (WM_CLOSE);
  pCPeriDialog  = NULL;
  pM->iOpen = 0;
  pM->hw    = NULL;
}

static void PeriDisp (AGSIMENU *pM)  {
  if (pM->pDlg->hw != NULL)  {              // created
    PeriKill (pM->pDlg);                    // close
  } else  {
//  AFX_MANAGE_STATE(AfxGetStaticModuleState());   // -- not necessary.
    pCPeriDialog = new CPeriDialog (pM, NULL);     // modeless construction
    if (pCPeriDialog != NULL)  {                   // construction was Ok.
      pM->pDlg->hw = pCPeriDialog->m_hWnd;         // Dialog handle
    }
  }
}

CPeriDialog::CPeriDialog (AGSIMENU *pMen, CWnd *pWnd)  {
  pM = pMen;                     // save DYM-Descriptor locally.
  Create (IDD_ADC, pWnd);
  pCPeriDialog = this;
}


// standard constructor does not work here because we are using modeless dialogs
//CPeriDialog::CPeriDialog(CWnd* pParent /*=NULL*/)
//  : CDialog(CPeriDialog::IDD, pParent)
//{
  //{{AFX_DATA_INIT(CPeriDialog)
    // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
//}


static DWORD ADC_AIN[8] = {
  IDC_ADC_AIN0, IDC_ADC_AIN1, IDC_ADC_AIN2, IDC_ADC_AIN3, 
  IDC_ADC_AIN4, IDC_ADC_AIN5, IDC_ADC_AIN6, IDC_ADC_AIN7
};


void CPeriDialog::Update (void)  {          /* Update Dialog Contents */
  DWORD     adcr,  addr;
  DWORD     adcrp, addrp;
  DWORD     rate;
  union fv  ain[8];
  union fv  v3a;
  union fv  clock;
  int       i;

  Agsi.ReadSFR(ADCR, &adcr, &adcrp, 0xFFFFFFFF);
  Agsi.ReadSFR(ADDR, &addr, &addrp, 0xFFFFFFFF);

  Agsi.ReadVTR(AIN0, &ain[0].DW);
  Agsi.ReadVTR(AIN1, &ain[1].DW);
  Agsi.ReadVTR(AIN2, &ain[2].DW);
  Agsi.ReadVTR(AIN3, &ain[3].DW);
  Agsi.ReadVTR(AIN4, &ain[4].DW);
  Agsi.ReadVTR(AIN5, &ain[5].DW);
  Agsi.ReadVTR(AIN6, &ain[6].DW);
  Agsi.ReadVTR(AIN7, &ain[7].DW);
  Agsi.ReadVTR(V3A,  &v3a.DW);
  
  Agsi.ReadVTR(CLOCK, &clock.DW);

  rate = clock.DW / (((adcr >> 8) & 0xFF) + 1);

  if (initflag == 1) {
    adcrd = ~adcr;
    addrd = ~addr;
    for (i = 0; i < 8; i++) {
      aind[i] = ain[i].f + 1.0f;
    }
    v3ad = v3a.f + 1.0f;
    rated = ~rate;
  }
  if (initflag == 2) {
    addrd = ~addr;
  }

  if (adcrd != adcr) {
	  StringHex(GetDlgItem(IDC_ADC_ADCR),    adcr, 8);
	  StringHex(GetDlgItem(IDC_ADC_SEL),     adcr & 0xFF, 2);
	  StringHex(GetDlgItem(IDC_ADC_CLKDIV), (adcr >> 8) & 0xFF, 2);
    if ((adcrd ^ adcr) & 0x00010000) ((CButton *)  GetDlgItem(IDC_ADC_BURST))->SetCheck ((adcr & 0x00010000) ? 1 : 0);
    if ((adcrd ^ adcr) & 0x00200000) ((CButton *)  GetDlgItem(IDC_ADC_PDN)  )->SetCheck ((adcr & 0x00200000) ? 1 : 0);
    if ((adcrd ^ adcr) & 0x08000000) ((CButton *)  GetDlgItem(IDC_ADC_EDGE) )->SetCheck ((adcr & 0x08000000) ? 1 : 0);
    if ((adcrd ^ adcr) & 0x000E0000) ((CComboBox *)GetDlgItem(IDC_ADC_CLKS) )->SetCurSel((adcr >> 17) & 0x07);
    if ((adcrd ^ adcr) & 0x07000000) ((CComboBox *)GetDlgItem(IDC_ADC_START))->SetCurSel((adcr >> 24) & 0x07);
    adcrd = adcr;
  }

  if (addrd != addr) {
	  StringHex(GetDlgItem(IDC_ADC_ADDR),  addr, 8);
	  StringHex(GetDlgItem(IDC_ADC_CHN),  (addr >> 24) & 0x0007, 2);
	  StringHex(GetDlgItem(IDC_ADC_VV3A), (addr >>  6) & 0x03FF, 4);
    if ((addrd ^ addr) & 0x80000000) ((CButton *)  GetDlgItem(IDC_ADC_DONE)  )->SetCheck((addr & 0x80000000) ? 1 : 0);
    if ((addrd ^ addr) & 0x40000000) ((CButton *)  GetDlgItem(IDC_ADC_OVERUN))->SetCheck((addr & 0x40000000) ? 1 : 0);
    addrd = addr;
  }

  if (rated != rate) {
    StringDec(GetDlgItem(IDC_ADC_RATE), rate);
    rated = rate;
  }

  for (i = 0; i < 8; i++) {
    if (aind[i] != ain[i].f) {
      StringFloat(GetDlgItem (ADC_AIN[i]), ain[i].f, 4);
      aind[i] = ain[i].f;
    }
  }
  if (v3ad != v3a.f) {
	  StringFloat(GetDlgItem (IDC_ADC_V3A), v3a.f, 4);
    v3ad = v3a.f;
  }

  initflag = 0;
}


BEGIN_MESSAGE_MAP(CPeriDialog, CDialog)
  //{{AFX_MSG_MAP(CPeriDialog)
  ON_WM_CLOSE()
  ON_WM_ACTIVATE()
  ON_EN_KILLFOCUS(IDC_ADC_ADCR, OnKillfocusAdcAdcr)
  ON_CBN_SELCHANGE(IDC_ADC_CLKS, OnSelchangeAdcClks)
  ON_CBN_SELCHANGE(IDC_ADC_START, OnSelchangeAdcStart)
  ON_EN_KILLFOCUS(IDC_ADC_SEL, OnKillfocusAdcSel)
  ON_EN_KILLFOCUS(IDC_ADC_CLKDIV, OnKillfocusAdcClkdiv)
  ON_BN_CLICKED(IDC_ADC_PDN, OnAdcPdn)
  ON_BN_CLICKED(IDC_ADC_BURST, OnAdcBurst)
  ON_BN_CLICKED(IDC_ADC_EDGE, OnAdcEdge)
  ON_EN_KILLFOCUS(IDC_ADC_ADDR, OnKillfocusAdcAddr)
  ON_EN_KILLFOCUS(IDC_ADC_CHN, OnKillfocusAdcChn)
  ON_EN_KILLFOCUS(IDC_ADC_VV3A, OnKillfocusAdcVv3a)
  ON_BN_CLICKED(IDC_ADC_DONE, OnAdcDone)
  ON_BN_CLICKED(IDC_ADC_OVERUN, OnAdcOverun)
  ON_EN_KILLFOCUS(IDC_ADC_V3A, OnKillfocusAdcV3a)
  ON_EN_KILLFOCUS(IDC_ADC_AIN0, OnKillfocusAdcAin0)
  ON_EN_KILLFOCUS(IDC_ADC_AIN1, OnKillfocusAdcAin1)
  ON_EN_KILLFOCUS(IDC_ADC_AIN2, OnKillfocusAdcAin2)
  ON_EN_KILLFOCUS(IDC_ADC_AIN3, OnKillfocusAdcAin3)
  ON_EN_KILLFOCUS(IDC_ADC_AIN4, OnKillfocusAdcAin4)
  ON_EN_KILLFOCUS(IDC_ADC_AIN5, OnKillfocusAdcAin5)
  ON_EN_KILLFOCUS(IDC_ADC_AIN6, OnKillfocusAdcAin6)
  ON_EN_KILLFOCUS(IDC_ADC_AIN7, OnKillfocusAdcAin7)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPeriDialog message handlers

void CPeriDialog::PostNcDestroy() {

  delete this;              // delete the new'ed object
  pCPeriDialog = NULL;      // clear external Object pointer here.
}

BOOL CPeriDialog::OnInitDialog() {
  CDialog::OnInitDialog();

  // TODO: Add extra initialization here

  // Restore Position (Only moving without resizing)
  if (PeriDlg.rc.left != -1) {
  SetWindowPos(NULL,                        /* placement order - not used */
               PeriDlg.rc.left,             /* left */
               PeriDlg.rc.top,              /* top  */
               0,                           /* width - not used */
               0,                           /* height - not used */
               SWP_NOSIZE | SWP_NOZORDER);  /* flags */
  }
  
  initflag = 1;
  Update();

  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}

void CPeriDialog::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) {
  CDialog::OnActivate(nState, pWndOther, bMinimized);
  
  switch (nState)  {
    case WA_INACTIVE:
      Agsi.HandleFocus(NULL);      // Clear Modeless Handle
      break;
    case WA_ACTIVE:
    case WA_CLICKACTIVE:
      Agsi.HandleFocus(m_hWnd);    // Set Modeless Handle
      break;
  }
}

void CPeriDialog::OnClose() {

  GetWindowRect (&pM->pDlg->rc);  // save Window position
  pM->pDlg->hw = NULL;            // clear m_hWnd
  DestroyWindow();                //--- modeless
}


void CPeriDialog::OnKillfocusAdcAdcr() {
  HandleHexInput(GetDlgItem(IDC_ADC_ADCR),  ADCR);	
}

void CPeriDialog::OnSelchangeAdcClks() {
  HandleSelInput(GetDlgItem(IDC_ADC_CLKS),  ADCR, 0x000E0000, 17);
}

void CPeriDialog::OnSelchangeAdcStart() {
  HandleSelInput(GetDlgItem(IDC_ADC_START), ADCR, 0x07000000, 24);
}

void CPeriDialog::OnKillfocusAdcSel() {
  DWORD val, oldval, newval;

  Agsi.ReadSFR(ADCR, &val, &oldval, 0x000000FF);
  oldval = val;
  if (GetDlgHex (GetDlgItem(IDC_ADC_SEL), oldval, &newval, 0xFF, 2)) {
    Agsi.WriteSFR(ADCR, newval, 0x000000FF);
    Agsi.UpdateWindows();
  }
}

void CPeriDialog::OnKillfocusAdcClkdiv() {
  DWORD val, oldval, newval;

  Agsi.ReadSFR(ADCR, &val, &oldval, 0x0000FF00);
  oldval = val >> 8;
  if (GetDlgHex (GetDlgItem(IDC_ADC_CLKDIV), oldval, &newval, 0xFF, 2)) {
    Agsi.WriteSFR(ADCR, newval << 8, 0x0000FF00);
    Agsi.UpdateWindows();
  }
}

void CPeriDialog::OnAdcPdn() {
  WriteBit(ADCR, 0x00200000, IsDlgButtonChecked (IDC_ADC_PDN));
}

void CPeriDialog::OnAdcBurst() {
  WriteBit(ADCR, 0x00010000, IsDlgButtonChecked (IDC_ADC_BURST));
}

void CPeriDialog::OnAdcEdge() {
  WriteBit(ADCR, 0x08000000, IsDlgButtonChecked (IDC_ADC_EDGE));
}


void CPeriDialog::OnKillfocusAdcAddr() {
  initflag = 2;
  HandleHexInput(GetDlgItem(IDC_ADC_ADDR), ADDR);	
}

void CPeriDialog::OnKillfocusAdcChn() {
  DWORD val, oldval, newval;

  Agsi.ReadSFR(ADDR, &val, &oldval, 0x07000000);
  oldval = val >> 24;
  if (GetDlgHex (GetDlgItem(IDC_ADC_CHN), oldval, &newval, 0x07, 2)) {
    Agsi.WriteSFR(ADDR, newval << 24, 0x07000000);
    Agsi.UpdateWindows();
  }
}

void CPeriDialog::OnKillfocusAdcVv3a() {
  DWORD val, oldval, newval;

  Agsi.ReadSFR(ADDR, &val, &oldval, 0x0000FFC0);
  oldval = val >> 6;
  if (GetDlgHex (GetDlgItem(IDC_ADC_VV3A), oldval, &newval, 0x03FF, 4)) {
    Agsi.WriteSFR(ADDR, newval << 6, 0x0000FFC0);
    Agsi.UpdateWindows();
  }
}

void CPeriDialog::OnAdcDone() {
  WriteBit(ADDR, 0x80000000, IsDlgButtonChecked (IDC_ADC_DONE));
}

void CPeriDialog::OnAdcOverun() {
  WriteBit(ADDR, 0x40000000, IsDlgButtonChecked (IDC_ADC_OVERUN));
}


void CPeriDialog::OnKillfocusAdcV3a() {
  HandleFloatInput(GetDlgItem(IDC_ADC_V3A),  V3A,  -0.5f, 3.6f, 4);
}

void CPeriDialog::OnKillfocusAdcAin0() {
  HandleFloatInput(GetDlgItem(IDC_ADC_AIN0), AIN0, -0.5f, 3.6f, 4);
}

void CPeriDialog::OnKillfocusAdcAin1() {
  HandleFloatInput(GetDlgItem(IDC_ADC_AIN1), AIN1, -0.5f, 3.6f, 4);
}

void CPeriDialog::OnKillfocusAdcAin2() {
  HandleFloatInput(GetDlgItem(IDC_ADC_AIN2), AIN2, -0.5f, 3.6f, 4);
}

void CPeriDialog::OnKillfocusAdcAin3() {
  HandleFloatInput(GetDlgItem(IDC_ADC_AIN3), AIN3, -0.5f, 3.6f, 4);
}

void CPeriDialog::OnKillfocusAdcAin4() {
  HandleFloatInput(GetDlgItem(IDC_ADC_AIN4), AIN4, -0.5f, 3.6f, 4);
}

void CPeriDialog::OnKillfocusAdcAin5() {
  HandleFloatInput(GetDlgItem(IDC_ADC_AIN5), AIN5, -0.5f, 3.6f, 4);
}

void CPeriDialog::OnKillfocusAdcAin6() {
  HandleFloatInput(GetDlgItem(IDC_ADC_AIN6), AIN6, -0.5f, 3.6f, 4);
}

void CPeriDialog::OnKillfocusAdcAin7() {
  HandleFloatInput(GetDlgItem(IDC_ADC_AIN7), AIN7, -0.5f, 3.6f, 4);
}


// The following two functions and the corresponding invisible buttons are necessary 
// to handle the behavior of the ESC and Enter Keys 
void CPeriDialog::OnCancel() {
  OnClose();	          // Close Dialog when <ESC> is pressed
}

void CPeriDialog::OnOK() {
//CDialog::OnOK();      // Do nothing when <Enter> is pressed
}
