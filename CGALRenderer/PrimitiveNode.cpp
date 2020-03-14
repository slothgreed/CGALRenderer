
namespace KI
{
PrimitiveNode::PrimitiveNode(shared_ptr<DefaultVertexBuffer> buffer)
{
	m_name = "Primitive";
	m_pVertexBuffer = buffer;
	m_pMaterial = make_shared<DefaultMaterial>();
}

PrimitiveNode::~PrimitiveNode()
{
}

void PrimitiveNode::Draw()
{
	if (m_pState != nullptr)
	{
		m_pState->Bind();
	}

	m_pMaterial->Draw(m_pVertexBuffer.get());

	if (m_pState != nullptr)
	{
		m_pState->UnBind();
	}

	Logger::GLError();
}


void PrimitiveNode::Update(void* sender, IEventArgs* args)
{

}

void PrimitiveNode::ShowProperty()
{

}
}
