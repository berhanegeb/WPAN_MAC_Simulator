MIL_3_Tfile_Hdr_ 150A 150A modeler 6 4CB8509C 50DD8DA2 9 s-cwc-pc204 bgebreme 0 0 none none 0 0 none 5FE1F27B 1A7B 0 0 0 0 0 0 21b7 3                                                                                                                                                                                                                                                                                                                                                                                           ��g�      <   @   Z  �  �  
�    B  D  L  P  '  7       Pulse����������������       General Description:    --------------------        �This device implement the MAC layer of the Low Rate WPAN according to the IEEE 802.15.4. The source type implements here is a basic simple source.       �The node "wpan_channel", which is the basic channel implements for the WPAN,  is required in the topology so that the simulation will work properly.             #WPAN MAC ParametersAcknowledgement      MAC.Acknowledgement����   ����           ����          ����          ����                         WPAN MAC ParametersChannel      MAC.Channel����    ����           ����          ����          ����                        "WPAN MAC ParametersChannel Access      MAC.Channel Access����   ����           ����          ����          ����                         Packet sourceGroup Number      MAC.Group number   source.Group number����    ����           ����          ����          ����                         %Packet sourceMAC Address Destination      source.Mac Address Destination����    ����           ����          ����          ����                         WPAN MAC ParametersMAC address      MAC.Address����    ����           ����          ����          ����                        WPAN MAC ParametersMode      MAC.Mode����   ����           ����          ����          ����                         .WPAN MAC ParametersNb of transmission retries      MAC.Nb of transmission retries����    ����           ����          ����          ����                        &Packet sourcePacket Interarrival Time      source.Packet Interarrival Time����   ����       ����      ����      ����                        Packet sourcePacket Size      source.Packet Size����   ����       ����      ����      ����                        WPAN MAC ParametersPower      	MAC.Power����   ����               ����              ����              ����                         !Packet sourcePredefined Profiles      source.Predefined Profiles����    ����           ����          ����          ����                        Packet sourceStart Time      source.Start Time����   ����               ����              ����              ����                        Packet sourceStart time shift      source.Start time shift����   ����               ����              ����              ����                        Packet sourceStop Time      source.Stop Time����   ����               ����              ����              ����                        Acknowledgement               Enabled      Channel                
channel 11      Channel Access                	Unslotted      Group Number              ����      MAC Address Destination          ����   Round Robin      MAC address          ����   Auto assigned      Mode               Slave      Nb of transmission retries                3      Packet Interarrival Time            constant (1.0)      Packet Size            constant (1024)      Power         ?�      ����      Predefined Profiles          ����   None      
Start Time         
        ����   
   Start time shift                    None      	Stop Time         ��         Infinity      
TIM source            none      altitude                 ����      altitude modeling            relative to subnet-platform      	condition            ����      financial cost            0.00      minimized icon            circle/#708090      phase                 ����      priority              ����      role         ����      user id              ����                �   >          
   source   
       J   lr_wpan_source_UWB_LECIM_app   J          	processor                   Packet Interarrival Time   ���   	   constant (1.0)   	      Packet Size   ���   	   constant (1024)   	      
Start Time   ���   	@$         10.0   	      	Stop Time   ���   	��         Infinity   	          �   �          
   MAC   
       J   6WPAN_802_15_4a_MAC_PSMA_LECIM_and_Slotted_ALOHA_GADGET   J          	processor                   CSMA-CA Parameters   ���   
            count    ���   
   ����   
      list   	���   
            Maximum backoff number    ���   
      4   
      Minimum backoff exponent    ���   
      2   
   
   
      Power   ���   	?�      ����   	      Source Type   ���   
      	Bulk Data   
      Superframe parameters   ���   
            count    ���   
   ����   
      list   	���   
            Beacon order    ���   
   ����   
      Superframe order    ���   
   ����   
      Final CAP slot    ���   
   ����   
   
   
                      �   B   �   �   
       
   strm_0   
       
   src stream [0]   
       
   dest stream [0]   
          ����                  ����          
@  �����   
                                        nd_packet_stream                      �   �   �   ?   
       
   strm_1   
       
   src stream [0]   
       
   dest stream [0]   
          ����                  ����          
@�����   
                                        nd_packet_stream                                  
   shape_0   
       
    ����   
          ����          
@ UU����   
       
@c�     ����   
       
@f�     ����   
       
@e      ����   
       
@`�     ����   
          	annot_box             Annotation Palette          
?|{(����   
       ����                  ����       ����                 
   text_0   
       
      Low Rate WPAN MAC layer   
       
@ UU����   
          ����              ����          
@g      ����   
       
@m      ����   
       
@X�     ����   
       
@<      ����   
          
annot_text             Annotation Palette          
?|{A����   
       ����          
@�������   
               ����              ����           ����                T�I�%��}   @      @  �   @�  @4                                  