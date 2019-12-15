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
char bits1[CHAR_BIT + 1];
char bits2[CHAR_BIT + 1];
char bits3[CHAR_BIT + 1];
unsigned char bitreg1;
unsigned char bitreg2;
unsigned char bitreg3;

//http://opengarages.org/index.php/Mazda_CAN_ID
//https://wiki.openstreetmap.org/wiki/VW-CAN

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
	
printf("\033[1;36m");
    printf("**********************************************************************************\n");
    printf("*                           PowerTune UDP Daemon for                             *\n");
    printf("*                                    Audi B7                                     *\n");
    printf("*                                  Version 0.2                                   *\n");
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

	addr.can_family  = AF_CAN;
	addr.can_ifindex = 0;

	if(bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Error in socket bind");
		return -2;
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
		case 0x280:
                sprintf(data_str[0],"179,%f",data[1]*0.25);          							//RPM
            break;
		case 0x320:
				sprintf(data_str[0],"191,%d",(unsigned short)frame.data[2]);          			//Fuel Level %? or Liters ?
                sprintf(data_str[1],"199,%f",(unsigned short)frame.data[4]);          			//Speed
            break;

		case 0x4A0:
                sprintf(data_str[0],"224,%f",data[0]*0.01);							        //Wheel Speed left front
                sprintf(data_str[1],"225,%f",data[1]*0.01);              					//Wheel Speed right front
                sprintf(data_str[2],"226,%f",data[2]*0.01);          						//Wheel Speed left rear
                sprintf(data_str[3],"227,%f",data[3]*0.01);  								//Wheel Speed right rear
            break;	
		case 0x420:
                sprintf(data_str[0],"170,%f",((unsigned short)frame.data[3]-64)*0.75);		//Oil Temp
                sprintf(data_str[1],"221,%f",((unsigned short)frame.data[4]-64)*0.75);      //Coolant Temp

            break;
		case 0x5A0:
                sprintf(data_str[0],"3,%f",((unsigned short)frame.data[0]-127)*0.01);		//Lateral Acceleration

            break;	
		default:
        	break;
		    }
	    for(int k=0;k<messages;k++)
	    {
	    	int retbytes = sendto(sockfd, data_str[k], strlen(data_str[k]) , 0, (struct sockaddr *)&dst_addr, sizeof dst_addr);
	        if(retbytes == -1)
		    {
	       		printf("UDP send pkt fail");
	       		exit(-1);
	       }
	    }
    }
	return 0;
}
