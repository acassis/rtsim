################################################################################
#   FILE:
#
#         Utilities.tcl
#
#    DESCRIPTION:
#
#       This file contains all the procedures to load the initial configurations
#	for see our interface correctly
#
#	To execute the program:
#
#         	This code only contains procedures that are called from
#		WindowProcedures.tcl, so if you execute this code, you won't see 
#		nothing	in display because there are only procedures that have 
#		to be called from another program.
#
#	See README file for details.
#
#	Copyright (C) 2008
#
#		Oskardie Castro, Ruben Batista, Arnoldo Diaz
#
#	This is free software;  you can  redistribute it  and/or modify it under
#	terms of the  GNU General Public License as published  by the Free Soft-
#	ware  Foundation;  either version 2,  or (at your option) any later ver-
#	sion.  It is distributed in the hope that it will be useful, but WITH-
#	OUT ANY WARRANTY;  without even the  implied warranty of MERCHANTABILITY
#	or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
#	for  more details.  You should have  received  a copy of the GNU General
#	Public License;  see file COPYING.  If not, write to  the Free Software
#	Foundation,  59 Temple Place - Suite 330,  Boston, MA 02111-1307, USA.
#
#	LAST REVISION:    September 2008
################################################################################


##########################################################################
#	saveTasksList
#	May 30, 2007
#	Allow to a user save in a text plain, the list of tasks that is
#	in the table, for other tests in other ocations with the current
#	list of tasks
#	Parameters: 
#		listTasks - It will contains the tasks concatenated
#	Returns:
#		None
#	Messages:
#		1. No file selected. Operation cancelled by user.
#		To do
#		2. The file does not seem to include a valid task set. The
#		task set is not valid or task parameters are invalid. 
##########################################################################
proc saveTasksList { listTasks args } {
	global pathSavedTasks
	#Types of files that can be opened with the dialog box are declarated in the var tipos
	#this is a kind of filter to use with tk_getSaveFile
	if { $listTasks == ""} {
		return [searchCommand NOT_TASKS]
	} else {
		#Is the location where we create the file to save
		set fileName $pathSavedTasks
		if {$fileName == ""} {
			return [searchCommand NOT_FILE_SELECTED]
		} else {
			if {[file exists $fileName] > 0 && [file isfile $fileName] > 0} {
				set tasksFile [open $fileName { RDWR TRUNC } ]
			} else {
				set tasksFile [open $fileName { RDWR CREAT } ]
			}
#			set textToSave "\[TASKS\]"
#			append textToSave "\n#[searchCommand ABBREVIATION_TASK_ID]\t[searchCommand ABBREVIATION_TASK_PHASE]\t[searchCommand ABBREVIATION_TASK_EXECUTION]\t[searchCommand ABBREVIATION_TASK_PERIOD]\t[searchCommand ABBREVIATION_TASK_DEADLINE]"
			set textToSave "$listTasks"
			puts $tasksFile $textToSave
			close $tasksFile
			set pathSavedTasks $fileName
			return [searchCommand SAVE_SUCCESSFUL]
		}
	}
}

proc saveAsTasksList { listTasks args } {
	global pathSavedTasks
	#Types of files that can be opened with the dialog box are declarated in the var tipos
	#this is a kind of filter to use with tk_getSaveFile
	set rtsExtension [searchCommand WINDOW_DIALOG_EXTENSION_RTS]
	set txtExtension [searchCommand WINDOW_DIALOG_EXTENSION_TXT]
        set types { 
		{{"RealTSS Files"} {.rts} }
		{{"Text Files"} {.txt} }
	}
	if { $listTasks == ""} {
		return [searchCommand NOT_TASKS]
	} else {
		#Is the location where we create the file to save
		set fileName [tk_getSaveFile -filetypes $types ]
		if {$fileName == ""} {
			return [searchCommand NOT_FILE_SELECTED]
		} else {
			if {[file exists $fileName] > 0 && [file isfile $fileName] > 0} {
				set tasksFile [open $fileName { RDWR TRUNC } ]
			} else {
				set tasksFile [open $fileName { RDWR CREAT } ]
			}
#			set textToSave "\[TASKS\]"
#			append textToSave "\n#[searchCommand ABBREVIATION_TASK_ID]\t[searchCommand ABBREVIATION_TASK_PHASE]\t[searchCommand ABBREVIATION_TASK_EXECUTION]\t[searchCommand ABBREVIATION_TASK_PERIOD]\t[searchCommand ABBREVIATION_TASK_DEADLINE]"
			set textToSave "$listTasks"
			puts $tasksFile $textToSave
			close $tasksFile
			set pathSavedTasks $fileName
			return [searchCommand SAVE_SUCCESSFUL]
		}
	}
}


##########################################################################
#	openFileTasklist
#	February 23, 2010
#	This procedure presents the Open File dialog and allows the user
#	to select a rtss work file. It reads it and process it, loads the
#	working environment.
#	Parameters: 
#		None
#	Returns:
#		None
#	Messages:
#		1. No file selected. Operation cancelled by user.
#		To do
#		2. The file does not seem to include a valid task set. The
#		task set is not valid or task parameters are invalid.
##########################################################################
proc openFileTasklist { } {
	global pathSavedTasks
        global array entorno ;		#Environment array
        global array algosLista ;	#Algorithms array
        global array conjuntoTareas ;	#Task set
        global array usos ;		#Usage array
        global numTareas ;		#Tasks quantity
        global numUsos ;		#Usae quantity
        global IDs ;			#Task index variable; indicates the following task index.
        set nTareas 0
        set nUsos 0
	set rtsExtension [searchCommand WINDOW_DIALOG_EXTENSION_RTS]
	set txtExtension [searchCommand WINDOW_DIALOG_EXTENSION_TXT]
        set types {
		{{"Text Files"} {.txt} }
		{{"RealTSS Files"} {.rts} }
	}
        
        set archName [tk_getOpenFile -filetypes $types ] 
        if {$archName == ""} {
        	tk_messageBox -message "[searchCommand NOT_FILE_SELECTED]" -type ok
        } else {
        	set entorno(archrts) $archName
		set pathSavedTasks $archName
        	set arch [open $archName { RDWR CREAT } ]
        	set tipo 0
        	#Read file line by line
        	while { [gets $arch linea ]  >= 0} { 
#        		#Process each line read
#        		switch $linea {
#        			"\[tareas\]" { ;	#Task
#                			set tipo 0
#                			set n 0
##        			continue
#        			}
#        			"\[recursos\]" { ;	#Resource
#                			set tipo 2
#                			set n 0
#                			continue
#        			}
#				"#ID	T.F.	T.E.	T.P.	T.D." { ;
#        				set tipo 1
#                			set n 0
#					continue
#				}
#        			"\[datos\]" {
#                			#Any other thing...
#                			set tipo 3
#                			continue
#        			}
#        		}
#        		switch $tipo {
#        			1 { 
#        				#Insert new task into task set array
#        				incr nTareas 
#        				readTasks $linea $nTareas
#        			}
#        			2 { 
#        				#Insert new resource into resources array
#        				incr nUsos
#        				leeRecurso $linea $nUsos
#        			}
#        			3 { 
#        				#Process any other thing
#        				leeDatos $linea 
#        			}
#        		}
			incr nTareas
			readTasks $linea $nTareas
    		}		
        	close $arch
        }
        set numTareas $nTareas
        set numUsos $nUsos
#        set IDs [incr nTareas]
}

##########################################################################
#	readTasks
#	May 30, 2007
#	Process tasks read from working file. Puts information on the task
#	set array and the interface task list
#	Parameters: 
#		linea - String to process.
#		n - Line number
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc readTasks { line n } {
#	global array taskListArray
#	set lista [list]
	set value ""
	set id ""
	set phase ""
	set tE ""
	set period ""
	set deadline ""
	set j 0
	
	set fields [split $line " "]
	## Assign fields to variables and print some out...
	lassign $fields \
		PERIOD TE
	append tE $TE
	append period $PERIOD
	
#	for {set i 0} {$i < [string length $line]} {incr i} {
#		set car [string index $line $i]
#		#HERE WE READ THE TASKS SEPARATED BY A SPACE
#		if {$car != " "} {
#			append value $car
#		} else { 
#			
#			switch $j {
#				#Wich parameters is it
#				0 { 
#					#ID
#					set tE $car 
#					puts $tE
#				}
#				1 { 
#					#Phase
#					set period $value
#					puts $period
#				}
#			}
#			set value ""
#			incr j
#		}
#	}
	insertRow [getTableTasksFrame] $n "0" $tE $period $period
	
#	puts "$n 0 $tE $period $period"
}

##########################################################################
#	cargarIni
#	July 2, 2007
#	Look up and reads realtss.ini 
#	Loads .ini on config array
#	Parameters: 
#		None
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc cargarIni { } {
	#Open file...
	set archName "realtss.ini" ;	#Name is fixed... realtss.ini
	set archExist [file exists $archName]
	if {$archExist > 0} {
		set arch [open $archName { RDWR CREAT } ]
		set tipo 0
		while { [gets $arch line ] >= 0} {
			
			#Process line 
			switch $line {
				"\[tcl\]" {
					set tipo 1
					continue
				}
				
				"\[directorios\]" {
					set tipo 1
					continue
				}
			}
			
			#Just in case we later put something else on the ini file 
			switch $tipo {
				1 {
					leeIni $line ;	#Call leeIni to assign values to config array
				}
			}
    	}
		close $arch
	}
	
}

##########################################################################
#	leeIni
#	May 30, 2007
#	Process rtss.ini file
#	This procedure populates the global array "config"
#	Parameters: 
#		line - String to process.
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc leeIni { line } {
	
	global array config
	set valor ""
	set nombre ""
	set bandera 0
	#Is it a var name or a value???
	for {set i 0} {$i < [string length $line]} {incr i} {
		set car [string index $line $i]
		if {$car != "="} {
			if {$bandera == 0} {
				#Var name
				append nombre $car
			} else {
				#Value
				append valor $car
			}
		} else {
			set bandera 1
			continue 
		}
	}
	#Assign values to variables
	if {$nombre != "" && $valor != ""} { 
		switch $nombre {
			#Wich variable???
			"algos" { set config(algos) $valor }
			"kiwi" { set config(kiwi) $valor }
			"wish" { set config(wish) $valor }
			"language" { set config(language) $valor }
			"algorithmsName" {set config(algorithmsName) $valor}
			"languagesContainer" {set config(languagesContainer) $valor}
			"fulllibfile" {set config(fulllibfile) $valor}
			"fulllibcommnad" {set config(fulllibcommnad) $valor}
		}
	}
}

##########################################################################
#	initEntorno
#	May 30, 2007
#	Clears entorno array
#	Parameters: 
#		None
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc initEntorno {} {
	global array entorno ;	#Environment array

	set entorno(archrts) ""
	set entorno(archtraza) ""
}

##########################################################################
#	initConfig
#	May 30, 2007
#	Clears config array
#	Parameters: 
#		None
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc initConfig {} {
	global array config
	#Config
	set config(algos) "algos" ;	#Default name for algorithm's directory
	set config(kiwi) "/home/vid/Aplicaciones/kiwi-1.0.1/kiwi.tcl"
	set config(wish) ""
	set config(language) "Languages/English.lng"
	set config(algorithmsName) "Algorithms/Algorithms.conf"
	set config(languagesContainer) "Languages/Languages.conf"
	set config(fulllibfile) libsimulator
	set config(fulllibcommnad) simulator
}

##########################################################################
#	loadLanguage
#	September 21, 2008
#	Reads the file .lng and load to memory each of one of the comands
#	used in the windows
#	Parameters:
#		filePath - This have to been the complete path of the file
#			that contains the .lng
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc loadLanguage { filePath } {
	global commandsLanguage ;
	global APP_PATH
	## First we read the file by the arguments given
	set language [open  "$APP_PATH/$filePath"]
	set contentLanguage [read $language]
	close $language
	## Split into records on newlines
	set records [split $contentLanguage "\n"]
	
	## Iterate over the records
	foreach rec $records {
		if {$rec != "/"} {
			set len [string length $rec]
			if {$len == 1} {
				#nada
			} else {
				set idRow $commandsLanguage(IDROW)
				set idCol $commandsLanguage(IDCOL)
				## Split into fields on colons
				set fields [split $rec "="]
				## Assign fields to variables and print some out...
				lassign $fields \
					COMMAND TRADUCTION
				set commandsLanguage($idRow,$idCol) $COMMAND
				incr commandsLanguage(IDCOL)
				set idCol $commandsLanguage(IDCOL)
				set commandsLanguage($idRow,$idCol) $TRADUCTION
				incr commandsLanguage(IDROW)
				set commandsLanguage(IDCOL) 0
    				
				
#						puts "$COMANDO - $TRADUCCION"
			}
		} else {
			break
		}
	}
}

##########################################################################
#	searchCommand
#	September 21, 2008
#	Search the equivalent of the command according with the
#	commandsLanguage array that contains all the commands according to
#	the language defined in realtss.ini
#	Parameters:
#		commandName: Is the name of the command that will be
#				searched in the array of commandsLanguage
#	Returns:
#		Returns the command traduction in according of .lng file
#	Messages:
#		None
##########################################################################
proc searchCommand { commandName } {
	global commandsLanguage ;
	set nComandos [expr [array size commandsLanguage]/2-2]
	for {set i 0} {$i<$nComandos} {incr i} {
		if { $commandsLanguage($i,0) == $commandName} {
#			puts $commandsLanguage($i,1)
			return $commandsLanguage($i,1)
		}
	}
	return "-"
}

proc countAlgorithms {filePath} {
	global algorithmsAvailables;
	global APP_PATH
	## First we read the file by the arguments given
	set algorithms [open "$APP_PATH/$filePath"]
	set contentAlgorithms [read $algorithms]
	close $algorithms
	## Split into algorithmsAvailables on newlines
	set algorithmsAvailables [split $contentAlgorithms "\n"]
}
##########################################################################
#	loadNameAlgorithms
#	Octuber 27, 2008
#	Reads the file Algorithms.conf that are in te package Algorithms 
#	and load to memory each of one of the name of Algorithms that are
#	Parameters:
#		filePath - This have to been the complete path of the file
#			that contains the .conf
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc loadNameAlgorithms { filePath } {
	global AlgorithmsName
	global APP_PATH
	## First we read the file by the arguments given
	set algorithms [open "$APP_PATH/$filePath"]
	set contentAlgorithms [read $algorithms]
	close $algorithms
	## Split into records on newlines
	set records [split $contentAlgorithms "\n"]
	
	## Iterate over the records
	foreach rec $records {
		set readPriority 1 
		if {$rec != "/"} {
			set len [string length $rec]
			if {$len == 1} {
				#nada
			} else {
				if {$readPriority == 1 } {
				
					set idRow $AlgorithmsName(IDROW)
					set idCol $AlgorithmsName(IDCOL)
					## Split into fields on colons
					set fields [split $rec "="]
					## Assign fields to variables and print some out...
					lassign $fields \
						ALGORITHM NAME
						
					##save algoritm name
					set AlgorithmsName($idRow,$idCol) $ALGORITHM
					incr AlgorithmsName(IDCOL)
					
					##save value
					set idCol $AlgorithmsName(IDCOL)
					set AlgorithmsName($idRow,$idCol) $NAME
					incr AlgorithmsName(IDCOL)
					
					set idCol $AlgorithmsName(IDCOL)
					incr AlgorithmsName(IDROW)
					set AlgorithmsName(IDCOL) 0
					incr readPriority
				} else {
					set idRow [expr [$AlgorithmsName(IDROW) -1 ]]
					
					## Split into fields on colons
					set fields [split $rec "="]
					## Assign fields to variables and print some out...
					lassign $fields \
						PRIORITY ENABLED
					set AlgorithmsName($idRow,3) $ENABLED
					set readPriority 1
				}
			}
		} else {
			break
		}
	}
}

##########################################################################
#	loadLangaugesAvailables
#	November 4, 2008
#	Reads the file Languages.conf that are in te package Languages 
#	and load to memory each of one of the name of Languages that are
#	available
#	Parameters:
#		filePath - This have to been the complete path of the file
#			that contains the .conf
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc loadLangaugesAvailables { filePath } {
	global languagesAvailables
	global APP_PATH
	## First we read the file by the arguments given
	set languages [open "$APP_PATH/$filePath"]
	set contentLanguages [read $languages]
	close $languages
	## Split into records on newlines
	set records [split $contentLanguages "\n"]
	
	## Iterate over the records
	foreach rec $records {
		if {$rec != "/"} {
			set len [string length $rec]
			if {$len == 1} {
				#nada
			} else {
				set idRow $languagesAvailables(IDROW)
				set idCol $languagesAvailables(IDCOL)
				## Split into fields on colons
				set fields [split $rec "="]
				## Assign fields to variables and print some out...
				lassign $fields \
					COMMAND TRADUCTION
				set languagesAvailables($idRow,$idCol) $COMMAND
				incr languagesAvailables(IDCOL)
				set idCol $languagesAvailables(IDCOL)
				set languagesAvailables($idRow,$idCol) $TRADUCTION
				incr languagesAvailables(IDROW)
				set languagesAvailables(IDCOL) 0
#					puts "$COMANDO - $TRADUCCION"
			}
		} else {
			break
		}
	}
}
	
##########################################################################
#	changeLanguage
#	November 15, 2008
#	Reads the file Algorithms.conf that are in te package Algorithms 
#	and load to memory each of one of the name of Algorithms that are
#	Parameters:
#		filePath - This have to been the complete path of the file
#			that contains the .lng
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc changeLanguage { filePath args} {
	global languageSelected
	## First we read the file by the arguments given
	set languages [open $filePath]
	set contentLanguages [read $languages]
	close $languages
	## Split into records on newlines
	set records [split $contentLanguages "\n"]
	#This var will contain the new realtss.ini
	set realTSS ""
	## Iterate over the records
	foreach rec $records {
		set value ""
		set languageIndicator ""
		set bandera 0
		#Is it a var name or a value???
		
		
		for {set i 0} {$i < [string length $rec]} {incr i} {
			set car [string index $rec $i]
			if {$car != "="} {
				if {$bandera == 0} {
					#Var name
					append languageIndicator $car
				} else {
					#Value
					append value $car
				}
			} else {
				set bandera 1
				continue 
			}
		}
		
		if {$languageIndicator == "language"} {
			set realTSS "$realTSS\nlanguage=Languages/$languageSelected"
		} else {
			if {$rec == ""} {
				#nada
			} else {
				if {$realTSS == ""} {
					set realTSS "$rec"
				} else {
					set realTSS "$realTSS\n$rec"
				}
			}
		}
	}
	
	if {[file exists $filePath] > 0 && [file isfile $filePath] > 0} {
		set languages [open $filePath { RDWR TRUNC }]
	} else {
		set languages [open $filePath { RDWR CREAT }]
	}
	puts $languages $realTSS
	close $languages
	return [searchCommand SAVE_SUCCESSFUL]
}