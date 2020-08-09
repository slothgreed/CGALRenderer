namespace KI
{
namespace Renderer
{
IModelNode::IModelNode()
{
	m_ModelMatrix = mat4x4(1.0);
}
IModelNode::IModelNode(shared_ptr<IModel> model)
	: IModelNode()
{
	m_pModel = model;
	m_pModel->AddObserver(this);
}

IModelNode::~IModelNode()
{
	if (m_pModel != nullptr)
	{
		m_pModel->RemoveObserver(this);
	}
}

void IModelNode::AddProperty(shared_ptr<IModelProperty> prop)
{
	auto itr = std::find_if(m_pProperty.begin(), m_pProperty.end(), 
		[&prop](shared_ptr<IModelProperty> value) {return value->Type() == prop->Type(); });
	if (itr == m_pProperty.end())
	{
		prop->Build(this);
		m_pProperty.push_back(prop);
	}
}

void IModelNode::RemoveProperty(shared_ptr<IModelProperty> prop)
{
	auto itr = std::find_if(m_pProperty.begin(), m_pProperty.end(),
		[&prop](shared_ptr<IModelProperty> value) {return value->Type() == prop->Type(); });
	if (itr != m_pProperty.end())
	{
		size_t dist = std::distance(m_pProperty.begin(), itr);
		m_pProperty.erase(m_pProperty.begin() + dist);
	}
}


void IModelNode::BindModel(shared_ptr<UniformStruct> pUniform, int index)
{
	if (pUniform != NULL)
	{
		if (pUniform->GetModel() != NULL)
		{
			pUniform->GetModel()->SetModelMatrix(m_ModelMatrix);
			pUniform->GetModel()->SetObjectId(GetPickID(index));
			pUniform->GetModel()->Bind();
		}
	}
}

void IModelNode::UnBindModel(shared_ptr<UniformStruct> pUniform, int index)
{
	if (pUniform != NULL)
	{
		if (pUniform->GetModel() != NULL)
		{
			pUniform->GetModel()->UnBind();
		}
	}
}

void IModelNode::PickDraw(shared_ptr<IShader> pShader, shared_ptr<UniformStruct> pUniform)
{
	if (m_visible == false)
	{
		return;
	}
	else
	{
		for (int i = 0; i < m_pRenderData.size(); i++)
		{
			BindModel(pUniform, i);
			m_pRenderData[i]->Draw(pShader, nullptr, pUniform);
		}

		UnBindModel(pUniform, 0);

		DrawProperty(pUniform);
	}
}

void IModelNode::Draw(shared_ptr<UniformStruct> pUniform)
{
	if (m_visible == false)
	{
		return;
	}
	else
	{
		for (int i = 0; i < m_pRenderData.size(); i++)
		{
			BindModel(pUniform, i);
			PreDraw(pUniform, i);
			m_pRenderData[i]->Draw(pUniform);
			PostDraw(pUniform, i);
		}

		UnBindModel(pUniform, 0);

		DrawProperty(pUniform);
	}
}

void IModelNode::AddRenderData(int id, shared_ptr<RenderData> pRenderData)
{
	m_pRenderData[id] = pRenderData;
}

void IModelNode::RemoveRenderData(int id, shared_ptr<RenderData> pRenderData)
{
	assert(0);
}

shared_ptr<RenderData> IModelNode::GetRenderData(int id)
{
	if (m_pRenderData[id] == NULL) {
		assert(0);
		return nullptr;
	}
	return m_pRenderData[id];
}

void IModelNode::DrawProperty(shared_ptr<UniformStruct> pUniform)
{
	for (int i = 0; i < m_pProperty.size(); i++)
	{
		m_pProperty[i]->Draw(pUniform);
	}
}

void IModelNode::Update(void* sender, IEventArgs* args)
{
	UpdateProperty();
}

void IModelNode::UpdateProperty()
{
	for (int i = 0; i < m_pProperty.size(); i++)
	{
		m_pProperty[i]->Update(this);
	}
}
}
}