#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lot_struct.h"
#include "display.h"

int BID_MODE = 0;
//#include "writing.h"

/*
	For testing out bits of code
	manually initialized bids.txt
*/

void init_lots(Lot *lots) {
	// hard-code a couple lots
	strcpy(lots[0].name, "The Scream");
	strcpy(lots[0].url, "http://pre04.deviantart.net/05eb/th/pre/f/2015/134/b/f/the_scream_minion_by_ying_min-d8tc8rf.jpg");
	strcpy(lots[0].description, "masterpiece by Munck");
	lots[0].number = 1;
	lots[0].hi_bid = 0;

	strcpy(lots[1].name, "The Scream");
	strcpy(lots[1].url, "http://pre04.deviantart.net/05eb/th/pre/f/2015/134/b/f/the_scream_minion_by_ying_min-d8tc8rf.jpg");
	strcpy(lots[1].description, "masterpiece by Munck");
	lots[1].number = 1;
	lots[1].hi_bid = 0;

	strcpy(lots[2].name, "The Scream");
	strcpy(lots[2].url, "http://pre04.deviantart.net/05eb/th/pre/f/2015/134/b/f/the_scream_minion_by_ying_min-d8tc8rf.jpg");
	strcpy(lots[2].description, "masterpiece by Munck");
	lots[2].number = 1;
	lots[2].hi_bid = 0;
}

int old_main() {
	// idea is so that I can't get a new PID every time...I want one bidder to have one paddle rather than having to open a new PID "paddle" every time
//	while (1) {
	Lot lots[3];
	init_lots(lots);
	int i = 0;
	Lot *pcurr_lot;
	pcurr_lot = (Lot *)malloc(sizeof(Lot));
	pcurr_lot = &lots[i];

	// deal with bidding ?/b/x
	printf("Enter ? to request information, b to bid, and x to exit.\n");
	printf("Action: ");
	char b[1];
	scanf("%s", b);
	if (strcmp(b, "?") == 0) {
		BID_MODE = 0;
		print(*pcurr_lot);
		display(lots[0]);
		//free(pcurr_lot);
	} else if (strcmp(b, "b") == 0) {
		BID_MODE = 1;
		printf("Bidmode = %d\n", BID_MODE);
	} else {
		BID_MODE = 0;
		if (strcmp(b, "x") == 0) printf("You chose to exit, exiting!\n");
		else printf("Invalid entry; exiting.\n");
		
		// tell server someone has left
/*
		// nah leave til later you have other problems lol
		char *buffer = "gone";
		portno = atoi(gettheportno);
		sockfd
*/
		exit(0);
	}
//	} //okay once I comment out the while loop, it doesn't let me enter a new bid but it doesn't hang.
	return 0;
}
