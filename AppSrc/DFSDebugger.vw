Use Windows.pkg
Use DFClient.pkg
Use DFTabDlg.pkg
Use cTextEdit.pkg
Use cRichEdit.pkg
Use dfLine.pkg
Use dfTreeVw.pkg
Use File_dlg.pkg
Use dfScriptor.pkg
Use cWinListView.pkg
Use cSplitterContainer.pkg

Use DrgNDrop.pkg
Use dfsScriptEditor.pkg
Use dfsConsole.pkg

Class cDebuggerPage is a TabPage
    Procedure OnPageButtonClick
    End_Procedure
End_Class

Class cDebuggerTreeView is a TreeView
    Import_Class_Protocol cDragAndDrop_mx

    Function DragAndDrop_DataType Returns String
        Function_Return "DD_TEXT"
    End_Function

End_Class


Activate_View Activate_oDFSDebugger for oDFSDebugger
Object oDFSDebugger is a dbView
    //
    Set Label to "DataFlex Script Debugger"
    Set Size to 335 545
    Set Location to 5 7
    Set DEO_Delegate_Mode to Delegate_Always
    Set Maximize_Icon to True
    Set Bitmap_Style to Bitmap_Stretch
    Set Border_Style to Border_Thick
    On_Key Key_Ctrl+Key_N Send mScriptNew
    On_Key Key_Ctrl+Key_O Send mScriptOpen
    On_Key Key_Ctrl+Key_S Send mScriptCompile
    On_Key Key_Ctrl+Key_B Send mScriptBuild
    On_Key Key_F2         Send mScriptSave
    On_Key Key_F5         Send mScriptRun

    Set Icon to "Scriptor16.ico"
    Set piMinSize to 335 545

    Object oDFScriptor is a cDFScriptor
    End_Object
    
    Object oScriptDebuggerDialog is a TabDialog
        Set Size to 336 546
        Set Location to -2 -3
        Set Rotate_Mode to RM_Rotate
        Set peAnchors to anAll
        Set pbFlatSeparators to True
        Set peTabStyle to tsFlatButtons
        Set peTabPosition to tpBottom
        Set TabWidth_Mode to twFixedWidth

        Object oTP_Script is a cDebuggerPage
            Set Label to 'Script'

            Object oSplitterContainer3 is a cSplitterContainer
                Set piSplitterLocation to 386
                Set peFixedPanel to fpFixLastPanel
                Set piMaxSplitterLocation to 50
                Set piMinSplitterLocation to 50
                Object oSplitterContainerChild5 is a cSplitterContainerChild
                    Object oContainer3d1 is a Container3d
                        Set Size to 320 383
                        Set Location to 0 0
                        Set peAnchors to anAll
                        Set Border_Style to Border_None

                        Object oSplitterContainer5 is a cSplitterContainer
                            Set pbSplitVertical to False
                            Set piSplitterLocation to 247
                            Set peFixedPanel to fpFixLastPanel
                            Object oSplitterContainerChild9 is a cSplitterContainerChild
                                Set Border_Style to Border_None
                                Object oSourceEditor is a cSourceEditor
                                    Set Size to 248 383
                                    Set Location to -1 1
                                    Set peAnchors to anAll
                                    Procedure onModifiedChange Integer bModified
                                        String sFileTitle sModified
                                        Get psScriptFile of oDFScriptor to sFileTitle
                                        If (sFileTitle="") Move "Noname" to sFileTitle
                                        If bModified Move '*' to sModified
                                        Set Label of oDFSDebugger to ("DataFlex Script Debugger - "+sFileTitle+sModified)
                                    End_Procedure
                                    Procedure Delete_Data
                                        Integer iRet
                                        Move (CM_Settext(Self,""))      to iRet
                                        Move (CM_ClearUndoBuffer(Self)) to iRet
                                        Move (CM_ClearUndoBuffer(Self)) to iRet
                                    End_Procedure
                                    Function DragAndDrop_CanReceiveData String sDataType Returns Integer
                                        If (CM_IsReadOnly(Self)) Function_Return 0
                                        If (HitTestCurrentMouse(Self)) Eq CM_EDITSPACE Begin
                                            If sDataType Eq "DD_TEXT"   Function_Return 1
                                            If sDataType Eq "DD_CLASS"  Function_Return 1
                                            If sDataType Eq "DD_OBJECT" Function_Return 1
                                            If sDataType Eq "DD_METHOD" Function_Return 1
                                        End
                                        Function_Return 0
                                    End_Function
                                    Function DragAndDrop_DropData Integer hoSrcObj Returns Integer
                                        Integer iLine
                                        String  sData sDataType
                                        Get DragAndDrop_DataType    of hoSrcObj to sDataType
                                        If (DragAndDrop_CanReceiveData(Self,sDataType)) Begin
                                            Move (LineRowUnderMouseCursor(Self))    to iLine
                                            Move (Hi (iLine))                       to iLine        
                                            Get DragAndDrop_GetData     of hoSrcObj to sData
                                            Send Request_InserTextUnderMouseCursor sData
                                        End
                                        Function_Return 0
                                    End_Function
                                End_Object

                            End_Object

                            Object oSplitterContainerChild10 is a cSplitterContainerChild
                                Set Border_Style to Border_None
                                Object oCompilerInfo is a TreeView
                                    Set Size to 60 385
                                    Set Location to 12 -1
                                    Set peAnchors to anAll
                    
                                    Object oImageList is a cImageList32
                                        Set piMaxImages to 3
                                        Procedure OnCreate // add the images
                                            Integer iImage
                                            Get AddBitmap 'Compile16.bmp' clFuchsia to iImage
                                            Get AddBitmap 'Include16.bmp' clFuchsia to iImage
                                            Get AddBitmap 'Warning16.bmp' clFuchsia to iImage
                                            Get AddBitmap 'Error16.bmp'   clFuchsia to iImage
                                            Get AddBitmap 'Stop16.bmp'    clFuchsia to iImage
                                            Get AddBitmap 'Build16.bmp'   clFuchsia to iImage
                                            Get AddBitmap 'Run16.bmp'     clFuchsia to iImage
                                        End_Procedure
                                    End_Object
                                    Set ImageListObject to (oImageList(Self))
                    
                                    // This routine extracts Parser Tree from DLL
                                    Procedure LoadCompileInfo
                                        Handle hRoot hStop hInclude hError
                                        //
                                        Send ClearAll
                                        //
                                        tCompilerInfo[] ltCompilerInfo
                                        Integer iMessage iMessages
                                        Get ptCompilerInfo of oDFScriptor to ltCompilerInfo
                                        Move (SizeOfArray(ltCompilerInfo)-1) to iMessages
                                        //
                                        tDFSError[] ltDFSErrors
                                        Integer iError iErrors
                                        String sError
                                        //
                                        For iMessage from 0 to iMessages
                                            If (ltCompilerInfo[iMessage].iLevel=0) ;
                                                Get AddTreeItem ltCompilerInfo[iMessage].sInfo 0 0 0 0 to hRoot
                                            If (ltCompilerInfo[iMessage].iLevel=1) ;
                                                Get AddTreeItem ltCompilerInfo[iMessage].sInfo hRoot 0 1 1 to hInclude
                                            If (ltCompilerInfo[iMessage].iLevel=2) ;
                                                Get AddTreeItem ltCompilerInfo[iMessage].sInfo hRoot 0 2 2 to hInclude
                                            If (ltCompilerInfo[iMessage].iLevel=3) ;
                                                Get AddTreeItem ltCompilerInfo[iMessage].sInfo hRoot 0 3 3 to hInclude
                                            If (ltCompilerInfo[iMessage].iLevel=4) ;
                                                Get AddTreeItem ltCompilerInfo[iMessage].sInfo 0 0 4 4 to hStop
                                            If (ltCompilerInfo[iMessage].iLevel=5) ;
                                                Get AddTreeItem ltCompilerInfo[iMessage].sInfo 0 0 5 5 to hRoot
                                            If (ltCompilerInfo[iMessage].iLevel=6) ;
                                                Get AddTreeItem ltCompilerInfo[iMessage].sInfo 0 0 6 6 to hRoot
                                        Loop
                                        //
                                        Send DoExpandAll hRoot
                                        //
                                        If (piErrorsCount(oDFScriptor(Self))) Begin
                                            Get ptDFSErrors of oDFScriptor to ltDFSErrors
                                            Move (SizeOfArray(ltDFSErrors)-1) to iErrors
                                            Get AddTreeItem "---- Compiler Error Summary ----" 0 0 3 3 to hRoot
                                            For iError from 0 to iErrors
                                                Move ("Error"*String(ltDFSErrors[iError].iNumber)+':') to sError
                                                Move (sError * ltDFSErrors[iError].sFile)   to sError
                                                Move (sError * "on line" * String(ltDFSErrors[iError].iLine)*'('+String(ltDFSErrors[iError].iErrLine)+')') to sError
                                                Move (sError * ltDFSErrors[iError].sText) to sError
                                                Get AddTreeItem sError hRoot 0 3 3 to hError
                                            Loop
                                        End
                                        //
                                        Send DoExpandAll hRoot
                                        //
                                    End_Procedure
                    
                                    Procedure OnCreateTree
                                        Send ClearAll
                                        Send LoadCompileInfo
                                    End_Procedure
                    
                                End_Object

                                Object oOutputHeader is a TextBox
                                    Set Auto_Size_State to False
                                    Set Size to 11 385
                                    Set Location to 1 0
                                    Set Label to "  Output"
                                    Set peAnchors to anTopLeftRight
                                    Set Color to clBtnShadow
                                    Set FontWeight to fw_Bold
                                End_Object
                            End_Object
                        End_Object
                    End_Object
                End_Object

                Object oSplitterContainerChild6 is a cSplitterContainerChild
                    Set Border_Style to Border_None
                    Object oContainer3d1 is a Container3d
                        Set Size to 320 154
                        Set Location to 0 0
                        Set peAnchors to anAll
                        Set Border_Style to Border_None

                        Object oSplitterContainer4 is a cSplitterContainer
                            Set pbSplitVertical to False
                            Set piSplitterLocation to 105
                            Set peFixedPanel to fpFixLastPanel
                            Object oSplitterContainerChild7 is a cSplitterContainerChild
                                Set Border_Style to Border_None
                                Object oParserTree is a cDebuggerTreeView //TreeView
                                    Set Size to 95 155
                                    Set Location to 11 0
                                    Set peAnchors to anAll
                                    Set pbEnableInfoTips to True

                                    Object oImageList is a cImageList32
                                        Set piMaxImages to 3
                                        Procedure OnCreate // add the images
                                            Integer iImage
                                            Get AddBitmap 'Script16.bmp' clFuchsia to iImage
                                            Get AddBitmap 'Package16.bmp' clFuchsia to iImage
                                            Get AddBitmap 'Method16.bmp' clFuchsia to iImage
                                            Get AddBitmap 'Object16.bmp' clFuchsia to iImage
                                        End_Procedure
                                    End_Object
                                    Set ImageListObject to (oImageList(Self))
                                    
                                    Function DragAndDrop_GetData Returns String 
                                        Integer iFile
                                        Handle  hoItem
                                        String  sData
                                        tDFSFile[] ltDFSFiles
                                        Get ptDFSFiles of oDFScriptor to ltDFSFiles
                                        Get CurrentTreeItem to hoItem
                                        Get ItemData hoItem to iFile
                                        If (ltDFSFiles[iFile].sMethod="Function")       Move (Character(10)+"Integer iRetValue"+Character(10)+"Get"*ltDFSFiles[iFile].sFileName*"To iRetValue") to sData
                                        If (ltDFSFiles[iFile].sMethod="Procedure")      Move (Character(10)+"Send"*ltDFSFiles[iFile].sFileName) to sData
                                        If (ltDFSFiles[iFile].sMethod="Procedure Set")  Move (Character(10)+"Set"*ltDFSFiles[iFile].sFileName*"To sValue") to sData
                                        If (ltDFSFiles[iFile].sMethod="Object")         Move ltDFSFiles[iFile].sFileName to sData
                                        If (ltDFSFiles[iFile].sMethod="Class")          Move ltDFSFiles[iFile].sFileName to sData
                                        Function_Return sData
                                    End_Function

                                    Procedure OnCreateTree
                                        Send ClearAll
                                        Send LoadScriptFiles
                                    End_Procedure
                                    
                                    // This routine extracts Parser Tree from DLL
                                    Procedure LoadScriptFiles
                                        tDFSFile[] ltDFSFiles
                                        Handle[]   haHandles
                                        Integer iFile iFiles iDepth
                                        Handle hFile hRoot
                                        String sFile sMethod
                                        //
                                        Get ptDFSFiles of oDFScriptor to ltDFSFiles
                                        //
                                        Move (SizeOfArray(ltDFSFiles)-1) to iFiles
                                        For iFile from 0 to iFiles
                                            Move (Uppercase(ltDFSFiles[iFile].sFileName)) to sFile
                                            If (iFile=0) Begin
                                                Get AddTreeItem (ltDFSFiles[iFile].sMethod*'['+sFile+']') 0 0 0 0 to hRoot
                                                Set ItemBold hRoot to True
                                                Move hRoot to haHandles[0]
                                            End
                                            Else Begin
                                                Move (ltDFSFiles[iFile].iDepth-1) to iDepth
                                                Move (ltDFSFiles[iFile].sMethod)  to sMethod
                                                Move haHandles[iDepth] to hFile
                                                If ((sMethod="Object")or(sMethod="Class")) ;
                                                    Get AddTreeItem (ltDFSFiles[iFile].sMethod*'['+sFile+'] on Line:'*String(ltDFSFiles[iFile].iLine)) hFile 0 3 3 to hFile
                                                Else If ((sMethod="Function")or(sMethod="Procedure")or(sMethod="Procedure Set")) ;
                                                    Get AddTreeItem (ltDFSFiles[iFile].sMethod*'['+sFile+'] on Line:'*String(ltDFSFiles[iFile].iLine)) hFile 0 2 2 to hFile
                                                Else Begin
                                                    Get AddTreeItem (ltDFSFiles[iFile].sMethod*'['+sFile+'] on Line:'*String(ltDFSFiles[iFile].iLine)) hFile 0 1 1 to hFile
                                                    Move hFile to haHandles[ltDFSFiles[iFile].iDepth]
                                                End
                                            End
                                            Set ItemData hFile to iFile
                                        Loop
                                        //
                                        Send DoExpandAll hRoot
                                        Set CurrentTreeItem to hRoot
                                        //
                                    End_Procedure
                    
                                End_Object
                    
                                Procedure Activating
                                    Forward Send Activating
                                    Send OnCreateTree to oParserTree
                                End_Procedure
                    
                                Object oScriptHeader is a TextBox
                                    Set Auto_Size_State to False
                                    Set Size to 11 160
                                    Set Location to 1 0
                                    Set Label to "  Script"
                                    Set peAnchors to anTopLeftRight
                                    Set Color to clBtnShadow
                                    Set FontWeight to fw_Bold
                                End_Object
                            End_Object

                            Object oSplitterContainerChild8 is a cSplitterContainerChild
                                Set Border_Style to Border_None

                                Object oApplicationDialog is a TabDialog
                                    Set Size to 204 181
                                    Set Location to 12 -2
                                    Set Rotate_Mode to RM_Rotate
                                    Set peAnchors to anAll
                                    Set peTabStyle to tsFlatButtons
                                    Set TabWidth_Mode to twFixedWidth
                                    //
                                    Object oAppImageList is a cImageList32
                                        Set piMaxImages to 3
                                        Procedure OnCreate // add the images
                                            Integer iImage
                                            Get AddBitmap 'Object16.bmp' clFuchsia to iImage
                                            Get AddBitmap 'Table16.bmp' clFuchsia to iImage
                                        End_Procedure
                                    End_Object
                                    Set phoImageList to (oAppImageList(Self))
                                    //
                                    Object oTP_Objects is a cDebuggerPage
                                        Set piImageIndex to 0
                                        Set Label to 'Objects'
                                        Object oObjectTree is a cDebuggerTreeView //TreeView
                                            Set Size to 190 180
                                            Set Location to 0 0
                                            Set peAnchors to anAll
                                            Set pbEnableInfoTips to True
        
                                            Object oImageList is a cImageList32
                                                Set piMaxImages to 3
                                                Procedure OnCreate // add the images
                                                    Integer iImage
                                                    Get AddBitmap 'Script16.bmp' clFuchsia to iImage
                                                    Get AddBitmap 'Package16.bmp' clFuchsia to iImage
                                                End_Procedure
                                            End_Object
                                            Set ImageListObject to (oImageList(Self))
                            
                                            Procedure OnGetInfoTip Handle hItem String ByRef sInfoTip
                                                Get ItemFullPath hItem to sInfoTip
                                            End_Procedure  // OnGetInfoTip
        
                                            Procedure OnCreateTree
                                                Send ClearAll
                                                Send LoadObjectList
                                            End_Procedure
                                            
                                            Function Object_Short_Name String sName Returns String 
                                                String sTmp
                                                While (sName contains '.')
                                                    Move (Left(sName, Pos('.', sName))) to sTmp
                                                    Move (Replace(sTmp, sName, "")) to sName
                                                Loop
                                                Function_Return sName
                                            End_Function
                                            
                                            Function CanCopy Returns Boolean
                                                Function_Return 1
                                            End_Function
                                            
                                            Procedure Copy
                                                Integer iData
                                                Get ItemData (CurrentTreeItem(Self)) to iData
                                                Direct_Output "clipboard:"
                                                Write (Object_Short_Name(Self, Name(iData)))
                                                Close_Output
                                            End_Procedure
                                            
                                            Function DragAndDrop_GetData Returns String 
                                                Integer iData
                                                Handle  hoItem
                                                Get CurrentTreeItem to hoItem
                                                Get ItemData hoItem to iData
                                                Function_Return (Character(10)+Object_Short_Name(Self, Name(iData)))
                                            End_Function
        
                                            Procedure LoadObjectList
                                                Integer iObject iParent
                                                Handle hRoot hoParent hoObject hoDesktop
                                                String sName
                                                Handle[TOTAL_OBJECTS+1] hoObjects
                                                //
                                                For iObject from 1 to TOTAL_OBJECTS
                                                    If (Object_Id(iObject)) Begin
                                                        If (Parent(iObject)=0) Begin
                                                            Get AddTreeItem (Name(iObject)*'['+String(iObject)+']') 0 0 0 0 to hRoot
                                                            Set ItemData hRoot to iObject
                                                            Move hRoot to hoObjects[iObject]
                                                            If (Name(iObject)="DESKTOP") Move hRoot to hoDesktop
                                                        End
                                                        Else Begin
                                                            Move (Parent(iObject)) to iParent
                                                            Move hoObjects[iParent] to hoParent
                                                            Get Object_Short_Name (Name(iObject)) to sName
                                                            Get AddTreeItem (sName*'['+String(iObject)+']') hoParent 0 1 1 to hoObject
                                                            Set ItemData hoObject to iObject
                                                            Move hoObject to hoObjects[iObject]
                                                        End
                                                    End
                                                Loop
                                                //
                                                Send DoExpandItem hoDesktop
                                                Set CurrentTreeItem to hoDesktop
                                                //
                                            End_Procedure
                            
                                        End_Object
                                        
                                    End_Object // TP_Objects
                                
                                    Object oTP_Database is a cDebuggerPage
                                        Set piImageIndex to 1
                                        Set Label to 'Database'
                                
                                        Object oTablesTree is a cDebuggerTreeView
                                            Set Size to 190 180
                                            Set Location to 0 0
                                            Set peAnchors to anAll
                                            Set pbEnableInfoTips to True
                            
                                            Object oImageList is a cImageList32
                                                Set piMaxImages to 3
                                                Procedure OnCreate // add the images
                                                    Integer iImage
                                                    Get AddBitmap 'Table16.bmp' clFuchsia to iImage
                                                    Get AddBitmap 'Columns16.bmp' clFuchsia to iImage
                                                    Get AddBitmap 'Column16.bmp' clFuchsia to iImage
                                                    Get AddBitmap 'Indexes16.bmp' clFuchsia to iImage
                                                    Get AddBitmap 'Index16.bmp' clFuchsia to iImage
                                                    Get AddBitmap 'Links16.bmp' clFuchsia to iImage
                                                    Get AddBitmap 'Link16.bmp' clFuchsia to iImage
                                                End_Procedure
                                            End_Object
                                            Set ImageListObject to (oImageList(Self))
        
                                            Procedure OnGetInfoTip Handle hItem String ByRef sInfoTip
                                                Get ItemFullPath hItem to sInfoTip
                                            End_Procedure  // OnGetInfoTip
        
                                            Function Table_Drop_Data Handle hItem Returns String
                                                String sData
                                                Integer iData bOpened hTable iIndex iSegment iSegments iColumn iType
                                                String sInfoTip sTable sColumn sSegments sFindInit sType
                                                Get ItemData hItem to iData
                                                If iData Begin
                                                    Get ItemFullPath hItem to sInfoTip
                                                    If (sInfoTip contains "Indexes") Begin
                                                        Move (hi(idata))  to hTable
                                                        Move (Low(idata)) to iIndex
                                                        Get_Attribute DF_FILE_LOGICAL_NAME of hTable to sTable
                                                        If (iIndex<>0) Begin
                                                            Get_Attribute DF_FILE_OPENED of hTable to bOpened
                                                            If (not(bOpened)) Open hTable
                                                            Get_Attribute DF_INDEX_NUMBER_SEGMENTS of hTable iIndex to iSegments
                                                            For iSegment from 1 to iSegments
                                                                Get_Attribute DF_INDEX_SEGMENT_FIELD  of hTable iIndex iSegment to iColumn
                                                                Get_Attribute DF_FIELD_NAME of hTable iColumn to sColumn
                                                                Get_Attribute DF_FIELD_TYPE of hTable iColumn to iType
                                                                If (sSegments="") Move sColumn to sSegments
                                                                Else Move (sSegments+','*sColumn) to sSegments
                                                                Move '""' to sType
                                                                If (iType=DF_BCD) Move 0 to sType
                                                                If (iType=DF_DATE) Move ("(Date("+dfsCurrentDate(Self)+'))') to sType
                                                                Move (sFindInit+"//Move"*sType*"To"*sTable+'.'+sColumn+Character(10)) to sFindInit
                                                            Loop
                                                            If (not(bOpened)) Close hTable
                                                            Move ("Index."+String(iIndex)*"//"* sSegments) to sSegments
                                                        End
                                                        Else Begin
                                                            Move "Recnum" to sSegments
                                                            Move ("//Move 0 to"*sTable+".Recnum"+Character(10)) to sFindInit
                                                        End
                                                        Move (Character(10)+"Clear"*sTable) to sData
                                                        Move (sData+Character(10)+sFindInit) to sData
                                                        Move (sData+("Find EQ"*sTable*"by"*sSegments)) to sData
                                                    End
                                                    Else If (sInfoTip contains "Columns") Begin
                                                        Move (hi(idata)) to hTable
                                                        Get_Attribute DF_FILE_LOGICAL_NAME of hTable to sTable
                                                        Get_Attribute DF_FILE_OPENED of hTable to bOpened
                                                        If (not(bOpened)) Open hTable
                                                        Get_Attribute DF_FIELD_NAME of hTable (Low(idata)) to sColumn
                                                        Move (Character(10)+sTable+"."+sColumn*'/'+'/'*String(hTable)+'.'+String(Low(idata))) to sData
                                                        If (not(bOpened)) Close hTable
                                                    End
                                                    Else If (sInfoTip contains "Relationships") Begin
                                                        Get_Attribute DF_FILE_LOGICAL_NAME of idata to sTable
                                                        Move (Character(10)+"Relate"*sTable) to sData
                                                    End
                                                    Else Begin
                                                        Get_Attribute DF_FILE_LOGICAL_NAME of idata to sTable
                                                        Move (Character(10)+"Open"*sTable) to sData
                                                    End
                                                End
                                                Function_Return sData
                                            End_Function
                                            
                                            Function DragAndDrop_GetData Returns String 
                                                Function_Return (Table_Drop_Data(Self, CurrentTreeItem(Self)))
                                            End_Function
        
                                            Procedure OnCreateTree
                                                Send ClearAll
                                                Send LoadTablesList
                                            End_Procedure
                                            
                                            Function Column_Type Integer iType Returns String
                                                Case Begin
                                                    Case (iType = DF_ASCII)
                                                        Function_Return "ASC"
                                                    Case (iType = DF_BCD)
                                                        Function_Return "NUM"
                                                    Case (iType = DF_DATE)
                                                        Function_Return "ASC"
                                                    Case (iType = DF_OVERLAP)
                                                        Function_Return "OVL"
                                                    Case (iType = DF_TEXT)
                                                        Function_Return "TXT"
                                                    Case (iType = DF_BINARY)
                                                        Function_Return "BIN"
                                                Case End
                                                Function_Return "???"
                                            End_Function
                                            
                                            Procedure LoadTablesList
                                                Handle hTable hParentFile hParentField iRecnum
                                                Handle hRoot hColumns hColumn hIndexes hIndex hSegment hLink hLinks
                                                String sTable sDisplay sColumn sType sLength sParentFile sParentField
                                                Integer iColumn iColumns bOpened bParent iType iLength iPrecision iData
                                                Integer iIndex iIndexes iSegment iSegments iLink iLinks
                                                String[] laLinks laDummy
                                                Move 0 to hTable
                                                Repeat
                                                    Get_Attribute DF_FILE_NEXT_USED of hTable to hTable
                                                    If (hTable > 0) Begin
                                                        Move laDummy to laLinks
                                                        // Tables
                                                        Get_Attribute DF_FILE_LOGICAL_NAME of hTable to sTable
                                                        Get_Attribute DF_FILE_DISPLAY_NAME of hTable to sDisplay
                                                        Get AddTreeItem (sTable*'['+String(hTable)+' - '+sDisplay+']') 0 0 0 0 to hRoot
                                                        Set ItemData hRoot to hTable
                                                        //
                                                        Get_Attribute DF_FILE_OPENED of hTable to bOpened
                                                        If (not(bOpened)) Open hTable
                                                        Get_Attribute DF_FILE_RECNUM_TABLE of hTable to iRecnum
                                                        // Columns
                                                        Get AddTreeItem "Columns" hRoot 0 1 1 to hColumns
                                                        Get_Attribute DF_FILE_NUMBER_FIELDS of hTable to iColumns
                                                        For iColumn from 1 to iColumns
                                                            Get_Attribute DF_FIELD_NAME             of hTable iColumn to sColumn
                                                            Get_Attribute DF_FIELD_TYPE             of hTable iColumn to iType
                                                            Get_Attribute DF_FIELD_LENGTH           of hTable iColumn to iLength
                                                            Get_Attribute DF_FIELD_PRECISION        of hTable iColumn to iPrecision
                                                            Get_Attribute DF_FIELD_RELATED_FILE     of hTable iColumn to hParentFile
                                                            Get_Attribute DF_FIELD_RELATED_FIELD    of hTable iColumn to hParentField
                                                            Move iLength to sLength
                                                            If iPrecision Move (sLength+'.'+String(iPrecision)) to sLength
                                                            Get Column_Type iType to sType
                                                            Get AddTreeItem (sColumn*'('+sType+sLength+')') hColumns 0 2 2 to hColumn
                                                            Move (65536 * hTable + iColumn) to iData
                                                            Set ItemData hColumn to iData
                                                            If (hParentFile+hParentField) Begin
                                                                Get_Attribute DF_FILE_OPENED of hParentFile to bParent
                                                                If (not(bParent)) Open hParentFile
                                                                Get_Attribute DF_FILE_LOGICAL_NAME of hParentFile to sParentFile
                                                                Get_Attribute DF_FIELD_NAME of hParentFile hParentField to sParentField
                                                                Move (sTable+'.'+sColumn+' > '+sParentFile+'.'+sParentField) to laLinks[SizeOfArray(laLinks)]
                                                                If (not(bParent)) Close hParentFile
                                                            End
                                                        Loop
                                                        // Indexes
                                                        Get AddTreeItem "Indexes" hRoot 0 3 3 to hIndexes
                                                        If iRecnum Begin
                                                            Get AddTreeItem "Recnum" hIndexes 0 4 4 to hIndex
                                                            Move (65536 * hTable + 0) to iData
                                                            Set ItemData hIndex to iData
                                                        End
                                                        Get_Attribute DF_FILE_LAST_INDEX_NUMBER of hTable to iIndexes
                                                        For iIndex from 1 to iIndexes
                                                            Get_Attribute DF_INDEX_NUMBER_SEGMENTS of hTable iIndex to iSegments
                                                            Get AddTreeItem ("Index."+String(iIndex)) hIndexes 0 4 4 to hIndex
                                                            Move (65536 * hTable + iIndex) to iData
                                                            Set ItemData hIndex to iData
                                                            For iSegment from 1 to iSegments
                                                                Get_Attribute DF_INDEX_SEGMENT_FIELD  of hTable iIndex iSegment to iColumn
                                                                Get_Attribute DF_FIELD_NAME of hTable iColumn to sColumn
                                                                Get AddTreeItem sColumn hIndex 0 2 2 to hColumn
                                                                Set ItemData hColumn to iData
                                                            Loop
                                                        Loop
                                                        // Links
                                                        Get AddTreeItem "Relationships" hRoot 0 5 5 to hLinks
                                                        Move (SizeOfArray(laLinks)-1) to iLinks
                                                        For iLink from 0 to iLinks
                                                            Get AddTreeItem laLinks[iLink] hLinks 0 6 6 to hColumn
                                                            Set ItemData hColumn to hTable
                                                        Loop
                                                        //
                                                        If (not(bOpened)) Close hTable
                                                    End
                                                Until (hTable = 0)
                                                //
                                            End_Procedure
                            
                                        End_Object // oParserTree
                                    End_Object // TP_Database
                                End_Object // ApplicationDialog

                                Object oApplicationHeader is a TextBox
                                    Set Auto_Size_State to False
                                    Set Size to 10 178
                                    Set Location to 0 0
                                    Set Label to " Application"
                                    Set peAnchors to anTopLeftRight
                                    Set Color to clBtnShadow
                                    Set FontWeight to fw_Bold
                                End_Object
                            End_Object
                        End_Object
                    End_Object
                End_Object
            End_Object

        End_Object

        Object oTP_Scopes is a cDebuggerPage
            Set Label to "Scopes"

            Object oSplitterContainer1 is a cSplitterContainer
                Set piSplitterLocation to 130
                Object oSplitterContainerChild1 is a cSplitterContainerChild
                    Object oScopesHeader is a TextBox
                        Set Auto_Size_State to False
                        Set Size to 10 305
                        Set Location to 0 0
                        Set Label to "  Scopes"
                        Set peAnchors to anTopLeftRight
                        Set Color to clBtnShadow
                        Set FontWeight to fw_Bold
                    End_Object

                    Object oScopes is a cDebuggerTreeView
                        Set Size to 311 270
                        Set Location to 10 -1
                        Set peAnchors to anAll
                        
                        Object oImageList is a cImageList32
                            Set piMaxImages to 3
                            Procedure OnCreate // add the images
                                Integer iImage
                                Get AddBitmap 'Script16.bmp' clFuchsia to iImage
                                Get AddBitmap 'Method16.bmp' clFuchsia to iImage
                                Get AddBitmap 'Object16.bmp' clFuchsia to iImage
                            End_Procedure
                        End_Object
                        Set ImageListObject to (oImageList(Self))
                        
                        Procedure OnItemChanged Handle hItem Handle hItemOld
                            Integer iScope
                            Forward Send OnItemChanged hItem hItemOld
                            Send Clear to oScope
                            Move (ItemData(Self, CurrentTreeItem(Self))) to iScope
                            Send AddTokens to oScope iScope
                            Send Clear to oScopeVariables
                            Send AddVariables to oScopeVariables iScope
                        End_Procedure

                        Procedure LoadScopesList
                            Handle hScope hRoot
                            String sName sType sReturn sDimension
                            tDFSScope[] ltDFSScopes
                            Integer iScope iScopes iImage
                            Get ptDFSScopes of oDFScriptor to ltDFSScopes
                            Move (SizeOfArray(ltDFSScopes)-1) to iScopes
                            For iScope from 0 to iScopes
                                If (iScope=0) ;
                                    Get AddTreeItem ("[Main Script]"*'-'*String(iScope)) 0 0 0 0 to hRoot
                                Else Begin
                                    Move ltDFSScopes[iScope].sName to sName
                                    If ((ltDFSScopes[iScope].iType=DFC_PROCEDURE) or ;
                                        (ltDFSScopes[iScope].iType=DFC_SET) or ;
                                        (ltDFSScopes[iScope].iType=DFC_FUNCTION)) ;
                                            Move 1 to iImage
                                    Else    Move 2 to iImage
                                    Get Scope_Type_Description of oDFScriptor ;
                                            ltDFSScopes[iScope].iType to sType
                                    If (ltDFSScopes[iScope].iReturnType) Begin
                                        Get Var_Type_String of oDFScriptor ;
                                            ltDFSScopes[iScope].iReturnType to sReturn
                                        If (ltDFSScopes[iScope].iReturnDimension) Begin
                                            Get fDFSOutDim of oDFScriptor ltDFSScopes[iScope].iReturnDimension to sDimension
                                            Move (sReturn+sDimension) to sReturn
                                        End
                                        Move (sReturn * sType) to sReturn
                                        Move (sName * '(' + sReturn + ')') to sName
                                    End
                                    Else Move (sName * '(' + sType + ')') to sName
                                    Get AddTreeItem (sName*'-'*String(iScope)) hRoot 0 iImage iImage to hScope
                                    Set ItemData hScope to iScope
                                End
                            Loop
                            Send DoExpandItem hRoot
                            Set CurrentTreeItem to hRoot
                        End_Procedure
                    
                        Procedure OnCreateTree
                            Send ClearAll
                            Send LoadScopesList
                        End_Procedure
                    
                    End_Object
                End_Object

                Object oSplitterContainerChild2 is a cSplitterContainerChild

                    Object oScopesHeader is a TextBox
                        Set Auto_Size_State to False
                        Set Size to 10 410
                        Set Location to 0 0
                        Set Label to "  Scope Tokens"
                        Set peAnchors to anTopLeftRight
                        Set Color to clBtnShadow
                        Set FontWeight to fw_Bold
                    End_Object

                    Object oScope is a cWinListView
                        Set Size to 215 410
                        Set Location to 10 0
                        Set peAnchors to anAll
                        Procedure Clear
                            Send DoDeleteAllItems
                        End_Procedure
                        Procedure Add_Token Integer iToken String sFile Integer iLine Integer iColumn Integer iSymbol String sImage
                            Integer iRow
                            Get AddListItem iToken 0 0 0 0 to iRow
                            Set ItemLabel iRow 1 to sFile
                            Set ItemLabel iRow 2 to iLine
                            Set ItemLabel iRow 3 to iColumn
                            Set ItemLabel iRow 4 to iSymbol
                            Set ItemLabel iRow 5 to sImage
                            //Set ItemSelectState iRow to True
                        End_Procedure
                        Procedure AddTokens Integer iScope
                            Integer iToken iTokens
                            tDFSToken[] ltToken
                            tDFSScope[] ltScopes
                            Get ptDFSScopes of oDFScriptor to ltScopes
                            If (SizeOfArray(ltScopes)=0) Procedure_Return
                            Move (ltScopes[iScope].atTokens) to ltToken
                            Move (SizeOfArray(ltToken)) to iTokens
                            For iToken from 0 to (iTokens-1)
                                Send Add_Token ;
                                    iToken ;
                                    ltToken[iToken].iSymbol ;
                                    ltToken[iToken].sImage ;
                                    ltToken[iToken].sFile ;
                                    ltToken[iToken].iLine ;
                                    ltToken[iToken].iColumn
                            Loop
                        End_Procedure
                        Procedure OnCreate
                            Send Clear
                            //
                            Send DoInsertColumn "Token"    1 60 LVCFMT_RIGHT
                            Send DoInsertColumn "Symbol"   2 70 LVCFMT_RIGHT
                            Send DoInsertColumn "Image"    3 310 LVCFMT_LEFT
                            Send DoInsertColumn "File"     4 130 LVCFMT_LEFT
                            Send DoInsertColumn "Line"     5 70 LVCFMT_RIGHT
                            Send DoInsertColumn "Column"   6 70 LVCFMT_RIGHT
                            //
                            Send AddTokens (ItemData(oScopes(Self), CurrentTreeItem(oScopes(Self))))
                        End_Procedure
                    End_Object
        
                    Object oVariablesHeader is a TextBox
                        Set Auto_Size_State to False
                        Set Size to 10 409
                        Set Location to 225 0
                        Set Label to "  Local Variables"
                        Set peAnchors to anBottomLeftRight
                        Set Color to clBtnShadow
                        Set FontWeight to fw_Bold
                    End_Object

                    Object oScopeVariables is a cWinListView
                        Set Size to 85 410
                        Set Location to 234 0
                        Set peAnchors to anBottomLeftRight
                        Procedure Clear
                            Send DoDeleteAllItems
                        End_Procedure
                        Procedure Add_Variable String sName String sScope String sType Integer iLine Integer iColumn Integer iSymbol String sImage
                            Integer iRow
                            Get AddListItem         sName 0 0 0 0 to iRow
                            Set ItemLabel iRow 1 to sScope
                            Set ItemLabel iRow 2 to sType
                            Set ItemLabel iRow 3 to iLine
                            Set ItemLabel iRow 4 to iColumn
                            Set ItemLabel iRow 5 to iSymbol
                            Set ItemLabel iRow 6 to sImage
                        End_Procedure
                        Procedure AddVariables Integer iScope
                            Integer iVariable iVariables iNumArguments iCount
                            String sIN
                            tDFSVariable[] ltVariables
                            tDFSScope[] ltScopes
                            Get ptDFSScopes of oDFScriptor to ltScopes
                            If (SizeOfArray(ltScopes)=0) Procedure_Return
                            Move (ltScopes[iScope].iNumArguments) to iNumArguments
                            Get ptVariables of oDFScriptor to ltVariables
                            //
                            Move (SizeOfArray(ltVariables)) to iVariables
                            For iVariable from 0 to (iVariables-1)
                                Move "" to sIN
                                If ((iNumArguments) and (iCount<iNumArguments)) ;
                                    Move "IN" to sIN
                                If (ltVariables[iVariable].iScope=iScope) Begin
                                    Send Add_Variable   (ltVariables[iVariable].sName) ;
                                                        sIN ;
                                                        ( (Var_Type_String(oDFScriptor(Self), ltVariables[iVariable].iType)) + ;
                                                        (fDFSOutDim(oDFScriptor(Self), ltVariables[iVariable].iDimension)) ) ;
                                                        (ltVariables[iVariable].iLine) ;
                                                        (ltVariables[iVariable].iColumn) ;
                                                        (ltVariables[iVariable].iType) ;
                                                        ((Var_Prefix(oDFScriptor(Self), ltVariables[iVariable].iType)+String(iVariable))+(If(ltVariables[iVariable].sValue<>"", ","+ltVariables[iVariable].sValue, "")))
                                    Increment iCount
                                End
                            Loop
                            //
                        End_Procedure
                        Procedure OnCreate
                            Send Clear
                            //
                            Send DoInsertColumn "Name"      1 150   LVCFMT_LEFT
                            Send DoInsertColumn ""          2 30    LVCFMT_LEFT
                            Send DoInsertColumn "Type"      4 90    LVCFMT_LEFT
                            Send DoInsertColumn "Line"      6 55    LVCFMT_RIGHT
                            Send DoInsertColumn "Column"    7 55    LVCFMT_RIGHT
                            Send DoInsertColumn "Symbol"    8 55    LVCFMT_RIGHT
                            Send DoInsertColumn "Image"     9 275   LVCFMT_LEFT
                            //
                            Send AddVariables (ItemData(oScopes(Self), CurrentTreeItem(oScopes(Self))))
                            //
                        End_Procedure
                    End_Object // oScopeVariables
                    
                End_Object // oSplitterContainerChild2
                
            End_Object
            
            Procedure OnPageButtonClick
                Integer iScope
                Send OnCreateTree to oScopes
                Move (ItemData(oScopes(Self), CurrentTreeItem(oScopes(Self)))) to iScope
                Send Clear to oScope
                Send AddTokens to oScope iScope
                Send Clear to oScopeVariables
                Send AddVariables to oScopeVariables iScope
            End_Procedure

        End_Object

        Object oTP_Variables is a cDebuggerPage
            Set Label to "Variables"

            Object oVariables is a cWinListView
                Set Size to 321 541
                Set Location to 1 1
                Set peAnchors to anAll
                Procedure Clear
                    Send DoDeleteAllItems
                End_Procedure
                Procedure Add_Variable String sName String sScope String sDesc String sType String sDimension Integer iLine Integer iColumn Integer iSymbol String sImage
                    Integer iRow
                    Get AddListItem         sName 0 0 0 0 to iRow
                    Set ItemLabel iRow 1 to sScope
                    Set ItemLabel iRow 2 to sDesc
                    Set ItemLabel iRow 3 to sType
                    Set ItemLabel iRow 4 to sDimension
                    Set ItemLabel iRow 5 to iLine
                    Set ItemLabel iRow 6 to iColumn
                    Set ItemLabel iRow 7 to iSymbol
                    Set ItemLabel iRow 8 to sImage
                End_Procedure
                Procedure AddVariables
                    Integer iVariable iVariables
                    tDFSVariable[] ltVariables
                    Get ptVariables of oDFScriptor to ltVariables
                    //
                    Move (SizeOfArray(ltVariables)) to iVariables
                    For iVariable from 0 to (iVariables-1)
                        Send Add_Variable   (ltVariables[iVariable].sName) ;
                                            (ltVariables[iVariable].iScope) ;
                                            (Scope_Name(oDFScriptor(Self), ltVariables[iVariable].iScope)) ;
                                            (Var_Type_String(oDFScriptor(Self), ltVariables[iVariable].iType)) ;
                                            (fDFSOutDim(oDFScriptor(Self), ltVariables[iVariable].iDimension)) ;
                                            (ltVariables[iVariable].iLine) ;
                                            (ltVariables[iVariable].iColumn) ;
                                            (ltVariables[iVariable].iType) ;
                                            ((Var_Prefix(oDFScriptor(Self), ltVariables[iVariable].iType)+String(iVariable))+(If(ltVariables[iVariable].sValue<>"", ","+ltVariables[iVariable].sValue, "")))
                    Loop
                    //
                End_Procedure
                Procedure OnCreate
                    Send Clear
                    //
                    Send DoInsertColumn "Name"      1 150   LVCFMT_LEFT
                    Send DoInsertColumn "Scope"     2 45    LVCFMT_LEFT
                    Send DoInsertColumn ""          3 190   LVCFMT_LEFT
                    Send DoInsertColumn "Type"      4 90    LVCFMT_LEFT
                    Send DoInsertColumn "Dim"       5 40    LVCFMT_LEFT
                    Send DoInsertColumn "Line"      6 55    LVCFMT_RIGHT
                    Send DoInsertColumn "Column"    7 55    LVCFMT_RIGHT
                    Send DoInsertColumn "Symbol"    8 55    LVCFMT_RIGHT
                    Send DoInsertColumn "Image"     9 280   LVCFMT_LEFT
                    //
                    Send AddVariables
                    //
                End_Procedure
            End_Object

            Procedure OnPageButtonClick
                Send Clear to oVariables
                Send AddVariables to oVariables
            End_Procedure

        End_Object

        Object oTP_Tokens is a cDebuggerPage
            Set Label to "Tokens"

            Object oTokens is a cWinListView
                Set Size to 321 541
                Set Location to 1 1
                Set peAnchors to anAll
                Procedure Clear
                    Send DoDeleteAllItems
                End_Procedure
                Procedure Add_Token Integer iToken String sFile Integer iLine Integer iColumn Integer iSymbol String sImage
                    Integer iRow
                    Get AddListItem iToken 0 0 0 0 to iRow
                    Set ItemLabel iRow 1 to sFile
                    Set ItemLabel iRow 2 to iLine
                    Set ItemLabel iRow 3 to iColumn
                    Set ItemLabel iRow 4 to iSymbol
                    Set ItemLabel iRow 5 to sImage
                    //Set ItemSelectState iRow to True
                End_Procedure
                Procedure AddTokens
                    Integer iToken iTokens
                    tDFSToken[] ltToken
                    Get ptTokens of oDFScriptor to ltToken
                    Move (SizeOfArray(ltToken)) to iTokens
                    For iToken from 0 to (iTokens-1)
                        Send Add_Token ;
                            iToken ;
                            ltToken[iToken].iSymbol ;
                            ltToken[iToken].sImage ;
                            ltToken[iToken].sFile ;
                            ltToken[iToken].iLine ;
                            ltToken[iToken].iColumn
                    Loop
                End_Procedure
                Procedure OnCreate
                    Send Clear
                    //
                    Send DoInsertColumn "Token"    1 60 LVCFMT_RIGHT
                    Send DoInsertColumn "Symbol"   2 70 LVCFMT_RIGHT
                    Send DoInsertColumn "Image"    3 330 LVCFMT_LEFT
                    Send DoInsertColumn "File"     4 130 LVCFMT_LEFT
                    Send DoInsertColumn "Line"     5 70 LVCFMT_RIGHT
                    Send DoInsertColumn "Column"   6 70 LVCFMT_RIGHT
                    //
                    Send AddTokens
                End_Procedure
            End_Object

            Procedure OnPageButtonClick
                Send Clear to oTokens
                Send AddTokens to oTokens
            End_Procedure
            
        End_Object

        Object oTP_Errors is a cDebuggerPage
            Set Label to "Errors"

            Object oErrors is a cWinListView
                Set Size to 321 541
                Set Location to 1 1
                Set peAnchors to anAll
                Object oImageList is a cImageList32
                    Set piMaxImages to 3
                    Procedure OnCreate // add the images
                        Integer iImage
                        Get AddBitmap 'Error16.bmp'   clFuchsia to iImage
                    End_Procedure
                End_Object

                Procedure Clear
                    Send DoDeleteAllItems
                End_Procedure
                Procedure Add_Error Integer iErrorNo String sError Integer iLine Integer iErrLine String sFile
                    Integer iRow
                    String  sLine
                    If ((iLine<>0) and (iErrline<>0)) Move (String(iLine)*'('+String(iErrLine)+')') to sLine
                    Else If ((iLine<>0) and (iErrLine=0)) Move (String(iLine)) to sLine
                    Else If ((iLine=0) and (iErrLine<>0)) Move (String(iErrLine)) to sLine
                    Else Move 0 to sLine
                    Get AddListItem iErrorNo 0 0 0 0 to iRow
                    Set ItemLabel iRow 1 to sError
                    Set ItemLabel iRow 2 to sLine
                    Set ItemLabel iRow 3 to sFile
                End_Procedure
                Procedure AddErrors
                    Integer iError iErrors
                    tDFSError[] ltDFSErrors
                    Get ptDFSErrors of oDFScriptor to ltDFSErrors
                    Move (SizeOfArray(ltDFSErrors)-1) to iErrors
                    For iError from 0 to iErrors
                        Send Add_Error  ltDFSErrors[iError].iNumber ;
                                        ltDFSErrors[iError].sText ;
                                        ltDFSErrors[iError].iLine ;
                                        ltDFSErrors[iError].iErrLine ;
                                        ltDFSErrors[iError].sFile
                    Loop
                End_Procedure
                Procedure OnCreate
                    Set phSmallIL  to (Window_Handle(oImageList(Self)))
                    Send Clear
                    Send DoInsertColumn "No."      1 100 LVCFMT_RIGHT
                    Send DoInsertColumn "Error"    2 450 LVCFMT_LEFT
                    Send DoInsertColumn "Line"     3 100 LVCFMT_LEFT
                    Send DoInsertColumn "File"     4 100 LVCFMT_LEFT
                    //
                    Send AddErrors
                    //
                End_Procedure
            End_Object

            Procedure OnPageButtonClick
                Send Clear to oErrors
                Send AddErrors to oErrors
            End_Procedure

        End_Object

        Object oTP_Symbols is a cDebuggerPage
            Set Label to "Symbols"
            
            Object oSymbols is a cWinListView
                Set Size to 321 541
                Set Location to 1 1
                Set peAnchors to anAll
                Procedure Clear
                    Send DoDeleteAllItems
                End_Procedure
                Procedure Add_Symbol String sSymbol String sType String sValue
                    Integer iRow
                    Get AddListItem sSymbol 0 0 0 0 to iRow
                    Set ItemLabel iRow 1 to sType
                    Set ItemLabel iRow 2 to sValue
                    //Set ItemSelectState iRow to True
                End_Procedure
                Procedure AddSymbols
                    Integer iSymbol iSymbols
                    Move (SizeOfArray(gtDFSSymbols)-1) to iSymbols
                    For iSymbol from 0 to iSymbols
                        Send Add_Symbol gtDFSSymbols[iSymbol].iSymbol ;
                                        gtDFSSymbols[iSymbol].sType ;
                                        gtDFSSymbols[iSymbol].sDescription
                    Loop
                End_Procedure
                Procedure OnCreate
                //    Set phSmallIL  To (Window_Handle(oSmallImages(Self)))
                    Send Clear
                    Send DoInsertColumn "Symbol"   1 100 LVCFMT_RIGHT
                    Send DoInsertColumn "Type"     2 200 LVCFMT_LEFT
                    Send DoInsertColumn "Value"    3 450 LVCFMT_LEFT
                    //
                    Send AddSymbols
                    //
                End_Procedure
            End_Object
            
        End_Object

        Object oTP_Charsets is a cDebuggerPage
            Set Label to "Charsets"

            Object oCharsets is a cWinListView
                Set Size to 321 541
                Set Location to 1 1
                Set peAnchors to anAll
                Procedure Clear
                    Send DoDeleteAllItems
                End_Procedure
                Procedure Add_Charset String sName String sValue
                    Integer iRow
                    Get AddListItem sName 0 0 0 0 to iRow
                    Set ItemLabel iRow 1 to sValue
                    Set ItemSelectState iRow to False
                End_Procedure
                Procedure AddCharSets
                    Integer iCharSet iCharSets
                    Move (SizeOfArray(gtDFSCharSets)-1) to iCharSets
                    For iCharSet from 0 to iCharSets
                        Send Add_CharSet    gtDFSCharSets[iCharSet].sName ;
                                            gtDFSCharSets[iCharSet].sValue
                    Loop
                End_Procedure
                Procedure OnCreate
                //    Set phSmallIL  To (Window_Handle(oSmallImages(Self)))
                    Send Clear
                    Send DoInsertColumn "Name"     1 200 LVCFMT_LEFT
                    Send DoInsertColumn "Set"      2 550 LVCFMT_LEFT
                    //
                    Send AddCharSets
                End_Procedure
            End_Object

        End_Object

        Object oTP_Console is a cDebuggerPage
            Set Label to "Console"
            Object oConsole is a cConsoleTerminal
                Set Size to 345 566
            End_Object // Console terminal
        End_Object // Console tab page

        Function Tab_Change Integer totab Integer PointerMode Returns Integer
            Integer iRetVal iCurrent
            Handle  hoTab
            Get Current_Tab to iCurrent
            Forward Get Tab_Change totab PointerMode Toggle_State to iRetVal
            If ( (iRetVal=0)and(toTab<>iCurrent) ) Begin
                Get Tab_Page_Id toTab to hoTab
                Send OnPageButtonClick to hoTab
            End
            Function_Return iRetVal
        End_Function

    End_Object

    Procedure DoClearDebugger
        Integer iRet
        // Clear Scriptor Instance
        Send Delete_Data to oDFScriptor
        Set piExecutable of oDFScriptor to 0
        Set psScriptSource of oDFScriptor to ""
        Set psScriptFile of oDFScriptor to ""
        // Clear Script Editor
        Send Delete_Data to oSourceEditor
        Get CM_SetReadOnly of oSourceEditor False to iRet
        // Clear Compiler Info
        Send ClearAll to oCompilerInfo
        //
        Send ClearAll to oScopes
        Send Clear to oScope
        Send Clear to oScopeVariables
        // Reset Tokens
        Send Clear to oTokens
        // Reset Variables
        Send Clear to oVariables
        // Reset Errors
        Send Clear to oErrors
        // Clear Parser Tree
        Send ClearAll to oParserTree
        //
        Set Label of oDFSDebugger to "DataFlex Script Debugger"
        //
    End_Procedure

    Object oOpenDialog1 is a OpenDialog
    
        Set Dialog_Caption to 'Open Script File...'
        Set Filter_String to 'DataFlex Script Source|*.ds|DataFlex Script Package|*.dp|DataFlex Script Executable|*.de|All Files|*.*'
        Set Initial_Folder to 'C:\'

        Procedure DoCallOpenDialog
            Boolean bOk
            Handle hoWorkspace
            String sDataPath sFileTitle sFileName
            Get phoWorkspace of oApplication to hoWorkspace
            Get psDataPath of hoWorkspace to sDataPath
            Set Initial_Folder to sDataPath
            Get Show_Dialog to bOk
            If (bOk) Begin
                Get File_Title to sFileTitle
                Get File_Name  to sFileName
                Send mScriptLoad sFileTitle sFileName
            End
        End_Procedure
    
    End_Object

    Object oSaveDialog is a SaveAsDialog
        Set Filter_String to 'DataFlex Script Source|*.ds|DataFlex Script Package|*.dp|All Source|*.ds;*.dp'
        Set Initial_Folder to 'C:\'
        Set Dialog_Caption to 'Save Script File...'
        Set File_Title to 'noname'
        Procedure DoCallOpenDialog
            Boolean bOk
            Handle hoWorkspace
            String sDataPath sFileTitle sFileName
            Get phoWorkspace of oApplication to hoWorkspace
            Get psDataPath of hoWorkspace to sDataPath
            Set Initial_Folder to sDataPath
            Get Show_Dialog to bOk
        End_Procedure
    End_Object

    Procedure mScriptLoad String sFileTitle String sFileName
        String sDataPath
        Integer iSource iRet
        Handle hoWorkspace
        Get phoWorkspace of oApplication to hoWorkspace
        Get psDataPath of hoWorkspace to sDataPath
        Send DoClearDebugger
        Set psScriptSource of oDFScriptor to sFileName
        Set psScriptFile   of oDFScriptor to sFileTitle
        If (Uppercase(sFileTitle) contains ".DE") Begin
            Set Label of oDFSDebugger to ("DataFlex Script Debugger - Executable"*sFileTitle)
            Move 0 to iSource
            Set piExecutable of oDFScriptor to 1
            Get CM_SetReadOnly of oSourceEditor True to iRet
            Get CM_Settext of oSourceEditor "*** Executable (Compiled) Script File ***" to iRet
        End
        If (Uppercase(sFileTitle) contains ".DS") Begin
            Set Label of oDFSDebugger to ("DataFlex Script Debugger - "+sFileTitle)
            Move 1 to iSource
        End
        If (Uppercase(sFileTitle) contains ".JS") Begin
            Set Label of oDFSDebugger to ("DataFlex Script Debugger - "+sFileTitle)
            Move 1 to iSource
        End
        If iSource Begin
            Get CM_SetReadOnly  of oSourceEditor False      to iSource
            Get CM_OpenFile     of oSourceEditor sFileName  to iSource
        End
    End_Procedure
    
    Procedure mScriptOpen
        Send DoClearDebugger
        Send DoCallOpenDialog to oOpenDialog1
        Send mScriptCompile
    End_Procedure

    Procedure mScriptNew
        Send DoClearDebugger
    End_Procedure

    Procedure mScriptRun
        Send Delete_Data to oDFScriptor
        If (psScriptSource(oDFScriptor(Self))="") Send mScriptOpen
        Send mScriptSave
        Send Compile to oDFScriptor
        Send Add_Compiler_Info  to oDFScriptor 6 ("---- Running Script in Debugger ----")
        Send Add_Compiler_Info  to oDFScriptor 1 (psScriptSource(oDFScriptor(Self)))
        Send Add_Compiler_Info  to oDFScriptor 4 ("---- Done ----")
        Send LoadCompileInfo    to oCompilerInfo
        Send ClearAll           to oParserTree
        Send LoadScriptFiles    to oParserTree
        Send DebuggerInfo       to oDFScriptor
        Send DFS_Exec           to oDFScriptor ""
    End_Procedure
    
    Procedure mScriptCompile
        Send mScriptSave
        Send Delete_Data to oDFScriptor
        If (psScriptSource(oDFScriptor(Self))="") Send mScriptOpen
        Send Compile to oDFScriptor
        Send LoadCompileInfo to oCompilerInfo
        Send DebuggerInfo to oDFScriptor
        Send ClearAll  to oParserTree
        Send LoadScriptFiles to oParserTree
    End_Procedure
    
    Procedure mScriptBuild
        tCompilerInfo[] ltCompilerInfo
        If (psScriptSource(oDFScriptor(Self))<>"") Begin
            Send ClearAll to oCompilerInfo
            Set  ptCompilerInfo  of oDFScriptor to ltCompilerInfo
            Send Compile to oDFScriptor
            If (piErrorsCount(oDFScriptor(Self))=0) ;
                Send Save_Executable to oDFScriptor
            Send LoadCompileInfo to oCompilerInfo
        End
    End_Procedure

    Procedure mScriptSave
        Integer iRetVal
        String  sSource sTitle
        Get psScriptSource  of (oDFScriptor(Self)) to sSource
        Get psScriptFile    of (oDFScriptor(Self)) to sTitle
        If (sSource="") Begin
            Send DoCallOpenDialog of oSaveDialog
            Get File_Title of oSaveDialog to sTitle
            Get File_Name  of oSaveDialog to sSource
            If (sSource="") Procedure_Return
            Get CM_SaveFile of oSourceEditor sSource 0 to iRetVal
            If (iRetVal=1) Begin
                Set Label of oDFSDebugger to ("DataFlex Script Debugger - "+sTitle)
                Set psScriptSource  of (oDFScriptor(Self)) to sSource
                Set psScriptFile    of (oDFScriptor(Self)) to sTitle
            End
        End
        If (CM_IsModified(oSourceEditor(Self))) Begin
            Get CM_SaveFile of oSourceEditor sSource 0 to iRetVal
            If (iRetVal=1) ;
                Set Label of oDFSDebugger to ("DataFlex Script Debugger - "+sTitle)
        End
    End_Procedure
    
End_Object

