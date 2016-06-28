#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <signal.h>
#include <time.h>
#include <sys/time.h>

#include "myBigChars.h"
#include "myTerm.h"
#include "read_key.h"
#include "ui.h"
#include "mySimpleComputer.h"
#include "u_io.h"
#include "read_key.h"
#include "alu_cu.h"

int main()
{
    signal (SIGALRM, signalhandler);
    signal (SIGUSR1, reset);

    nval.it_interval.tv_sec  = 1;
    nval.it_interval.tv_usec = 0;
    nval.it_value.tv_sec  = 1;
    nval.it_value.tv_usec = 0;	
	
    sc_regInit();
    termInit();
    ax = 0x0;
    ip = 0x0;

    enum Keys key = K_UNKNOWN;
	
	displayBorders();
    displayUI();
    
    f_key = 0;
    f_ign = 0;
    
    while (key != K_Q) {
		
		readKey (&key);
		
		if (key == K_T) {
			sc_regSet(IR, 0);
			alarm(0); 
			f_key = 0;
			cu();
		}
		
		if (!f_key) {
			if (key == K_R    )  {
				sc_regSet(IR, 1);
				sc_regSet(IF, 0);
			}
			
			sc_regGet(IR, &f_key);
			
			if (f_key) {
				timerStart();        
			}
			
			if (key == K_F5   ) user_input_ax();
			if (key == K_F6   ) user_input_ip();
			if (key == K_RIGHT) if (mem_ptr < 99) ++mem_ptr;
			if (key == K_LEFT ) if (mem_ptr >  0) --mem_ptr;
			if (key == K_UP   ) if (mem_ptr - 10 >=  0) mem_ptr -= 10;
			if (key == K_DOWN ) if (mem_ptr + 10 < 100) mem_ptr += 10;
			if (key == K_L	  ) sc_memoryLoad("memory.o");
			if (key == K_S	  ) sc_memorySave("memory.o");
			if (key == K_E	  ) user_input_mem(); 
			if (key == K_I) {
				displayBorders();
				displayUI();
				sc_memoryInit();
				sc_regInit();
			}
			displayUI ();
		}
		
	}
    
	return 0;
}
