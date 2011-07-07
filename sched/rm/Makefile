############################################################################################
# configurar rutas a las carpetas necesarias
############################################################################################
SCHED_DIR	=.
BASE_DIR	=../..
UTILS_DIR 	=$(BASE_DIR)/utils
INCLUDE_DIR =$(BASE_DIR)/include
LIB_DIR		=$(BASE_DIR)/RealTSS/AlgorithmsLibraries
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

app = $(objects) $(schedulers) main
#includes = $(INCLUDE_DIR)/task.h $(INCLUDE_DIR)/processor.h $(INCLUDE_DIR)/sched_event.h
includes = $(INCLUDE_DIR)/

all : $(rm_rbound_mp)

############################################################################################
#copiar esta funcion y remplazar por los archivos de la nueva funcion
############################################################################################
#rm_rbound_mp: $(objects)
#	gcc $(SCHED_DIR)/rm_rbound_mp/rbound_mp.c  $(SCHED_DIR)/rm_rbound_mp/base_rm_global_sched.c $(objects) $(schedulers) -shared -o $(LIB_DIR)/librmrbound_mp.so -DUSE_TCL_STUBS -DSIMLUATOR_LIB_TCL -I$(includes)-I/usr/include/tcl8.5 -L/usr/lib -ltclstub8.5 -lm $(CC_OPT)
############################################################################################

rm_rbound_mp: $(objects)
	gcc $(SCHED_DIR)/rm_rbound_mp/rbound_mp.c  $(SCHED_DIR)/rm_rbound_mp/base_rm_global_sched.c $(objects) $(schedulers) -shared -o $(LIB_DIR)/librmrbound_mp.so -DUSE_TCL_STUBS -DSIMLUATOR_LIB_TCL -I$(includes)-I/usr/include/tcl8.5 -L/usr/lib -ltclstub8.5 -lm $(CC_OPT)

	
	

clean :
	-rm $(objects) $(rm_rbound_mp)

# installer : $(app)
	# mkdir $(APP_NAME)
	# mkdir ./$(APP_NAME)/examples
	# cp $(APP_NAME).run ./$(APP_NAME)
	# cp $(DATA_DIR)/* ./$(APP_NAME)/examples
	# makeself --notemp ./$(APP_NAME)/ $(APP_NAME)_installer.run "Simulator" echo "Done"
	# rm -rf $(APP_NAME)/
