#ifndef __AGSI_H__
#define __AGSI_H__


#include <windows.h>


#define AGSIEXPORT __declspec( dllexport )
#define AGSIAPI    WINAPIV




#ifdef __cplusplus
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
//
// AGSI: Advanced Generic Simulator Interface (Simulation Interface Part)
//

// ACCESS REASON FOR MEMORY ACCESS CALLBACK FUNCTIONS
#ifndef __AGSICB_REASON
  #define __AGSICB_REASON

  typedef enum {
    CB_VOID     = 0,      // no access
    CB_READ     = 0x02,   // adr = memory address
    CB_WRITE    = 0x04,   // adr = memory address
    CB_VT_READ  = 0x12,   // adr = VTR ** = AGSIVTR
    CB_VT_WRITE = 0x14,   // adr = VTR ** = AGSIVTR
  } AGSICB_REASON;  
#endif

#ifndef PSIAPI
typedef enum CALLERID {				// BGN 09.09.2003 added for Rom Monitor
	Simulator, RomMonitor, EmulatorKSC, EmulatorHitex
}	CALLERID;

typedef enum RMWID {					// BGN 10.09.2003 added for Rom Monitor
	RMW_ANL,RMW_ORL,RMW_XRL,RMW_CPL,RMW_INC,RMW_DEC,RMW_MOV,RMW_CLR,RMW_SETB
} RMWID;
#endif // PSIAPI

typedef DWORD AGSIVTR;
typedef DWORD AGSIADDR;
typedef DWORD AGSITIMER;
typedef void (* AGSICALLBACK) (void);                         // Timer
typedef void (* AGSICALLBACKA)(DWORD adr, AGSICB_REASON r);   // memory Access

typedef struct {
  HINSTANCE     m_hInstance;
  const char*   m_pszProjectPath;
  const char*   m_pszDevice;
  const char*   m_pszConfiguration;
  const char*   m_pszAppFile;
  HWND          m_hwnd;
  CALLERID      m_callerId;	// BGN 29.04.2004 for RomMonitor and Emulators
} AGSICONFIG;

typedef struct {         // access to internal structures
  DWORD           Size;  // Size of AGSIEXTINFO in bytes
  struct dbgblk * pdbg;
  struct bom    * bom;
} AGSIEXTINFO;

typedef enum {
  AGSIBYTE = 1,
  AGSIWORD = 2,
  AGSILONG = 4,
  AGSIBIT  = 5,
  AGSIVTRCHAR = 10,
  AGSIVTRWORD = 11,
  AGSIVTRLONG = 12,
  AGSIVTRFLOAT = 13
} AGSITYPE;

typedef enum {
  AGSIREAD,
  AGSIWRITE,
  AGSIREADWRITE,
} AGSIACCESS;

// function code numbers for AgsiEntry function
typedef enum {
  AGSI_CHECK       = 0,
  AGSI_INIT        = 1,
  AGSI_TERMINATE   = 2,
  AGSI_RESET       = 3,
  AGSI_PREPLL      = 4,
  AGSI_POSTPLL     = 5,
  AGSI_PRERESET    = 6,    // before CPU RESET                   24.6.2003
  AGSI_CMDOUT      = 7,    // Command output of 'exec' commands  24.6.2003
  AGSI_ENTERSLEEP  = 8,    // HS 08.03.2004 currently only used for smartcards
  AGSI_EXITSLEEP   = 9,    // HS 08.03.2004 currently only used for smartcards
  AGSI_ONINTERRUPT = 10,   // HS 08.03.2004 currently only used for smartcards
  AGSI_ONRETI      = 11,   // HS 08.03.2004 currently only used for smartcards
} AGSIFUNC;

typedef struct {
#if defined (__ARMCM3__)    // for ARM Cortex-M3
   WORD            idx;     // Interrupt Index
   char          *mess;     // Interrupt Message
   char          *name;     // Interrupt Name
   DWORD          rsfr;     // Interrupt Request Register
   DWORD         rmask;     // Interrupt Request Bit Mask
#elif defined (__ARMSSC__)    // for Samsung SC ARM
   WORD           num;      // Interrupt Number
   char          *mess;     // Interrupt Message
   char          *name;     // Interrupt Name
   DWORD          bmsk;     // Interrupt Registers Bit Mask
#elif defined (__ARMAT__)   // for Atmel ARM
   WORD            idx;     // Interrupt Index
   char          *mess;     // Interrupt Message
   char          *name;     // Interrupt Name
   DWORD          rsfr;     // Interrupt Request Register
   DWORD          esfr;     // Interrupt Enable Register
   WORD         extint;     // External Interrupt
#elif defined (__ARMP__)    // for Philips ARM
   WORD           chan;     // Interrupt Channel
   char          *mess;     // Interrupt Message
   char          *name;     // Interrupt Name
   DWORD          rsfr;     // Interrupt Request Register
   DWORD         rmask;     // Interrupt Request Bit Mask
   DWORD          esfr;     // Interrupt Enable Register
   DWORD         emask;     // Interrupt Enable Bit Mask
#elif defined (__ARMAD__)   // for Analog Devices ARM
   WORD            idx;     // Interrupt Index
   char          *mess;     // Interrupt Message
   char          *name;     // Interrupt Name
   DWORD          rsfr;     // Interrupt Request Register
   DWORD         rmask;     // Interrupt Request Bit Mask
#elif defined (__C166__)
   AGSIADDR        vec;
   char          *mess;     // interrupt name
   AGSIADDR        sfr;     // interrupt control sfr 
#elif defined (__SLE66__)   // for Infineon SLE66
   AGSIADDR        vec;
   char          *mess;     // Interrupt name
   const char   *rname;     // name of interrupt request bit
   const char   *ename;     // name of interrupt enable bit
   const char   *pname;     // name of interrupt priority bit
   DWORD           num;     // Interrupt Number
   DWORD           pwl;     // priority within level
#else                       // other targets (x51 based)
   AGSIADDR        vec;
   char          *mess;     // interrupt name
   AGSIADDR       msfr;     // interrupt mode sfr 
   WORD          mmask;     // interrupt mode bit mask
   const char   *mname;     // name of interrupt mode bit
   AGSIADDR       rsfr;     // interrupt request sfr 
   WORD          rmask;     // interrupt request bit mask
   const char   *rname;     // name of interrupt request bit
   AGSIADDR       esfr;     // interrupt enable sfr
   WORD          emask;     // interrupt enable bit mask
   const char   *ename;     // name of interrupt enable bit
   AGSIADDR      p0sfr;     // interrupt priority 0 sfr
   WORD         p0mask;     // interrupt priority 0 bit mask
   const char   *pname;     // name of interrupt priority bit
   AGSIADDR      p1sfr;     // interrupt priority 1 sfr
   WORD         p1mask;     // interrupt priority 1 bit mask
   WORD            pwl;     // priority within level
   WORD     auto_reset;     // reset interrupt request flag on interrupt entry
#endif
} AGSIINTERRUPT;


/*
 * Symbol search masks (may be combined using |) :
 */

typedef enum {
  AGSI_SYM_VAR = 0x0001,         // search for non-bit Variables
  AGSI_SYM_CON = 0x0002,         // search for named Constants
  AGSI_SYM_BIT = 0x0004,         // search for Bit in Memory
  AGSI_SYM_LOC = 0x0008,         // search for Function/Label
  AGSI_SYM_SFR = 0x0200          // search for SFR name
} AGSISYMMASK;

/*
 * Type of found symbol:
 */

typedef enum {
  AGSI_TP_VOID   = 0,
  AGSI_TP_BIT    = 1,
  AGSI_TP_CHAR   = 2,
  AGSI_TP_UCHAR  = 3,
  AGSI_TP_INT    = 4,
  AGSI_TP_UINT   = 5,
  AGSI_TP_SHORT  = 6,
  AGSI_TP_USHORT = 7,
  AGSI_TP_LONG   = 8,
  AGSI_TP_ULONG  = 9,
  AGSI_TP_FLOAT  = 10,
  AGSI_TP_DOUBLE = 11,
  AGSI_TP_PTR    = 12,
  AGSI_TP_UNION  = 13,
  AGSI_TP_STRUCT = 14,
  AGSI_TP_FUNC   = 15,
  AGSI_TP_STRING = 16,
  AGSI_TP_ENUM   = 17,
  AGSI_TP_FIELD  = 18,

//---HP. added  /28.7.2005/
  AGSI_TP_INT64  = 19,
  AGSI_TP_UINT64 = 20,
  AGSI_TP_ARRAY  = 30
//---

} AGSISYMTYPE;

/*
 * Type of lock
 */

typedef enum {
	AGSI_LK_INFO   = 0,
	AGSI_LK_LOCK   = 1,
	AGSI_LK_UNLOCK = -1
} AGSILOCK;

typedef struct  {                  // Search for Sym by Name or Value.
  AGSISYMMASK nMask;               // search mask (AG_SYM_LOC | ...)
  char szName [256];               // search/found name (zero-terminated
  UINT64        val;               // search/found Adr/Value
  AGSISYMTYPE  type;               // type of found symbol (AGSI_TP_???)
  DWORD          Ok;               // 1:=Ok, else find failed.
} AGSISYMDSC;

typedef enum {
  AGSI_GETACTSFRSEL = 1,
  AGSI_ACEREAD      = 2,
  AGSI_RFREAD       = 3,
  AGSI_RFWRITE      = 4,
  AGSI_BONVMREAD    = 5,
  AGSI_BONVMPROG    = 6
} AGSISPFUNC;

/*
 * Dynamic Menu construction and maintanance
 */

//#pragma pack(1)

#define AGSIDLGD struct AgsiDlgDat
struct AgsiDlgDat {                      // every dialog has it's own structure
  DWORD             iOpen;               // auto reopen dialog (pos := 'rc')
  HWND                 hw;               // Hwnd of Dialog
  BOOL (CALLBACK *wp) (HWND hw, UINT msg, WPARAM wp, LPARAM lp);
  RECT                 rc;               // Position rectangle
  void   (*Update) (void);               // Update dialog content
  void (*Kill) (AGSIDLGD *pM);           // Kill dialog
  void                *vp;               // reserved for C++ Dialogs (Dlg *this)
};

#define AGSIMENU struct AgsiDynaM
struct AgsiDynaM  {                      // Menu item data structure
  int              nDelim;               // Menu template delimiter
  char            *szText;               // Menu item text
  void    (*fp) (AGSIMENU *pM);          // create/bringDlgtoTop function
  DWORD               nID;               // uv3 assigned ID_xxxx
  DWORD            nDlgId;               // Dialog ID
  AGSIDLGD          *pDlg;               // link to dialog attributes
};
//#pragma pack()

// extensions for Philips MX SmartCards
#define AGSIHOOK_PC        0x01
#define AGSIHOOK_PREEXEC   0x02
#define AGSIHOOK_POSTEXEC  0x04
#define AGSIHOOK_DELETE    0x10

typedef struct tagAGSIHOOKCONTEXT
{
	BYTE		bEvent;
	AGSIADDR	Pc;
	AGSIADDR	Ypc;
	UINT64		Advance;
} AGSIHOOKCONTEXT;

typedef void ( *AGSIHOOKFUNC )(AGSIHOOKCONTEXT *);

typedef struct sAGSIPERIPARA {
  DWORD  size;               // sizeof this structure
  DWORD  FamexRamSize;       // Famex Ramsize specified with -f parameter
  DWORD  UnusedParameter[9]; // reduce this number when new parameters are added so that the size of this structure remains the same
} AGSIPERIPARA;
 
typedef BOOL (* REGISTERADRBREAK) (BYTE bEvent, DWORD adr, AGSIHOOKFUNC pFunc);


/*
 * nDelim:  1 := normal Menu entry
 *          2 := Popup-Entry (nested submenu)
 *         -2 := end of Popup-Group-List
 *         -1 := total end of Menu-List
 *  text:   the name for the menu/popup-menu entry
 *    fp:   Function to be activated on menu-selection
 */


/* Revised AGSI functions from Hans 10/07/07 */
BOOL AGSIAPI AgsiDefineSFR(const char* pszSfrName, AGSIADDR dwAddress, AGSITYPE eType, BYTE bBitPos); 
AGSIVTR AGSIAPI AgsiDefineVTR(const char* pszVtrName, AGSITYPE eType, DWORD dwValue);
BOOL AGSIAPI AgsiSetWatchOnSFR(AGSIADDR SFRAddress, AGSICALLBACKA pfnReadWrite, AGSIACCESS eAccess); 
BOOL AGSIAPI AgsiSetWatchOnVTR(AGSIVTR hVTR, AGSICALLBACKA pfnReadWrite, AGSIACCESS eAccess); 
BOOL AGSIAPI AgsiWriteSFR(AGSIADDR SFRAddress, DWORD dwValue, DWORD dwMask); 
BOOL AGSIAPI AgsiReadSFR(AGSIADDR SFRAddress, DWORD* pdwCurrentValue, DWORD* pdwPreviousValue, DWORD dwMask); 
BOOL AGSIAPI AgsiWriteVTR(AGSIVTR hVTR, DWORD dwValue);
BOOL AGSIAPI AgsiReadVTR(AGSIVTR hVTR, DWORD* pdwCurrentValue); 
BOOL AGSIAPI AgsiSetSFRReadValue(DWORD dwValue); 
BOOL AGSIAPI AgsiIsSimulatorAccess(void);
AGSITIMER AGSIAPI AgsiCreateTimer(AGSICALLBACK pfnTimer); 
BOOL AGSIAPI AgsiSetTimer(AGSITIMER hTimer, DWORD dwClock);
UINT64 AGSIAPI AgsiGetClock(void); // AgsiGetStates should be used for future development!!! This function still exits for compatibility reasons.
UINT64 AGSIAPI AgsiGetStates(void);
double AGSIAPI AgsiGetTime(void);  // HS 18.06.2007 function added (copied from DP51) 
double AGSIAPI AgsiGetClockFactor(void); 
DWORD AGSIAPI AgsiGetExternalClockRate(void); 
DWORD AGSIAPI AgsiGetInternalClockRate(void); 
AGSIADDR AGSIAPI AgsiGetProgramCounter(void); 
BOOL AGSIAPI AgsiDeclareInterrupt(AGSIINTERRUPT * itab); 
BOOL AGSIAPI AgsiIsSleeping(void); 
DWORD AGSIAPI AgsiIsInInterrupt(void); 
void AGSIAPI AgsiStopSimulator(); 
void AGSIAPI AgsiTriggerReset(void); 
void AGSIAPI AgsiUpdateWindows(void); 
BOOL AGSIAPI AgsiSetWatchOnMemory(AGSIADDR dwStartAddress, AGSIADDR dwEndAddress, AGSICALLBACKA pfnReadWrite, AGSIACCESS eAccess); 
BOOL AGSIAPI AgsiReadMemory(AGSIADDR dwAddress, DWORD dwCount, BYTE* pbValue); 
BOOL AGSIAPI AgsiWriteMemory(AGSIADDR dwAddress, DWORD dwCount, BYTE* pbValue); 
DWORD AGSIAPI AgsiGetLastMemoryAddress(void) ;
const char * AGSIAPI AgsiGetTargetKey(const char* pszKey); 
BOOL AGSIAPI AgsiSetTargetKey(const char* pszKey, const char *pszString); 
DWORD AGSIAPI AgsiGetSymbolByName (AGSISYMDSC *vp); 
DWORD AGSIAPI AgsiGetSymbolByValue (AGSISYMDSC *vp); 
void AGSIAPI AgsiMessage(const char* pszFormat, ...); 
void AGSIAPI AgsiExecuteCommand(const char* pszCommand); 
BOOL AGSIAPI AgsiDefineMenuItem(AGSIMENU *pDym); 
void AGSIAPI AgsiHandleFocus (HWND hwndDialog);

#ifdef __cplusplus
}
#endif


#endif // __AGSI_H__


