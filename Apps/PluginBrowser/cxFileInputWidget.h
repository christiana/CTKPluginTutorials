#ifndef CXFILEINPUTWIDGET_H
#define CXFILEINPUTWIDGET_H

#include <QWidget>
class QLabel;
class QLineEdit;
class QTextEdit;
class QToolButton;
class QGridLayout;
class QAction;

namespace cx
{

/** 
 *	Widget for displaying, editing and browsing for a filename.
 *  \sa FileSelectWidget
 *
 * \ingroup cx_resource_widgets
 * \date 28 Oct 2013, 2013
 * \author christiana
 */
class FileInputWidget : public QWidget
{
	Q_OBJECT
public:
	FileInputWidget(QWidget* parent=0);

	void setDescription(QString text);
	void setFilename(QString text);
	void setHelp(QString text);
	void setBrowseHelp(QString text);
	QString getFilename() const;
	QString getAbsoluteFilename() const;
	void setBasePath(QString path);
	void setUseRelativePath(bool on);

signals:
	void fileChanged();

private slots:
	void browse();
	void updateColor();
private:
	void updateHelpInternal();
	void widgetHasBeenChanged();

	QString mBasePath;
	bool mUseRelativePath;
	QString mBaseHelp;

	QLabel* mDescription;
	QLineEdit* mFilenameEdit;
	QToolButton* mBrowseButton;
	QGridLayout* mLayout;
	QAction* mBrowseAction;
};


/**
 *	Widget for displaying, editing and browsing for a filename.
 *  \sa FileSelectWidget
 *
 * \ingroup cx_resource_widgets
 * \date 2014-04-17
 * \author christiana
 */
class MultiFileInputWidget : public QWidget
{
	Q_OBJECT
public:
	MultiFileInputWidget(QWidget* parent=0);

	void setDescription(QString text);
	void setFilenames(QStringList text);
//	void addFilename(QString text);
	void setHelp(QString text);
	void setBrowseHelp(QString text);
	QStringList getFilenames() const;
	QStringList getAbsoluteFilenames() const;
	void setBasePath(QString path);
	void setUseRelativePath(bool on);

signals:
	void fileChanged();

private slots:
	void browse();
	void updateColor();
	void evaluateTextChanges();
private:
	void updateHelpInternal();
	void widgetHasBeenChanged();
	QStringList convertToAbsoluteFilenames(QStringList text) const;
	QString convertToAbsoluteFilename(QString text) const;
	QString convertFilenamesToTextEditText(QStringList files) const;
	QString convertToPresentableFilename(QString text) const;

	QStringList mLastFilenames;
	QString mBasePath;
	bool mUseRelativePath;
	QString mBaseHelp;

	QLabel* mDescription;
	QTextEdit* mFilenameEdit;
	QToolButton* mBrowseButton;
	QGridLayout* mLayout;
	QAction* mBrowseAction;
};

} // namespace cx

#endif // CXFILEINPUTWIDGET_H
