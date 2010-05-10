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

	G5EInterface *main_interface = new G5EInterface();
	main_interface->init_interface(gdraw.gsystem->ifsurface);

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

	G5ETerrainObject gtobj = G5ETerrainObject(10.0f,-10.0f);  // (maximale Höhe, minimale Höhe) - 255 wird also auf -10 bis 10 skaliert
	gtobj.gettxtdata("test.txt",500,500,1); // (file, Anzahl Bytes X, Anzahl Bytes Z, Schritt (1- jedes element; 2 - jedes zweite)
	gtobj.scalef(0.1f,0.1f,0.1f);
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

	//Interface test - to be moved BEGIN
	/*
	G5EIPanel *tpan1 = new G5EIPanel(200, 200, 10, 10, true, 0x99222222);
	main_interface->add_panel(tpan1);
	*/
	main_interface->add_panel(new G5EIPanel(200, 60, 10, 10, true, 0x88cdcdcd));
	main_interface->if_panels[0].add_text(new G5EIStaticText(10, 10, "FPS:", 4, 8));
	G5EIDynamicText *t1 = new G5EIDynamicText();
	t1->posx=50;
	t1->posy=10;
	//int ival = 597;
	//int ival2 = 0;
	//gsystem.gtime->fps
	//t1->assign_textptr(&ival);
	t1->assign_textptr(&gsystem.gtime->fps);
	main_interface->if_panels[0].add_dyntext(t1);

	main_interface->add_panel(new G5EIPanel(200, 100, 590, 10, true, 0x88abeeab));
	main_interface->if_panels[1].add_text(new G5EIStaticText(10, 10, "Camera  Position", 4, 8));
	main_interface->if_panels[1].add_text(new G5EIStaticText(20, 35, "x", 4, 8));
	main_interface->if_panels[1].add_text(new G5EIStaticText(20, 55, "y", 4, 8));
	main_interface->if_panels[1].add_text(new G5EIStaticText(20, 75, "z", 4, 8));
	G5EIDynamicText *cp1 = new G5EIDynamicText();
	G5EIDynamicText *cp2 = new G5EIDynamicText();
	G5EIDynamicText *cp3 = new G5EIDynamicText();
	cp1->posx=35;
	cp1->posy=35;
	cp1->assign_textptr(&gdraw.gcamera->pos.v1);
	cp2->posx=35;
	cp2->posy=55;
	cp2->assign_textptr(&gdraw.gcamera->pos.v2);
	cp3->posx=35;
	cp3->posy=75;
	cp3->assign_textptr(&gdraw.gcamera->pos.v3);
	main_interface->if_panels[1].add_dyntext(cp1);
	main_interface->if_panels[1].add_dyntext(cp2);
	main_interface->if_panels[1].add_dyntext(cp3);

	//ival2 = *((int*)(t1->ptr_text)); // works
	//gdraw.gcamera->pos.v1

	//Interface test END


	//MAIN LOOP - TO BE MOVED TO MANAGER
	while(gsystem.runstate)
	{
		gsystem.run();
		gdraw.run();
		
/*		SDL_FillRect(gsystem.surface, NULL, 0x550000); */
		main_interface->draw_interface();
		int retx;
/*		retx = SDL_BlitSurface(main_interface->if_surface, NULL, gsystem.surface, NULL); */
		
//		SDL_Flip(gsystem.surface);
		gdraw.run_end();
	}
	gsystem.free();
	return 0;
}

