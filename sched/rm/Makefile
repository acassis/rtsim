############################################################################################
# Configure paths to the folders necesary
############################################################################################
SCHED_DIR	=.
BASE_DIR	=../..
UTILS_DIR 	=$(BASE_DIR)/utils
INCLUDE_DIR 	=$(BASE_DIR)/include
LIB_DIR		=$(BASE_DIR)/RealTSS/AlgorithmsLibraries
OBJ_DIR 	=$(SCHED_DIR)/obj
############################################################################################
# Option of compilator for use of threads
CC_OPT 		=-lpthread
CC		=cc
# CFLAGS		=-Wl,-fPIC

#BUILD Lib or executable
BUILD_TCL_LIB	=-DUSE_TCL_STUBS -DSIMLUATOR_LIB_TCL -I$(INCLUDE_DIR) -I/usr/include/tcl8.5 -L/usr/lib -ltclstub8.5 -lm $(CC_OPT)
BUILD_EXECUTABLE=-I$(INCLUDE_DIR) -lm $(CC_OPT)

############################################################################################
# List of objects common for all methods
############################################################################################
OBJECTS		=$(UTILS_DIR)/task_lists.o $(UTILS_DIR)/sched_events.o $(UTILS_DIR)/processor_lists.o $(UTILS_DIR)/trace_event.o $(UTILS_DIR)/logger.o


# For add to compilation, files of new methods follows the next steps:
############################################################################################
# 1. Copy and configure paths for a new method 
############################################################################################
### Configuraci$(OBJECTS) -Wl, -fPICon para metodo 

#Folder where are the files
# dir_rmrboundmp	=$(SCHED_DIR)/rm_rbound_mp
# # C files that was compiled
# file1_rmrboundmp=$(dir_rmrboundmp)/rbound_mp.c
# file2_rmrboundmp=$(dir_rmrboundmp)/base_rm_global_sched.c
# #Name of the library that was generated 
# lib_rmrboundmp	=$(LIB_DIR)/librmrboundmp.so
# #name of the executable to be generated
# exe_rmrboundmp	=$(LIB_DIR)/librmrboundmp

### Configuration to method rm rbound
#Folder where are the files
dir_rmrboundmp	=$(SCHED_DIR)/rm_rbound_mp
# # C files that was compiled
file1_rmrboundmp=$(dir_rmrboundmp)/rbound_mp.c
file2_rmrboundmp=$(dir_rmrboundmp)/base_rm_global_sched.c
# #Name of the library that was generated 
lib_rmrboundmp	=$(LIB_DIR)/librmrboundmp.so
# #name of the executable to be generated
exe_rmrboundmp	=$(LIB_DIR)/librmrboundmp

### Configuration to method rm bf du uo
dir_rmbfduuo	=$(SCHED_DIR)/rm_bf_du_uo
file1_rmbfduuo	=$(dir_rmbfduuo)/rm_bf_du_uo.c
file2_rmbfduuo	=$(dir_rmbfduuo)/base_rm_global_sched.c
lib_rmbfduuo	=$(LIB_DIR)/librmbfduuo.so
exe_rmbfduuo	=$(LIB_DIR)/librmbfduuo

### Configuration to method rm rbound mp bf
dir_rmrboundmpbf	=$(SCHED_DIR)/rm_rbound_mp_bf
file1_rmrboundmpbf	=$(dir_rmrboundmpbf)/rbound_mp_bf.c
file2_rmrboundmpbf	=$(dir_rmrboundmpbf)/base_rm_global_sched.c
lib_rmrboundmpbf	=$(LIB_DIR)/librmrboundmpbf.so
exe_rmrboundmpbf	=$(LIB_DIR)/librmrboundmpbf


### Configuration to method rm rbound mp nfr
dir_rmrboundmpnfr	=$(SCHED_DIR)/rm_rbound_mp_nfr
file1_rmrboundmpnfr	=$(dir_rmrboundmpnfr)/rbound_mp_nfr.c
file2_rmrboundmpnfr	=$(dir_rmrboundmpnfr)/base_rm_global_sched.c
lib_rmrboundmpnfr	=$(LIB_DIR)/librmrboundmpnfr.so
exe_rmrboundmpnfr	=$(LIB_DIR)/librmrboundmpnfr


### Configuration to method rm bf ip
dir_rmbfip	=$(SCHED_DIR)/rm_bf_ip
file1_rmbfip	=$(dir_rmbfip)/rm_bf_ip.c
file2_rmbfip	=$(dir_rmbfip)/base_rm_global_sched.c
lib_rmbfip	=$(LIB_DIR)/librmbfip.so
exe_rmbfip	=$(LIB_DIR)/librmbfip

### Configuration to method rm bf llrm_global
dir_rmbfll	=$(SCHED_DIR)/rm_bf_ll
file1_rmbfll	=$(dir_rmbfll)/rm_bf_ll.c
file2_rmbfll	=$(dir_rmbfll)/base_rm_global_sched.c
lib_rmbfll	=$(LIB_DIR)/librmbfll.so
exe_rmbfll	=$(LIB_DIR)/librmbfll

### Configuration to method rm ff du uo
dir_rmffduuo	=$(SCHED_DIR)/rm_ff_du_uo
file1_rmffduuo	=$(dir_rmffduuo)/rm_ff_du_uo.c
file2_rmffduuo	=$(dir_rmffduuo)/base_rm_global_sched.c
lib_rmffduuo	=$(LIB_DIR)/librmffduuo.so
exe_rmffduuo	=$(LIB_DIR)/librmffduuo

### Configuration to method rm ff ip
dir_rmffip	=$(SCHED_DIR)/rm_ff_ip
file1_rmffip	=$(dir_rmffip)/rm_ff_ip.c
file2_rmffip	=$(dir_rmffip)/base_rm_global_sched.c
lib_rmffip	=$(LIB_DIR)/librmffip.so
exe_rmffip	=$(LIB_DIR)/librmffip

### Configuration to method rm ff ll
dir_rmffll	=$(SCHED_DIR)/rm_ff_ll
file1_rmffll	=$(dir_rmffll)/rm_ff_ll.c
file2_rmffll	=$(dir_rmffll)/base_rm_global_sched.c
lib_rmffll	=$(LIB_DIR)/librmffll.so
exe_rmffll	=$(LIB_DIR)/librmffll

### Configuration to method rm wf ll
dir_rmwfll	=$(SCHED_DIR)/rm_wf_ll
file1_rmwfll	=$(dir_rmwfll)/rm_wf_ll.c
file2_rmwfll	=$(dir_rmwfll)/base_rm_global_sched.c
lib_rmwfll	=$(LIB_DIR)/librmwfll.so
exe_rmwfll	=$(LIB_DIR)/librmwfll

### Configuration to method rm st
dir_rmst	=$(SCHED_DIR)/rm_st
file1_rmst	=$(dir_rmst)/rm_st.cCFLAGS
file2_rmst	=$(dir_rmst)/base_rm_global_sched.c
lib_rmst	=$(LIB_DIR)/librmst.so
exe_rmst	=$(LIB_DIR)/librmst

### Configuration to method rm nf ip
dir_rmnfip	=$(SCHED_DIR)/rm_nf_ip
file1_rmnfip	=$(dir_rmnfip)/rm_nf_ip.c
file2_rmnfip	=$(dir_rmnfip)/base_rm_global_sched.c
lib_rmnfip	=$(LIB_DIR)/librmnfip.so
exe_rmnfip	=$(LIB_DIR)/librmnfip

## Configuration to method rm gt
dir_rmgt	=$(SCHED_DIR)/rm_gt
file1_rmgt	=$(dir_rmgt)/rm_gt.c
file2_rmgt	=$(dir_rmgt)/base_rm_global_sched.c
lib_rmgt	=$(LIB_DIR)/librmgt.so
exe_rmgt	=$(LIB_DIR)/librmgt

### Configuration to method rm nf ll
dir_rmnfll	=$(SCHED_DIR)/rm_nf_ll
file1_rmnfll	=$(dir_rmnfll)/rm_nf_ll.c
file2_rmnfll	=$(dir_rmnfll)/base_rm_global_sched.c
lib_rmnfll	=$(LIB_DIR)/librmnfll.so
exe_rmnfll	=$(LIB_DIR)/librmnfll

### Configuration to method rm exact audsley
dir_rmexactAudsley	=$(SCHED_DIR)/rm_exactAudsley
file1_rmexactAudsley	=$(dir_rmexactAudsley)/rm_exactAudsley.c
file2_rmexactAudsley	=$(dir_rmexactAudsley)/base_rm_global_sched.c
lib_rmexactAudsley	=$(LIB_DIR)/librmeaudsley.so
exe_rmeaudsley	=$(LIB_DIR)/librmeaudsley

### Configuration to method rm exact lehoczky
dir_rmexactLehoczky	=$(SCHED_DIR)/rm_exactLehoczky
file1_rmexactLehoczky	=$(dir_rmexactLehoczky)/rm_exactLehoczky.c
file2_rmexactLehoczky	=$(dir_rmexactLehoczky)/base_rm_global_sched.c
lib_rmexactLehoczky	=$(LIB_DIR)/librmexactLehoczky.so
exe_rmexactLehoczky	=$(LIB_DIR)/librmexactLehoczky


############################################################################################
all: $(OBJECTS) $(rm_rbound_mp) $(rm_bf_du_uo)


############################################################################################
# 2. Copy this function and replace by the files of the new function 
############################################################################################
### Create library for rm rbound
# rm_rbound_mp: $(OBJECTS)
	# @echo ==================================================================
	# @echo Compiling...
	# @echo ==================================================================
	# cc $(file1_rmrboundmp) $(file2_rmrboundmp) $(OBJECTS) -shared -o $(lib_rmrboundmp) -DUSE_TCL_STUBS -DSIMLUATOR_LIB_TCL -I$(INCLUDE_DIR) -I/usr/include/tcl8.5 -L/usr/lib -ltclstub8.5 -lm $(CC_OPT)
	# @echo ==================================================================
	# @echo Finish.
	# @echo ==================================================================
############################################################################################

# objectos: @echo ----- 
# 	cc $(UTILS_DIR)/task_lists.c -o $(UTILS_DIR)/task_lists.o 
# 	cc $(UTILS_DIR)/sched_events.c -o $(UTILS_DIR)/sched_events.o -Wl, -fPIC
# 	cc $(UTILS_DIR)/processor_lists.c -o $(UTILS_DIR)/processor_lists.o -Wl, -fPIC
# 	cc $(UTILS_DIR)/trace_event.c -o $(UTILS_DIR)/trace_event.o -Wl, -fPIC
# 	cc $(UTILS_DIR)/logger.c -o $(UTILS_DIR)/logger.o -Wl, -fPIC

### Create library and executable for rm rbound
rm_rbound_mp:  $(OBJECTS)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	cc $(file1_rmrboundmp) $(file2_rmrboundmp) -shared -o $(lib_rmrboundmp) $(BUILD_TCL_LIB)
	
	@echo ------------------------------------------------------------------
	@echo Building executable...
	cc $(file1_edfbf) $(file2_edfbf) $(objects) -o $(exe_edfbf) $(BUILD_EXECUTABLE)
	
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================

### Create library and executable for rm bf du uo
rm_bf_du_uo: $(OBJECTS)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	cc $(file1_rmbfduuo) $(file2_rmbfduuo) $(OBJECTS) -shared -o $(lib_rmbfduuo) $(BUILD_TCL_LIB)
	
	@echo ------------------------------------------------------------------
	@echo Building executable...
	cc $(file1_edfbf) $(file2_edfbf) $(objects) -o $(exe_edfbf) $(BUILD_EXECUTABLE)
	
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================

### Create library and executable for rm rbound mp bf
rm_rbound_mp_bf: $(OBJECTS)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	cc $(file1_rmrboundmpbf) $(file2_rmrboundmpbf) $(OBJECTS) -shared -o $(lib_rmrboundmpbf) $(BUILD_TCL_LIB)
	
	@echo ------------------------------------------------------------------
	@echo Building executable...
	cc $(file1_edfbf) $(file2_edfbf) $(objects) -o $(exe_edfbf) $(BUILD_EXECUTABLE)
	
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================

### Create library and executable for rm rbound mp nfr
rm_rbound_mp_nfr: $(OBJECTS)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	cc $(file1_rmrboundmpnfr) $(file2_rmrboundmpnfr) $(OBJECTS) -shared -o $(lib_rmrboundmpnfr) $(BUILD_TCL_LIB)
	
	@echo ------------------------------------------------------------------
	@echo Building executable...
	cc $(file1_edfbf) $(file2_edfbf) $(objects) -o $(exe_edfbf) $(BUILD_EXECUTABLE)
	
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================

## Create library and executable for rm bf ip
rm_bf_ip: $(OBJECTS)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	cc $(file1_rmbfip) $(file2_rmbfip) $(OBJECTS) -shared -o $(lib_rmbfip) $(BUILD_TCL_LIB)
	
	@echo ------------------------------------------------------------------
	@echo Building executable...
	cc $(file1_edfbf) $(file2_edfbf) $(objects) -o $(exe_edfbf) $(BUILD_EXECUTABLE)
	
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================

## Create library and executable for rm bf ll
rm_bf_ll: $(OBJECTS)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	cc $(file1_rmbfll) $(file2_rmbfll) $(OBJECTS) -shared -o $(lib_rmbfll) $(BUILD_TCL_LIB)
	
	@echo ------------------------------------------------------------------
	@echo Building executable...
	cc $(file1_edfbf) $(file2_edfbf) $(objects) -o $(exe_edfbf) $(BUILD_EXECUTABLE)
	
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================


## Create library and executable for rm ff du uo
rm_ff_du_uo: $(OBJECTS)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	cc $(file1_rmffduuo) $(file2_rmffduuo) $(OBJECTS) -shared -o $(lib_rmffduuo) $(BUILD_TCL_LIB)
	
	@echo ------------------------------------------------------------------
	@echo Building executable...
	cc $(file1_edfbf) $(file2_edfbf) $(objects) -o $(exe_edfbf) $(BUILD_EXECUTABLE)
	
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================

## Create library and executable for rm ff ip
rm_ff_ip: $(OBJECTS)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	cc $(file1_rmffip) $(file2_rmffip) $(OBJECTS) -shared -o $(lib_rmffip) $(BUILD_TCL_LIB)
	
	@echo ------------------------------------------------------------------
	@echo Building executable...
	cc $(file1_edfbf) $(file2_edfbf) $(objects) -o $(exe_edfbf) $(BUILD_EXECUTABLE)
	
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================

## Create library and executable for rm ff llrm_global
rm_ff_ll: $(OBJECTS)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	cc $(file1_rmffll) $(file2_rmffll) $(OBJECTS) -shared -o $(lib_rmffll) $(BUILD_TCL_LIB)
	
	@echo ------------------------------------------------------------------
	@echo Building executable...
	cc $(file1_edfbf) $(file2_edfbf) $(objects) -o $(exe_edfbf) $(BUILD_EXECUTABLE)
	
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================

## Create library and executable for rm wf ll
rm_wf_ll: $(OBJECTS)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	cc $(file1_rmwfll) $(file2_rmwfll) $(OBJECTS) -shared -o $(lib_rmwfll) $(BUILD_TCL_LIB)
	
	@echo ------------------------------------------------------------------
	@echo Building executable...
	cc $(file1_edfbf) $(file2_edfbf) $(objects) -o $(exe_edfbf) $(BUILD_EXECUTABLE)
	
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================

## Create library and executable for rm strm_global
rm_st: $(OBJECTS)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	gcOBJECTSc $(file1_rmst) $(file2_rmst) $(OBJECTS) -shared -o $(lib_rmst) $(BUILD_TCL_LIB)
	
	@echo ------------------------------------------------------------------
	@echo Building executable...
	cc $(file1_edfbf) $(file2_edfbf) $(objects) -o $(exe_edfbf) $(BUILD_EXECUTABLE)
	
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================

## Create library and executable for rm nf ip
rm_nf_ip: $(OBJECTS)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	cc $(file1_rmnfip) $(file2_rmnfip) $(OBJECTS) -shared -o $(lib_rmnfip) $(BUILD_TCL_LIB)
	
	@echo ------------------------------------------------------------------
	@echo Building executable...
	cc $(file1_edfbf) $(file2_edfbf) $(objects) -o $(exe_edfbf) $(BUILD_EXECUTABLE)
	
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================

## Create library and executable for rm gt
rm_gt: $(OBJECTS)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	cc $(file1_rmgt) $(file2_rmgt) $(OBJECTS) -shared -o $(lib_rmgt) $(BUILD_TCL_LIB)
	
	@echo ------------------------------------------------------------------
	@echo Building executable...
	cc $(file1_edfbf) $(file2_edfbf) $(objects) -o $(exe_edfbf) $(BUILD_EXECUTABLE)
	
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================

## Create library and executable for rm nf ll
rm_nf_ll: $(OBJECTS)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	cc $(file1_rmnfll) $(file2_rmnfll) $(OBJECTS) -shared -o $(lib_rmnfll) $(BUILD_TCL_LIB)
	
	@echo ------------------------------------------------------------------
	@echo Building executable...
	cc $(file1_edfbf) $(file2_edfbf) $(objects) -o $(exe_edfbf) $(BUILD_EXECUTABLE)
	
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================

## Create library and executable for rm exact audsley
rm_exactAudsley: $(OBJECTS)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	cc $(file1_rmexactAudsley) $(file2_rmexactAudsley) $(OBJECTS) -shared -o $(lib_rmexactAudsley) $(BUILD_TCL_LIB)
	
	@echo ------------------------------------------------------------------
	@echo Building executable...
	cc $(file1_edfbf) $(file2_edfbf) $(objects) -o $(exe_edfbf) $(BUILD_EXECUTABLE)
	
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================

## Create library and executable for rm exact lehoczky
rm_exactLehoczky: $(OBJECTS)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	cc $(file1_rmexactLehoczky) $(file2_rmexactLehoczky) $(OBJECTS) -shared -o $(lib_rmexactLehoczky) $(BUILD_TCL_LIB)
	
	@echo ------------------------------------------------------------------
	@echo Building executable...
	cc $(file1_edfbf) $(file2_edfbf) $(objects) -o $(exe_edfbf) $(BUILD_EXECUTABLE)
	
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================


### Cleaned
clean:
	-rm $(OBJECTS)

end:
# installer : $(app)
	# mkdir $(APP_NAME)
	# mkdir ./$(APP_NAME)/examples
	# cp $(APP_NAME).run ./$(APP_NAME)
	# cp $(DATA_DIR)/* ./$(APP_NAME)/examples
	# makeself --notemp ./$(APP_NAME)/ $(APP_NAME)_installer.run "Simulator" echo "Done"
	# rm -rf $(APP_NAME)/