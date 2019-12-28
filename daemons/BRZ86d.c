// Acceleration in G  (float) msg->vcds_y.y_accel*0.00012742 - 4.1768;
// Yaw rate (degrees per second) *0.005 - 163.84),

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <net/if.h>
#include <fcntl.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>


#define MAX_DATA_LEN 8
#define MAX_FIELDS 23
#define MAX_FIELD_LEN 64
#include <limits.h>

#define COLOR_RESET "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

char data_str[MAX_FIELDS][MAX_FIELD_LEN];
//Bit Flags 
int i;
int s; /* can raw socket */ 
char bits1[CHAR_BIT + 1];
char bits2[CHAR_BIT + 1];
char bits3[CHAR_BIT + 1];
unsigned char bitreg1;
unsigned char bitreg2;
unsigned char bitreg3;
int message1 = 0;
int message2 = 0;
int message3 = 0;
int message4 = 0;
int message5 = 0;
int message6 = 0;
int message7 = 0;
int message8 = 0;
int message9 = 0;
int message10 = 0;
int message11 = 0;
int message12 = 0;
int message13 = 0;
int
main(void)
{
	int messages; // determines how many messages will be sent 
	int s;
	int nbytes;
	struct sockaddr_can addr;
	struct can_frame frame;
	unsigned short data[MAX_FIELDS];
	int sockfd=0;
	int bcast=1;
	struct sockaddr_in src_addr;
	struct sockaddr_in dst_addr;
	int numbytes;
	int16_t word;
	const char *ifname = "can0";
	
printf("\033[1;36m");
    printf("**********************************************************************************\n");
    printf("*                           PowerTune UDP Daemon for                             *\n");
    printf("*                      Subaru BRZ / Toyota 86 /Scion FRS                         *\n");
    printf("*                                  Version 1.5a                                  *\n");
    printf("*                              © 2019 Markus Ippy                                *\n");
    printf("*                                                                                *\n");
    printf("*                    THIS SOFTWARE IS PROVIDED BY THE AUTHOR                     *\n");
    printf("* ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,INCLUDING, BUT NOT LIMITED TO, *\n");
    printf("* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE *\n");
    printf("* ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,         *\n");
    printf("* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES             *\n");
    printf("* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;   *\n");
    printf("* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND    *\n");
    printf("* ON ANY THEORY OF LIABILITY,WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT      *\n");
    printf("* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS  *\n");
    printf("* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                   *\n");                               
    printf("*              Use of this software is strictly for PowerTune.                   *\n");
    printf("* The distribution and sale of this Software is exclusive to the copyright       *\n");
    printf("*                        owner and his affilliates.                              *\n");
    printf("*      To purchase a legal copy ,please email Markus.Ippy1981@gmail.com          *\n");
    printf("**********************************************************************************\n");	
printf("\033[0m");	

//Licence Key Validation start
	// Read the MAC adress of the Network adapter (for the Licence mechanism)
    int fa;
    struct ifreq ifr;
    
    fa = socket(AF_INET, SOCK_DGRAM, 0);
    
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, "eth0", IFNAMSIZ-1);
    
    ioctl(fa, SIOCGIFHWADDR, &ifr);
    close(fa);
 
	FILE *fp_lic= NULL; //Licence request file
	unsigned char LICENCE[100]; // Holds all values of the Licence read from file
	char line[100];
	int itemsread = 0;
	 fp_lic = fopen ("Licence.lic","r+");//Open Licence file
     char *token2;
	 //This logic will parse  '-' seperated values into buffer
	if(fp_lic != NULL)
	{
		while(fgets(line,sizeof(line),fp_lic) != NULL)
		{
			token2 = strtok(line, "-");
			while(token2 != NULL)
			{
				char *endptr;
				LICENCE[itemsread] = ("%.2x",strtoimax(token2,&endptr,0));
				itemsread++;
				token2 = strtok(NULL,"-");
			}
		}

	} 
		fclose(fp_lic);
		if(LICENCE[3] == (unsigned char)ifr.ifr_hwaddr.sa_data[0] && LICENCE[4] == (unsigned char)ifr.ifr_hwaddr.sa_data[1] && LICENCE[14] == (unsigned char)ifr.ifr_hwaddr.sa_data[2] && LICENCE[8] == (unsigned char)ifr.ifr_hwaddr.sa_data[3] && LICENCE[10] == (unsigned char)ifr.ifr_hwaddr.sa_data[4] && LICENCE[12] == (unsigned char)ifr.ifr_hwaddr.sa_data[5])
		{printf(GREEN"Licence Key validated \n");}
		else{
		printf(RED"Licence Key Invalid\n");
		exit(1);
		}
//Licence Key Validation End
	
	//
	if((sockfd = socket(PF_INET,SOCK_DGRAM,0)) == -1)
	{
		perror("Udp sockfd create failed");
		exit(1);
	}
	//Enabled broadcast mode for udp
	if((setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,
				&bcast,sizeof bcast)) == -1)
	{
		perror("setsockopt failed for broadcast mode ");
		exit(1);
	}
	src_addr.sin_family = AF_INET;
	src_addr.sin_port = htons(8888);
	src_addr.sin_addr.s_addr = INADDR_ANY;
	memset(src_addr.sin_zero,'\0',sizeof src_addr.sin_zero);

	if(bind(sockfd, (struct sockaddr*) &src_addr, sizeof src_addr) == -1)
	{
		perror("bind");
		exit(1);
	}

	dst_addr.sin_family = AF_INET;
	dst_addr.sin_port = htons(45454);
	dst_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(dst_addr.sin_zero,'\0',sizeof dst_addr.sin_zero);



	if((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		perror("Error while opening socket");
		return -1;
	}
	strcpy(ifr.ifr_name, ifname);
	ioctl(s, SIOCGIFINDEX, &ifr);
	addr.can_family  = AF_CAN;
	//addr.can_ifindex = 0;
	addr.can_ifindex = ifr.ifr_ifindex;

	if(bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Error in socket bind");
		return -2;
	}
	//Sends the decoded can message via UDP to PowerTune
	void send()
	{
		for(int k=0;k<messages;k++)	
			{
 
				//printf("%d seconds have passed\n", i + 1); 
				//printf(GREEN"%s\n", data_str[k]);
				int retbytes = sendto(sockfd, data_str[k], strlen(data_str[k]) , 0, (struct sockaddr *)&dst_addr, sizeof dst_addr);
				if(retbytes == -1)
				{
					printf("UDP send pkt fail");
					exit(-1);
			   }
			}	
	}

void clearScreen()
{
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}
	//struct can_frame frame;
    while(1)
    {
	    nbytes = read(s, &frame, sizeof(struct can_frame));

	    if (nbytes < 0) {
	            perror("can raw socket read");
	            return 1;
	    }

	    /* paranoid check ... */
	    if (nbytes < sizeof(struct can_frame)) {
	            fprintf(stderr, "read: incomplete CAN frame\n");
	            return 1;
	    }	

		//Structure the frame Data (Little Endian)
		data[0] = (unsigned short)frame.data[1]*256 + ((unsigned short)frame.data[0]);
		data[1] = (unsigned short)frame.data[3]*256 + ((unsigned short)frame.data[2]);
		data[2] = (unsigned short)frame.data[5]*256 + ((unsigned short)frame.data[4]);
		data[3] = (unsigned short)frame.data[7]*256 + ((unsigned short)frame.data[6]);
	    messages = 4; // by default we have 4 messages to be sent 	
		//printf("GREEN %d \n",frame.can_id);
	    switch(frame.can_id)
	    {
			case 0x7E8: //Decode OBD PIDS
					switch(frame.data[1])
						{
						case 0x01:		 //OBD Mode 1 standard PIDS
							switch(frame.data[2])
							{						
							case 0x42:
								messages = 1;
								sprintf(data_str[0],"228,%.2f",((unsigned short)frame.data[3]*256 + ((unsigned short)frame.data[4]))*0.001);		//Battery Voltage
								send();
							break;
							
							default:
							break;
							}
						case 0x21:		 //OBD Mode 21 special PIDS
							switch(frame.data[2])
							{						
							case 0x29:
								messages = 1;
								sprintf(data_str[0],"191,%.2f",((unsigned short)frame.data[3]*0.5));		//Fuel Level in Liters 
								send();
							break;
							
							default:
							break;
							}	
		
						default:
							break;				
						}
// Messages at 0.4Hz		
			case 0x6E1:
				//Request Supported PID's
				frame.can_id=0x7DF;
				frame.can_dlc=8;
				frame.data[0]=0x02; frame.data[1]=0x01; frame.data[2]=0x00; frame.data[3]=0x00; frame.data[4]=0x00; frame.data[5]=0x00; frame.data[6]=0x00; frame.data[7]=0x00;
				nbytes = write(s, &frame, sizeof(struct can_frame));
				//send();			
			break;	
			case 0x6E2:
				//Request Fuel Level via OBD mode 2 
				frame.can_id=0x7C0;
				frame.can_dlc=8;
				frame.data[0]=0x02; frame.data[1]=0x21; frame.data[2]=0x29; frame.data[3]=0x00; frame.data[4]=0x00; frame.data[5]=0x00; frame.data[6]=0x00; frame.data[7]=0x00;
				nbytes = write(s, &frame, sizeof(struct can_frame));
				//send();			
			break;	
// Messages at 1 Hz	
			case 0x374:
				//Request MAF Rate
				frame.can_id=0x7DF;
				frame.can_dlc=8;
				frame.data[0]=0x02; frame.data[1]=0x01; frame.data[2]=0x10; frame.data[3]=0x00; frame.data[4]=0x00; frame.data[5]=0x00; frame.data[6]=0x00; frame.data[7]=0x00;
				nbytes = write(s, &frame, sizeof(struct can_frame));		
			break;	
		case 0x375:
				//messages = 3;     
				//Request MAP
				frame.can_id=0x7DF;
				frame.can_dlc=8;
				frame.data[0]=0x02; frame.data[1]=0x01; frame.data[2]=0x0B; frame.data[3]=0x00; frame.data[4]=0x00; frame.data[5]=0x00; frame.data[6]=0x00; frame.data[7]=0x00;
				nbytes = write(s, &frame, sizeof(struct can_frame));
				// Byte 0 door lock state (bitflags)
				// Byte 1 door closed status
				//send();
			break;	
			case 0x37A:
				//Request Supported PIDS
				frame.can_id=0x7DF;
				frame.can_dlc=8;
				frame.data[0]=0x02; frame.data[1]=0x01; frame.data[2]=0x42; frame.data[3]=0x00; frame.data[4]=0x00; frame.data[5]=0x00; frame.data[6]=0x00; frame.data[7]=0x00;
				nbytes = write(s, &frame, sizeof(struct can_frame));		
			break;	
			case 0x4C1:
				send();			
			break;	
			case 0x4C3:
				send();			
			break;	
			case 0x4C6:
				send();			
			break;
			case 0x4C8:
				send();			
			break;	
			case 0x4DC:
				send();			
			break;		
			case 0x4DD:
				send();			
			break;				
// Messages at 2 Hz			
			case 0x63B:
				send();			
			break;
//Messages at 2.5 Hz			
			case 0x440:
				send();			
			break;	
			case 0x442:
				send();			
			break;				
			case 0x44D:
				send();			
			break;	
			case 0x46C:
				send();			
			break;	
//Messages at 10Hz		
			case 0x284:
				send();			
			break;	
			case 0x372:
				send();			
			break;	
//Messages at 16.7 Hz 
			case 0x282:
				send();			
			break;	
//Messages at 20 Hz
		case 0x360:	
				messages = 3;
                sprintf(data_str[0],"170,%d",(unsigned short)frame.data[2]-40);			    									//Oil Temp
                sprintf(data_str[1],"221,%d",(unsigned short)frame.data[3]-40);             									//Coolant Temp
				sprintf(data_str[3],"219,%d",2);																				//Set Toyota Ecu for Logging in PowerTune
				send();
            break;
		case 0x361:
				messages = 3;
				//sprintf(data_str[0],"170,%d",(unsigned short)frame.data[0]);													//Gear
				//printf("Gear %d \n",frame.data[1]);
				send();
            break;	
		case 0x370: //Power Steering

				messages = 1;    
				//sprintf(data_str[0],"9,%d",frame.data[0]); 																	//Seems to be Steering force format unclear
					
/*
    Byte 0: Changes when I turn the wheel. 0xFF when not working
    Byte 1 & 2: Zero when working 0xFF when not working.
    Byte 3 & 4: Current in Amps?
    Byte 5: Message Counter
    Byte 6 & 7: Zero 
*/				
				send();
            break;
//Messages at 50 Hz			
		case 0x144:
				message1 ++;
				if (message1 == 3)
				{
				message1 = 0;
				messages = 0;
				//sprintf(data_str[0],"9,%d",(unsigned short)frame.data[2]);											//Increases and decreases with RPM (even stationary) , might be MAF Sensor 
				send();
				}
			break;
		case 0x152:
		message2 ++;
				if (message2 == 3)
				{
				message2 = 0;
				messages = 17;
				//Byte 6 flags ( Handbrake- 0x08) 
                //Byte 7 Bitflags for stalks ?
				//Convert Byte 1 to binary bitflags
					
 			 bitreg2 = frame.data[6];
                for (i = CHAR_BIT - 1; i >= 0; i -= 1)
			{
				bits2[i] = '0' + (bitreg2 & 0x01);
				bitreg2 >>= 1;
			}
				bits2[CHAR_BIT] = 0;
//	        	 sprintf(data_str[1],"49,%d",bits2[0]-48);               //Flag 1
//      	     sprintf(data_str[2],"50,%d",bits2[1]-48);              //Flag 2
//  	         sprintf(data_str[3],"51,%d",bits2[2]-48);              //Flag 3
// 	             sprintf(data_str[4],"52,%d",bits2[3]-48);              //Flag 4
                 sprintf(data_str[5],"177,%d",bits2[4]-48);              //Handbrake confirmed 
//	    		 sprintf(data_str[6],"54,%d",bits2[5]-48);              //Flag 6
//				 sprintf(data_str[7],"55,%d",bits2[6]-48);              //Flag 7
//				 sprintf(data_str[8],"56,%d",bits2[7]-48);              //Flag 8
 
			 bitreg3 = frame.data[7];
                for (i = CHAR_BIT - 1; i >= 0; i -= 1)
			{
				bits3[i] = '0' + (bitreg3 & 0x01);
				bitreg3 >>= 1;
			}
				bits3[CHAR_BIT] = 0;

		//		 sprintf(data_str[9],"49,%d",bits2[0]-48);               // ???
        //       sprintf(data_str[10],"50,%d",bits2[1]-48);              //Wiper
                 sprintf(data_str[11],"178,%d",bits2[2]-48);              //Indicator R
                 sprintf(data_str[12],"150,%d",bits2[3]-48);              //Indicator L
                 sprintf(data_str[13],"118,%d",bits2[4]-48);              //High Beam
				 sprintf(data_str[14],"287,%d",bits2[5]-48);              //Low Beam
		//		 sprintf(data_str[15],"55,%d",bits2[6]-48);              //??
		//		 sprintf(data_str[16],"56,%d",bits2[7]-48);              //??

				send();
				}
            break;				
			case 0x156:
				message3 ++;
				if (message3 == 3)
				{
				message3 = 0;
				send();	
				}				
			break;		
		case 0x280:
				message4 ++;
				if (message4 == 3)
				{
				message4 = 0;
				send();
				}				
			break;	
		case 0x0D0:
				message5 ++;
				if (message5 == 3)
				{
				message5 = 0;
				messages = 3;
				word = (frame.data[1] << 8) | (frame.data[0] & 0xff) ;
                sprintf(data_str[0],"194,%.0f",word*0.1);																		//Steering Wheel Angle in degrees
				//clearScreen();
				//word = (frame.data[3] << 8) | (frame.data[2] & 0xff) ;
				//printf(GREEN"Lat ?      %d \n",word);																			//Longitudinal  ACCELERatION?
				//sprintf(data_str[1],"9,%.2f",word*0.01);
				//word = (frame.data[7] << 8) | (frame.data[6] & 0xff) ;
				//printf(YELLOW"Long ? %.2f \n",word*0.01);
				//sprintf(data_str[2],"9,%.2f",word*0.01);																		// Yaw rate ?
				
				//BO_ 315 G_Sensor: 8 XXX
// SG_ longitudinal : 63|8@0- (1,0) [0|255] "" XXX
// SG_ Latitudinal : 48|8@1- (1,0) [0|255] "" XXX
				send();
				}
			break;	
		case 0x0D1:
				message6 ++;
				if (message6 == 3)
				{
				message6 = 0;
				messages = 2;
				sprintf(data_str[0],"199,%.0f",data[0]*0.05747);																//Overall Speed 
                sprintf(data_str[1],"26,%d",(unsigned short)frame.data[2]);														//Brake Pressure . Formula unknown
				send();
				}
			break;
		case 0x0D2:
			
				message7 ++;
				if (message7 == 3)
				{
				message7 = 0;
				send();
				}
			break;	
		case 0x0D3:
				message8 ++;
				if (message8 == 3)
				{
				message8 = 0;
				messages = 2;
		bitreg1 = frame.data[0];
                for (i = CHAR_BIT - 1; i >= 0; i -= 1)
			{
				bits1[i] = '0' + (bitreg1 & 0x01);
				bitreg1 >>= 1;
			}
				bits1[CHAR_BIT] = 0;
                sprintf(data_str[0],"290,%d",bits1[2]-48);                														//Traction control 
				//sprintf(data_str[1],"179,%d",((unsigned short)frame.data[3] & 63 )*256 + ((unsigned short)frame.data[2]));      //RPM
				send();
				}
			break;	
		
		case 0x0D4:
		message9 ++;
				if (message9 == 3)
				{
				message9 = 0;	
				messages = 4;
                sprintf(data_str[0],"224,%.0f",data[0]*0.05747);																//Wheel Speed left front
                sprintf(data_str[1],"225,%.0f",data[1]*0.05747);              													//Wheel Speed right front
                sprintf(data_str[2],"226,%.0f",data[2]*0.05747);          														//Wheel Speed left rear
                sprintf(data_str[3],"227,%.0f",data[3]*0.05747);  																//Wheel Speed right rear
				send();
				}
            break;					
// Messages at 100 Hz
		case 0x018:
		message10 ++;
				if (message10 == 4)
				{
				 message10 = 0;	
				 messages = 0;
				 send();
				}
            break;		
		case 0x140:
		message11 ++;
				if (message11 == 4)
				{
				message11 = 0;
				messages = 6;
				sprintf(data_str[0],"1,%.0f",(unsigned short)frame.data[0]*0.392157);											//Accelerator Pedal Position % 
				//sprintf(data_str[1],"1,%.0f",(unsigned short)frame.data[5]*0.392157);											//Throttle Body Position  %
				bitreg1 = frame.data[1];
                for (i = CHAR_BIT - 1; i >= 0; i -= 1)
			{
				bits1[i] = '0' + (bitreg1 & 0x01);
				bitreg1 >>= 1;
			}
				 bits1[CHAR_BIT] = 0;
                 sprintf(data_str[1],"27,%d",bits1[0]-48);              //Clutch Switch state
                 sprintf(data_str[2],"50,%d",bits1[1]-48);              //Flag 2
                 sprintf(data_str[3],"51,%d",bits1[2]-48);              //Flag 3
                 sprintf(data_str[4],"52,%d",bits1[3]-48);              //Flag 4

				sprintf(data_str[5],"179,%d",((unsigned short)frame.data[3] & 63 )*256 + ((unsigned short)frame.data[2]));      //RPM
				send();
				}
			break;;	
		case 0x141:
		message12 ++;
				if (message12 == 4)
				{
				message12 = 0;
				messages = 0;
				//sprintf(data_str[0],"179,%d",((unsigned short)frame.data[5] & 63 )*256 + ((unsigned short)frame.data[4]));      //RPM
				//sprintf(data_str[1],"228,%.2f",(unsigned short)frame.data[0]*0.1);											//Not Battery Voltage ?
				send();
				}
			break;		
		case 0x142:
		message13 ++;
				if (message13 == 3)
				{
				message13 = 0;
				messages = 0;
				//sprintf(data_str[0],"228,%.2f",(unsigned short)frame.data[0]*0.1);											//Not Battery Voltage ?
				send();
				}
			break;	
			
		default:
        	break;				
		    }
    }
	return 0;
}
/*
7DF#02010D0000000000
	frame.can_id  = 0x7DF;
	frame.can_dlc = 8;
	frame.data[0] = 0x02;
	frame.data[1] = 0x01;
	frame.data[2] = 0x0D;
	frame.data[3] = 0x00;
	frame.data[4] = 0x00;
	frame.data[5] = 0x00;
	frame.data[6] = 0x00;
	frame.data[7] = 0x00;
	nbytes = write(s, &frame, sizeof(struct can_frame));
*/