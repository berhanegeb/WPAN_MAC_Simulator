/*
** Physical_Layer.h :
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
** Secondary Author:	Nicolas Chevrollier
** Module description:  Physical Layer for Low Rate WPAN model
** Last Modification:   February, 4, 2004
*/

#ifndef __PHYSICAL_LAYER__
#define __PHYSICAL_LAYER__

/* include standards library */
#include <opnet.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lr_wpan_support_15_4a.h"

/* define some constant */
#define LN_10		2.302585
#define LN_2		0.693147
#define RATIO_TO_DB	4.342944 // 10 / ln(10)
#define	DB_TO_RATIO	0.230258 // ln(10) / 10
#define PI		3.141592
#define SQRT_2PI	2.506628 // square root of 2*pi
#define INFINITY_FREQ	10000.0
#define SIGNAL_MARGIN	10.0
#define IMPLEMENTATION_LOSS -5.0	//in dB, to match AWGN SNR with analysis.


/* define some macros */
/* 
 * return -1^k for integer k.  In other words,
 * return 1.0 if k is even, -1.0 if k is odd 
 */
#define MINUS1EXP(k)	(((k&1)==0)?1.0:-1.0)

/* Define a new type for the 802.11b rates */
typedef enum {
  WLAN_MBPS_11,
  WLAN_MBPS_5_5,
  WLAN_MBPS_2,
  WLAN_MBPS_1
} Wlan_Rate;

typedef enum {
	AWGN_15_4A,
	NAKAGAMI_15_4A
} Channel_Model;

/* function prototypes */

/* Util functions: file Util.ex.c */
double	util_dB (double ratio);
double	util_inverse_dB (double dB);
double path_loss_attenuation (double separation, double frequency);

/* Binomial functions: file Binomial.ex.c */
double	binomial_factorial (int m);
int	binomial_choose (int m, int j);

/* Bit Error Rate function: file BER.ex.c */
double bit_error_rate_802_15_4 (double sirDB);
double bit_error_rate_802_11b (double sirDB, Wlan_Rate fRate);
double bit_error_rate_802_15_4a (double sirDB, Channel_Model Channel);

/* Qerf function: file Qerf.ex.c */
double qerf_lerp (double x);
double qerf_Q (double x);

/* Coexistence functions: file Coexistence.ex.c */
double coexistence_ri(Wpan_Pkt_Type receiver_type, double receiver_freq, double t_power, double t_distance, 
	Wpan_Pkt_Type interferer_type, double interferer_freq, double i_power, double i_distance);

double coexistence_15d4r_11bi (double receiver_freq, double t_power, double t_distance,
			       double interferer_freq, double i_power, double i_distance);
double coexistence_15d4ri (double receiver_freq, double t_power, double t_distance,
			       double interferer_freq, double i_power, double i_distance);

double coexistence_11br_15d4i (double receiver_freq,	double t_power, double t_distance, Wlan_Rate receiver_rate, 
	double interferer_freq, double i_power, double i_distance);
double coexistence_11bri( double receiver_freq,	double t_power, double t_distance, Wlan_Rate receiver_rate, 
	double interferer_freq, double i_power, double i_distance);


double coexistence_coupling_15d4r_11bi (double Receiver_Freq, double Interferer_Freq);
double coexistence_coupling_15d4ri (double Receiver_Freq, double Interferer_Freq);

double coexistence_coupling_11br_15d4i (double Receiver_Freq, double Interferer_Freq);
double coexistence_coupling_11bri (double Receiver_Freq, double Interferer_Freq);
double snr_15_4a (double receiver_freq, double t_power, double t_distance);

/* Spectrum functions: file Spectrum.ex.c */
void	spectrum_multiply (double ispectrum[][2], int isize, double rspectrum[][2], int rsize, double (*prod_spectrum)[][2]);
double	spectrum_find_gain_at (double frequency, double spectrum[][2], int size);
double	spectrum_lerp (double x, double x0, double x1, double y0, double y1);
double	spectrum_area (double spectrum[][2], int size);
double	spectrum_db_trapezoid (double d0, double d1, double width);
void	spectrum_sort (double (*spectrum)[][2], int size);
void	spectrum_display (double spectrum[][2], int size);



#endif /* end of __PHYSICAL_LAYER__ */
