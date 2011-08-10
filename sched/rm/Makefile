############################################################################################
# configurar rutas a las carpetas necesarias
############################################################################################
SCHED_DIR	=.
BASE_DIR	=../..
UTILS_DIR 	=$(BASE_DIR)/utils
INCLUDE_DIR 	=$(BASE_DIR)/include
LIB_DIR		=$(BASE_DIR)/RealTSS/AlgorithmsLibraries
OBJ_DIR 	=$(SCHED_DIR)/obj
############################################################################################
# opcion de compilador para el uso de threads
CC_OPT 		= -lpthread


############################################################################################
# Lista de objectos comunes para todos los metodos
############################################################################################
objects = $(UTILS_DIR)/task_lists.o\
	$(UTILS_DIR)/sched_events.o\
	$(UTILS_DIR)/processor_lists.o\
	$(UTILS_DIR)/trace_event.o\
	$(UTILS_DIR)/logger.o

	
############################################################################################
# 1. Copiar y configurar las rutas para un nuevo metodo
############################################################################################
### Configuracion para metodo 
#carpeta donde estan los archivos
# dir_rmrboundmp	=$(SCHED_DIR)/rm_rbound_mp
# #archivos C que se compilaran
# file1_rmrboundmp=$(dir_rmrboundmp)/rbound_mp.c
# file2_rmrboundmp=$(dir_rmrboundmp)/base_rm_global_sched.c
# #nombre de la libreria que se generara
# lib_rmrboundmp	=$(LIB_DIR)/librmrboundmp.so


### Configuracion para metodo rm rbound
#carpeta donde estan los archivos
dir_rmrboundmp	=$(SCHED_DIR)/rm_rbound_mp
#archivos C que se compilaran
file1_rmrboundmp=$(dir_rmrboundmp)/rbound_mp.c
file2_rmrboundmp=$(dir_rmrboundmp)/base_rm_global_sched.c
#nombre de la libreria que se generara
lib_rmrboundmp	=$(LIB_DIR)/librmrboundmp.so

### Configuracion para metodo rm bf du uo
dir_rmbfduuo	=$(SCHED_DIR)/rm_bf_du_uo
file1_rmbfduuo	=$(dir_rmbfduuo)/rm_bf_du_uo.c
file2_rmbfduuo	=$(dir_rmbfduuo)/base_rm_global_sched.c
lib_rmbfduuo	=$(LIB_DIR)/librmbfduuo.so

### Configuracion para metodo rm rbound mp bf
dir_rmrboundmpbf	=$(SCHED_DIR)/rm_rbound_mp_bf
file1_rmrboundmpbf	=$(dir_rmrboundmpbf)/rbound_mp_bf.c
file2_rmrboundmpbf	=$(dir_rmrboundmpbf)/base_rm_global_sched.c
lib_rmrboundmpbf	=$(LIB_DIR)/librmrboundmpbf.so


### Configuracion para metodo rm rbound mp nfr
dir_rmrboundmpnfr	=$(SCHED_DIR)/rm_rbound_mp_nfr
file1_rmrboundmpnfr	=$(dir_rmrboundmpnfr)/rbound_mp_nfr.c
file2_rmrboundmpnfr	=$(dir_rmrboundmpnfr)/base_rm_global_sched.c
lib_rmrboundmpnfr	=$(LIB_DIR)/librmrboundmpnfr.so


### Configuracion para metodo rm bf ip
dir_rmbfip	=$(SCHED_DIR)/rm_bf_ip
file1_rmbfip	=$(dir_rmbfip)/rm_bf_ip.c
file2_rmbfip	=$(dir_rmbfip)/base_rm_global_sched.c
lib_rmbfip	=$(LIB_DIR)/librmbfip.so


### Configuracion para metodo rm bf ll
dir_rmbfll	=$(SCHED_DIR)/rm_bf_ll
file1_rmbfll	=$(dir_rmbfll)/rm_bf_ll.c
file2_rmbfll	=$(dir_rmbfll)/base_rm_global_sched.c
lib_rmbfll	=$(LIB_DIR)/librmbfll.so

### Configuracion para metodo rm ff du uo
dir_rmffduuo	=$(SCHED_DIR)/rm_ff_du_uo
file1_rmffduuo	=$(dir_rmffduuo)/rm_ff_du_uo.c
file2_rmffduuo	=$(dir_rmffduuo)/base_rm_global_sched.c
lib_rmffduuo	=$(LIB_DIR)/librmffduuo.so

### Configuracion para metodo rm ff ip
dir_rmffip	=$(SCHED_DIR)/rm_ff_ip
file1_rmffip	=$(dir_rmffip)/rm_ff_ip.c
file2_rmffip	=$(dir_rmffip)/base_rm_global_sched.c
lib_rmffip	=$(LIB_DIR)/librmffip.so

### Configuracion para metodo rm ff ll
dir_rmffll	=$(SCHED_DIR)/rm_ff_ll
file1_rmffll	=$(dir_rmffll)/rm_ff_ll.c
file2_rmffll	=$(dir_rmffll)/base_rm_global_sched.c
lib_rmffll	=$(LIB_DIR)/librmffll.so

### Configuracion para metodo rm wf ll
dir_rmwfll	=$(SCHED_DIR)/rm_wf_ll
file1_rmwfll	=$(dir_rmwfll)/rm_wf_ll.c
file2_rmwfll	=$(dir_rmwfll)/base_rm_global_sched.c
lib_rmwfll	=$(LIB_DIR)/librmwfll.so

### Configuracion para metodo rm st
dir_rmst	=$(SCHED_DIR)/rm_st
file1_rmst	=$(dir_rmst)/rm_st.c
file2_rmst	=$(dir_rmst)/base_rm_global_sched.c
lib_rmst	=$(LIB_DIR)/librmst.so

### Configuracion para metodo rm nf ip
dir_rmnfip	=$(SCHED_DIR)/rm_nf_ip
file1_rmnfip	=$(dir_rmnfip)/rm_nf_ip.c
file2_rmnfip	=$(dir_rmnfip)/base_rm_global_sched.c
lib_rmnfip	=$(LIB_DIR)/librmnfip.so

## Configuracion para metodo rm gt
dir_rmgt	=$(SCHED_DIR)/rm_gt
file1_rmgt	=$(dir_rmgt)/rm_gt.c
file2_rmgt	=$(dir_rmgt)/base_rm_global_sched.c
lib_rmgt	=$(LIB_DIR)/librmgt.so

### Configuracion para metodo rm nf ll
dir_rmnfll	=$(SCHED_DIR)/rm_nf_ll
file1_rmnfll	=$(dir_rmnfll)/rm_nf_ll.c
file2_rmnfll	=$(dir_rmnfll)/base_rm_global_sched.c
lib_rmnfll	=$(LIB_DIR)/librmnfll.so

### Configuracion para metodo rm exact audsley
dir_rmexactAudsley	=$(SCHED_DIR)/rm_exactAudsley
file1_rmexactAudsley	=$(dir_rmexactAudsley)/rm_exactAudsley.c
file2_rmexactAudsley	=$(dir_rmexactAudsley)/base_rm_global_sched.c
lib_rmexactAudsley	=$(LIB_DIR)/librmeaudsley.so

### Configuracion para metodo rm exact lehoczky
dir_rmexactLehoczky	=$(SCHED_DIR)/rm_exactLehoczky
file1_rmexactLehoczky	=$(dir_rmexactLehoczky)/rm_exactLehoczky.c
file2_rmexactLehoczky	=$(dir_rmexactLehoczky)/base_rm_global_sched.c
lib_rmexactLehoczky	=$(LIB_DIR)/librmexactLehoczky.so


############################################################################################
all: $(objects) $(rm_rbound_mp) $(rm_bf_du_uo)


############################################################################################
# 2. Copiar esta funcion y remplazar por los archivos de la nueva funcion
############################################################################################
### Crear libreria para rm rbound
# rm_rbound_mp: $(objects)
	# @echo ==================================================================
	# @echo Compiling...
	# @echo ==================================================================
	# gcc $(file1_rmrboundmp) $(file2_rmrboundmp) $(objects) -shared -o $(lib_rmrboundmp) -DUSE_TCL_STUBS -DSIMLUATOR_LIB_TCL -I$(INCLUDE_DIR) -I/usr/include/tcl8.5 -L/usr/lib -ltclstub8.5 -lm $(CC_OPT)
	# @echo ==================================================================
	# @echo Finish.
	# @echo ==================================================================
############################################################################################

### Crear libreria para rm rbound
rm_rbound_mp: $(objects)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	gcc $(file1_rmrboundmp) $(file2_rmrboundmp) $(objects) -shared -o $(lib_rmrboundmp) -DUSE_TCL_STUBS -DSIMLUATOR_LIB_TCL -I$(INCLUDE_DIR) -I/usr/include/tcl8.5 -L/usr/lib -ltclstub8.5 -lm $(CC_OPT)
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================

### Crear libreria para rm bf du uo
rm_bf_du_uo: $(objects)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================

	gcc $(file1_rmbfduuo) $(file2_rmbfduuo) $(objects) -shared -o $(lib_rmbfduuo) -DUSE_TCL_STUBS -DSIMLUATOR_LIB_TCL -I$(INCLUDE_DIR) -I/usr/include/tcl8.5 -L/usr/lib -ltclstub8.5 -lm $(CC_OPT)
	
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================

### Crear libreria para rm rbound mp bf
rm_rbound_mp_bf: $(objects)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	gcc $(file1_rmrboundmpbf) $(file2_rmrboundmpbf) $(objects) -shared -o $(lib_rmrboundmpbf) -DUSE_TCL_STUBS -DSIMLUATOR_LIB_TCL -I$(INCLUDE_DIR) -I/usr/include/tcl8.5 -L/usr/lib -ltclstub8.5 -lm $(CC_OPT)
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================

### Crear libreria para rm rbound mp nfr
rm_rbound_mp_nfr: $(objects)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	gcc $(file1_rmrboundmpnfr) $(file2_rmrboundmpnfr) $(objects) -shared -o $(lib_rmrboundmpnfr) -DUSE_TCL_STUBS -DSIMLUATOR_LIB_TCL -I$(INCLUDE_DIR) -I/usr/include/tcl8.5 -L/usr/lib -ltclstub8.5 -lm $(CC_OPT)
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================

## Crear libreria para rm bf ip
rm_bf_ip: $(objects)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	gcc $(file1_rmbfip) $(file2_rmbfip) $(objects) -shared -o $(lib_rmbfip) -DUSE_TCL_STUBS -DSIMLUATOR_LIB_TCL -I$(INCLUDE_DIR) -I/usr/include/tcl8.5 -L/usr/lib -ltclstub8.5 -lm $(CC_OPT)
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================

## Crear libreria para rm bf ll
rm_bf_ll: $(objects)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	gcc $(file1_rmbfll) $(file2_rmbfll) $(objects) -shared -o $(lib_rmbfll) -DUSE_TCL_STUBS -DSIMLUATOR_LIB_TCL -I$(INCLUDE_DIR) -I/usr/include/tcl8.5 -L/usr/lib -ltclstub8.5 -lm $(CC_OPT)
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================


## Crear libreria para rm ff du uo
rm_ff_du_uo: $(objects)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	gcc $(file1_rmffduuo) $(file2_rmffduuo) $(objects) -shared -o $(lib_rmffduuo) -DUSE_TCL_STUBS -DSIMLUATOR_LIB_TCL -I$(INCLUDE_DIR) -I/usr/include/tcl8.5 -L/usr/lib -ltclstub8.5 -lm $(CC_OPT)
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================

## Crear libreria para rm ff ip
rm_ff_ip: $(objects)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	gcc $(file1_rmffip) $(file2_rmffip) $(objects) -shared -o $(lib_rmffip) -DUSE_TCL_STUBS -DSIMLUATOR_LIB_TCL -I$(INCLUDE_DIR) -I/usr/include/tcl8.5 -L/usr/lib -ltclstub8.5 -lm $(CC_OPT)
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================

## Crear libreria para rm ff ll
rm_ff_ll: $(objects)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	gcc $(file1_rmffll) $(file2_rmffll) $(objects) -shared -o $(lib_rmffll) -DUSE_TCL_STUBS -DSIMLUATOR_LIB_TCL -I$(INCLUDE_DIR) -I/usr/include/tcl8.5 -L/usr/lib -ltclstub8.5 -lm $(CC_OPT)
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================


## Crear libreria para rm wf ll
rm_wf_ll: $(objects)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	gcc $(file1_rmwfll) $(file2_rmwfll) $(objects) -shared -o $(lib_rmwfll) -DUSE_TCL_STUBS -DSIMLUATOR_LIB_TCL -I$(INCLUDE_DIR) -I/usr/include/tcl8.5 -L/usr/lib -ltclstub8.5 -lm $(CC_OPT)
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================

## Crear libreria para rm st
rm_st: $(objects)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	gcc $(file1_rmst) $(file2_rmst) $(objects) -shared -o $(lib_rmst) -DUSE_TCL_STUBS -DSIMLUATOR_LIB_TCL -I$(INCLUDE_DIR) -I/usr/include/tcl8.5 -L/usr/lib -ltclstub8.5 -lm $(CC_OPT)
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================

## Crear libreria para rm nf ip
rm_nf_ip: $(objects)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	gcc $(file1_rmnfip) $(file2_rmnfip) $(objects) -shared -o $(lib_rmnfip) -DUSE_TCL_STUBS -DSIMLUATOR_LIB_TCL -I$(INCLUDE_DIR) -I/usr/include/tcl8.5 -L/usr/lib -ltclstub8.5 -lm $(CC_OPT)
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================

## Crear libreria para rm gt
rm_gt: $(objects)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	gcc $(file1_rmgt) $(file2_rmgt) $(objects) -shared -o $(lib_rmgt) -DUSE_TCL_STUBS -DSIMLUATOR_LIB_TCL -I$(INCLUDE_DIR) -I/usr/include/tcl8.5 -L/usr/lib -ltclstub8.5 -lm $(CC_OPT)
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================

## Crear libreria para rm nf ll
rm_nf_ll: $(objects)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	gcc $(file1_rmnfll) $(file2_rmnfll) $(objects) -shared -o $(lib_rmnfll) -DUSE_TCL_STUBS -DSIMLUATOR_LIB_TCL -I$(INCLUDE_DIR) -I/usr/include/tcl8.5 -L/usr/lib -ltclstub8.5 -lm $(CC_OPT)
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================

## Crear libreria para rm exact audsley
rm_exactAudsley: $(objects)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	gcc $(file1_rmexactAudsley) $(file2_rmexactAudsley) $(objects) -shared -o $(lib_rmexactAudsley) -DUSE_TCL_STUBS -DSIMLUATOR_LIB_TCL -I$(INCLUDE_DIR) -I/usr/include/tcl8.5 -L/usr/lib -ltclstub8.5 -lm $(CC_OPT)
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================

## Crear libreria para rm exact lehoczky
rm_exactLehoczky: $(objects)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	gcc $(file1_rmexactLehoczky) $(file2_rmexactLehoczky) $(objects) -shared -o $(lib_rmexactLehoczky) -DUSE_TCL_STUBS -DSIMLUATOR_LIB_TCL -I$(INCLUDE_DIR) -I/usr/include/tcl8.5 -L/usr/lib -ltclstub8.5 -lm $(CC_OPT)
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================


### Limpiar
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
