#ifndef _EYETER_OPERATOR_MODEL_H_
#define _EYETER_OPERATOR_MODEL_H_

#include <QAbstractTableModel>

namespace EyeTER {
    namespace ui {

class OperatorModel : public QAbstractTableModel {
    Q_OBJECT
 public:
    OperatorModel(QObject *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
};

}
}
#endif
