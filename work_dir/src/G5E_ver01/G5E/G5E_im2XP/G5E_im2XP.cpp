// g5e_imp2.cpp : Defines the entry point for the console application.
//
#include "g5e_include.h"
int _tmain(int argc, _TCHAR* argv[])
{
	G5ESystem gsystem;
	//G5EWorld gworld; // Objekt hat noch keinen nutzen
	G5EDraw gdraw;
	gsystem.init();//&gdraw);  // DrawPointer überhabe im systeminit
	gdraw.init(&gsystem);

	/*Erzeugung des _MÄCHTIGEN_ Meshobjects*/
	G5EMeshObject gmeshobject;
	G5EPoint points[3] = {G5EPoint(-1.0f,1.0f,0.0f), G5EPoint(1.0f,1.0f,0.0f), G5EPoint(0.0f,-1.0f,0.0f)};
	gmeshobject.add(points);
	G5EPoint points2[3] = {G5EPoint(1.0f,1.0f,0.0f),G5EPoint(1.5f,1.0f,-1.0f), G5EPoint(0.0f,-1.0f,0.0f)};
	gmeshobject.add(points2);
	G5EPoint points3[3] = {G5EPoint(0.0f,-1.0f,0.0f),G5EPoint(-1.0f,-2.0f,0.0f), G5EPoint(1.0f,-2.0f,0.0f)};
	gmeshobject.add(points3);
	G5EWorldMeshObject gworldmeshobject;
	gworldmeshobject = G5EWorldMeshObject(&gmeshobject);
	G5EWorldMeshObject gworldmeshobject2;
	gworldmeshobject2 = G5EWorldMeshObject(&gmeshobject);
	gworldmeshobject.translatef(0.0f,0.0f,-5.0f);
	gworldmeshobject2.translatef(-10.0f,0.0f,-5.0f);
	gdraw.gdrawobjects->addwmo(&gworldmeshobject);
	gdraw.gdrawobjects->addwmo(&gworldmeshobject2);

	G5ETerrainObject gtobj = G5ETerrainObject(10.0f,-10.0f);  // (maximale Höhe, minimale Höhe) - 255 wird also auf 0 bis 10 skaliert
	gtobj.gettxtdata("test.txt",500,500,1); // (file, Anzahl Bytes X, Anzahl Bytes Z, Schritt (1- jedes element; 2 - jedes zweite)
	gdraw.gdrawobjects->addto(&gtobj); // hinzufügen des generierten terrainobjects zum drawobject
	//gmeshobject.point = G5EPoint(0.0f,0.0f,-5.0f);

	/* Übertragung des Worldmeshobjects in das DrawMeshObject */
	/*G5EDrawMeshObject gdrawmeshobject;
	gdrawmeshobject = G5EDrawMeshObject(&gmeshobject);
	gdraw.drawmeshtest = gdrawmeshobject;  // Temporäres Meshobject, sollte eigentlich zumindest nen Pointerarray sein*/
	//gdraw.add_meshobject(&gmeshobject);  Ich glaub der Aufruf kann weg

	//MAIN LOOP - TO BE MOVED TO MANAGER
	while(gsystem.runstate)
	{
		gsystem.run();
		gdraw.run();
	}
	gsystem.free();
	return 0;
}

