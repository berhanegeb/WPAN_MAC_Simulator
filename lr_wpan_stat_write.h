/*
** $File : lr_wpan_stat_write.h
**
** Low Rate WPAN model in Opnet
** National Institute of Standards and Technology
**
** This model was developed at the National Institute of Standards
** and Technology by employees of the Federal Government in the course
** of their official duties. Pursuant to title 17 Section 105 of the
** United States Code this software is not subject to copyright
** protection and is in the public domain. This is an experimental
** system.  NIST assumes no responsibility whatsoever for its use by
** other parties, and makes no guarantees, expressed or implied,
** about its quality, reliability, or any other characteristic.
**
** We would appreciate acknowledgement if the model is used.
**
** NIST ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS" CONDITION
** AND DISCLAIM ANY LIABILITY OF ANY KIND FOR ANY DAMAGES WHATSOEVER
** RESULTING FROM THE USE OF THIS SOFTWARE.
**
** Primary Author:      O. Rebala
** Module description:  support file header for writing statistics
** Last Modification:   November, 28th 2003
**
*/

#ifndef __LR_WPAN_STAT_WRITE__
#define __LR_WPAN_STAT_WRITE__

/* Standard includes */
#include <opnet.h>
#include <time.h>
#include "lr_wpan_support_15_4a.h"

/* define some ODB trace */
#define ODB_STAT_WRITE	(op_prg_odb_ltrace_active("file_info") == OPC_TRUE)


/* define the statistic structure for the WLAN MAC */
typedef struct {
	int packet_rcvd;
	int bad_packet;
	int lost_packet;
	int collided_packet;
} WlanT_Mac_Stat;


/* function prototypes */
void 	lr_wpan_stat_error (const char * fcnt, const char * msg, const char * opt);
FILE *	lr_wpan_open_report_file (const char * name, Boolean * already_created);
char *	integer_to_string (int integer, int str_size);
char *	double_to_string (double a_double, int str_size);
void 	wlan_mac_collect_stat (const WlanT_Mac_Stat wlan_stat, const char * wlan_name);


#endif // end of __LR_WPAN_STAT_WRITE__
