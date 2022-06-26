#include "Board.h"
#include "Fruit.h"
#include "GameObject.h"
#include "Gameplay.h"
#include "Ghost.h"
#include "io_utils.h"
#include "Pacman.h"
#include "Point.h"
using namespace std;

void main()
{
	srand(time(NULL));
	Gameplay g;
	g.init();
}