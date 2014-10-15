#include "Highlighter.h"

namespace EyeTER {
    namespace ui {

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat_.setForeground(Qt::darkBlue);
    keywordFormat_.setFontWeight(QFont::Bold);

    rule.pattern = QRegExp("\\b("
                           "if|else|elseif|endif|"
                           "for|to|continue|endfor|"
                           "while|whileend"
                           ")\\b");
    rule.format = keywordFormat_;
    highlightingRules_.append(rule);

    quotationFormat_.setForeground(Qt::darkRed);
    rule.pattern = QRegExp("\".*\"");
    rule.format = quotationFormat_;
    highlightingRules_.append(rule);

    functionFormat_.setForeground(Qt::blue);
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat_;
    highlightingRules_.append(rule);
}

void Highlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules_) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
}

}
}
