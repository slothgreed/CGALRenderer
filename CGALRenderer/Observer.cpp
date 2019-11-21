namespace KI
{
ISubject::ISubject()
{
}

ISubject::~ISubject()
{
}

void ISubject::AddObserver(IObserver* observer)
{
	m_observer.push_back(observer);
}

void ISubject::RemoveObserver(IObserver* observer)
{
	auto itr = find(m_observer.begin(), m_observer.end(), observer);
	m_observer.erase(itr);
}

void ISubject::Update()
{
	for (int i = 0; i < m_observer.size(); i++)
	{
		m_observer[i]->Update(this, make_shared<EventArgs>());
	}
}

void ISubject::Clear()
{
	m_observer.clear();
}
}