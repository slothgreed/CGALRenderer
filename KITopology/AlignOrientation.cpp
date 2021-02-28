namespace KI
{
namespace Topology
{
AlignOrientation::AlignOrientation(HalfEdgeDS* pHalfEdgeDS, DownSampling* pDownSampling)
{
	m_pHalfEdgeDS = pHalfEdgeDS;
	m_pDownSampling = pDownSampling;
	SetRandomTangent();
}

AlignOrientation::~AlignOrientation()
{
}

void AlignOrientation::ClosestDirection(const vec3& tangent1, const vec3& normal1,
										const vec3& tangent2, const vec3& normal2,
										vec3* orient1, vec3* orient2)
{
	vec3 orients1[2] = { tangent1, glm::cross(tangent1,normal1) };
	vec3 orients2[2] = { tangent1, glm::cross(tangent2,normal2) };

	float maxInner = -0.0f;
	int max1 = -1;
	int max2 = -1;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			float inner = std::abs(glm::dot(orients1[i], orients2[j]));
			if (maxInner < inner) {
				max1 = i;
				max2 = j;
				maxInner = inner;
			}
		}
	}

	maxInner = glm::dot(orients1[max1], orients2[max2]);
	assert(maxInner < 1.5);

	*orient1 = orients1[max1];
	if (maxInner > 0) {
		*orient2 = orients2[max2];
	}
	else {
		*orient2 = -orients2[max2];
	}
}

void AlignOrientation::AssignLowerByUpper(int upperIndex)
{
	if (upperIndex + 1 >= m_pDownSampling->GetResolutionNum()) {
		return;
	}
	// upper�����1�K�w��(�ׂ���)�̂��̂ɔ��f����B
	int upperLevel = upperIndex;
	int lowerLevel = upperIndex + 1;
	auto pDetailRes = m_pDownSampling->GetResolution(upperLevel);
	auto pSimpleRes = m_pDownSampling->GetResolution(lowerLevel);
	for (int j = 0; j < pSimpleRes->GetClusterNum(); j++)
	{
		for (int k = 0; k < pSimpleRes->GetBranchNum(); k++)
		{
			auto index = pSimpleRes->GetToUpper(j, k);
			if (index == AdjancyMatrix::Link::INVALID) {
				continue;
			}

			auto pDetailData = pDetailRes->GetData(index);
			auto pSimpleData = pSimpleRes->GetData(j);
			vec3 tangent = glm::normalize(pSimpleData->Tangent() - pDetailData->Normal() *
					glm::dot(pSimpleData->Tangent(), pDetailData->Normal()));
			pDetailData->SetTangent(tangent);
		}
	}

}

void AlignOrientation::SetRandomTangent()
{
	auto pResolution = m_pDownSampling->GetResolution(0);
	auto pAdjancyMatrix = pResolution->GetAdjancyMatrix();
	float sum = 0;
	for (int i = 0; i < m_pHalfEdgeDS->VertexList().size(); i++)
	{
		auto pVertex = m_pHalfEdgeDS->VertexList()[i];

		vec3 end = pVertex->Edge()->End()->Position();
		vec3 vector = end - pVertex->Position();
		// By. Discrete Differential-Geometry Operators for Triangulated 2 - Manifolds 5 - 3, dij
		vec3 tangent = vector - pVertex->Normal() * glm::dot(vector, pVertex->Normal());
		tangent = glm::normalize(tangent);
		m_pHalfEdgeDS->VertexList()[i]->SetTangent(tangent);
	}

	for (int i = 0; i < pResolution->GetClusterNum(); i++)
	{
		auto pData = pResolution->GetData(i);
		pData->SetTangent(m_pHalfEdgeDS->VertexList()[i]->Tangent());
	}
}
int g_index = 0;
void AlignOrientation::Calculate(int localItrNum)
{
	assert(m_pDownSampling != NULL);

	int resolutionIndex = m_pDownSampling->GetResolutionNum() - 1;
	while (resolutionIndex >= 0)
	{
		for (int j = 0; j < localItrNum; j++)
		{
			LocalAlignment(resolutionIndex);

			int globalItr = resolutionIndex;
			while (globalItr >= 0)
			{
				AssignLowerByUpper(globalItr);
				globalItr--;
			}

			CalcErrorValue();
		}

		resolutionIndex--;
	}

	auto pResolution = m_pDownSampling->GetResolution(0);
	auto pAdjancyMatrix = pResolution->GetAdjancyMatrix();
	vector<vec3> tangents;
	for (int i = 0; i < m_pHalfEdgeDS->VertexList().size(); i++)
	{
		auto pVertex = m_pHalfEdgeDS->VertexList()[i];
		pVertex->SetTangent(pResolution->GetData(i)->Tangent());
		tangents.push_back(pVertex->Tangent());
	}


#ifdef _DEBUG
	ArrayCSVIO csvio;
	csvio.Output("C:\\Users\\stmnd\\Desktop\\Tmp\\output" + std::to_string(g_index) + ".txt", tangents);
	g_index++;
#endif
}

void AlignOrientation::LocalAlignment(int resolution)
{
	auto pResolution = m_pDownSampling->GetResolution(resolution);
	auto pAdjancyMatrix = pResolution->GetAdjancyMatrix();
	vec3 orient1;
	vec3 orient2;

	// row �� index �� cluster �� index �͓���
	for (int i = 0; i < pAdjancyMatrix->RowNum(); i++)
	{
		auto pLink1 = pAdjancyMatrix->Get(i, 0);
		int vertexIndex1 = pLink1->GetStart();
		auto pVertex1 = pResolution->GetData(vertexIndex1);
		
		float weight = 0.0f;
		vec3 tangent = pVertex1->Tangent();
		for (int j = 0; j < pAdjancyMatrix->ColumnNum(i); j++)
		{
			auto pLink2 = pAdjancyMatrix->Get(i, j);
			int vertexIndex2 = pLink2->GetEnd();
			auto pVertex2 = pResolution->GetData(vertexIndex2);

			ClosestDirection(
				tangent, pVertex1->Normal(),
				pVertex2->Tangent(), pVertex2->Normal(),
				&orient1, &orient2);
			
			tangent = orient1 * weight + orient2 * pLink2->GetWeight();
			tangent = tangent - pVertex1->Normal() * glm::dot(pVertex1->Normal(), tangent);
			weight += pLink2->GetWeight();

			assert(weight != 0.0f && pLink2->GetWeight() != 0.0f);	// tangent�̒�����0�ɂȂ�B
			tangent = glm::normalize(tangent);
		}

		if (weight > 0) {
			pVertex1->SetTangent(glm::normalize(tangent));
		}
	}

}

void AlignOrientation::CalcErrorValue()
{
	assert(m_pHalfEdgeDS != nullptr);
	auto pResolution = m_pDownSampling->GetResolution(0);
	auto pAdjancyMatrix = pResolution->GetAdjancyMatrix();
	vec3 orient1;
	vec3 orient2; 
	float sum = 0;
	for (int i = 0; i < pAdjancyMatrix->RowNum(); i++)
	{
		auto pVertex1 = pResolution->GetData(i);
		for (int j = 0; j < pAdjancyMatrix->ColumnNum(i); j++)
		{
			auto pLink = pAdjancyMatrix->Get(i, j);
			auto pVertex2 = pResolution->GetData(pLink->GetEnd());

			ClosestDirection(
				pVertex1->Tangent(), pVertex1->Normal(),
				pVertex2->Tangent(), pVertex2->Normal(),
				&orient1, &orient2);

			float angle = 0;
			float inner = glm::dot(orient1, orient2);
			if (inner >= 1) {
				angle = 0;
			}
			else
			{
				angle = MathHelper::ToAngle(glm::acos(inner));
			}

			sum += angle * angle;
		}
	}


	m_error.push_back(sum);
}
}
}


