#ifndef _EYETER_HIGHLIGHTER_H_
#define _EYETER_HIGHLIGHTER_H_

#include <QSyntaxHighlighter>
#include <QTextCharFormat>

class QTextDocument;

namespace EyeTER {
    namespace ui {

class Highlighter : public QSyntaxHighlighter {
    Q_OBJECT

 public:
    Highlighter(QTextDocument *parent = 0);

 protected:
    void highlightBlock(const QString &text);

 private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules_;

    QTextCharFormat keywordFormat_;
    QTextCharFormat quotationFormat_;
    QTextCharFormat functionFormat_;
};

}
}
#endif
