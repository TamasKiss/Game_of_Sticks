#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>


/*
A játék szabályai:
1., Minden játékos elvesz 1,2 vagy 3 pálcát a saját körében
2., Az veszít, aki az utolsó pálcát elveszi
*/



bool check_validity(int sticks, int valasz, bool isPlayer)
{
	if(valasz > 3 || valasz < 1)
	{
		if(isPlayer)
			printf("Lehetséges választás: 1, 2, 3\n");
		return false;
	}

	if(sticks - valasz < 0)
	{
		if(isPlayer)
			printf("Ennyit már nem vehetsz el.\n");
		return false;
	}

	return true;
}

int main() {
	srand(time(NULL));

	int sticks = 0;
	int mode = 0;
	int turns = 0;

	printf("játékos vs. AI(1) vagy két játékos(2)?\n");
	scanf("%i", &mode);

	printf("Hány pálca legyen?\n");
	scanf("%i", &sticks);

	if(mode == 2)	//HUMAN VS. HUMAN
	{
		while(sticks > 0)
		{
			if(turns % 2 == 0)
			{
				printf("#1. játékos jön, %i db pálca van az asztalon. Hányat veszel el?(1-3)\n",sticks);
				sticks = humanplayer(sticks);
			}

			else
			{
				printf("#2. játékos jön, %i db pálca van az asztalon. Hányat veszel el?(1-3)\n",sticks);
				sticks = humanplayer(sticks);
			}
			turns++;
		}

		if(turns % 2 == 0 )
			printf("Az első játékos nyert!\n");
		else
			printf("A második játékos nyert!\n");
	}

	else  //HUMAN VS. AI
	{
		int tries = 0;
		printf("Hány próbálkozása van az AI-nak?\n");
		scanf("%i",&tries);

		const int container = tries + 3; // ez határozza meg a tömb méretét

		int initial_tries = tries;
		int initial_sticks = sticks;

		int gepnyer = 0;
		int jatnyer = 0;

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
					printf("A számítógép jön. %i pálca van.\n", sticks);
					sticks = AIplayer(sticks, initial_tries, hats, currentplay);
					printf("%i pálca maradt.\n",sticks);
				}
				else
				{
					printf("A játékos jön, %i db pálca van az asztalon. Hányat veszel el?(1-3)\n",sticks);
					sticks = humanplayer(sticks);
				}
				turns++;
			}

			if(turns % 2 == 1)
			{
				printf("A játékos nyert!\n\n");
				getthemoutfromthehats(initial_tries, initial_sticks, hats, currentplay);
				jatnyer++;
			}
			else
			{
				printf("A gép nyert!\n\n");
				putthemtothehats(initial_tries, initial_sticks, hats, currentplay);
				gepnyer++;
			}

			sticks = initial_sticks;
		}

		printf("A játékos %i-szer nyert\n",jatnyer);
		printf("A gép %i-szer nyert\n",gepnyer);
	}
}

int humanplayer(int sticks) {
	int valasz = 100;
	bool valid = false;

	while(!valid)
	{
		scanf("%i",&valasz);
		valid = check_validity(sticks, valasz, true);
	}

	return sticks - valasz;
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