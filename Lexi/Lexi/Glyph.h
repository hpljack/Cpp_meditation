#include "Window.h"
class Point{
public:
	Point(int xx, int yy):x(xx),y(yy){}
private:
	int x, y;
};
class Rect{

};
/*
 * ³éÏóÍ¼Ôª
*/
class Glyph{
public:
	virtual void Draw(Window*);
	virtual void Bounds(Rect&);
	virtual bool Intersects(const Point&);
	virtual void Insert(Glyph*, int);
	virtual void Remove(Glyph*);
	virtual Glyph* Child(int);
	virtual Glyph* Parent();
};

class Character: public Glyph{
public:
	virtual void Draw(Window*);
	virtual void Bounds(Rect&);
	virtual bool Intersects(const Point&);
	virtual void Insert(Glyph*, int);
	virtual void Remove(Glyph*);
	virtual Glyph* Child(int);
	virtual Glyph* Parent();
};
