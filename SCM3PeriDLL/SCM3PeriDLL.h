// SCM3PeriDLL.h : main header file for the SCM3PERIDLL DLL
//

#if !defined(AFX_SCM3PERIDLL_H__920AF05D_C2EF_4274_B77A_4CC338FF24B1__INCLUDED_)
#define AFX_SCM3PERIDLL_H__920AF05D_C2EF_4274_B77A_4CC338FF24B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSCM3PeriDLLApp
// See SCM3PeriDLL.cpp for the implementation of this class
//

class CSCM3PeriDLLApp : public CWinApp
{
public:
	CSCM3PeriDLLApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCM3PeriDLLApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CSCM3PeriDLLApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
/*
Table 293. ADC registers
Name	Description						Access	Reset value		Address
ADCR	ADC Control Register.			R/W		0x0000 0001		0xE003.4000
        The ADCR register must 
		be written to select 
		the operating mode before 
		ADC conversion can occur.

ADGDR	ADC Global Data Register.		R/W		NA				0xE003.4004
		This register contains the 
		ADC’s DONE bit and the result 
		of the most recent ADC conversion.
*/

// SFR's
#define ADCR    0x40034000 // control register
#define ADDR    0x40034004 // data register


// VTR's
extern struct vtrlist VTREG[];

#define XTAL   (VTREG[ 0].hVTR)
#define CLOCK  (VTREG[ 1].hVTR)
#define AIN0   (VTREG[ 2].hVTR)
#define AIN1   (VTREG[ 3].hVTR)
#define AIN2   (VTREG[ 4].hVTR)
#define AIN3   (VTREG[ 5].hVTR)
#define AIN4   (VTREG[ 6].hVTR)
#define AIN5   (VTREG[ 7].hVTR)
#define AIN6   (VTREG[ 8].hVTR)
#define AIN7   (VTREG[ 9].hVTR)
#define V3A    (VTREG[10].hVTR)


// Simulation Functions
extern void wr_adcr (void);
extern void rd_addr (void);
extern void AdcConv (void);
extern void AdcDone (void);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCM3PERIDLL_H__920AF05D_C2EF_4274_B77A_4CC338FF24B1__INCLUDED_)
