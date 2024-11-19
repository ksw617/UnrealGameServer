#pragma once
template <typename T>
class Singleton
{
protected:
	Singleton() = default;
	~Singleton() = default;
public:
	static T& Get()
	{
		static T instance;
		return instance;
	}
public:
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
};