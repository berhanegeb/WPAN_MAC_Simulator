/*
** $File : lr_wpan_stat_write.ex.c
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
** Secondary Author:    N. Chevrollier
** Module description:  support file for writing statistics
** Last Modification:   November, 28th 2004
**
*/

/* include header */
#include "lr_wpan_stat_write.h"


/*
 * Function:	lr_wpan_stat_error
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

void lr_wpan_stat_error (const char * fcnt, const char * msg, const char * opt)
{
	FIN (static void lr_wpan_mac_error (fcnt, msg, opt));
	
	/* print error message and end the simulation */
	op_sim_end ("Low Rate WPAN Statistic:", fcnt, msg, opt);
	
	FOUT;
}


/*
 * Function:	lr_wpan_open_report_file
 *
 * Description:	open a file and return the file pointer
 *				to it.
 *
 * ParamIn:		const char * name
 *				total name of the file to open
 *
 *				Boolean * already_created
 *				if the file exists, this flag will be true,
 *				otherswise, it is false
 *
 * ParamOut:	FILE * fp
 *				file pointer
 */

FILE * lr_wpan_open_report_file (const char * name, Boolean * already_created)
{
	FILE * fp; // return value
	Boolean is_already_exists = OPC_FALSE;
	char * total_report_name;
	int total_report_name_size;
	const char * default_path = "C:\\Users\\bgebreme\\op_reports\\";
	char message[256];
	
	static char directory_path[256];
	static int directory_path_size = 0;
	
	
	FIN (lr_wpan_open_report_file (name, already_created));
		
	/* get the report directory path */
	if (directory_path_size == 0)
		{
		/* access the global attribute in the channel */
		//if (op_ima_sim_attr_get_str ("Directory Path", 256, directory_path) == OPC_COMPCODE_FAILURE)
		if (op_ima_obj_attr_get_str (wpan_channel_objid, "Report Path", 256, directory_path) == OPC_COMPCODE_FAILURE)
			{
			/* set the message to display */
			sprintf (message, "Path set to default: %s", default_path);
			
			/*printf ("Report Path: %s\n", directory_path);*/
			/* print the message */
			op_sim_message ("lr_wpan_open_report_file: Unable to read the report directory path.\nCheck if the WPAN Channel is present in the topology", message);
			
			/* set the path to default */
			strcpy (directory_path, default_path);
			}
		
		/* get the size of the string "directory_path" */
		directory_path_size = strlen (directory_path);
		}
	
	/* compute the size of the string "total_report_name" */
	total_report_name_size = directory_path_size + strlen (name) + 1;
	
	/* allocate memory and get the total report name */
	total_report_name = (char *) op_prg_mem_alloc (total_report_name_size * sizeof (char));
	sprintf (total_report_name, "%s%s", directory_path, name);
	/* printf ("total report name: %s\n", total_report_name);*/

		
	/* open the file in read mode */
	if ((fp = fopen (total_report_name, "r")) != NULL)
		{
		/* the file is already created */
		is_already_exists = OPC_TRUE;
		
		/* we close the file in order to open it again in "append" mode */
		fclose (fp);
		}
		
	if ((fp = fopen (total_report_name, "a")) == NULL)
		lr_wpan_stat_error ("lr_wpan_open_report_file:", "Unable to open or create the report file:", name);
	else if (ODB_STAT_WRITE)
		{
		/* printing information */
		printf ("+------------------------------------------------------\n");
		printf ("| Statistic Report Printing.\n");
		printf ("| \tLocation: %s\n", directory_path);
		printf ("| \tFile name: %s\n", name);
		printf ("| \t%s\n", is_already_exists ? "the file already exists: we append it" : "The file doesn't exist, we create it");
		printf ("+------------------------------------------------------\n");
		}
	
	/* update the flag in parameter */
	*already_created = is_already_exists;
	//printf("CHANNEL MODEL: %s\n", total_report_name);
	FRET (fp);
}


/*
 * Function:	integer_to_string
 *
 * Description:	convert an integer to a string with a
 *				number of character equal to max_size
 *
 * ParamIn:		int data
 *				integer to convert
 *
 *				int str_size
 *				number of character of the string
 *
 * ParamOut:	char * string
 *				string containing the integer
 */

char * integer_to_string (int integer, int str_size)
{
	char buffer[32];
	char * string;
	int size;
	int i; // loop variable
	
	FIN (integer_to_string (integer, str_size));
	
	/* get the data into the buffer */
	if (integer == -1)
		strcpy (buffer, "N/A");
	else
		sprintf (buffer, "%d", integer);
	
	if ((size = strlen(buffer)) >= str_size)
		{
		/* allocate the string */
		string = (char *) op_prg_mem_alloc ((size + 1) * sizeof (char));
		
		/* copy the buffer*/
		strcpy (string, buffer);
		}
	else
		{
		/* allocate the string */
		string = (char *) op_prg_mem_alloc ((str_size + 1) * sizeof (char));
		
		/* complete the first cell with a space */
		for (i=0; i< (str_size - size); i++)
			string[i] = ' ';
		
		string[i] = '\0';
		
		/* complete the string */
		if (integer == -1)
			strcat (string, "N/A");
		else
			sprintf (string, "%s%d", string, integer);
		}
	
	
	FRET (string);
}



/*
 * Function:	double_to_string
 *
 * Description:	convert a double to a string with a
 *				number of character equal to str_size
 *
 * ParamIn:		double a_double
 *				double to convert
 *
 *				int str_size
 *				number of character of the string
 *
 * ParamOut:	char * string
 *				string containing the integer
 */

char * double_to_string (double a_double, int str_size)
{
	char buffer[32];
	char * string;
	int size;
	int i; // loop variable
	
	FIN (double_to_string (a_double, str_size));
	
	/* get the data into the buffer */
	if (a_double == -1.0)
		strcpy (buffer, "N/A");
	else
		sprintf (buffer, "%.6f", a_double);
	
	if ((size = strlen(buffer)) >= str_size)
		{
		/* allocate the string */
		string = (char *) op_prg_mem_alloc ((size + 1) * sizeof (char));
		
		/* copy the buffer*/
		strcpy (string, buffer);
		}
	else
		{
		/* allocate the string */
		string = (char *) op_prg_mem_alloc ((str_size + 1) * sizeof (char));
		
		/* complete the first cell with a space */
		for (i=0; i< (str_size - size); i++)
			string[i] = ' ';
		
		string[i] = '\0';
		
		/* complete the string */
		if (a_double == -1.0)
			strcat (string, "N/A");
		else
			sprintf (string, "%s%.6f", string, a_double);
		}
	
	FRET (string);
}

/*
 * Function:	wlan_mac_collect_stat
 *
 * Description:	collect the statistic in the WLAN MAC Customized.
 *
 * ParamIn:		const WlanT_Mac_Stat wlan_stat
 *				vector of WLAN MAC Statistics
 *
 *				const char * wlan_name
 *				name of the WLAN node
 */

void wlan_mac_collect_stat (const WlanT_Mac_Stat wlan_stat, const char * wlan_name)
{
	FILE * fp;
	char report_name[64], date_str[32];
	time_t date;
	Boolean exist;
	
	
	FIN (wlan_mac_collect_stat ());
	
	/* get the date of the day */
	time (&date);
	sprintf (date_str, "%s", ctime (&date));
		
	/* start printing report */
	/* get the report name according to the RX/TX status */
	sprintf (report_name, "%s_mac.txt", wlan_name);
	
	/* open the file */
	fp = lr_wpan_open_report_file (report_name, &exist);
	
	if (!exist)
		{
		/* write a header in the file */
		fprintf (fp, "\t*** Packet received at the node %s ***\n", wlan_name);
		fprintf (fp, "\tCreation date: %s\n", date_str);
		fprintf (fp, "\tNumber of packets received\n");
		fprintf (fp, "\tNumber of packet lost\n");
		fprintf (fp, "\tNb of packet collided\n");
		fprintf (fp, "\tNb of bad packets\n");
		fprintf (fp, "\tSimulation time:\t\ttotal simulation time in seconds\n\n");
		fprintf (fp, "Packets received\t Packets lost\t packets collided\t bad packets\t Simulation time\t Last modified date\n");
		}
	
	/* write the statistics */
	fprintf (fp, "%s\t %s\t %s\t %s\t %s\t %s", integer_to_string (wlan_stat.packet_rcvd, strlen ("Packets received")),
		integer_to_string (wlan_stat.lost_packet, strlen ("Packets lost")),
		integer_to_string (wlan_stat.collided_packet, strlen ("packets collided")),
		integer_to_string (wlan_stat.bad_packet, strlen ("bad packets")),
		double_to_string (op_sim_time (), strlen ("Simulation time")),
		date_str);
	
	fclose (fp);
	
	FOUT;
}
