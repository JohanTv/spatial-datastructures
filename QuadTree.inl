#include "QuadTree.h"
#include <memory>
#include <iostream>
#include <vector>

namespace utec
{
namespace spatial
{

template<typename Node, typename Rectangle, typename Point>
QuadTree<Node, Rectangle, Point>::QuadTree(){
    this->root=nullptr;
}

template<typename Node, typename Rectangle, typename Point>
void QuadTree<Node, Rectangle, Point>::insert(Point new_point){
    std::shared_ptr<Node>& target = search(new_point, this->root);
    if(target==nullptr){
        target=std::make_shared<Node>(new_point);
    }
}

template<typename Node, typename Rectangle, typename Point>
std::shared_ptr<Node>& QuadTree<Node, Rectangle, Point>::search(Point target, std::shared_ptr<Node>& node){
    if(node == nullptr){
        return node; //not found
    } else if(node->get_point() == target){
        return node;
    }
    
    auto cur_point = node->get_point();

    const int x=0, y=1;

    if(target.get(x) < cur_point.get(x)){
        if(target.get(y) > cur_point.get(y))
            return search(target, node->NW());
        else
            return search(target, node->SW());
    }else{
        if(target.get(y) > cur_point.get(y))
            return search(target, node->NE());
        else
            return search(target, node->SE());
    }
}

template<typename Node, typename Rectangle, typename Point>
std::vector<Point> QuadTree<Node, Rectangle, Point>::range(Rectangle region, std::shared_ptr<Node>& node){
    if(node == nullptr)
        return std::vector<Point>();
    if(region.isInside(node->get_point())){
        std::vector<Point> points = {node->get_point()};
        auto pointsNW = range(region, node->NW());
        auto pointsNE = range(region, node->NE());
        auto pointsSW = range(region, node->SW());
        auto pointsSE = range(region, node->SE());
        points.insert(points.end(), pointsNW.begin(), pointsNW.end());
        points.insert(points.end(), pointsNE.begin(), pointsNE.end());
        points.insert(points.end(), pointsSW.begin(), pointsSW.end());
        points.insert(points.end(), pointsSE.begin(), pointsSE.end());
        return points;
    }else{
        const int x=0, y=1;
        std::vector<Point> points;

        if(node->get_point().get(x) <= region._max.get(x) && node->get_point().get(y) < region._max.get(y)){
            auto pointsNE = range(region, node->NE());
            points.insert(points.begin(), pointsNE.begin(), pointsNE.end());
            if(region._min.get(x) < node->get_point().get(x)){
                auto pointsNW = range(region, node->NW());
                points.insert(points.begin(), pointsNW.begin(), pointsNW.end());
            }else if(region._min.get(y) <= node->get_point().get(y)){
                auto pointsSE = range(region, node->SE());
                points.insert(points.begin(), pointsSE.begin(), pointsSE.end());
            }
        }else if(region._max.get(x) < node->get_point().get(x) && node->get_point().get(y) < region._max.get(y)){
            auto pointsNW = range(region, node->NW());
            points.insert(points.begin(), pointsNW.begin(), pointsNW.end());
            if(region._min.get(y) <= node->get_point().get(y)){
                auto pointsSW = range(region, node->SW());
                points.insert(points.begin(), pointsSW.begin(), pointsSW.end());
            }
        }else if(region._min < node->get_point()){
            auto pointsSW = range(region, node->SW());
            points.insert(points.begin(), pointsSW.begin(), pointsSW.end());
            if(node->get_point().get(x) <= region._max.get(x)){
                auto pointsSE = range(region, node->SE());
                points.insert(points.begin(), pointsSE.begin(), pointsSE.end());
            }
        }else{
            auto pointsSE = range(region, node->SE());
            points.insert(points.begin(), pointsSE.begin(), pointsSE.end());
        }
        return points;
    }
}

template<typename Node, typename Rectangle, typename Point>
std::shared_ptr<Node> QuadTree<Node, Rectangle, Point>::search(Point target){
    return search(target, this->root);
}

template<typename Node, typename Rectangle, typename Point>
std::vector<Point> QuadTree<Node, Rectangle, Point>::range(Rectangle region){
    return range(region, this->root);
}

template<typename Node, typename Rectangle, typename Point>
Point QuadTree<Node, Rectangle, Point>::nearest_neighbor(Point reference){
    // TODO
}

} //spatial
} //utec
