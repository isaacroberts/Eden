
#include "Square.h"

#include "../main.h"
#include "../Gui/Event.h"
#include "Map.h"
#include "Game.h"
#include "Grid.h"


#include "../Matter/_.h"

#include "../Gui/Gui.h"
#include "../Ref/_.h"

#include <iostream>

using namespace std;

#define for_each_occ for(int o=0;o<occs.size();++o)

int Square::squareSize=10;
int Square::halfSquareSize=squareSize/2;
int Square::quarterSquareSize=squareSize/4;


Square::Square(int x, int y)
{
    gx=x;
    gy=y;
    freeSpace=MAX_FREE_SPACE;
    
    hash=rand()>>4;// why is this rand/16 ?
    pixX=gx*squareSize+Gui::minPx;
    pixY=gy*squareSize+Gui::minPy;
    
    sky=new Sky();
    terrain=Map::getDefaultTerrain();
    liquid=Map::getDefaultLiquid();
    occs=vector<Thing*>();
    redraw=2;
}
Square::Square()//error constructor
{
    gx=-1;
    gy=-1;
    freeSpace=0;
    
    hash=-1;
    pixX=50;
    pixY=50;
    
    sky=NULL;
    terrain=NULL;
    liquid=NULL;
    occs=vector<Thing*>();
    redraw=255;
}
void Square::finalizeConstruction()
{
    sky->setLoc(this);
    terrain->setLoc(this);
    liquid->setLoc(this);
    for_each_occ
        occs[o]->setLoc(this);
}
Square::~Square()
{
    for_each_occ
        delete occs[o];
    deleteTerrain();
    delete sky;
}
void Square::preStep()
{
    if (Util::everyNth(Gui::forceRedrawFreq,hash))
        requireRedraw();
    sky->preStep();
    terrain->preStep();
    liquid->preStep();
    for_each_occ
    {
        occs[o]->run();
        if (occs[o]->isDead())
        {
            clearOccupant(o);
            o--;
        }
    }
}
void Square::update()
{
    sky->update();
    terrain->run();
    if (terrain->isDead())
        clearTerrain();
    liquid->update();
    for_each_occ
    {
        occs[o]->preStep();
    }
}
void Square::endStep()
{
    sky->endStep();
    terrain->endStep();
    liquid->endStep();
    for_each_occ
    {
        occs[o]->endStep();
    }
}
void Square::draw()
{
    if (redraw>0 || Gui::globalRedraw>0 
            || displayType!=DisplayType::Normal)
    {
        if (px()<Gui::minPx || px()>Gui::maxPx)
            return;
        if (py()<Gui::minPy || py()>Gui::maxPy)
            return;
        terrain->paint();
        for_each_occ
            occs[o]->paint();
        liquid->paint();
        sky->paint();
//        if (displayType==DisplayType::Normal)
//        {
//            Draw::setColor(0,0,0,Earth::nightAlpha);
//            fillRect();
//        }
        if (redraw<=1)
            redraw=0;
        else
            redraw--;
    }
}

/*------------------------------------*/
/*----------Occupant------------------*/
/*------------------------------------*/
void Square::addOccupant(Thing* add)
{
    add->setLoc(this);
    if (!add->isDead())
    {
        requireRedraw();
        freeSpace-=add->getSize();
        occs.push_back(add);
    }
    else
    {
        cout<<"Adding dead occupant "<<add->getType()->toString()<<endl;
        add->banishFromSquare();
    }
}
void Square::addOccupant(Thing* add,byte references)
{
    add->setLoc(this);
    add->setRefs(references);
    if (!add->isDead())
    {
        requireRedraw();
        freeSpace-=add->getSize();
        occs.push_back(add);
    }
    else
    {
        cout<<"Adding dead occupant "<<add->getType()->toString()<<endl;
        add->banishFromSquare();
    }
}
void Square::deleteOccupant(int o)
{
    occs[o]->banishFromSquare();
    occs.erase(occs.begin()+o);    
}
void Square::clearOccupant(int o)
{
    requireRedraw();
    freeSpace+=occs[o]->getSize();
    deleteOccupant(o);
}
bool Square::clearOccupant(Thing* remove)
{
    for_each_occ
    {
        if (remove->equals(occs[o]))
        {
            clearOccupant(o);
            requireRedraw();
            return true;
        }
    }
    cout<<"clearOccupant called on occ not in list"<<remove<<endl;
    return false;
}
bool Square::removeOccupant(Thing* remove)
{
    for_each_occ
    {
        if (remove->equals(occs[o]))
        {
            freeSpace+=occs[o]->getSize();
            occs.erase(occs.begin()+o);
            requireRedraw();
            return true;
        }
    }
    cout<<"removeOccupant called on occ not in list"<<remove<<endl;
    return false;
}
void Square::queueOccRemoval(int o)
{
    GRID.queueOccRemoval(occs[o]);
}
void Square::clearAllOccupants()
{
    requireRedraw();
    while (!occs.empty())
        deleteOccupant(0);
    freeSpace=MAX_FREE_SPACE;
}
/*-----Occ-Checkers---------*/
bool Square::hasOccOfType(ThingType* type) const
{
    for_each_occ
    {
        if (occs[o]->isA(type))
            return true;
    }
    return false;
}
bool Square::hasOccOfTypes(ThingType* type1,ThingType* type2) const
{
//    cout<<"  loc=";
//    printString();
//    cout<<endl;
    for_each_occ
    {
        if (occs[o]->isA(type1) || occs[o]->isA(type2))
        {
//            cout<<"     blockn occ loc = ";
//            occs[o]->getLoc()->printString();
//            cout<<endl;
            return true;
        }
    }
    return false;
}
bool Square::hasOccOfTypes(ThingType** typeArray, int typeAmt) const
{
    for_each_occ
    {
        for (int type=0;type<typeAmt;type++)
        {
            if (occs[o]->isA(typeArray[type]))
            {
                return true;
            }
        }
    }
    return false;
}
Thing* Square::getOccOfType(ThingType* type)
{
    for_each_occ
    {
        if (occs[o]->isA(type))
            return occs[o];
    }
    return NULL;
}
/*-------Spaced-Based Occing*/
Thing* Square::getBiggestOcc()
{
    sizeval bigness=0;
    Thing* biggest=NULL;
    for_each_occ
    {
        //assume that getSize() may be an expensive function
        sizeval occsize=occs[o]->getSize();
        if (occsize>bigness)
        {
            bigness=occsize;
            biggest=occs[o];
        }
    }
    return biggest;
}
/*---------Terrain--------------*/
void Square::deleteTerrain()
{
    delete terrain;
}
void Square::queueTerrainReplacement(Terrain* replacewith)
{//to be used only to avoid created .cpp files
    GRID.queueTerrainReplacement(replacewith);
}
void Square::clearTerrain()
{
    requireRedraw();
    Terrain* dirt=new Dirt();
    dirt->replace(terrain);
    deleteTerrain();
    terrain=dirt;
}
void Square::setTerrain(Terrain* set)
{
    requireRedraw();
    set->replace(terrain);
    deleteTerrain();
    terrain=set;
}
void Square::installTerrain(Terrain* set)
{//sets terrain without changing heat & moisture
    requireRedraw();
    set->setElevation(terrain->getElevation());
    set->setLoc(this);
    deleteTerrain();
    terrain=set;
}

/*---------Liquid------------------*/
void Square::replaceLiquid(Liquid* replaceWith)
{
    requireRedraw();
    delete liquid;
    liquid=replaceWith;
    liquid->setLoc(this);
}
bool Square::requisitionWater(float amt)
{
    if (liquid->getMass()>amt)
    {
        liquid->changeMass(-amt);
        return true;
    }
    else
    {
        amt-=liquid->getMass();
        liquid->setMass(0);
        return getSky()->takeMoisture(amt);
    }
}


/*-------------------------------------*/
/*-------------------------------------*/
/*------Geographic Functions-----------*/
/*-------------------------------------*/
/*-------------------------------------*/
Square* Square::transform(int dx,int dy) const
{
    if (Earth::wraparound && dx!=0)
    {
        if (gx+dx>=GRID.xAmt)
        {
            int tx=(gx+dx)%GRID.xAmt;
            return getSquare(tx,gy+dy);
        }
        else if (gx+dx<0)
        {
            int tx=GRID.xAmt+(gx+dx)%GRID.xAmt;
            return getSquare(tx,gy+dy);
        }
    }
    return getSquare(gx+dx,gy+dy);
}
Square* Square::safeTransform(int dx, int dy) const
{
    if (Earth::wraparound && dx!=0)
    {
        if (gx+dx>=GRID.xAmt)
        {
            int tx=(gx+dx)%GRID.xAmt;
            return getSquare(tx,gy+dy);
        }
        else if (gx+dx<0)
        {
            int tx=GRID.xAmt+(gx+dx)%GRID.xAmt;
            return getSquare(tx,gy+dy);
        }
    }
    int transY=GRID.validizeY(gy+dy);
    return getSquare(gx+dx,transY);
}
Square* Square::transformCoord(coord& cx, coord& cy, int dx, int dy) const
{
    int sqrDx=moveCoord(cx,dx);
    int sqrDy=moveCoord(cy,dy);
    return transform(sqrDx,sqrDy);
}
Square* Square::safeTranformCoord(coord& cx, coord& cy, int dx, int dy) const
{//ensures that transform will not go over top or bottom wall
    int sqrDx=moveCoord(cx,dx);
    int sqrDy=moveCoord(cy,dy);
    if (gy+sqrDy>=GRID.xAmt) {
        cy=COORD_RESOLUTION-1;
        int transX=GRID.wrapX(gx+sqrDx);
        return getSquare(transX,GRID.xAmt-1);
    }
    else if (gy<-sqrDy) {
        cy=0;
        int transX=GRID.wrapX(gx+sqrDx);
        return getSquare(transX,0);
    }
    return transform(sqrDx,sqrDy);
}
int Square::neighborAmt() const
{
    if (isError()) return 0;
    int amt=4;
    if (gy==0)
        amt=3;
    if (gy==GRID.xAmt-1)
        amt--;
    if (!Earth::wraparound)
    {
        if (gx==0)
            amt--;
        if (gx==GRID.xAmt-1)
            amt--;
    }
    return amt;
}
vector<Square*>* Square::getNeighbors() const
{
    vector<Square*>* naybs=new vector<Square*>();
    Dir *dir=Dir::North;
    for (int r=0;r<4;++r)
    {
        Square* nabor=transform(dir);
        if (nabor->notError())
        {
            naybs->push_back(nabor);
        }
        dir=dir->rotateClockwise();
    }
    return naybs;
}
vector<Square*>* Square::getOrdinalNeighbors() const
{
    vector<Square*>* naybs=new vector<Square*>();
    for (int x=-1;x<=1;++x)//go across neighboring columns
    {
        for (int y=-1;y<=1;++y)//go across neighboring rows
        {
            if (Earth::wraparound || (gy>=-x && gx<y+GRID.xAmt))
            {//if the map doesnt wrap, make sure x is in bounds
                Square* nabor=getSquare(GRID.wrapX(gx+x),gy+y);
                if (!nabor->isError())
                {
                    naybs->push_back(nabor);
                }
            }
        }
    }
    return naybs;
}
Square* Square::randNeighbor() const
{
    if (isError())
        return Grid::squerror;
    Square* neighb;
    do {
        neighb=transform(Dir::getRandDir());
    } while(neighb->isError());
    return neighb;
}
bool Square::isNeighbor(Square* other) const
{
    int yDif=gy-other->y();
    if (yDif>1 || yDif<-1)
        return false;
    int xDif=gx-other->x();
    if (xDif>1 || xDif<-1)
    {
        if (Earth::wraparound)
        {
            if (gx==0 && other->x()==GRID.xAmt-1)
                return true;
            if (gx==GRID.xAmt-1 && other->x()==0)
                return true;
        }
        return false;
    }
    //is true only IFF xDif is 0 or yDif is 0 but not both
    return (xDif==0 ^ yDif==0);
}
bool Square::isOrdinalNeighbor(Square* other) const
{
    int yDif=gy-other->y();
    if (yDif>1 || yDif<-1)
        return false;
    int xDif=gx-other->x();
    if (xDif>1 || xDif<-1)
    {
        if (Earth::wraparound)
        {
            if (gx==0 && other->x()==GRID.xAmt-1)
                return true;
            if (gx==GRID.xAmt-1 && other->x()==0)
                return true;
        }
        return false;
    }
    //true as long as this!=other
    return (xDif!=0 || yDif!=0);
}
/*-----------Printers------------*/
void Square::printString() const
{
    cout<<gx<<", "<<gy;
}
void Square::printInfo() const
{
    cout<<gx<<", "<<gy<<endl;
    sky->printInfo();
    terrain->printInfo();
    liquid->printInfo();
    cout<<"  Occ amt = "<<occs.size()<<endl;
    for_each_occ
        occs[o]->printInfo();
}
void Square::printAmtsOfTypes() const
{
    vector<pair<ThingType*,int> > amts=vector<pair<ThingType*,int> >();
    for_each_occ
    {
        bool inList=false;
        ThingType* occType=occs[o]->getType();
        for (int a=0;a<amts.size();++a)
        {
            if (occType==amts[a].first) {
                inList=true;
                amts[a].second++;
            }
        }
        if (!inList)
        {
            amts.push_back(pair<ThingType*,int>(occType,1));
        }
    }
    for (int a=0;a<amts.size();++a)
    {
        cout<<"    "<<amts[a].first->toString()<<" : "<<amts[a].second<<endl;
    }
}
/*---------Static---------------*/
Square* Square::getSquare(int x,int y)
{
    return GRID.getSquare(x,y);
}
#undef for_each_occ