#ifndef IMODEL_H
#define IMODEL_H

class IModel : public ISubject
{
public:
	IModel();
	~IModel() {};
	virtual void Load(const std::string& filePath) = 0;
	virtual void GetFacetList(std::vector<vec3>& position, std::vector<vec3>& normal) = 0;
	virtual void GetEdgeList(std::vector<vec3>& edgeList) = 0;
	virtual void GetVertexList(std::vector<vec3>& position) = 0;
	virtual void GetBDB(BDB& bdb) = 0;

protected:
	void SetBDB(BDB bdb);
private:
	BDB m_bdb;
};

#endif IMODEL_H