#pragma once
#include <algorithm>
#include <list>
#include <functional>

using namespace std;
template<class T>
class Node
{
public:
	Node(T v)
		:value(v)
	{}
	Node(T v, Node* p)
		: value(v), parent(p)
	{}
	void updateF()
	{
		f = g + h;
	}

	operator T() const { return value; }
	bool operator==(const T& v) const { return value == v; }
	bool operator==(const Node& n) const { return value == n.value; }

	Node* parent = nullptr;

	T value;
	double f = 0.0;
	double g = 0.0;
	double h = 0.0;

};
template<class T>
class PathFinder
{
public:

	PathFinder()
	{
	}
	PathFinder(function<list<T>(T)> getAdjacentNodes, function<bool(T)> isWalkable, function<double(T, T)> heuristic)
		: _getAdjacentNodes(getAdjacentNodes), _isWalkable(isWalkable), _heuristic(heuristic)
	{

	}

	virtual ~PathFinder()
	{
	}

	list<T> getPathAStar(T from, T to)
	{
		if (!_isWalkable(to))
			return list<T>();
		Node<T> first(from);
		Node<T> last(to);

		list<Node<T>*> openList;
		list<Node<T>*> closedList;

		// push the first Node<T> into the openlist
		openList.push_back(&first);

		while (!openList.empty())
		{
			// selecting the Node<T> with the lower F and set it as the current Node<T>
			Node<T>* currentNode = openList.front();
			double m = currentNode->f;
			for (Node<T>* n : openList)
			{
				if (n->f < m)
				{
					m = n->f;
					currentNode = n;
				}
			}
			
			// switch it to the closed list
			closedList.push_back(currentNode);
			openList.remove(currentNode);

			// if it is the target Node<T> then we are arrived; stop
			if (*currentNode == last)
				break;

			// get all the adjacent T and build a list of Node<T>s from it
			list<T> adj = _getAdjacentNodes(*currentNode);
			list<Node<T>*> adjacentNodes;
			for (T& a : adj)
			{
				adjacentNodes.push_back(new Node<T>(a));
			}
			// for each adjacent Node<T>
			for (Node<T>* node : adjacentNodes)
			{
				// if it is on the closed list ignore it
				if (find_if(closedList.begin(), closedList.end(), [&](Node<T>* n){return *n == *node; }) != closedList.end())
					continue;
				// if we can't go there ignore it
				else if (!_isWalkable(*node))
					continue;
				//LOGINFO << "Exploring " << node->value << endl;
				// else
				// if it isn't in the openlist
				auto it = find_if(openList.begin(), openList.end(), [&](Node<T>* n){return *n == *node; });
				if (it == openList.end())
				{
					// update the parent and set it on the openlist
					node->parent = currentNode;
					node->g = currentNode->g + 1;
					node->h = _heuristic(*node, to);
					node->updateF();
					openList.push_back(node);
				}
				// else if it is in the openlist and we found a better path
				else if ((*it)->g > node->g)
				{
					// update the Node<T> in the openlist
					(*it)->parent = currentNode;
					(*it)->g = currentNode->g + 1;
					// h should be already calculated
					(*it)->updateF();
				}
				


			}

		}

		return buildPath(closedList.back());
	}

	list<T> buildPath(Node<T>* last)
	{
		list<T> ret;
		ret.push_front(*last);
		while (last->parent != nullptr)
		{
			last = last->parent;
			ret.push_front(*last);
		}
		ret.pop_front();
		return ret;
	}
private:
	function<list<T>(T)> _getAdjacentNodes;
	function<bool(T)> _isWalkable;
	function<double(T, T)> _heuristic;
};

