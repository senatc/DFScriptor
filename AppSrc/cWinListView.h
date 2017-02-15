//************************************************************************
// cWinListView.pkg   LISTVIEW Package
//
// Copyright (c) 1999-2001 Out of the Box Consulting, Inc.
// All rights reserved.
//
//***************************************************************************
//  Description:
//      A DataFlex class to support the Windows' ListView class.
//      This class supports nearly all of the features available in the 
//      windows cListCtrl class.  Most of the missing features are not
//      available because they cannot properly be supported from VDF.
//
//      NOTE: This class is provided without documentation, beyond what is
//            documented in this source.
//
//  Author: Oliver T. Nelson
//***************************************************************************

//Use cWindowsEx.h
//Use cWinControls.pkg

#IFNDEF Get_InitCommonControlsEx
External_function InitCommonControlsEx "InitCommonControlsEx" COMCTL32.DLL Pointer lpInitCtrls Returns Integer
#ENDIF
Type tINITCOMMONCONTROLSEX
    Field tINITCOMMONCONTROLSEX.dwSize as DWord
    Field tINITCOMMONCONTROLSEX.dwICC  as DWord
End_Type

Define LVM_FIRST               For |CI$1000      // ListView messages
Define LVN_FIRST               For (-100)        // listview

Define NM_FIRST                For 0
Define NM_SETFOCUS             For (NM_FIRST - 7)
Define NM_KILLFOCUS            For (NM_FIRST - 8)

Define MAXUINT For $FFFFFFFF
Define ICC_LISTVIEW_CLASSES For |CI$00000001 // listview, header
Define ICC_TREEVIEW_CLASSES For |CI$00000002 // treeview, tooltips
Define ICC_BAR_CLASSES      For |CI$00000004 // toolbar, statusbar, trackbar, tooltips
Define ICC_TAB_CLASSES      For |CI$00000008 // tab, tooltips
Define ICC_UPDOWN_CLASS     For |CI$00000010 // updown
Define ICC_PROGRESS_CLASS   For |CI$00000020 // progress
Define ICC_HOTKEY_CLASS     For |CI$00000040 // hotkey
Define ICC_ANIMATE_CLASS    For |CI$00000080 // animate
Define ICC_WIN95_CLASSES    For |CI$000000FF
Define ICC_DATE_CLASSES     For |CI$00000100 // month picker, date picker, time picker, updown
Define ICC_USEREX_CLASSES   For |CI$00000200 // comboex
Define ICC_COOL_CLASSES     For |CI$00000400 // rebar (coolbar) control
Define ICC_INTERNET_CLASSES For |CI$00000800
Define ICC_PAGESCROLLER_CLASS For |CI$00001000   // page scroller
Define ICC_NATIVEFNTCTL_CLASS For |CI$00002000   // native font control

Define LVS_ICON                For |CI$0000
Define LVS_REPORT              For |CI$0001
Define LVS_SMALLICON           For |CI$0002
Define LVS_LIST                For |CI$0003
Define LVS_TYPEMASK            For |CI$0003
Define LVS_SINGLESEL           For |CI$0004
Define LVS_SHOWSELALWAYS       For |CI$0008
Define LVS_SORTASCENDING       For |CI$0010
Define LVS_SORTDESCENDING      For |CI$0020
Define LVS_SHAREIMAGELISTS     For |CI$0040
Define LVS_NOLABELWRAP         For |CI$0080
Define LVS_AUTOARRANGE         For |CI$0100
Define LVS_EDITLABELS          For |CI$0200
Define LVS_OWNERDATA           For |CI$1000
Define LVS_NOSCROLL            For |CI$2000
Define LVS_TYPESTYLEMASK       For |CI$fc00
Define LVS_ALIGNTOP            For |CI$0000
Define LVS_ALIGNLEFT           For |CI$0800
Define LVS_ALIGNMASK           For |CI$0c00
Define LVS_OWNERDRAWFIXED      For |CI$0400
Define LVS_NOCOLUMNHEADER      For |CI$4000
Define LVS_NOSORTHEADER        For |CI$8000

Define LVM_SETUNICODEFORMAT    For CCM_SETUNICODEFORMAT
Define LVM_GETUNICODEFORMAT    For CCM_GETUNICODEFORMAT
Define LVM_GETBKCOLOR          For (LVM_FIRST + 0)
Define LVM_SETBKCOLOR          For (LVM_FIRST + 1)
Define LVM_GETIMAGELIST        For (LVM_FIRST + 2)

Define LVSIL_NORMAL            For 0
Define LVSIL_SMALL             For 1
Define LVSIL_STATE             For 2

Define LVM_SETIMAGELIST        For (LVM_FIRST + 3)
Define LVM_GETITEMCOUNT        For (LVM_FIRST + 4)

Define LVIF_TEXT               For |CI$0001
Define LVIF_IMAGE              For |CI$0002
Define LVIF_PARAM              For |CI$0004
Define LVIF_STATE              For |CI$0008
Define LVIF_INDENT             For |CI$0010
Define LVIF_NORECOMPUTE        For |CI$0800

Define LVIS_FOCUSED            For |CI$0001
Define LVIS_SELECTED           For |CI$0002
Define LVIS_CUT                For |CI$0004
Define LVIS_DROPHILITED        For |CI$0008
Define LVIS_ACTIVATING         For |CI$0020
Define LVIS_OVERLAYMASK        For |CI$0F00
Define LVIS_STATEIMAGEMASK     For |CI$F000

Define I_INDENTCALLBACK        For (-1)

Type tLVITEM
    Field tLVITEM.mask as UInteger
    Field tLVITEM.iItem as Integer
    Field tLVITEM.iSubItem as Integer
    Field tLVITEM.state as UInteger
    Field tLVITEM.stateMask as UInteger
    Field tLVITEM.pszText as Pointer
    Field tLVITEM.cchTextMax as Integer
    Field tLVITEM.iImage as Integer
    Field tLVITEM.lParam as DWORD
    Field tLVITEM.iIndent as Integer
End_Type

Define LPSTR_TEXTCALLBACKA     For (-1)
Define LPSTR_TEXTCALLBACK      For LPSTR_TEXTCALLBACKA

//Define I_IMAGECALLBACK         for (-1)

Define LVM_GETITEMA            For (LVM_FIRST + 5)
Define LVM_GETITEM             For LVM_GETITEMA

Define LVM_SETITEMA            For (LVM_FIRST + 6)
Define LVM_SETITEM             For LVM_SETITEMA

Define LVM_INSERTITEMA         For (LVM_FIRST + 7)
Define LVM_INSERTITEM          For LVM_INSERTITEMA

Define LVM_DELETEITEM          For (LVM_FIRST + 8)
Define LVM_DELETEALLITEMS      For (LVM_FIRST + 9)
Define LVM_GETCALLBACKMASK     For (LVM_FIRST + 10)
Define LVM_SETCALLBACKMASK     For (LVM_FIRST + 11)

Define LVNI_ALL                For |CI$0000
Define LVNI_FOCUSED            For |CI$0001
Define LVNI_SELECTED           For |CI$0002
Define LVNI_CUT                For |CI$0004
Define LVNI_DROPHILITED        For |CI$0008
Define LVNI_ABOVE              For |CI$0100
Define LVNI_BELOW              For |CI$0200
Define LVNI_TOLEFT             For |CI$0400
Define LVNI_TORIGHT            For |CI$0800

Define LVM_GETNEXTITEM         For (LVM_FIRST + 12)

Define LVFI_PARAM              For |CI$0001
Define LVFI_STRING             For |CI$0002
Define LVFI_PARTIAL            For |CI$0008
Define LVFI_WRAP               For |CI$0020
Define LVFI_NEARESTXY          For |CI$0040

Type tLVFINDINFO
    Field tLVFINDINFO.flags as UInteger
    Field tLVFINDINFO.psz as Pointer
    Field tLVFINDINFO.lParam as DWORD
    Field tLVFINDINFO.pt.x as Integer
    Field tLVFINDINFO.pt.y as Integer
    Field tLVFINDINFO.vkDirection as UInteger
End_Type

Define LVM_FINDITEMA           For (LVM_FIRST + 13)
Define  LVM_FINDITEM           For LVM_FINDITEMA

TYPE LV_FINDINFO
    FIELD LV_FINDINFO.flags       as integer
    FIELD LV_FINDINFO.psz         as pointer
    FIELD LV_FINDINFO.lParam      as integer
    FIELD LV_FINDINFO.x           as dword
    FIELD LV_FINDINFO.y           as dword
    FIELD LV_FINDINFO.vkDirection as integer
END_TYPE

Define LVIR_BOUNDS             For 0
Define LVIR_ICON               For 1
Define LVIR_LABEL              For 2
Define LVIR_SELECTBOUNDS       For 3

Define LVM_GETITEMRECT         For (LVM_FIRST + 14)
Define LVM_SETITEMPOSITION     For (LVM_FIRST + 15)
Define LVM_GETITEMPOSITION     For (LVM_FIRST + 16)
Define LVM_GETSTRINGWIDTHA     For (LVM_FIRST + 17)
Define  LVM_GETSTRINGWIDTH     For LVM_GETSTRINGWIDTHA

Define LVHT_NOWHERE            For |CI$0001
Define LVHT_ONITEMICON         For |CI$0002
Define LVHT_ONITEMLABEL        For |CI$0004
Define LVHT_ONITEMSTATEICON    For |CI$0008
Define LVHT_ONITEM             For (LVHT_ONITEMICON Ior LVHT_ONITEMLABEL Ior LVHT_ONITEMSTATEICON)

Define LVHT_ABOVE              For |CI$0008
Define LVHT_BELOW              For |CI$0010
Define LVHT_TORIGHT            For |CI$0020
Define LVHT_TOLEFT             For |CI$0040

Type tLVHITTESTINFO
    Field tLVHITTESTINFO.pt.x as Integer
    Field tLVHITTESTINFO.pt.y as Integer
    Field tLVHITTESTINFO.flags as UInteger
    Field tLVHITTESTINFO.iItem as Integer
    Field tLVHITTESTINFO.iSubItem as Integer
End_Type

Define LVM_HITTEST             For (LVM_FIRST + 18)
Define LVM_ENSUREVISIBLE       For (LVM_FIRST + 19)
Define LVM_SCROLL              For (LVM_FIRST + 20)
Define LVM_REDRAWITEMS         For (LVM_FIRST + 21)

Define LVA_DEFAULT             For |CI$0000
Define LVA_ALIGNLEFT           For |CI$0001
Define LVA_ALIGNTOP            For |CI$0002
Define LVA_SNAPTOGRID          For |CI$0005

Define LVM_ARRANGE             For (LVM_FIRST + 22)
Define LVM_EDITLABELA          For (LVM_FIRST + 23)
Define LVM_EDITLABELW          For (LVM_FIRST + 118)
Define LVM_EDITLABEL           For LVM_EDITLABELA
Define LVM_GETEDITCONTROL      For (LVM_FIRST + 24)

Type tLVCOLUMN
    Field tLVCOLUMN.mask as UInteger
    Field tLVCOLUMN.fmt as Integer
    Field tLVCOLUMN.cx as Integer
    Field tLVCOLUMN.pszText as Pointer
    Field tLVCOLUMN.cchTextMax as Integer
    Field tLVCOLUMN.iSubItem as Integer
    Field tLVCOLUMN.iImage as Integer
    Field tLVCOLUMN.iOrder as Integer
End_Type

Define LVCF_FMT                For |CI$0001
Define LVCF_WIDTH              For |CI$0002
Define LVCF_TEXT               For |CI$0004
Define LVCF_SUBITEM            For |CI$0008
Define LVCF_IMAGE              For |CI$0010
Define LVCF_ORDER              For |CI$0020

Define LVCFMT_LEFT             For |CI$0000
Define LVCFMT_RIGHT            For |CI$0001
Define LVCFMT_CENTER           For |CI$0002
Define LVCFMT_JUSTIFYMASK      For |CI$0003
Define LVCFMT_IMAGE            For |CI$0800
Define LVCFMT_BITMAP_ON_RIGHT  For |CI$1000
Define LVCFMT_COL_HAS_IMAGES   For |CI$8000

Define LVM_GETCOLUMNA          For (LVM_FIRST + 25)
Define  LVM_GETCOLUMN          For LVM_GETCOLUMNA

Define LVM_SETCOLUMNA          For (LVM_FIRST + 26)
Define  LVM_SETCOLUMN          For LVM_SETCOLUMNA

Define LVM_INSERTCOLUMNA       For (LVM_FIRST + 27)
Define  LVM_INSERTCOLUMN       For LVM_INSERTCOLUMNA

Define LVM_DELETECOLUMN        For (LVM_FIRST + 28)
Define LVM_GETCOLUMNWIDTH      For (LVM_FIRST + 29)

Define LVSCW_AUTOSIZE              For -1
Define LVSCW_AUTOSIZE_USEHEADER    For -2
Define LVM_SETCOLUMNWIDTH          For (LVM_FIRST + 30)

Define LVM_GETHEADER           For (LVM_FIRST + 31)
Define LVM_CREATEDRAGIMAGE     For (LVM_FIRST + 33)
Define LVM_GETVIEWRECT         For (LVM_FIRST + 34)
Define LVM_GETTEXTCOLOR        For (LVM_FIRST + 35)
Define LVM_SETTEXTCOLOR        For (LVM_FIRST + 36)
Define LVM_GETTEXTBKCOLOR      For (LVM_FIRST + 37)
Define LVM_SETTEXTBKCOLOR      For (LVM_FIRST + 38)
Define LVM_GETTOPINDEX         For (LVM_FIRST + 39)
Define LVM_GETCOUNTPERPAGE     For (LVM_FIRST + 40)
Define LVM_GETORIGIN           For (LVM_FIRST + 41)
Define LVM_UPDATE              For (LVM_FIRST + 42)
Define LVM_SETITEMSTATE        For (LVM_FIRST + 43)
Define LVM_GETITEMSTATE        For (LVM_FIRST + 44)
Define LVM_GETITEMTEXTA        For (LVM_FIRST + 45)
Define  LVM_GETITEMTEXT        For LVM_GETITEMTEXTA
Define LVM_SETITEMTEXTA        For (LVM_FIRST + 46)
Define  LVM_SETITEMTEXT        For LVM_SETITEMTEXTA

Define LVSICF_NOINVALIDATEALL  For |CI$00000001
Define LVSICF_NOSCROLL         For |CI$00000002

Define LVM_SETITEMCOUNT        For (LVM_FIRST + 47)
Define LVM_SORTITEMS           For (LVM_FIRST + 48)
Define LVM_SETITEMPOSITION32   For (LVM_FIRST + 49)
Define LVM_GETSELECTEDCOUNT    For (LVM_FIRST + 50)
Define LVM_GETITEMSPACING      For (LVM_FIRST + 51)
Define LVM_GETISEARCHSTRINGA   For (LVM_FIRST + 52)
Define LVM_GETISEARCHSTRING    For LVM_GETISEARCHSTRINGA
Define LVM_SETICONSPACING      For (LVM_FIRST + 53)
Define LVM_SETEXTENDEDLISTVIEWSTYLE For (LVM_FIRST + 54)   // optional wParam == mask
Define LVM_GETEXTENDEDLISTVIEWSTYLE For (LVM_FIRST + 55)

Define LVS_EX_GRIDLINES        For |CI$00000001
Define LVS_EX_SUBITEMIMAGES    For |CI$00000002
Define LVS_EX_CHECKBOXES       For |CI$00000004
Define LVS_EX_TRACKSELECT      For |CI$00000008
Define LVS_EX_HEADERDRAGDROP   For |CI$00000010
Define LVS_EX_FULLROWSELECT    For |CI$00000020 // applies to report mode only
Define LVS_EX_ONECLICKACTIVATE For |CI$00000040
Define LVS_EX_TWOCLICKACTIVATE For |CI$00000080
Define LVS_EX_FLATSB           For |CI$00000100
Define LVS_EX_REGIONAL         For |CI$00000200
Define LVS_EX_INFOTIP          For |CI$00000400 // listview does InfoTips for you
Define LVS_EX_UNDERLINEHOT     For |CI$00000800
Define LVS_EX_UNDERLINECOLD    For |CI$00001000
Define LVS_EX_MULTIWORKAREAS   For |CI$00002000

Define LVM_GETSUBITEMRECT      For (LVM_FIRST + 56)
Define LVM_SUBITEMHITTEST      For (LVM_FIRST + 57)
Define LVM_SETCOLUMNORDERARRAY For (LVM_FIRST + 58)
Define LVM_GETCOLUMNORDERARRAY For (LVM_FIRST + 59)
Define LVM_SETHOTITEM          For (LVM_FIRST + 60)
Define LVM_GETHOTITEM          For (LVM_FIRST + 61)
Define LVM_SETHOTCURSOR        For (LVM_FIRST + 62)
Define LVM_GETHOTCURSOR        For (LVM_FIRST + 63)
Define LVM_APPROXIMATEVIEWRECT For (LVM_FIRST + 64)

Define LV_MAX_WORKAREAS        For 16                          
Define LVM_SETWORKAREAS        For (LVM_FIRST + 65)
Define LVM_GETWORKAREAS        For (LVM_FIRST + 70)
Define LVM_GETNUMBEROFWORKAREAS For (LVM_FIRST + 73)
Define LVM_GETSELECTIONMARK    For (LVM_FIRST + 66)
Define LVM_SETSELECTIONMARK    For (LVM_FIRST + 67)
Define LVM_SETHOVERTIME        For (LVM_FIRST + 71)
Define LVM_GETHOVERTIME        For (LVM_FIRST + 72)
Define LVM_SETTOOLTIPS         For (LVM_FIRST + 74)
Define LVM_GETTOOLTIPS         For (LVM_FIRST + 78)

Type tLVBKIMAGE
    Field tLVBKIMAGE.ulFlags as UInteger
    Field tLVBKIMAGE.hbm as Handle
    Field tLVBKIMAGE.pszImage as Pointer
    Field tLVBKIMAGE.cchImageMax as Integer
    Field tLVBKIMAGE.xOffsetPercent as Integer
    Field tLVBKIMAGE.yOffsetPercent as Integer
End_Type

Define LVBKIF_SOURCE_NONE      For |CI$00000000
Define LVBKIF_SOURCE_HBITMAP   For |CI$00000001
Define LVBKIF_SOURCE_URL       For |CI$00000002
Define LVBKIF_SOURCE_MASK      For |CI$00000003
Define LVBKIF_STYLE_NORMAL     For |CI$00000000
Define LVBKIF_STYLE_TILE       For |CI$00000010
Define LVBKIF_STYLE_MASK       For |CI$00000010

Define LVM_SETBKIMAGEA         For (LVM_FIRST + 68)
Define LVM_GETBKIMAGEA         For (LVM_FIRST + 69)
Define LVM_SETBKIMAGE          For LVM_SETBKIMAGEA
Define LVM_GETBKIMAGE          For LVM_GETBKIMAGEA

Type tNM_LISTVIEW
    Field tNM_LISTVIEW.NMHDR.hwndFrom As Handle
    Field tNM_LISTVIEW.NMHDR.idFrom   As Integer
    Field tNM_LISTVIEW.NMHDR.code     As Integer
    Field tNM_LISTVIEW.iItem as Integer
    Field tNM_LISTVIEW.iSubItem as Integer
    Field tNM_LISTVIEW.uNewState as UInteger
    Field tNM_LISTVIEW.uOldState as UInteger
    Field tNM_LISTVIEW.uChanged as UInteger
    Field tNM_LISTVIEW.pt.x as Integer
    Field tNM_LISTVIEW.pt.y as Integer
    Field tNM_LISTVIEW.lParam as DWORD
End_Type

// NMITEMACTIVATE is used instead of NMLISTVIEW in IE >= for |CI$400
// therefore all the fields are the same except for extra uKeyFlags
// they are used to store key flags at the time of the single click with
// delayed activation - because by the time the timer goes off a user may
// not hold the keys (shift, ctrl) any more
Type tNMITEMACTIVATE
    Field tNMITEMACTIVATE.NMHDR.hwndFrom As Handle
    Field tNMITEMACTIVATE.NMHDR.idFrom   As Integer
    Field tNMITEMACTIVATE.NMHDR.code     As Integer
    Field tNMITEMACTIVATE.iItem as Integer
    Field tNMITEMACTIVATE.iSubItem as Integer
    Field tNMITEMACTIVATE.uNewState as UInteger
    Field tNMITEMACTIVATE.uOldState as UInteger
    Field tNMITEMACTIVATE.uChanged as UInteger
    Field tNMITEMACTIVATE.pt.x as Integer
    Field tNMITEMACTIVATE.pt.y as Integer
    Field tNMITEMACTIVATE.lParam as DWORD
    Field tNMITEMACTIVATE.uKeyFlags as UInteger
End_Type

// key flags stored in uKeyFlags
Define LVKF_ALT       For |CI$0001
Define LVKF_CONTROL   For |CI$0002
Define LVKF_SHIFT     For |CI$0004

Type tNMLVCACHEHINT
    Field tNMLVCACHEHINT.NMHDR.hwndFrom As Handle
    Field tNMLVCACHEHINT.NMHDR.idFrom   As Integer
    Field tNMLVCACHEHINT.NMHDR.code     As Integer
    Field tNMLVCACHEHINT.iFrom as Integer
    Field tNMLVCACHEHINT.iTo as Integer
End_Type

Type tNMLVFINDITEM
    Field tNMLVFINDITEM.NMHDR.hwndFrom As Handle
    Field tNMLVFINDITEM.NMHDR.idFrom   As Integer
    Field tNMLVFINDITEM.NMHDR.code     As Integer
    Field tNMLVFINDITEM.iState as Integer
    Field tNMLVFINDITEM.tLVFINDINFO.flags as UInteger
    Field tNMLVFINDITEM.tLVFINDINFO.psz as Pointer
    Field tNMLVFINDITEM.tLVFINDINFO.lParam as DWORD
    Field tNMLVFINDITEM.tLVFINDINFO.pt.x as Integer
    Field tNMLVFINDITEM.tLVFINDINFO.pt.y as Integer
    Field tNMLVFINDITEM.tLVFINDINFO.vkDirection as UInteger
End_Type


Type tNMLVODSTATECHANGE
    Field tNMLVODSTATECHANGE.NMHDR.hwndFrom As Handle
    Field tNMLVODSTATECHANGE.NMHDR.idFrom   As Integer
    Field tNMLVODSTATECHANGE.NMHDR.code     As Integer
    Field tNMLVODSTATECHANGE.iFrom as Integer
    Field tNMLVODSTATECHANGE.iTo as Integer
    Field tNMLVODSTATECHANGE.uNewState as UInteger
    Field tNMLVODSTATECHANGE.uOldState as UInteger
End_Type

Define LVN_ITEMCHANGING        For (LVN_FIRST-0)
Define LVN_ITEMCHANGED         For (LVN_FIRST-1)
Define LVN_INSERTITEM          For (LVN_FIRST-2)
Define LVN_DELETEITEM          For (LVN_FIRST-3)
Define LVN_DELETEALLITEMS      For (LVN_FIRST-4)
Define LVN_BEGINLABELEDITA     For (LVN_FIRST-5)
Define LVN_BEGINLABELEDITW     For (LVN_FIRST-75)
Define LVN_ENDLABELEDITA       For (LVN_FIRST-6)
Define LVN_ENDLABELEDITW       For (LVN_FIRST-76)
Define LVN_COLUMNCLICK         For (LVN_FIRST-8)
Define LVN_BEGINDRAG           For (LVN_FIRST-9)
Define LVN_BEGINRDRAG          For (LVN_FIRST-11)
Define LVN_ODCACHEHINT         For (LVN_FIRST-13)
Define LVN_ODFINDITEMA         For (LVN_FIRST-52)
Define LVN_ODFINDITEMW         For (LVN_FIRST-79)
Define LVN_ITEMACTIVATE        For (LVN_FIRST-14)
Define LVN_ODSTATECHANGED      For (LVN_FIRST-15)
Define LVN_ODFINDITEM          For LVN_ODFINDITEMA
Define LVN_HOTTRACK            For (LVN_FIRST-21)
Define LVN_GETDISPINFOA        For (LVN_FIRST-50)
Define LVN_GETDISPINFOW        For (LVN_FIRST-77)
Define LVN_SETDISPINFOA        For (LVN_FIRST-51)
Define LVN_SETDISPINFOW        For (LVN_FIRST-78)
Define LVN_BEGINLABELEDIT      For LVN_BEGINLABELEDITA
Define LVN_ENDLABELEDIT        For LVN_ENDLABELEDITA
Define LVN_GETDISPINFO         For LVN_GETDISPINFOA
Define LVN_SETDISPINFO         For LVN_SETDISPINFOA

Define LVIF_DI_SETITEM         For |CI$1000

Type tNMLVDISPINFO
    Field tNMLVDISPINFO.NMHDR.hwndFrom As Handle
    Field tNMLVDISPINFO.NMHDR.idFrom   As Integer
    Field tNMLVDISPINFO.NMHDR.code     As Integer
    Field tNMLVDISPINFO.LVITEM.mask as UInteger
    Field tNMLVDISPINFO.LVITEM.iItem as Integer
    Field tNMLVDISPINFO.LVITEM.iSubItem as Integer
    Field tNMLVDISPINFO.LVITEM.state as UInteger
    Field tNMLVDISPINFO.LVITEM.stateMask as UInteger
    Field tNMLVDISPINFO.LVITEM.pszText as Pointer
    Field tNMLVDISPINFO.LVITEM.cchTextMax as Integer
    Field tNMLVDISPINFO.LVITEM.iImage as Integer
    Field tNMLVDISPINFO.LVITEM.lParam as DWORD
    Field tNMLVDISPINFO.LVITEM.iIndent as Integer
End_Type

Define LVN_KEYDOWN             For (LVN_FIRST-55)

Type tNMLVKEYDOWN
    Field tNMLVKEYDOWN.NMHDR.hwndFrom As Handle
    Field tNMLVKEYDOWN.NMHDR.idFrom   As Integer
    Field tNMLVKEYDOWN.NMHDR.code     As Integer
    Field tNMLVKEYDOWN.wVKey as WORD
    Field tNMLVKEYDOWN.flags as UInteger
End_Type

Define LVN_MARQUEEBEGIN        For (LVN_FIRST-56)

Type tNMLVGETINFOTIP
    Field tNMLVGETINFOTIP.NMHDR.hwndFrom As Handle
    Field tNMLVGETINFOTIP.NMHDR.idFrom   As Integer
    Field tNMLVGETINFOTIP.NMHDR.code     As Integer
    Field tNMLVGETINFOTIP.dwFlags as DWORD
    Field tNMLVGETINFOTIP.pszText as Pointer
    Field tNMLVGETINFOTIP.cchTextMax as Integer
    Field tNMLVGETINFOTIP.iItem as Integer
    Field tNMLVGETINFOTIP.iSubItem as Integer
    Field tNMLVGETINFOTIP.lParam as DWORD
End_Type

Define LVGIT_UNFOLDED  For |CI$0001

Define LVN_GETINFOTIPA         For (LVN_FIRST-57)
Define LVN_GETINFOTIP          For LVN_GETINFOTIPA

//#IFDEF IMI_HAND
//#ELSE
//Type tINITCOMMONCONTROLSEX
//    Field tINITCOMMONCONTROLSEX.dwSize as DWORD              // size of this structure
//    Field tINITCOMMONCONTROLSEX.dwICC  as DWORD              // flags indicating which classes to be initialized
//End_Type
//#ENDIF

//#IFDEF GET_INITCOMMONCONTROLSEX
//#ELSE
//External_function InitCommonControlsEx "InitCommonControlsEx" COMCTL32.DLL Pointer lpCCE Returns Integer
//#ENDIF
//external_function CoInitialize "CoInitialize" ole32.dll Pointer lpVoid returns integer

Procedure DoInitCommonControlsEx Integer iClasses
    String szINITCOMMONCONTROLSEX
    Pointer pszINITCOMMONCONTROLSEX
    Integer iVoid
    
    ZeroType tINITCOMMONCONTROLSEX To szINITCOMMONCONTROLSEX
    Put tINITCOMMONCONTROLSEX_size To szINITCOMMONCONTROLSEX At tINITCOMMONCONTROLSEX.dwSize
    Put iClasses To szINITCOMMONCONTROLSEX At tINITCOMMONCONTROLSEX.dwICC
    
    GetAddress Of szINITCOMMONCONTROLSEX To pszINITCOMMONCONTROLSEX
    Move (InitCommonControlsEx(pszINITCOMMONCONTROLSEX)) To iVoid
End_Procedure

