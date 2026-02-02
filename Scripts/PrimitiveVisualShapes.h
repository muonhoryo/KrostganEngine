#pragma once

#include <ICallbackRec_GraphRen.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <_VisualEffectsCore.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine::Core;

namespace KrostganEngine::Visual {
	class QuadVisPrimitive :public ICallbackRec_GraphRen {
	public:
		QuadVisPrimitive(
			Vector2f		lt, 
			Vector2f		rt, 
			Vector2f		rb, 
			Vector2f		lb,
			Color			edgeColor,
			std::byte		RendLayer = DEFAULT_RENDLAYER_UI,
			PrimitiveType	quadType = PrimitiveType::LinesStrip,
			sf::Shader*		RenShader = nullptr);
		QuadVisPrimitive(
			Vector2f		minCorner,
			Vector2f		maxCorner,
			Color			edgeColor,
			std::byte		RendLayer = DEFAULT_RENDLAYER_UI,
			PrimitiveType	quadType = PrimitiveType::LinesStrip,
			sf::Shader*		RenShader = nullptr);

		FloatRect GetBounds();
		Color GetEdgeColor();

		void SetPoints(Vector2f lt, Vector2f rt, Vector2f rb, Vector2f lb);
		void SetPointsBy2Corners(Vector2f corner1, Vector2f corner2);
		void SetEdgeColor(Color edgeColor);

		/// <summary>
		/// Instantiate QuadVisPrimitive, based on two of its opposite corners.
		/// </summary>
		/// <param name="corner1"></param>
		/// <param name="corner2"></param>
		/// <param name="edgeColor"></param>
		/// <param name="RendLayer"></param>
		/// <returns></returns>
		static QuadVisPrimitive& InstantiateQuad(Vector2f corner1, Vector2f corner2, Color edgeColor, std::byte RendLayer = DEFAULT_RENDLAYER_UI);

	protected:

		void RenderGraphicAction(RenderWindow& window) override;

	private:
		VertexArray Vertexes;

		RenderStates RenStates;
		Shader* Shader;
	};

	class CircleVisPrimitive : public ICallbackRec_GraphRen {
	public:
		CircleVisPrimitive(
			Vector2f	center, 
			float		radius,
			Color		edgeColor,
			size_t		pointsCount,
			std::byte		RendLayer = DEFAULT_RENDLAYER_UI);

		Vector2f GetCenter();
		float GetRadius();
		Color GetEdgeColor();
		size_t GetPointsCount();

		void SetCenter(Vector2f center);
		void SetRadius(float radius);
		void SetEdgeColor(Color color);
		void SetPointsCount(size_t count);

	protected:
		void RenderGraphicAction(RenderWindow& window) override;

	private:
		CircleShape CirShape;
	};

	class LinesVisPrimitive :public ICallbackRec_GraphRen {
	public:
		LinesVisPrimitive(vector<Vector2f>& pointsCoord, Color edgesColor, std::byte	RendLayer = DEFAULT_RENDLAYER_UI);
		LinesVisPrimitive(vector<Vector2f>& pointsCoord, vector<Color>& edgeColors, std::byte RendLayer = DEFAULT_RENDLAYER_UI);
		virtual ~LinesVisPrimitive() {};
		
		Color GetEdgeColor(size_t index) const;
		size_t GetPointsCount() const;

		virtual void AddPoint(Vector2f point);
		virtual void RemovePointAt(size_t index);
		virtual void ReduceSize(size_t newCount);
		virtual void SetEdgeColor_AllPnts(Color color);
		virtual void SetEdgeColor(Color color, size_t index);
		virtual void SetPointPosition(Vector2f newPos, size_t pointIndex);


	protected:
		VertexArray Vertexes;

		void RenderGraphicAction(RenderWindow& window) override;
	};

	class WideLineVisual :public ICallbackRec_GraphRen, public IColoredObject{
	public:
		WideLineVisual(
			Vector2f	Start, 
			Vector2f	End, 
			float		Width, 
			Color		LineColor,
			std::byte		RendLayer = DEFAULT_RENDLAYER_UI);
		virtual ~WideLineVisual(){}

		Vector2f GetStart() const {
			return Start;
		}
		Vector2f GetEnd() const {
			return End;
		}
		float GetWidth() const {
			return Width;
		}
		Color GetColor() const{
			return LineColor;
		}

		void SetStart(Vector2f start);
		void SetEnd(Vector2f end);
		void SetWidth(float width);
		void SetColor(Color color);

		void RenderGraphicAction(RenderWindow& window) override;

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