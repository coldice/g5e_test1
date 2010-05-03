// g5e_imp2.cpp : Defines the entry point for the console application.
//
#include "g5e_include.h"
int _tmain(int argc, _TCHAR* argv[])
{
	g5e_log_clearinit();
	G5ESystem gsystem;
	//G5EWorld gworld; // Objekt hat noch keinen nutzen
	
	gsystem.init();//&gdraw);  // DrawPointer überhabe im systeminit
	G5EDraw gdraw;
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

	gdraw.gcamera->setClippingPlanes(0.1f,2000.0f);

	G5ETerrainObject gtobj = G5ETerrainObject(10.0f,-10.0f);  // (maximale Höhe, minimale Höhe) - 255 wird also auf -10 bis 10 skaliert
	//gtobj.gettxtdata("test.txt",500,500,1);
	gtobj.gettxtdata("Terrain.raw",1024,1024,4);// (file, Anzahl Bytes X, Anzahl Bytes Z, Schritt (1- jedes element; 2 - jedes zweite)
	//gtobj.scalef(0.1f,0.1f,0.1f);
	gdraw.gdrawobjects->addto(&gtobj); // hinzufügen des generierten terrainobjects zum drawobject
	//gmeshobject.point = G5EPoint(0.0f,0.0f,-5.0f);
	
	/* Übertragung des Worldmeshobjects in das DrawMeshObject */
	/*G5EDrawMeshObject gdrawmeshobject;
	gdrawmeshobject = G5EDrawMeshObject(&gmeshobject);
	gdraw.drawmeshtest = gdrawmeshobject;  // Temporäres Meshobject, sollte eigentlich zumindest nen Pointerarray sein*/
	//gdraw.add_meshobject(&gmeshobject);  Ich glaub der Aufruf kann weg
	
	float p[9];
	for(int n=0;n<9;n++) p[n] = (float)n+1;
	p[8] = (float)17;
	G5EMatrix3 mat1 = G5EMatrix3(p);
	mat1.invert();


	//MAIN LOOP - TO BE MOVED TO MANAGER
	while(gsystem.runstate)
	{
		gsystem.run();
		gdraw.run();
	}
	gsystem.free();
	return 0;
}

