namespace KI
{
namespace Topology
{
void DownSamplingOperator::SetVertexOfCluster()
{
	assert(m_pInstance != nullptr);
	auto pResolution = m_pInstance->m_pResolution;
	auto pHalfEdgeDS = m_pInstance->m_pHalfEdgeDS;
	for (int level = 0; level < pResolution.size(); level++) {

		if (level == 0) {
			std::vector<DownSampling::SampleData> datas;
			datas.resize(pHalfEdgeDS->VertexList().size());
			for (int i = 0; i < pHalfEdgeDS->VertexList().size(); i++) {
				DownSampling::SampleData data(i);
				data.Set(i,
					pHalfEdgeDS->VertexList()[i]->Position(),
					pHalfEdgeDS->VertexList()[i]->Normal(),
					pHalfEdgeDS->VertexList()[i]->Area());
				datas.push_back(data);
			}
		}
		else
		{
			auto pCurrent = pResolution[level];	// ex : 1
			if (pCurrent == NULL) {
				return;
			}
			for (int i = 0; i < pCurrent->GetClusterNum(); i++)
			{
				std::vector<DownSampling::SampleData> datas;
				for (int j = 0; j < pCurrent->GetBranchNum(); j++)
				{
					int _upper = pCurrent->GetToUpper(i, j);
					if (AdjancyMatrix::Link::INVALID == _upper)
						continue;
					SetVertexOfClusterRecursive(level - 1, _upper, &datas);
				}
			}
		}
	}
}

void DownSamplingOperator::GetData(int level, std::vector<vec3>* position, std::vector<vec3>* normal, std::vector<vec3>* tangent, std::vector<vec3>* quadPos)
{
	auto pResolution = m_pInstance->m_pResolution[level];
	if (position)
		position->resize(pResolution->GetClusterNum());
	if (normal)
		normal->resize(pResolution->GetClusterNum());
	if(tangent)
		tangent->resize(pResolution->GetClusterNum());
	if(quadPos)
		quadPos->resize(pResolution->GetClusterNum());
	
	for (int i = 0; i < pResolution->GetClusterNum(); i++)
	{
		if (position)
			(*(position))[i] = (pResolution->GetData(i)->Position());
		if (normal)
			(*(normal))[i] = (pResolution->GetData(i)->Normal());
		if (tangent)
			(*(tangent))[i] = (pResolution->GetData(i)->Tangent());
		if(quadPos)
			(*(quadPos))[i] = (pResolution->GetData(i)->QuadPosition());
	}
}
void DownSamplingOperator::SetVertexOfClusterRecursive(int level, int upper, std::vector<DownSampling::SampleData>* datas)
{
	assert(m_pInstance != nullptr);
	auto pResolution = m_pInstance->m_pResolution;
	auto pHalfEdgeDS = m_pInstance->m_pHalfEdgeDS;
	if (level == 0) {
		assert(datas != nullptr);
		DownSampling::SampleData data(upper);
		data.Set(upper,
			pHalfEdgeDS->VertexList()[upper]->Position(),
			pHalfEdgeDS->VertexList()[upper]->Normal(),
			pHalfEdgeDS->VertexList()[upper]->Area());
		datas->push_back(data);
	}
	else
	{
		auto pCurrent = pResolution[level];	// ex : 0
		for (int j = 0; j < pCurrent->GetBranchNum(); j++)
		{
			int _upper = pCurrent->GetToUpper(upper, j);
			if (AdjancyMatrix::Link::INVALID == _upper)
				continue;
			SetVertexOfClusterRecursive(level - 1, _upper, datas);
		}
	}
}
void DownSamplingOperator::GetCluster(int level, std::vector<int>& index)
{
	assert(m_pInstance != nullptr);
	auto pResolution = m_pInstance->m_pResolution;
	auto pHalfEdgeDS = m_pInstance->m_pHalfEdgeDS;
	index.resize(pHalfEdgeDS->VertexList().size());
	if (level == pResolution.size()) {
		return;
	}
	if (level == 0) {
		for (int i = 0; i < pHalfEdgeDS->VertexList().size(); i++) {
			index[i] = i;
		}
	}
	else
	{
		auto pCurrent = pResolution[level];	// ex : 1
		if (pCurrent == NULL) {
			return;
		}
		int clusterIndex = 0;
		for (int i = 0; i < pCurrent->GetClusterNum(); i++)
		{
			for (int j = 0; j < pCurrent->GetBranchNum(); j++)
			{
				int _upper = pCurrent->GetToUpper(i, j);
				if (AdjancyMatrix::Link::INVALID == _upper)
					continue;
				GetClusterRecursive(level - 1, _upper, clusterIndex, index);
			}
			clusterIndex++;
		}
	}
}

void DownSamplingOperator::GetClusterRecursive(int level, int upper, int clusterIndex, std::vector<int>& index)
{
	assert(m_pInstance != nullptr);
	if (level == 0) {
		index[upper] = clusterIndex;
	}
	else
	{
		auto pCurrent = m_pInstance->m_pResolution[level];	// ex : 0
		for (int j = 0; j < pCurrent->GetBranchNum(); j++)
		{
			int _upper = pCurrent->GetToUpper(upper, j);
			if (AdjancyMatrix::Link::INVALID == _upper)
				continue;
			GetClusterRecursive(level - 1, _upper, clusterIndex, index);
		}
	}
}

}
}
