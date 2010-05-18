#ifndef HIC_TERRAINEDIT
#define HIC_TERRAINEDIT

#include "g5e_std.h"
#include "g5e_world.h"

class G5ETerrainEditor
{
private:
	G5ETerrainObject *terrain;
public:
	int cursorX, cursorZ;
	G5EWorldMeshObject *wmopointer1, *wmopointer2, *wmopointer3, *wmopointer4;
	G5ETerrainEditor(G5ETerrainObject *INterrain, G5EWorldMeshObject *INwmo);
	void setCursor(int x, int z);
	void moveCursorUp();
	void moveCursorDown();
	void moveCursorLeft();
	void moveCursorRight();
	void incHeight(int x, int z, float value);
	void decHeight(int pos);
	void incSelected(float value);
};
#endif