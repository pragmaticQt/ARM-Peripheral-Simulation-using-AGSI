
// This module contains functions that are needed for almost every AGSI DLL

#include "stdafx.h"
#include "AGSI.h"
#include "Common.h"


AGSICONFIG  AgsiConfig;
struct AGSIFUNCS  Agsi;

DWORD GetFunctionPointers(void) {           // get all function pointers

  Agsi.DefineSFR            = (tAgsiDefineSFR)             GetProcAddress(AgsiConfig.m_hInstance, "AgsiDefineSFR");
  Agsi.DefineVTR            = (tAgsiDefineVTR)             GetProcAddress(AgsiConfig.m_hInstance, "AgsiDefineVTR");
  Agsi.DeclareInterrupt     = (tAgsiDeclareInterrupt)      GetProcAddress(AgsiConfig.m_hInstance, "AgsiDeclareInterrupt");
  Agsi.SetWatchOnVTR        = (tAgsiSetWatchOnVTR)         GetProcAddress(AgsiConfig.m_hInstance, "AgsiSetWatchOnVTR");
  Agsi.SetWatchOnSFR        = (tAgsiSetWatchOnSFR)         GetProcAddress(AgsiConfig.m_hInstance, "AgsiSetWatchOnSFR");
  Agsi.SetWatchOnMemory     = (tAgsiSetWatchOnMemory)      GetProcAddress(AgsiConfig.m_hInstance, "AgsiSetWatchOnMemory");
  Agsi.CreateTimer          = (tAgsiCreateTimer)           GetProcAddress(AgsiConfig.m_hInstance, "AgsiCreateTimer");
  Agsi.DefineMenuItem       = (tAgsiDefineMenuItem)        GetProcAddress(AgsiConfig.m_hInstance, "AgsiDefineMenuItem");
  Agsi.WriteSFR             = (tAgsiWriteSFR)              GetProcAddress(AgsiConfig.m_hInstance, "AgsiWriteSFR");
  Agsi.ReadSFR              = (tAgsiReadSFR)               GetProcAddress(AgsiConfig.m_hInstance, "AgsiReadSFR");
  Agsi.WriteVTR             = (tAgsiWriteVTR)              GetProcAddress(AgsiConfig.m_hInstance, "AgsiWriteVTR");
  Agsi.ReadVTR              = (tAgsiReadVTR)               GetProcAddress(AgsiConfig.m_hInstance, "AgsiReadVTR");
  Agsi.SetSFRReadValue      = (tAgsiSetSFRReadValue)       GetProcAddress(AgsiConfig.m_hInstance, "AgsiSetSFRReadValue");
  Agsi.ReadMemory           = (tAgsiReadMemory)            GetProcAddress(AgsiConfig.m_hInstance, "AgsiReadMemory");
  Agsi.WriteMemory          = (tAgsiWriteMemory)           GetProcAddress(AgsiConfig.m_hInstance, "AgsiWriteMemory");
  Agsi.GetLastMemoryAddress = (tAgsiGetLastMemoryAddress)  GetProcAddress(AgsiConfig.m_hInstance, "AgsiGetLastMemoryAddress");
  Agsi.IsSimulatorAccess    = (tAgsiIsSimulatorAccess)     GetProcAddress(AgsiConfig.m_hInstance, "AgsiIsSimulatorAccess");
  Agsi.SetTimer             = (tAgsiSetTimer)              GetProcAddress(AgsiConfig.m_hInstance, "AgsiSetTimer");
  Agsi.GetStates            = (tAgsiGetStates)             GetProcAddress(AgsiConfig.m_hInstance, "AgsiGetStates");
  Agsi.GetProgramCounter    = (tAgsiGetProgramCounter)     GetProcAddress(AgsiConfig.m_hInstance, "AgsiGetProgramCounter");
  Agsi.IsInInterrupt        = (tAgsiIsInInterrupt)         GetProcAddress(AgsiConfig.m_hInstance, "AgsiIsInInterrupt");
  Agsi.IsSleeping           = (tAgsiIsSleeping)            GetProcAddress(AgsiConfig.m_hInstance, "AgsiIsSleeping");
  Agsi.StopSimulator        = (tAgsiStopSimulator)         GetProcAddress(AgsiConfig.m_hInstance, "AgsiStopSimulator");
  Agsi.TriggerReset         = (tAgsiTriggerReset)          GetProcAddress(AgsiConfig.m_hInstance, "AgsiTriggerReset");
  Agsi.UpdateWindows        = (tAgsiUpdateWindows)         GetProcAddress(AgsiConfig.m_hInstance, "AgsiUpdateWindows");
  Agsi.HandleFocus          = (tAgsiHandleFocus)           GetProcAddress(AgsiConfig.m_hInstance, "AgsiHandleFocus");
  Agsi.GetExternalClockRate = (tAgsiGetExternalClockRate)  GetProcAddress(AgsiConfig.m_hInstance, "AgsiGetExternalClockRate");
  Agsi.GetInternalClockRate = (tAgsiGetInternalClockRate)  GetProcAddress(AgsiConfig.m_hInstance, "AgsiGetInternalClockRate");
  Agsi.GetClockFactor       = (tAgsiGetClockFactor)        GetProcAddress(AgsiConfig.m_hInstance, "AgsiGetClockFactor");
  Agsi.Message              = (tAgsiMessage)               GetProcAddress(AgsiConfig.m_hInstance, "AgsiMessage");
  Agsi.SetTargetKey         = (tAgsiSetTargetKey)          GetProcAddress(AgsiConfig.m_hInstance, "AgsiSetTargetKey");
  Agsi.GetSymbolByName      = (tAgsiGetSymbolByName)       GetProcAddress(AgsiConfig.m_hInstance, "AgsiGetSymbolByName");
  Agsi.GetTargetKey         = (tAgsiGetTargetKey)          GetProcAddress(AgsiConfig.m_hInstance, "AgsiGetTargetKey");
  Agsi.GetSymbolByValue     = (tAgsiGetSymbolByValue)      GetProcAddress(AgsiConfig.m_hInstance, "AgsiGetSymbolByValue");
//  Agsi.GetClock             = (tAgsiGetClock)              GetProcAddress(AgsiConfig.m_hInstance, "AgsiGetClock");
//  Agsi.GetTime              = (tAgsiGetTime)               GetProcAddress(AgsiConfig.m_hInstance, "AgsiGetTime");

  if ((Agsi.DefineSFR            == NULL) ||
      (Agsi.DefineVTR            == NULL) ||
      (Agsi.DeclareInterrupt     == NULL) ||
      (Agsi.SetWatchOnSFR        == NULL) ||
      (Agsi.SetWatchOnVTR        == NULL) ||
      (Agsi.CreateTimer          == NULL) ||
      (Agsi.DefineMenuItem       == NULL) ||

      (Agsi.WriteSFR             == NULL) ||
      (Agsi.ReadSFR              == NULL) ||
      (Agsi.WriteVTR             == NULL) ||
      (Agsi.ReadVTR              == NULL) ||
      (Agsi.SetSFRReadValue      == NULL) ||
      (Agsi.ReadMemory           == NULL) ||
      (Agsi.WriteMemory          == NULL) ||
      (Agsi.GetLastMemoryAddress == NULL) ||
      (Agsi.IsSimulatorAccess    == NULL) ||
      (Agsi.SetTimer             == NULL) ||
      (Agsi.GetStates            == NULL) ||
      (Agsi.GetProgramCounter    == NULL) ||
      (Agsi.IsInInterrupt        == NULL) ||
      (Agsi.IsSleeping           == NULL) ||
      (Agsi.StopSimulator        == NULL) ||
      (Agsi.TriggerReset         == NULL) ||
      (Agsi.UpdateWindows        == NULL) ||
      (Agsi.HandleFocus          == NULL) ||
      (Agsi.GetExternalClockRate == NULL) ||
      (Agsi.GetInternalClockRate == NULL) ||
      (Agsi.GetClockFactor       == NULL) ||
      (Agsi.Message              == NULL) ||
      (Agsi.GetTargetKey         == NULL) ||
      (Agsi.SetTargetKey         == NULL) ||
      (Agsi.GetSymbolByName      == NULL) ||
      (Agsi.GetSymbolByValue     == NULL)) {

    return(FALSE);
  }

  return(1);
}


//********************************************************************************************
// The following functions help you to input and output strings and (float) numbers in dialogs
// Please review them before you try to write your own function


// Output Hex number to Text-Control of given Dialog
void StringHex (CWnd * pCWnd, DWORD val, int places)  {
  char locbuffer[20];

  sprintf (locbuffer, "0x%0*X", places, val & (0xFFFFFFFF >> 4*(8 - places)));
  pCWnd->SetWindowText (locbuffer);
}

// Output Dec number to Text-Control of given Dialog
void StringDec (CWnd * pCWnd, DWORD val)  {
  char locbuffer[20];

  sprintf (locbuffer, "%u", val);
  pCWnd->SetWindowText (locbuffer);
}

// Output Float number to Text-Control of given Dialog
void StringFloat (CWnd * pCWnd, float val, int precision)  {
  char locbuffer[20];

  sprintf (locbuffer, "%1.*f", precision, val);
  pCWnd->SetWindowText (locbuffer);
}


static const char INPUT_ERR_TITLE [] = "Invalid number";
static const char INPUT_ERRMSG[]     = "You have entered an invalid number!\n"
                                       "The previous value will be restored.\n"
                                       "Examples: 0x12\n";

static const char INPUT_OVR_TITLE [] = "Out of range";
static const char INPUT_OVRMSG[]     = "You have entered a number that is out of range!\n";

BOOL GetDlgHex (CWnd *pCWnd, DWORD oldval, DWORD *newval, DWORD max, int places) {
  DWORD val;
  WORD  n;
  char  lbuf[100];
  
  n = pCWnd->GetWindowText (lbuf, 100);
  lbuf[n] = '\0';  /* terminate string */
  n = sscanf(lbuf, "%x", &val);
  if (n != 1) {
    MessageBeep(MB_ICONEXCLAMATION);
    pCWnd->MessageBox(INPUT_ERRMSG, INPUT_ERR_TITLE, MB_OK|MB_ICONSTOP);
    StringHex(pCWnd, oldval, places);
    return(FALSE);
  }
  if (val > max) {
    MessageBeep(MB_ICONEXCLAMATION);
    pCWnd->MessageBox(INPUT_OVRMSG, INPUT_OVR_TITLE, MB_OK | MB_ICONSTOP); 
    StringHex(pCWnd, oldval, places);
    return(FALSE);
  }
  StringHex(pCWnd, val, places);
  *newval = val;
  return(TRUE);
}


static const char INPUT_F_ERR_TITLE [] = "Invalid float number";
static const char INPUT_F_ERRMSG[]     = "You have entered an invalid float number!\n"
                                         "The previous value will be restored.\n"
                                         "Example: 1.234\n";

float GetDlgFloat (CWnd * pCWnd, float oldval, float min, float max, int precision) {
  float val;
  WORD  n;
  char  lbuf[100];
  
  n = pCWnd->GetWindowText (lbuf, 100);
  lbuf[n] = '\0';  /* terminate string */
  n = sscanf(lbuf, "%f", &val);
  if (n != 1) {
    MessageBeep(MB_ICONEXCLAMATION);
    pCWnd->MessageBox(INPUT_F_ERRMSG, INPUT_F_ERR_TITLE, MB_OK | MB_ICONSTOP); 
    StringFloat(pCWnd, oldval, precision);
    return((float)-1.9876e-36);
  }
  if (val < min) {
    MessageBeep(MB_ICONEXCLAMATION);
    pCWnd->MessageBox(INPUT_OVRMSG, INPUT_OVR_TITLE, MB_OK | MB_ICONSTOP); 
    StringFloat(pCWnd, oldval, precision);
    return((float)-1.9876e-36);
  }
  if (val > max) {
    pCWnd->MessageBox(INPUT_OVRMSG, INPUT_OVR_TITLE, MB_OK | MB_ICONSTOP); 
    StringFloat(pCWnd, oldval, precision);
    return((float)-1.9876e-36);
  }
  StringFloat(pCWnd, val, precision);
  return(val);
}


// This function handles a hex input in a dialog
void HandleHexInput(CWnd * pCWnd, AGSIADDR sfr, DWORD max, int places) {
  DWORD oldval, oldvalp, newval;

  Agsi.ReadSFR(sfr, &oldval, &oldvalp, 0xFFFFFFFF);
  if (GetDlgHex (pCWnd, oldval, &newval, max, places)) {
    Agsi.WriteSFR(sfr, newval, 0xFFFFFFFF);
    Agsi.UpdateWindows();
  }
}

// This function handles a Combo Box selection input in a dialog
void HandleSelInput(CWnd * pCWnd, AGSIADDR sfr, DWORD mask, DWORD pos) {
  DWORD val, valp;
  int   i;

  i = ((CComboBox *)pCWnd)->GetCurSel();
  Agsi.ReadSFR(sfr, &val, &valp, ~mask);
  val |= i << pos;
  Agsi.WriteSFR(sfr, val, mask);
  Agsi.UpdateWindows();
}

// This function handles a float number input in a dialog
void HandleFloatInput(CWnd * pCWnd, AGSIVTR vtr, float min, float max, int precision) {
  union fv tmp;
  float result;

  Agsi.ReadVTR(vtr, &tmp.DW);
  result = GetDlgFloat (pCWnd, tmp.f, min, max, precision);
  if (result != -1.9876e-36) {
    tmp.f = result;
    Agsi.WriteVTR(vtr, tmp.DW);
    Agsi.UpdateWindows();
  }
}


// This function is intended to be called when a checkbox is clicked (SFR bit)
void WriteBit(AGSIADDR sfr, DWORD mask, DWORD set) {
  DWORD value;

  value = (set == 0) ? 0 : 0xFFFFFFFF;
  Agsi.WriteSFR(sfr, value, mask);
  Agsi.UpdateWindows();
}

// This function is intended to be called when a checkbox is clicked (VTR bit)
void WriteBitVTR(AGSIVTR vtr, DWORD mask, DWORD set) {
  DWORD value;  

  Agsi.ReadVTR(vtr, &value);
  if (set) {
    value |=  mask;
  } else {
    value &= ~mask;
  }
  Agsi.WriteVTR(vtr, value);
  Agsi.UpdateWindows();
}

