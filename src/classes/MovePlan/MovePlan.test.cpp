#include <stdio.h>
#include "MovePlan.class.h"
#include "../Emplacement/Emplacement.class.h"
#include "../../config/constants.h"

/*
	UNIT TEST FOR MOVEPLAN
*/

#define SHOULD_BE_TRUE(a) if(a == -1)printf("FALSE %d\n",  err++);
#define SHOULD_BE_FALSE(a) if(a == 0)printf("TRUE %d\n",  err++);


int main(int argc, char const *argv[])
{
	int team;
	Emplacement grille[TAILLE][TAILLE];
	MovePlan a;
	int err=0;

	grille[1][2].valeur = 1;
	grille[1][3].valeur = 1;
	grille[6][7].valeur = 1;
	grille[7][7].valeur = 1;
	grille[1][1].valeur = 1;
	grille[4][3].valeur = 1;
	grille[4][5].valeur = 1;

	grille[1][2].hauteur = 1;
	grille[1][3].hauteur = 1;
	grille[6][7].hauteur = 1;
	grille[7][7].hauteur = 1;
	grille[1][1].hauteur = 1;
	grille[4][3].hauteur = 1;
	grille[4][5].hauteur = 1;

	for (team = 0; team < 2; ++team)
	{
		if(a.init(-1, -1, -2, -2, 3, grille) == 0)
			return -1;
		//SHOULD_BE_FALSE(a.init(1, 2, 1, 2, team, grille));
		if(a.init(1, 2, 1, 2, team, grille) == 0)
			return -1;

		SHOULD_BE_TRUE(a.init(1, 2, 1, 3, team, grille));
		SHOULD_BE_TRUE(a.init(6, 7, 7, 7, team, grille));
		SHOULD_BE_TRUE(a.init(1, 2, 1, 1, team, grille));
		SHOULD_BE_TRUE(a.init(4, 5, 4, 3, team, grille));
	}

	grille[2][4].valeur = 2;
	grille[2][5].valeur = 2;
	grille[2][6].valeur = 2;
	grille[2][7].valeur = 2;

	for (team = 0; team < 2; ++team)
	{
		SHOULD_BE_FALSE(a.init(2, 3, 2, 4, team, grille));
		SHOULD_BE_FALSE(a.init(3, 4, 2, 4, team, grille));
		SHOULD_BE_FALSE(a.init(2, 4, 2, 5, team, grille));
		SHOULD_BE_FALSE(a.init(2, 4, 2, 3, team, grille));
		SHOULD_BE_FALSE(a.init(2, 5, 2, 5, team, grille));

		SHOULD_BE_TRUE(a.init(1, 2, 1, 3, team, grille));
		SHOULD_BE_TRUE(a.init(2, 8, 3, 7, team, grille));
	}

	if(err)
		return err;
	else
		return 0;
}