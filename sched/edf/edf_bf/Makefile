MAIN_DIR = ../
SCHED_DIR = ../sched
UTILS_DIR = ../utils
INCLUDE_DIR = ../include
DATA_DIR = $(MAIN_DIR)/data
LIB_DIR=./../RealTSS/AlgorithmsLibraries
CC_OPT = -lpthread
APP_NAME=simulator

schedulers = $(SCHED_DIR)/rm_global_sched.o\
	$(SCHED_DIR)/edf_global_sched.o\
	$(SCHED_DIR)/fifo_global_sched.o\
	$(SCHED_DIR)/edf_deadlines_global_sched.o\
	$(SCHED_DIR)/rm_deadlines_global_sched.o

objects = $(UTILS_DIR)/task_lists.o\
	$(UTILS_DIR)/sched_events.o\
	$(UTILS_DIR)/processor_lists.o\
	$(UTILS_DIR)/trace_event.o\
	$(UTILS_DIR)/rm_nf_ll.o\
	$(UTILS_DIR)/rm_bf_ll.o\
	$(UTILS_DIR)/rm_ff_ll.o\
	$(UTILS_DIR)/rm_wf_ll.o\
	$(UTILS_DIR)/rm_ff_du_uo.o\
	$(UTILS_DIR)/rm_ff_ip.o\
	$(UTILS_DIR)/rm_gt.o\
	$(UTILS_DIR)/rm_nf_ip.o\
	$(UTILS_DIR)/rm_st.o\
	$(UTILS_DIR)/rm_bf_ip.o\
	$(UTILS_DIR)/rm_bf_du_uo.o\
	$(UTILS_DIR)/rbound_mp.o\
	$(UTILS_DIR)/rbound_mp_bf.o\
	$(UTILS_DIR)/rbound_mp_nfr.o\
	$(UTILS_DIR)/edf_nf.o\
	$(UTILS_DIR)/edf_ff.o\
	$(UTILS_DIR)/edf_bf.o\
	$(UTILS_DIR)/edf_wf.o\
	$(UTILS_DIR)/logger.o

app = $(objects) $(schedulers) main
#includes = $(INCLUDE_DIR)/task.h $(INCLUDE_DIR)/processor.h $(INCLUDE_DIR)/sched_event.h
includes = $(INCLUDE_DIR)/*.h

all : $(app) $(so)

so: $(objects) $(schedulers) $(includes)
	gcc $(MAIN_DIR)/main.c $(objects) $(schedulers) -shared -o $(LIB_DIR)/libsimulator.so -DUSE_TCL_STUBS -DSIMLUATOR_LIB_TCL -I/usr/include/tcl8.5 -L/usr/lib -ltclstub8.5 -lm $(CC_OPT)
	echo ........... full simulator lib end ..........................

# compile rm global sched
	#gcc $(SCHED_DIR)/rm_global_sched.c $(objects) -shared -o ./../RealTSS/AlgorithmsLibraries/libRM_Global.so -DSCHED_GLOBAL -DUSE_TCL_STUBS -DSIMLUATOR_LIB_TCL -I/usr/include/tcl8.5 -L/usr/lib -ltclstub8.5 -lm $(CC_OPT)
	#echo .....................................
# compile rm partial NF LL
	#gcc $(SCHED_DIR)/rm_global_sched.c $(objects) -shared -o ./../RealTSS/AlgorithmsLibraries/librmnfll.so -DSCHED_PARTIAL_NF_LL -DUSE_TCL_STUBS -DSIMLUATOR_LIB_TCL -I/usr/include/tcl8.5 -L/usr/lib -ltclstub8.5 -lm $(CC_OPT)
#echo ...........end compilation..........................


main : $(schedulers) $(objects) $(includes)
	cc $(MAIN_DIR)/main.c $(objects) $(schedulers) -o $(APP_NAME).run -lm $(CC_OPT)

rm_global_sched.o : $(objects) $(includes)
	cc -c $(SCHED_DIR)/rm_global_sched.c $(CC_OPT)

edf_global_sched.o : $(objects) $(includes)
	cc -c $(SCHED_DIR)/edf_global_sched.c $(CC_OPT)

fifo_global_sched.o : $(objects) $(includes)
	cc -c $(SCHED_DIR)/fifo_global_sched.c $(CC_OPT)

edf_deadlines_global_sched.o : $(objects) $(includes)
	cc -c $(SCHED_DIR)/edf_deadlines_global_sched.c $(CC_OPT)

rm_deadlines_global_sched.o : $(objects) $(includes)
	cc $(SCHED_DIR)/rm_deadlines_global_sched.c $(CC_OPT)

#$(UTILS_DIR)/task_lists.o :$(UTILS_DIR)/task_lists.c $(includes)
#	@cd $(UTILS_DIR) ; cc -c task_lists.c $(CC_OPT)

#$(UTILS_DIR)/processor_lists.o : $(UTILS_DIR)/processor_lists.c $(includes)
#	@cd $(UTILS_DIR) ; cc -c processor_lists.c $(CC_OPT)

#$(UTILS_DIR)/sched_events.o : $(UTILS_DIR)/sched_events.c $(includes)
#	@cd $(UTILS_DIR) ; cc -c sched_events.c $(CC_OPT)

#$(UTILS_DIR)/trace_event.o : $(UTILS_DIR)/trace_event.c $(includes)
#	@cd $(UTILS_DIR) ; cc -c trace_event.c $(CC_OPT)

# $(UTILS_DIR)/rm_nf_ll.o : $(UTILS_DIR)/rm_nf_ll.c $(includes)
	# @cd $(UTILS_DIR) ; cc -c rm_nf_ll.c $(CC_OPT)

# $(UTILS_DIR)/edf_nf.o : $(UTILS_DIR)/edf_nf.c $(includes)
	# @cd $(UTILS_DIR) ; cc -c edf_nf.c $(CC_OPT)
	
clean :
	-rm $(objects) $(schedulers)

installer : $(app)
	mkdir $(APP_NAME)
	mkdir ./$(APP_NAME)/examples
	cp $(APP_NAME).run ./$(APP_NAME)
	cp $(DATA_DIR)/* ./$(APP_NAME)/examples
	makeself --notemp ./$(APP_NAME)/ $(APP_NAME)_installer.run "Simulator" echo "Done"
	rm -rf $(APP_NAME)/
