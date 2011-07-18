############################################################################################
# configurar rutas a las carpetas necesarias
############################################################################################
SCHED_DIR	=.
BASE_DIR	=../..
UTILS_DIR 	=$(BASE_DIR)/utils
INCLUDE_DIR =$(BASE_DIR)/include
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
# #carpeta donde estan los archivos
# dir_edfbf	=$(SCHED_DIR)/edf_bf
# #archivos C que se compilaran
# file1_edfbf	=$(dir_edfbf)/edf_bf.c
# file2_edfbf	=$(dir_edfbf)/config_edf_sched.c
# #nombre de la libreria que se generara
# lib_edfbf	=$(LIB_DIR)/libedfbf.so


### Configuracion para metodo edf bf
#carpeta donde estan los archivos
dir_edfbf	=$(SCHED_DIR)/edf_bf
#archivos C que se compilaran
file1_edfbf	=$(dir_edfbf)/edf_bf.c
file2_edfbf	=$(dir_edfbf)/config_edf_sched.c
#nombre de la libreria que se generara
lib_edfbf	=$(LIB_DIR)/libedfbf.so

### Configuracion para metodo edf ff
#carpeta donde estan los archivos
dir_edfff	=$(SCHED_DIR)/edf_ff
#archivos C que se compilaran
file1_edfff	=$(dir_edfff)/edf_ff.c
file2_edfff	=$(dir_edfff)/config_edf_sched.c
#nombre de la libreria que se generara
lib_edfff	=$(LIB_DIR)/libedfff.so

### Configuracion para metodo edf nf
#carpeta donde estan los archivos
dir_edfnf	=$(SCHED_DIR)/edf_nf
#archivos C que se compilaran
file1_edfnf	=$(dir_edfnf)/edf_nf.c
file2_edfnf	=$(dir_edfnf)/config_edf_sched.c
#nombre de la libreria que se generara
lib_edfnf	=$(LIB_DIR)/libedfnf.so

### Configuracion para metodo edf wf
#carpeta donde estan los archivos
dir_edfwf	=$(SCHED_DIR)/edf_wf
#archivos C que se compilaran
file1_edfwf	=$(dir_edfwf)/edf_wf.c
file2_edfwf	=$(dir_edfwf)/config_edf_sched.c
#nombre de la libreria que se generara
lib_edfwf	=$(LIB_DIR)/libedfwf.so


### Configuracion para metodo edf global
#carpeta donde estan los archivos
dir_edfglobal	=$(SCHED_DIR)/global
#archivos C que se compilaran
file2_edfglobal	=$(dir_edfglobal)/config_edf_sched.c
#nombre de la libreria que se generara
lib_edfglobal	=$(LIB_DIR)/libedfglobal.so

############################################################################################
#all: $(objects) $(rm_rbound_mp) $(rm_bf_du_uo)


############################################################################################
# 2. Copiar esta funcion y remplazar por los archivos de la nueva funcion
############################################################################################
### Crear libreria para rm rbound
# edf_bf: $(objects)
	# @echo ==================================================================
	# @echo Compiling...
	# @echo ==================================================================
	# gcc $(file1_edfbf) $(file2_edfbf) $(objects) -shared -o $(lib_edfbf) -DUSE_TCL_STUBS -DSIMLUATOR_LIB_TCL -I$(INCLUDE_DIR) -I/usr/include/tcl8.5 -L/usr/lib -ltclstub8.5 -lm $(CC_OPT)
	# @echo ==================================================================
	# @echo Finish.
	# @echo ==================================================================
############################################################################################
### Crear libreria para edf global
edf_global: $(objects)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	gcc $(file2_edfglobal) $(objects) -shared -o $(lib_edfglobal) -DUSE_TCL_STUBS -DSIMLUATOR_LIB_TCL -I$(INCLUDE_DIR) -I/usr/include/tcl8.5 -L/usr/lib -ltclstub8.5 -lm $(CC_OPT)
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================
	
### Crear libreria para edf bf
edf_bf: $(objects)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	gcc $(file1_edfbf) $(file2_edfbf) $(objects) -shared -o $(lib_edfbf) -DUSE_TCL_STUBS -DSIMLUATOR_LIB_TCL -I$(INCLUDE_DIR) -I/usr/include/tcl8.5 -L/usr/lib -ltclstub8.5 -lm $(CC_OPT)
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================

### Crear libreria para edf ff
edf_ff: $(objects)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	gcc $(file1_edfff) $(file2_edfff) $(objects) -shared -o $(lib_edfff) -DUSE_TCL_STUBS -DSIMLUATOR_LIB_TCL -I$(INCLUDE_DIR) -I/usr/include/tcl8.5 -L/usr/lib -ltclstub8.5 -lm $(CC_OPT)
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================

### Crear libreria para edf ff
edf_nf: $(objects)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	gcc $(file1_edfnf) $(file2_edfnf) $(objects) -shared -o $(lib_edfnf) -DUSE_TCL_STUBS -DSIMLUATOR_LIB_TCL -I$(INCLUDE_DIR) -I/usr/include/tcl8.5 -L/usr/lib -ltclstub8.5 -lm $(CC_OPT)
	@echo ==================================================================
	@echo Finish.
	@echo ==================================================================
	
### Crear libreria para edf ff
edf_wf: $(objects)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	gcc $(file1_edfwf) $(file2_edfwf) $(objects) -shared -o $(lib_edfwf) -DUSE_TCL_STUBS -DSIMLUATOR_LIB_TCL -I$(INCLUDE_DIR) -I/usr/include/tcl8.5 -L/usr/lib -ltclstub8.5 -lm $(CC_OPT)
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
