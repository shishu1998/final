typedef struct Lot {
	char url[200];
	int number;
	char name[100];
	char description[1000];
	int hi_bid;
} Lot;

//extern Lot *pcurr_lot;

void print(Lot l) {
	printf("\nLot #%d: %s\n", l.number, l.name);
	printf("currently at $%d\n", l.hi_bid);
	printf("\nDescription:\n%s\n", l.description);
	printf("\n");
}
