#include <AT89X51.H>
//Include file for 8051
#define keyport P0	//keypad connected to P2
#define col1 P0_0	//column 1
#define col2 P0_1	//column 2
#define col3 P0_2	//column 3
#define col4 P0_3	//column 4

#define row1 P0_4	//ligne 1
#define row2 P0_5	//ligne 2
#define row3 P0_6	//ligne 3
#define row4 P0_7	//ligne 4

#define TRUE 1		//some defines
#define FALSE 0
const char a[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};

/*
+---------------------------------------+
| Prototype: void key_init(void);       |
| Return Type: void                     |
| Arguments: None                       |
| Description: Initialize ports and     |
|              Keypad.                  |
+---------------------------------------+
*/
void key_init(){
	keyport &=0x0F;	//make Rows as o/p and cols are i/p
}
 
/*
+-----------------------------------------------+
| Prototype: unsigned char get_key(void);       |
| Return Type: unsigned char                    |
| Arguments: None                               |
| Description: To read key from the keypad      |
+-----------------------------------------------+
*/
unsigned char get_key(){
	unsigned char i,k,key=0;
	
	k=0;
			
	for(i=0;i<5;i++){		//loop for 4 rows
		keyport &=~(0x80>>i);	//to make rows low 1 by 1
		if(i==0) {
				if(!col1){	//check if key1 is pressed
					return (-1);	//return key number
				}
				if(!col2){	//check if key2 is pressed
					key = k+0;	//set key number
					while(!col2);	//wait for release
					return key;	//return key number
				}
				if(!col3){	//check if key3 is pressed
					return (-1);	//return key number
				}
				
				k+=1;
			}
			
		else {
			if(!col1){	//check if key1 is pressed
				key = k+0;	//set key number
				while(!col1);	//wait for release
				return key;	//return key number
			}
			if(!col2){	//check if key2 is pressed
				key = k+1;	//set key number
				while(!col2);	//wait for release
				return key;	//return key number
			}
			if(!col3){	//check if key3 is pressed
				key = k+2;	//set key number
				while(!col3);	//wait for release
				return key;	//return key number
			}
			
		k+=3;	
		
		}
		keyport |= 0x80>>i;	//make the row high again
}
	return (-1);			//return false if no key pressed
}

void main(void){
    unsigned char key,de,un;
		unsigned int compteur=0;
		
    key_init();
    while (1) {
        key = get_key();
			
if(key!=(-1)) {
	if(compteur%2==0)	P1=a[key];
	if(compteur%2==1)	P3=a[key];

	compteur++;
}			

        }

}