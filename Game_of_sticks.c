#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>


/*
Rules:
1., Each player takes one, two or three stick in turns
2., The player who takes the last stick loses the match
*/



bool check_validity(int sticks, int answer, bool isPlayerOne)
{
	if(answer > 3 || answer < 1)
	{
		if(isPlayerOne)
			printf("How many sticks do you want to take?(1,2,3)\n");
		return false;
	}

	if(sticks - answer < 0)
	{
		if(isPlayerOne)
			printf("You can't take that many.\n");
		return false;
	}

	return true;
}

int main() {
	srand(time(NULL));

	int sticks = 0;
	int mode = 0;
	int turns = 0;
  char playerNumber[] = "Second";

	printf("player vs. AI(1) or two players?(2)?\n");
	scanf("%i", &mode);

	printf("How many sticks?\n");
	scanf("%i", &sticks);

	if(mode == 2)	//HUMAN VS. HUMAN
	{
		while(sticks > 0)
		{


			if(turns % 2 == 0)
        strcpy(playerNumber,"First");


		  printf("%s player's turn. There are %i number of sticks. How many do you want to take?(1-3)\n",playerNumber,sticks);
			sticks = humanplayer(sticks);

			turns++;
		}

		if(turns % 2 == 0 )
			printf("The first player won!\n");
		else
			printf("The second player won!\n");
	}

	else  //HUMAN VS. AI
	{
		int tries = 0;
		printf("How many tries should the AI get?\n");
		scanf("%i",&tries);

		const int container = tries + 3; // ez határozza meg a tömb méretét

		int initial_tries = tries;
		int initial_sticks = sticks;

		int aiwins = 0;
		int playerwins = 0;

		int hats[sticks][initial_tries];
		initializehats(initial_sticks, initial_tries, hats);

		for(;tries > 0; tries--)
		{
			int currentplay[sticks];
			initializecurrentplay(initial_sticks, currentplay);

			while(sticks > 0)
			{
				if(turns % 2 == 0)
				{
					printf("The AI goes next. There are %i sticks.\n", sticks);
					sticks = AIplayer(sticks, initial_tries, hats, currentplay);
					printf("%i sticks remain.\n",sticks);
				}
				else
				{
					printf("The player goes next. There are %i sticks. How many do you take?(1,2,3)\n",sticks);
					sticks = humanplayer(sticks);
				}
				turns++;
			}

			if(turns % 2 == 1)
			{
				printf("The player won!\n\n");
				getthemoutfromthehats(initial_tries, initial_sticks, hats, currentplay);
				playerwins++;
			}
			else
			{
				printf("The AI won!\n\n");
				putthemtothehats(initial_tries, initial_sticks, hats, currentplay);
				aiwins++;
			}

			sticks = initial_sticks;
		}

		printf("The human won %i times\n",playerwins);
		printf("The AI won    %i times\n",aiwins);
	}
}

int humanplayer(int sticks) {
	int answer = 100;
	bool valid = false;

	while(!valid)
	{
		scanf("%i",&answer);
		valid = check_validity(sticks, answer, true);
	}

	return sticks - answer;
}

int AIplayer(int sticks, int tries, int hats[][tries], int currentplay[]) {
	int choice = hats[sticks-1][rand() % tries];

	while(!check_validity(sticks, choice, false))
		choice = hats[sticks-1][rand() % tries];

	currentplay[sticks-1] = choice;
	return sticks - choice;
}

int initializehats(int sticks, int tries, int hats[][tries])
{
	int i,j;
	for(i=0;i<sticks;i++)
		for(j=0;j<tries;j++)
		{
			if(j < 3)
				hats[i][j] = j+1;
			else
				hats[i][j] = 0;
		}

	return 0;
}

int initializecurrentplay(int length, int currentplay[])
{
	int i;
	for(i=0;i<length; i++)
		currentplay[i] = 0;

	return 0;
}

int putthemtothehats(int tries, int sticks, int hats[][tries], int currentplay[])
{
	int i,j;
	for(i=0;i<sticks;i++)
		for(j=0;j<tries;j++)
			if(hats[i][j] == 0)
				hats[i][j] = currentplay[i];
	return 0;
}

int getthemoutfromthehats(int tries, int sticks, int hats[][tries], int currentplay[])
{
	int i,j;
	for(i=0;i<sticks;i++)
		for(j=3;j<tries;j++)
			if(hats[i][j] == currentplay[i])
				hats[i][j] = 0;

	return 0;
}
