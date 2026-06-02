#pragma once
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <fstream>

using namespace std;

void PrintMap();
void PlaceShip(int size);
int shipAttack(int x, int y, int Hit);