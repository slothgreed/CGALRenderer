#ifndef CGAL_LINEAR_CELL_COMPLEX_H
#define CGAL_LINEAR_CELL_COMPLEX_H
namespace KI
{
namespace Asset
{
class DLL_EXPORT CGALLinearCellComplex : public ExtLibsModel
{
public:
	CGALLinearCellComplex();
	~CGALLinearCellComplex();

	virtual MODEL_TYPE Type() override { return MODEL_TYPE::MODEL_TYPE_CGAL_LINEARCELLCOMPLEX; };
	virtual void Load(const std::string& filePath);
	virtual void GenSampleModel();
	virtual void GetFacetList(std::vector<vec3>& position, std::vector<vec3>& normal);
	virtual void GetEdgeList(std::vector<vec3>& edgeList);
	virtual void GetPositionList(std::vector<vec3>& position);
	virtual void GetBDB(BDB& bdb);
private:

};
}
}
#endif CGAL_LINEAR_CELL_COMPLEX_H