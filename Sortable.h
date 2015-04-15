#pragma once
class Sortable
{
public:
	Sortable();
	virtual ~Sortable();
	virtual bool needSort() { return _needSort; }

	virtual bool compare(const Sortable*) const = 0;
	static bool compare(const Sortable&, const Sortable&);

	void setSorted(bool sorted = true) { _needSort = !sorted; }
protected:
	bool _needSort = true;
};

bool compare(const Sortable*, const Sortable*);
