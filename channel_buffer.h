/*
** channel_buffer.h :
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
** Module description:  Channel Buffer for Low Rate WPAN model
** Last Modification:   October, 23, 2003
*/

#ifndef __CHANNEL_BUFFER_H__
#define __CHANNEL_BUFFER_H__

/* standard includes */
#include <opnet.h>
#include "lr_wpan_support_15_4a.h"

/* declare the buffer structure */
typedef struct T_buffer {
  OpT_Packet_Id		packet_id; // Packet ID
  Wpan_Pkt_Type		packet_type; // type of packet
  double			packet_size; // size of packet
  double 			power; // TX power
  double			tx_x;	// coordinates of
  double			tx_y;	// the transmitter
  double			rx_x;	// coordinates of
  double			rx_y;	// the receiver
  double			txrx_distance; // distance between TX and RX
  Objid				dest_objid; // objid of the destination module of the packet
  Objid				src_objid; // objid of the source module of the packet
  double 			tx_time; // transmission time of the packet
  double			tx_delay; // transmission delay
  double			prop_delay; // propagation delay
  double			delivery_time; // delivery time for the packet (= tx_time + tx_delay + prop_delay)
  double			frequency; // Transmission frequency
  int				nb_collisions; // number of collisions
  Boolean			noise;// categorize the packet as noise (true) or valid (false)
  struct T_buffer *	next_packet;
  struct T_buffer *	next_collision;
} Buff_Info_Packet;

/* declare the first cell */
Buff_Info_Packet * channel_buffer_ptr;

/* function prototypes */
void				channel_buffer_error (char * fcnt, char * msg, char * opt);
void 				channel_buffer_register_packet (Buff_Info_Packet * packet);
void 				channel_buffer_remove_packet (Buff_Info_Packet * packet);
Buff_Info_Packet *	channel_buffer_search_by_id (int packet_id);
Buff_Info_Packet *	create_info_packet_cell (void);
void 				channel_buffer_register_collision (Buff_Info_Packet * current_packet, Buff_Info_Packet * packet_to_register);
Buff_Info_Packet * 	copy_packet_info_cell (Buff_Info_Packet * packet);
Buff_Info_Packet *	search_pkt_info_for_delivery (void);
void 				chan_buffer_print_info_pkt (Buff_Info_Packet * packet);


#endif /* end of __CHANNEL_BUFFER_H__ */
