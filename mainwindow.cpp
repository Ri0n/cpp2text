#include <QRegExp>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_btnToCpp_clicked()
{
	/* c++11 here just for fun =) */
	ui->teCpp->setText([](const QStringList &l){
		QStringList escaped;
		QRegExp re("(\"|\\\\)");
		foreach (const QString &s, l) {
			QString s2 = s;
			escaped += s2.replace(re, "\\\\1");
		}
		QString ret = '"' + escaped.join("\\n\"\n\"") + '"';
		if (ret.endsWith("\n\"\"")) {
			ret.resize(ret.size() - 3);
		}
		return ret;
	}(ui->teText->toPlainText().split('\n')));
}

void MainWindow::on_btnToText_clicked()
{
	QStringList lines = ui->teCpp->toPlainText().replace("\r\n", "\n").split('\n');
	QString text;
	QString unescaped;
	foreach (const QString &l, lines) {
		QString s = l.trimmed();
		s = s.mid(1, s.size() - 2);
		if (!s.size())
			continue;
		unescaped.clear();
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '\\') {
				if (i < s.size() - 1) {
					/* cpp has more escape sequences. but I need just next ones atm */
					if (s[i+1] == 'n')
						unescaped += '\n';
					else if (s[i+1] == 't')
						unescaped += '\t';
					else
						unescaped += s[i+1];
					i++;
				} else {
					break;
				}
			} else {
				unescaped += s[i];
			}
		}
		text += unescaped;
	}
	ui->teText->setPlainText(text);
}
