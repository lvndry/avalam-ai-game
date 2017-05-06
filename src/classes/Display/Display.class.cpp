#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#include "../GraphicComponent/GraphicComponent.class.h"
#include "Display.class.h"

// include global constants
#include "../../config/constants.h"

Display::Display(int set_x, int set_y, int set_width, int set_height) {
	components = (GraphicComponent**) malloc(sizeof(GraphicComponent*));
	size = 0;
	x = set_x;
	y = set_y;
	width = set_width;
	height = set_height;
};

Display::~Display() {};

Display* Display::initRenderer(SDL_Window *window){ //The renderer is where all the graphic components will be placed
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL)
		printf("renderer non creer\n");

	return 0;
}

Display* destroyRenderer(SDL_Renderer *renderer){
	SDL_DestroyRenderer(renderer);
}

Display* Display::initWindow() { //TODO merge to initRenderer();
	bool error = false;
	//initRenderer(); 
		/*
			 SDL initialisation de la fenêtre

			 Mettre error = true s'il y a eu une erreur
			 				(qui empeche de continuer)

		*/

	if(error)
		return NULL;
	return this;
};

int Display::update() {
	//Move to Window class
	SDL_Event event;
	if(event.type == SDL_MOUSEBUTTONUP){
		GraphicComponent* target = getTargeted(event.button.x, event.button.y);
		if(target == NULL)
			return -1;
		else 
			target->onClick();
	}




	if(updateWindow() == NULL)
		return -1;

	return 0;
}

Display* Display::updateWindow() {
	bool error = false;
		// SDL clear la fenetre

	for (int i = 0; i < size; ++i)
	{
			// Ajouter le components[i] à la fenetre
			// error = true si erreur
	}

	if(error)
		return NULL;
	return this;
};

std::string* Display::inputString(std::string question) {
	std::string* rep = (std::string*) malloc(sizeof(std::string));
	std::cout << question;
	std::cin >> *rep;
	return rep;
}

/*int* Display::inputNumber(std::string question) {
	std::string rep = "-1";
	std::cout << question;
	std::cin >> rep;
	int* repint;
	repint=(int*) malloc(sizeof(int));
	*repint = std::stoi(rep);
	return repint;
}*/

void* Display::input(std::string question, int type) {
	switch(type) {
		case INPUT_TYPE_STRING:
			return inputString(question);
		//case INPUT_TYPE_NUMBER:
			//return inputNumber(question);
		default:
		return NULL;
	}
}

GraphicComponent* Display::addComponent(GraphicComponent* componentToAdd) {
	components = (GraphicComponent**) realloc(components, sizeof(GraphicComponent*) * size + 1);
	components[size] = componentToAdd;
	printf("Component [%d;%d] has been added to display [%d;%d] (%d:%d) [size : %d]\n", components[size]->x, components[size]->y, x, y, width, height, size);
	return components[size++]; //size is incremented after he gets injected as index of array (post inc)
};

GraphicComponent* Display::getTargeted(int mouse_x, int mouse_y) {
	if(mouse_x < x || mouse_x > x+width || mouse_y < y || mouse_y > y+height)
		return NULL;
	else
		for (int i = 0; i < size; ++i)
			if(mouse_x < components[i]->x || mouse_x > components[i]->x+components[i]->width || mouse_y < components[i]->y || mouse_y > components[i]->y+components[i]->height)
				continue;
			else
				return components[i];
			return NULL;
		};

#endif