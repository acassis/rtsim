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
# 0. Copiar y configurar las rutas para un nuevo metodo
############################################################################################
### Configuracion para metodo 
# dir_rmrboundmp	=$(SCHED_DIR)/rm_rbound_mp
# file1_rmrboundmp=$(dir_rmrboundmp)/rbound_mp.c -o $(dir_rmrboundmp)/rbound_mp.o
# file2_rmrboundmp=$(dir_rmrboundmp)/base_rm_global_sched.c -o $(dir_rmrboundmp)/base_rm_global_sched.o
# lib_rmrboundmp	=$(LIB_DIR)/librmrboundmp.so

### Configuracion para metodo rm rbound
dir_rmrboundmp	=$(SCHED_DIR)/rm_rbound_mp
file1_rmrboundmp=$(dir_rmrboundmp)/rbound_mp.c
file2_rmrboundmp=$(dir_rmrboundmp)/base_rm_global_sched.c
lib_rmrboundmp	=$(LIB_DIR)/librmrboundmp.so

### Configuracion para metodo rm bf du uo
dir_rmbfduuo	=$(SCHED_DIR)/rm_bf_du_uo
file1_rmbfduuo	=$(dir_rmbfduuo)/rm_bf_du_uo.c
file2_rmbfduuo	=$(dir_rmbfduuo)/base_rm_global_sched.c
lib_rmbfduuo	=$(LIB_DIR)/librmbfduuo.so


############################################################################################
all: $(objects) $(rm_rbound_mp) $(rm_bf_du_uo)


############################################################################################
# 1. Copiar esta funcion y remplazar por los archivos de la nueva funcion
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
