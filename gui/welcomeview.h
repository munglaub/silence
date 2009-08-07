#ifndef WELCOMEVIEW_H
#define WELCOMEVIEW_H

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
};

#endif // WELCOMEVIEW_H

