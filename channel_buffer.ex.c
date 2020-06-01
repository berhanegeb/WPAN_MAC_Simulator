/*
** channel_buffer.ex.c :
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
** Primary Author:      Olivier Rebala
** Secondary Author:    Nicolas Chevrollier
** Module description:  Channel Buffer for Low Rate WPAN model
** Last Modification:   October, 23, 2004
*/

/* include header */
#include "channel_buffer.h"


/*
 * Function:	channel_buffer_error
 *
 * Description:	Error handling procedure
 *
 * ParamIn:		char * : fcnt
 *				The function in the process
 *				where the error occured
 *
 * ParamIn:		char * : msg
 *				The description of the error
 *
 * ParamIn:		char * : opt
 *				An optional message
 */

void	channel_buffer_error (char * fcnt, char * msg, char * opt)
{
	/* Terminates simulation and print an error message. */
	FIN (channel_buffer_error (fcnt, msg, opt));

	op_sim_end ("Error in the channel buffer interface:", fcnt, msg, opt);

	FOUT;
}


/*
 * Function:	channel_buffer_register_packet
 *
 * Description:	record a packet into the channel buffer
 *
 * ParamIn:		Buff_Info_Packet * packet
 *				pointer to the packet to be registered
 */

void channel_buffer_register_packet (Buff_Info_Packet * packet)
{
	Buff_Info_Packet * packet_browser;
	
	FIN (channel_buffer_register_packet (buffer_ptr, packet));
	
	/* check the pointer to the packet to register */
	if (packet == NULL)
		channel_buffer_error ("channel_buffer_register_packet:", "The pointer to the packet to register is null.", OPC_NIL);
	
	/* initialize the packet browser */
	if ((packet_browser = channel_buffer_ptr) == NULL)
		{
		/* copy the packet into the first cell */
		channel_buffer_ptr = packet;
		}
	else
		{
		while (packet_browser->next_packet != NULL)
			{
			/* check if the current packet is overlap with the packet to register */ 
			channel_buffer_register_collision (packet_browser, packet);
			
			/* get the next cell */
			packet_browser = packet_browser->next_packet;
			}
		
		/* register the collision for the last current packet */
		channel_buffer_register_collision (packet_browser, packet);
		
		/* copy the packet */
		packet_browser->next_packet = packet;
		}

	FOUT;
}


/*
 * Function:	channel_buffer_remove_packet
 *
 * Description:	remove a packet from the channel buffer
 */

void channel_buffer_remove_packet (Buff_Info_Packet * packet)
{
	Buff_Info_Packet * packet_browser;
	
	FIN (channel_buffer_remove_packet (packet));
	
	/* initialize the packet browser */
	packet_browser = channel_buffer_ptr;
	
	/* special case: if the packet to remove is the first one of the buffer */
	if (packet_browser == packet)
		{
		/* remove the packet from the list */
		channel_buffer_ptr = packet->next_packet;
		
		/* free the memory */
		while (packet != NULL)
			{
			/* keep a pointer to the packet */
			packet_browser = packet;
		
			/* get the next collision packet */
			packet = packet->next_collision;
		
			/* free the memory for the previous packet */
			op_prg_mem_free (packet_browser);
			}
		
		FOUT;
		}
	
	/* search the position of the packet to remove inside the buffer */
	while (packet_browser != NULL && packet_browser->next_packet != NULL && packet_browser->next_packet != packet)
		packet_browser = packet_browser->next_packet;
	
	/* check if the selected packet precedes the packet to remove */
	if (packet_browser->next_packet != packet)
		channel_buffer_error ("channel_buffer_remove_packet", "the packet to remove doesn't exixt", OPC_NIL);
	
	/* remove the packet from the buffer list */
	packet_browser->next_packet = packet->next_packet;
	
	/* free the memory */
	while (packet != NULL)
		{
		/* keep a pointer to the packet */
		packet_browser = packet;
		
		/* get the next collision packet */
		packet = packet->next_collision;
		
		/* free the memory for the previous packet */
		op_prg_mem_free (packet_browser);
		}
	
	FOUT;
}


/*
 * Function:	channel_buffer_search_by_id
 *
 * description:	search a packet into the buffer according the ID of the packet
 *
 * ParamIn:		int packet_id
 *				ID of the packet to search
 *
 * ParamOut:	Buff_Info_Packet * packet_browser
 *				pointer to the found packet. Pointer is null if no packet fit the ID.
 */

Buff_Info_Packet * channel_buffer_search_by_id (int packet_id)
{
	Buff_Info_Packet * packet_browser;
	
	FIN (channel_buffer_search_by_id (packet_id));
	
	/* initialize the packet pointer */
	packet_browser = channel_buffer_ptr;
	
	/* search the good packet */
	while (packet_browser != NULL && packet_browser->packet_id != packet_id)
		packet_browser = packet_browser->next_packet;
	
	FRET (packet_browser);
}


/*
 * Function:	allocate_info_packet_cell
 *
 * Description:	create a new info packet cell
 *
 * ParamOut:	Buff_Info_Packet * pkptr
 *				return a pointer to the created cell
 */

Buff_Info_Packet * create_info_packet_cell ()
{
	Buff_Info_Packet * pkptr;
	
	FIN (allocate_info_packet_cell ());
	
	/* allocate the memory */
	pkptr = (Buff_Info_Packet *) op_prg_mem_alloc (sizeof (Buff_Info_Packet));
	
	/* make default value */
	pkptr->packet_id 		= 0;
	pkptr->packet_type 		= 0.0;
	pkptr->packet_size 		= 0.0;
	pkptr->power 			= 0.0;
	pkptr->txrx_distance 	= 0.0;
	pkptr->tx_x 			= 0.0;
	pkptr->tx_y 			= 0.0;
	pkptr->rx_x 			= 0.0;
	pkptr->rx_y 			= 0.0;
	pkptr->dest_objid 		= 0;
	pkptr->src_objid 		= 0;
	pkptr->tx_time 			= 0.0;
	pkptr->tx_delay		 	= 0.0;
	pkptr->prop_delay		= 0.0;
	pkptr->delivery_time	= 0.0;
	pkptr->frequency 		= 0.0;
	pkptr->nb_collisions 	= 1;
	
	/* initialize the pointer to null */
	pkptr->next_packet = NULL;
	pkptr->next_collision = NULL;
	
	FRET (pkptr);
}


/*
 * Function:	channel_buffer_register_collision
 *
 * Description:	if the two packet in parameters are in collision, we record a copy
 *				of each one into the packet cells.
 *
 * ParamIn:		Buff_Info_Packet * current_packet
 *				pointer to a packet already record in the channel buffer
 *
 *				Buff_Info_Packet * packet_to_register
 *				pointer to a packet to record in the buffer
 */

void channel_buffer_register_collision (Buff_Info_Packet * current_packet, Buff_Info_Packet * packet_to_register)
{
	Buff_Info_Packet * collision_browser;
	
	
	FIN (channel_buffer_register_collision (current_packet, packet_to_register));
	
	/* check the both pointers */
	if (current_packet == NULL || packet_to_register == NULL)
		channel_buffer_error ("channel_buffer_register_collision:", "channel packet buffer pointer is null.", OPC_NIL);
	
	/* if the 2 packets come from the same sources, the packets cannot overlap */
	if (packet_to_register->src_objid == current_packet->src_objid)
		{
		/* exit the function */
		FOUT;
		}
	
	/*
	printf("packet to register src %d det %d \n", packet_to_register->src_objid, packet_to_register->dest_objid);
	printf(" device id register src %d\n",op_topo_parent(packet_to_register->src_objid));
	printf(" device id register dest %d\n",op_topo_parent(packet_to_register->dest_objid));
	printf("packet to current src %d det %d \n", current_packet->src_objid, current_packet->dest_objid);
	printf(" device id current src %d\n",op_topo_parent(current_packet->src_objid));
	printf(" device id current dest %d\n",op_topo_parent(current_packet->dest_objid));
	*/
	
	/* check if the current packet is overlap with the packet to register */ 
	if (packet_to_register->tx_time != 0.0 &&
		packet_to_register->tx_time < current_packet->delivery_time)
		{
		
		if (packet_to_register->packet_type == WPAN_PKT_TYPE && current_packet->packet_type == WPAN_PKT_TYPE)
			{
			if ( packet_to_register->dest_objid == current_packet->dest_objid)
				{
				if((packet_to_register->noise == OPC_FALSE) && (current_packet->noise == OPC_FALSE))
					{
					packet_to_register->noise = OPC_TRUE;			
					}
				}
			}
		
		if (op_topo_parent(current_packet->dest_objid) != op_topo_parent(packet_to_register->src_objid))
			{
			/* initialize the pointer to the first collision */
			collision_browser = current_packet;
		
			/* we get the last collision registered */
			while (collision_browser->next_collision != NULL)
				collision_browser = collision_browser->next_collision;
		
			/* copy the packet information at the end of the list */
			collision_browser->next_collision = copy_packet_info_cell (packet_to_register);
			}
		
		if (op_topo_parent(packet_to_register->dest_objid) != op_topo_parent(current_packet->src_objid))
			{/* copy the current packet as collision of the packet to register */
			collision_browser = packet_to_register;
			
			while (collision_browser->next_collision != NULL)
				collision_browser = collision_browser->next_collision;
			
			collision_browser->next_collision = copy_packet_info_cell (current_packet);
		
			/* update the number of collision of each packet */
			(current_packet->nb_collisions)++;
			(packet_to_register->nb_collisions)++;		
			}
		}
	
	FOUT;
}


/*
 * Function:	copy_packet_info_cell
 *
 * Description:	copy a info packet cell into another cell
 *
 * ParamIn:		Buff_Info_Packet * packet
 *				pointer to the packet to copy
 *
 * ParamOut:	Buff_Info_Packet * copy_ptr
 *				pointer to the copy of the cell
 */

Buff_Info_Packet * copy_packet_info_cell (Buff_Info_Packet * packet)
{
	Buff_Info_Packet * copy_ptr;
	
	FIN (copy_packet_info_cell (packet));
	
	/* create a new cell */
	copy_ptr = create_info_packet_cell ();
	
	/* copy the value */
	copy_ptr->packet_id 	= packet->packet_id;
	copy_ptr->packet_type 	= packet->packet_type;
	copy_ptr->packet_size 	= packet->packet_size;
	copy_ptr->power 		= packet->power;
	copy_ptr->txrx_distance = packet->txrx_distance;
	copy_ptr->tx_x			= packet->tx_x;
	copy_ptr->tx_y			= packet->tx_y;
	copy_ptr->rx_x			= packet->rx_x;
	copy_ptr->rx_y			= packet->rx_y;
	copy_ptr->dest_objid	= packet->dest_objid;
	copy_ptr->src_objid		= packet->src_objid;
	copy_ptr->frequency 	= packet->frequency;
	copy_ptr->tx_time 		= packet->tx_time;
	copy_ptr->tx_delay 		= packet->tx_delay;
	copy_ptr->prop_delay 	= packet->prop_delay;
	copy_ptr->delivery_time = packet->delivery_time;
	
		
	FRET (copy_ptr);
}


/*
 * Function:	search_pkt_id_for_delivery
 *
 * Description:	
 */

Buff_Info_Packet * search_pkt_info_for_delivery ()
{
	Buff_Info_Packet * element;
	
	
	FIN (search_pkt_info_for_delivery ());
	
	/* initialize the element */
	element = channel_buffer_ptr;
	
	/* we search the packet with a delivery time equal to the current time */
	while (element != NULL && element->delivery_time != op_sim_time ())
		element = element->next_packet;
	
	/* check if the element is NULL */
	if (element == NULL)
		channel_buffer_error ("search_pkt_id_for_delivery:", "No packet found for delivery.", OPC_NIL);
	
	FRET (element);
}


/*
 * Function:	chan_buffer_print_info_pkt
 *
 * Description:	print a packet information cell from the buffer
 *
 * ParamIn:		Buff_Info_Packet * packet
 *				pointer to the information cell to print
 */

void chan_buffer_print_info_pkt (Buff_Info_Packet * packet)
{	
	char dest_name[64];
	
	FIN (chan_buffer_print_info_pkt (info_pkt));

	if (packet == NULL)
		channel_buffer_error ("chan_buffer_print_info_pkt:", "The information packet cell is void", OPC_NIL);
	
	/* get the name of the destination */
	op_ima_obj_attr_get_str (op_topo_parent (packet->dest_objid), "name", 64, dest_name);
	
	/*printf ("\n+--------------------------------------------------------------\n");
	printf ("| Packet %d, %.0f MHz\n", (int) packet->packet_id, packet->frequency); 
	printf ("| Packet %d, %s, %.0f bits, %.0f MHz\n", (int) packet->packet_id,
		(packet->packet_type == WLAN_PKT_TYPE)?"WLAN":"LR WPAN", packet->packet_size, packet->frequency);
	printf ("| Destination name: %s\n", dest_name);
	printf ("| coordinates:\n");
	printf ("| \tTransmitter (%.1f ; %.1f)\n", packet->tx_x, packet->tx_y);
	printf ("| \tReceiver (%.1f ; %.1f)\n", packet->rx_x, packet->rx_y);
	printf ("| Transmission:\n");
	printf ("| \ttime %.15f s\n", packet->tx_time);
	printf ("| \tdelay %.15f s\n", packet->tx_delay);
	printf ("| Propagation: delay %.12f s\n", packet->prop_delay);
	printf ("| delivery time: %.12f s\n", packet->delivery_time);
	printf ("| Nb of collision(s): %d\n", packet->nb_collisions);
	printf ("+--------------------------------------------------------------\n");
	*/
	
	/*
	fprintf (fp_channel_debug, "\n+--------------------------------------------------------------\n");
	fprintf (fp_channel_debug, "| Packet %d, %.0f MHz\n", (int) packet->packet_id, packet->frequency); 
	fprintf (fp_channel_debug, "| Destination name: %s\n", dest_name);
	fprintf (fp_channel_debug, "| delivery time: %.12f s\n", packet->delivery_time);
	fprintf (fp_channel_debug, "| Nb of collision(s): %d\n", packet->nb_collisions);
	fprintf (fp_channel_debug, "+--------------------------------------------------------------\n");
	*/
	
	FOUT;
}
