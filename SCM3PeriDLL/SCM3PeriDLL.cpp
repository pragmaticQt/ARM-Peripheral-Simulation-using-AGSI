// SCM3PeriDLL.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "AGSI.h"
#include "SCM3PeriDLL.h"
#include "Common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//


// CSCM3PeriDLLApp

BEGIN_MESSAGE_MAP(CSCM3PeriDLLApp, CWinApp)
END_MESSAGE_MAP()


// CSCM3PeriDLLApp construction

CSCM3PeriDLLApp::CSCM3PeriDLLApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CSCM3PeriDLLApp object

CSCM3PeriDLLApp theApp;


DWORD DefineAllSFR(void) {          // declare all special function registers
  BOOL ret = TRUE;

  ret &= Agsi.DefineSFR("ADCR", ADCR, AGSILONG, 0);  // If more SFR's are defined, do it in a table
  ret &= Agsi.DefineSFR("ADDR", ADDR, AGSILONG, 0);

  return(ret);
}

//------------------------------------------------------------------------------------------

struct vtrlist VTREG[] = {          // VTR's definition: keep this table consistent with defines in SCM3PeriDLL.h
  { "XTAL",   AGSIVTRLONG,  0x00A8C000, NULL },  // 11.0592MHz Oscillator Frequency
  { "CLOCK",  AGSIVTRLONG,  0x00A8C000, NULL },  // 11.0592MHz CPU Clock Frequency
  { "AIN0",   AGSIVTRFLOAT, 0x00000000, NULL },
  { "AIN1",   AGSIVTRFLOAT, 0x00000000, NULL },
  { "AIN2",   AGSIVTRFLOAT, 0x00000000, NULL },
  { "AIN3",   AGSIVTRFLOAT, 0x00000000, NULL },
  { "AIN4",   AGSIVTRFLOAT, 0x00000000, NULL },
  { "AIN5",   AGSIVTRFLOAT, 0x00000000, NULL },
  { "AIN6",   AGSIVTRFLOAT, 0x00000000, NULL },
  { "AIN7",   AGSIVTRFLOAT, 0x00000000, NULL },
  { "V3A",    AGSIVTRFLOAT, 0x40533333, NULL },  // 3.3 V
};

DWORD DefineAllVTREG(void) {        // declare all virtual registers
  BOOL ret = TRUE;
  int i;

  for (i = 0; i < (sizeof(VTREG) / sizeof (VTREG[0])); i++) {
    VTREG[i].hVTR = Agsi.DefineVTR(VTREG[i].pName, VTREG[i].Type, VTREG[i].Value);
    if (!VTREG[i].hVTR) ret = FALSE;
  }

  return(ret);
}

//------------------------------------------------------------------------------------------

AGSIINTERRUPT Interrupt = {         // Table of all Interrupts
// idx  *mess            *name     rsrf    rmask
    16, "A/D Converter", "",       ADDR,   0x80000000
};


DWORD DefineAllInterrupts(void) {   // define all interrupts

  if (!Agsi.DeclareInterrupt(&Interrupt)) return(FALSE);

  return(TRUE);
}

//------------------------------------------------------------------------------------------

AGSITIMER Timer;

DWORD DefineAllWatches(void) {      // define all Watches
  BOOL ret = TRUE;

  ret &= Agsi.SetWatchOnSFR(ADCR, wr_adcr, AGSIWRITE);
  ret &= Agsi.SetWatchOnSFR(ADDR, rd_addr, AGSIREAD);

  Timer = Agsi.CreateTimer(AdcDone);
  if (!Timer) return(FALSE);

  return(ret);
}

//------------------------------------------------------------------------------------------

DWORD DefineAllMenuEntries(void) {  // declare all peripheral-menu entries and dialogs

  if (!Agsi.DefineMenuItem(&PeriMenu)) return(FALSE);

  return(TRUE);
}

//------------------------------------------------------------------------------------------

DWORD ResetPeripheral(void) {       // reset all SFR's of this peripheral
  BOOL ret = TRUE;
  
  ret &= Agsi.WriteSFR(ADCR, 0x00000001, 0xFFFFFFFF);
  ret &= Agsi.WriteSFR(ADDR, 0x00000000, 0xFFFFFFFF);

  return(ret);
}

//------------------------------------------------------------------------------------------
// This function is directly called from uVision to initialize the DLL and to define all SFR's ...

extern "C" DWORD AGSIEXPORT AgsiEntry (DWORD nCode, void *vp) {
  DWORD CpuType;

  switch (nCode) {
    case AGSI_CHECK:
      CpuType = *((DWORD *)vp);
      if (CpuType == 7) return(1);     // This driver supports the ARM7 family of microcontrollers 
      else              return(0);     // Other microcontrollers are not supported by the driver
      break;

    case AGSI_INIT:                    // Declare all SFR's, VTREG's, Watches and Interrupts here
      AgsiConfig = *((AGSICONFIG *)vp);
//    AgsiConfig.m_hInstance;          // this pointer is used to get the function addresses of uVision
//    AgsiConfig.m_pszProjectPath;     // Path to application e.g. C:\KEIL\C51\EXAMPLES\HELLO
//    AgsiConfig.m_pszDevice;          // Simulated Device e.g. 52. This string is extracted out of the -p option.
//    AgsiConfig.m_pszConfiguration;   // complete dialog DLL options e.g. -p52 -dmydll ...
//    AgsiConfig.m_pszAppFile;         // name of loaded OMF file including path e.g. C:\KEIL\C51\EXAMPLES\HELLO\HELLO

      if (!GetFunctionPointers()) return(FALSE);   // get all function pointers for Agsi calls
      if (!DefineAllSFR()) return(FALSE);          // define all special function registers
      if (!DefineAllVTREG()) return(FALSE);        // define all virtual registers
      if (!DefineAllInterrupts()) return(FALSE);   // define all interrupts
      if (!DefineAllWatches()) return(FALSE);      // define all watches
      if (!DefineAllMenuEntries()) return(FALSE);  // define all peripheral-menu entries and dialogs
      break;

    case AGSI_TERMINATE:               // Free all allocated memory, close all files ...
      break;

    case AGSI_RESET:                   // Reset all SFR's of this peripheral
      if (!ResetPeripheral()) return(FALSE);
    break;

    case AGSI_PREPLL:                  // Recalculate all peripherals before clock prescaler/PLL is set to a new value
      break;

    case AGSI_POSTPLL:                 // Recalculate all peripherals after clock prescaler/PLL is set to a new value
      break;
  }
  return(TRUE);       // return OK
}

//------------------------------------------------------------------------------------------
// Simulation of A/D Converter for LPC22xx

static DWORD adcdisable = 0;
static DWORD adcr,  addr;
static DWORD adcrp, addrp;
static DWORD adval, adch;

void wr_adcr (void) {

  if (adcdisable) return;
  adcdisable = 1;

  Agsi.ReadSFR(ADCR, &adcr, &adcrp, 0xFFFFFFFF);

  if ((adcr & 0xFF) == 0) adcr |= 0x01;

  if (adcr & 0x00200000) {
    // PDN = 1: A/D Operational
    switch (adcr & 0x07010000) {
      case 0x01000000:  // Software Start
      case 0x00010000:  // Burst
        adch = 0;
        AdcConv();
        break;
    }
  } else {
    // PDN = 0: A/D in Power Down
    Agsi.SetTimer(Timer, 0xFFFFFFFF);
  }

  adcdisable = 0;
}

void rd_addr (void) {
  DWORD dr;

  if (!Agsi.IsSimulatorAccess()) return;
  if (adcdisable) return;
  adcdisable = 1;
  Agsi.ReadSFR(ADDR, &addr, &addrp, 0xFFFFFFFF);
  dr = addr;
  addr &= ~0xC0000000;              // Clear DONE and OVERUN Bits
  Agsi.WriteSFR(ADDR, addr, 0xFFFFFFFF);
  Agsi.SetSFRReadValue(dr);
  adcdisable = 0;
}

void AdcConv (void) {
  union fv  ain,  v3a;
  DWORD     bits;

  // Select Channel
  while ((adcr & (1 << adch)) == 0) {
    adch = (adch + 1) & 0x07;
  }

  // Read Analog Inputs
  Agsi.ReadVTR(VTREG[2+adch].hVTR, &ain.DW);
  Agsi.ReadVTR(V3A,                &v3a.DW);

  // Calculate A/D Value
  if (ain.f < 0.0f) {
    adval = 0;
  } else {
    if (v3a.f == 0.0f) {
      adval = 0x03FF;
    } else {
      adval = (DWORD)(1024.0f * (ain.f / v3a.f));
      if (adval > 0x03FF) adval = 0x03FF;
    }
  }

  // Bit(Clock) Value (only for Burst Mode)
  if (adcr & 0x00010000) {
    bits = 10 - ((adcr >> 17) & 0x07);
    adval &= 0x03FF << (10 - bits);
  } else {
    bits = 10;
  }

  // Time Watch for Conversion End
  Agsi.SetTimer(Timer, ((bits + 1) * (((adcr >> 8) & 0xFF) + 1)));
}

void AdcDone (void) {

  adcdisable = 1;

  Agsi.SetTimer(Timer, 0xFFFFFFFF); // Delete Time Watch

  Agsi.ReadSFR(ADCR, &adcr, &adcrp, 0xFFFFFFFF);
  Agsi.ReadSFR(ADDR, &addr, &addrp, 0xFFFFFFFF);

  addr &= ~0x0700FFC0;
  addr |=  adval <<  6;             // A/D Conversion Result
  addr |=  adch  << 24;             // A/D Channel
  if (addr & 0x80000000) {
    addr |= 0xC0000000;             // Set DONE and OVERUN Bit
  } else {
    addr |= 0x80000000;             // Set DONE Bit
  }

  Agsi.WriteSFR(ADDR, addr, 0xFFFFFFFF);

  if (adcr & 0x00010000) {          // Burst Mode
    adch = (adch + 1) & 0x07;       // Next Channel
    AdcConv();                      // Start Next Conversion
  }

  adcdisable = 0; 
}

