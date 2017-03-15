/* 
 * File:   Grid.cpp
 * Author: Isaac
 * 
 * Created on April 3, 2014, 12:51 AM
 */

#include "Grid.h"


#include "../main.h"
#include "../Gui/Event.h"
#include "Game.h"

#include "Square.h"
#include "../Matter/Terrain.h"
#include "../Matter/Plant.h"

#include "../Ref/Earth.h"

Square* Grid::squerror=new Square();
Grid::Grid(int xCount,int yCount)
{
    xPixelOffset=0;
    yPixelOffset=0;
    Driver::loadingScreen->setTask(LoadingScreen::Square);
    terrainReplacementQu=queue<pair<Terrain*,Square*> >();
    occRemovalQu=queue<Thing*>();
    occMovementQu=queue<pair<Thing*,Square*> >();
    xAmt=xCount;
    yAmt=yCount;
    grid=new Square**[xAmt];
    for (int x=0;x<xAmt;++x)
    {
        if (freq(x,xAmt,32))
            Driver::loadingScreen->setPercentage(x,xAmt);
        grid[x]=new Square*[yAmt];
        for (int y=0;y<yAmt;++y)
        {
            grid[x][y]=new Square(x,y);
        }
    }
    for (int x=0;x<xAmt;++x)
    {
        for (int y=0;y<yAmt;++y)
        {
            grid[x][y]->finalizeConstruction();
        }
    }
    Driver::loadingScreen->setPercentage(1);
    cout<<"Grid size = "<<xAmt<<" by "<<yAmt;
    cout<<"   = "<<xAmt*yAmt<<" squares"<<endl;
    Event::checkForExit();
    Gui::globalRedraw=2;
}
Grid::~Grid()
{
    for (int x=0;x<xAmt;x++)
    {
        for (int y=0;y<yAmt;y++)
        {
            delete grid[x][y];
        }
        delete grid[x];
    }
    delete grid;
   /*
    // neccessary?
    while (!terrainReplacementQu.empty())
        terrainReplacementQu.pop();
    while (!occMovementQu.empty())
        occMovementQu.pop();
    while (!occRemovalQu.empty())
        occRemovalQu.pop();
    */
}
void Grid::updateAll()
{
    for (int x=0;x<xAmt;x++)
        for (int y=0;y<yAmt;y++)
            grid[x][y]->preStep();
    for (int x=0;x<xAmt;x++)
    {
        for (int y=0;y<yAmt;y++)
        {
            grid[x][y]->update();
        }
    }
    Plant::updateAll();
    for (int x=0;x<xAmt;x++)
    {
        for (int y=0;y<yAmt;y++)
        {
            grid[x][y]->endStep();
        }
    }
    removeFromQus();
}
void Grid::removeFromQus()
{
    while (!terrainReplacementQu.empty())
    {
        Square* change=terrainReplacementQu.front().second;
        Terrain* replace=terrainReplacementQu.front().first;
        if (replace!=NULL)
            change->setTerrain(replace);
        else
            change->clearTerrain();
        terrainReplacementQu.pop();
    }
    while (!occMovementQu.empty())
    {
        Square* moveFrom=occMovementQu.front().first->getLoc();
        Square* moveTo=occMovementQu.front().second;
        Thing* move=occMovementQu.front().first;
        moveFrom->removeOccupant(move);
        moveTo->addOccupant(move);
        occMovementQu.pop();
    }
    while (!occRemovalQu.empty())
    {
        Square* removeFrom=occRemovalQu.front()->getLoc();
        if (removeFrom->isError() || removeFrom==NULL)
        {
            cout<<"Boss, youre not going to like this but we lost a "
                    "Occupant we were supposed to remove.\n";
            cout<<"    "<<occRemovalQu.front()->getType()->toString()<<
                    ", says hes from ";removeFrom->printString();cout<<endl;
            occRemovalQu.pop();
        }
        else
        {
            bool success=removeFrom->clearOccupant(occRemovalQu.front());
            if (!success)
            {
                cout<<"Boss, youre not going to like this but we lost a "
                    "Occupant we were supposed to remove.\n";
                cout<<"    "<<occRemovalQu.front()->getType()->toString()<<" wasnt found in ";
                removeFrom->printString();cout<<endl;
            }
            occRemovalQu.pop();
        }
    }
}
void Grid::queueThingMovement(Thing* move, Square* moveTo)
{
    if (moveTo->isError())
    {
        queueOccRemoval(move);
    }
    else {
        occMovementQu.push(pair<Thing*,Square*>(move,moveTo));
    }
}
void Grid::queueOccRemoval(Thing* remove)
{
    occRemovalQu.push(remove);
}
void Grid::queueTerrainReplacement(Terrain* replaceWith)
{//replaces terrain at the end of the updating phase
    terrainReplacementQu.push( pair<Terrain*,Square*>(replaceWith,replaceWith->getLoc()) );
}
void Grid::drawAll()
{
    for (int x=0;x<xAmt;x++)
    {
        for (int y=0;y<yAmt;y++)
        {
            grid[x][y]->draw();
        }
    }
    if (Gui::globalRedraw>0)
        Gui::globalRedraw--;
}
//static squarelist getter functions
vector<Square*>* Grid::getSquareOfSquares(Square* center,int radius)
{
    vector<Square*>* squareOf=new vector<Square*>();
    for (int y=validizeY(center->y()-radius);y<=validizeY(center->y()+radius);y++)
    {
        for (int x=validizeX(center->x()-radius);x<=validizeX(center->x()+radius);x++)
        {
            squareOf->push_back(grid[x][y]);
        }
        if (Earth::wraparound)
        {
            if (radius>center->x())
                for (int x=wrapX(center->x()-radius);x<xAmt;x++)
                    squareOf->push_back(grid[x][y]);
            if (center->x()+radius>=xAmt)
                for (int x=0;x<=wrapX(center->x()+radius);x++)
                    squareOf->push_back(grid[x][y]);
        }
    }
    return squareOf;
}
vector<Square*>* Grid::getSquaresInRadius(Square* center,int radius)
{
    vector<Square*>* area=getSquareOfSquares(center,radius);
    int gx=center->gx,gy=center->gy;
    if (radius<=2)
    {
        for (int x=-radius;x<=radius;x++)
        {
            for (int y=-radius;y<=radius;y++)
            {
                if (abs(x)+abs(y)<=radius)
                    addToVector(area,gx+x,gy+y);
            }
        }
        return area;
    }
    //this is a modified bresenham circle algorithm
    //instead of painting the eight edges, it paints every point from 
    // px=0 to px=x on each y
    //it has to avoid overlap in case the color is translucent
    int x=radius,y=1;
    int slopeTracker=1-radius;
    double internalSquareRad;
    internalSquareRad=(radius)/1.41421356   +.25;
    //the radius of a square touching a circle on all four points is r/√2
    //the overlap of the fill-modified bresenham algorithm is a cocentric square in the center
    //to avoid the overlap, dont color the reflection inside of this square
    while (x>=y)
    {
        for (int fillX=1;fillX<=x;fillX++)
        {
            addToVector(area,gx+fillX,gy+y);
            addToVector(area,gx+fillX,gy-y);
            addToVector(area,gx-fillX,gy+y);
            addToVector(area,gx-fillX,gy-y);
            //reflect along y=x 
            if (fillX>internalSquareRad)
            {//avoid overlap
                addToVector(area,gx+y,gy+fillX);
                addToVector(area,gx-y,gy+fillX);
                addToVector(area,gx+y,gy-fillX);
                addToVector(area,gx-y,gy-fillX);
            }
        }
        ++y;
        if (slopeTracker<0)
           slopeTracker+=2*y +1;
        else
        {
            --x;
            //devil magic involving calculus
            slopeTracker+=2*(y-x+1);
        }
    }
    for (int y=1;y<=radius;++y)
    {//previous loop skips center lines to avoid overlap
        addToVector(area,gx+y,gy);
        addToVector(area,gx,gy+y);
        addToVector(area,gx-y,gy);
        addToVector(area,gx,gy-y);
    }
    //center-line-loop skips center to avoid overlap
    addToVector(area,gx,gy);
    return area;
}

//vector<Square*>* Grid::getSquaresInRadius(int radius)
/*
{
    if (isError())
    {
        cout<<" getSquaresInRadius called on squerror. wat\n";
    }
    double sqrdRad=radius*radius;
    vector<Square*>* area=getSquareOfSquares(this,radius);
    for (int n=0;n<area->size();n++)
    {
        if (Util::sqrdDist(this,area->at(n))>sqrdRad)
        {
            area->erase(area->begin()+n);
            n--;
        }
    }
    return area;
}
 */
float Grid::getChunkElevation(int xFrom, int yFrom, int xTo, int yTo)
{
    float total=0;
    int amt=0;
    for (int y=yFrom;y<=yTo;++y)
    {
        if (xFrom<=xTo)
        {
            for (int x=xFrom;x<=xTo;++x)
            {
                ++amt;
                total+=getSquare(x,y)->getTerrain()->getElevation();
            }
        }
        else
        {
            for (int x=0;x<=xTo;++x)
            {
                ++amt;
                total+=getSquare(x,y)->getTerrain()->getElevation();
            }
            for (int x=xFrom;x<xAmt;++x)
            {
                ++amt;
                total+=getSquare(x,y)->getTerrain()->getElevation();
            }
        }
    }
    return total/float(amt);
}
void Grid::changeChunkElevation(int xFrom, int yFrom, int xTo, int yTo, float amt)
{
    for (int y=yFrom;y<=yTo;++y)
    {
        if (xFrom<=xTo)
        {
            for (int x=xFrom;x<=xTo;++x)
            {
                getSquare(x,y)->getTerrain()->changeElevation(amt);
            }
        }
        else
        {
            for (int x=0;x<=xTo;++x)
            {
                getSquare(x,y)->getTerrain()->changeElevation(amt);
            }
            for (int x=xFrom;x<xAmt;++x)
            {
                getSquare(x,y)->getTerrain()->changeElevation(amt);
            }
        }
    }
}
//static square-getter functions
Square* Grid::get(int x,int y)
{
    if (inBounds(x,y))
        return grid[x][y];
    else return squerror;
}
int Grid::getGridXByPixel(int px)
{
    return mod(px-Gui::minPx -xPixelOffset,totalXPixels())/Square::squareSize;
}
int Grid::getGridYByPixel(int py)
{
    return (py-Gui::minPy - yPixelOffset)/Square::squareSize;;
}
Square* Grid::getSquareByConformedPixel(int px, int py)
{
    return getSquareByPixel(screenConformX(px),screenConformY(py));
}
Square* Grid::getSquareByPixel(int px, int py)
{
    return getSquare(getGridXByPixel(px),getGridYByPixel(py));
}
Square* Grid::getNrstValidSquare(int px, int py)
{
    int gx=getGridXByPixel(px);
    int gy=getGridYByPixel(py);
    if (gx>=xAmt)
        gx=xAmt-1;
    else if (gx<0)
        gx=0;
    if (gy>=yAmt)
        gy=yAmt-1;
    else if (gy<0)
        gy=0;
    return getSquare(gx,gy);
}
Square* Grid::getRandSquare()
{
    return grid[rand()%xAmt][rand()%yAmt];
}
//static set functions
void Grid::changePixelXOffset(int amt)
{
    Gui::requireGlobalRedraw();
    xPixelOffset+=amt;
    int totalXPix=totalXPixels();
    xPixelOffset=mod(xPixelOffset,totalXPix);
    int px=Gui::minPx+xPixelOffset;
    int seam=totalXPix+Gui::minPx;
    for (int x=0;x<xAmt;x++)
    {
        for (int y=0;y<yAmt;y++)
        {
            grid[x][y]->pixX=px;
        }
        px+=Square::squareSize;
        if (px>seam)
            px-=totalXPix;
    }
}
void Grid::changePixelYOffset(int amt)
{
    if (yPixelOffset>-amt)
        amt=-yPixelOffset;
    Util::ensureAbove(amt,Gui::maxPy-Gui::minPx-totalYPixels()
            -Square::squareSize-yPixelOffset);
    Util::ensureBelow(amt,-Gui::minPx+totalYPixels()+yPixelOffset);
    if (amt==0)
        return;
    Gui::requireGlobalRedraw();
    yPixelOffset+=amt;
    for (int x=0;x<xAmt;x++)
    {
        for (int y=0;y<yAmt;y++)
        {
            grid[x][y]->pixY+=amt;
        }
    }
}
void Grid::setSquareSize(int set)
{
    Square::squareSize=set;
    boundScreenSize();
    Square::halfSquareSize=Square::squareSize>>1;
    Square::quarterSquareSize=Square::squareSize>>2;
    adjustScreenForResize();
    
    Gui::requireGlobalRedraw();
    Event::requireGuiRedraw();
}
void Grid::changeSquareSize(int delta)
{
    int origSIZE=Square::squareSize;
    Square::squareSize+=delta;
    boundScreenSize();
    if (Square::squareSize==origSIZE) return;
    Square::halfSquareSize=Square::squareSize>>1;
    Square::quarterSquareSize=Square::squareSize>>2;
    movePixelOffsetsForScreenResize(origSIZE);
    adjustScreenForResize();
    
    Gui::requireGlobalRedraw();
    Event::requireGuiRedraw();
}
void Grid::movePixelOffsetsForScreenResize(int prevSize)
{
    double ratio=double(Square::squareSize)/double(prevSize);
    int midScreenX=pixWidth()/2;
    xPixelOffset=ratio*(xPixelOffset-midScreenX) +midScreenX;
    int midScreenY=pixHeight()/2;
    yPixelOffset=ratio*(yPixelOffset-midScreenY) +midScreenY;
//    cout<<"xPixOff="<<xPixelOffset<<" yPixOff="<<yPixelOffset<<endl;
    Util::ensureAbove(yPixelOffset,Gui::maxPy-Gui::minPx-totalYPixels()-Square::squareSize);
}
void Grid::boundScreenSize()
{//TODO: MOVE INTO GUI NAMESPACE
    Util::ensureAbove(Square::squareSize,2);
    Util::ensureBelow(Square::squareSize,55);
    int minXSize=(Gui::maxPx-Gui::permMinPx)/xAmt;
    int minYSize=(Gui::maxPy-Gui::permMinPy)/yAmt;
    if (minYSize>minXSize)
        Util::ensureAbove(Square::squareSize,minXSize);
    else
        Util::ensureAbove(Square::squareSize,minYSize);
    if (Square::squareSize<minXSize || Gui::minPx>Gui::permMinPx)
    {
        int blackSpace=(Gui::maxPx-Gui::permMinPx)-Square::squareSize*xAmt;
        blackSpace/=2;
        int deltaMin=-Gui::minPx;
        Gui::minPx=Gui::permMinPx+blackSpace;
        deltaMin+=Gui::minPx;
        int width=totalXPixels();
        for (int x=0;x<xAmt;++x)
        {
            for (int y=0;y<yAmt;++y)
            {
//TODO BUG: only auto adjusts on maximum zoom out
                getSquare(x,y)->pixX+=deltaMin;
                if (getSquare(x,y)->pixX<Gui::minPx+xPixelOffset) {
                    getSquare(x,y)->pixX+=width;
                }
            }
        }
    }
    if (Square::squareSize<minYSize)
    {
        int blackSpace=pixHeight()-Square::squareSize*yAmt;
        blackSpace/=2;
        Gui::minPy+=blackSpace;
//TODO: adjust py values (if neccessary)
    }
}
void Grid::adjustScreenForResize()
{
    int totalXPix=totalXPixels();
    int px=(Gui::minPx+xPixelOffset);
    while (px>totalXPix)
        px-=totalXPix;
    for (int x=0;x<xAmt;++x)
    {
        int py=Gui::minPy+yPixelOffset;
        for (int y=0;y<yAmt;++y)
        {
            grid[x][y]->pixX=px;
            grid[x][y]->pixY=py;
            py+=Square::squareSize;
        }
        px+=Square::squareSize;
        if (px>totalXPix)
            px-=totalXPix;
    }
}
bool Grid::onScreen(int px, int py)
{
    if (px<Gui::minPx)
        return false;
    if (px>Gui::maxPx)
        return false;
    if (py<Gui::minPy)
        return false;
    if (py>Gui::maxPy)
        return false;
    return true;
}
int Grid::validizeY(int y)
{
    if (y<0) y=0;
    if (y>=yAmt) y=yAmt-1;
    return y;
}
int Grid::validizeX(int x)
{
    if (x<0) x=0;
    if (x>=xAmt) x=xAmt-1;
    return x;
}
int Grid::screenConformY(int y)
{
    if (y<Gui::minPy) y=Gui::minPy;
    if (y>Gui::maxPy) y=Gui::maxPy;
    return y;
}
int Grid::screenConformX(int x)
{
    if (x<Gui::minPx) x=Gui::minPx;
    if (x>Gui::maxPx) x=Gui::maxPx;
    return x;
}
int Grid::totalXPixels() {
    return (xAmt)*Square::squareSize;
}
int Grid::totalYPixels() {
    return (yAmt)*Square::squareSize;
}
int Grid::wrapX(int x)
{
    if (!Earth::wraparound) return validizeX(x);
    else
    {
        if (x<0 || x>=xAmt)
            return mod(x,xAmt);
        else return x;
    }
}
int Grid::screenWrapX(int px)
{
    if (!Earth::wraparound) return px;
    else
    {
        int xWidth=pixWidth();
        while (px<Gui::minPx)
            px+=xWidth;
        while (px>Gui::maxPx)
            px-=xWidth;
        return px;
    }
}
