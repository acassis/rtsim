################################################################################
#
#	FILE:
#
#	GraphicInterface.tcl
#
#	his file contains the procedure that paint the interface to show to the
#	user, by this the user can probe the simulator 
#
#	To execute the program:
#
#         	This code only contains a procedure that is called from
#		RealTSS.tcl, so if you execute this code, you won't see nothing
#		in display because there are only procedures that have to be
#		called from another program.
#
#	See README file for details.
#
#	Copyright (C) 2008
#
#	Oskardie Castro, Ruben Batista, Arnoldo Diaz
#
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
#	LAST REVISION:    July 2007
#
################################################################################
package require Tk
package require tablelist
package require Tcl

global array entorno ;		#Array to store framewrok variables
global array config
global APP_PATH ;		#Application Path

global algorithmsAvailables;
set algorithmsAvailables 1


#Current path.
set APPPATH ""
set ENT_PATH ""
set script_name [file tail [info script]]
if { [lsearch -exact [array names env] ENTPATH]==-1 } { 
	set APP_PATH [file dirname [info script]]
} else {
	set APP_PATH $env(ENTPATH)
}

lappend auto_path $APP_PATH

#Takes the contents of the specified file
source $APP_PATH/Utilities.tcl
source $APP_PATH/WindowProcedures.tcl
source $APP_PATH/WindowProcedures.tcl
source $APP_PATH/AlgorithmsLibraries/pkgIndex.tcl

initConfig
cargarIni
loadAlgorithms


global AlgorithmInfo;		#This array will contains all the algorithm INFO indicated in the file Algorithms.conf
global pathSavedTrace;
global languagesAvailables;	#This array will contains all the names of the Languages indicated in the file Languages.conf
global languageSelected;	#This var will contains the name of the selected language by the user in the program
global schedSelected;	#This var will conatins the name of the algorithm selected by the user
global typeTestSelected;	#This var will contains the type of test selected by the user
global pathSavedTasks
global simulationTime
global numberProcessors
set numberProcessors 1
set pathSavedTrace ""
set simulationTime 0
set pathSavedTasks ""
global commandsLanguage	;	#This array contains all the commands depending of the language indicated in realtss.ini
global width ;			#This var contains the width of the display
global height ;			#This var contains the height of the display
global algLibraryNames ;
global algLibraryCount ;
global idEntry;
global phaseEntry;
global executionTimeEntry;
global periodEntry;
global deadLineEntry;
global array taskListArray

set commandsLanguage(IDROW) 0 ;		#Assign a element to array that indicate the row in the array
set commandsLanguage(IDCOL) 0 ; 	#Assign a element to array that indicate the column in the array
set languagesAvailables(IDROW) 0;	#Assign a element to array that indicate the row in the array
set languagesAvailables(IDCOL) 0;	#Assign a element to array that indicate the column in the array
set AlgorithmInfo(IDROW) 0 ;		#Assign a element to array that indicate the row in the array
set AlgorithmInfo(IDCOL) 0 ;		#Assign a element to array that indicate the column in the array
loadLanguage $config(language)
loadNameAlgorithms $config(algorithmsName)
countAlgorithms $config(algorithmsName)
loadLangaugesAvailables $config(languagesContainer)
set LibFolder  $config(libFolder)

#no usados
set fullLibFile $config(fulllibfile)
set fullLibCommand $config(fulllibcommnad)

##########################################################################
#	initializationProcedures
#	November 4, 2008
#	This will initialice the window interface, and call all the others
#	procs
#	Parameters: 
#		frames - Is the parameter that contains the frame
#		content - This is a array that contains the names of the headers
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc initializationProcedures { } {
	global screenSize
	global width
	global height
	
	global idEntry;
	global phaseEntry;
	global executionTimeEntry;
	global periodEntry;
	global deadLineEntry;
	
	set idEntry 1
	set phaseEntry 0
	set executionTimeEntry 0
	set periodEntry 0
	set deadLineEntry 0
	
	wm withdraw .	;					#Hides the window parent	
	toplevel .realtss ;					#Set at top level the window
	wm title .realtss [searchCommand REALTSS_SIMULATOR];	#Put the title of the window
	#set width [expr {[winfo screenwidth .] - 8}] ;		#This var is for obtain the width of the actual resolution
	set width 800
	#set height [expr {[winfo screenheight .] - 100}] ;	#This var is for obtain the height of the actual resolution
	set height 600
	wm minsize .realtss $width $height
	#We add direct access to some process
	
	makeMenuBar .realtss .	;				#Create the frame menu bar in the window
	#makeToolsBar .realtss	;				#Create the frame tools bar in the window
	makeDirectAcceses .realtss ;				#Create the frame access for some functions
	
	
	makeFramesAll .realtss
	makeButtonsTasks .realtss
	#makeButtonsBar [getToolsBarFrame]
	
	makeTableTasks [getTableTasksFrame]
	
	makeTasksEntrys [getEntryTasksFrame]
	makeResultsBox [getResultsBoxFrame]
}

##########################################################################
#	makeDirectAcceses
#	November 4, 2008
#	This will make the direct access for the user, for using some keys
#	of the keyboard to access to some functions
#	Parameters: 
#		frameParent - Is the parameter that contains the frame
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc makeDirectAcceses {frameParent} {
	bind .realtss <F1> aboutRealTSSWindow
}

##########################################################################
#	makeTasksEntrys
#	November 4, 2008
#	Makes the entrys for each column of the table tasks
#	Parameters: 
#		frameParent - Is the parameter that contains the frame
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc makeTasksEntrys { frameParent } {
	global idEntry;
	global phaseEntry;
	global executionTimeEntry;
	global periodEntry;
	global deadLineEntry;
	#Tasks entry labels
	label $frameParent.taskID.taskIDLabel -text "[searchCommand TASK_ID]"
	pack $frameParent.taskID.taskIDLabel -side top -padx 3 -pady 1
	label $frameParent.phase.phaseLabel -text "[searchCommand TASK_PHASE]"
	pack $frameParent.phase.phaseLabel -side top -padx 3 -pady 1
	label $frameParent.timeExecution.timeExecutionLabel -text "[searchCommand TASK_EXECUTION_TIME]"
	pack $frameParent.timeExecution.timeExecutionLabel -side top -padx 3 -pady 1
	label $frameParent.period.periodLabel -text "[searchCommand TASK_PERIOD]"
	pack $frameParent.period.periodLabel -side top -padx 3 -pady 1
	label $frameParent.deadLine.deadLineLabel -text "[searchCommand TASK_DEADLINE]"
	pack $frameParent.deadLine.deadLineLabel -side top -padx 3 -pady 1
	
	#Task Entrys
	#TaskID
	entry $frameParent.taskID.taskID -bd 2 -width 5 -textvariable IDs -state readonly -relief sunken -width 10
	pack $frameParent.taskID.taskID -side bottom -padx 12 -pady 1 
	#Phase
#	entry $frameParent.phase.phase -bd 2 -bg white -width 5 -validate key -vcmd {string is double %P} -textvariable phaseEntry -relief sunken -width 10
	entry $frameParent.phase.phase -bd 2 -bg white -width 5  -textvariable phaseEntry -state readonly -relief sunken -width 10
	pack $frameParent.phase.phase -side bottom -padx 12 -pady 1 
	#Execution Time
	entry $frameParent.timeExecution.timeExecution -bd 2 -bg white -width 5 -validate key -vcmd {string is double %P} -textvariable executionTimeEntry -relief sunken -width 10
	pack $frameParent.timeExecution.timeExecution -side bottom -padx 12 -pady 1 
	#Period
	entry $frameParent.period.period -bd 2 -bg white -width 5 -validate key -vcmd {string is double %P} -textvariable periodEntry -relief sunken -width 10
	pack $frameParent.period.period -side bottom -padx 12 -pady 1 
	#Deadline
	entry $frameParent.deadLine.deadLine -bd 2 -bg white -width 5 -state readonly -textvariable periodEntry -relief sunken -width 10
	pack $frameParent.deadLine.deadLine -side bottom -padx 12 -pady 1
}

##########################################################################
#	makeTableTasks
#	November 4, 2008
#	Makes a table based on tablelist
#	Parameters: 
#		frameParent - Is the parameter that contains the frame
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc makeTableTasks { frameParent } {
	global width
	global height
	set columns [list]
#	tablelist::tablelist $frameParent.table -columns { 0  -title $phase 0 "[ TASK_PHASE]" 0 "[ TASK_EXECUTION_TIME]" 0 "[ TASK_PERIOD]" 0 "[ TASK_DEADLINE]"} -background white  -width [expr $width/16 ] -height [expr $height/45 ]
	#We adds the column's names
	lappend columns 0 [searchCommand TASK_ID] center
	lappend columns 15 [searchCommand TASK_PHASE] center
	lappend columns 15 [searchCommand TASK_EXECUTION_TIME] center
	lappend columns 15 [searchCommand TASK_PERIOD] center
	lappend columns 15 [searchCommand TASK_DEADLINE] center
	tablelist::tablelist $frameParent.table -columns $columns -background white  -width [expr $width/16 ] -height [expr $height/45 ]
	frame $frameParent.scroll
	scrollbar $frameParent.scroll.sy -orient vertical -command [list $frameParent.table yview] -elementborderwidth 1
#	scrollbar $frameParent.scroll.sx -orient horizontal -command [list $frameParent.table xview] -elementborderwidth 1
	# Create small widget for the upper right corner:
	ttk::label $frameParent.scroll.corner -style TablelistHeader.TLabel
	pack $frameParent.scroll.corner -side top -fill x
#	pack $frameParent.scroll.corner -side right -fill y
	$frameParent.table columnconfigure 1 -maxwidth 30 -editable yes
	$frameParent.table columnconfigure 2 -maxwidth 30 -editable yes
	$frameParent.table columnconfigure 3 -maxwidth 30 -editable yes
	
	pack $frameParent.scroll.sy -side top -fill y -expand 1
#	pack $frameParent.scroll.sx -side bottom -fill x -expand 1
	pack $frameParent.scroll -side right -fill y -pady {0 20}
#	pack $frameParent.scroll -side bottom -fill x -padx {0 20}
	$frameParent.table configure -yscrollcommand [list $frameParent.scroll.sy set]
#	$frameParent.table configure -xscrollcommand [list $frameParent.scroll.sx set]
	$frameParent.table configure -title 0 
	pack $frameParent.table
}

##########################################################################
#	makeButtonsInformation
#	November 4, 2008
#	Makes a table based on labels
#	Parameters: 
#		frameParent - Is the parameter that contains the frame
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc makeButtonsInformation { frameParent args } {
	button $frameParent.informationContainer.showUtilization.utilization -text "[searchCommand SHOW_PROCESS_UTILIZATION]" -command { testButtons [searchCommand SHOW_PROCESS_UTILIZATION] }
	pack $frameParent.informationContainer.showUtilization.utilization -padx 10 -pady 10
	button $frameParent.informationContainer.showTrace.trace -text "[searchCommand SHOW_TRACE]" -command { testButtons [searchCommand SHOW_TRACE] }
	pack $frameParent.informationContainer.showTrace.trace -padx 10 -pady 10
	button $frameParent.informationContainer.showResults.results -text "[searchCommand SHOW_RESULTS]" -command { testButtons [searchCommand SHOW_RESULTS] }
	pack $frameParent.informationContainer.showResults.results -padx 10 -pady 10
}

##########################################################################
#	makeButtonsTasks
#	November 4, 2008
#	Makes the buttons that will give to the user the control to add
#	and remove tasks
#	Parameters: 
#		frameParent - Is the parameter that contains the frame
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc makeButtonsTasks { frameParent args} {
	global width
	global height
	global APP_PATH
	
	global idEntry;
	global phaseEntry;
	global executionTimeEntry;
	global periodEntry;
	global deadLineEntry;
	image create photo addIcon -format gif -file "$APP_PATH/Icons/addIcon.gif"
	image create photo removeIcon -format gif -file "$APP_PATH/Icons/removeIcon.gif"
	button $frameParent.tasksContainer.buttons.addTask -image addIcon -text "[searchCommand ADD]" -command { insertRow [getTableTasksFrame] $idEntry $phaseEntry $executionTimeEntry $periodEntry $deadLineEntry } -borderwidth 3 -width 40 -height 40
	pack $frameParent.tasksContainer.buttons.addTask -padx 15 -pady 30  -side top
#	button $frameParent.tasksContainer.buttons.deleteTask -image removeIcon -text "[searchCommand DELETE]" -command { returnTasksList [getTableTasksFrame]} -borderwidth 3 -width 40 -height 40
	button $frameParent.tasksContainer.buttons.deleteTask -image removeIcon -text "[searchCommand DELETE]" -command { deleteRowSelected [getTableTasksFrame]} -borderwidth 3 -width 40 -height 40
	
	pack $frameParent.tasksContainer.buttons.deleteTask -padx 15 -pady 30  -side bottom
	###deleteRowSelected [getTableTasksFrame]
}

##########################################################################
#	helpRealTSSWindow
#	September 21, 2008
#	Shows the help for the user that how to use the application
#	Parameters: 
#		None
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc helpRealTSSWindow { } {
	
}

##########################################################################
#	aboutRealTSSWindow
#	September 21, 2008
#	Shows the about file of RealTSS
#	Parameters: 
#		None
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc aboutRealTSSWindow { } {
	global APP_PATH
	set about [open "$APP_PATH/HelpContent/[searchCommand ABOUT_FILE]"]
	set aboutContent [read $about]
	close $about
	toplevel .about
	wm title .about [searchCommand ABOUT_REALTSS]
	label .about.text -text "$aboutContent"
	pack .about.text -side top -fill both -expand 1
	button .about.ok -text OK -command about_ok
	pack .about.ok -side bottom -expand 1
	bind .about <Return> about_ok
	wm title .about [searchCommand ABOUT_REALTSS]
	proc about_ok {} {destroy .about}
	wm deiconify .about

}

##########################################################################
#	languageSelectionWindow
#	November 21, 2008
#	Shows the about file of RealTSS
#	Parameters: 
#		None
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc languageSelectionWindow { } {
	toplevel .languageWindow
	wm title .languageWindow [searchCommand LANGUAGE_MENU]
	wm minsize .languageWindow 300 150
	
	#We make a frame that will contain the listbox
	frame .languageWindow.frameList -bd 4 -width 300 -height 100 -relief sunken
	pack .languageWindow.frameList -padx 1 -pady 5
	
	#We put a scrollbar to the listbox
	scrollbar .languageWindow.frameList.scrollbarlist3 -command { .languageWindow.frameList.listLanguage yview } -orient vertical 
	pack .languageWindow.frameList.scrollbarlist3 -side left
	
	#We create a listbox with the scrollbar
	listbox .languageWindow.frameList.listLanguage -selectmode single -bd 2 -bg white -yscrollcommand { .languageWindow.frameList.scrollbarlist3 set} -width 10 -height 3 -relief sunken	
	pack .languageWindow.frameList.listLanguage -side left -padx 1 -pady 10 

	#Inserts each of ones languages availables in the Languages.conf
	global languagesAvailables	
	set nLanguages [expr [array size languagesAvailables]/2-1]
	for {set i 0} {$i<$nLanguages} {incr i} {
		#Each of one languages will showed at the listbox
		.languageWindow.frameList.listLanguage insert end $languagesAvailables($i,1) 
	}
	
	#When the user select some language, it will be changed at the variable languageSelected
	bind .languageWindow.frameList.listLanguage <<ListboxSelect>> {
		global languageSelected
		set indice [.languageWindow.frameList.listLanguage curselection]
		set languageSelected $languagesAvailables($indice,1)
	}
	#Create a button that will be write at the realtss.ini the changes for the language selected
	button .languageWindow.select -text [searchCommand LOAD_LANGUAGE] -command { 
		changeLanguageCommand
		destroy .languageWindow
	}
	pack .languageWindow.select -side bottom -expand 1
	wm deiconify .languageWindow
}

proc simulationSetting { } {
	global numberProcessors
	global simulationTime
	toplevel .simulationWindow
	wm title .simulationWindow [searchCommand SCHEDULER_SETTINGS]
	wm minsize .simulationWindow 300 200
	
	#We make a frame that will contain the listbox
	frame .simulationWindow.frameList -bd 4 -width 300 -height 150 -relief sunken
	pack .simulationWindow.frameList -padx 1 -pady 5
	
	#We put a scrollbar to the listbox
	label .simulationWindow.frameList.tS -text "[searchCommand SIMULATION_TIME]"
	pack .simulationWindow.frameList.tS  -side bottom -padx 12 -pady 1
	entry .simulationWindow.frameList.timeSimulator -bd 2 -bg white -width 5 -validate key -vcmd {string is double %P} -textvariable simulationTime -relief sunken -width 10
	pack .simulationWindow.frameList.timeSimulator -side bottom -padx 12 -pady 1
	
	label .simulationWindow.frameList.nP -text "[searchCommand NO_PROCESSORS_MENU]"
	pack .simulationWindow.frameList.nP  -side bottom -padx 12 -pady 1
	entry .simulationWindow.frameList.numberP -bd 2 -bg white -width 5 -validate key -vcmd {string is double %P} -textvariable numberProcessors -relief sunken -width 10
	pack .simulationWindow.frameList.numberP -side bottom -padx 12 -pady 1
	
	
	#Create a button that will be write at the realtss.ini the changes for the language selected
	button .simulationWindow.ok -text [searchCommand SAVE] -command { 
		puts "$numberProcessors - $simulationTime"
		destroy .simulationWindow
	}
	pack .simulationWindow.ok -side bottom -expand 1
	wm deiconify .simulationWindow
}

proc makeButtonsBar {frameParent args} {
	global width
	image create photo exitIcon -format gif -file "Icons/exitIcon.gif"
	image create photo cancelIcon -format gif -file "Icons/cancelIcon.gif"
	image create photo okIcon -format gif -file "Icons/okIcon.gif"
	image create photo resultsIcon -format gif -file "Icons/resultsIcon.gif"
	image create photo saveIcon -format gif -file "Icons/saveIcon.gif"
	image create photo simulateIcon -format gif -file "Icons/simulateIcon.gif"
	image create photo toolsIcon -format gif -file "Icons/toolsIcon.gif"
	image create photo traceIcon -format gif -file "Icons/traceIcon.gif"
	image create photo utilizationIcon -format gif -file "Icons/utilizationIcon.gif"
	
	button $frameParent.saveButton -image saveIcon -width 50 -height 50 -borderwidth 3 -command { saveTasksCommand }
	pack $frameParent.saveButton -side left
	button $frameParent.cancelButton -image cancelIcon -width 50 -height 50  -borderwidth 3
	pack $frameParent.cancelButton -side left
	button $frameParent.okButton -image okIcon -width 50 -height 50 -borderwidth 3
	pack $frameParent.okButton -side left
	button $frameParent.toolsButton -image toolsIcon -width 50 -height 50 -borderwidth 3
	pack $frameParent.toolsButton -side left
	button $frameParent.resultsButton -image resultsIcon -width 50 -height 50 -borderwidth 3
	pack $frameParent.resultsButton -side left
	button $frameParent.simulateButton -image simulateIcon -width 50 -height 50 -borderwidth 3
	pack $frameParent.simulateButton -side left
	button $frameParent.traceButton -image traceIcon -width 50 -height 50 -borderwidth 3
	pack $frameParent.traceButton -side left
	button $frameParent.utilizationButton -image utilizationIcon -width 50 -height 50 -borderwidth 3
	pack $frameParent.utilizationButton -side left
	button $frameParent.exitButton -image exitIcon -width 50 -height 50 -borderwidth 3
	pack $frameParent.exitButton -side left
	frame $frameParent.vacio -width $width -height 50
	pack $frameParent.vacio -side right
}

##########################################################################
#	makeToolsBar
#	December 5, 2008
#	Create a tools bar like world
#	Parameters: 
#		frameParent - Is the parameter that contains the frame
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc makeToolsBar { frameParent args} {
	global width
	global height
	frame $frameParent.toolBar -bd 1 -width $width -height [expr $height/22 ] -relief sunken
	pack $frameParent.toolBar -padx 3 -pady 3
}

##########################################################################
#	makeMenuBar
#	November 4, 2008
#	Create a menu bar in the window that was sent by parameter
#	Parameters: 
#		frameParent - Is the parameter that contains the frame
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc makeMenuBar { frameParent parent args} {
	global schedSelected;		#This variable contains the algorithm that is selected by the user
	global algorithmsAvailables;
	global typeTestSelected;
	global pathSavedTasks
	menu $frameParent.menu -tearoff 0
	#Establishing the items vars on the menu bar and submenus
	set files $frameParent.menu.files
	set settings $frameParent.menu.settings
	set run $frameParent.menu.run
	set build $frameParent.menu.build
	set help $frameParent.menu.helps
	set view $frameParent.menu.view
	
	
	set tools $frameParent.menu.tools
	set algorithms $frameParent.menu.build.algorithms
	set typeTest $frameParent.menu.build.typeTest
	
	
	menu $files -tearoff 0
	menu $settings -tearoff 0
	menu $run -tearoff 0
	menu $build -tearoff 0
	menu $help -tearoff 0
	menu $view -tearoff 0
	
	menu $tools -tearoff 0
	menu $algorithms -tearoff 0
	menu $typeTest -tearoff 0
	
	#Puts all the name of menus
	$frameParent.menu add cascade -label "[searchCommand FILE]" -menu $files -underline 0
	#Menu build is the same that menu Edit
	$frameParent.menu add cascade -label "[searchCommand BUILD_MENU]" -menu $build -underline 0
	$frameParent.menu add cascade -label "[searchCommand VIEW_MENU]" -menu $view -underline 0
	$frameParent.menu add cascade -label "[searchCommand RUN_MENU]" -menu $run -underline 0
	$frameParent.menu add cascade -label "[searchCommand SETTINGS_MENU]" -menu $settings -underline 0
	$frameParent.menu add cascade -label "[searchCommand TOOLS_MENU]" -menu $tools -underline 0
	$frameParent.menu add cascade -label "[searchCommand HELP]" -menu $help -underline 0
	
	
	#File items menu
	$files add command -label "[searchCommand NEW]" -command { newSetTasks  [getTableTasksFrame] [getResultsBoxFrame] } -underline 0 ;	#New set of tasks option
	$files add command -label "[searchCommand OPEN]" -command { openTasksCommand [getTableTasksFrame] [getResultsBoxFrame] } -underline 0;	#Open file option 
	$files add command -label "[searchCommand SAVE]" -command { saveTasksCommand } -underline 1 ;			#Save file optiom
	$files add command -label "[searchCommand SAVE_AS]" -command { saveAsTasksCommand } -underline 1 ;		#Save as file option
#	$files add command -label "TEST BUTTON" -command { testCodeButton [getTableTasksFrame] } -underline 1 ;		#Save as file option
	
	$files add separator
	$files add command -label "[searchCommand PRINT]" -command { printTasksCommand } -underline 1 -state disabled;			#Print option
	$files add separator
	$files add command -label "[searchCommand EXIT]" -command "destroy $parent"
	
	#Settings items menu
	$settings add command -label "[searchCommand SCHEDULER_SETTINGS]" -command { simulationSetting } -underline 1 ;				#Build option
#	$settings add command -label "[searchCommand NO_PROCESSORS_MENU]" -command {  } -underline 1 ;			#NO_PROCESSORS option
	
	#Run items menu
	#$run add command -label "[searchCommand SIMULATE]" -command { simulate $pathSavedTasks [searchAlgLib $schedSelected] $schedSelected [getResultsBoxFrame] } -underline 1 ;					#Simulate option
	
	#run using full library
	#$run add command -label "[searchCommand SIMULATE]" -command { simulate $pathSavedTasks $fullLibFile $schedSelected [getResultsBoxFrame] } -underline 1 ;					#Simulate option
	#run using partial library
	$run add command -label "[searchCommand SIMULATE]" -command { simulate $pathSavedTasks $schedSelected [getResultsBoxFrame] } -underline 1 ;					#Simulate option
	$view add command -label "[searchCommand OPEN_KIWI]" -command { loadTraceKiwi } -underline 1 ;				#Open kiwi option
	
	#Build items menu
	#$build add command -label "[searchCommand SIMULATION]" -command { testButtons [searchCommand SIMULATION] } -underline 0 ;			#Execute option
	$build add command -label "[searchCommand SIMULATION_TYPE]" -command { simulationTypeCommand [searchCommand SIMULATION] } -underline 0 -state disabled;	#Simulation type option
	$build add command -label "[searchCommand SCHEDULER_ALGORITHMS]" -command { schedulerAlgorithmsCommand [searchCommand SCHEDULER_ALGORITHMS] } -underline 0 -state disabled;	#Scheduler Algorithms option
	$build add command -label "[searchCommand SHARED_RESOURCES]" -command { sharedResourcesCommand [searchCommand SHARED_RESOURCES] } -underline 0 -state disabled;	#Shared Resources option
	#$build add command -label "[searchCommand FEASIBILITY_TEST]" -command { testButtons [searchCommand FEASIBILITY_TEST] } -underline 0
	$build add cascade -label "[searchCommand TYPE_TEST]" -menu $typeTest -underline 0 -state disabled;								#Type of Test option
		$build.typeTest add radio -value 1 -label [searchCommand ACCURATE] -variable typeTestSelected
		$build.typeTest add radio -value 2 -label [searchCommand INACCURATE] -variable typeTestSelected
	
	$build add cascade -label "[searchCommand ALGORITHMS_MENU]" -menu $algorithms -underline 0
		#Here we load all the algorithms name that are in the Algorithms.conf and list as a radiobuttons
		global algLibraryNames ;
		global algLibraryCount ;
		#set nAlghoritms [expr [array size algLibraryNames]/2-3]
		for {set i 0} {$i < $algLibraryCount} {incr i} {
		
			if {$algLibraryNames($i,0) != ""} {
				#Each of one algorithms will be put a value on the variable schedSelected and this will contain the algorithm selected
				$frameParent.menu.build.algorithms add radio -value $algLibraryNames($i,1) -label $algLibraryNames($i,0) -variable schedSelected -command {  }
			} else {
				$frameParent.menu.build.algorithms add separator
			}
		}
		set schedSelected $algLibraryNames(0,1)
		
		puts "Algoritmo seleccionado $algLibraryNames(0,1)"
	
	
	
	#Tools items menu
	$tools add command -label "[searchCommand LANGUAGE_MENU]" -command {  languageSelectionWindow } -underline 0
	$tools add command -label "[searchCommand PREFERENCES_MENU]" -command {  languageSelectionWindow } -underline 0 -state disabled
	
	#Help items menu
	$help add command -label "[searchCommand HELP_CONTENTS]" -underline 0 -command { testButtons [searchCommand HELP_CONTENTS] } -state disabled
	$help add command -label "[searchCommand ABOUT_REALTSS]" -command { aboutRealTSSWindow } -underline 0
	
	#And here we put in its place
	$frameParent configure -menu $frameParent.menu
}

##########################################################################
#	makeResultsBox
#	April 27, 2010
#	Create the boxes to show the results
#	Parameters: 
#		frameParent - Is the parameter that contains the frame
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc makeResultsBox { frameparent args} {
	#scrollbar $frameparent.trace.scrollbarTrace -command {$frameparent.trace.textoTrace yview} -orient vertical 
	#pack $frameparent.trace.scrollbarTrace -side left
	label $frameparent.trace.labtxt2 -bd 2 -text " [searchCommand RESULTS] "
	text $frameparent.trace.textoTrace -bg white -width 50 -height 20
	pack $frameparent.trace.labtxt2 -side top
	pack $frameparent.trace.textoTrace -padx 10 -pady 1
	
	#scrollbar $frameparent.statistics.scrollbarStatistics -command {$frameparent.trace.textoStatistics yview} -orient vertical 
	#pack $frameparent.statistics.scrollbarStatistics -side left
#	label $frameparent.statistics.labtxt3 -bd 2 -text " [searchCommand RESULTS] "
	text $frameparent.statistics.textoStatistics -bg white -width 50 -height 20
#	pack $frameparent.statistics.labtxt3 -side top
	pack $frameparent.statistics.textoStatistics -padx 10 -pady 1
}

##########################################################################
#	makeFramesAll
#	November 4, 2008
#	Create all the frames that will contain the tasks, buttons, and all
#	Parameters: 
#		frameParent - Is the parameter that contains the frame
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc makeFramesAll { frameParent args} {
	global width
	global height
	
	#Creates the global containers
	frame $frameParent.tasksContainer -bd 5 -width [expr $width/1.5 ] -height [expr $height/1.7 ] -relief sunken
	pack $frameParent.tasksContainer -padx 20 -pady 15
	
	#Create the container of tasks
	frame $frameParent.tasksContainer.buttons -bd 8 -width [expr $width/8 ] -height [expr $height/4] -relief sunken
	pack $frameParent.tasksContainer.buttons -padx 5 -pady 15  -side left
	frame $frameParent.tasksContainer.table -bd 6 -width [expr $width/1.9 ] -height [expr $height/1.8 ] -relief sunken
	pack $frameParent.tasksContainer.table -padx 10 -pady 10 -side right
	
	#Create the frames of the lists and headers
	frame $frameParent.tasksContainer.table.tableTasks -bd 4 -width [expr $width/1.9 ] -height [expr $height/3 ] -relief sunken
	pack $frameParent.tasksContainer.table.tableTasks -padx 10 -pady 5
	frame $frameParent.tasksContainer.table.entrys -bd 3 -width [expr $width/1.9 ] -height [expr $height/15 ] -relief sunken
	pack $frameParent.tasksContainer.table.entrys -padx 10 -pady 10
	
	#Create the frames of the entrys
	frame $frameParent.tasksContainer.table.entrys.taskID -bd 1 -width [expr $width/10 ] -height [expr $height/18 ] -relief sunken
	pack $frameParent.tasksContainer.table.entrys.taskID -padx 2 -pady 2 -side left
	frame $frameParent.tasksContainer.table.entrys.phase -bd 1 -width [expr $width/10] -height [expr $height/18 ] -relief sunken
	pack $frameParent.tasksContainer.table.entrys.phase -padx 2 -pady 2 -side left
	frame $frameParent.tasksContainer.table.entrys.timeExecution -bd 1 -width [expr $width/10 ] -height [expr $height/18 ] -relief sunken
	pack $frameParent.tasksContainer.table.entrys.timeExecution -padx 2 -pady 2 -side left
	frame $frameParent.tasksContainer.table.entrys.period -bd 1 -width [expr $width/10 ] -height [expr $height/18 ] -relief sunken
	pack $frameParent.tasksContainer.table.entrys.period -padx 2 -pady 2 -side left
	frame $frameParent.tasksContainer.table.entrys.deadLine -bd 1 -width [expr $width/10 ] -height [expr $height/18 ] -relief sunken
	pack $frameParent.tasksContainer.table.entrys.deadLine -padx 2 -pady 2 -side left
	
	#Create the frames of results
	frame $frameParent.tasksResults  -bd 5 -width [expr $width/1.5 ] -height [expr $height/1.7 ] -relief sunken
	pack $frameParent.tasksResults -padx 20 -pady 15
	frame $frameParent.tasksResults.trace -bd 1 -width [expr $width/3 ] -height [expr $height/3 ] -relief sunken
	pack $frameParent.tasksResults.trace -padx 2 -pady 2 -side left
	frame $frameParent.tasksResults.statistics -bd 1 -width [expr $width/3 ] -height [expr $height/3 ] -relief sunken
	pack $frameParent.tasksResults.statistics -padx 2 -pady 2 -side right
}


##########################################################################
#	getTableTasksFrame
#	November 21, 2008
#	Returns the frame that contains the tasks table
#	Parameters: 
#		None
#	Returns:
#		frame - This will be returned a frame
#	Messages:
#		None
##########################################################################
proc getTableTasksFrame { } {
	set frame .realtss.tasksContainer.table.tableTasks
	return $frame
}

##########################################################################
#	getInformationButtonsFrame
#	November 21, 2008
#	Returns the frame that contains the information buttons
#	Parameters: 
#		None
#	Returns:
#		frame - This will be returned a frame
#	Messages:
#		None
##########################################################################
proc getToolsBarFrame { } {
	set frame .realtss.toolBar
	return $frame
}

##########################################################################
#	getEntryTasksFrame
#	November 21, 2008
#	Returns the frame that contains the section of the entrys to tasks
#	Parameters: 
#		None
#	Returns:
#		frame - This will be returned a frame
#	Messages:
#		None
##########################################################################
proc getEntryTasksFrame { } {
	set frame .realtss.tasksContainer.table.entrys
	return $frame
}

##########################################################################
#	getResultsBoxFrame
#	April 27, 2010
#	Returns the frame that contains the section of the results of tasks
#	Parameters: 
#		None
#	Returns:
#		frame - This will be returned a frame
#	Messages:
#		None
##########################################################################
proc getResultsBoxFrame { } {
	set frame .realtss.tasksResults
	return $frame
}

##########################################################################
#	getFrameParent
#	November 21, 2008
#	Returns the frame principal
#	Parameters: 
#		None
#	Returns:
#		frame - This will be returned a frame
#	Messages:
#		None
##########################################################################
proc getFrameParent { } {
	set frame .realtss
	return $frame
}

##########################################################################
#	testButtons
#	November 21, 2008
#	This procedure is only for test the items of menu
#	Parameters: 
#		None
#	Returns:
#		None
#	Messages:
#		None
##########################################################################
proc testButtons { item } {
	toplevel .prueba
	wm title .prueba test
	label .prueba.text -text "Here we will call the correspondent procedure of $item"
	pack .prueba.text -side top -fill both -expand 1
}

initializationProcedures