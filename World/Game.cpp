/* 
 * File:   Game.cpp
 * Author: Isaac
 * 
 * Created on April 3, 2014, 12:44 AM
 */

#include "Game.h"

Game::Game() {
    grid=new Grid(145,87);
}

Game::~Game() {
    delete grid;
}
void Game::update()
{
    grid->updateAll();
}
void Game::draw()
{
    grid->drawAll();
}
