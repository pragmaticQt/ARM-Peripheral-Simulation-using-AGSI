#ifndef __COMMON_H__
#define __COMMON_H__


// Callback functions that are ONLY allowed to call during the initialisation process
typedef AGSIEXPORT BOOL      (*tAgsiDefineSFR) (const char* pszSfrName, AGSIADDR dwAddress, AGSITYPE eType, BYTE bBitPos);
typedef AGSIEXPORT AGSIVTR   (*tAgsiDefineVTR) (const char* pszVtrName, AGSITYPE eType, DWORD dwValue);
typedef AGSIEXPORT BOOL      (*tAgsiDeclareInterrupt)(AGSIINTERRUPT *pInterrupt);
typedef AGSIEXPORT BOOL      (*tAgsiSetWatchOnSFR) (AGSIADDR SFRAddress, AGSICALLBACK pfnReadWrite, AGSIACCESS eAccess);
typedef AGSIEXPORT BOOL      (*tAgsiSetWatchOnVTR) (AGSIVTR hVTR, AGSICALLBACK pfnReadWrite, AGSIACCESS eAccess);
typedef AGSIEXPORT BOOL      (*tAgsiSetWatchOnMemory) (AGSIADDR StartAddress, AGSIADDR EndAddress, AGSICALLBACK pfnReadWrite, AGSIACCESS eAccess);
typedef AGSIEXPORT AGSITIMER (*tAgsiCreateTimer) (AGSICALLBACK pfnTimer);
typedef AGSIEXPORT BOOL      (*tAgsiDefineMenuItem)(AGSIMENU *pDym);

// Callback functions that are NOT allowed to call during the initialisation process
typedef AGSIEXPORT BOOL      (*tAgsiWriteSFR) (AGSIADDR SFRAddress, DWORD dwValue, DWORD dwMask);
typedef AGSIEXPORT BOOL      (*tAgsiReadSFR)  (AGSIADDR SFRAddress, DWORD* pdwCurrentValue, DWORD* pdwPreviousValue, DWORD dwMask);
typedef AGSIEXPORT BOOL      (*tAgsiWriteVTR) (AGSIVTR hVTR, DWORD dwValue);
typedef AGSIEXPORT BOOL      (*tAgsiReadVTR) (AGSIVTR hVTR, DWORD* pdwCurrentValue);
typedef AGSIEXPORT BOOL      (*tAgsiSetSFRReadValue)(DWORD dwValue);
typedef AGSIEXPORT BOOL      (*tAgsiReadMemory) (AGSIADDR Address, DWORD dwCount, BYTE* pbValue);
typedef AGSIEXPORT BOOL      (*tAgsiWriteMemory)(AGSIADDR Address, DWORD dwCount, BYTE* pbValue);
typedef AGSIEXPORT AGSIADDR  (*tAgsiGetLastMemoryAddress)(void);
typedef AGSIEXPORT BOOL      (*tAgsiIsSimulatorAccess)(void);
typedef AGSIEXPORT BOOL      (*tAgsiSetTimer)(AGSITIMER hTimer, DWORD dwClock);
typedef AGSIEXPORT UINT64    (*tAgsiGetStates)(void);
typedef AGSIEXPORT AGSIADDR  (*tAgsiGetProgramCounter)(void);
typedef AGSIEXPORT DWORD     (*tAgsiIsInInterrupt)(void);
typedef AGSIEXPORT BOOL      (*tAgsiIsSleeping)(void);
typedef AGSIEXPORT void      (*tAgsiStopSimulator)(void);
typedef AGSIEXPORT void      (*tAgsiTriggerReset)(void);
typedef AGSIEXPORT void      (*tAgsiUpdateWindows)(void);
typedef AGSIEXPORT void      (*tAgsiHandleFocus) (HWND hwndDialog);
typedef AGSIEXPORT DWORD     (*tAgsiGetExternalClockRate)(void);
typedef AGSIEXPORT DWORD     (*tAgsiGetInternalClockRate)(void);
typedef AGSIEXPORT double    (*tAgsiGetClockFactor)(void);
typedef AGSIEXPORT void      (*tAgsiMessage)(const char* pszFormat, ...);
typedef AGSIEXPORT const char*(*tAgsiGetTargetKey)(const char* pszKey);
typedef AGSIEXPORT BOOL      (*tAgsiSetTargetKey)(const char* pszKey, const char *pszString);
typedef AGSIEXPORT DWORD     (*tAgsiGetSymbolByName) (AGSISYMDSC *vp);
typedef AGSIEXPORT DWORD     (*tAgsiGetSymbolByValue)(AGSISYMDSC *vp);

struct AGSIFUNCS {
  tAgsiDefineSFR             DefineSFR;
  tAgsiDefineVTR             DefineVTR;
  tAgsiSetWatchOnSFR         SetWatchOnSFR;
  tAgsiSetWatchOnVTR         SetWatchOnVTR;
  tAgsiSetWatchOnMemory      SetWatchOnMemory;
  tAgsiCreateTimer           CreateTimer;
  tAgsiDefineMenuItem        DefineMenuItem;
  tAgsiWriteSFR              WriteSFR;
  tAgsiReadSFR               ReadSFR;
  tAgsiWriteVTR              WriteVTR;
  tAgsiReadVTR               ReadVTR;
  tAgsiSetSFRReadValue       SetSFRReadValue;
  tAgsiReadMemory            ReadMemory;
  tAgsiWriteMemory           WriteMemory;
  tAgsiGetLastMemoryAddress  GetLastMemoryAddress;
  tAgsiIsSimulatorAccess     IsSimulatorAccess;
  tAgsiSetTimer              SetTimer;
  tAgsiGetStates             GetStates;
  tAgsiGetProgramCounter     GetProgramCounter;
  tAgsiDeclareInterrupt      DeclareInterrupt;
  tAgsiIsInInterrupt         IsInInterrupt;
  tAgsiIsSleeping            IsSleeping;
  tAgsiStopSimulator         StopSimulator;
  tAgsiTriggerReset          TriggerReset;
  tAgsiUpdateWindows         UpdateWindows;
  tAgsiHandleFocus           HandleFocus;
  tAgsiGetExternalClockRate  GetExternalClockRate;
  tAgsiGetInternalClockRate  GetInternalClockRate;
  tAgsiGetClockFactor        GetClockFactor;
  tAgsiMessage               Message;
  tAgsiGetTargetKey          GetTargetKey;
  tAgsiSetTargetKey          SetTargetKey;
  tAgsiGetSymbolByName       GetSymbolByName;
  tAgsiGetSymbolByValue      GetSymbolByValue;
};

extern struct AGSIFUNCS  Agsi;
extern AGSICONFIG  AgsiConfig;

extern AGSIMENU    PeriMenu;  // Peripheral Dialog


union fv {      // float value union
  float f;
  DWORD DW;
};

struct vtrlist {
  char     *pName;       // name of VTREG
  AGSITYPE Type;         // type of VTREG
  DWORD    Value;        // value of VTREG
  AGSIVTR  hVTR;         // handle of VTREG
};


extern DWORD GetFunctionPointers (void);    // get all function pointers

extern void  StringHex        (CWnd *pCWnd, DWORD val, int places);
extern void  StringDec        (CWnd *pCWnd, DWORD val);
extern void  StringFloat      (CWnd *pCWnd, float val, int precision);
extern BOOL  GetDlgHex        (CWnd *pCWnd, DWORD oldval, DWORD *newval, DWORD max, int places);
extern float GetDlgFloat      (CWnd *pCWnd, float oldval, float  min,    float max, int precision);
extern void  HandleHexInput   (CWnd *pCWnd, AGSIADDR sfr, DWORD max = 0xFFFFFFFF, int places = 8);
extern void  HandleSelInput   (CWnd *pCWnd, AGSIADDR sfr, DWORD mask, DWORD pos);
extern void  HandleFloatInput (CWnd *pCWnd, AGSIVTR  vtr, float min = 0.0f, float max = 5.0f, int precision = 4);
extern void  WriteBit         (AGSIADDR sfr, DWORD mask, DWORD set);
extern void  WriteBitVTR      (AGSIVTR  vtr, DWORD mask, DWORD set);


#endif  // __COMMON_H__


