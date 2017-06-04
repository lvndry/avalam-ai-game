#ifndef PLAYER_CPP
#define PLAYER_CPP

#include <stdio.h>
#include <iostream>
#include <string>
#include "../Display/Display.class.h"
#include "../Emplacement/Emplacement.class.h"
#include "../Mouvement/Mouvement.class.h"
#include "../MovePlan/MovePlan.class.h"
#include "Player.class.h"
#include <vector>
#include "SDL2/SDL.h"

// include global constants
#include "../../config/constants.h"
#include "../../config/macros.h"

using namespace std;

int Player::init(Display* display, int newTeam, string newName, int newType) {
	if((!AVAILABLE_TEAM(newTeam)) || newName.empty() || (!AVAILABLE_TYPE(newType)))
		return -1;
	team = newTeam;
	name = newName;
	type = newType;
	playerDisplay = display;
	/* TODO : int(Player::*evaluate)(Emplacement[TAILLE][TAILLE]) function pointer
	switch(type) {
		case PLAYER_TYPE_HUMAN:
			evaluate=&Player::HumanEvaluate;
		break;
		case PLAYER_TYPE_IA:
			evaluate=&Player::IAEvaluate;
		break;
		default :
			evaluate=&Player::HumanEvaluate;
		break;
	}*/
	points = 0;
	//cout << name << " a rejoint la partie ! (équipe : "<< team <<")\n";
	return 0;
}

string Player::getName() {
	return name;
}

int Player::getScore(Emplacement grille[TAILLE][TAILLE]) {
	int score=0, x, y;
	for (x = 0; x < TAILLE; ++x)
		for (y = 0; y < TAILLE; ++y)
			if(grille[x][y].valeur == team) score++;
		return score;
}

int Player::HumanEvaluate(Emplacement grille[TAILLE][TAILLE]) {
	/*
	Mouvement mvt;
	int x_s, y_s, x_d, y_d;
	vector<int> click(1);
	Emplacement* first;
	Emplacement* second;

	puts("====Quel pion bouger?====\n");
	puts("> x : ");
	scanf("%d", &x_s);
	puts("> y : ");
	scanf("%d", &y_s);
	puts("==Vers quelle position?==\n");
	puts("> x : ");
	scanf("%d", &x_d);
	puts("> y : ");
	scanf("%d", &y_d);

	if(mvt.init(x_s, y_s, x_d, y_d, grille) == -1)
		return -1;

	mvt.apply(grille);
	*/

	Mouvement move;
	std::vector<int> first;
	std::vector<int> second;
	std::vector<int> selection;
		
	while(first.size() == 0 || second.size() == 0){

		selection = playerDisplay->getSelect(grille);

		if(selection.size() == 2){

			if(first.size() == 0){
				first.push_back(selection[0]);
				first.push_back(selection[1]);
				printf("first[0] : %d\n", first[0]);
				printf("first[1] : %d\n", first[1]);
			}

			else{
				second.push_back(selection[0]);
				second.push_back(selection[1]);
				printf("Second[0] %d\n", second[0]);
				printf("second[1] : %d\n", second[1]);
			}
		}
	}

	if(move.init(first[0], first[1], second[0], second[1], grille) != -1){
		move.apply(grille);
		grille[first[0]][first[1]].selected = 0;
		grille[second[0]][second[1]].selected = 0;
	}
	else{ 
		printf("Uncorrect move\n"); 
		return -1;
	}
	playerDisplay->printGrille(grille);

	return 0;
}

int Player::evaluate(Emplacement grille[TAILLE][TAILLE]) {
	
	switch(type) {
		case PLAYER_TYPE_HUMAN:
			return HumanEvaluate(grille);
		case PLAYER_TYPE_IA:
			return IAEvaluate(grille);
		default:
			return HumanEvaluate(grille);
	}
}

int Player::IAEvaluate(Emplacement grille[TAILLE][TAILLE]) {
	int x, y, k, l;
	MovePlan bestmove, tmp;

	for (x = 0; x < TAILLE; ++x)
		for (y = 0; y < TAILLE; ++y)
			if(grille[x][y].valeur == 2)
				continue;
			else
				for (k = -1; k <= 1; ++k)
					for (l = -1; l <= 1; ++l)
						if(grille[x+l][y+k].valeur == 2) continue;
					else
						if(tmp.init(x, y, x+l, y+k, team, grille) > bestmove.getScore())
							bestmove.init(x, y, x+l, y+k, team, grille);

						bestmove.calcScore(grille);
						if(bestmove.score == -1) return -1;
						bestmove.mvt.apply(grille);
						return 0;
	}

#endif