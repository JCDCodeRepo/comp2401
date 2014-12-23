Preamble:
-- Program name:  cuShell
-- Purpose:       A simple shell that secretly sends all user
--                entered commands to a remote logger process
--                that stores them in a file.
-- Author:        John Diyala
-- Date:          December 6, 2014

Files:
-- Source:
---- cuShell.c
---- logger.c
-- Executables:
---- cuShell
---- logger
-- Configuration:
---- .config

Compilation:
-- use given Makefile to create both executables	"make"

Launch:
-- launch logger in the background : 			"./logger &"
-- launch cuShell from the same directory		"./cuShell"
   (they must use the same config file)

Operation:
-- logger 
---- can run in the background without
     user interaction
---- terminates when the exit command
     is received from cuShell
-- cuShell 
---- behaves as a regular shell, 
     except for commands that do not work
     with execvp
---- terminate by entering "exit"			"exit"

