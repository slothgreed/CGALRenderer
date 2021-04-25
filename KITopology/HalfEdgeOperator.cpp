namespace KI
{
namespace Topology
{
HalfEdgeOperator::HalfEdgeOperator()
{
}

HalfEdgeOperator::~HalfEdgeOperator()
{
}


void HalfEdgeOperator::SmoothingByGravity(HalfEdgeDS* halfEdgeDS, int loopNum)
{
	vector<vec3> gravitys(halfEdgeDS->VertexList().size());
	for (int i = 0; i < halfEdgeDS->VertexList().size(); i++)
	{
		auto pVertex = halfEdgeDS->VertexList()[i];
		VertexAroundEdgeIterator itr(pVertex.get());
		vec3 sum = vec3(0);
		int counter = 0;
		for (itr; itr.HasNext(); itr.Next())
		{
			auto pEdge = itr.Current();
			
			sum += pEdge->End()->Position();
			counter++;
		}


		gravitys[i].x = sum.x / counter;
		gravitys[i].y = sum.y / counter;
		gravitys[i].z = sum.z / counter;
	}

	for (int i = 0; i < halfEdgeDS->VertexList().size(); i++)
	{
		halfEdgeDS->VertexList()[i]->SetPosition(gravitys[i]);
	}

	halfEdgeDS->CalcElement();
}
void HalfEdgeOperator::FaceSplit(HalfEdgeDS* halfEdgeDS, shared_ptr<HalfEdgeFace> face, vec3 position)
{

}

void HalfEdgeOperator::MakeTriangle(shared_ptr<HalfEdgeFace> face,
	shared_ptr<HalfEdge> edge0,
	shared_ptr<HalfEdge> edge1,
	shared_ptr<HalfEdge> edge2,
	shared_ptr<HalfEdge> oppo0,
	shared_ptr<HalfEdge> oppo1,
	shared_ptr<HalfEdge> oppo2)
{
	//�e�X�g���ĂȂ�
	assert(0);

	face->SetEdge(edge0);

	edge0->SetFace(face);
	edge1->SetFace(face);
	edge2->SetFace(face);

	edge0->SetOpposite(oppo0);
	edge1->SetOpposite(oppo1);
	edge2->SetOpposite(oppo2);
	oppo0->SetOpposite(edge0);
	oppo1->SetOpposite(edge1);
	oppo2->SetOpposite(edge2);

	edge0->SetNext(edge1); edge1->SetNext(edge2); edge2->SetNext(edge0);
	edge0->SetBefore(edge2); edge1->SetBefore(edge0); edge2->SetBefore(edge1);

	face->Validate();
	edge0->Validate(); edge1->Validate(); edge2->Validate();
	oppo0->Validate(); oppo1->Validate(); oppo2->Validate();
}
//         v1                    v1
//    �@  �^�_ �@�@	      �@    �^|�_
//      �^  �@�_ �@           �^  |�@�_ 
//    �^<=edge  �_          �^ed  | �@ �_ 
// s  ------------ e  =>  s ------v0---- e
//    �_ oppo=> �^	        �_ �@ | op �^
//    �@�_ �@ �^	       �@ �_  |  �^
//      �@�_�^		          �@�_|�^
//         v2		              v2
//
// edge  : s -> e => s -> v0
// oppo  : e -> s => e -> v0
// edge0 : v0 -> s
// edge1 : v0 -> v2
// edge2 : v2 -> v0
// edge3 : v0 -> e
// edge4 : v0 -> v1
// edge5 : v1 -> v0
// face0 : (s,e,v2) => (s,v0,v2) 
// face1 : (e,s,v1) => (e,v0,v1)
// face2 : (...)    => (v2,v0,e)
// face3 : (...)    => (v0,s,v1)
void HalfEdgeOperator::EdgeSplit(HalfEdgeDS* halfEdgeDS, shared_ptr<HalfEdge> edge, vec3 position)
{
	size_t vertexIndex = halfEdgeDS->VertexList().size();
	auto v0 = make_shared<HalfEdgeVertex>(vertexIndex);
	

	size_t edgeIndex = halfEdgeDS->EdgeList().size();
	auto opposite = edge->Opposite();
	auto edge0 = make_shared<HalfEdge>(edgeIndex);
	auto edge1 = make_shared<HalfEdge>(edgeIndex + 1);
	auto edge2 = make_shared<HalfEdge>(edgeIndex + 2);
	auto edge3 = make_shared<HalfEdge>(edgeIndex + 3);
	auto edge4 = make_shared<HalfEdge>(edgeIndex + 4);
	auto edge5 = make_shared<HalfEdge>(edgeIndex + 5);

	size_t faceIndex = halfEdgeDS->FaceList().size();
	auto face0 = edge->Face();
	auto face1 = opposite->Face();
	auto face2 = make_shared<HalfEdgeFace>(faceIndex);
	auto face3 = make_shared<HalfEdgeFace>(faceIndex + 1);

	auto s = edge->End();
	auto e = edge->Start();
	auto v1 = edge->Next()->End();
	auto v2 = opposite->Next()->End();
	
	auto sTov1 = edge->Next();
	auto v1Toe = edge->Before();
	auto eTov2 = opposite->Next();
	auto v2Tos = opposite->Before();
	v0->SetPosition(position);
	v0->SetEdge(edge0);

	edge->SetOpposite(edge3);
	edge->SetEnd(v0);
	edge->SetNext(edge4);
	edge->SetBefore(v1Toe);
	opposite->SetOpposite(edge0);
	opposite->SetEnd(v0);
	opposite->SetNext(edge1);
	opposite->SetBefore(v2Tos);
	edge0->Set(
		s,
		sTov1,
		edge5,
		opposite,
		face3);

	edge1->Set(
		v2,
		v2Tos,
		opposite,
		edge2,
		opposite->Face());

	edge2->Set(
		v0,
		edge3,
		eTov2,
		edge1,
		face2);

	edge3->Set(
		e,
		eTov2,
		edge2,
		edge,
		face2);

	edge4->Set(
		v1,
		v1Toe,
		edge,
		edge5,
		edge->Face());

	edge5->Set(
		v0,
		edge0,
		sTov1,
		edge4,
		face3);

	face0->SetEdge(edge);
	face1->SetEdge(opposite);
	face2->SetEdge(edge2);
	face3->SetEdge(edge0);

	eTov2->SetFace(face2);
	eTov2->SetBefore(edge3);
	eTov2->SetNext(edge2);

	sTov1->SetFace(face3);
	sTov1->SetBefore(edge0);
	sTov1->SetNext(edge5);

	v1Toe->SetBefore(edge4);
	v1Toe->SetNext(edge);
	v1Toe->SetFace(face0);

	v2Tos->SetBefore(edge1);
	v2Tos->SetFace(face1);
	v2Tos->SetNext(opposite);

	v0->Validate();
	edge->Validate();
	opposite->Validate();

	eTov2->Validate();
	sTov1->Validate();
	v1Toe->Validate();
	v2Tos->Validate();

	edge0->Validate();	
	edge1->Validate();
	edge2->Validate();
	edge3->Validate();	
	edge4->Validate();	
	edge5->Validate();



	face0->Validate();
	face1->Validate();
	face2->Validate();
	face3->Validate();
	
	halfEdgeDS->AddVertex(v0);
	halfEdgeDS->AddEdge(edge0);	halfEdgeDS->AddEdge(edge1);	halfEdgeDS->AddEdge(edge2);
	halfEdgeDS->AddEdge(edge3);	halfEdgeDS->AddEdge(edge4);	halfEdgeDS->AddEdge(edge5);

	halfEdgeDS->AddFace(face2);	halfEdgeDS->AddFace(face3);

}


//         v1                    v1
//    �@  �^�_ �@�@	      �@    �^|�_
//      �^  �@�_ �@           �^  |�@�_ 
//    �^  edge=>�_          �^  ^ | �@ �_ 
// s  ------------ e  =>  s    ed | op   e
//    �_  <=op  �^	        �_ �@ | �@ �^
//    �@�_ �@ �^	       �@ �_  |  �^
//      �@�_�^		          �@�_|�^
//         v2		              v2
void HalfEdgeOperator::EdgeFlips(HalfEdgeDS* halfEdgeDS, shared_ptr<HalfEdge> edge)
{
	auto opposite = edge->Opposite();

	// ���_�����G�b�W���t���b�v�Ώۂ̏ꍇ�́A�ݒ��ύX����B
	{
		edge->Start()->SetEdge(opposite->Next());
		opposite->Start()->SetEdge(edge->Next());
	}

	auto v1 = opposite->Next()->End();
	auto v2 = edge->Before()->Start();
	
	// ��̃R�����g�̒��_ : sv1 = (s => v1)�̃G�b�W
	auto v1Tos = edge->Before();
	auto sTov2 = opposite->Next();
	auto v2Toe = opposite->Before();
	auto eTov1 = edge->Next();

	// �t���b�v�G�b�W
	{
		edge->Set(
			v2, v1Tos, sTov2,
			opposite,
			edge->Face());
		edge->Face()->SetEdge(edge);

		opposite->Set(
			v1, v2Toe, eTov1,
			edge,
			opposite->Face());
		opposite->Face()->SetEdge(opposite);
	}

	// �t���b�v�ȊO�̃G�b�W
	{
		v1Tos->SetBefore(edge);
		v1Tos->SetNext(sTov2);
		v1Tos->SetFace(edge->Face());

		sTov2->SetBefore(v1Tos);
		sTov2->SetNext(edge);
		sTov2->SetFace(edge->Face());

		v2Toe->SetBefore(opposite);
		v2Toe->SetNext(eTov1);
		v2Toe->SetFace(opposite->Face());

		eTov1->SetBefore(v2Toe);
		eTov1->SetNext(opposite);
		eTov1->SetFace(opposite->Face());
	}

	edge->Validate();
	opposite->Validate();
	v1Tos->Validate(); sTov2->Validate();
	v2Toe->Validate(); eTov1->Validate();
}

void HalfEdgeOperator::SetRandomTangentForVertex(HalfEdgeDS* halfEdgeDS)
{
	for (size_t i = 0; i < halfEdgeDS->VertexList().size(); i++)
	{
		auto pVertex = halfEdgeDS->VertexList()[i];
		vec3 normal = pVertex->Normal();
		vec3 value1;
		vec3 value2;
		if (abs(normal.x) > abs(normal.y)) 
		{
			float invLength = 1.0f / std::sqrt(normal.x * normal.x + normal.z * normal.z);
			value1 = vec3(normal.z * invLength, 0.0, -normal.x * invLength);
		}
		else
		{
			float invLength = 1.0f / std::sqrt(normal.y * normal.y + normal.z * normal.z);
			value1 = vec3(0.0, normal.z * invLength, -normal.y * invLength);
		}

		float random = Gaccho::rnd(0, 1);
		value2 = glm::cross(value1, normal);
		float angle = Gaccho::rnd(0, 1) * 2 * pi<float>();
		vec3 tangent = glm::normalize(value1 * std::cos(angle) + value2 * std::sin(angle));
		pVertex->SetTangent(tangent);
	}
}

}
}
