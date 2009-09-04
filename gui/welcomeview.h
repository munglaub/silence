#ifndef WELCOMEVIEW_H
#define WELCOMEVIEW_H

#include <QGridLayout>
#include <QLabel>
#include <QWidget>

class WelcomeView : public QWidget
{
	public:
		~WelcomeView();

		static WelcomeView* create();

	protected:
		WelcomeView(QWidget *parent = 0);

	private:
		static WelcomeView *welcomeview;

		QGridLayout *layout;
		QLabel	*icon,
				*welcome,
				*versionCap,
				*versionVal,
				*authorCap,
				*authorVal,
				*licenseCap,
				*licenseVal;
};

#endif // WELCOMEVIEW_H

