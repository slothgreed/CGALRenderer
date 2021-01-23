#include "BVH.h"
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
	TriangleIterator itr(TriangleIterator::TriangleType::TRIANGLES, positions.data(), indexs.data(), indexs.size());
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
		// �I������
		return;
	}
	
	pNode->m_left = new BVH::Node();
	pNode->m_right = new BVH::Node();
	bool splited = false;
	while (splited == false) {
		for (int i = 0; i < pNode->m_triangleIndex.size(); i++) {
			int index = pNode->m_triangleIndex[i];
			vec3 gravity = m_triangles[index].Gravity();
			if (axis == 0)	// x ��
			{
				if (gravity.x < pNode->m_bdb.Center().x) {
					pNode->m_left->m_triangleIndex.push_back(index);
				}
				else {
					pNode->m_right->m_triangleIndex.push_back(index);
				}
			}
			else if (axis == 1) { // y ��
				if (gravity.y < pNode->m_bdb.Center().y) {
					pNode->m_left->m_triangleIndex.push_back(index);
				}
				else {
					pNode->m_right->m_triangleIndex.push_back(index);
				}
			}
			else if (axis == 2) {  // z ��
				if (gravity.z < pNode->m_bdb.Center().z) {
					pNode->m_left->m_triangleIndex.push_back(index);
				}
				else {
					pNode->m_right->m_triangleIndex.push_back(index);
				}
			}
		}

		if (pNode->m_left->m_triangleIndex.size() != pNode->m_triangleIndex.size() &&
			pNode->m_right->m_triangleIndex.size() != pNode->m_triangleIndex.size()) {
			splited = true;
		} else {
			assert(0);
			// �����ł��Ȃ������ꍇ�͎���ς��čČv�Z
			pNode->m_left->m_triangleIndex.clear();
			pNode->m_right->m_triangleIndex.clear();
			axis = (axis + 1) % 3;
		}
	}

	// x,y,z,x,y,z �̏��ōċA�I�Ɏ��s
	CalculateRecursive(pNode->m_left, (axis + 1) % 3);
	CalculateRecursive(pNode->m_right, (axis + 1) % 3);

}

void BVH::CalculateBDB(BVH::Node* pNode)
{
	vec3 pos0, pos1, pos2;
	for (int i = 0; i < pNode->m_triangleIndex.size(); i++) {
		pNode->m_bdb.Apply(m_triangles[pNode->m_triangleIndex[i]].Gravity());
	}
}



}
}