typedef struct Lot {
	char url[200];
	int number;
	char name[100];
	char description[1000];
	int hi_bid; // figure out some nice way of getting rid of it and all its references
} Lot;

void print(Lot l) {
	printf("\n >>>>>>>>>> >>>>>>>>>> >>>>>>>>>> >>>>>>>>>> >>>>>>>>>>\n");
	printf("Lot #%d: %s\n", l.number, l.name);
	printf("currently at $%d\n", l.hi_bid);
	printf("\nDescription:\n%s\n", l.description);
	printf("\n");
}
