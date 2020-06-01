/*
** $File : lr_wpan_support.ex.c
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
** Module description:  support file for the Low Rate WPAN model
** Last Modification:   October, 2nd 2003
**
*/

/* include header */
#include "lr_wpan_support_15_4a.h"
#include "Physical_Layer.h"

/*
 * Function:	lr_wpan_mac_error
 *
 * Descritpion: print error message and end the simulation
 *
 * ParamIn:		const char * fcnt
 *				name of the function
 *
 *				const char * msg
 *				error message to print
 *
 *				const char * opt
 *				optional error message to print
 *
 */

void lr_wpan_mac_error (const char * fcnt, const char * msg, const char * opt)
{
	FIN (static void lr_wpan_mac_error (fcnt, msg, opt));
	
	/* print error message and end the simulation */
	op_sim_end ("LPR WPAN MAC layer:", fcnt, msg, opt);
	
	FOUT;
}

/*
 * Function:	is_wpan_packet
 *
 * Description:	check if the packet is a wpan packet
 *
 * ParamIn:		Packet * pkptr
 *				pointer to the packet to check
 *
 * ParamOut:	Boolean is_wpan
 *				boolean set to true if the packet is a wpan,
 *				false otherwise
 */

Boolean is_wpan_packet (Packet * pkptr)
{
	char format[64];
	Boolean is_wpan = OPC_TRUE; // return value
	
	
	FIN (is_wpan_packet (pkptr));
	
	/* get the format of the packet */
	op_pk_format (pkptr, format);
	
	/* check the packet format */
	if (!strcmp (format, "lr_wpan_mac") ||
		!strcmp (format, "lr_wpan_ack"))
		is_wpan = OPC_TRUE;
		
	FRET (is_wpan);
}


/*
 * Function:	wpan_node_list_compare_proc
 *
 * Description:	compare the MAC address of two elements
 *				This function is used to find an element
 *				into a list.
 *
 * ParamIn:		const Wpan_Node_Param * element1
 *				pointer to the first element
 *
 *				const Wpan_Node_Param * element2
 *				pointer to the second element
 *
 * ParamOut:	int
 *				integer equal to 0 if the element are the same,
 *				-1 or 1 otherwise.
 */

int wpan_node_list_compare_proc (const Wpan_Node_Param * element1, const Wpan_Node_Param * element2)
{
	/* compare the MAC address of the two elements */
	if (element1->mac_address == element2->mac_address)
		return 0;
	else if (element1->mac_address < element2->mac_address)
		return 1;
	else
		return -1;
}

/*
 * Function:	wpan_search_mac_address
 *
 * Description:	search an element in the list of node, according
 *				to the MAC address in parameter and return the
 *				index of this element in the list if it exists,
 *				otherwise return -1
 *
 * ParamIn:		int mac_address
 *				MAC address to search
 *
 * ParamOut:	int pos_index
 *				position index of the element
 *
 * WARNING: THIS FUNCTION MUST BE USED AFTER THAT ALL THE WPAN
 * DEVICES BE RECORDED IN THE DEVICE LIST.
 */

int wpan_search_mac_address (int mac_address)
{
	int i, pos_index = -1;
	Wpan_Node_Param * element;
	int nbElement = op_prg_list_size (wpan_node_param_list);
	
	FIN (wpan_search_mac_address (mac_address));
	
	if (!nbElement)
		lr_wpan_mac_error ("wpan_search_mac_address:", "No device registered.", OPC_NIL);

	/* search the element in the list of nodes */
	for (i = 0; i < nbElement; i++)
		{
		/* access the element */
		element = op_prg_list_access (wpan_node_param_list, i);
		
		/* check the MAC address*/
		if (element->mac_address == mac_address)
			pos_index = i;
		}

	FRET (pos_index);
}


/*
 * Function:	wpan_store_stranger_node
 *
 * Description:	function used to register the WLAN informations
 *				into the topology
 *
 * ParamIn:		int mac_address
 *				MAC address of the node to register
 *
 *				const char type[5]
 *				string for the node type (ex: "wlan")
 *
 *				WlanT_Rx_State_Info * wlan_info
 *				pointer to the state variable of the WLAN MAC layer
 *				called "rx_state_info_ptr"
 */

void wpan_store_stranger_node (int mac_address, const char type[5], WlanT_Rx_State_Info * wlan_info)
{
	Wpan_Node_Param * new_elt;
	Objid parent;
	double x,y,d_x, d_y; //position of the node
	
	
	FIN (wpan_store_stranger_node (mac_address));
	
	/* get the parent objid */
	parent = op_topo_parent (op_id_self ());
	
	/* get the coordinate of the node */
	op_ima_obj_attr_get (parent, "x position", &x);
	op_ima_obj_attr_get (parent, "y position", &y);
	
	/* addition Milcom 05 */
	op_ima_obj_attr_get (parent, "delta x", &d_x);
	op_ima_obj_attr_get (parent, "delta y", &d_y);

	x = x + d_x;
	y = y + d_y;
	/* end addition Milcom 05 */
	
	
	/* create a new element */
	new_elt = (Wpan_Node_Param *) op_prg_mem_alloc (sizeof(Wpan_Node_Param));
	
	/* fill out this new element */
	new_elt->parent_id = parent;
	new_elt->objid = parent;
	new_elt->mac_address = mac_address;
	new_elt->group = 0;
	new_elt->slotted_enable = OPC_FALSE;
	new_elt->master_enable = OPC_FALSE;
	new_elt->x = x;
	new_elt->y = y;
	new_elt->cca_requirement = OPC_FALSE;
	new_elt->share_statistic = 0;
	new_elt->wlan_info = wlan_info;;
	strcpy (new_elt->type, type);
	
	/* initialize the node list if it is not done */
	if (wpan_node_param_list == OPC_NIL)
		wpan_node_param_list = op_prg_list_create ();
	
	/* register the node into the list */
	op_prg_list_insert (wpan_node_param_list, new_elt, OPC_LISTPOS_TAIL);
	
	
	FOUT;
}


/*
 * Function:	wlan_state_variable_get
 *
 * Description:	get a pointer to the state variable called
 *				"rx_state_info_ptr" in the MAC layer of the WLAN
 *				to update the field "rx_end_time"
 *
 * ParamIn:		Objid objid
 *				ID of the process RX of the custom WLAN
 *
 * ParamOut:	pointer to the state variable of the MAC layer
 *
 * WARNING: THIS FUNCTION MUST BE USED AFTER THAT ALL THE WPAN
 * DEVICES BE RECORDED IN THE DEVICE LIST.
 */

WlanT_Rx_State_Info * wlan_state_variable_get (Objid objid)
{
	int i; // loop variable
	Wpan_Node_Param * element;
	int nbElement = op_prg_list_size (wpan_node_param_list);
	
	
	FIN (wlan_state_variable_get (objid));
	
	/* check if the list is not empty */
	if (!nbElement)
		lr_wpan_mac_error ("wlan_state_variable_get:", "No device registered.", OPC_NIL);

	/* search the element in the list of nodes */
	for (i = 0; i < nbElement; i++)
		{
		/* access the element */
		element = (Wpan_Node_Param *) op_prg_list_access (wpan_node_param_list, i);
		
		/* check the MAC address*/
		if (element->objid == objid)
			{
			FRET ((WlanT_Rx_State_Info *) element->wlan_info);
			}
		}
	
	/* we shouldn't be here */
	lr_wpan_mac_error ("wlan_state_variable_get:", "No device found.", OPC_NIL);
	
	FRET (NULL);
}


/*
 * Function:	wpan_get_mac_address
 *
 * description:	get the MAC address of the Node according
 *				to its ID
 *				The node must be registered in the list
 *				wpan_node_param_list
 *
 * ParamIn:		Objid node_id
 *				ID of the node
 *
 * ParamOut:	int 
 *				MAC address of the node
 *
 * WARNING: THIS FUNCTION MUST BE USED AFTER THAT ALL THE WPAN
 * DEVICES BE RECORDED IN THE DEVICE LIST.
 */

int	wpan_get_mac_address (Objid node_id)
{
	int i; // loop variable
	Wpan_Node_Param * element;
	int nbElement = op_prg_list_size (wpan_node_param_list);
	
	FIN (wpan_get_mac_address (node_id));
	
	/* check if the list is not empty */
	if (!nbElement)
		lr_wpan_mac_error ("wpan_get_mac_address:", "No device registered.", OPC_NIL);

	/* search the element in the list of nodes */
	for (i = 0; i < nbElement; i++)
		{
		/* access the element */
		element = (Wpan_Node_Param *) op_prg_list_access (wpan_node_param_list, i);
		
		/* check the MAC address*/
		if (element->parent_id == node_id)
			{
			FRET (element->mac_address);
			}
		}
	
	/* we shouldn't be here */
	lr_wpan_mac_error ("wpan_get_mac_address:", "No device found.", OPC_NIL);
	
	FRET (-1);
}


/*
 * Function:	wpan_search_wlan_node
 *
 * Description:	search a wlan node
 *
 * WARNING: THIS FUNCTION MUST BE USED AFTER THAT ALL THE WPAN
 * DEVICES BE RECORDED IN THE DEVICE LIST.
 */

Wpan_Node_Param * wpan_search_wlan_node (int index)
{
	Wpan_Node_Param * element = NULL;
	int nbElement = op_prg_list_size (wpan_node_param_list);
	int i;
	int current_index = 0;
	
	FIN (wpan_search_wlan_node (index));
	
	/* check if the list is not empty */
	if (!nbElement)
		lr_wpan_mac_error ("wpan_search_wlan_node:", "No device found.", OPC_NIL);

	/* search the element in the list of nodes */
	for (i = 0; i < nbElement; i++)
		{
		/* access the element */
		element = (Wpan_Node_Param *) op_prg_list_access (wpan_node_param_list, i);
		
		/* check the type of device and the current index */
		if ((strcmp (element->type, "wlan") == 0) && (current_index++ == index))
			{
			FRET (element);
			}
		}
	
	/* we shouldn't be here */
	if (index > current_index)
		{
		/* if the index is too high, we print a special error message */
		lr_wpan_mac_error ("wpan_search_wlan_node:", "The given index is too high.", OPC_NIL);
		}
	
	/* otherwise, we print the standard error message */
	lr_wpan_mac_error ("wpan_search_wlan_node:", "No device match the index.", OPC_NIL);
	
	FRET (OPC_NIL);
}


/*
 * Function:	wpan_list_size_get_wlan_node
 *
 * WARNING: THIS FUNCTION MUST BE USED AFTER THAT ALL THE WPAN
 * DEVICES BE RECORDED IN THE DEVICE LIST.
 */
int wpan_list_size_get_wlan_node ()
{
	int list_size = 0;
	Wpan_Node_Param * element = NULL;
	int nbElement = op_prg_list_size (wpan_node_param_list);
	int i; // loop variable
	
	FIN (wpan_list_size_get_wlan_node ());
	
	/* check if the list is not empty */
	if (!nbElement)
		lr_wpan_mac_error ("wpan_list_size_get_wlan_node:", "No device found.", OPC_NIL);

	/* search the element in the list of nodes */
	for (i = 0; i < nbElement; i++)
		{
		/* access the element */
		element = (Wpan_Node_Param *) op_prg_list_access (wpan_node_param_list, i);
		
		/* check the type of device and the current index */
		if (strcmp (element->type, "wlan") == 0)
			{
			list_size++;
			}
		}
	
	FRET (list_size);
}


/*
 * Function:	lr_wpan_slotted_consistency
 *
 * Description:	check the consistency of the slotted mode
 *				of a LR-WPAN network:
 *				*	check if all the devices of a same group
 *					are in a slotted mode
 *				*	check if there is only one master for one
 *					group
 *				if one of these conditions is false, the function
 *				end the simulation and return an error message
 *
 * ParamIn:		Wpan_Node_Param * master_elt
 *				current master element.
 *
 * WARNING: THIS FUNCTION MUST BE USED AFTER THAT ALL THE WPAN
 * DEVICES BE RECORDED IN THE DEVICE LIST.
 */

void lr_wpan_slotted_consistency (Wpan_Node_Param * master_elt)
{
	Wpan_Node_Param * element = NULL;
	int nbElement = op_prg_list_size (wpan_node_param_list);
	int i; // loop variable
	char error_msg[256], name[64];
	
	
	FIN (lr_wpan_slotted_consistency ());
	
	/* check if the list is not empty */
	if (!nbElement)
		lr_wpan_mac_error ("lr_wpan_slotted_consistency:", "No device found.", "Check if you call the function at the right place !");

	/* search the element in the list of nodes */
	for (i = 0; i < nbElement; i++)
		{
		/* access the element */
		element = (Wpan_Node_Param *) op_prg_list_access (wpan_node_param_list, i);
		
		/* search the element in the same group than the master element */
		if (element != master_elt &&
			!strcmp (element->type, "wpan") &&
			element->group == master_elt->group)
			{
			/* if an element is also a master, we end the simulation with an error message */
			if (element->master_enable)
				{
				/* set the error message and end the simulation */
				sprintf (error_msg, "There is more than 1 master in the group %d", master_elt->group);
				lr_wpan_mac_error ("lr_wpan_slotted_consistency:", error_msg, OPC_NIL);
				}
			
			/* if an element is unslotted, we end the simulation with a error message */
			if (element->slotted_enable == OPC_FALSE)
				{
				/* get the name of the node */
				op_ima_obj_attr_get_str (element->parent_id, "name", 64, name);
				
				/* set the error message and end the simulation */
				sprintf (error_msg, "The mode slotted is off in the device %s", name);
				lr_wpan_mac_error ("lr_wpan_slotted_consistency:", error_msg, OPC_NIL);
				}
			}
		}
	
	FOUT;
}


/*
 * Function:	lr_wpan_slotted_generate_addr_table
 *
 * Description:	generate the destination address table to send
 *				the Beacons on broadcast.
 *
 * ParamIn:		int * nbElement
 *				pointer fill by the function: give the number
 *				of addresses have been set
 *
 * ParamOut:	int * addr_table
 *				destination address table
 *
 * WARNING: THIS FUNCTION MUST BE USED AFTER THAT ALL THE WPAN
 * DEVICES BE RECORDED IN THE DEVICE LIST.
 */

void lr_wpan_slotted_generate_addr_table (Wpan_Node_Param * master_elt, Wpan_Beacon_Param * beacon_ptr)
{
	Wpan_Node_Param * element = NULL;
	int nbElement = op_prg_list_size (wpan_node_param_list);
	int i, j; // loop variable
	
	FIN (lr_wpan_slotted_generate_addr_table (nbElement));
	
	/* check if the list is not empty */
	if (!nbElement)
		lr_wpan_mac_error ("lr_wpan_slotted_generate_addr_table:", "No device found.", "Check if you call the function at the right place !");

	/* reset the number of address */
	beacon_ptr->nb_addresses = 0;
	
	/* search the element in the list of nodes */
	for (i = 0; i < nbElement; i++)
		{
		/* access the element */
		element = (Wpan_Node_Param *) op_prg_list_access (wpan_node_param_list, i);
		
		if (element != master_elt && element->group == master_elt->group)
			beacon_ptr->nb_addresses++;
		}
	
	/* allocate the address table */
	beacon_ptr->addr_table = (int *) op_prg_mem_alloc (beacon_ptr->nb_addresses * sizeof(int));
	
	/* Set the table by searching again the element in the list of nodes */
	for (j = 0, i = 0; i < nbElement; i++)
		{
		/* access the element */
		element = (Wpan_Node_Param *) op_prg_list_access (wpan_node_param_list, i);
		
		if (element != master_elt && element->group == master_elt->group)
			beacon_ptr->addr_table[j++] = element->mac_address;
		}
	
	
	FOUT;
}


/*
 * Function:	lr_wpan_slotted_check_time
 *
 * Description:	compute the time to reach the boundary of
 *				one slot.
 

double lr_wpan_slotted_boundary_time (void)
{
	double time = op_sim_time ();
	double remainder = time;
	
	const double unit = LR_WPAN_BACKOFF_UNIT;//WPAN_CCA_PERIOD + WPAN_TURN_AROUND_TIME;
	
	
	FIN (lr_wpan_slotted_boundary ());
	
	// compute the remainder 
	while (remainder >= unit) remainder -= unit;
	
	// if the remainder is not zero, we compute the next odd time 
	if (remainder > 0.0000001)
		time += (unit - remainder);
	
	FRET (time);
}
*/

/*
 * Function:	uniform_random_value by FRancesco Pantisano
 *
 * Description:	returns a uniform random value in the interval (-a, 1-a)
 */

double uniform_random_value (double a)
{
	double value; 
	
	FIN (uniform_random_value (a));
	
    value =( op_dist_uniform (1.0) ) - a;
	
	FRET (value);
}

/*
 * Function:	Pmd_802_15_4a
 *
 * Description:	Given a Signal To Interference Ratio, return the Prob of 
                missdetection predicted for this receiver.  The graph pmd is based on 
                Ls=64 , TW=128ns ,chan: AWGN ,
 *
 *				## This routine has been coded by Francesco Pantisano 
 *				## recommendations.  - rdp 20 Jun 2008
 * ParamIn:		double sirDB
 *				Signal To Interference (dB)
 *
 * ParamOut:	double Prob_mp
 *				Probability of missdetection
 */

double Pmd_802_15_4a (double snrDB) 
{
  double EbN0,Prob_md;
  double snr = util_inverse_dB (snrDB);
  const double Rb = 1.01e6;		// preamble rate
  const double BW = 499.2e6;		// bandwidth
  const double Tint = 32.05e-9;		// Integration time (Np = 16, T = 2 ns)
  
  /*const double Rb = 106250;	??? 	// bit rate
  const double BW = 4.992e6;	    	// bandwidth*/
  
  Modulation_Handle			modulation_table;
  double EbN0dB;
  
  FIN (Pmd_802_15_4a (snrDB));
  
  //EbN0 = snr*(BW/Rb);	// conversion from SNR to EbN0
  EbN0 = snr + sqrt(snr*(snr+(Tint*BW))); 	//conversion from SNR to EbN0
  
  modulation_table = op_tbl_modulation_get ("Pmd");
  EbN0dB = util_dB (EbN0);
  Prob_md= op_tbl_mod_ber (modulation_table, EbN0dB);
  
  

  FRET (Prob_md);
}

/*
 * Function:	compute_center_frequency
 *
 * Description:	return the center frequency as a function of channel number (ref. Table 39i IEEE 802.15.4a)
 *
 *				## This routine has been coded by Flavia Martelli
 *				## 27 Oct 2008
 *
 * ParamIn:		int channel_number
 *
 * ParamOut:	double fc
 *				Center Frequency
 */

double compute_center_frequency (int channel_number) 
{
  double fc;
  
  
  FIN (compute_center_frequency (int channel_number));
  
  switch(channel_number) {
  	case 0:
		fc = channel0_fc;
		break;
	case 1:
		fc = channel1_fc;
		break;
	case 2:
		fc = channel2_fc;
		break;
	case 3:
		fc = channel3_fc;
		break;
	case 4:
		fc = channel4_fc;
		break;
	case 5:
		fc = channel5_fc;
		break;
	case 6:
		fc = channel6_fc;
		break;
	case 7:
		fc = channel7_fc;
		break;
	case 8:
		fc = channel8_fc;
		break;
	case 9:
		fc = channel9_fc;
		break;
	case 10:
		fc = channel10_fc;
		break;
	case 11:
		fc = channel11_fc;
		break;
	case 12:
		fc = channel12_fc;
		break;
	case 13:
		fc = channel13_fc;
		break;
	case 14:
		fc = channel14_fc;
		break;
	case 15:
		fc = channel15_fc;
		break;
	}

  FRET (fc);
}

/*
 Function:	compute_lecim_dsss_center_frequency
 *
 * Description:	returns LECIM_DSSS center frequency as a function of channel number (ref. Table 68i IEEE 802.15.4k)
 *
 *				
 * ParamIn:		int channel_number
 *
 * ParamOut:	double fc
 *				Center Frequency
 */

double compute_lecim_dsss_center_frequency (int channel_number) 
{
  double fc;
  
  
  FIN (compute_lecim_dsss_center_frequency (int channel_number));
  
  switch(channel_number) {
  	case 0:
		fc = fc_channel0;
		break;
	case 1:
		fc = fc_channel1;
		break;
	case 2:
		fc = fc_channel2;
		break;
	case 3:
		fc = fc_channel3;
		break;
	case 4:
		fc = fc_channel4;
		break;
	case 5:
		fc = fc_channel5;
		break;
	case 6:
		fc = fc_channel6;
		break;
	case 7:
		fc = fc_channel7;
		break;
	case 8:
		fc = fc_channel8;
		break;
	case 9:
		fc = fc_channel9;
		break;
	case 10:
		fc = fc_channel10;
		break;
	case 11:
		fc = fc_channel11;
		break;
	case 12:
		fc = fc_channel12;
		break;
	case 13:
		fc = fc_channel13;
		break;
	case 14:
		fc = fc_channel14;
		break;
	case 15:
		fc = fc_channel15;
		break;
	case 16:
		fc = fc_channel16;
		break;
	case 17:
		fc = fc_channel17;
		break;
	case 18:
		fc = fc_channel18;
		break;
	case 19:
		fc = fc_channel19;
		break;
	case 20:
		fc = fc_channel20;
		break;
	case 21:
		fc = fc_channel21;
		break;
	case 22:
		fc = fc_channel22;
		break;
	case 23:
		fc = fc_channel23;
		break;
	case 24:
		fc = fc_channel24;
		break;
	case 25:
		fc = fc_channel25;
		break;
	case 26:
		fc = fc_channel27;
		break;
	case 28:
		fc = fc_channel28;
		break;
	case 29:
		fc = fc_channel29;
		break;
	case 30:
		fc = fc_channel30;
		break;
	case 31:
		fc = fc_channel31;
		break;
	case 32:
		fc = fc_channel32;
		break;
	case 33:
		fc = fc_channel33;
		break;	
  FRET (fc);
 }
 
 /*
 * Function:	compute_datarate 
 *
 * Description:	returns LECIM_DSSS data rate as a function of data rate number (ref. 19.1.2.1 Data rate in d3IEEE802.15.4k)
 * ParamIn:		int channel_number
 *
 * ParamOut:	double fc
 *				Center Frequency
 */
 double compute_datarate(int datarate)
{

  double d_rate;
  
  
  FIN (compute_datarate (datarate));
  
  switch(datarate) {
  	case 0:
		d_rate = data_rate0;
		break;
	case 1:
		d_rate = data_rate1;
		break;
	case 2:
		d_rate = data_rate2;
		break;
	case 3:
		d_rate = data_rate3;
		break;
	case 4:
		d_rate = data_rate4;
		break;
	case 5:
		d_rate = data_rate5;
		break;
	case 6:
		d_rate = data_rate6;
		break;
	case 7:
		d_rate = data_rate7;
		break;
	case 8:
		d_rate = data_rate8;
		break;
	case 9:
		d_rate = data_rate9;
		break;
	case 10:
		d_rate= data_rate10;
		break;
	case 11:
		d_rate = data_rate11;
		break;
	case 12:
		d_rate= data_rate12;
		break;
	case 13:
		d_rate = data_rate13;
		break;
	case 14:
		d_rate = data_rate14;
		break;
	case 15:
		d_rate = data_rate15;
		break;
	case 16:
		d_rate = data_rate16;
		break;
	case 17:
		d_rate = data_rate17;
		break;
	case 18:
		d_rate = data_rate18;
		break;
	case 19:
		d_rate = data_rate19;
		break;
	case 20:
		d_rate = data_rate20;
		break;
	case 21:
		d_rate = data_rate21;
		break;
	case 22:
		d_rate = data_rate22;
		break;
	case 23:
		d_rate = data_rate23;
		break;
	case 24:
		d_rate = data_rate24;
		break;
	case 25:
		d_rate = data_rate25;
		break;
	case 26:
		d_rate = data_rate27;
		break;
	case 28:
		d_rate= data_rate28;
		break;
	case 29:
		d_rate = data_rate29;
		break;
	case 30:
		d_rate = data_rate30;
		break;
	case 31:
		d_rate = data_rate31;
		break;
	case 32:
		d_rate = data_rate32;
		break;
	case 33:
		d_rate = data_rate33;
		break;	
	case 34:
		d_rate = data_rate34;
		break;
	case 35:
		d_rate = data_rate35;
		break;
	case 36:
		d_rate = data_rate36;
		break;
	case 37:
		d_rate = data_rate37;
		break;
	case 38:
		d_rate = data_rate38;
		break;
	case 39:
		d_rate = data_rate39;
		break;
	case 40:
		d_rate = data_rate40;
		break;
	case 41:
		d_rate = data_rate41;
		break;
	case 42:
		d_rate = data_rate42;
		break;
	case 43:
		d_rate = data_rate43;
		break;
	case 44:
		d_rate = data_rate44;
		break;
	case 45:
		d_rate = data_rate45;
		break;
	case 46:
		d_rate = data_rate46;
		break;
	case 47:
		d_rate = data_rate47;
		break;
	case 48:
		d_rate= data_rate48;
		break;
	case 49:
		d_rate = data_rate49;
		break;
	case 50:
		d_rate = data_rate50;
		break;
	case 51:
		d_rate = data_rate51;
		break;
	case 52:
		d_rate = data_rate52;
		break;
	case 53:
		d_rate = data_rate53;
		break;
	case 54:
		d_rate = data_rate54;
		break;
	case 55:
		d_rate = data_rate55;
		break;
	case 56:
		d_rate = data_rate56;
		break;
	case 57:
		d_rate = data_rate57;
		break;
	case 58:
		d_rate= data_rate58;
		break;
	case 59:
		d_rate = data_rate59;
		break;
	FRET (d_rate);
}