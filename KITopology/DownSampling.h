#ifndef DOWN_SAMPLING_HPP
#define DOWN_SAMPLING_HPP

namespace KI
{
namespace Topology
{

class DLL_EXPORT DownSampling
{
public:
	friend class DownSamplingOperator;
	class SampleData
	{
	public:
		SampleData() : m_index(0),m_area(0),m_position(vec3(1)),m_normal(vec3(1)),m_tangent(vec3(1,0,0)) {};
		SampleData(int positionNum);
		~SampleData();
		void Set(int index, const vec3& position, const vec3& normal, float area);
		void SetTangent(const vec3& tangent) { m_tangent = tangent; }
		int Index() { return m_index; }
		float Area() { return m_area; }
		vec3 Position() { return m_position; }
		vec3 Normal() { return m_normal; }
		vec3 Tangent() { return m_tangent; }
		void SetOriginal(const std::vector<SampleData>& original) { m_original = std::move(original); }
	private:
		int m_index;
		float m_area;
		vec3 m_position;
		vec3 m_normal;
		vec3 m_tangent;
		std::vector<SampleData> m_original;	// おおもとの頂点データ
	};

	// 木構造の深さ毎の情報を持つ
	class Resolution
	{
	public:
		friend class DownSampling;
		Resolution();
		~Resolution();
		SampleData* GetData(int index);
		ivec2  GetToUpper(int index);
		int  GetToUpper(int index1, int index2);

		int GetToLower(int index);
		int GetClusterNum() { return m_UpperNum; }
		int GetBranchNum() { return 2; }
		shared_ptr<AdjancyMatrix> GetAdjancyMatrix() { return m_pMatrix; }

	private:
		//	1:	     a
		//         ／　＼
		//	2:	  b      c
		//	    ／ ＼   ／＼
		//	3: d     e f    g
		//	
		int m_UpperNum;
		int m_LowerNum;
		// cube.obj;
		// to_upper : (0,1) (2,6) (3,7) (4,5)
		// to_lower : 0, 0, 1, 2, 3, 3, 1, 2
		// index    : 0, 1, 2, 3, 4, 5, 6, 7
		std::vector<ivec2> m_toUpper;  // Resolution 2 のとき a = To Detail 細かい方へのインデックス
		std::vector<int> m_toLower;	  // Resolution 2 のとき 荒い方へのインデックス
		std::vector<SampleData> m_pSampleData;	// この解像度のサンプル
		shared_ptr<AdjancyMatrix> m_pMatrix;

		void SetToUpper(int index, int value1, int value2);
		void SetToLower(int index, int value);
		void SetAdjancyMatrix(shared_ptr<AdjancyMatrix> pMatrix) { m_pMatrix = pMatrix; };
		void NewData(int positionNum, int originalPosNum);
		void FreeData();
	};

	DownSampling(HalfEdgeDS* pHalfEdgeDS);
	~DownSampling() {};
	void Generate();
	shared_ptr<DownSampling::Resolution> GetResolution(int level);
	int GetResolutionNum() { return (int)m_pResolution.size(); }
	void GetCluster(int level, std::vector<int>& index);	// original 頂点の順番
	void SetVertexOfCluster();	// 階層数×元頂点数分のデータが作成されるので重い
private:
	void InitialResolution(shared_ptr<DownSampling::Resolution> pResolution, HalfEdgeDS* pHalfEdgeDS);
	void CreateResolution(int level, shared_ptr<DownSampling::Resolution> pOrgResolution, shared_ptr<DownSampling::Resolution> pResolution);
	HalfEdgeDS* m_pHalfEdgeDS;
	vector<shared_ptr<DownSampling::Resolution>> m_pResolution;	// indexが大きいほど荒い
	
};

}
}

#endif // !DOWN_SAMPLING_HPP
