#pragma once
class Modifiable
{
public:
	Modifiable();
	virtual ~Modifiable();
	virtual bool isDirty() = 0;

	virtual void setDirty(bool b = true) = 0;

protected:
	/*
	set dst to src if src != dst and set dirty.
	return true if it was different (any of the pairs)
	call it with even number of parameters only
	*/
	template<typename T, typename ...A >
	bool setIfDifferent(T& dst, const T& src, A... args)
	{
		bool ret = false;
		if (dst != src)
		{
			dst = src;
			setDirty();
			ret = true;
		}
		return setIfDifferent(args...) | ret;
	}

private:
	bool setIfDifferent() { return false; }
};

