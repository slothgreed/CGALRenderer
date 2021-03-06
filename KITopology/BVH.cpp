namespace KI
{
namespace Topology
{

BVH::BVH()
{
}

BVH::~BVH()
{
	RELEASE_INSTANCE(m_root.m_left);
	RELEASE_INSTANCE(m_root.m_right);
}


void BVH::MakeTriangleList(const vector<vec3>& positions, const vector<int>& indexs)
{
	TriangleIterator itr(TriangleIterator::TriangleType::TRIANGLES, positions.data(), indexs.data(), (int32_t)indexs.size());
	vec3 pos0, pos1, pos2;
	m_triangles.resize(itr.TriangleSize());
	while (itr.HasNext())
	{
		itr.Current(&pos0, &pos1, &pos2);
		m_triangles[itr.Index()].SetPosition(pos0, pos1, pos2);
		itr.Next();
	}
}

void BVH::CalculateRoot()
{
	m_root.m_Index = 0;
	m_root.m_triangleIndex.resize(m_triangles.size());
	for (int i = 0; i < m_triangles.size(); i++) {
		m_root.m_triangleIndex[i] = i;
	}

	vec3 pos0, pos1, pos2;
	for (int i = 0; i < m_root.m_triangleIndex.size(); i++) {
		m_triangles[m_root.m_triangleIndex[i]].GetPosition(&pos0, &pos1, &pos2);
		m_root.m_bdb.Apply(pos0);
		m_root.m_bdb.Apply(pos1);
		m_root.m_bdb.Apply(pos2);
	}
}
void BVH::Calculate(const vector<vec3>& positions, const vector<int>& indexs)
{
	MakeTriangleList(positions, indexs);
	CalculateRoot();
	CalculateRecursive(&m_root, 0);
}

void BVH::CalculateRecursive(BVH::Node* pNode, int axis)
{
	CalculateBDB(pNode);
	if (pNode->m_triangleIndex.size() <= 1) {
		// 終了条件
		return;
	}

	pNode->m_left = new BVH::Node();
	pNode->m_right = new BVH::Node();
	pNode->m_left->m_Index = pNode->m_Index + 1;
	pNode->m_right->m_Index = pNode->m_Index + 1;

	for (int i = 0; i < pNode->m_triangleIndex.size(); i++) {
		int index = pNode->m_triangleIndex[i];
		vec3 gravity = m_triangles[index].Gravity();
		if (axis == 0)	// x 軸
		{
			if (gravity.x < pNode->m_bdb.Center().x) {
				pNode->m_left->m_triangleIndex.push_back(index);
			}
			else {
				pNode->m_right->m_triangleIndex.push_back(index);
			}
		}
		else if (axis == 1) { // y 軸
			if (gravity.y < pNode->m_bdb.Center().y) {
				pNode->m_left->m_triangleIndex.push_back(index);
			}
			else {
				pNode->m_right->m_triangleIndex.push_back(index);
			}
		}
		else if (axis == 2) {  // z 軸
			if (gravity.z < pNode->m_bdb.Center().z) {
				pNode->m_left->m_triangleIndex.push_back(index);
			}
			else {
				pNode->m_right->m_triangleIndex.push_back(index);
			}
		}
	
		if (pNode->m_left->m_triangleIndex.size() == pNode->m_triangleIndex.size() ||
			pNode->m_right->m_triangleIndex.size() == pNode->m_triangleIndex.size()) {
			// 分割できなかった場合は単純に分ける
			pNode->m_left->m_triangleIndex.clear();
			pNode->m_right->m_triangleIndex.clear();
			for (int i = 0; i < pNode->m_triangleIndex.size(); i++) {
				int index = pNode->m_triangleIndex[i];
				if (i < pNode->m_triangleIndex.size() / 2) {
					pNode->m_left->m_triangleIndex.push_back(index);
				}
				else {
					pNode->m_right->m_triangleIndex.push_back(index);
				}
			}
		}
	}



	// x,y,z,x,y,z の順で再帰的に実行
	CalculateRecursive(pNode->m_left, (axis + 1) % 3);
	CalculateRecursive(pNode->m_right, (axis + 1) % 3);

}

void BVH::CalculateBDB(BVH::Node* pNode)
{
	vec3 pos0, pos1, pos2;
	for (int i = 0; i < pNode->m_triangleIndex.size(); i++) {
		m_triangles[pNode->m_triangleIndex[i]].GetPosition(&pos0, &pos1, &pos2);
		pNode->m_bdb.Apply(pos0);
		pNode->m_bdb.Apply(pos1);
		pNode->m_bdb.Apply(pos2);
	}
}

void BVH::GetBVHBoundingBox(int level, std::vector<BDB>& bdbs)
{
	GetBVHBoundingBoxRecursive(&m_root, level, bdbs);
}

void BVH::GetBVHBoundingBoxRecursive(Node* pNode, int level, std::vector<BDB>& bdbs)
{
	if (pNode->m_Index == level) {
		bdbs.push_back(pNode->m_bdb);
		return;
	}

	GetBVHBoundingBoxRecursive(pNode->m_left, level, bdbs);
	GetBVHBoundingBoxRecursive(pNode->m_right, level, bdbs);
}


}
}