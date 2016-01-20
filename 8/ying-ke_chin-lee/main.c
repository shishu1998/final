#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lot_struct.h"
#include "display.h"
#include "writing.h"

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

int main() {
	Lot lots[3];
	init_lots(lots);
	int i = 0;
	pcurr_lot = (Lot *)malloc(sizeof(Lot));
	pcurr_lot = &lots[i];
	print(*pcurr_lot);
	display(lots[0]);
	//free(pcurr_lot);
	return 0;
}
