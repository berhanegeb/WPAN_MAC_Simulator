/*
** Util.ex.c :
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
** Module description:  Physical Layer for Low Rate WPAN model
** Last Modification:   January, 21, 2004
*/

/* include the header */
#include "Physical_Layer.h"

/* 
 * function:	util_dB
 *
 * Description:	Given a power ratio, return decibels.
 *
 * ParamIn:	double ratio
 *		power ratio
 *
 * ParamOut:	double dB
 *		power in decibels
 */

double	util_dB (double ratio)
{
  double dB;

  FIN (util_db (ratio));

  /* compute the power in dB */
  dB = log (ratio) * RATIO_TO_DB;

  FRET (dB);
}

/* 
 * function:	util_inverse_dB
 *
 * Description:	Given decibels, return a power ratio.
 *
 * ParamIn:	double dB
 *		power in decibels
 *
 * ParamOut:	double ratio
 *		power ratio
 */

double	util_inverse_dB (double dB)
{
  double ratio;

  FIN (util_inverse_dB (dB));

  /* compute the power ratio */
  ratio = exp (dB * DB_TO_RATIO);

  FRET (ratio);
}


/*
 * Function:	path_loss_attenuation
 *
 * Description:	Given a separation in meters, return the attenuation in dB due
 *		to path loss.  Attenuation is d^-2 when d is less than 8
 *		meters, d^-3.3 otherwise. (reference: pag 161 IEEE 802.15.4a)
 *
 * ParamIn:	double separation
 *		separation beetween the receiver and the interferer in meter
 *
 *          double frequency
 *      center frequency
 *
 * ParamOut:	double pathloss
 *		attenuation in dB due to path loss
 */

double path_loss_attenuation (double separation, double frequency)
{
  double pathloss = 0.0;
  double gamma1 = 2.0;
  double gamma8 = 3.3;

  FIN (path_loss_attenuation (separation, frequency));

  if (separation <= 8.0)
    pathloss = gamma1*util_dB (4.0*PI*frequency*separation/LIGHT_SPEED);
  else if (separation > 8.0)
    pathloss = gamma1*util_dB (4.0*PI*frequency*8/LIGHT_SPEED) + gamma8 * util_dB (separation/8.0);

  FRET (pathloss);
}
