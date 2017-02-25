// DataFlex Scriptor constants
// Sergey V. Natarov
//

// Version Prefix
Define DFS_VERSION for "DFS002"

Define DFS_DESKTOP for 0
Global_Variable Integer DFS$CURRENT$SCOPE
Global_Variable Integer giScript$Return$Flag

// Init
Move DFS_DESKTOP    to DFS$CURRENT$SCOPE
Move 0              to giScript$Return$Flag

// File Structure
Struct tDFSFile
    String  sFileName
    String  sMethod
    Integer iDepth
    Integer iLine
End_Struct

// DFScriptor Tokens Structure
Struct tDFSToken
    Integer iLine       // Source Line No
    Integer iColumn     // Source Column No
    Integer iSymbol     // Symbol ID
    Integer iIndex      // Variable Index (DFS_ID) if any
    String  sFile       // Source File Name
    String  sImage      // Image of the token
End_Struct

Struct tDFSDataFiles
    String sFileName
    Integer iFileNumber
End_Struct

// Variables Storage
Struct tDFSVariable
    String              sName       // "iTest"
    Integer             iScope      // Scope of variable
    Integer             iType       // DFS_INTEGER
    Integer             iLine       // 18
    Integer             iColumn     // 10
    Integer             iDimension  // 0|1|2|3|4|5
    String              sValue      // 25
    String[]            saValue1
    String[][]          saValue2
    String[][][]        saValue3
    String[][][][]      saValue4
    String[][][][][]    saValue5
End_Struct

Struct tDFSScope
    String         sName            // Scope (Subscript) Name
    Integer        iType            // 0=Main Script, 1=Procedure, 2=Function, 3=Object
    Integer        iNumArguments    // Number of Arguments scope can receive
    Integer        iReturnType      // Scope return type (DFS_INTEGER, DFS_STRING etc)
    Integer        iReturnDimension // Return type dimension ([], [][], ... etc)
    tDFSToken[]    atTokens         // Scope (Subscript) Tokens
End_Struct

Struct tDFSCharSet
    String sName
    String sValue
End_Struct

Struct tDFSSymbol
    Integer iSymbol
    String  sType
    String  sDescription
End_Struct

Struct tCompilerInfo
    Integer iLevel
    String  sInfo
End_Struct

Struct tDFSError
    Integer iNumber
    Integer iLine
    Integer iErrLine
    String  sText
    String  sFile
End_Struct

//???
Struct tDFSAppObjects
    Handle hoObject
    String sName
End_Struct

tDFSToken[]     gtDFSTokens
tDFSDataFiles[] gtDFSDataFiles
tDFSScope[]     gtDFSScopes
tDFSCharSet[]   gtDFSCharSets
tDFSSymbol[]    gtDFSSymbols
Integer[]       giDFSBlockStack

Define dfsCR                for (Character(13))
Define dfsLF                for (Character(10))
Define dfsCRLF              for (Character(13)+Character(10))
Define dfsTAB               for (Character(9))

// DFScriptor Character Sets
Define DFS_STRING_SET   for ('"'+"'")
Define DFS_COMMENT_SET  for ("/"+"/")
Define DFS_DIGIT_SET    for "0123456789"
Define DFS_ID_SET       for "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
Define DFS_ID_HEAD      for (DFS_ID_SET+'_#')
Define DFS_ID_TAIL      for (DFS_ID_SET+DFS_DIGIT_SET+"$._")
Define DFS_REAL_SET     for ".eE"
Define DFS_OPERATOR_SET for "~&*+-/^<=>"
Define DFS_FUNCLIST_SET for ","
Define DFS_TAGSTART_SET for "{"
Define DFS_TAGSTOP_SET  for "}"
Define DFS_SYMBOLS_SET  for (DFS_OPERATOR_SET+"(){}[]"+DFS_FUNCLIST_SET)
Define DFS_CRLF         for (Character(13)+Character(10))
Define DFS_TAB          for (Character(9))

// DFScriptor Symbols
Enum_List
    // Tokens
    Define DFT_EOF       // End of File              (EOF)
    Define DFT_ERROR     // Error                    (ERROR)
    Define DFT_NEWLINE   // End of Line              (EOL)
    Define DFT_COMMENT   // Comment                  {'//'}
    Define DFT_STRING    // String Type Constant     {"String Sample"}
    Define DFT_REAL      // Real Type Constant       {123.004e2}
    Define DFT_NUMBER    // Number Type Constant     {123.45}
    Define DFT_INTEGER   // Integer Type Constant    {123}
    Define DFT_COMMAND   // Command                  {MOVE|IF|OBJECT|WRITE|...}
    Define DFT_ID        // Id                       {Variable, Function, Object...}
    Define DFT_OPERATOR  // Operator                 {+, -, /, ~, >, <...}
    Define DFT_EXPSTART  // Start of Expression      {'('}
    Define DFT_EXPSTOP   // End of Expression        {')'}
    Define DFT_DIMSTART  // Native Array Dimension   {'['}
    Define DFT_DIMSTOP   // Native Array Dimension   {']'}
    Define DFT_TAGSTART  // Start of Tag             {'{'}
    Define DFT_TAGSTOP   // End of Tag               {'}'}
    Define DFT_FUNCLIST  // Function List Separator  {','}
    Define DFT_DIRECTIVE // Compiler Directive       {#IF|#IFDEF|#IFNDEF|#ENDIF|...}
    Define DFT_FILEFIELD // Database feild           {FILE.FIELD}
    Define DFT_SCOPE     // DFScriptor Scope         {Function mSomeMethod etc}
    // Commands
    Define DFC_LOCAL                // *
    Define DFC_GLOBAL_VARIABLE      // *
    Define DFC_STRING               // *
    Define DFC_INTEGER              // *
    Define DFC_NUMBER               // *
    Define DFC_DATE                 // *
    Define DFC_DATETIME             // *
    Define DFC_TIMESPAN             // *
    Define DFC_TIME                 // *
    Define DFC_REAL                 // *
    Define DFC_CHAR                 // *
    Define DFC_UCHAR                // *
    Define DFC_SHORT                // *
    Define DFC_USHORT               // *
    Define DFC_UINTEGER             // *
    Define DFC_BIGINT               // *
    Define DFC_UBIGINT              // *
    Define DFC_ADDRESS              // *
    Define DFC_ROWID                // *
    Define DFC_VARIANT              // *
    Define DFC_OPEN                 // *
    Define DFC_DEFINE               // *
    //
    // Scope Start
    Define DFC_WHILE                // *
    Define DFC_FOR                  // *
    Define DFC_REPEAT               // *
    Define DFC_BEGIN                // *
    Define DFC_FUNCTION             // *
    Define DFC_PROCEDURE            // *
    Define DFC_OBJECT               // *
    Define DFC_CLASS                // *
    //
    // Scope Stop
    Define DFC_LOOP                 // *
    Define DFC_UNTIL                // *
    Define DFC_END                  // *
    Define DFC_END_FUNCTION         // *
    Define DFC_END_PROCEDURE        // *
    Define DFC_END_OBJECT           // *
    Define DFC_END_CLASS            // *
    //
    Define DFC_PROPERTY
    Define DFC_IMPORT_CLASS_PROTOCOL
    Define DFC_REGISTER_OBJECT
    //
    Define DFC_IF                   // *
    Define DFC_IFNOT                // *
    Define DFC_ELSE                 // *
    Define DFC_BREAK                // ?
    //
    Define DFC_REGISTER_PROCEDURE
    Define DFC_REGISTER_FUNCTION
    Define DFC_FUNCTION_RETURN      // *
    Define DFC_PROCEDURE_RETURN     // *
    Define DFC_FORWARD
    Define DFC_DELEGATE
    Define DFC_BROADCAST
    Define DFC_SET                  // *
    Define DFC_GET                  // *
    Define DFC_SEND                 // *
    Define DFC_GET_ATTRIBUTE        // *
    Define DFC_SET_ATTRIBUTE        // *
    Define DFC_SYSDATE              // *
    // MOVE Commands
    Define DFC_MOVE$START
        Define DFC_MOVE             // *
        Define DFC_CALC             // *
        Define DFC_ADD              // *
        Define DFC_SUBTRACT         // *
        Define DFC_INCREMENT        // *
        Define DFC_DECREMENT        // *
        Define DFC_INDICATE         // *
    Define DFC_MOVE$STOP
    // DB Commands
    Define DFC_DB$START
        Define DFC_CLOSE            // *
        Define DFC_REREAD           // *
        Define DFC_LOCK             // *
        Define DFC_UNLOCK           // *
        Define DFC_CLEAR            // *
        Define DFC_SAVE             // *
        Define DFC_SAVERECORD       // *
        Define DFC_DELETE           // *
        Define DFC_RELATE           // *
        Define DFC_ATTACH           // *
    Define DFC_DB$STOP
    Define DFC_FIND                 // *
    Define DFC_BEGIN_TRANSACTION    // *
    Define DFC_END_TRANSACTION      // *
    Define DFC_STRUCTURE_START      // *
    Define DFC_STRUCTURE_END        // *
    Define DFC_STRUCTURE_ABORT      // *
    // IO commands
    Define DFC_IO$START
        Define DFC_SHOW             // *
        Define DFC_SHOWLN           // *
        Define DFC_WRITE            // *
        Define DFC_WRITELN          // *
        Define DFC_WRITE_HEX        // *
        Define DFC_READ             // *
        Define DFC_READLN           // *
        Define DFC_READ_BLOCK       // *
        Define DFC_READ_HEX         // *
        Define DFC_DIRECT_OUTPUT    // *
        Define DFC_DIRECT_INPUT     // *
        Define DFC_APPEND_OUTPUT    // *
        Define DFC_CLOSE_INPUT      // *
        Define DFC_CLOSE_OUTPUT     // *
    Define DFC_IO$STOP
    // Other
    Define DFC_USE                  // *
    Define DFC_ERROR                // *
    Define DFC_SCRIPT_RETURN        // *
    Define DFC_ABORT                // *
    Define DFC_CMDLINE              // *
    Define DFC_SLEEP                // *
    // Directives
    Define DFD_IF
    Define DFD_IFDEF
    Define DFD_IFNDEF
    Define DFD_ELSE
    Define DFD_ENDIF
    Define DFD_REPLACE
    Define DFD_REM
    Define DFD_ERROR
    Define DFD_INCLUDE
    // Types
    Define DFS_STRING
    Define DFS_INTEGER 
    Define DFS_NUMBER  
    Define DFS_DATE    
    Define DFS_DATETIME
    Define DFS_TIMESPAN
    Define DFS_TIME    
    Define DFS_REAL    
    Define DFS_CHAR    
    Define DFS_UCHAR   
    Define DFS_SHORT   
    Define DFS_USHORT  
    Define DFS_UINTEGER
    Define DFS_BIGINT  
    Define DFS_UBIGINT 
    Define DFS_ADDRESS 
    Define DFS_ROWID   
    Define DFS_VARIANT 
    Define DFS_FILE    
    Define DFS_CONSTANT
    Define DFS_CLASS
    // Operators
    Define DFO_OP$START
        Define DFO_GT
        Define DFO_GE
        Define DFO_LT
        Define DFO_LE
        Define DFO_EQ
        Define DFO_NE
        Define DFO_CONTAINS
        Define DFO_MATCHES
        Define DFO_AND
        Define DFO_OR
        Define DFO_IAND
        Define DFO_IOR
        Define DFO_NOT
    Define DFO_OP$STOP
    // Reserved Keywords
    Define DFW_IS
    Define DFW_A   // +DFW_AN
    Define DFW_AS
    Define DFW_BY
    Define DFW_BYREF
    Define DFW_GLOBAL
    Define DFW_FOR
    Define DFW_RETURNS
    Define DFW_FROM
    Define DFW_TO
    Define DFW_OF
    Define DFW_CHANNEL
    Define DFW_RECURSIVE
    Define DFW_RECURSIVE_UP
    Define DFW_NOSTOP
    Define DFW_RECNUM
    Define DFW_INDEX_1 // Index{.N}
    Define DFW_INDEX_2
    Define DFW_INDEX_3
    Define DFW_INDEX_4
    Define DFW_INDEX_5
    Define DFW_INDEX_6
    Define DFW_INDEX_7
    Define DFW_INDEX_8
    Define DFW_INDEX_9
    Define DFW_INDEX_10
    Define DFW_INDEX_11
    Define DFW_INDEX_12
    Define DFW_INDEX_13
    Define DFW_INDEX_14
    Define DFW_INDEX_15
    Define DFW_TRUE
    Define DFW_FALSE
    Define DFW_FOUND
    Define DFW_SEQEOF
    Define DFW_SEQEOL
    Define DFW_ERR
    Define DFW_AT
    Define DFW_ITEM
    Define DFW_FIELD
    Define DFW_FILE_FIELD
    Define DFW_SELF  // +DFW_CURRENT_OBJECT
    Define DFW_DF_ALL 
    Define DFW_DF_TEMPORARY
    Define DFW_DF_PERMANENT
    // Built-in Functions
    Define DFF_LIST$START
    Define DFF_Abs
    Define DFF_Acos
    Define DFF_Append
    Define DFF_Ascii
    Define DFF_Asin
    Define DFF_Atan
    Define DFF_Center
    Define DFF_Character
    Define DFF_Cos
    Define DFF_Date
    Define DFF_Eval
    Define DFF_Exp
    Define DFF_Hi
    Define DFF_If
    Define DFF_Insert
    Define DFF_Integer
    Define DFF_Left
    Define DFF_Length
    Define DFF_Log
    Define DFF_Low
    Define DFF_Lowercase
    Define DFF_Ltrim
    Define DFF_Mid
    Define DFF_Mod
    Define DFF_Not
    Define DFF_Number
    Define DFF_Overstrike
    Define DFF_Pad
    Define DFF_Pos
    Define DFF_Random
    Define DFF_Real
    Define DFF_Remove
    Define DFF_Repeat
    Define DFF_Replace
    Define DFF_Replaces
    Define DFF_Right
    Define DFF_Round
    Define DFF_Rtrim
    Define DFF_Sin
    Define DFF_Sqrt
    Define DFF_String
    Define DFF_Tan
    Define DFF_Trim
    Define DFF_Uppercase
    Define DFF_CurrentDateTime
    Define DFF_DateGetDay
    Define DFF_DateGetDayofWeek
    Define DFF_DateGetDayofYear
    Define DFF_DateGetHour
    Define DFF_DateGetMinute
    Define DFF_DateGetMonth
    Define DFF_DateGetSecond
    Define DFF_DateGetYear
    Define DFF_DateSetDay
    Define DFF_DateSetHour
    Define DFF_DateSetMinute
    Define DFF_DateSetMonth
    Define DFF_DateSetSecond
    Define DFF_DateSetYear
    Define DFF_IsDateValid
    Define DFF_SpanDays
    Define DFF_SpanHours
    Define DFF_SpanMinutes
    Define DFF_SpanSeconds
    Define DFF_SpanTotalDays
    Define DFF_SpanTotalHours
    Define DFF_SpanTotalMinutes
    Define DFF_SpanTotalSeconds
    Define DFF_Addressof
    Define DFF_Cast
    Define DFF_Convert
    Define DFF_InvokeXML
    Define DFF_Storec
    Define DFF_Storew
    Define DFF_Storedw
    Define DFF_Derefc
    Define DFF_Derefw
    Define DFF_Derefdw
    Define DFF_MemCopy
    Define DFF_MemSet
    Define DFF_IsSameCOMObject
    Define DFF_IsNullCOMObject
    Define DFF_NullCOMObject
    Define DFF_FindByRowId
    Define DFF_GetRowId
    Define DFF_NullRowId
    Define DFF_IsNullRowId
    Define DFF_IsSameRowId
    Define DFF_SerializeRowId
    Define DFF_DeSerializeRowId
    Define DFF_SizeOfArray
    Define DFF_ResizeArray
    Define DFF_CStringLength
    Define DFF_SizeOfType
    Define DFF_BinarySearchArray
    Define DFF_CopyArray
    Define DFF_CountArray
    Define DFF_FillArray
    Define DFF_MinArray
    Define DFF_MaxArray
    Define DFF_ReverseArray
    Define DFF_SearchArray
    Define DFF_ShuffleArray
    Define DFF_SortArray
    Define DFF_RemoveFromArray
    Define DFF_InsertInArray
    Define DFF_RightPos
    Define DFF_LIST$STOP
End_Enum_List

Define DFS_BOOLEAN  for DFS_INTEGER
Define DFS_HANDLE   for DFS_INTEGER
Define DFS_POINTER  for DFS_INTEGER
Define DFC_BOOLEAN  for DFC_INTEGER
Define DFC_HANDLE   for DFC_INTEGER
Define DFC_POINTER  for DFC_INTEGER

// Tables
/CHARHDR
Name             Set
---------------------------------------------------------------------------------------------
/CHARTBL
_______________  ____________________________________________________________________________
/SYMHDR
Symbol    Type             Value
---------------------------------------------------------------------------------------------
/SYMTBL
_____.    _____________    __________________________________________________________________
/TOKENHDR
  Token  File                    Line  Column  Symbol    Image
---------------------------------------------------------------------------------------------
/TOKENTBL
______.  ____________________ ______.  _____.  _____.    ____________________________________
/VARTBLHDR
Name                 Scope Type       Dimension    Line   Col Symbol Image
---------------------------------------------------------------------------------------------
/VARTBL
____________________ ____. __________ __________ _____. ____. _____. _________________________________________________________________________
/*


Procedure dfsStaticLoadDataFiles
    Handle hTable
    String sTable
    Integer iSize
    Move 0 To hTable
    Repeat
        Get_Attribute DF_FILE_NEXT_USED Of hTable To hTable
        If (hTable > 0) Begin
            Move (SizeOfArray(gtDFSDataFiles)) To iSize
            Move hTable To gtDFSDataFiles[iSize].iFileNumber
            Get_Attribute DF_FILE_LOGICAL_NAME Of hTable To sTable
            Uppercase sTable To gtDFSDataFiles[iSize].sFileName
        End
    Until (hTable = 0)
End_Procedure

Procedure dfsStaticLoadCharSets
    Move "String"           to gtDFSCharSets[0].sName
    Move ('" ' + "'")       to gtDFSCharSets[0].sValue
    Move "Comment"          to gtDFSCharSets[1].sName
    Move ("//")             to gtDFSCharSets[1].sValue
    Move "Digit"            to gtDFSCharSets[2].sName
    Move DFS_DIGIT_SET      to gtDFSCharSets[2].sValue
    Move "Alpha"            to gtDFSCharSets[3].sName
    Move DFS_ID_SET         to gtDFSCharSets[3].sValue
    Move "ID Head"          to gtDFSCharSets[4].sName
    Move DFS_ID_HEAD        to gtDFSCharSets[4].sValue
    Move "ID Tail"          to gtDFSCharSets[5].sName
    Move DFS_ID_TAIL        to gtDFSCharSets[5].sValue
    Move "Real"             to gtDFSCharSets[6].sName
    Move DFS_REAL_SET       to gtDFSCharSets[6].sValue
    Move "Operator"         to gtDFSCharSets[7].sName
    Move DFS_OPERATOR_SET   to gtDFSCharSets[7].sValue
    Move "List"             to gtDFSCharSets[8].sName
    Move DFS_FUNCLIST_SET   to gtDFSCharSets[8].sValue
    Move "Tags"             to gtDFSCharSets[9].sName
    Move "{ }"              to gtDFSCharSets[9].sValue
    Move "Expresions"       to gtDFSCharSets[10].sName
    Move "( )"              to gtDFSCharSets[10].sValue
    Move "Arrays"           to gtDFSCharSets[11].sName
    Move "[ ]"              to gtDFSCharSets[11].sValue
    Move "CRLF"             to gtDFSCharSets[12].sName
    Move "(13)(10)"         to gtDFSCharSets[12].sValue
    Move "TAB"              to gtDFSCharSets[13].sName
    Move "(9)"              to gtDFSCharSets[13].sValue
End_Procedure


Procedure dfsAddStaticSymbol Integer iSymbol String sType String sDescription
    Integer iCount
    Move (SizeOfArray(gtDFSSymbols))    to iCount
    Move iSymbol                        to gtDFSSymbols[iCount].iSymbol
    Move sType                          to gtDFSSymbols[iCount].sType
    Move sDescription                   to gtDFSSymbols[iCount].sDescription
End_Procedure
Procedure dfsStaticLoadSymbols
    Send dfsAddStaticSymbol DFT_EOF           "Token"     "(End-Of-File)"
    Send dfsAddStaticSymbol DFT_ERROR         "Token"     "(ERROR)"
    Send dfsAddStaticSymbol DFT_NEWLINE       "Token"     "(End-Of-Line)"
    Send dfsAddStaticSymbol DFT_COMMENT       "Token"     "(COMMENT)"
    Send dfsAddStaticSymbol DFT_STRING        "Token"     "String Constant ('Test')"
    Send dfsAddStaticSymbol DFT_REAL          "Token"     "Real Constant (123.21e5)"
    Send dfsAddStaticSymbol DFT_NUMBER        "Token"     "Number Constant (123.21)"
    Send dfsAddStaticSymbol DFT_INTEGER       "Token"     "Integer Constant (123)"
    Send dfsAddStaticSymbol DFT_COMMAND       "Token"     "DataFlex Command (MOVE|OPEN...)"
    Send dfsAddStaticSymbol DFT_ID            "Token"     "ID (Variable|Object|Function etc. name)"
    Send dfsAddStaticSymbol DFT_OPERATOR      "Token"     "Operator (+, -, /, >, =...)"
    Send dfsAddStaticSymbol DFT_EXPSTART      "Token"     "Expression Start ('(')"
    Send dfsAddStaticSymbol DFT_EXPSTOP       "Token"     "Expression Stop (')')"
    Send dfsAddStaticSymbol DFT_DIMSTART      "Token"     "Native Array Start ('[')"
    Send dfsAddStaticSymbol DFT_DIMSTOP       "Token"     "Native Array Stop (']')"
    Send dfsAddStaticSymbol DFT_TAGSTART      "Token"     "Tag Start ('{')"
    Send dfsAddStaticSymbol DFT_TAGSTOP       "Token"     "Tag Stop ('}')"
    Send dfsAddStaticSymbol DFT_FUNCLIST      "Token"     "Function List (',')"
    Send dfsAddStaticSymbol DFT_DIRECTIVE     "Token"     "Compiler Directive (#IF|#IFDEF|#IFNDEF|#ENDIF|...)"
    Send dfsAddStaticSymbol DFT_FILEFIELD     "Token"     "DataFlex DataBase Field (FILE.FIELD)"
    Send dfsAddStaticSymbol DFT_SCOPE         "Token"     "DataFlex Scriptor Scope Name"
    // Commands
    Send dfsAddStaticSymbol DFC_LOCAL         "Command"   "DataFlex LOCAL Command"
    Send dfsAddStaticSymbol DFC_GLOBAL_VARIABLE "Command"   "DataFlex GLOBAL_VARIABLE Command"
    Send dfsAddStaticSymbol DFC_STRING        "Command"   "DataFlex STRING Command"
    Send dfsAddStaticSymbol DFC_INTEGER       "Command"   "DataFlex INTEGER Command"
    Send dfsAddStaticSymbol DFC_NUMBER        "Command"   "DataFlex NUMBER Command"
    Send dfsAddStaticSymbol DFC_DATE          "Command"   "DataFlex DATE Command"
    Send dfsAddStaticSymbol DFC_DATETIME      "Command"   "DataFlex DATETIME Command"
    Send dfsAddStaticSymbol DFC_TIMESPAN      "Command"   "DataFlex TIMESPAN Command"
    Send dfsAddStaticSymbol DFC_TIME          "Command"   "DataFlex TIME Command"
    Send dfsAddStaticSymbol DFC_REAL          "Command"   "DataFlex REAL Command"
    Send dfsAddStaticSymbol DFC_CHAR          "Command"   "DataFlex CHAR Command"
    Send dfsAddStaticSymbol DFC_UCHAR         "Command"   "DataFlex UCHAR Command"
    Send dfsAddStaticSymbol DFC_SHORT         "Command"   "DataFlex SHORT Command"
    Send dfsAddStaticSymbol DFC_USHORT        "Command"   "DataFlex USHORT Command"
    Send dfsAddStaticSymbol DFC_UINTEGER      "Command"   "DataFlex UINTEGER Command"
    Send dfsAddStaticSymbol DFC_BIGINT        "Command"   "DataFlex BIGINT Command"
    Send dfsAddStaticSymbol DFC_UBIGINT       "Command"   "DataFlex UBIGINT Command"
    Send dfsAddStaticSymbol DFC_ADDRESS       "Command"   "DataFlex ADDRESS Command"
    Send dfsAddStaticSymbol DFC_ROWID         "Command"   "DataFlex ROWID Command"
    Send dfsAddStaticSymbol DFC_VARIANT       "Command"   "DataFlex VARIANT Command"
    Send dfsAddStaticSymbol DFC_OPEN          "Command"   "DataFlex OPEN Command"
    Send dfsAddStaticSymbol DFC_DEFINE        "Command"   "DataFlex DEFINE Command"
    //
    Send dfsAddStaticSymbol DFC_WHILE         "Command"   "DataFlex WHILE Command"
    Send dfsAddStaticSymbol DFC_FOR           "Command"   "DataFlex FOR Command"
    Send dfsAddStaticSymbol DFC_REPEAT        "Command"   "DataFlex REPEAT Command"
    Send dfsAddStaticSymbol DFC_BEGIN         "Command"   "DataFlex BEGIN Command"
    Send dfsAddStaticSymbol DFC_FUNCTION      "Command"   "DataFlex FUNCTION Command"
    Send dfsAddStaticSymbol DFC_PROCEDURE     "Command"   "DataFlex PROCEDURE Command"
    Send dfsAddStaticSymbol DFC_OBJECT        "Command"   "DataFlex OBJECT Command"
    Send dfsAddStaticSymbol DFC_CLASS         "Command"   "DataFlex CLASS Command"
    //
    Send dfsAddStaticSymbol DFC_LOOP          "Command"   "DataFlex LOOP Command"
    Send dfsAddStaticSymbol DFC_UNTIL         "Command"   "DataFlex UNTIL Command"
    Send dfsAddStaticSymbol DFC_END           "Command"   "DataFlex END Command"
    Send dfsAddStaticSymbol DFC_END_FUNCTION  "Command"   "DataFlex END_FUNCTION Command" 
    Send dfsAddStaticSymbol DFC_END_PROCEDURE "Command"   "DataFlex END_PROCEDURE Command"
    Send dfsAddStaticSymbol DFC_END_OBJECT    "Command"   "DataFlex END_OBJECT Command"
    Send dfsAddStaticSymbol DFC_END_CLASS     "Command"   "DataFlex END_CLASS Command"
    Send dfsAddStaticSymbol DFC_PROPERTY      "Command"   "DataFlex PROPERTY Command"
    Send dfsAddStaticSymbol DFC_IMPORT_CLASS_PROTOCOL ;
                                              "Command"   "DataFlex IMPORT_CLASS_PROTOCOL Command"
    Send dfsAddStaticSymbol DFC_REGISTER_OBJECT "Command"   "DataFlex REGISTER_OBJECT Command"
    //
    Send dfsAddStaticSymbol DFC_IF            "Command"   "DataFlex IF Command"
    Send dfsAddStaticSymbol DFC_IFNOT         "Command"   "DataFlex IFNOT Command"
    Send dfsAddStaticSymbol DFC_ELSE          "Command"   "DataFlex ELSE Command"
    Send dfsAddStaticSymbol DFC_BREAK         "Command"   "DataFlex BREAK Command"
    Send dfsAddStaticSymbol DFC_REGISTER_PROCEDURE "Command"   "DataFlex REGISTER_PROCEDURE Command"
    Send dfsAddStaticSymbol DFC_REGISTER_FUNCTION "Command"   "DataFlex REGISTER_FUNCTION Command"
    Send dfsAddStaticSymbol DFC_FUNCTION_RETURN   "Command"   "DataFlex FUNCTION_RETURN Command"
    Send dfsAddStaticSymbol DFC_PROCEDURE_RETURN  "Command"   "DataFlex PROCEDURE_RETURNS Command"
    Send dfsAddStaticSymbol DFC_FORWARD       "Command"   "DataFlex FORWARD Command"
    Send dfsAddStaticSymbol DFC_DELEGATE      "Command"   "DataFlex DELEGATE Command"
    Send dfsAddStaticSymbol DFC_BROADCAST     "Command"   "DataFlex BROADCAST Command"
    Send dfsAddStaticSymbol DFC_SET           "Command"   "DataFlex SET Command"
    Send dfsAddStaticSymbol DFC_GET           "Command"   "DataFlex GET Command"
    Send dfsAddStaticSymbol DFC_SEND          "Command"   "DataFlex SEND Command"
    Send dfsAddStaticSymbol DFC_GET_ATTRIBUTE "Command"   "DataFlex GET_ATTRIBUTE Command"
    Send dfsAddStaticSymbol DFC_SET_ATTRIBUTE "Command"   "DataFlex SET_ATTRIBUTE Command"
    Send dfsAddStaticSymbol DFC_SYSDATE       "Command"   "DataFlex SYSDATE Command"   
    Send dfsAddStaticSymbol DFC_MOVE          "Command"   "DataFlex MOVE Command"
    Send dfsAddStaticSymbol DFC_CALC          "Command"   "DataFlex CALC Command"
    Send dfsAddStaticSymbol DFC_ADD           "Command"   "DataFlex ADD Command"
    Send dfsAddStaticSymbol DFC_SUBTRACT      "Command"   "DataFlex SUBTRACT Command"   
    Send dfsAddStaticSymbol DFC_INCREMENT     "Command"   "DataFlex INCREMENT Command" 
    Send dfsAddStaticSymbol DFC_DECREMENT     "Command"   "DataFlex DECREMENT Command" 
    Send dfsAddStaticSymbol DFC_INDICATE      "Command"   "DataFlex INDICATE Command" 
    Send dfsAddStaticSymbol DFC_CLOSE         "Command"   "DataFlex CLOSE Command"
    Send dfsAddStaticSymbol DFC_REREAD        "Command"   "DataFlex REREAD Command" 
    Send dfsAddStaticSymbol DFC_LOCK          "Command"   "DataFlex LOCK Command"  
    Send dfsAddStaticSymbol DFC_UNLOCK        "Command"   "DataFlex UNLOCK Command"    
    Send dfsAddStaticSymbol DFC_CLEAR         "Command"   "DataFlex CLEAR Command"
    Send dfsAddStaticSymbol DFC_SAVE          "Command"   "DataFlex SAVE Command"
    Send dfsAddStaticSymbol DFC_SAVERECORD    "Command"   "DataFlex SAVERECORD Command"  
    Send dfsAddStaticSymbol DFC_DELETE        "Command"   "DataFlex DELETE Command" 
    Send dfsAddStaticSymbol DFC_RELATE        "Command"   "DataFlex RELATE Command"  
    Send dfsAddStaticSymbol DFC_ATTACH        "Command"   "DataFlex ATTACH Command"    
    Send dfsAddStaticSymbol DFC_FIND          "Command"   "DataFlex FIND Command"
    Send dfsAddStaticSymbol DFC_BEGIN_TRANSACTION "Command" "DataFlex BEGIN_TRANSACTION Command"
    Send dfsAddStaticSymbol DFC_END_TRANSACTION   "Command" "DataFlex END_TRANSACTION Command"
    Send dfsAddStaticSymbol DFC_STRUCTURE_START   "Command" "DataFlex DFC_STRUCTURE_START Command"
    Send dfsAddStaticSymbol DFC_STRUCTURE_END     "Command" "DataFlex DFC_STRUCTURE_END Command"
    Send dfsAddStaticSymbol DFC_STRUCTURE_ABORT   "Command" "DataFlex DFC_STRUCTURE_ABORT Command"
    Send dfsAddStaticSymbol DFC_SHOW          "Command"   "DataFlex SHOW Command"
    Send dfsAddStaticSymbol DFC_SHOWLN        "Command"   "DataFlex SHOWLN Command"  
    Send dfsAddStaticSymbol DFC_WRITE         "Command"   "DataFlex WRITE Command" 
    Send dfsAddStaticSymbol DFC_WRITELN       "Command"   "DataFlex WRITELN Command"  
    Send dfsAddStaticSymbol DFC_WRITE_HEX     "Command"   "DataFlex WRITE_HEX Command"    
    Send dfsAddStaticSymbol DFC_READ          "Command"   "DataFlex READ Command"
    Send dfsAddStaticSymbol DFC_READLN        "Command"   "DataFlex READLN Command"
    Send dfsAddStaticSymbol DFC_READ_BLOCK    "Command"   "DataFlex READ_BLOCK Command"  
    Send dfsAddStaticSymbol DFC_DIRECT_OUTPUT "Command"   "DataFlex DIRECT_OUTPUT Command" 
    Send dfsAddStaticSymbol DFC_DIRECT_INPUT  "Command"   "DataFlex DIRECT_INPUT Command"  
    Send dfsAddStaticSymbol DFC_APPEND_OUTPUT "Command"   "DataFlex APPEND_OUTPUT Command"    
    Send dfsAddStaticSymbol DFC_CLOSE_INPUT   "Command"   "DataFlex CLOSE_INPUT Command"
    Send dfsAddStaticSymbol DFC_CLOSE_OUTPUT  "Command"   "DataFlex CLOSE_OUTPUT Command"
    Send dfsAddStaticSymbol DFC_USE           "Command"   "DataFlex USE Command"
    Send dfsAddStaticSymbol DFC_ERROR         "Command"   "DataFlex ERROR Command"
    Send dfsAddStaticSymbol DFC_SCRIPT_RETURN "Command"   "DFScriptor SCRIPT_RETURN Command"
    Send dfsAddStaticSymbol DFC_ABORT         "Command"   "DFScriptor ABORT Command"
    Send dfsAddStaticSymbol DFC_CMDLINE       "Command"   "DataFlex CMDLINE Command"
    Send dfsAddStaticSymbol DFC_SLEEP         "Command"   "DataFlex SLEEP Command"
    //
    Send dfsAddStaticSymbol DFD_IF            "Directive" "Compiler #IF Directive"
    Send dfsAddStaticSymbol DFD_IFDEF         "Directive" "Compiler #IFDEF Directive"
    Send dfsAddStaticSymbol DFD_IFNDEF        "Directive" "Compiler #IFNDEF Directive"
    Send dfsAddStaticSymbol DFD_ELSE          "Directive" "Compiler #ELSE Directive"
    Send dfsAddStaticSymbol DFD_ENDIF         "Directive" "Compiler #ENDIF Directive"
    Send dfsAddStaticSymbol DFD_REPLACE       "Directive" "Compiler #REPLACE Directive"
    Send dfsAddStaticSymbol DFD_REM           "Directive" "Compiler #REM Directive"
    Send dfsAddStaticSymbol DFD_ERROR         "Directive" "Compiler #ERROR Directive"
    Send dfsAddStaticSymbol DFD_INCLUDE       "Directive" "Compiler #INCLUDE Directive"
    //
    Send dfsAddStaticSymbol DFS_STRING        "Type"      "String Variable Type (|VI)"
    Send dfsAddStaticSymbol DFS_INTEGER       "Type"      "Integer Variable Type (|VI)"
    Send dfsAddStaticSymbol DFS_BOOLEAN       "Type*"     "Boolean Type (*Defined as Integer)"
    Send dfsAddStaticSymbol DFS_HANDLE        "Type*"     "Handle Type (*Defined as Integer)"
    Send dfsAddStaticSymbol DFS_POINTER       "Type*"     "Pointer Type (*Defined as Integer)"
    Send dfsAddStaticSymbol DFS_NUMBER        "Type"      "Number Variable Type (|VI)"
    Send dfsAddStaticSymbol DFS_DATE          "Type"      "Date Variable Type (|VI)"
    Send dfsAddStaticSymbol DFS_DATETIME      "Type"      "DateTime Variable Type (|VI)"
    Send dfsAddStaticSymbol DFS_TIMESPAN      "Type"      "TimeSpan Variable Type (|VI)"
    Send dfsAddStaticSymbol DFS_TIME          "Type"      "Time Variable Type (|VI)"
    Send dfsAddStaticSymbol DFS_REAL          "Type"      "Real Variable Type (|VI)"
    Send dfsAddStaticSymbol DFS_CHAR          "Type"      "Char Variable Type (|VI)"
    Send dfsAddStaticSymbol DFS_UCHAR         "Type"      "UChar Variable Type (|VI)"
    Send dfsAddStaticSymbol DFS_SHORT         "Type"      "Short Variable Type (|VI)"
    Send dfsAddStaticSymbol DFS_USHORT        "Type"      "UShort Variable Type (|VI)"
    Send dfsAddStaticSymbol DFS_UINTEGER      "Type"      "UInteger Variable Type (|VI)"
    Send dfsAddStaticSymbol DFS_BIGINT        "Type"      "BigInt Variable Type (|VI)"
    Send dfsAddStaticSymbol DFS_UBIGINT       "Type"      "UBigInt Variable Type (|VI)"
    Send dfsAddStaticSymbol DFS_ADDRESS       "Type"      "Address Variable Type (|VI)"
    Send dfsAddStaticSymbol DFS_ROWID         "Type"      "RowID Variable Type (|VI)"
    Send dfsAddStaticSymbol DFS_VARIANT       "Type"      "Variant Variable Type (|VI)"
    Send dfsAddStaticSymbol DFS_FILE          "Type"      "Database File (|FI)"
    Send dfsAddStaticSymbol DFS_CONSTANT      "Type"      "Constant (|CI)"
    Send dfsAddStaticSymbol DFS_CLASS         "Type"      "Class (ID)"
    //
    Send dfsAddStaticSymbol DFO_GT            "Operator"  "DataFlex GT Operator"
    Send dfsAddStaticSymbol DFO_GE            "Operator"  "DataFlex GE Operator"
    Send dfsAddStaticSymbol DFO_LT            "Operator"  "DataFlex LT Operator"
    Send dfsAddStaticSymbol DFO_LE            "Operator"  "DataFlex LE Operator"
    Send dfsAddStaticSymbol DFO_EQ            "Operator"  "DataFlex EQ Operator"
    Send dfsAddStaticSymbol DFO_NE            "Operator"  "DataFlex NE Operator"
    Send dfsAddStaticSymbol DFO_CONTAINS      "Operator"  "DataFlex CONTAINS Operator"
    Send dfsAddStaticSymbol DFO_MATCHES       "Operator"  "DataFlex MATCHES Operator"
    Send dfsAddStaticSymbol DFO_AND           "Operator"  "DataFlex AND Operator"
    Send dfsAddStaticSymbol DFO_OR            "Operator"  "DataFlex OR Operator"
    Send dfsAddStaticSymbol DFO_IAND          "Operator"  "DataFlex IAND Operator"
    Send dfsAddStaticSymbol DFO_IOR           "Operator"  "DataFlex IOR Operator"
    Send dfsAddStaticSymbol DFO_NOT           "Operator"  "DataFlex NOT Operator"
    //
    Send dfsAddStaticSymbol DFW_IS            "Keyword"  "DataFlex IS Reserved Keyword"
    Send dfsAddStaticSymbol DFW_A             "Keyword"  "DataFlex A/AN Reserved Keyword"
    Send dfsAddStaticSymbol DFW_BY            "Keyword"  "DataFlex BY Reserved Keyword"
    Send dfsAddStaticSymbol DFW_BYREF         "Keyword"  "DataFlex BYREF Reserved Keyword"
    Send dfsAddStaticSymbol DFW_GLOBAL        "Keyword"  "DataFlex GLOBAL Reserved Keyword"
    Send dfsAddStaticSymbol DFW_FOR           "Keyword"  "DataFlex FOR Reserved Keyword"
    Send dfsAddStaticSymbol DFW_RETURNS       "Keyword"  "DataFlex RETURNS Reserved Keyword"
    Send dfsAddStaticSymbol DFW_FROM          "Keyword"  "DataFlex FROM Reserved Keyword"
    Send dfsAddStaticSymbol DFW_TO            "Keyword"  "DataFlex TO Reserved Keyword"
    Send dfsAddStaticSymbol DFW_OF            "Keyword"  "DataFlex OF Reserved Keyword"
    Send dfsAddStaticSymbol DFW_CHANNEL       "Keyword"  "DataFlex CHANNEL Reserved Keyword"
    Send dfsAddStaticSymbol DFW_RECURSIVE     "Keyword"  "DataFlex RECURSIVE Reserved Keyword"
    Send dfsAddStaticSymbol DFW_RECURSIVE_UP  "Keyword"  "DataFlex RECURSIVE_UP Reserved Keyword"
    Send dfsAddStaticSymbol DFW_NOSTOP        "Keyword"  "DataFlex NO_STOP Reserved Keyword"
    Send dfsAddStaticSymbol DFW_RECNUM        "Keyword"  "DataFlex RECNUM Reserved Keyword"
    Send dfsAddStaticSymbol DFW_INDEX_1       "Keyword"  "DataFlex INDEX.1 Reserved Keyword"
    Send dfsAddStaticSymbol DFW_INDEX_2       "Keyword"  "DataFlex INDEX.2 Reserved Keyword"
    Send dfsAddStaticSymbol DFW_INDEX_3       "Keyword"  "DataFlex INDEX.3 Reserved Keyword"
    Send dfsAddStaticSymbol DFW_INDEX_4       "Keyword"  "DataFlex INDEX.4 Reserved Keyword"
    Send dfsAddStaticSymbol DFW_INDEX_5       "Keyword"  "DataFlex INDEX.5 Reserved Keyword"
    Send dfsAddStaticSymbol DFW_INDEX_6       "Keyword"  "DataFlex INDEX.6 Reserved Keyword"
    Send dfsAddStaticSymbol DFW_INDEX_7       "Keyword"  "DataFlex INDEX.7 Reserved Keyword"
    Send dfsAddStaticSymbol DFW_INDEX_8       "Keyword"  "DataFlex INDEX.8 Reserved Keyword"
    Send dfsAddStaticSymbol DFW_INDEX_9       "Keyword"  "DataFlex INDEX.9 Reserved Keyword"
    Send dfsAddStaticSymbol DFW_INDEX_10      "Keyword"  "DataFlex INDEX.10 Reserved Keyword"
    Send dfsAddStaticSymbol DFW_INDEX_11      "Keyword"  "DataFlex INDEX.11 Reserved Keyword"
    Send dfsAddStaticSymbol DFW_INDEX_12      "Keyword"  "DataFlex INDEX.12 Reserved Keyword"
    Send dfsAddStaticSymbol DFW_INDEX_13      "Keyword"  "DataFlex INDEX.13 Reserved Keyword"
    Send dfsAddStaticSymbol DFW_INDEX_14      "Keyword"  "DataFlex INDEX.14 Reserved Keyword"
    Send dfsAddStaticSymbol DFW_INDEX_15      "Keyword"  "DataFlex INDEX.15 Reserved Keyword"
    Send dfsAddStaticSymbol DFW_TRUE          "Keyword"  "DataFlex TRUE Reserved Keyword"
    Send dfsAddStaticSymbol DFW_FALSE         "Keyword"  "DataFlex FALSE Reserved Keyword"
    Send dfsAddStaticSymbol DFW_FOUND         "Keyword"  "DataFlex FOUND Reserved Keyword"
    Send dfsAddStaticSymbol DFW_SEQEOF        "Keyword"  "DataFlex SEQEOF Reserved Keyword"
    Send dfsAddStaticSymbol DFW_SEQEOL        "Keyword"  "DataFlex SEQEOL Reserved Keyword"
    Send dfsAddStaticSymbol DFW_ERR           "Keyword"  "DataFlex ERR Reserved Keyword"
    Send dfsAddStaticSymbol DFW_AT            "Keyword"  "DataFlex AT Reserved Keyword"
    Send dfsAddStaticSymbol DFW_ITEM          "Keyword"  "DataFlex ITEM Reserved Keyword"
    Send dfsAddStaticSymbol DFW_FIELD         "Keyword"  "DataFlex FIELD Reserved Keyword"
    Send dfsAddStaticSymbol DFW_FILE_FIELD    "Keyword"  "DataFlex FILE_FIELD Reserved Keyword"
    Send dfsAddStaticSymbol DFW_SELF          "Keyword"  "DataFlex SELF/CURRENT_OBJECT Reserved Keyword"
    Send dfsAddStaticSymbol DFW_DF_ALL        "Keyword"  "DataFlex DF_ALL Reserved Keyword"
    Send dfsAddStaticSymbol DFW_DF_TEMPORARY  "Keyword"  "DataFlex DF_TEMPORARY Reserved Keyword"
    Send dfsAddStaticSymbol DFW_DF_PERMANENT  "Keyword"  "DataFlex DF_PERMANENT Reserved Keyword"
    // Built-in Functions
    Send dfsAddStaticSymbol DFF_LIST$START          "Function" "Start of the DataFlex Built-in Functions List"
    Send dfsAddStaticSymbol DFF_Abs                 "Function" "DataFlex Abs Built-in Function"
    Send dfsAddStaticSymbol DFF_Acos                "Function" "DataFlex Acos Built-in Function"
    Send dfsAddStaticSymbol DFF_Append              "Function" "DataFlex Append Built-in Function"
    Send dfsAddStaticSymbol DFF_Ascii               "Function" "DataFlex Ascii Built-in Function"
    Send dfsAddStaticSymbol DFF_Asin                "Function" "DataFlex Asin Built-in Function"
    Send dfsAddStaticSymbol DFF_Atan                "Function" "DataFlex Atan Built-in Function"
    Send dfsAddStaticSymbol DFF_Center              "Function" "DataFlex Center Built-in Function"
    Send dfsAddStaticSymbol DFF_Character           "Function" "DataFlex Character Built-in Function"
    Send dfsAddStaticSymbol DFF_Cos                 "Function" "DataFlex Cos Built-in Function"
    Send dfsAddStaticSymbol DFF_Date                "Function" "DataFlex Date Built-in Function"
    Send dfsAddStaticSymbol DFF_Eval                "Function" "DataFlex Eval Built-in Function"
    Send dfsAddStaticSymbol DFF_Exp                 "Function" "DataFlex Exp Built-in Function"
    Send dfsAddStaticSymbol DFF_Hi                  "Function" "DataFlex Hi Built-in Function"
    Send dfsAddStaticSymbol DFF_If                  "Function" "DataFlex If Built-in Function"
    Send dfsAddStaticSymbol DFF_Insert              "Function" "DataFlex Insert Built-in Function"
    Send dfsAddStaticSymbol DFF_Integer             "Function" "DataFlex Integer Built-in Function"
    Send dfsAddStaticSymbol DFF_Left                "Function" "DataFlex Left Built-in Function"
    Send dfsAddStaticSymbol DFF_Length              "Function" "DataFlex Length Built-in Function"
    Send dfsAddStaticSymbol DFF_Log                 "Function" "DataFlex Log Built-in Function"
    Send dfsAddStaticSymbol DFF_Low                 "Function" "DataFlex Low Built-in Function"
    Send dfsAddStaticSymbol DFF_Lowercase           "Function" "DataFlex Lowercase Built-in Function"
    Send dfsAddStaticSymbol DFF_Ltrim               "Function" "DataFlex Ltrim Built-in Function"
    Send dfsAddStaticSymbol DFF_Mid                 "Function" "DataFlex Mid Built-in Function"
    Send dfsAddStaticSymbol DFF_Mod                 "Function" "DataFlex Mod Built-in Function"
    Send dfsAddStaticSymbol DFF_Not                 "Function" "DataFlex Not Built-in Function"
    Send dfsAddStaticSymbol DFF_Number              "Function" "DataFlex Number Built-in Function"
    Send dfsAddStaticSymbol DFF_Overstrike          "Function" "DataFlex Overstrike Built-in Function"
    Send dfsAddStaticSymbol DFF_Pad                 "Function" "DataFlex Pad Built-in Function"
    Send dfsAddStaticSymbol DFF_Pos                 "Function" "DataFlex Pos Built-in Function"
    Send dfsAddStaticSymbol DFF_Random              "Function" "DataFlex Random Built-in Function"
    Send dfsAddStaticSymbol DFF_Real                "Function" "DataFlex Real Built-in Function"
    Send dfsAddStaticSymbol DFF_Remove              "Function" "DataFlex Remove Built-in Function"
    Send dfsAddStaticSymbol DFF_Repeat              "Function" "DataFlex Repeat Built-in Function"
    Send dfsAddStaticSymbol DFF_Replace             "Function" "DataFlex Replace Built-in Function"
    Send dfsAddStaticSymbol DFF_Replaces            "Function" "DataFlex Replaces Built-in Function"
    Send dfsAddStaticSymbol DFF_Right               "Function" "DataFlex Right Built-in Function"
    Send dfsAddStaticSymbol DFF_Round               "Function" "DataFlex Round Built-in Function"
    Send dfsAddStaticSymbol DFF_Rtrim               "Function" "DataFlex Rtrim Built-in Function"
    Send dfsAddStaticSymbol DFF_Sin                 "Function" "DataFlex Sin Built-in Function"
    Send dfsAddStaticSymbol DFF_Sqrt                "Function" "DataFlex Sqrt Built-in Function"
    Send dfsAddStaticSymbol DFF_String              "Function" "DataFlex String Built-in Function"
    Send dfsAddStaticSymbol DFF_Tan                 "Function" "DataFlex Tan Built-in Function"
    Send dfsAddStaticSymbol DFF_Trim                "Function" "DataFlex Trim Built-in Function"
    Send dfsAddStaticSymbol DFF_Uppercase           "Function" "DataFlex Uppercase Built-in Function"
    Send dfsAddStaticSymbol DFF_CurrentDateTime     "Function" "DataFlex CurrentDateTime Built-in Function"
    Send dfsAddStaticSymbol DFF_DateGetDay          "Function" "DataFlex DateGetDay Built-in Function"
    Send dfsAddStaticSymbol DFF_DateGetDayofWeek    "Function" "DataFlex DateGetDayofWeek Built-in Function"
    Send dfsAddStaticSymbol DFF_DateGetDayofYear    "Function" "DataFlex DateGetDayofYear Built-in Function"
    Send dfsAddStaticSymbol DFF_DateGetHour         "Function" "DataFlex DateGetHour Built-in Function"
    Send dfsAddStaticSymbol DFF_DateGetMinute       "Function" "DataFlex DateGetMinute Built-in Function"
    Send dfsAddStaticSymbol DFF_DateGetMonth        "Function" "DataFlex DateGetMonth Built-in Function"
    Send dfsAddStaticSymbol DFF_DateGetSecond       "Function" "DataFlex DateGetSecond Built-in Function"
    Send dfsAddStaticSymbol DFF_DateGetYear         "Function" "DataFlex DateGetYear Built-in Function"
    Send dfsAddStaticSymbol DFF_DateSetDay          "Function" "DataFlex DateSetDay Built-in Function"
    Send dfsAddStaticSymbol DFF_DateSetHour         "Function" "DataFlex DateSetHour Built-in Function"
    Send dfsAddStaticSymbol DFF_DateSetMinute       "Function" "DataFlex DateSetMinute Built-in Function"
    Send dfsAddStaticSymbol DFF_DateSetMonth        "Function" "DataFlex DateSetMonth Built-in Function"
    Send dfsAddStaticSymbol DFF_DateSetSecond       "Function" "DataFlex DateSetSecond Built-in Function"
    Send dfsAddStaticSymbol DFF_DateSetYear         "Function" "DataFlex DateSetYear Built-in Function"
    Send dfsAddStaticSymbol DFF_IsDateValid         "Function" "DataFlex IsDateValid Built-in Function"
    Send dfsAddStaticSymbol DFF_SpanDays            "Function" "DataFlex SpanDays Built-in Function"
    Send dfsAddStaticSymbol DFF_SpanHours           "Function" "DataFlex SpanHours Built-in Function"
    Send dfsAddStaticSymbol DFF_SpanMinutes         "Function" "DataFlex SpanMinutes Built-in Function"
    Send dfsAddStaticSymbol DFF_SpanSeconds         "Function" "DataFlex SpanSeconds Built-in Function"
    Send dfsAddStaticSymbol DFF_SpanTotalDays       "Function" "DataFlex SpanTotalDays Built-in Function"
    Send dfsAddStaticSymbol DFF_SpanTotalHours      "Function" "DataFlex SpanTotalHours Built-in Function"
    Send dfsAddStaticSymbol DFF_SpanTotalMinutes    "Function" "DataFlex SpanTotalMinutes Built-in Function"
    Send dfsAddStaticSymbol DFF_SpanTotalSeconds    "Function" "DataFlex SpanTotalSeconds Built-in Function"
    Send dfsAddStaticSymbol DFF_Addressof           "Function" "DataFlex Addressof Built-in Function"
    Send dfsAddStaticSymbol DFF_Cast                "Function" "DataFlex Cast Built-in Function"
    Send dfsAddStaticSymbol DFF_Convert             "Function" "DataFlex Convert Built-in Function"
    Send dfsAddStaticSymbol DFF_InvokeXML           "Function" "DataFlex InvokeXML Built-in Function"
    Send dfsAddStaticSymbol DFF_Storec              "Function" "DataFlex Storec Built-in Function"
    Send dfsAddStaticSymbol DFF_Storew              "Function" "DataFlex Storew Built-in Function"
    Send dfsAddStaticSymbol DFF_Storedw             "Function" "DataFlex Storedw Built-in Function"
    Send dfsAddStaticSymbol DFF_Derefc              "Function" "DataFlex Derefc Built-in Function"
    Send dfsAddStaticSymbol DFF_Derefw              "Function" "DataFlex Derefw Built-in Function"
    Send dfsAddStaticSymbol DFF_Derefdw             "Function" "DataFlex Derefdw Built-in Function"
    Send dfsAddStaticSymbol DFF_MemCopy             "Function" "DataFlex MemCopy Built-in Function"
    Send dfsAddStaticSymbol DFF_MemSet              "Function" "DataFlex MemSet Built-in Function"
    Send dfsAddStaticSymbol DFF_IsSameCOMObject     "Function" "DataFlex IsSameCOMObject Built-in Function"
    Send dfsAddStaticSymbol DFF_IsNullCOMObject     "Function" "DataFlex IsNullCOMObject Built-in Function"
    Send dfsAddStaticSymbol DFF_NullCOMObject       "Function" "DataFlex NullCOMObject Built-in Function"
    Send dfsAddStaticSymbol DFF_FindByRowId         "Function" "DataFlex FindByRowId Built-in Function"
    Send dfsAddStaticSymbol DFF_GetRowId            "Function" "DataFlex GetRowId Built-in Function"
    Send dfsAddStaticSymbol DFF_NullRowId           "Function" "DataFlex NullRowId Built-in Function"
    Send dfsAddStaticSymbol DFF_IsNullRowId         "Function" "DataFlex IsNullRowId Built-in Function"
    Send dfsAddStaticSymbol DFF_IsSameRowId         "Function" "DataFlex IsSameRowId Built-in Function"
    Send dfsAddStaticSymbol DFF_SerializeRowId      "Function" "DataFlex SerializeRowId Built-in Function"
    Send dfsAddStaticSymbol DFF_DeSerializeRowId    "Function" "DataFlex DeSerializeRowId Built-in Function"
    Send dfsAddStaticSymbol DFF_SizeOfArray         "Function" "DataFlex SizeOfArray Built-in Function"
    Send dfsAddStaticSymbol DFF_ResizeArray         "Function" "DataFlex ResizeArray Built-in Function"
    Send dfsAddStaticSymbol DFF_CStringLength       "Function" "DataFlex CStringLength Built-in Function"
    Send dfsAddStaticSymbol DFF_SizeOfType          "Function" "DataFlex SizeOfType Built-in Function"
    Send dfsAddStaticSymbol DFF_BinarySearchArray   "Function" "DataFlex BinarySearchArray Built-in Function"
    Send dfsAddStaticSymbol DFF_CopyArray           "Function" "DataFlex CopyArray Built-in Function"
    Send dfsAddStaticSymbol DFF_CountArray          "Function" "DataFlex CountArray Built-in Function"
    Send dfsAddStaticSymbol DFF_FillArray           "Function" "DataFlex FillArray Built-in Function"
    Send dfsAddStaticSymbol DFF_MinArray            "Function" "DataFlex MinArray Built-in Function"
    Send dfsAddStaticSymbol DFF_MaxArray            "Function" "DataFlex MaxArray Built-in Function"
    Send dfsAddStaticSymbol DFF_ReverseArray        "Function" "DataFlex ReverseArray Built-in Function"
    Send dfsAddStaticSymbol DFF_SearchArray         "Function" "DataFlex SearchArray Built-in Function"
    Send dfsAddStaticSymbol DFF_ShuffleArray        "Function" "DataFlex ShuffleArray Built-in Function"
    Send dfsAddStaticSymbol DFF_SortArray           "Function" "DataFlex SortArray Built-in Function"
    Send dfsAddStaticSymbol DFF_RemoveFromArray     "Function" "DataFlex RemoveFromArray Built-in Function"
    Send dfsAddStaticSymbol DFF_InsertInArray       "Function" "DataFlex InsertInArray Built-in Function"
    Send dfsAddStaticSymbol DFF_RightPos            "Function" "DataFlex RightPos Built-in Function"
    Send dfsAddStaticSymbol DFF_LIST$STOP           "Function" "End of the DataFlex Built-in Functions List"
End_Procedure

Procedure dfsLoadStaticData
    Send dfsStaticLoadDataFiles
    Send dfsStaticLoadCharSets
    Send dfsStaticLoadSymbols
    Move DFS_DESKTOP to DFS$CURRENT$SCOPE
End_Procedure
Send dfsLoadStaticData
