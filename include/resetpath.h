#ifndef RESETPATH_H
#define RESETPATH_H

#include <vector>
#include <QObject>
#include <QVariant>

class ResetPath
{
public:
    ResetPath();
    void set_edges(QObject*, QVariant, QVariant);
    void reset();
private:
    std::vector <QObject*> edge;
    std::vector <QVariant> color;
    std::vector <QVariant> strokeWidth;
};

#endif // RESETPATH_H
