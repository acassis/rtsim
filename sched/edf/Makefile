############################################################################################
# Configure paths to the folders necesary
############################################################################################
SCHED_DIR	=.
BASE_DIR	=../..
UTILS_DIR 	=$(BASE_DIR)/utils
INCLUDE_DIR =$(BASE_DIR)/include
LIB_DIR		=$(BASE_DIR)/RealTSS/AlgorithmsLibraries
OBJ_DIR 	=$(SCHED_DIR)/obj
############################################################################################
# Option of compilator for use of threads
CC_OPT 		= -lpthread

#BUILD Lib or executable
BUILD_TCL_LIB	=-DUSE_TCL_STUBS -DSIMLUATOR_LIB_TCL -I$(INCLUDE_DIR) -I/usr/include/tcl8.5 -L/usr/lib -ltclstub8.5 -lm $(CC_OPT)
BUILD_EXECUTABLE=-I$(INCLUDE_DIR) -lm $(CC_OPT)

############################################################################################
# List of objects common for all methods
############################################################################################
objects = $(UTILS_DIR)/task_lists.o\
	$(UTILS_DIR)/sched_events.o\
	$(UTILS_DIR)/processor_lists.o\
	$(UTILS_DIR)/trace_event.o\
	$(UTILS_DIR)/logger.o

	
# For add to compilation, files of new methods follows the next steps:
############################################################################################
# 1. Copy and configure paths for a new method 
############################################################################################
###Configuration for method
#Folder where are the files
# dir_edfbf	=$(SCHED_DIR)/edf_bf
# # C files that was compiled
# file1_edfbf	=$(dir_edfbf)/edf_bf.c
# file2_edfbf	=$(dir_edfbf)/base_edf_sched.c
# #Name of the library to be generated 
# lib_edfbf	=$(LIB_DIR)/libedfbf.so
# #name of the executable to be generated
# exe_edfbf	=edfbf

### Configuration to method edf bf
#Folder where are the files
dir_edfbf	=$(SCHED_DIR)/edf_bf
# # C files that was compiled
file1_edfbf	=$(dir_edfbf)/edf_bf.c
file2_edfbf	=$(dir_edfbf)/base_edf_sched.c
# #Name of the library to be generated 
lib_edfbf	=$(LIB_DIR)/libedfbf.so
# #name of the executable to be generated
exe_edfbf	=$(LIB_DIR)/libedfbf

### Configuration to method edf ff
#Folder where are the files
dir_edfff	=$(SCHED_DIR)/edf_ff
# # C files that was compiled
file1_edfff	=$(dir_edfff)/edf_ff.c
file2_edfff	=$(dir_edfff)/base_edf_sched.c
# #Name of the library to be generated 
lib_edfff	=$(LIB_DIR)/libedfff.so
# #name of the executable to be generated
exe_edfff	=$(LIB_DIR)/libedfff

### Configuration to method edf nf
#Folder where are the files
dir_edfnf	=$(SCHED_DIR)/edf_nf
# # C files that was compiled
file1_edfnf	=$(dir_edfnf)/edf_nf.c
file2_edfnf	=$(dir_edfnf)/base_edf_sched.c
# #Name of the library to be generated 
lib_edfnf	=$(LIB_DIR)/libedfnf.so
# #name of the executable to be generated
exe_edfnf	=$(LIB_DIR)/libedfnf

### Configuration to method edf wf
#Folder where are the files
dir_edfwf	=$(SCHED_DIR)/edf_wf
# # C files that was compiled
file1_edfwf	=$(dir_edfwf)/edf_wf.c
file2_edfwf	=$(dir_edfwf)/base_edf_sched.c
# #Name of the library to be generated 
lib_edfwf	=$(LIB_DIR)/libedfwf.so
# #name of the executable to be generated
exe_edfwf	=$(LIB_DIR)/libedfwf

### Configuration to method edf global
#Folder where are the files
dir_edfglobal	=$(SCHED_DIR)/global
# # C files that was compiled
file2_edfglobal	=$(dir_edfglobal)/base_edf_sched.c
# #Name of the library to be generated 
lib_edfglobal	=$(LIB_DIR)/libedfglobal.so
# #name of the executable to be generated
exe_edfglobal	=$(LIB_DIR)/libedfglobal

############################################################################################
#all: $(objects) $(rm_rbound_mp) $(rm_bf_du_uo)

############################################################################################
# 2. Copy this function and replace by the files of the new function 
############################################################################################
### Create library for edf bf
# edf_bf: $(objects)
	# @echo ==================================================================
	# @echo Compiling...
	# @echo ==================================================================
	# gcc $(file1_edfbf) $(file2_edfbf) $(objects) -shared -o $(lib_edfbf) $(BUILD_TCL_LIB)
	# @echo ==================================================================
	# @echo Finish.
	# @echo ==================================================================
############################################################################################
### Create library for edf global
edf_global: $(objects)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	cc $(file2_edfglobal) $(objects) -shared -o $(lib_edfglobal) $(BUILD_TCL_LIB)

	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================
	
### Create library for edf bf
edf_bf: $(objects)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	@echo Building lib...
	cc $(file1_edfbf) $(file2_edfbf) $(objects) -shared -o $(lib_edfbf) $(BUILD_TCL_LIB)
	
	@echo ------------------------------------------------------------------
	@echo Building executable...
	cc $(file1_edfbf) $(file2_edfbf) $(objects) -o $(exe_edfbf) $(BUILD_EXECUTABLE)
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================

### Create library for edf ff
edf_ff: $(objects)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	@echo Building lib...
	cc $(file1_edfff) $(file2_edfff) $(objects) -shared -o $(lib_edfff) $(BUILD_TCL_LIB)

	@echo ------------------------------------------------------------------
	@echo Building executable...
	cc $(file1_edfff) $(file2_edfff) $(objects) -o $(exe_edfff) $(BUILD_EXECUTABLE)
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================

### Create library for edf ff
edf_nf: $(objects)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	@echo Building lib...
	cc $(file1_edfnf) $(file2_edfnf) $(objects) -shared -o $(lib_edfnf) $(BUILD_TCL_LIB)

	@echo ------------------------------------------------------------------
	@echo Building executable...
	cc $(file1_edfnf) $(file2_edfnf) $(objects) -o $(exe_edfnf) $(BUILD_EXECUTABLE)
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================
	
### Create library for edf wf
edf_wf: $(objects)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	@echo Building lib...
	cc $(file1_edfwf) $(file2_edfwf) $(objects) -shared -o $(lib_edfwf) $(BUILD_TCL_LIB)

	@echo ------------------------------------------------------------------
	@echo Building executable...
	cc $(file1_edfwf) $(file2_edfwf) $(objects) -o $(exe_edfwf) $(BUILD_EXECUTABLE)
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================
	
### Cleaned
clean:
	-rm $(objects)

end:
# installer : $(app)
	# mkdir $(APP_NAME)
	# mkdir ./$(APP_NAME)/examples
	# cp $(APP_NAME).run ./$(APP_NAME)
	# cp $(DATA_DIR)/* ./$(APP_NAME)/examples
	# makeself --notemp ./$(APP_NAME)/ $(APP_NAME)_installer.run "Simulator" echo "Done"
	# rm -rf $(APP_NAME)/