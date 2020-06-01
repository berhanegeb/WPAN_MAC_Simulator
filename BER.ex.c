/*
** BER.ex.c :
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
** Module description:  Physical Layer for Low Rate WPAN model
** Last Modification:   January, 21, 2005
*/

/* include the header */
#include "Physical_Layer.h"
#include "MODULATION_TABLES.h"

/*
 * Function:	bit_error_rate_802_15_4
 *
 * Description:	Given a Signal To Interference Ratio, return the bit error
 *				rate predicted for this receiver.  The ber() function should
 *				take into account the modulation scheme, processing gain and
 *				bits per symbol.
 *
 *				## This routine has been verified to match Paul Gorday's 
 *				## recommendations.  - rdp 6 Aug 2002
 *
 * ParamIn:		double sirDB
 *				Signal To Interference (dB)
 *
 * ParamOut:	double ber
 *				Bit Error rate
 */

double bit_error_rate_802_15_4 (double sirDB) 
{
  double EbN0, ber;
  double snr = util_inverse_dB (sirDB);

  //const int M = 2;
  //const double Rb = 850000;		// bit rate
  const double BW = 499.2e6;		// bandwidth
  const double Tint = 32.05e-9;		// Integration time (Np = 16, T = 2 ns)
  
  Modulation_Handle			modulation_table;
  double EbN0dB;

  FIN (bit_error_rate_802_15_4 (sirDB));
  
  EbN0 = snr + sqrt(snr*(snr+(Tint*BW))); 	//conversion from SNR to EbN0
  /*
  EsN0 = EbN0*log(M)/LN_2;	// conversion from bit to symbol
  sum = 0.0;
  for (k=2; k<=M; k++)
  sum += MINUS1EXP (k) * binomial_choose (M, k) * exp ((EsN0 / (double) k) - EsN0);
  
  ser = sum / (double) M;
  convert from symbol error rate (ser) to bit error rate (ber) 
  ber = ser*((double) M / 2.0)/((double) M - 1.0);
  printf("BER nel ber= %f\n", ber);
  */
  
  
  //Modulation_Handle			modulation_table;
  modulation_table = op_tbl_modulation_get ("CustomPPM");
  EbN0dB = util_dB (EbN0);
  ber = op_tbl_mod_ber (modulation_table, EbN0dB);
  //printf("BER nel ber= %f\n", ber); 
  

  FRET (ber);
}

/*
 * Function:	bit_error_rate_802_15_4a
 *
 * Description:	Given a Signal To Interference Ratio, return the bit error
 *				rate predicted for this receiver.  The ber() function 
 *				takes into account the modulation scheme.
 *
 *				## This routine has been verified with analytical results
 *				## Jussi Haapola. 01.11.2010
 *
 * ParamIn:		double sirDB
 *				Signal To Interference (dB)
 *				Channel_Model Channel
 *				channel model used (enumeration) 0: AWGN; 1: Nakagami
 *
 * ParamOut:	double ber
 *				Bit Error rate
 */

double bit_error_rate_802_15_4a (double sirDB, Channel_Model Channel)
{
	
	double ber;
	int location;

	FIN (bit_error_rate_802_15_4a(sirDB, Channel));
	
	if (sirDB <= -10.0)
		location = 0;
	else if (sirDB > 30.0)
			location = 400;
	else
		{
		if (sirDB >= 0.0)
			{
			if ((sirDB*10) - (int)(sirDB*10) < 0.5)
				location = (int)(sirDB*10)+99;
			else
				location = (int)(sirDB*10)+100;
			}
		else
			{
			if ((int)(sirDB*10) - (sirDB*10) < 0.5)
				location = (int)(99+(sirDB*10));
			else
				location = (int)(100+(sirDB*10));
			}
					
		}
	
	switch (Channel)
		{
    case AWGN_15_4A: //AWGN
    	ber = awgn_vector_802_15_4a[location];
    	break;

    case NAKAGAMI_15_4A: //Nakagami
		ber = nakagami_vector_802_15_4a[location];
		break;

    default :
		//use AWGN and report error
		ber = awgn_vector_802_15_4a[location];
		printf("unidentified channel model ar %f. Using AWGN\n", op_sim_time ());
      break;
		}
	//printf("BER.ex.c: SNRdB = %f, location = %d, BER = %f\n", snrdB, location, ber);
	
	FRET (ber);
}

/*
 * Function:	bit_error_rate_802_11b
 *
 * Description:	Given a Signal To Interference Ratio, return the bit error
 *				rate predicted for this receiver.  The ber() function should
 *				take into account the modulation scheme, processing gain and
 *				bits per symbol.
 *
 *				## Adapted from TG2 models.
 *
 * ParamIn:		double sirDB
 *				Signal To Interference (dB)
 *
 * ParamOut:	double ber
 *				Bit Error rate
 */

double bit_error_rate_802_11b (double sirDB, Wlan_Rate fRate)
{
  double sir = util_inverse_dB (sirDB);
  double ser, ber;
  int M;

  FIN (bit_error_rate_802_11b (sirDB, fRate));

  switch (fRate)
    {
    case WLAN_MBPS_1:
      M = 2;
      ser = qerf_Q (sqrt(11.0*sir));
      break;

    case WLAN_MBPS_2:
      M = 2;
      ser = qerf_Q (sqrt(5.5*2.0*sir/2.0));
      break;

    case WLAN_MBPS_5_5:
      M = 8;
      ser = 14.0*qerf_Q (sqrt(8.0*sir)) + qerf_Q (sqrt(16.0*sir));
      break;
    
    case WLAN_MBPS_11:
      M = 256;
      ser = 24.0*qerf_Q (sqrt(4.0*sir)) + 16.0*qerf_Q (sqrt(6.0*sir)) + 174.0*qerf_Q (sqrt(8.0*sir)) +
	16.0*qerf_Q (sqrt(10.0*sir)) + 24.0*qerf_Q (sqrt(12.0*sir)) + qerf_Q (sqrt(16.0*sir));
    }
  
  /* convert from symbol error rate (ser) to bit error rate (ber) */
  ber = ser * ((double) M / 2.0)/ ((double) M - 1.0);

  /* return the minimum beetween the ber value and 0.5 */
  ber = (ber < 0.5)?ber:0.5;

  FRET (ber);
} 
