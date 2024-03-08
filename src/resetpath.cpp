#include "resetpath.h"

ResetPath::ResetPath() {}

void ResetPath::set_edges (QObject* object, QVariant edge_color, QVariant width){
    edge.push_back(object);
    color.push_back(edge_color);
    strokeWidth.push_back(width);
}

void ResetPath::reset (){
    for (int i=0 ; i<edge.size(); i++){
        edge[i]-> setProperty("color" , color[i]);
        edge[i]-> setProperty("strokeWidth" , strokeWidth[i]);
    }
    edge.clear();
    color.clear();
    strokeWidth.clear();
}