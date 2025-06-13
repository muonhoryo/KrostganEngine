#pragma once

#include <ICallbackRec_GraphPostRen.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;
using namespace KrostganEngine::Core;

namespace KrostganEngine::UI {
	class QuadVisPrimitive :public ICallbackRec_GraphPostRen {
	public:
		QuadVisPrimitive(Vector2f lt, Vector2f rt, Vector2f rb, Vector2f lb,
			Color edgeColor);

		FloatRect GetBounds();
		Color GetEdgeColor();

		void SetPoints(Vector2f lt, Vector2f rt, Vector2f rb, Vector2f lb);
		void SetPointsBy2Corners(Vector2f corner1, Vector2f corner2);
		void SetEdgeColor(Color edgeColor);

		void RenderGraphic(RenderWindow& window) override;

		static QuadVisPrimitive& InstanceQuad(Vector2f corner1, Vector2f corner2, Color edgeColor);
	private:
		VertexArray Vertexes;
	};

	class CircleVisPrimitive : public ICallbackRec_GraphPostRen {
	public:
		CircleVisPrimitive(Vector2f center, float radius,Color edgeColor,size_t pointsCount);

		Vector2f GetCenter();
		float GetRadius();
		Color GetEdgeColor();
		size_t GetPointsCount();

		void SetCenter(Vector2f center);
		void SetRadius(float radius);
		void SetEdgeColor(Color color);
		void SetPointsCount(size_t count);

		void RenderGraphic(RenderWindow& window) override;

	private:
		CircleShape CirShape;
	};

	class LinesVisPrimitive :public ICallbackRec_GraphPostRen {
	public:
		LinesVisPrimitive(vector<Vector2f>& pointsCoord, Color edgesColor);
		LinesVisPrimitive(vector<Vector2f>& pointsCoord, vector<Color>& edgeColors);
		virtual ~LinesVisPrimitive() {};
		
		Color GetEdgeColor(size_t index) const;
		size_t GetPointsCount() const;

		virtual void AddPoint(Vector2f point);
		virtual void RemovePointAt(size_t index);
		virtual void ReduceSize(size_t newCount);
		virtual void SetEdgeColor_AllPnts(Color color);
		virtual void SetEdgeColor(Color color, size_t index);
		virtual void SetPointPosition(Vector2f newPos, size_t pointIndex);

		void RenderGraphic(RenderWindow& window) override;

	protected:
		VertexArray Vertexes;
	};

	class WideLineVisual :public ICallbackRec_GraphPostRen {
	public:
		WideLineVisual(Vector2f Start, Vector2f End, float Width, Color LineColor);

		Vector2f GetStart() const {
			return Start;
		}
		Vector2f GetEnd() const {
			return End;
		}
		float GetWidth() const {
			return Width;
		}
		Color GetEdgeColor() const{
			return LineColor;
		}

		void SetStart(Vector2f start);
		void SetEnd(Vector2f end);
		void SetWidth(float width);
		void SetColor(Color color);

		void RenderGraphic(RenderWindow& window) override;

	private:
		Vector2f Start;
		Vector2f End;
		float Width;
		Color LineColor;
		VertexArray Vertexes;

		void Rebuild();
	};

	//class OutlineLineVisual : public LinesVisPrimitive {
	//public:
	//	enum class JointType :size_t {
	//		Angle,
	//		Cut
	//	};

	//public:
	//	OutlineLineVisual(vector<Vector2f>& pointsCoord, Color edgesColor,JointType jointType=JointType::Angle);
	//	OutlineLineVisual(vector<Vector2f>& pointsCoord, vector<Color>& edgeColors, JointType jointType = JointType::Angle);

	//	JointType GetJointType() const;
	//	size_t GetOutlinePntsCount() const;

	//	void SetJointType(JointType jntType);

	//	Color GetEdgeColor(size_t index) const override;
	//	size_t GetPointsCount() const override;

	//	void AddPoint(Vector2f point) override;
	//	void RemovePointAt(size_t index) override;
	//	void ReduceSize(size_t newCount) override;
	//	void SetEdgeColor_AllPnts(Color color) override;
	//	void SetEdgeColor(Color color, size_t index) override;
	//	void SetPointPosition(Vector2f newPos, size_t pointIndex) override;

	//	void RenderGraphic(RenderWindow& window) override;

	//private:
	//	JointType JntType;
	//	vector<Vertex> SourceLineVrtxs;

	//	void RebuildVertexes();
	//	void RebuildMids();

	//	void BuildFirstPnt();
	//	void BuildFirstPnt(Vector2f* rightOutLPnt, Vector2f* leftOutLPnt, Vector2f* segDir);

	//	void BuildLastPnt();
	//	void BuildLastPnt(Vector2f* rightOutLPnt, Vector2f* leftOutLPnt);
	//	
	//	struct MidPntBuildCashe {
	//		Vector2f ToNextPntDirection;
	//		Vector2f PrevOutLinePnt_Left;
	//		Vector2f PrevOutLinePnt_Right;
	//		Vector2f NextOutLinePnt_Left;
	//		Vector2f NextOutLinePnt_Right;
	//	};

	//	MidPntBuildCashe& GetCasheForMidPoint(size_t index) const;

	//	void BuildMidPnt(size_t index);
	//	void BuildMidPnt(size_t index, MidPntBuildCashe& cashe);
	//};
}