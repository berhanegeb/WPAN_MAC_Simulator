/*
** $File : lr_wpan_support_15_4a.h
** model lr_wpan_support 
** MODIFIED FOR IEEE Std 802.15.4a-2007 (Amendment to IEEE Std 802.15.4-2006)
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
** Module description:  support file header for Low Rate WPAN model
** Last Modification:   October 27 2008, Flavia Martelli
**
*/

#ifndef __LR_WPAN_SUPPORT_15_4a__
#define __LR_WPAN_SUPPORT_15_4a__

/* Standard includes */
#include <opnet.h>
#include <stdio.h>
#include <stdlib.h>

/* wlan support include */
#include "wlan_support.h"

/* define some interrupt constants */
#define BEGIN_SIM	(op_intrpt_type () == OPC_INTRPT_BEGSIM)
#define END_SIM	(op_intrpt_type () == OPC_INTRPT_ENDSIM)
#define INTRPT_STRM	(op_intrpt_type () == OPC_INTRPT_STRM)
#define INTRPT_SELF	(op_intrpt_type () == OPC_INTRPT_SELF)
#define INTRPT_REMOTE	(op_intrpt_type () == OPC_INTRPT_REMOTE)
#define INTRPT_PROCESS	(op_intrpt_type () == OPC_INTRPT_PROCESS)

#define CHANNEL_UP_STREAM	0

/* define some ODB trace */
#define ODB_CHANNEL_BUFFER	(op_prg_odb_ltrace_active("chan_buffer") == OPC_TRUE)
#define STATE_PRINT_STATUS	(op_prg_odb_ltrace_active("wpan_state") == OPC_TRUE)
#define FLAG_PRINT_STATUS	(op_prg_odb_ltrace_active("wpan_flag") == OPC_TRUE)
#define ODB_GENERATOR_ENABLED (op_prg_odb_ltrace_active("generator") == OPC_TRUE)
#define ODB_WLAN_TRANSMISSION (op_prg_odb_ltrace_active("wlan_transmission") == OPC_TRUE)

/* general constants */
//light speed in m/s
#define LIGHT_SPEED		300000000.0
//Boltzmann constant in J•K^(-1)
#define K_BOLTZMANN  1.3806504e-23 	
//room temperature in Kelvin
#define T 290


/* Low Rate WPAN constants */

/* define WPAN bit rate (in bit/s) (chosen from the possible values in Table 39a 802.15.4a)*/
#define LR_WPAN_BIT_RATE		850000.0

/* define one symbol (in seconds) for a data rate of 850 Kb/s */
#define LR_WPAN_SYMBOL		0.00000102564

/* define how many bits correspond to a symbol (referring to BPM-BPSK modulation with ED receiver)*/
#define LR_WPAN_BITS_PER_SYMBOL		1

/*define the center frequency for the different channels UWB PHY (Table 39i 802.15.4a)*/
#define channel0_fc		499.2e6
#define channel1_fc		3494.4e6
#define channel2_fc		3993.6e6
#define channel3_fc		4492.8e6
#define channel4_fc		3993.6e6
#define channel5_fc		6489.6e6
#define channel6_fc		6988.8e6
#define channel7_fc		6489.6e6
#define channel8_fc		7488.0e6
#define channel9_fc		7987.2e6
#define channel10_fc	8486.4e6
#define channel11_fc	7987.2e6
#define channel12_fc	8985.6e6
#define channel13_fc	9484.8e6
#define channel14_fc	9984.8e6
#define channel15_fc	9484.8e6

/*define the bandwidth for the different channels UWB PHY (Table 39i 802.15.4a)*/
#define channel0_W		499.2e6
#define channel1_W		499.2e6
#define channel2_W		499.2e6
#define channel3_W		499.2e6
#define channel4_W		1331.2e6
#define channel5_W		499.2e6
#define channel6_W		499.2e6
#define channel7_W		1081.6e6
#define channel8_W		499.2e6
#define channel9_W		499.2e6
#define channel10_W		499.2e6
#define channel11_W		1331.2e6
#define channel12_W		499.2e6
#define channel13_W		499.2e6
#define channel14_W		499.2e6
#define channel15_W		1354.97e6

/*define the center frequency for the different channels UWB PHY (Table 68i 802.15.4k)*/
#define fc_channel0		863.125e6
#define fc_channel1		863.325e6
#define fc_channel2		863.525e6
#define fc_channel3		863.725e6
#define fc_channel4		863.925e6
#define fc_channel5		864.125e6
#define fc_channel6		864.325e6
#define fc_channel7		864.525e6
#define fc_channel8		864.725e6
#define fc_channel9		864.925e6
#define fc_channel10	865.125e6
#define fc_channel11	865.325e6
#define fc_channel12	865.525e6
#define fc_channel13	865.725e6
#define fc_channel14	865.925e6
#define fc_channel15	866.125e6
#define fc_channel16	866.325e6
#define fc_channel17	866.525e6
#define fc_channel18	866.725e6
#define fc_channel19	866.925e6
#define fc_channel20	867.125e6
#define fc_channel21	867.325e6
#define fc_channel22	867.525e6
#define fc_channel23	867.725e6
#define fc_channel24	867.925e6
#define fc_channel25	868.125e6
#define fc_channel26    868.325e6
#define fc_channel27	868.525e6
#define fc_channel28	868.725e6
#define fc_channel29	868.925e6
#define fc_channel30	869.125e6
#define fc_channel31	869.325e6
#define fc_channel32	869.525e6
#define fc_channel33	869.725e6

/* PHY constants (Table 22 802.15.4) */
//The maximum PSDU size (in octets) the PHY shall be able to receive
#define aMaxPHYPacketSize			127 
//RX-to-TX or TX-to-RX maximum turnaround time (in symbols) 
#define aTurnaroundTime				12  

/* MAC sublayer constants*/

/*(in symbols)*/
/*define the Ack wait duration = aTurnaroundTime + PreambleSymbols (64) + SFDSymbols(8)+ ACK_PHR&PSDUSymbols (56) */
#define macAckWaitDuration			140

// (Table 3 802.15.4a)
#define aMinLIFSPeriod				40
#define aMinSIFSPeriod				12

// (Table 85 802.15.4)
#define aNumSuperframeSlots			16
#define aBaseSuperframeDuration		(aBaseSlotDuration * aNumSuperframeSlots)

/*(in octets)*/
#define aMinMPDUOverhead			9
#define aMaxMACPayloadSize			(aMaxPHYPacketSize - aMinMPDUOverhead)
#define aMaxSIFSFrameSize			18

/* define the lenght of the different fields in the PHY header (in symbols) */
#define PRE 		64
#define SFD   		8
#define PHR 		16
/* define the physical overhead in symbols*/
#define LR_WPAN_PHY_OVERHEAD    		(PRE+SFD+PHR)

/*define the size of the Ack packet (5 bytes) = 40 bits*/
#define ACK 		40

/* define the maximum MAC payload size in bits */
#define WPAN_PAYLOAD_MAX_SIZE	(aMaxMACPayloadSize*8)

/* define the MAC header size in bits */
#define WPAN_HEADER_SIZE	(aMinMPDUOverhead*8)

/* define the maximum bit for a MAC WPAN packet (in bits) */
#define WPAN_MAC_MAX_SIZE	(aMaxPHYPacketSize*8)

/* define the size of the data request packet (10 bytes) = 80 bits */
#define WPAN_DATA_REQ_SIZE	80

/* Define the time to wait for an acknowledgment (in seconds) */
#define MAC_ACK_WAIT_DURATION	((double)macAckWaitDuration*LR_WPAN_SYMBOL)

/* define the turn around time, period needed to switch the channel (in seconds)*/
#define WPAN_TURN_AROUND_TIME	((double)aTurnaroundTime*LR_WPAN_BITS_PER_SYMBOL/LR_WPAN_BIT_RATE)

/* define the LIFS period (in seconds)*/
#define WPAN_LIFS_DURATION	((double)aMinLIFSPeriod*LR_WPAN_BITS_PER_SYMBOL/LR_WPAN_BIT_RATE)

/* define the time spend in the CCA (in seconds) = 80 symbols(64 symb pre) 40 symbols(32 symb pre) 20 symbols(16 symb pre)*/
#define	WPAN_CCA_PERIOD		(80.0*LR_WPAN_SYMBOL)



/* Propagation delay to compute aBaseSlotDuration (symbols) */
#define PROPAGATION_DELAY		1

/*the superframe slot has been computed considering that it has to comprise the headers and the payload of both data frame and acknowledgement frame, the propagation delays and the minimum long interframe spacing (LIFS) */
//#define aBaseSlotDuration		(2*PROPAGATION_DELAY+2*LR_WPAN_PHY_OVERHEAD+WPAN_HEADER_SIZE+WPAN_PAYLOAD_MAX_SIZE+aTurnaroundTime+macAckWaitDuration+ACK+aMinLIFSPeriod)
//#define aBaseSlotDuration		1426

// aUnitBackoffPeriod = aBaseSlotDuration/2 (PSMA)
//# define aUnitBackoffPeriod				(aBaseSlotDuration/2)

/* backoff time unit (in seconds) */
//#define LR_WPAN_BACKOFF_UNIT 				(aUnitBackoffPeriod*LR_WPAN_BITS_PER_SYMBOL/LR_WPAN_BIT_RATE)
//#define LR_WPAN_BACKOFF_PERIOD_DURATION  	(aUnitBackoffPeriod*LR_WPAN_BITS_PER_SYMBOL/LR_WPAN_BIT_RATE)






#define MAX_NUMBER_OF_BACKOFF_PERIODS 	786432

/* define the maximum sequence number (8 bits) = 2^8 */
#define MAX_MAC_SEQN			256
	
/* define the maximum devices per group */
//#define MAX_DEVICES_PER_GROUP		64
	
/* Maximum and minimum of the backoff exponent as defined in the specification */
//#define MIN_BACKOFF_EXPONENT	2
//#define MAX_BACKOFF_EXPONENT	5
	
/* Flags to load different variables based on attribute settings.	*/
#define	WPAN_PNC					1
#define	WPAN_FFD					1
#define WPAN_RFD					0

/*define the minimum number of backoff periods needed to perform the CCA in the current superframe*/
#define MIN_BACKOFF_PERIOD_TO_PROCEED_PSMA		3

/* define the packet type*/
typedef enum {
	WLAN_PKT_TYPE,
	WPAN_PKT_TYPE,
	BT_MAS_PKT_TYPE,
	BT_SLA_PKT_TYPE	
} Wpan_Pkt_Type;


/* structure for the WPAN frame types */
typedef enum WPAN_MAC_Frame_Type
{
	WPAN_Beacon			= 0, 
	WPAN_Data	    	= 1,
	WPAN_Ack 		    = 2,       
	WPAN_Command		= 3,  
	WPAN_None			= 7,
//	zero                = 7,
} WPAN_MAC_Frame_Type;


/* Define the superframe parameters */
typedef struct {
  int 		beacon_interval_symbols;
  double	beacon_interval_seconds;
  int 		superframe_duration_symbols;  
  double 	superframe_duration_seconds;
  double 	superframe_start_time;
  int 		inactive_period_symbols;
  double 	inactive_period_seconds;
  int 		slot_duration_symbols;
  double 	slot_duration_seconds;
  int 		backoff_periods_per_superframe;
  int 		backoff_periods_per_CAP;
  int 		backoff_periods_per_slot;
  int 		backoff_periods_time_symbols;
  int 		backoff_periods_time_seconds;
  int 		backoff_period_index;
  int 		time_slot_index;
  int 		CAP_period_length_symbols;
  double 	CAP_period_length_seconds;
  double	CAP_start_time;
  int 		remaining_CAP_backoff_periods;
  double 	end_of_the_CAP_period;
  int 		GTS_period_length_symbols;
  double 	GTS_period_length_seconds;
  int 		remaining_GTS_backoff_periods;
  
  Boolean 	has_GTS_period;
  Boolean 	has_inactive_period;
  Boolean 	CAP_PERIOD_ACTIVE;
  Boolean 	GTS_PERIOD_ACTIVE;
  Boolean 	INACTIVE_PERIOD;
  int *		backoff_period_boundary_symbols;
  int *		time_slot_boundary_symbols;
 } Wpan_Superframe_Param;


/* structure for the superframe specification field */
typedef struct {
  int beacon_order;
  int superframe_order; 
  int final_CAP_slot;
  Boolean battery_life_ext;
  //int-Boolean reserved
  Boolean PAN_coordinator;
  Boolean association_permit;
	  
} Superframe_Spec_Field;


/* define structure */
/* structure for the packet definition in the MAC Layer */
typedef struct {
  int frame_type;
  Boolean security_enabled;
  Boolean frame_pending;
  Boolean ack_req;
  Boolean intra_pan;
  int dest_addr_mode;
  int src_addr_mode;
} Frame_Ctrl_Field;

typedef struct {
  int dest_pan_id;
  int dest_addr; // destination MAC address
  int src_pan_id;
  int src_addr; // source MAC address
  int packet_pending; // artificial flag to know how many packets are pending in the slotted model
} Addressing_Field;

typedef struct {
	Objid	parent_id; // ID of the node
	Objid	objid;	// ID of the module which received the packets
	int		mac_address; // mac address of the node
	int		group; // group of the node
	double 	frequency_wpan;
	Boolean slotted_enable; // establish a slotted or unslotted connexion
	Boolean master_enable; // In case of slotted access, we have to determine a master
	double	x; // X coordinate of the node 
	double	y; // Y coordinate of the node
	char 	type[5]; // type of node
	Boolean cca_requirement; // say if a CCA is required
	int 	share_statistic; // Higher layer packet well received
	double	power;			// Power of the transmission
	double  frequency;      // frequency center of WLAN
	WlanT_Rx_State_Info * wlan_info; // info on the WLAN
} Wpan_Node_Param;

/* Define the Beacon parameters */
typedef struct {
	double stop_time; // stop time of the beacon
	int * addr_table; // mac address table for the broadcast transmission of the Beacons
	int nb_addresses; // number of addresses in the table
	Boolean beacon_rcvd; // flag to know if a Beacon has been received
	Boolean data_req_rcvd; // flag to know if we received a data request
	Boolean second_cca_req; // flag to know if a second cca is pending
	int master_addr; // MAC address of the master of the group
	Packet * data_request; // data request packet
} Wpan_Beacon_Param;

/* variable to store the nodes parameters */
List * wpan_node_param_list;

/* objid of the channel in the topology */
Objid wpan_channel_objid;

/* center frequency according to the channel number */
//double wpan_center_freq;

/* CCA mode flag: check of all packet types or just the WPAN/WLAN packets */
Boolean wpan_cca_all_pkt_types;
Boolean wlan_cca_all_pkt_types;


/* function prototypes */
void				lr_wpan_mac_error (const char * fcnt, const char * msg, const char * opt);
Boolean				is_wpan_packet (Packet * pkptr);
int					wpan_node_list_compare_proc (const Wpan_Node_Param * element1, const Wpan_Node_Param * element2);
int 				wpan_search_mac_address (int mac_address);
void 				wpan_store_stranger_node (int mac_address, const char type[5], WlanT_Rx_State_Info * wlan_info);
WlanT_Rx_State_Info * 	wlan_state_variable_get (Objid objid);
int					wpan_get_mac_address (Objid node_id);
Wpan_Node_Param *	wpan_search_wlan_node (int index);
int					wpan_list_size_get_wlan_node (void);
void 				lr_wpan_slotted_consistency (Wpan_Node_Param * master_elt);
void				lr_wpan_slotted_generate_addr_table (Wpan_Node_Param * master_elt, Wpan_Beacon_Param * beacon_ptr);
//double				lr_wpan_slotted_boundary_time (void);

double	            uniform_random_value (double a);
double              Pmd_802_15_4a (double snrDB); 

double 				compute_center_frequency (int channel_number); 

#endif // end of __LR_WPAN_SUPPORT_15_4a__
