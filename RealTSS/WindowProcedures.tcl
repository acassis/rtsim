################################################################################
#   FILE:
#
#         WindowProcedures.tcl
#
#    DESCRIPTION:
#
#       This file contains all the procedures that allow the interface interct
#	with the procedures of Utilities.tcl
#
#	To execute the program:
#
#         	This code only contains procedures that are called from
#		GraphicInterface.tcl, so if you execute this code, you won't see
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
#	helpRealTSSCommand
#	November 4, 2008
#	Call the procedures for show the help content
#	Parameters: 
#		None
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc helpRealTSSCommand { } {
	
}

##########################################################################
#	changeLanguageCommand
#	November 4, 2008
#	Call the procedures for change the language for the next restart
#	Parameters: 
#		None
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc changeLanguageCommand {} {
	global array config
	set messageError [changeLanguage "realtss.ini"]
	tk_messageBox -message "$messageError" -type ok
}

##########################################################################
#	saveTasksCommand
#	November 4, 2008
#	Call the procedures for save the tasks
#	Parameters: 
#		None
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc saveTasksCommand { } {
#	set tasks [returnTasksList [getTableTasksFrame]]
	global pathSavedTasks
	set tasks [returnTasksListForSave [getTableTasksFrame]]
	if {$pathSavedTasks !=""} {
		set messageError [saveTasksList $tasks]
	} else {
		set messageError [saveAsTasksList $tasks]
	}
	tk_messageBox -message "$messageError" -type ok
	
}

##########################################################################
#	saveAsTasksCommand
#	February 18, 2010
#	Call the procedures for save the tasks with other name
#	Parameters: 
#		None
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc saveAsTasksCommand { } {
	set tasks [returnTasksList [getTableTasksFrame]]
	set messageError [saveAsTasksList $tasks]
	tk_messageBox -message "$messageError" -type ok
}

##########################################################################
#	openTasksCommand
#	April 27, 2010
#	Call the procedures for open the tasks
#	Parameters: 
#		None
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc openTasksCommand { frameTasksTable frameResultBox} {
	newSetTasks $frameTasksTable $frameResultBox
	openFileTasklist
}

##########################################################################
#	printTasksCommand
#	February 18, 2010
#	Call the procedures for print the set of tasks
#	Parameters: 
#		None
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc printTasksCommand { } {
	set tasks [returnTasksList [getTableTasksFrame]]
	set messageError [saveTasksList $tasks]
	tk_messageBox -message "$messageError" -type ok
}

##########################################################################
#	simulationTypeCommand
#	February 18, 2010
#	Call the procedures for select the type of the simulation of the set of tasks
#	Parameters: 
#		None
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc simulationTypeCommand { item } {
	toplevel .prueba
	wm title .prueba test
	label .prueba.text -text "Here we will call the correspondent procedure of $item"
	pack .prueba.text -side top -fill both -expand 1
}

##########################################################################
#	schedulerAlgorithmsCommand
#	February 18, 2010
#	Call the procedures for change de scheduler algorithms to the simulation of the set of tasks
#	Parameters: 
#		None
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc schedulerAlgorithmsCommand { item } {
	toplevel .prueba
	wm title .prueba test
	label .prueba.text -text "Here we will call the correspondent procedure of $item"
	pack .prueba.text -side top -fill both -expand 1
}

##########################################################################
#	sharedResourcesCommand
#	February 18, 2010
#	Call the procedures for manage the shared resources used during the simulation of the set of tasks
#	Parameters: 
#		None
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc sharedResourcesCommand { item } {
	toplevel .prueba
	wm title .prueba test
	label .prueba.text -text "Here we will call the correspondent procedure of $item"
	pack .prueba.text -side top -fill both -expand 1
}

##########################################################################
#	insertRow
#	November 4, 2008
#	Insert a new row in the table in fact of the entrys
#	Parameters: 
#		frameParent - Is the parameter that contains the frame
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc insertRow { frameParent idEntry phaseEntry executionTimeEntry periodEntry deadLineEntry} {
#	global idEntry;
#	global phaseEntry;
#	global executionTimeEntry;
#	global periodEntry;
#	global deadLineEntry;
	if {[catch {$frameParent.table size} errmsg]} {
		set idEntry 1
	} else {
		set idEntry [expr [$frameParent.table size]+1]
	}
	if {$executionTimeEntry>0 && $periodEntry>0} {
#	if {$phaseEntry>0 && $executionTimeEntry>0 && $periodEntry>0} 
		$frameParent.table insert end [list  "$idEntry" "$phaseEntry" "$executionTimeEntry" "$periodEntry" "$periodEntry"]
	}
}

##########################################################################
#	indexSelectReturn
#	November 4, 2008
#	Returns the index of the row selected
#	Parameters: 
#		frameParent - Is the parameter that contains the frame
#	Returns:
#		indexSelected - Is the index of the current row selected
#	Messages:
#		None
##########################################################################
proc indexSelectReturn { frameParent } {
	set indexSelected [$frameParent.table curselection]
	return $indexSelected
}

##########################################################################
#	deleteRowSelected
#	November 4, 2008
#	Delete the row selected in the table
#	Parameters: 
#		frameParent - Is the parameter that contains the frame
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc deleteRowSelected { frameParent } {
	$frameParent.table delete [indexSelectReturn $frameParent]
	
	set taskList ""
	
	for {set i 0 } {$i<[$frameParent.table size]} { incr i} {
#		set taskList [$frameParent.table get [indexSelectReturn $frameParent] ]

		if {$taskList == ""} {
			set taskList "[$frameParent.table get $i ]"
		} else {
			set taskList "$taskList\n[$frameParent.table get $i ]"
		}
#		puts [ [$frameParent.table get $i] "\n"]
#		puts [concat [$frameParent.table get $i ] "\n"]
		
	}
	
#	set taskList ""
#	for {set i 0 } {$i<[$frameParent.table size]} { incr i} {
##		set taskList [$frameParent.table get [indexSelectReturn $frameParent] ]
#
#		if {$taskList == ""} {
#			set taskList "[$frameParent.table get $i ]"
#		} else {
#			set taskList "$taskList\n[$frameParent.table get $i ]"
#		}
#		puts [concat [$frameParent.table get $i ] "\n"]
#	}
#	return $taskList
	
	
}

##########################################################################
#	returnTasksList
#	November 4, 2008
#	Modified March 25, 2010
#	Returns in a string all the current tasks in the table
#	Parameters: 
#		frameParent - Is the parameter that contains the frame
#	Returns:
#		taskList - Is a string that contains all the tasks
#	Messages:
#		None
##########################################################################
proc returnTasksList { frameParent } {
	set taskList ""
	for {set i 0 } {$i<[$frameParent.table size]} { incr i} {
		for {set j 0 } {$j<[$frameParent.table columncount]} { incr j} {
			if {$taskList == ""} {
        			set taskList "[$frameParent.table getcells $i,$j]"
        		} else {
				if { $j == 0} {
					set taskList "$taskList\n[$frameParent.table getcells $i,$j]"
				} else {
					set taskList "$taskList\t[$frameParent.table getcells $i,$j]"
				}
        		}
		}
	}
#	puts $taskList
	return $taskList
}

##########################################################################
#	returnTasksListForSave
#	November 4, 2008
#	Modified March 25, 2010
#	Returns in a string all the current tasks in the table
#	Parameters: 
#		frameParent - Is the parameter that contains the frame
#	Returns:
#		taskList - Is a string that contains all the tasks
#	Messages:
#		None
##########################################################################
proc returnTasksListForSave { frameParent } {
	set taskList ""
	for {set i 0 } {$i<[$frameParent.table size]} { incr i} {
		if {$taskList == ""} {
			set taskList "[$frameParent.table getcells $i,3] [$frameParent.table getcells $i,2]"
		} else {
			set taskList "$taskList\n[$frameParent.table getcells $i,3] [$frameParent.table getcells $i,2]"
		}
#		for {set j 0 } {$j<[$frameParent.table columncount]} { incr j} {
#			if {$taskList == ""} {
#				
#				if { $j==2 } {
#					set taskList "[$frameParent.table getcells $i,$j]"
#				} else {
#					if { $j==3 } {
#						set taskList " [$frameParent.table getcells $i,$j]"
#					}
#				}
#        			
#        		} else {
#				if { $j == 2 } {
#					set taskList "$taskList\n[$frameParent.table getcells $i,$j]"
#				} else {
#					if { $j ==3 } {
#						set taskList "$taskList [$frameParent.table getcells $i,$j]"
#					}
#				}
#        		}
#		}
	}
#	puts $taskList
	return $taskList
}

##########################################################################
#	simulate
#	May 10, 2010
#	Run the library of the selected algorithm
#	Parameters: 
#		frameParent - Is the parameter that contains the frame
#		pathSavedTasks - Path of the set of tasks
#		schedSelected - algorithm library name to simulate
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc simulate { pathSavedTasks schedSelected frameResultsBox} {
	
	global APP_PATH
	global LibFolder
	global numberProcessors
	global simulationTime
#	global pathSavedTrace
	set resultAlg ""
	#usar siempre test4.txt como ejemplo
	set pathSavedTasks "/home/kary/simulador/RealTSS/test4.txt"
	deleteResultsBox $frameResultsBox
	
	#el nombre de la libreria siempre debera ser lib+nombredelplanificador
	set libName lib$schedSelected
	set cmdName $schedSelected
	
	if { $libName != "" } {
		if { $schedSelected != ""} {
			if { $numberProcessors>0 && $simulationTime>=0 } {
			# Load the extension
			# switch $tcl_platform(platform) {
			   # windows {
				#  load [file join [pwd] $APP_PATH/AlgorithmsLibraries/$libName.so]
			   # }
			   # unix {
				  # load [file join [pwd] lib+$libName[info sharedlibextension]]
			   # }
			# }
			
			### Cargar la libreria de C
				puts "Cargando $libName ..."
				set r [catch {load $LibFolder/$libName[info sharedlibextension]} err]
				# set r [catch {load $APP_PATH/AlgorithmsLibraries/$libName} err]
				
				### Si ocurrio un error
				if {$r} {
					tk_messageBox -icon error -title "Error" -message $err
				}

        		### Ejecutar el comando de la libreria		
				puts "Ejecutando $cmdName $schedSelected $numberProcessors $simulationTime $pathSavedTasks"
        		set r [catch {eval $cmdName $schedSelected $numberProcessors $simulationTime $pathSavedTasks } errmsg]
				
				### Cargar el log  en la interface
				set r [catch { cargarLog [getResultsBoxFrame] } errmsg]

				### Si ocurrio un error
				if {$r} {
					tk_messageBox -icon error -title "Error" -message $errmsg
				}
			}
		}
	}
#	return 0
}

proc deleteResultsBox { frameParent } {
	if { [$frameParent.trace.textoTrace get 0.0 {end -1c}]!="" } {
		$frameParent.trace.textoTrace delete 0.0 {end -1c}
	} else {
		$frameParent.trace.textoTrace delete end
	}
	
}

proc cargarLog { frameParent } {

#Open file...
	set archName "logs.txt" ;	#Name is fixed... realtss.ini
	set archExist [file exists $archName]
	#$frameParent.trace.textoTrace insert end "Cargando archivo...\n"
	if {$archExist > 0} {
		set arch [open $archName { RDWR CREAT } ]
		set tipo 0
		while { [gets $arch line ] >= 0} {
			$frameParent.trace.textoTrace insert end $line\n
    		} 
		close $arch
	} else {
		$frameParent.trace.textoTrace insert end [searchCommand CANT_LOAD_LOG]
	}
}

proc insertResultsBox { frameParent result} {
	$frameParent.trace.textoTrace insert end $result\n
}

proc newSetTasks {frameTasksEntrys frameResultsBox } {
        global schedSelected;
        global pathSavedTasks
        global idEntry;
        global phaseEntry;
        global executionTimeEntry;
        global periodEntry;
        global deadLineEntry;
	global pathSavedTrace
	
	set deadLineEntry 0
	set periodEntry 0
	set executionTimeEntry 0
	set phaseEntry 0
	set idEntry 0
	set pathSavedTasks ""
	set pathSavedTrace ""
	
	deleteResultsBox $frameResultsBox
	$frameTasksEntrys.table delete 0 end
}

proc loadTraceKiwi { } {
	global pathSavedTasks
	global array config
	global pathSavedTrace
	puts $config(kiwi)
	if {$config(kiwi) != ""} {
		if {$pathSavedTrace == ""} {
			tk_messageBox -message "There is not tasks saved..." -type ok
			return
		}
		puts "\n\nsss\n$pathSavedTrace"
		set tmp [file exists $config(kiwi)]
		if {$tmp <= 0} {
			tk_messageBox -message "Could not find KIWI..." -type ok
			return
		}
		set dir [file dirname $config(kiwi)]
		set arch [file tail $config(kiwi)]
		set kiwiarch [file join $dir $arch]
		set wishapp $config(wish)
		###Plataform????
#		set plat [string toupper $tcl_platform(platform)]
#		###Is it windows???
#		if {$plat eq "WINDOWS"} {
#			###add wish to the exec 
#			exec $wishapp $kiwiarch $pathSavedTasks
#		} else {
			###Just need kiwi and the trace log
			puts "$kiwiarch - $pathSavedTrace"
			exec $kiwiarch $pathSavedTrace
#		}
		
		# $entorno(archtraza)
	} else {
		#### Kiwi not defined
		tk_messageBox -message "KIWI PATH not specified..." -type ok
	}
}

##########################################################################
#	OLD CODE OF TASK LIST RETURN
##########################################################################
proc returnTasksList_OLDD_CODE { frameParent } {
	set taskList ""
	for {set i 0 } {$i<[$frameParent.table size]} { incr i} {
#		set taskList [$frameParent.table get [indexSelectReturn $frameParent] ]
		if {$taskList == ""} {
    			set taskList "[$frameParent.table get $i ]"
    		} else {
    			set taskList "$taskList\n[$frameParent.table get $i ]"
    		}
		puts [concat [$frameParent.table get $i ] "\n"]
	}
	return $taskList
}

proc testCodeButton { frameParent } {
	set rtsExtension [searchCommand WINDOW_DIALOG_EXTENSION_RTS]
	set txtExtension [searchCommand WINDOW_DIALOG_EXTENSION_TXT]
        set types { 
		{{rtsExtension} {.rts} }
		{{[$txtExtension]} {.txt} }
	}
	puts $types
}