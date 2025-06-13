//
//#include <PrimitiveVisualShapes.h>
//
//using namespace std;
//using namespace sf;
//using namespace KrostganEngine::UI;
//
//
//OutlineLineVisual::OutlineLineVisual(vector<Vector2f>& pointsCoord, Color edgesColor, JointType jointType ) : LinesVisPrimitive(pointsCoord,edgesColor),
//	JntType(jointType){
//
//	SourceLineVrtxs = vector<Vertex>(GetPointsCount());
//	RebuildVertexes();
//}
//OutlineLineVisual::OutlineLineVisual(vector<Vector2f>& pointsCoord, vector<Color>& edgeColors, JointType jointType ): LinesVisPrimitive(pointsCoord,edgeColors),
//	JntType(jointType){
//
//	SourceLineVrtxs = vector<Vertex>(GetPointsCount());
//	RebuildVertexes();
//}
//
//OutlineLineVisual::JointType OutlineLineVisual::GetJointType() const {
//	return JntType;
//}
//size_t OutlineLineVisual::GetOutlinePntsCount() const {
//	return Vertexes.getVertexCount();
//}
//
//void OutlineLineVisual::SetJointType(OutlineLineVisual::JointType jntType) {
//	if (jntType != JntType) {
//
//		JntType = jntType;
//		size_t count = GetOutlinePntsCount();
//		if (count > 2) {
//			RebuildMids();
//		}
//	}
//}
//
//Color OutlineLineVisual::GetEdgeColor(size_t index) const {
//	return SourceLineVrtxs[index].color;
//}
//size_t OutlineLineVisual::GetPointsCount() const {
//	return SourceLineVrtxs.size();
//}
//
//void OutlineLineVisual::AddPoint(Vector2f point) {
//	SourceLineVrtxs.push_back(point);
//	size_t count = GetPointsCount();
//	Vertexes.resize(GetOutlinePntsCount() + 3);
//	MidPntBuildCashe& cashe = GetCasheForMidPoint(count-2);
//	BuildMidPnt(count - 2, cashe);
//	BuildLastPnt(&cashe.NextOutLinePnt_Right, &cashe.NextOutLinePnt_Left);
//}
//void OutlineLineVisual::RemovePointAt(size_t index) {
//
//	if (index == 0)
//	{
//		vector<Vertex>::iterator beg = SourceLineVrtxs.begin();
//		vector<Vertex>::iterator end = SourceLineVrtxs.end();
//		--end;
//		++beg;
//		for (int i=0;beg != end;++beg) {
//
//			
//		}
//	}
//}
//void ReduceSize(size_t newCount) override;
//void SetEdgeColor_AllPnts(Color color) override;
//void SetEdgeColor(Color color, size_t index) override;
//void SetPointPosition(Vector2f newPos, size_t pointIndex) override;
//
//void RenderGraphic(RenderWindow& window) override;
//
//void RebuildVertexes();
//void RebuildMids();
//
//void BuildFirstPnt();
//void BuildFirstPnt(Vector2f* rightOutLPnt, Vector2f* leftOutLPnt, Vector2f* segDir);
//
//void BuildLastPnt();
//void BuildLastPnt(Vector2f* rightOutLPnt, Vector2f* leftOutLPnt);
//
//struct MidPntBuildCashe {
//	Vector2f ToNextPntDirection;
//	Vector2f PrevOutLinePnt_Left;
//	Vector2f PrevOutLinePnt_Right;
//	Vector2f ToNextPntDirection_LeftNorm;
//	Vector2f ToNextPntDirection_RightNorm;
//};
//
//MidPntBuildCashe& GetCasheForMidPoint(size_t index) const;
//
//void BuildMidPnt(size_t index);
//void BuildMidPnt(size_t index, MidPntBuildCashe& cashe);