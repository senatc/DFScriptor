DFScriptor v2.0, (C) 2017, Just for Fun by Sergey V. Natarov

What's New
----------

1. General Changes

   1.1. Built using DataFlex 18.x
   1.2. Gold Parser removed from the Project as old DLL is not compatible with DF11+ and new DLL does not implement parser features in full.
   1.3. Parser now was implemented in DataFlex.
   1.4. Brand new DFS Debugger with Codemax control.
   1.5. New options Script "Compile" and "Build".
        1.4.1. Script pre-compiler implemented.
        1.4.2. Script EXE builder implemented (script now can be compiled to DFS executable file .DE). Script executable may be loaded and executed stright away.
        1.4.3. Script Pre-Compiler produces Script .PRN and .TBL files. TBL is a script tables output, including Variables, Tokens, Scopes.
   
2. Language Changes

   2.1. Tags are now supported ({Description="Test"}).
   2.2. Native arrays were implemented (Structs are not supported so far). Parser only for the moment.
   2.3. Most of commands support expressions evaluation (in v1, eg. IO commands did not support expressions).
   2.4. IO Commands now support IO Channels.
   2.5. Get/Set commands are implemented (v1 had SEND command only, GET command required a call using MOVE expression).
   2.6. More data types were immplemented.
   2.7. Script Procedure/Functions were implemented (Can be used as sub-script with Calls from the script or outside).
   2.8. Number of compiler directives implemented (including USE and #INCLUDE, #REM, #ERROR).
   2.9. Objects can now be instantiated using both "Create" function and OBJECT commands. Classes are not supported and must be provided from the parent application. Objects augmentation is not supported so far as well. So object command should be used to create object only.
   2.10. LOCK and ATTACH commands implemented.
   2.11. Database related commands now support command options like "DF_ALL" (includng CLOSE modes) and list of database files.
   2.12. Increment/Decrement commands were implemented.
   2.13. Repeat/Until/Loop statements were implemented.
   2.14. ADD/SUBTRACT commands were implemented.
   2.15. INDICATE command implemented for the pre-defined indicators FOUND|SEQEOF|SEQEOL|ERR
   2.16. IF/ELSE commands improved to support blocks, cascade IF/ELSE and constructions like "ELSE IF"

3. Samples

   3.1. DataFlex Scriptor Console (see DFS Debugger Tab).
   3.2. Dynamic application menu items, based on the DFScriptor.
   3.3. Number of sample scripts are provided (Input/Output, If/Else, Database, Attributes etc.).


File Extensions
---------------

Default folder is [Workspace]\Data
*.DS - DataFlex Script Source (like .SRC)
*.DP - DataFlex Script Package (like .PKG)
*.DE - DataFlex Compiled Script (like .EXE)

*.PRN - Script PRN file
*.TBL - Script tables (for the Debug purposes)


DataFlex Script Debugger
------------------------

Basic debugger added to simplify script creation.


Base Workspace
--------------

Order Sample is used as a base Workspace.


Data types
----------

Base (+Define/Constants+Data files):
INTEGER | NUMBER | DATE | REAL | STRING

Extended types (Mostly Parser Only):
DATETIME | TIMESPAN | TIME | REAL | CHAR | UCHAR | SHORT | USHORT | UINTEGER | BIGINT | UBIGINT | ADDRESS | ROWID | VARIANT 


Supported commands
------------------

Scopes:
WHILE | FOR | REPEAT | BEGIN | FUNCTION | PROCEDURE | OBJECT (Create Object only) | CLASS (Parser only)
LOOP | UNTIL | END | END_FUNCTION | END_PROCEDURE | END_OBJECT (Create Object only) | END_CLASS (Parser only) 
FUNCTION_RETURN | PROCEDURE_RETURN | SCRIPT_RETURN (Script only)

Logical operations:
IF | IFNOT | ELSE 

Methods and Attributes:
SET | GET | SEND | GET_ATTRIBUTE | SET_ATTRIBUTE | SYSDATE | 

Assign:
MOVE | CALC | ADD | SUBTRACT | INCREMENT | DECREMENT | INDICATE (Indicators as a type are not supported, Built-in only)

Database Related:
CLOSE | REREAD | LOCK | UNLOCK | CLEAR | SAVE | SAVERECORD | DELETE | RELATE | ATTACH | FIND 
BEGIN_TRANSACTION | END_TRANSACTION

Input/Output:
SHOW | SHOWLN | WRITE | WRITELN | WRITE_HEX | READ | READLN | READ_BLOCK | READ_HEX
DIRECT_OUTPUT | DIRECT_INPUT | APPEND_OUTPUT | CLOSE_INPUT | CLOSE_OUTPUT 

General Purposes:
USE | ERROR | ABORT (Windows only, Confirmation provided) | SLEEP 


Directives
----------

USE | #REM | #ERROR | #INCLUDE

