#include "g5e_terrainedit.h"

G5ETerrainEditor::G5ETerrainEditor(G5ETerrainObject *INterrain, G5EWorldMeshObject *INwmo)
{
	terrain = INterrain;
	wmopointer1 = INwmo;
	cursorX = 0;
	cursorZ = 0;
	wmopointer1->translation = G5EPoint(0, terrain->getHeight(cursorX,cursorZ)+0.2, 0);
}
void G5ETerrainEditor::setCursor(int x, int z)
{
	cursorX = x;
	cursorZ = z;
	wmopointer1->translation = G5EPoint((float)cursorX,terrain->getHeight(cursorX,cursorZ)+0.2,(float)cursorZ);
}
void G5ETerrainEditor::moveCursorUp()
{
	if(cursorZ > -terrain->getdimZ()/2)
	{
		cursorZ--;
		wmopointer1->translatef(0,0,-1.0f);
		wmopointer1->translation.y = terrain->getHeight(cursorX,cursorZ)+0.2;
	}
}
void G5ETerrainEditor::moveCursorDown()
{
	if(cursorZ < terrain->getdimZ()/2-1)
	{
		cursorZ++;
		wmopointer1->translatef(0,0,1.0f);
		wmopointer1->translation.y = terrain->getHeight(cursorX,cursorZ)+0.2;
	}
}
void G5ETerrainEditor::moveCursorLeft()
{
	if(cursorX > -terrain->getdimX()/2)
	{
		cursorX--;
		wmopointer1->translatef(-1.0f,0,0);
		wmopointer1->translation.y = terrain->getHeight(cursorX,cursorZ)+0.2;
	}
}
void G5ETerrainEditor::moveCursorRight()
{
	if(cursorX < terrain->getdimX()/2-1)
	{
		cursorX++;
		wmopointer1->translatef(1.0,0,0);
		wmopointer1->translation.y = terrain->getHeight(cursorX,cursorZ)+0.2;
	}
}
void G5ETerrainEditor::incHeight(int x, int z, float value)
{
	float nuHeight = terrain->getHeight(x,z)+value;
	terrain->setHeight(nuHeight,x,z);
	if(nuHeight - terrain->getHeight(x+1,z) > 0.5) incHeight(x+1,z, value);
	if(nuHeight - terrain->getHeight(x-1,z) > 0.5) incHeight(x-1,z, value);
	if(nuHeight - terrain->getHeight(x,z+1) > 0.5) incHeight(x,z+1, value);
	if(nuHeight - terrain->getHeight(x,z-1) > 0.5) incHeight(x,z-1, value);

}
void G5ETerrainEditor::incSelected(float value)
{
	incHeight(cursorX,cursorZ,value);
	wmopointer1->translation.y = terrain->getHeight(cursorX,cursorZ)+0.2;
}		