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
# file2_edfbf	=$(dir_edfbf)/base_edf_global_sched.c
# #nombre de la libreria que se generara
# lib_edfbf	=$(LIB_DIR)/libedfbf.so


### Configuracion para metodo rm rbound
#carpeta donde estan los archivos
dir_edfbf	=$(SCHED_DIR)/edf_bf
#archivos C que se compilaran
file1_edfbf	=$(dir_edfbf)/edf_bf.c
file2_edfbf	=$(dir_edfbf)/base_edf_global_sched.c
#nombre de la libreria que se generara
lib_edfbf	=$(LIB_DIR)/libedfbf.so


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

### Crear libreria para edf bf
edf_bf: $(objects)
	@echo ==================================================================
	@echo Compiling...
	@echo ==================================================================
	gcc $(file1_edfbf) $(file2_edfbf) $(objects) -shared -o $(lib_edfbf) -DUSE_TCL_STUBS -DSIMLUATOR_LIB_TCL -I$(INCLUDE_DIR) -I/usr/include/tcl8.5 -L/usr/lib -ltclstub8.5 -lm $(CC_OPT)
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
