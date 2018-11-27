


int awardPoints(int);

/*
	int awardPoints(int sum)
	
	Based on the sum of the numbers in the player's 
	selected line, "sum", assigns the player a score. 
*/
int awardPoints(int sum) {
	int pointTable[] = {10000, 36, 720, 360, 80, 252, 
	108, 72, 54, 180, 72, 180, 119, 36, 306, 1080, 
	144, 1800, 3600};
	
	/*
	The payout table starts at 6, so its fine to just
	subtract six to get the value we want
	*/
	int award = pointTable[sum - 6];
	return award;
}