#include <QIcon>

#include "OperatorModel.h"

namespace EyeTER {
    namespace ui {

OperatorModel::OperatorModel(QObject *parent)
    :QAbstractTableModel(parent)
{
}

int OperatorModel::rowCount(const QModelIndex & /*parent*/) const
{
   return 2;
}

int OperatorModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 3;
}

QVariant OperatorModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole) {
       return QString("Row%1Column%2")
                   .arg(index.row() + 1)
                   .arg(index.column() +1);
    } else {
        if(index.column() == 0 && role == Qt::DecorationRole)
            return QIcon("res/icons/function.png");
    }

    return QVariant();
}

}
}
