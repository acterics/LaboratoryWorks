#ifndef Voronoi_h
#define Voronoi_h

#include <list>
#include <queue>
#include <set>
#include <fstream>
#include "VPoint.h"
#include "VEdge.h"
#include "VParabola.h"
#include "VEvent.h"
#include <functional>
#include <windows.h>

#pragma warning(disable : 4703)

namespace vor
{


	typedef std::list<VPoint *>		Vertices	;
	typedef std::list<VEdge *>		Edges		;



	class Voronoi
	{
	public:
		


		Voronoi();


		Vertices *		generate(int count, int w, int h);
		Vertices *		init(std::string filePath, int w, int h);
		Edges *			GetEdges(Vertices * v, int w, int h);
		void			drawLine(HDC hdc, VPoint * begin, VPoint * end);
		void			drawDiagram(HDC hdc, Edges * edges);

	private:



		Vertices *		places;
		Edges *			edges;
		double			width, height;
		VParabola *		root;
		double			ly;



		std::set<VEvent *>	deleted;
		std::list<VPoint *> points;
		std::priority_queue<VEvent *, std::vector<VEvent *>, VEvent::CompareEvent> queue;



		void		InsertParabola(VPoint * p);
		void		RemoveParabola(VEvent * e);
		void		FinishEdge(VParabola * n);
		double		GetXOfEdge(VParabola * par, double y);
		VParabola * GetParabolaByX(double xx);
		double		GetY(VPoint * p, double x);
		void		CheckCircle(VParabola * b);
		VPoint *	GetEdgeIntersection(VEdge * a, VEdge * b);
	};
}

#endif