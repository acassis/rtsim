#ifndef __SIMULATOR_H__
#define __SIMULATOR_H__

	#define OS_WINDOWS
	//#define OS_LINUX


	#ifdef OS_LINUX
		#define USE_THREAD			//ONLY for linux version
	#endif

	#ifdef USE_THREAD
		#include <pthread.h>
	#endif


	typedef enum {
		EDF = 0,
		RM,
		EDF_DEADLINES,
		RM_DEADLINES,
		FIFO,
	} ALGORITHM;

	typedef enum
	{
		MODE_GLOBAL,
		MODE_PARTIAL,
		MODE_COUNT,
	}ALGORITHM_MODE;

	typedef struct
	{
		ALGORITHM algorithm;
		ALGORITHM_MODE mode;
		int	partial_func;
		int processor;
		int time;
		char data[255];
		int param_count;
	}ALGORITHM_PARAMS;


	typedef enum {
		MENU_EDF_GLOBAL = 0,
		MENU_EDF_PARTIAL_NF,
		MENU_EDF_PARTIAL_FF,
		MENU_EDF_PARTIAL_BF,
		MENU_EDF_PARTIAL_WF,

		MENU_RM_GLOBAL,
		MENU_RM_PARTIAL_NF_LL,
		MENU_RM_PARTIAL_BF_LL,
		MENU_RM_PARTIAL_FF_LL,
		MENU_RM_PARTIAL_WF_LL,

		MENU_RM_PARTIAL_FF_DU_UO,
		MENU_RM_PARTIAL_FF_IP,
		MENU_RM_PARTIAL_GT,
		MENU_RM_PARTIAL_NF_IP,
		MENU_RM_PARTIAL_ST,

		MENU_RM_PARTIAL_BF_IP,
		MENU_RM_PARTIAL_BF_DU_UO,
		MENU_RM_PARTIAL_RBOUND_MP,
		MENU_RM_PARTIAL_RBOUND_MP_BF,
		MENU_RM_PARTIAL_RBOUND_MP_NFR,


		MENU_EDF_DEADLINES,
		MENU_RM_DEADLINES,
		MENU_FIFO,
		MENU_COUNT,
	} MENU_ITEM;


	#include "logger.h"

#endif //__CONFIG_H__
