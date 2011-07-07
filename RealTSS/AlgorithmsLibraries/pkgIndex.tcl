##########################################################################
#	loadAlgorithms
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
proc loadAlgorithms { } {
	global APP_PATH
	global algLibraryNames
	global algLibraryCount
	set algLibraryCount 0
	set algLibraryNames(IDROW) 0 
	set algLibraryNames(IDCOL) 0
	set archName "$APP_PATH/Algorithms/Algorithms.conf" ;	 #The ubication of the .conf
	set arch [open $archName]
	set contentAlgConf [read $arch]
	close $arch
	## Split into records on newlines
	set records [split $contentAlgConf "\n"]
	
	## Iterate over the records
	set type 0
	foreach rec $records {
		switch $rec {
			"\[ALGORITHMS_NAMES\]" {
				set type 1
				continue
				
			}
		}
		
		switch $type {
			1 {
				set len [string length $rec]
        			if {$len >= 1} {
        				set idRow $algLibraryNames(IDROW)
        				set idCol $algLibraryNames(IDCOL)
        				## Split into fields on colons
        				set fields [split $rec "="]
        				## Assign fields to variables and print some out...
        				lassign $fields \
        					ALGORITHM PROCEDURENAME
							#ALGORITHM DESCRIPTION LIBNAME PROCEDURENAME
					
					#save algorithm name
        				set algLibraryNames($idRow,$idCol) $ALGORITHM
        				incr algLibraryNames(IDCOL)
        			
					#save description
						# set idCol $algLibraryNames(IDCOL)
        				# set algLibraryNames($idRow,$idCol) $DESCRIPTION
        				# incr algLibraryNames(IDCOL)
        			
					#save libname
						# set idCol $algLibraryNames(IDCOL)
						# set algLibraryNames($idRow,$idCol) $LIBNAME
						# incr algLibraryNames(IDCOL)
					
					#save procedure value
        				set idCol $algLibraryNames(IDCOL)
						set algLibraryNames($idRow,$idCol) $PROCEDURENAME
					#reset IDCOL
        				set algLibraryNames(IDCOL) 0	
						
					#increment row 
						incr algLibraryNames(IDROW)
						incr algLibraryCount
					
        			}
			}
		}
	}
}



##########################################################################
#	searchAlgLib
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
proc searchAlgLib { commandName } {
	global algLibraryNames ;
	set nComandos [expr [array size algLibraryNames]/2-3]
	for {set i 0} {$i<$nComandos} {incr i} {
		if { $algLibraryNames($i,2) == $commandName} {
			return $algLibraryNames($i,3)
		}
	}
	return "-"
}