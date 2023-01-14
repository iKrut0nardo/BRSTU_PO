                       README.TXT
**********************************************************
                   Release Notes for
 
    Microsoft(R) FoxPro(R) for MS-DOS(R) Version 2.6

    (C)1994 Microsoft Corporation. All Rights Reserved.

This README provides information not contained in the
FoxPro online Help file or print documentation, and provides
corrections to both. Information in Help is more current than
information in the print documentation. 
**********************************************************
========
CONTENTS
========

Part   Description
----   -----------
 1     New Features in FoxPro 2.6
 2     Installation Notes
 3     New and Enhanced Commands and Functions
 4     Notes about the Catalog Manager
 5     Notes about Wizards
 6     Macro Key Support in FoxPro 2.6
 7     FoxPro and Other Applications
 8     International and Cross-Platform Recommendations
 9     Installation Questions and Answers
 10    Product Support Questions and Answers

----------------------------------------------------------


===================================
Part 1: New Features in FoxPro 2.6
===================================

Microsoft FoxPro version 2.6 includes the following
new features:

   *  A Catalog Manager interface that provides convenient 
      access to database files and functions, and enables you
      to convert dBASE(R) files easily.
	
   *  A collection of wizards that simplify common database 
      tasks.

   *  Language additions that provide dBASE IV(R) language 
      compatibility.

FoxPro version 2.6 includes existing print
documentation from version 2.5, as well as significant 
updates to the Help file that describe new 2.6
functionality. For more information, see the What's New 
Since FoxPro 2.5 Help topic.

Important:  The FoxPro Catalog Manager is not available in 
the 16-bit Standard version of FoxPro. To convert dBASE III(R) 
and dBASE IV files in the 16-bit Standard version, select 
Convert dBASE files... from the Run menu.  For more help 
converting files, press F1 while in this dialog.
----------------------------------------------------------


===========================
Part 2: Installation Notes
===========================

There are three types of installation for FoxPro for
MS-DOS: Normal Installation, Administrative Installation
and Workstation Installation. Instructions for Normal
Installation are in the FoxPro Installation and
Configuration manual. For information about Administrative
and Workstation Installation, see INSTALL.TXT on FoxPro 
for MS-DOS Disk 1.

Installing FoxPro on the Microsoft Windows NT(TM) 
operating system
-------------------------------------------------
FoxPro for MS-DOS cannot install in an MS-DOS window within 
Microsoft Windows NT. To install FoxPro for MS-DOS, you must 
be able to boot to a separate MS-DOS partition.
----------------------------------------------------------


=================================================
Part 3: New and Enhanced Commands and Functions
=================================================
Several commands and functions are new to FoxPro 2.6, 
and some have been enhanced to provide additional 
compatibility with dBASE IV(R). For additional information 
about these commands and functions, see the New and Enhanced 
Commands and Functions Help topic.

New/Enhanced Commands
---------------------
ON BAR
ON EXIT BAR
ON EXIT MENU
ON EXIT PAD
ON EXIT POPUP
ON MENU
ON MOUSE
ON PAD
ON POPUP
SET CPCOMPILE
SET CPDIALOG
SET COLLATE
SET DIRECTORY
SET FIELDS
SET FORMAT
SET KEY
SET NOCPTRANS
SET VIEW

New/Enhanced Functions
----------------------
BARCOUNT( )
BARPROMPT( )
BLANK
CPCURRENT()
CPDBF()
CPCONVERT()
DESCENDING( )
FLDCOUNT( )
FOR( )
FTIME( )
HOME( )
ID( )
IDXCOLLATE()
ISBLANK( )
ISMOUSE( )
KEYMATCH( )
MEMORY(0)
MEMORY(1)
MEMORY(2)
MEMORY(3)
MEMORY(4)
MEMORY(5)
MEMORY(6)
MEMORY(7)
PADPROMPT( )
PCOUNT( )
PRTINFO( )
RUN( )
SET("ATTRIBUTES")
SET("DIRECTORY")
SET("DISPLAY")
SET("LIBRARY")
SET MBLOCK
SET("MBLOCK")
SYS(1037)
TAG( )
TAGCOUNT( )
TAGNO( )
UNIQUE( )
WINDOW( )

New/Enhanced System Memory Variables
------------------------------------
_ASSIST
_SHELL
----------------------------------------------------------


========================================
Part 4: Notes about the Catalog Manager
========================================

Reserved Names in the Catalog Manager
-------------------------------------
Like any other FoxPro application, the Catalog Manager calls 
and runs procedures and programs whose names may interfere 
with other user-defined procedures and programs. 

When you execute a program or procedure, FoxPro searches for
the program or procedure in a specific order.  This order 
includes the current file as well as programs that were 
executed prior to the current one, including the Catalog 
Manager itself.

Below is a list of procedure and program names that can cause
errors if run from within the Catalog Manager.

ABORT
ACTTHERM
ADDALIAS
ADDBS
ADDFILE
ADDTASK
ANALYZE
CLEANUP
CONTROL
DELUSER
DUMMY
ERRHAND
ESCHAND
EXECUTE
EXPORT
FILEEXT
FINDFILE
FORCEEXT
GETSQL
GETSTAMP
GETWPARM
IMPORT
INDEX
ISMAC
ISSPR
JUSTEXT
JUSTFNAME
JUSTPATH
MENUPROC
MIGRATE
MODIFY
MSGBOX
ORDER
PARSFIL
PRINT
REMOVE
SAVEPREF
SETTINGS
SETTOPIC
SHUTDOWN
TOUCHED
TRASHCAN
UPDTHERM
VRUN 


API Library Routines and the Catalog Manager
--------------------------------------------
If you use any routines that are called when an API library 
is opened or closed, you should note the following Catalog 
Manager behaviors.

The Catalog Manager opens and closes API libraries on
these occasions:

* When the Catalog Manager is started, all API 
  libraries are closed.

* When a program is run from within the Catalog
  Manager, all API libraries that were open before
  the Catalog Manager started are opened.  When the program
  ends the API libraries are closed.

* When the Catalog Manager is exited, all API 
  libraries that were open before the Catalog
  Manager started are opened.
----------------------------------------------------------


============================
Part 5: Notes about Wizards
============================
Running Wizards in the 16-bit Standard version of FoxPro
--------------------------------------------------------
To run the FoxPro Wizards in the 16-bit Standard version 
of FoxPro you need to have at least 525KB of free
conventional memory.  You can also run the Wizards in the 
32-bit Extended version of FoxPro.

Memo and General Fields and the Label Wizard
--------------------------------------------
Memo and General fields cannot be included in a label
created with the Label Wizard.  To add Memo and General
fields you must modify the label with the Label Writer.

Modifying Wizard-Created Items in Microsoft Windows NT(TM)
----------------------------------------------------------
If you are using the Microsoft Windows NT operating system, 
you can use wizards to create tables, queries, 
screens, reports, or labels. To modify items created with a 
wizard you must use the appropriate FoxPro power tool, such 
as the Report Writer, Screen Builder, or RQBE.
----------------------------------------------------------


========================================
Part 6: Macro Key Support in FoxPro 2.6
========================================
In FoxPro 2.6, the key combinations Alt+1 to Alt+9 cannot
be used to define macros. For a list of key combinations
supported in FoxPro 2.6 see the ON KEY LABEL topic in Help.
----------------------------------------------------------


======================================
Part 7: FoxPro and Other Applications
======================================
Importing Microsoft Excel Spreadsheets to FoxPro
----------------------------------------------------
FoxPro can import spreadsheet files from Microsoft 
Excel version 4.0. To import spreadsheets from Microsoft 
Excel version 5.0, you must first save them as version 
4.0 files. Columns from the spreadsheet become fields 
in the table, and rows from the spreadsheet become records
in the table.

Running dBASE Applications in FoxPro
------------------------------------
To run dBASE III and IV applications in FoxPro, first you 
must convert the individual components, and then re-compile 
them in FoxPro.

To convert dBASE III and dBASE IV files in the 32-bit
Extended version, use the FoxPro Catalog Manager. For 
information on converting dBASE files in the Catalog
Manager, see the Switching from dBASE Help topic.  

To convert dBASE III and dBASE IV files in the 16-bit 
Standard version, select Convert dBASE files... from the
Run menu.  For more help converting files, press F1 while 
in this dialog.
----------------------------------------------------------


=========================================================
Part 8: International and Cross-Platform Recommendations 
=========================================================
See the International and Cross-Platform Features topic in
Help for the latest information on code pages and collation
sequences.

Tagging Codepages to Tables in the Catalog Manager
--------------------------------------------------
Note:  This section only applies if you are using code
pages for cross-platform development.

To ensure that accented characters in a table are displayed 
correctly on the current platform, the table must be tagged 
with a code page. In Catalog Manager, to tag a code page to
a table that does not have one, make sure the following 
are true:

1.  SET EXCLUSIVE is ON.  The exclusive setting can 
    be set in the Catalog Manager Settings dialog.
2.  The configuration file (CONFIG.FP) includes the
    line CODEPAGE = AUTO

When you try to use the table without a code page in the
Catalog Manager a dialog appears, allowing you to specify 
the platform on which the file was created.  Once a table 
is tagged with a code page you do not have to tag it again. 
If you do not specify a code page, the table is displayed 
with the code page of the current platform.  To remove a 
tag from a table, run CPZERO.PRG, located in the 
FoxPro root directory.
----------------------------------------------------------


===========================================
Part 9: Installation Questions and Answers
===========================================

Overview of Questions
---------------------

1   Why does the FoxPro installation sometimes stop before
    allowing the installation of optional components?
2   How do I install additional files that I didn't
    specify during installation?
3   Why does FoxPro reboot during the installation process?
4   What MS-DOS BUFFERS and FILES statements are appropriate
    for FoxPro for MS-DOS?
5   Does FoxPro for MS-DOS operate with the DOS
    Protected Mode Interface (DPMI)?
6   What factors influence FoxPro startup speed?
7   I'm receiving the error message "Too many files open."
    How can I correct this problem?
8   The Standard Version of FoxPro for MS-DOS runs
    correctly on my computer, but when I load the 32-bit 
    Extended version I receive the error message "Incompatible
    memory manager." What is causing this problem?
9   I am receiving the error message "RUN/! command failed."
    How can I correct this problem?
10  Why do I have several files with the extension .TMP on
    my disk?
11  When I try to start up a second instance of FoxPro 
    for MS-DOS within Windows, I get the error "Cannot
    Access File at this Time." This only happens when the
    version of FoxPro resides on my local drive.
12  I get the Cannot Create <Path>\FOXPRO.EXE" Error 
    During Installation.  How can I correct this problem?
13  What are the minimum files required to run FoxPro?
14  A "CRC Error" Occurs During Setup. 
    How can I correct this error?
15  The following error occurs File 'ADDUSER.APP' Does Not Exist" 
    Running INSTALL /N.  How can I correct this?
16  The Configuration Portion of INSTALL /N Fails.
    How can I correct this problem?
17  Why does INSTALL /N Prompt for a Floppy Disk?
18  When I type INSTALL /N at an MS-DOS prompt within Windows
    I receive a memory error.  What can I do?
----------------------------------------------------------

Question 1

Why does the FoxPro installation sometimes stop before
allowing the installation of optional components?

Answer 1

Sometimes in low memory conditions the installation program
is unable to determine whether to run the Standard
(FOXPRO.EXE) or the 32-bit Extended (FOXPROX.EXE) version
to complete the installation. If you're installing from 
within Windows, you can exit Windows to make more memory
available. If you have any TSR programs residing in memory,
removing them from memory may free additional memory.  For
information on installing optional components after you have
installed FoxPro, see Question 2 in this section.
----------------------------------------------------------

Question 2

How do I install additional files that I didn't specify
during installation?

Answer 2

Restart FoxPro by typing FOX at the MS-DOS prompt and
pressing Enter. Insert any one of the product disks into
drive A and enter the following command in the FoxPro
Command window:

DO INSTALL

You are prompted to insert the disk or disks that
contain the additional files you want to install.  If you
are attempting to install from a drive other than drive A,
you are instructed to select another source drive
after the "Abort, Retry, Fail?" message.
----------------------------------------------------------

Question 3

Why does FoxPro reboot during the installation process?

Answer 3

You could have an anti-virus program running, a memory
conflict, or an old video driver. Disable any anti-virus 
program or old video driver and retry the installation
of optional components as described in Question 2, above.
Make sure you are excluding areas of memory required to
load video drivers or network cards. For example, if you
are loading EMM386 in your CONFIG.SYS file, the
"X=D800-DFFF" parameter in the following device driver
load command in MS-DOS will reserve those memory segments:
 
   DEVICE=C:\WINDOWS\EMM386.EXE RAM 2048 X=D800-DFFF
 
If you are using an older version of your video card 
driver, contact the manufacturer or use the Microsoft
Download Service (MSDL) to get new drivers. MSDL is
described in the Product Support section, below.

If you are installing from within Windows, try using a
different video driver (for example, the generic VGA 
driver, VGA.DRV) and run with no old video drivers
loaded in the AUTOEXEC.BAT or CONFIG.SYS files.
----------------------------------------------------------

Question 4

What MS-DOS BUFFERS and FILES statements are appropriate for
FoxPro for MS-DOS?

Answer 4

For best performance with FoxPro when the SMARTDRV device 
driver is loaded, set BUFFERS to 10 in the CONFIG.SYS file.
Anything more is redundant, taking up valuable memory that
FoxPro could use for processing.

If you don't use a disk cache program such as SMARTDRV,
you should allocate enough MS-DOS buffers to hold all of
the directory entries in the subdirectory where you will
be working.  Setting BUFFERS to 40 is usually sufficient
as long as the number of files in a subdirectory remains
below 250.

The FILES statement should always be at least 10 more than
the greatest number of files that you will have open at
one time.  We recommend that you set FILES to 40 or greater.
----------------------------------------------------------

Question 5

Can I run the FoxPro 32-bit Extended version in Enhanced
Mode Windows or with EMM386 with the NOEMS option?

Answer 5

Yes.  FoxPro works with DPMI-compliant memory managers,
such as Microsoft Windows and EMM386.  If you use a DPMI
memory manager, you can control the physical memory that
FoxPro uses by specifying the MEMLIMIT option in your
CONFIG.FP file. For more information on the MEMLIMIT option,
refer to the Update manual and to "Changes to Documentation 
Since Printing" in Help.
----------------------------------------------------------

Question 6

What factors influence FoxPro startup speed?

Answer 6

The time required to load and start FoxPro relates to the
physical size of FoxPro, the length of the path in effect,
the number of items FoxPro has to locate at startup, and
other factors.  You can control many of these items.
For a complete discussion of this issue, refer to 
"Optimizing Your System" in the Installation and 
Configuration manual.
----------------------------------------------------------

Question 7

I'm receiving the error message "Too many files open."
How can I correct this problem?

Answer 7

If you receive this error message, use one or more of the
following strategies:

* Increase the FILES setting in the CONFIG.SYS file.
* If you are using a Novell network, increase the FILE
  HANDLES setting in the SHELL.CFG file.
* If you are using the MS-DOS SHARE program, increase the
  number of files and locks. For example, you could use
  SHARE /F: 4096 /L:500 in the CONFIG.SYS file.
----------------------------------------------------------

Question 8

The Standard version of FoxPro for MS-DOS runs
correctly on my computer, but when I load the 32-bit
Extended version I receive the error message "Incompatible
memory manager."  What's causing this problem?

Answer 8

When you configure your memory manager, verify that it
can use extended memory, and that the proper switches
are set. For further information on the 32-bit Extended
version of FoxPro, refer to "Optimizing Your System" in
the Installation and Configuration Guide.
----------------------------------------------------------

Question 9

I'm receiving the error message "RUN/! command failed." How
can I correct this problem?

Answer 9

Make sure your CONFIG.SYS file contains this line:
 
  SHELL = C:\<path>\COMMAND.COM C:\<path>\ /P /E:1024
 
Also, make sure that the correct version of COMMAND.COM
resides in the specified directory.

If the SHELL line shown here is already in your CONFIG.SYS
file, then you've received this error because FoxPro doesn't
have enough conventional memory to execute the RUN command.
If this is the case, use RUN /0 DIR instead of RUN DIR.
RUN /0 automatically loads FoxSwap, which makes all
available conventional memory accessible to FoxPro.
For more information on the RUN command and FoxSwap, refer
to "RUN|! Commands" in Help.
----------------------------------------------------------

Question 10

Why do I have several files with the extension .TMP on my
disk?

Answer 10

Every time you load FoxPro, it creates temporary (.TMP)
files. These files are automatically deleted when you exit
FoxPro with a normal shutdown. However, .TMP files still
exist if you reboot the machine from within FoxPro, or if
you don't have delete rights in the directory where the
files reside. Exit FoxPro and acquire the rights to delete
all these files. One caution: Other programs, such as
Windows, also create .TMP files. To be safe, make sure no
other applications are active when you delete .TMP files.
----------------------------------------------------------

Question 11

When I try to start up a second instance of FoxPro for
MS-DOS within Windows, I get the error "Cannot access file
at this time." This only happens when the version of
FoxPro resides on my local drive.

Answer 11

The MS-DOS SHARE program is the most common cause of this
problem.  Current workarounds include marking the FoxPro
FOXPRO.EXE and FOXPROX.EXE files read only, running under
Windows for Workgroups, or running a copy of FoxPro from
a network location.
----------------------------------------------------------

Question 12

I get Cannot Create <Path>\FOXPRO.EXE" Error 
During Installation.  How can I correct this problem?

Answer 12

One possible cause is that FOXPRO.EXE or FOXPROX.EXE already 
exists in that directory and it is marked read-only.

For the Setup program to be able to perform a successful 
install, the .EXE file must be either renamed or marked as 
read/write. The command ATTRIB -R <path>\FOXPRO.EXE will 
remove the Read-Only attribute from the file.
----------------------------------------------------------

Question 13

What are the minimum files required to run FoxPro?

Answer 13

Not all files placed on the hard disk during installation 
of FoxPro are absolutely required for operation of the 
product.  FoxPro for MS-DOS can be started with only two 
files: FOXPRO.EXE and FOXPRO.OVL. For the extended (32 bit) 
version, these two files can be replaced by only one, 
FOXPROX.EXE.

The minimum files needed to run FoxPro, use the menu and 
screen generators, and set printer drivers are listed below.

NOTE: Upon startup, FoxPro will create FOXUSER.DBF and 
FOXUSER.FPT files, and upon screen or menu generation, it 
will create the appropriate .FXP files. 


Versions 2.6 (MS-DOS)
------------------------------

   Filename         Bytes      Comments
   ------------------------------------------------------

   DRIVER2.PLB      14029
   FOXSWAP.COM       5971      Only needed for standard version.
   GENMENU.PRG      57109
   GENPD.APP       374351
   GENSCRN.PRG     292613
   GENXTAB.PRG      29246      Only needed for cross tabulation.
   PSAPI.PLB        24451
   FOXPRO.EXE      411599
   FOXPRO.OVL     1424976

---------------------------------------------------------

Question 14

A "CRC Error" Occurs During Setup. 
How can I correct this error?

Answer 14

When reading a disk, MS-DOS performs a cyclical redundancy 
check (CRC) to verify disk sectors. The CRC is a 
sophisticated parity check of the data in each sector and 
will detect most data errors, such as lost or scrambled 
bits.
 
To determine if there is a problem with the disks:
 
1. Attempt the installation a second time.

2. Install on a "clean" (minimal) configuration.

3. Install on another machine to verify there is not a 
   hardware problem. 

4. Copy the floppy disks to a temporary directory on the
   hard disk and run the Setup program from this temporary 
   directory.
 
If the installation still fails, call Microsoft Product 
Support Services for assistance.
---------------------------------------------------------

Question 15

The following error occurs File 'ADDUSER.APP' Does Not 
Exist" Running INSTALL /N.  How can I correct this?

Answer 15

The INSTALL /N command was not issued from the directory 
containing the Administrative Installation (INSTALL /A) of 
FoxPro.

After a Workstation Installation completes the Basic 
portion of its installation, it calls the FoxPro program 
ADDUSER.APP to configure the workstation for the network 
environment. In order for FoxPro to load and run 
ADDDUSER.APP, the current directory must be the 
Administrative Installation directory.

Even if the Administrative Installation directory is on 
the MS-DOS search path, allowing FoxPro itself to start, 
because ADDUSER.APP is not an MS-DOS executable program 
(.COM or .EXE), it cannot be located on the path, thus
causing the error message.

RESOLUTION

Go to the drive and directory containing the Administrative 
Installation of FoxPro, and type "INSTALL /N" (without the 
quotation marks).
---------------------------------------------------------

Question 16

The Configuration Portion of INSTALL /N Fails.
How can I correct this problem?

Answer 16

The command, "INSTALL /N" (without the quotation marks) was 
not issued from the directory containing the Administrative 
Installation (INSTALL /A) of FoxPro.

Go to the drive and directory containing the Administrative 
Installation of FoxPro, then reissue the INSTALL /N command.

After a Workstation Installation completes the Basic portion
of its installation, it calls the FoxPro program ADDUSER.APP 
to configure the workstation for the network environment. In 
order for FoxPro to load and run ADDDUSER.APP, the current 
directory must be the Administrative Installation directory.

The error received depends on which directory you started 
INSTALL /N from, and whether you are running it from an 
MS-DOS prompt in Windows, or at MS-DOS itself.
---------------------------------------------------------

Question 17

Why does INSTALL /N Prompt for a Floppy Disk?

Answer 17

The INSTALL /N command was not issued from the Administrative 
Installation directory.

To avoid this problem, use one of the following workarounds.

Workaround 1: Go to the Administrative Installation 
Directory

Go to the Administrative Installation directory, and then 
type the command "INSTALL /N" (without the quotation marks).

For example, assuming the Administrative Installation is 
located in a directory named N:\ADMIN, type the following 
commands at the MS-DOS prompt:

   N:
   CD\ADMIN
   INSTALL /N

Workaround 2: Use SUBST to Reassign the Local Drive to 
Another Letter

If, for reasons such as testing, you require that the 
Administrative Installation be located on a local hard disk 
and you do not want to issue the INSTALL /N command from the 
Administrative Installation directory, use the MS-DOS SUBST 
command to reassign the directory containing the
Administrative Installation to another drive letter.

For example, assuming the Administrative Installation is 
located in a directory named C:\ADMIN and you want to create 
a Workstation Installation in a directory named C:\WORKSTA, 
type the following at the MS-DOS prompt:

   SUBST N: C:\ADMIN
   C:
   CD\WORKSTA
   N:\INSTALL /N

The Workstation Installation requires a previous
Administrative Installation. Even though it prompts for a 
floppy disk, the Workstation Installation cannot be 
performed using the Installation floppy disks.
---------------------------------------------------------
Question 18

When I type INSTALL /N at an MS-DOS prompt within Windows
I receive a memory error.  What can I do?

Answer 18

In some instances, an Administrative Installation will not
work from an MS-DOS prompt within Windows.  To run a 
Network installation from an Administrative Installation 
directory, you might need to exit Windows and use the main 
MS-DOS prompt.
----------------------------------------------------------

===============================================
Part 10: Product Support Questions and Answers
===============================================

Overview of Questions
---------------------

1   Where can I go for additional pre-sale information
    on Microsoft Fox products such as pricing, upgrade
    policies, release dates, and so on?
2   Where can I go for additional FoxPro product support?
3   If I call for support or post a message on the Fox
    Forum, what information should I include?
4   I have a hearing impairment. Where can I go for
    additional FoxPro product support?
5   I have some specific comments and suggestions on
    Microsoft Fox products. Where can I direct these
    comments?
----------------------------------------------------------

Question 1

Where can I go for additional pre-sale information on
Microsoft Fox products such as pricing, upgrade policies,
release dates, and so on?

Answer 1

In the United States, call 800-426-9400.
----------------------------------------------------------

Question 2

Where can I go for additional FoxPro product support?

Answer 2

Call *Microsoft FastTips* to hear recorded responses to
common questions about Microsoft FoxPro.  You can also
order technical notes that will be sent to your fax
machine.  FastTips is available seven days a week, 24 
hours a day.  For assistance with FoxPro, dial 206-635-7190.

Use the *Microsoft Forums* on CompuServe.  You can discuss
current support and design issues with other developers and
download sample files from the libraries.  For an
introductory CompuServe membership kit specifically for
Microsoft users, call CompuServe at 800-848-8199 and ask
for operator 170.  If you are already a CompuServe member,
type GO MICROSOFT at any ! prompt.  For specific FoxPro
information, type GO FOXFORUM, or GO FOXUSER.

Use the *Microsoft Download Service* to access technical
notes and supplementary files covering common Microsoft
product support issues. This service is available via
modem 24 hours a day, seven days a week at 206-936-6735.

Call *Microsoft Product Support Services* between 6 a.m.
and 6 p.m. Pacific time, Monday through Friday.  For
assistance with Microsoft Fox products for MS-DOS or for
Windows, call 206-635-7191.  For assistance with Microsoft
Fox products for the Macintosh, call 206-635-7192.

Microsoft support services are subject to Microsoft prices,
terms, and conditions that are in place at the time the
service is used.
----------------------------------------------------------

Question 3

If I call for support or post a message on the FoxForum,
what information should I include?

Answer 3

When you call, you should be at your computer and have the
appropriate product documentation at hand.  Be prepared to
give the following information:

* The version number and platform of the Microsoft Fox
  product you are using.  
  This can be obtained by typing ?VERSION(1) in the Command
  window for FoxPro.
* The type of hardware you are using, including network
  hardware if applicable; and the operating environment
  that you are using.
* The contents of the following files: CONFIG.FP,
   CONFIG.SYS, AUTOEXEC.BAT, and any network
  configuration files.
* The exact wording of any messages that appeared on your
  screen.
* A description of what happened and what you were doing
  when the problem occurred.
* Can you reproduce the problem using a small number of
  steps?
* What steps have you already taken to solve the problem?
----------------------------------------------------------

Question 4

I have a hearing impairment. Where can I go for additional
FoxPro product support?

Answer 4

Microsoft Product Support Services is available for the
hearing impaired. Using a special TDD/TT modem, dial
206-635-4948 between 6 a.m. and 6 p.m. Pacific time,
Monday through Friday.

Microsoft support services are subject to Microsoft
prices, terms, and conditions that are in place at the
time the service is used.
----------------------------------------------------------

Question 5

I have some specific comments and suggestions on Microsoft
Fox products. Where can I direct these comments?

Answer 5

We'd like to hear your comments about Microsoft Fox
products and services.  Help us make future versions of
Microsoft Fox products even better by calling, sending a
fax, dropping us a note, or sending electronic mail.
Your feedback will be considered in developing future
versions of Microsoft FoxPro.

Call 206-936-9474 and leave your comments using a
touch-tone phone 24 hours a day.

Fax 206-936-7329 and provide detailed comments 24
hours a day.

Send a note to:

Microsoft FoxPro WishLine
One Microsoft Way
Redmond, WA  98052

If you have access to the Internet, send electronic
mail at:

foxwish@microsoft.com.

Or, address CompuServe mail to:

>INTERNET:foxwish@microsoft.com.
----------------------------------------------------------

                   =================
                   End of README.TXT
                   =================
